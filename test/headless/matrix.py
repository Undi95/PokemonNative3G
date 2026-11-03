#!/usr/bin/env python3
"""Grille options × écrans (docs/DEVTOOLS.md, « Grille ») : les écrans du jeu (menu Start, équipe, résumé, sac,
Pokédex, carte de dresseur, sauvegarde, options, dialogues, boutique, PC, combats), dans les deux régions, avec les
9 options d'affichage combinées pour que chaque paire de valeurs de deux options soit vue au moins une fois.

Chaque (région, combinaison) est un jeu, parti de la sauvegarde de début de partie de la région (fixtures kanto et
hoenn), avec un MEWTWO N.100. Une capture par étape de chaque écran ; une planche par écran dans
build/headless/matrix/planches/ (une ligne par jeu) ; les anomalies des détecteurs et les erreurs (écran qui ne
s'ouvre pas, qui ne se ferme pas, gel) dans rapport.txt.

usage: matrix.py BINAIRE [--ecrans REGEX] [--regions kanto,hoenn] [--jobs N] [--out DIR]
"""

import argparse
import concurrent.futures
import itertools
import json
import os
import re
import shutil
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import crawl  # noqa: E402
import driver  # noqa: E402
from driver import (GameError, continue_game, fight_battle, finish_dialog, mark, saw_text, talk_to,  # noqa: E402
                    wait_until)
from headless import BUILD_DIR, fixture  # noqa: E402

# Les options d'affichage (index de jeu.options, src/debug_tools.c), toutes à deux valeurs : 0 Hoenn, 1 Kanto
OPTIONS = [("PERSO", 6), ("DIALOGUE", 8), ("POLICE", 9), ("POKEDEX", 10), ("MENUS", 11), ("BOITES", 12),
           ("SAC", 13), ("POKEMON", 14), ("JOURNUIT", 16)]
OPTION_FRAME = 1        # le cadre des fenêtres (0 à 19), changé à chaque combinaison
OPTION_BATTLE_STYLE = 3

# Les entrées du menu Start (MENU_ACTION_*, src/start_menu.c)
MENU_POKEDEX, MENU_POKEMON, MENU_BAG, MENU_POKENAV, MENU_PLAYER, MENU_SAVE, MENU_OPTION = range(7)

# Par région : où se mettre entre deux écrans, l'herbe, une boutique, un dresseur
REGIONS = {
    "kanto": {"home": "PalletTown", "grass": "Route1", "mart": "PewterCity_Mart", "trainer": ("Route3", 32, 6)},
    "hoenn": {"home": "LittlerootTown", "grass": "Route101", "mart": "OldaleTown_Mart",
              "trainer": ("Route102", 33, 14)},
}


def combos():
    """Les combinaisons des options : tout Hoenn, tout Kanto, puis de quoi voir chaque paire de valeurs de deux
    options (choix glouton, toujours le même)."""
    n = len(OPTIONS)

    def pairs(row):
        return {(i, row[i], j, row[j]) for i in range(n) for j in range(i + 1, n)}

    rows = [(0,) * n, (1,) * n]
    missing = {(i, a, j, b) for i in range(n) for j in range(i + 1, n) for a in (0, 1) for b in (0, 1)}
    for row in rows:
        missing -= pairs(row)
    candidates = list(itertools.product((0, 1), repeat=n))
    while missing:
        best = max(candidates, key=lambda row: len(pairs(row) & missing))
        rows.append(best)
        missing -= pairs(best)
    return rows


def combo_name(row):
    """« DIALOGUE POLICE ... » : les options à Kanto (1), ou « tout-hoenn »."""
    names = [name for (name, _), value in zip(OPTIONS, row) if value]
    return "-".join(names) if names else "tout-hoenn"


# --- Aller d'un écran à l'autre ------------------------------------------------------------------------------------

def back_to_free(game, limit=30):
    """B jusqu'à pouvoir bouger (sortir d'un menu, d'un écran), puis la fin de ce qui parle encore."""
    for _ in range(limit):
        if game.state.free:
            return finish_dialog(game, limit=60)
        game.tap("B", hold=2, gap=20)
    raise GameError(f"l'écran ne se ferme pas avec B : {game.describe()}")


