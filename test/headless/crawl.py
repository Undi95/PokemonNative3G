#!/usr/bin/env python3
"""Explorateur du jeu (docs/DEVTOOLS.md, « Explorateur ») : chaque carte, téléporté sur son premier warp (là où l'on
arrive d'habitude), une capture, puis chaque PNJ présent et chaque panneau, avec A jusqu'au bout de ce qu'ils disent
(puis B pour sortir d'un menu ; les combats sont faits, avec un MEWTWO N.100). Garde les textes, les combats, les
anomalies des détecteurs du jeu et les erreurs (personne à qui parler, script sans fin, gel, plantage) dans
build/headless/crawl/atlas.json, et un résumé dans build/headless/crawl/rapport.txt. Les cartes vont par lots, chaque
lot dans un jeu ; un jeu qui plante ou gèle est relancé, et l'exploration reprend à l'interaction suivante.

Chaque région part de sa sauvegarde de début de partie (fixtures kanto et hoenn).

usage: crawl.py BINAIRE [--cartes REGEX] [--jobs N] [--lot N] [--sans-parler] [--out DIR] [--rapport-seul]
"""

import argparse
import concurrent.futures
import json
import os
import re
import shutil
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import driver  # noqa: E402
import maps  # noqa: E402
import names  # noqa: E402
from driver import (GameError, continue_game, fight_battle, finish_dialog, mark, talk_to,  # noqa: E402
                    talk_to_object)
from headless import BUILD_DIR, REPO_DIR, fixture  # noqa: E402

# Images qu'une interaction (ou une arrivée) peut prendre, combats compris : au-delà, le script ne finit pas (le
# joueur repoussé en boucle par un PNJ, un menu dont on ne sort pas...)
FRAMES_PER_STEP = 20000
MAX_FRAMES = 50_000_000
# Ce que dit une interaction, gardé dans l'atlas (les textes de plus servent rarement)
MAX_TEXTS = 40
# Les états de partie de l'exploration (--etat), posés après le chargement de la sauvegarde de début de partie : des
# actions du menu DEBUG (jeu.debug, par leur nom) et des drapeaux (scripts.flag, par leur nom)
STATES = {
    "debut": [],
    # L'arrivée à Kanto dans le vrai jeu : le ferry ne part qu'après la Ligue de Hoenn
    "champion": [("scripts.flag", "FLAG_SYS_GAME_CLEAR", 1), ("scripts.flag", "FLAG_SYS_POKEDEX_GET", 1),
                 ("scripts.flag", "FLAG_SYS_POKENAV_GET", 1)]
                + [("scripts.flag", f"FLAG_BADGE0{i}_GET", 1) for i in range(1, 9)],
    # Les deux Ligues finies, comme le testeur avec le menu DEBUG
    "fin": [("jeu.debug", "Débloquer les 2 POKéDEX"), ("jeu.debug", "Ajout objets"), ("jeu.debug", "Pass îles Sevii"),
            ("jeu.debug", "Deux Ligues finies"), ("jeu.debug", "POKé MONTURE + badges")],
}
# Et les deux histoires finies : l'avancement déduit des scripts (scripts.histoire, tools/debug_states.py)
STATES["histoire"] = STATES["fin"] + [("scripts.histoire", 2)]


def apply_state(game, state):
    """Pose l'état de partie (STATES) ; une action ou un drapeau inconnu est une erreur."""
    actions = {line.split(" ", 1)[1]: int(line.split(" ", 1)[0]) for line in game.dev("jeu.debug").splitlines()}
    for command, name, *value in STATES[state]:
        reply = game.dev(command, actions[name]) if command == "jeu.debug" else game.dev(command, name, *value)
        if "refuse" in reply:
            raise GameError(f"état {state} : {command} {name} : {reply.strip()}")


