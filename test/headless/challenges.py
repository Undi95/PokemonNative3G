"""Pilote des défis (docs/DEVTOOLS.md, « Défis ») : parle au préposé d'un défi (Zone de Combat, Tentes, Mont Combat,
Tour Dresseur, concours…), répond A à ses questions, choisit l'équipe ou les Pokémon de location, fait les combats,
jusqu'à N combats joués. Les scénarios challenge_*.py s'en servent ; ce qu'ils vérifient : le défi démarre, les
combats ont lieu, aucune anomalie, aucun plantage.
"""

import crawl
import names
from driver import GameError, fight_battle, mark, talk_to

# Une équipe autorisée à la Zone de Combat (MEWTWO y est interdit) : 4 Pokémon, pour les combats doubles
TEAM = [
    ("SPECIES_TYRANITAR", ("MOVE_ROCK_SLIDE", "MOVE_CRUNCH", "MOVE_EARTHQUAKE", "MOVE_ICE_BEAM")),
    ("SPECIES_METAGROSS", ("MOVE_METEOR_MASH", "MOVE_EARTHQUAKE", "MOVE_PSYCHIC", "MOVE_SHADOW_BALL")),
    ("SPECIES_SALAMENCE", ("MOVE_DRAGON_CLAW", "MOVE_FLAMETHROWER", "MOVE_EARTHQUAKE", "MOVE_AERIAL_ACE")),
    ("SPECIES_GARDEVOIR", ("MOVE_PSYCHIC", "MOVE_THUNDERBOLT", "MOVE_CALM_MIND", "MOVE_SHADOW_BALL")),
]


# Une équipe pour le Mont Combat (aucun Pokémon interdit ; les adversaires au niveau du plus fort de l'équipe), en
# combats doubles contre deux dresseurs : la première attaque (celle du pilote) touche les deux adversaires
HILL_TEAM = [
    ("SPECIES_KYOGRE", ("MOVE_SURF", "MOVE_ICE_BEAM", "MOVE_THUNDER", "MOVE_CALM_MIND")),
    ("SPECIES_MEWTWO", ("MOVE_PSYCHIC", "MOVE_ICE_BEAM", "MOVE_THUNDERBOLT", "MOVE_FLAMETHROWER")),
    ("SPECIES_LATIOS", ("MOVE_PSYCHIC", "MOVE_DRAGON_CLAW", "MOVE_THUNDERBOLT", "MOVE_ICE_BEAM")),
    ("SPECIES_LATIAS", ("MOVE_PSYCHIC", "MOVE_DRAGON_CLAW", "MOVE_THUNDERBOLT", "MOVE_ICE_BEAM")),
]


def give_team(game, level=50, team=TEAM):
    """L'équipe team, chacun avec ses 4 attaques (joueur.capacite)."""
    for species, moves in team:
        game.give_mon(species, level)
        game.wait(1)
        slot = len(game.state.party) - 1
        for place, move in enumerate(moves):
            reply = game.dev("joueur.capacite", slot, place, names.number(move))
            if "refuse" in reply:
                raise GameError(f"joueur.capacite : {reply.strip()}")


def choose_party(game, count):
    """Le menu d'équipe d'un défi (PARTY_MENU_TYPE_CHOOSE_HALF) : A, A (ENTRER) sur chacun des count premiers ; le jeu
    met le curseur sur CONFIRMER au dernier ; A."""
    for i in range(count):
        game.tap("A", gap=30)
        game.tap("A", gap=40)
        if i < count - 1:
            game.tap("DOWN", gap=20)
    game.tap("A", gap=40)


def choose_rentals(game, count=3):
    """L'écran de location de l'Usine (et de la Tente de Poivressel) : A, BAS, A (son menu : RÉSUMÉ, LOUER, AUTRES)
    puis la Poké Ball à droite, count fois ; A (OUI)."""
    for i in range(count):
        game.tap("A", gap=30)
        game.tap("DOWN", gap=20)
        game.tap("A", gap=40)
        if i < count - 1:
            game.tap("RIGHT", gap=20)
    game.tap("A", gap=60)


# Les questions d'un défi qui ne se répondent pas par A : (mots du dernier texte, touches)
ANSWERS = [
    # Dôme (« Votre combat du premier tour va avoir lieu. Pouvons-nous commencer? ») : ADVERSAIRE, TABLEAU,
    # COMBATTRE… ; le Palais et les autres posent la même question avec COMBATTRE en premier
    ("tour va avoir lieu", ("DOWN", "DOWN", "A")),
]


def attendant(map_name, words="Attendant"):
    """Le préposé de la carte : la première cible PNJ dont le script contient words."""
    for target in crawl.targets(map_name):
        if target["genre"] == "pnj" and words in target["script"]:
            return target
    raise GameError(f"pas de préposé « {words} » sur {map_name}")