def open_start_entry(game, action):
    """Ouvre l'entrée du menu Start qui fait action (MENU_*)."""
    wait_until(game, lambda s: s.free)
    game.tap("START")
    game.wait(30)
    entries, cursor = game.start_menu()
    target = next((i for i, (a, _) in enumerate(entries) if a == action), None)
    if target is None:
        raise GameError(f"pas d'entrée {action} dans le menu Start : {entries}")
    count = len(entries)
    delta = (target - cursor) % count
    if delta <= count // 2:
        game.tap("DOWN", delta, gap=8)
    else:
        game.tap("UP", count - delta, gap=8)
    game.tap("A")


def tap_until_text(game, words, button="A", limit=30):
    """Appuie jusqu'à ce qu'un texte avec ces mots s'écrive (un menu, la suite d'un dialogue)."""
    since = mark(game)
    for _ in range(limit):
        if saw_text(game, words, since):
            return
        game.tap(button, gap=30)
    raise GameError(f"pas de texte « {words} » : {game.describe()}")


def talk_at(game, map_name, x, y):
    """Va à côté de ce qui est en (x, y) sur la carte et lui parle (sans aller au bout)."""
    places = crawl.spots(map_name, x, y)
    if not places:
        raise GameError(f"personne où se tenir près de {map_name} {x},{y}")
    sx, sy, direction = places[0]
    game.warp(map_name, sx, sy)
    talk_to(game, direction, finish=False)