# Les écrans qui durent (Panthéon, crédits) : on les laisse aller au bout
LONG_SCREENS = re.compile(r"HallOfFame|Hof|Credits")
# Les écrans d'un défi lancé par un PNJ (Zone de Combat, Tentes, concours) : ils ne se quittent qu'en jouant le défi
CHALLENGE_SCREENS = re.compile(r"SelectScreen|Swap_|Contest|PyramidBag|DomeTourney|ArenaFunction|Factory|Blender")
# Les attaques du MEWTWO des combats (Explorer.give_mewtwo)
STRONG_MOVES = ("MOVE_PSYCHIC", "MOVE_ICE_BEAM", "MOVE_THUNDERBOLT", "MOVE_FLAMETHROWER")
# Les salles où l'on n'entre que pendant un défi (Zone de Combat, Tentes, Mont Combat), un concours, un link ou avec
# un dresseur E-Reader, et les Bases Secrètes (chargées avec la base d'un joueur, ou reçue par Record Mixing) : y
# arriver par téléport, hors défi, n'a pas de sens (combat sans données, plantage). Elles sont à tester par un vrai
# défi ; l'explorateur les liste à part.
CHALLENGE_ROOMS = re.compile(r"BattleTent(Corridor|BattleRoom)$|^BattleColosseum|^TradeCenter$|^RecordCorner$|"
                             r"^UnionRoom$|^(Unused)?ContestHall|^SevenIsland_House_Room2$|"
                             r"^SootopolisCity_MysteryEventsHouse_B1F$|^TrainerTower_(\dF|Roof|Elevator)$|"
                             r"^SecretBase_|^BattlePyramidSquare|^TrainerHill_(\dF|Roof|Elevator)$|"
                             r"^BattleFrontier_Battle\w*(Elevator|Corridor|BattleRoom|PartnerRoom|Floor|Top|"
                             r"ThreePathRoom|Room(Normal|Final|WildMons))$")


def all_maps():
    names = []
    for name in sorted(os.listdir(os.path.join(REPO_DIR, "data", "maps"))):
        if not os.path.exists(os.path.join(REPO_DIR, "data", "maps", name, "map.json")):
            continue
        try:
            maps.find_map(name)
        except KeyError:
            continue
        names.append(name)
    return names


_GROUPS = json.load(open(os.path.join(REPO_DIR, "data", "maps", "map_groups.json")))


def region(name):
    """kanto ou hoenn : la région d'une carte, par son groupe (gMapGroup_Kanto...)."""
    for group in _GROUPS["group_order"]:
        if name in _GROUPS[group]:
            return "kanto" if group.startswith("gMapGroup_Kanto") else "hoenn"
    return "hoenn"


def map_info(name):
    with open(os.path.join(REPO_DIR, "data", "maps", name, "map.json"), encoding="utf-8") as f:
        return json.load(f)


def spawn_point(name):
    """Où arriver : le premier warp (on y arrive d'habitude), sinon la case praticable la plus proche du centre."""
    info = map_info(name)
    the_map = maps.load(name)
    for warp in info.get("warp_events") or []:
        if 0 <= warp["x"] < the_map.width and 0 <= warp["y"] < the_map.height:
            return warp["x"], warp["y"]
    cx, cy = the_map.width // 2, the_map.height // 2
    tiles = [(x, y) for y in range(the_map.height) for x in range(the_map.width) if the_map.tile(x, y) == "."]
    if not tiles:
        return cx, cy
    return min(tiles, key=lambda t: abs(t[0] - cx) + abs(t[1] - cy))


# Le côté d'où un panneau se lit (player_facing_dir) : le joueur regarde dans cette direction
SIGN_FACING = {"BG_EVENT_PLAYER_FACING_NORTH": "UP", "BG_EVENT_PLAYER_FACING_SOUTH": "DOWN",
               "BG_EVENT_PLAYER_FACING_EAST": "RIGHT", "BG_EVENT_PLAYER_FACING_WEST": "LEFT"}