def run(game, map_name, words="Attendant", party=3, battles=2, level=50, frames=120000, rentals=False, trigger=None,
        flags=(), walking=False, reach=None, team=TEAM, watch=None):
    """Un scénario de défi : la sauvegarde de Hoenn, l'équipe au niveau voulu, le style de combat DÉFINI, puis le
    défi jusqu'à `battles` combats gagnés. Avec des Pokémon loués (rentals : Usine, Tente de Poivressel), tirés au
    hasard, un combat peut être perdu : il suffit qu'il soit joué jusqu'au bout ; de même pour les défis où l'on
    marche (Antre, Pyramide, Mont Combat : rencontres sauvages, issue remise à zéro par le défi). Avec reach (une
    carte, ou une suite de cartes), il faut en plus y arriver, dans l'ordre, après les combats (Mont Combat : l'étage
    suivant ne s'ouvre qu'aux vainqueurs ; concours : la salle puis le retour au hall, battles=0)."""
    from driver import continue_game, expect

    continue_game(game)
    give_team(game, level, team)
    game.dev("jeu.options", 3, 1)
    game.max_frames = max(game.max_frames, game.frames + frames + 20000)    # la partie : de quoi finir le défi
    for flag in flags:                  # ce que le défi demande (Mont Combat : la Ligue finie)
        game.flag(flag, 1)
    route = [reach] if isinstance(reach, str) else list(reach or ())
    played = play_challenge(game, map_name, words, party, battles and (1 if rentals or walking else battles), frames,
                            trigger, route, watch)
    if reach:
        expect(game, not route, f"{map_name} : {' puis '.join([reach] if isinstance(reach, str) else reach)} "
                                f"atteint après les combats (reste {route} ; {played})")
    if not battles:
        pass
    elif rentals or walking:
        expect(game, any(b["outcome"] for b in played), f"{map_name} : un combat joué jusqu'au bout ({played})")
    else:
        won = [b for b in played if b["outcome"] == "WON"]
        expect(game, len(won) >= battles, f"{map_name} : {battles} combats gagnés ({played})")


# La marche dans une salle de défi : (direction, cases), en boucle
WALK = [("UP", 4), ("LEFT", 3), ("UP", 4), ("RIGHT", 6), ("DOWN", 2), ("LEFT", 3), ("UP", 5), ("RIGHT", 2)]


def wander(game, step, entry=None, talked=None):
    """Le joueur est libre dans une salle de défi, sur la carte telle qu'elle est en jeu (étages générés du Mont
    Combat et de la Pyramide) : il va parler à quelqu'un qu'il n'a pas encore abordé (talked : dresseurs, objets au
    sol, PNJ d'une salle de l'Antre), sinon il prend une porte plus haut (Antre : trois portes ; jamais celle par
    laquelle il est entré, entry, sinon il fait l'aller-retour entre deux étages), sinon un bout de la marche WALK."""
    from driver import live_map, talk_to_object, walk_to

    if game.frames + 4000 < game.max_frames:
        here = game.state.map_name
        px, py = game.state.pos
        talked = set() if talked is None else talked
        # 3 000 images au plus pour y arriver : un dresseur peut être hors d'atteinte
        outer = game.max_frames
        game.max_frames = game.frames + 3000
        try:
            # Pas dans une entrée (Mont Combat) : le préposé y propose d'abandonner
            people = sorted(zip(game.state.objects, game.state.object_ids),
                            key=lambda o: abs(o[0][0] - px) + abs(o[0][1] - py))
            if not crawl.CHALLENGE_ROOMS.search(here or ""):
                people = []
            for (x, y), local_id in people:
                if (here, local_id, (x, y)) in talked:
                    continue
                talked.add((here, local_id, (x, y)))
                try:
                    talk_to_object(game, x, y, finish=False, live=True)
                    return
                except GameError:
                    continue
            grid = live_map(game)
            doors = [(x, y) for (x, y) in grid.warps if y < py
                     and not (entry and abs(x - entry[0]) + abs(y - entry[1]) <= 1)]
            for x, y in sorted(doors, key=lambda d: abs(d[0] - px) + abs(d[1] - py)):
                if grid.path((px, py), (x, y), set(game.state.objects)) is None:
                    continue
                walk_to(game, x, y, live=True)
                # Sur la porte : la direction qui la passe, maintenue (un escalier latéral de RF : une quarantaine
                # d'images) ; s'il s'en éloigne, il y revient pour la suivante
                def started():
                    s = game.state
                    return s.map_name != here or s.locked or s.script or s.battle or s.fade

                for direction in ("UP", "LEFT", "RIGHT"):
                    for _ in range(6):
                        if started() or game.state.pos != (x, y):
                            break
                        game.press(direction, 8)
                    if started():
                        break
                    if game.state.pos != (x, y):
                        walk_to(game, x, y, live=True)
                return
        except GameError:
            pass                # le plafond, ou personne ni porte à portée : la marche WALK (un plantage y ressort)
        finally:
            game.max_frames = outer
    direction, tiles = WALK[step % len(WALK)]
    for _ in range(tiles):
        if not game.state.free:
            return
        game.press(direction, 16)