class Screens:
    """Chaque écran : de la carte (joueur libre) à la carte, en appelant shot(nom) à chaque étape."""

    def __init__(self, game, region, shot):
        self.game, self.region, self.shot = game, REGIONS[region], shot

    def start_menu(self):
        game = self.game
        game.tap("START")
        game.wait(40)
        self.shot("menu")
        back_to_free(game)

    def party(self):
        game = self.game
        open_start_entry(game, MENU_POKEMON)
        game.wait(120)
        self.shot("equipe")
        game.tap("A")
        game.wait(40)
        self.shot("choix")
        back_to_free(game)

    def summary(self):
        game = self.game
        open_start_entry(game, MENU_POKEMON)
        game.wait(120)
        game.tap("A")
        game.wait(40)
        game.tap("A")                   # RÉSUMÉ, la première entrée (MEWTWO ne connaît pas de capacité de terrain)
        game.wait(120)
        self.shot("page1")
        for page in range(2, 5):
            game.tap("RIGHT")
            game.wait(60)
            self.shot(f"page{page}")
        back_to_free(game)

    def bag(self):
        game = self.game
        open_start_entry(game, MENU_BAG)
        game.wait(120)
        self.shot("poche1")
        for pocket in range(2, 6):
            game.tap("RIGHT")
            game.wait(50)
            self.shot(f"poche{pocket}")
        back_to_free(game)

    def pokedex(self):
        game = self.game
        open_start_entry(game, MENU_POKEDEX)
        game.wait(150)
        self.shot("ouverture")
        game.tap("A")
        game.wait(60)
        self.shot("liste")
        game.tap("A")
        game.wait(90)
        self.shot("fiche")
        back_to_free(game)

    def pokenav(self):
        game = self.game
        open_start_entry(game, MENU_POKENAV)
        game.wait(180)
        for item in range(5):           # chaque entrée et sa description ; la 5e revient à la première
            self.shot(f"menu{item + 1}")
            game.tap("DOWN")
            game.wait(40)
        game.tap("A")                   # CARTE DE HOENN
        game.wait(150)
        self.shot("carte")
        game.tap("B")
        game.wait(120)
        game.tap("DOWN", 2, gap=20)     # MATCH CALL
        game.tap("A")
        game.wait(150)
        self.shot("match-call")
        game.tap("B")
        game.wait(120)
        game.tap("B")
        game.wait(150)
        back_to_free(game)

    def trainer_card(self):
        game = self.game
        open_start_entry(game, MENU_PLAYER)
        game.wait(120)
        self.shot("recto")
        game.tap("A")
        game.wait(90)
        self.shot("verso")
        game.tap("B")                   # au verso, B retourne la carte ; SELECT au recto : la carte de l'autre région
        game.wait(90)
        game.tap("SELECT")
        game.wait(180)
        self.shot("autre-recto")
        game.tap("A")
        game.wait(90)
        self.shot("autre-verso")
        back_to_free(game)

    def save(self):
        game = self.game
        open_start_entry(game, MENU_SAVE)
        game.wait(200)                  # la question écrite en entier
        self.shot("question")
        back_to_free(game)

    def options(self):
        game = self.game
        open_start_entry(game, MENU_OPTION)
        game.wait(120)
        self.shot("page1")
        game.tap("R")
        game.wait(60)
        self.shot("page2")
        game.tap("DOWN", 9, gap=12)
        game.wait(40)
        self.shot("page2-bas")
        back_to_free(game)

    def dialog_sign(self):
        game = self.game
        home = self.region["home"]
        sign = next(t for t in crawl.targets(home) if t["genre"] == "panneau")
        talk_at(game, home, sign["x"], sign["y"])
        game.wait(90)
        self.shot("panneau")
        finish_dialog(game)

    def dialog_npc(self):
        """Le premier PNJ de la carte qui parle (les moins mobiles d'abord : certains sont cachés à ce moment de
        l'histoire), au milieu de ce qu'il dit."""
        game = self.game
        home = self.region["home"]
        npcs = sorted((t for t in crawl.targets(home) if t["genre"] == "pnj"), key=lambda t: t["portee"])
        for npc in npcs:
            since = mark(game)
            talk_at(game, home, npc["x"], npc["y"])
            game.wait(90)
            if any(window == 0 for _, window, _ in game.texts[since:]):
                self.shot("pnj")
                finish_dialog(game, answers={"surnom": "B"})
                return
            back_to_free(game)
        raise GameError(f"aucun PNJ de {home} ne parle")

    def shop(self):
        game = self.game
        mart = self.region["mart"]
        clerk = next(t for t in crawl.targets(mart) if t["genre"] == "pnj" and "Clerk" in t["script"])
        talk_at(game, mart, clerk["x"], clerk["y"])
        game.wait(90)
        self.shot("bonjour")
        tap_until_text(game, "ACHETER")
        game.wait(30)
        self.shot("menu")
        game.tap("A")                   # ACHETER
        game.wait(120)
        self.shot("liste")
        game.tap("A")
        game.wait(60)
        self.shot("quantite")
        back_to_free(game)

    def pc(self):
        game = self.game
        game.script("EventScript_PC")
        game.wait(90)
        self.shot("allume")
        game.tap("A")
        game.wait(60)
        self.shot("quel-pc")
        game.tap("A")                   # PC de ??? (ou de LANETTE, de LÉO) : le Système de Stockage
        game.wait(90)
        tap_until_text(game, "RETIRER")
        game.wait(30)
        self.shot("stockage")
        game.tap("DOWN")                # DÉPOSER : l'écran des boîtes, avec l'équipe
        game.tap("A")
        game.wait(150)
        self.shot("boites")
        back_to_free(game)

    def wild_battle(self):
        game = self.game
        grass = self.region["grass"]
        the_map = crawl.maps.load(grass)
        tile = next((x, y) for y in range(the_map.height) for x in range(the_map.width)
                    if the_map.tile(x, y) == "g" and the_map.tile(x, y + 1) == "g")
        game.warp(grass, *tile)
        game.dev("jeu.rencontres", 1)
        try:
            for step in range(200):
                if self.in_transition():
                    break
                game.press("DOWN" if step % 2 == 0 else "UP", 16)
            else:
                raise GameError("pas de Pokémon sauvage en 200 pas")
        finally:
            game.dev("jeu.rencontres", 0)
        self.battle_shots()

    def trainer_battle(self):
        game = self.game
        map_name, x, y = self.region["trainer"]
        talk_at(game, map_name, x, y)
        for _ in range(80):             # A dans ce qu'il dit avant le combat
            if self.in_transition():
                break
            game.tap("A", hold=2, gap=4)
        else:
            raise GameError(f"le combat ne commence pas : {game.describe()}")
        self.battle_shots()

    def in_transition(self):
        """La transition vers un combat a commencé (tâche Task_BattleTransition, ou déjà le combat)."""
        state = self.game.state
        return state.battle or any("BattleTransition" in self.game.function(t) for t in state.tasks)

    def battle_shots(self):
        """La transition (sur la carte : teinte jour/nuit, cadre), l'arrivée, le menu d'action et celui des
        capacités, puis le combat jusqu'au bout."""
        game = self.game
        for step in range(3):
            game.wait(20)
            self.shot(f"transition{step + 1}")
        wait_until(game, lambda s: s.battle, step=4, limit=600)
        game.wait(30)
        self.shot("arrivee")
        texts = mark(game)
        for _ in range(60):             # jusqu'au menu d'action (« Que doit faire ... ? »)
            if any("Que doit faire" in " ".join(t.split()) for _, _, t in game.texts[texts:]):
                break
            game.tap("A", gap=30)
        game.wait(60)
        self.shot("action")
        game.tap("A")
        game.wait(40)
        self.shot("capacites")
        game.tap("B")
        game.wait(20)
        fight_battle(game)
        finish_dialog(game, answers={"surnom": "B"})