def targets(name):
    """Les PNJ (avec un script), les panneaux et les objets cachés de la carte : {genre, x, y, script, portee,
    cote}, cote = la direction où regarder pour leur parler (None : de n'importe quel côté)."""
    info = map_info(name)
    found = []
    for index, obj in enumerate(info.get("object_events") or []):
        script = obj.get("script", "0x0")
        if script not in ("0x0", "0", "") and "x" in obj:
            reach = int(obj.get("movement_range_x", 0)) + int(obj.get("movement_range_y", 0))
            # localId : son rang dans object_events, à partir de 1 (tools/mapjson)
            found.append({"genre": "pnj", "x": obj["x"], "y": obj["y"], "script": script, "portee": reach,
                          "cote": None, "dessin": obj.get("graphics_id", ""), "id": index + 1})
    for bg in info.get("bg_events") or []:
        if bg.get("type") == "sign" and bg.get("script", "0x0") not in ("0x0", "0", ""):
            found.append({"genre": "panneau", "x": bg["x"], "y": bg["y"], "script": bg["script"], "portee": 0,
                          "cote": SIGN_FACING.get(bg.get("player_facing_dir"))})
        elif bg.get("type") == "hidden_item":
            found.append({"genre": "objet caché", "x": bg["x"], "y": bg["y"], "script": bg["item"], "portee": 0,
                          "cote": None})
    return found


def spots(name, x, y, side=None):
    """Où se tenir pour parler à ce qui est en (x, y) : [(sx, sy, direction)], les cases à côté, puis à deux cases
    (de l'autre côté d'un comptoir)."""
    the_map = maps.load(name)
    found = []
    for distance in (1, 2):
        for direction, (dx, dy) in maps.DIRECTIONS.items():
            if side and direction != side:
                continue
            sx, sy = x - dx * distance, y - dy * distance
            # L'eau aussi (« ~ ») : le téléport y pose le joueur, de quoi parler aux nageurs
            if the_map.tile(sx, sy) in ".g~" and (sx, sy) not in the_map.warps:
                if distance == 1 or the_map.tile(x - dx, y - dy) == "#":
                    found.append((sx, sy, direction))
    return found


def give_mewtwo(game):
    """Un MEWTWO N.100 avec les 4 attaques de STRONG_MOVES, en dernier de l'équipe."""
    game.give_mon("SPECIES_MEWTWO", 100)
    game.wait(1)                # l'équipe de l'état est celle de la dernière image
    slot = len(game.state.party) - 1
    for place, move in enumerate(STRONG_MOVES):
        reply = game.dev("joueur.capacite", slot, place, names.number(move))
        if "refuse" in reply:
            raise GameError(f"joueur.capacite : {reply.strip()}")


def texts_since(game, before):
    return [text for _, _, text in game.texts[before:] if text.strip() not in ("", "▶")][:MAX_TEXTS]