def play_challenge(game, map_name, words="Attendant", party=3, battles=2, frames=60000, trigger=None, route=None,
                   watch=None):
    """Parle au préposé et joue le défi jusqu'à `battles` combats finis, et l'arrivée sur chacune des cartes de route
    dans l'ordre (la liste se vide au fur et à mesure), ou `frames` images. Renvoie les combats. watch : passé à
    fight_battle."""
    route = [] if route is None else route
    start = len(game.battles)
    if trigger:
        # Le défi part d'une case de déclenchement (Mont Combat) : on y monte depuis la case du dessous
        game.warp(map_name, trigger[0], trigger[1] + 1)
        game.press("UP", 16)
        game.wait(30)
        if game.state.free:
            raise GameError(f"la case {trigger} de {map_name} ne déclenche rien : {game.describe()}")
    target = None if trigger else attendant(map_name, words)
    for attempt in range(0 if trigger else 6):
        # Là où il est maintenant (un préposé peut bouger sur place), d'une case possible (comptoir : à 2 cases)
        x, y = target["x"], target["y"]
        for pos, local_id in zip(game.state.objects, game.state.object_ids):
            if local_id == target["id"] and game.state.map_name == map_name:
                x, y = pos
        places = crawl.spots(map_name, x, y)
        sx, sy, direction = places[attempt % len(places)]
        game.warp(map_name, sx, sy)
        talk_to(game, direction, finish=False)
        if not game.state.free:
            break
    else:
        if not trigger:
            raise GameError(f"le préposé de {map_name} ne répond pas : {game.describe()}")
    step = 0
    last_map = entry = None     # la salle où il erre, et sa case d'arrivée
    talked = set()              # ceux à qui il a parlé (wander)
    chose_party = chose_rentals = False
    asked = mark(game)          # les textes depuis la dernière réponse d'ANSWERS
    limit = game.frames + frames
    while game.frames < limit:
        played = [b for b in game.battles[start:] if b["outcome"]]
        if route and game.state.map_name == route[0]:
            route.pop(0)
        if len(played) >= battles and not route:
            break
        screen = game.function(game.state.cb2)
        if game.state.battle:
            fight_battle(game, limit=6000, watch=watch)     # Pokémon loués peu efficaces : un combat peut être long
        elif "PartyMenu" in screen and not chose_party:
            # Le nombre demandé (« choisir les deux POKéMON » : chaque match du Dôme), sinon celui du défi
            dialogue = " ".join(text for _, window, text in game.texts[-30:] if window == 0).lower()
            count = next((n for word, n in (("deux pok", 2), ("trois pok", 3), ("quatre pok", 4)) if word in dialogue),
                         party)
            game.wait(60)
            choose_party(game, count)
            chose_party = True
        elif "PartyMenu" not in screen and chose_party and not game.state.battle:
            chose_party = False         # un autre choix pourra venir (le match suivant du Dôme)
            game.tap("A", hold=2, gap=20)
        elif "SelectScreen" in screen and not chose_rentals:
            game.wait(90)
            choose_rentals(game)
            chose_rentals = True
        elif "Swap" in screen:
            game.tap("B", gap=40)       # Usine : pas d'échange de Pokémon après le combat
        elif "TourneyTree" in screen:
            game.tap("B", gap=60)       # Dôme : le tableau après un tour (A y ouvre la fiche d'un dresseur)
        elif game.state.free and game.state.map_name == map_name and not trigger and not game.battles[start:]:
            raise GameError(f"le défi n'a pas commencé : {game.describe()}")
        elif game.state.free:
            if game.state.map_name != last_map:
                last_map, entry = game.state.map_name, game.state.pos
            wander(game, step, entry, talked)   # Antre, Pyramide, Mont Combat (dont l'entrée) : on avance
            step += 1
        else:
            dialogue = [text for _, window, text in game.texts[asked:] if window == 0]
            last = " ".join(dialogue[-1].split()) if dialogue else ""
            answer = next((keys for words, keys in ANSWERS if words in last), None)
            if answer:
                # Le menu affiché (un texte hors de la boîte de dialogue, écrit après la question) avant d'y bouger
                question = max(i for i, (_, window, _) in enumerate(game.texts) if window == 0)
                for _ in range(60):
                    if any(window != 0 for _, window, _ in game.texts[question + 1:]):
                        break
                    game.wait(4)
                game.wait(40)
                for key in answer:
                    game.tap(key, hold=4, gap=30)
                asked = mark(game)
            else:
                game.tap("A", hold=2, gap=20)
    return game.battles[start:]