SCREENS = ["start_menu", "party", "summary", "bag", "pokedex", "pokenav", "trainer_card", "save", "options",
           "dialog_sign", "dialog_npc", "shop", "pc", "wild_battle", "trainer_battle"]


def run_one(binary, region, index, row, out_dir, screens):
    """Un jeu : la région, la combinaison d'options row, chaque écran. Renvoie {jeu, captures, erreurs, anomalies}."""
    name = f"{region}_{index:02}"
    result = {"jeu": name, "region": region, "options": combo_name(row), "captures": {}, "erreurs": [],
              "anomalies": []}
    game = driver.Game(binary, os.path.join(out_dir, name), save=fixture(binary, region), max_frames=5_000_000)
    try:
        continue_game(game)
        crawl.give_mewtwo(game)     # 4 attaques : les combats finissent
        # De quoi remplir les écrans : un 2e Pokémon qui tient un objet, un objet de chaque poche
        game.give_mon("SPECIES_PIKACHU", 25, "ITEM_ORAN_BERRY")
        for item, count in (("ITEM_POTION", 5), ("ITEM_SUPER_POTION", 3), ("ITEM_POKE_BALL", 10),
                            ("ITEM_GREAT_BALL", 2), ("ITEM_TM01", 1), ("ITEM_ORAN_BERRY", 4), ("ITEM_MACH_BIKE", 1)):
            game.item(item, count)
        game.dev("jeu.rencontres", 0)
        for flag in ("FLAG_SYS_POKEDEX_GET", "FLAG_KANTO_SYS_POKEDEX_GET", "FLAG_SYS_POKEMON_GET",
                     "FLAG_SYS_POKENAV_GET", "FLAG_ADDED_MATCH_CALL_TO_POKENAV"):
            game.flag(flag, 1)
        for (_, option), value in zip(OPTIONS, row):
            game.dev("jeu.options", option, value)
        game.dev("jeu.options", OPTION_FRAME, (index * 7) % 20)
        # STYLE COMBAT : DEFINI, sans la question « changer de POKéMON ? » (fight_battle y répondrait OUI)
        game.dev("jeu.options", OPTION_BATTLE_STYLE, 1)
        home = REGIONS[region]["home"]
        spawn = crawl.spawn_point(home)
        for screen in screens:
            shots = []

            def shot(step, screen=screen, shots=shots):
                shots.append(game.shot(f"{screen}-{step}"))

            anomalies = len(game.anomalies)
            try:
                game.warp(home, *spawn)
                finish_dialog(game, limit=100)
                getattr(Screens(game, region, shot), screen)()
            except Exception as e:      # GameError, ou une erreur de la grille elle-même
                result["erreurs"].append(f"{screen} : {type(e).__name__}: {str(e)[:300]}")
                if game.proc.poll() is not None:
                    break
                try:
                    back_to_free(game)
                except GameError:
                    break
            result["captures"][screen] = shots
            result["anomalies"] += [f"{screen} : {kind} : {text}" for _, kind, text in game.anomalies[anomalies:]]
    except GameError as e:
        result["erreurs"].append(f"jeu : {str(e)[:300]}")
    finally:
        game.finish()
    return result