class Explorer:
    def __init__(self, binary, out_dir, save, state="debut", options=()):
        self.binary, self.out_dir, self.save, self.state = binary, out_dir, save, state
        self.options = options      # [(N, V)] : jeu.options N V au départ de chaque jeu (--options)
        self.game = None
        self.starts = 0

    def alive(self):
        return self.game is not None and self.game.proc.poll() is None

    def start(self):
        self.stop()
        self.starts += 1
        # Un dossier par jeu lancé : le journal d'un jeu qui a planté reste
        out = self.out_dir if self.starts == 1 else f"{self.out_dir}_{self.starts}"
        self.game = driver.Game(self.binary, out, save=self.save, max_frames=MAX_FRAMES)
        continue_game(self.game)
        self.give_mewtwo()
        self.game.dev("jeu.rencontres", 0)
        apply_state(self.game, self.state)
        # Texte rapide, sans animations de combat (OPTION_TEXT_SPEED, OPTION_BATTLE_SCENE_OFF) : les combats de
        # la Ligue tiennent dans le budget
        self.game.dev("jeu.options", 0, 2)
        self.game.dev("jeu.options", 4, 1)
        # STYLE COMBAT : DEFINI, sans la question « changer de POKéMON ? » (fight_battle y répondrait OUI : la
        # sauvegarde de Hoenn a son starter)
        self.game.dev("jeu.options", 3, 1)
        for option, value in self.options:
            self.game.dev("jeu.options", option, value)

    def give_mewtwo(self):
        """Le MEWTWO N.100 des combats, en dernier de l'équipe, avec 4 attaques (50 PP) : de lui-même, il n'en a
        qu'une (PSYKO, 10 PP), puis AMNESIE, SOIN, RUNE PROTECT, et le combat ne finit plus."""
        give_mewtwo(self.game)

    def stop(self):
        if self.game is not None:
            try:
                self.game.finish()
            except Exception:
                pass
            self.game = None

    def within_budget(self, action):
        """Fait action(game) en FRAMES_PER_STEP images au plus (et dans le budget de l'action qui l'appelle)."""
        game = self.game
        outer = game.max_frames
        game.max_frames = min(outer, game.frames + FRAMES_PER_STEP)
        try:
            return action(game)
        finally:
            game.max_frames = outer

    def finish(self, game):
        """Jusqu'au bout de ce qui se passe : A ; puis B pour sortir d'un menu où A ne mène nulle part ; puis B, A, A
        ou B, HAUT, A, A (quitter ? OUI : Easy Chat, horloge) ; puis START, A, A (écran des noms : OK)."""
        error = None
        # Panthéon et crédits (après la Ligue) : des milliers d'images, A de temps en temps
        while LONG_SCREENS.search(game.function(game.state.cb2)):
            game.tap("A", hold=2, gap=60)
        for buttons, limit in ((("A",), 150), (("B",), 60), (("B", "A", "A"), 45), (("B", "UP", "A", "A"), 40),
                               (("START", "A", "A"), 30)):
            try:
                if len(buttons) == 1:
                    return finish_dialog(game, button=buttons[0], limit=limit, answers={"surnom": "B"},
                                         on_battle=lambda g: fight_battle(g, limit=2000))
                for i in range(limit):
                    if game.state.free:
                        return finish_dialog(game, limit=20)
                    game.tap(buttons[i % len(buttons)], hold=2, gap=30)
            except GameError as e:
                if "still busy" not in str(e):
                    raise
                error = e
        raise error or GameError(f"still busy: {game.describe()}")

    def arrive(self, name, spawn):
        """Téléporte sur la carte, et finit ce qui s'y passe à l'arrivée (une scène peut durer). Renvoie l'erreur, ou
        None ; si le joueur ne peut toujours pas bouger, le jeu est arrêté (relancé pour la suite)."""
        def go(game):
            game.wait(2)
            if not game.state.free:
                self.finish(game)
            game.warp(name, *spawn)
        try:
            self.within_budget(go)
            return None
        except GameError as e:
            first = str(e)[:400]
        if not self.alive():
            return first
        try:
            self.within_budget(self.finish)
            return None
        except GameError as e:
            self.stop()
            return f"{first} ; puis : {str(e)[:300]}"

    def find_object(self, target):
        """Où est le PNJ maintenant (il se promène, ou un script l'a déplacé), par son localId ; None s'il n'est pas
        là (caché par un flag)."""
        state = self.game.state
        for pos, local_id in zip(state.objects, state.object_ids):
            if local_id == target["id"]:
                return pos
        return None

    def interact(self, name, target, spawn):
        record = dict(target)
        game = self.game
        before = mark(game)
        anomalies = len(game.anomalies)
        battles = len(game.battles)
        start_map = game.state.map

        def happened(said):
            return mark(game) > said or game.state.map != start_map or game.battles[battles:]

        def talk(game):
            # Téléporté à côté (le jeu ne charge que les PNJ près de la caméra), de chaque côté possible
            places = spots(name, target["x"], target["y"], target["cote"])
            if not places:
                record["inaccessible"] = True
                return
            for sx, sy, direction in places[:4]:
                if game.state.map != start_map or game.state.pos != (sx, sy):
                    error = self.arrive(name, (sx, sy))
                    if error:
                        if not self.alive():    # arrêté par arrive : relancé par explore
                            raise GameError(f"arrivée à côté : {error}")
                        record.setdefault("erreurs_arrivee", []).append(error)
                        continue
                    if game.state.map != start_map:
                        continue
                said = mark(game)
                if target["genre"] == "pnj":
                    pos = self.find_object(target)
                    if pos is None:
                        record["absent"] = True     # caché par un flag, ou parti
                        return
                    if pos != (target["x"], target["y"]):
                        # Il s'est promené : on va le voir à pied, ou par téléport (sur l'eau : un nageur)
                        record["bouge"] = True
                        try:
                            talk_to_object(game, *pos, finish=False)
                        except GameError:
                            near = spots(name, *pos)
                            error = self.arrive(name, near[0][:2]) if near else "personne où se tenir"
                            if error and not self.alive():  # arrêté par arrive : relancé par explore
                                raise GameError(f"arrivée à côté : {error}")
                            if error:
                                continue
                            talk_to(game, near[0][2], finish=False)
                        self.finish(game)
                        if happened(said):
                            return
                        continue
                talk_to(game, direction, finish=False)
                self.finish(game)
                if happened(said):
                    return
            record["muet"] = True

        try:
            self.within_budget(talk)
        except GameError as e:
            if record.get("bouge") and not any(window == 0 for _, window, _ in game.texts[before:]):
                # Un PNJ qui bouge sans cesse, rattrapé nulle part dans le budget : aucun dialogue (le nom de la
                # carte, à chaque téléport, ne compte pas)
                record["insaisissable"] = str(e)[:200]
            else:
                record["erreur"] = str(e)[:400]
        record["textes"] = texts_since(game, before)
        record["anomalies"] = [f"{kind} : {text}" for _, kind, text in game.anomalies[anomalies:]]
        record["combats"] = game.battles[battles:]
        if not self.alive():
            return record
        where = game.state.map_name or ""
        if "erreur" in record and (CHALLENGE_ROOMS.search(where)
                                   or CHALLENGE_SCREENS.search(game.function(game.state.cb2))):
            # Le PNJ a lancé un défi : à tester par un vrai défi (le jeu est relancé pour la suite)
            record["defi"] = f"{where} {game.function(game.state.cb2)}"
            del record["erreur"]
            self.stop()
            return record
        # Retour au calme, sur la carte, avec l'équipe soignée
        try:
            if not game.state.free:
                self.within_budget(self.finish)
            if game.state.map != start_map:
                record["vers"] = game.state.map_name
                error = self.arrive(name, spawn)
                if error:
                    raise GameError(error)
            if not any(m[1] == 100 for m in game.state.party):
                self.give_mewtwo()      # échangé, ou laissé à la pension
            game.heal()
        except GameError as e:
            record["erreur_retour"] = str(e)[:400]
            self.stop()     # le jeu est relancé pour la suite
        return record

    def explore(self, name, talk):
        result = {"carte": name, "interactions": [], "erreurs": []}
        begin = time.time()
        if not self.alive():
            self.start()
        game = self.game
        spawn = spawn_point(name)
        result["arrivee"] = spawn
        anomaly_count = len(game.anomalies)
        before = mark(game)
        error = self.arrive(name, spawn)
        if error:
            result["erreurs"].append(f"arrivée : {error}")
        result["textes_arrivee"] = texts_since(game, before)
        if self.alive():
            game.wait(30)
            game.shot(name)
            result["capture"] = os.path.join(game.shots_dir, name + ".ppm")
            result["ecran"] = game.function(game.state.cb2)
            result["sur_la_carte"] = game.state.map_name == name
        anomalies = [f"{kind} : {text}" for _, kind, text in game.anomalies[anomaly_count:]]
        if talk and self.alive() and game.state.map_name == name:
            for target in targets(name):
                if not self.alive():
                    self.start()
                    error = self.arrive(name, spawn)
                    if error:
                        result["erreurs"].append(f"retour après une relance : {error}")
                        break
                record = self.interact(name, target, spawn)
                result["interactions"].append(record)
                anomalies += record["anomalies"]
        result["anomalies"] = anomalies
        result["secondes"] = round(time.time() - begin, 1)
        return result