def sheets(results, out_dir):
    """Une planche par écran : une ligne par jeu (région, options), une colonne par capture."""
    from PIL import Image, ImageDraw

    folder = os.path.join(out_dir, "planches")
    os.makedirs(folder, exist_ok=True)
    label_width, width, height, gap = 230, 240, 160, 4
    screens = sorted({screen for r in results for screen in r["captures"]})
    for screen in screens:
        rows = [r for r in results if r["captures"].get(screen)]
        columns = max(len(r["captures"][screen]) for r in rows)
        sheet = Image.new("RGB", (label_width + columns * (width + gap), len(rows) * (height + gap)), (40, 40, 40))
        draw = ImageDraw.Draw(sheet)
        for i, r in enumerate(rows):
            y = i * (height + gap)
            draw.text((4, y + 4), r["jeu"], fill=(255, 255, 255))
            for j, word in enumerate(r["options"].split("-")):
                draw.text((4, y + 20 + j * 13), word, fill=(200, 200, 120))
            for j, path in enumerate(r["captures"][screen]):
                if os.path.exists(path):
                    sheet.paste(Image.open(path).convert("RGB"), (label_width + j * (width + gap), y))
        sheet.save(os.path.join(folder, f"{screen}.png"))
    return folder


def summary(results):
    lines = [f"{len(results)} jeux, {sum(len(r['erreurs']) for r in results)} erreurs, "
             f"{sum(len(r['anomalies']) for r in results)} anomalies"]
    for r in results:
        if r["erreurs"] or r["anomalies"]:
            lines.append(f"\n{r['jeu']} ({r['options']}) :")
            lines += [f"  ERREUR {e}" for e in r["erreurs"]]
            lines += [f"  ANOMALIE {a}" for a in r["anomalies"]]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("binary")
    parser.add_argument("--ecrans", default="", help="expression régulière sur le nom des écrans")
    parser.add_argument("--regions", default="kanto,hoenn")
    parser.add_argument("--combos", type=int, default=0, help="seulement les N premières combinaisons")
    parser.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 2) // 2))
    parser.add_argument("--out", default=os.path.join(BUILD_DIR, "matrix"))
    args = parser.parse_args()

    binary = os.path.abspath(args.binary)
    screens = [s for s in SCREENS if re.search(args.ecrans, s)]
    rows = combos()[:args.combos or None]
    shutil.rmtree(args.out, ignore_errors=True)
    os.makedirs(args.out)
    regions = args.regions.split(",")
    for region in regions:
        fixture(binary, region)         # faites une fois, avant les jeux en parallèle
    jobs = [(region, i, row) for region in regions for i, row in enumerate(rows)]
    print(f"{len(jobs)} jeux ({len(rows)} combinaisons × {len(regions)} régions), {len(screens)} écrans", flush=True)
    begin = time.time()
    results = []
    with concurrent.futures.ThreadPoolExecutor(args.jobs) as pool:
        futures = [pool.submit(run_one, binary, region, i, row, args.out, screens) for region, i, row in jobs]
        for done, future in enumerate(concurrent.futures.as_completed(futures), 1):
            results.append(future.result())
            print(f"  {done}/{len(jobs)} jeux, {time.time() - begin:.0f} s", flush=True)
    results.sort(key=lambda r: r["jeu"])
    with open(os.path.join(args.out, "grille.json"), "w", encoding="utf-8") as f:
        json.dump(results, f, ensure_ascii=False, indent=1)
    folder = sheets(results, args.out)
    report = summary(results)
    with open(os.path.join(args.out, "rapport.txt"), "w", encoding="utf-8") as f:
        f.write(report + "\n")
    print(report)
    print(f"planches : {folder}")


if __name__ == "__main__":
    main()