def run_batch(binary, names, out_dir, save, talk, state="debut", options=()):
    explorer = Explorer(binary, out_dir, save, state, options)
    results = []
    for name in names:
        try:
            results.append(explorer.explore(name, talk))
        except Exception as e:      # le jeu a planté ou gelé hors d'une interaction : relancé pour la carte suivante
            results.append({"carte": name, "interactions": [], "anomalies": [],
                            "erreurs": [f"jeu arrêté : {type(e).__name__}: {str(e)[:400]}"]})
            explorer.stop()
    explorer.stop()
    return results


# Un texte qui a l'air faux : un octet sans lettre (names.decode), un code {XX} pas remplacé, de l'anglais
SUSPECT_TEXT = re.compile(r"�|\{[0-9A-F]{2}\}|\b(the|you|your|this|that|with|have|what|is not|can't|don't|"
                          r"Pokémon Center|Poké Mart|PLAYER|RIVAL|STR_VAR)\b")


def suspect_texts(results):
    """(carte, texte) des textes qui ont l'air faux, chacun une fois."""
    seen = set()
    found = []
    for r in results:
        texts = list(r.get("textes_arrivee", []))
        for i in r.get("interactions", []):
            texts += i.get("textes", [])
        for text in texts:
            if text not in seen and SUSPECT_TEXT.search(text):
                seen.add(text)
                found.append((r["carte"], text))
    return found


def summary(results):
    lines = []
    suspects = suspect_texts(results)
    errors = [(r["carte"], e) for r in results for e in r.get("erreurs", [])]
    talk_errors = [(r["carte"], i) for r in results for i in r.get("interactions", [])
                   if "erreur" in i or "erreur_retour" in i]
    mute = [(r["carte"], i) for r in results for i in r.get("interactions", []) if i.get("muet")]
    unreachable = [(r["carte"], i) for r in results for i in r.get("interactions", []) if i.get("inaccessible")]
    anomalies = {}
    for r in results:
        for a in r.get("anomalies", []):
            anomalies.setdefault(a, []).append(r["carte"])
    talks = sum(1 for r in results for i in r.get("interactions", []) if not i.get("absent"))
    absent = sum(1 for r in results for i in r.get("interactions", []) if i.get("absent"))
    battles = sum(len(i.get("combats", [])) for r in results for i in r.get("interactions", []))
    explored = sum(1 for r in results if not r.get("salle_de_defi"))
    lines.append(f"{explored} cartes, {talks} interactions ({absent} PNJ absents, {battles} combats), "
                 f"{len(errors)} erreurs de carte, {len(talk_errors)} interactions en erreur, {len(mute)} muettes, "
                 f"{len(unreachable)} inaccessibles, {len(anomalies)} anomalies différentes, "
                 f"{len(suspects)} textes suspects")
    if anomalies:
        lines.append("\nAnomalies :")
        lines += [f"  {a}  ({', '.join(sorted(set(where))[:6])})" for a, where in sorted(anomalies.items())]
    if suspects:
        lines.append("\nTextes suspects :")
        lines += [f"  {name} : {text}".replace("\n", " / ") for name, text in suspects]
    if errors:
        lines.append("\nErreurs de carte :")
        lines += [f"  {name} : {e}" for name, e in errors]
    if talk_errors:
        lines.append("\nInteractions en erreur :")
        lines += [f"  {name} {i['genre']} {i['x']},{i['y']} ({i['script']}) : "
                  f"{i.get('erreur') or ''}{' / retour : ' + i['erreur_retour'] if 'erreur_retour' in i else ''}"
                  for name, i in talk_errors]
    if mute:
        lines.append("\nInteractions muettes (rien ne s'est passé) :")
        lines += [f"  {name} {i['genre']} {i['x']},{i['y']} ({i['script']})" for name, i in mute]
    if unreachable:
        lines.append("\nInaccessibles (aucune case où se tenir) :")
        lines += [f"  {name} {i['genre']} {i['x']},{i['y']} ({i['script']})" for name, i in unreachable]
    challenge_rooms = [r["carte"] for r in results if r.get("salle_de_defi")]
    if challenge_rooms:
        lines.append(f"\nSalles de défi, de concours ou de link, à tester par un vrai défi ({len(challenge_rooms)}) :")
        lines.append("  " + ", ".join(challenge_rooms))
    elusive = [(r["carte"], i) for r in results for i in r.get("interactions", []) if i.get("insaisissable")]
    if elusive:
        lines.append("\nPNJ insaisissables (ils bougent sans cesse ; rattrapés nulle part) :")
        lines += [f"  {name} {i['genre']} {i['x']},{i['y']} ({i['script']})" for name, i in elusive]
    challenges = [(r["carte"], i) for r in results for i in r.get("interactions", []) if i.get("defi")]
    if challenges:
        lines.append("\nDéfis lancés par un PNJ, à tester par un vrai défi :")
        lines += [f"  {name} {i['genre']} {i['x']},{i['y']} ({i['script']}) -> {i['defi']}" for name, i in challenges]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("binary")
    parser.add_argument("--cartes", default="", help="expression régulière sur le nom des cartes")
    parser.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 2) // 2))
    parser.add_argument("--lot", type=int, default=8, help="cartes par jeu")
    parser.add_argument("--sans-parler", action="store_true", help="seulement l'arrivée et la capture")
    parser.add_argument("--etat", default="debut", choices=sorted(STATES),
                        help="état de partie : debut (sauvegarde de début), champion (Hoenn fini, l'arrivée à Kanto), "
                             "fin (les deux Ligues), histoire (et l'avancement des deux histoires, déduit des scripts)")
    parser.add_argument("--out", default=None, help="par défaut build/headless/crawl (crawl-ETAT hors debut)")
    parser.add_argument("--rapport-seul", action="store_true", help="refait rapport.txt depuis atlas.json")
    parser.add_argument("--options", default="", help="N=V,... : options (jeu.options) au départ de chaque jeu, "
                                                      "par exemple 8=1 pour DIALOGUE = KANTO")
    args = parser.parse_args()
    options = [tuple(int(x) for x in pair.split("=")) for pair in args.options.split(",") if pair]
    if args.out is None:
        args.out = os.path.join(BUILD_DIR, "crawl" if args.etat == "debut" else f"crawl-{args.etat}")

    if args.rapport_seul:
        with open(os.path.join(args.out, "atlas.json"), encoding="utf-8") as f:
            report = summary(json.load(f))
        with open(os.path.join(args.out, "rapport.txt"), "w", encoding="utf-8") as f:
            f.write(report + "\n")
        print(report)
        return

    binary = os.path.abspath(args.binary)
    names = [n for n in all_maps() if re.search(args.cartes, n)]
    challenge_rooms = [n for n in names if CHALLENGE_ROOMS.search(n)]
    names = [n for n in names if n not in challenge_rooms]
    shutil.rmtree(args.out, ignore_errors=True)
    os.makedirs(args.out)
    # Chaque région part de sa sauvegarde : le début de partie de RF (Bourg Palette) ou d'Émeraude (Bourg-en-Vol)
    batches = []
    for zone in ("kanto", "hoenn"):
        in_zone = [n for n in names if region(n) == zone]
        if in_zone:
            save = fixture(binary, zone)
            batches += [(in_zone[i:i + args.lot], save) for i in range(0, len(in_zone), args.lot)]
    print(f"{len(names)} cartes en {len(batches)} lots, {args.jobs} à la fois", flush=True)
    begin = time.time()
    results = []
    with concurrent.futures.ThreadPoolExecutor(args.jobs) as pool:
        futures = [pool.submit(run_batch, binary, batch, os.path.join(args.out, f"lot_{i:03}"), save,
                               not args.sans_parler, args.etat, options) for i, (batch, save) in enumerate(batches)]
        for done, future in enumerate(concurrent.futures.as_completed(futures), 1):
            results += future.result()
            print(f"  {done}/{len(batches)} lots, {len(results)} cartes, {time.time() - begin:.0f} s", flush=True)
    results += [{"carte": n, "salle_de_defi": True, "interactions": [], "erreurs": [], "anomalies": []}
                for n in challenge_rooms]
    results.sort(key=lambda r: r["carte"])
    with open(os.path.join(args.out, "atlas.json"), "w", encoding="utf-8") as f:
        json.dump(results, f, ensure_ascii=False, indent=1)
    report = summary(results)
    with open(os.path.join(args.out, "rapport.txt"), "w", encoding="utf-8") as f:
        f.write(report + "\n")
    print(report)


if __name__ == "__main__":
    main()
