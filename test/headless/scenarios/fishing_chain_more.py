# Pêche à Kanto, cas restants (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto » :
# - les trois gourous (Carmin : CANNE, Parmanie : SUPER CANNE, Route 12 : MEGA CANNE) : sans la canne, ils disent où
#   la trouver à Hoenn ; avec, ils l'améliorent ;
# - la série (outil jeu.peche), à graines fixes, avec la MEGA CANNE améliorée : chaque POKéMON remonté au même
#   endroit l'allonge (un tirage chromatique de plus à la prise suivante) ; « Rien de rien… » la brise, comme un pas,
#   ou une autre canne.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import wait_action_menu, texts

GURUS = [   # carte, PNJ, canne, drapeau, mot du texte « où la trouver »
    ("VermilionCity_House1", (4, 5), "ITEM_OLD_ROD", "FLAG_OLD_ROD_UPGRADED", "MYOKARA"),
    ("FuchsiaCity_House2", (6, 5), "ITEM_GOOD_ROD", "FLAG_GOOD_ROD_UPGRADED", "ROUTE 118"),
    ("Route12_FishingHouse", (4, 4), "ITEM_SUPER_ROD", "FLAG_SUPER_ROD_UPGRADED", "ALGATIA"),
]


def talk_below(game, place, npc):
    game.warp(place, npc[0], npc[1] + 1); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(40)
    finish_dialog(game)
    return " ".join(t for _, t in texts(game, since))


def chain(game):
    m = re.search(r"serie (\d+) canne (\d+) tirages (\d+)", game.dev("jeu.peche"))
    return int(m.group(1))


def fish(game, seed):
    """SELECT (canne enregistrée) ; un A par « Ça mord ! » (la MEGA CANNE peut relancer des manches : un A pendant
    les points fait partir le POKéMON) ; combat : FUITE. Rend 'pris', 'parti' ou 'rien'."""
    wait_until(game, lambda s: s.free)
    game.dev("jeu.hasard", seed)
    since = mark(game)
    battles = len(game.battles)
    game.tap("SELECT")
    handled = 0
    hooked = False
    result = None
    for _ in range(1500):
        bites = sum(1 for _, _, t in game.texts[since:] if "Ça mord" in t)
        if bites > handled:
            handled = bites
            game.wait(2)
            game.tap("A", hold=2, gap=2)
            continue
        if saw_text(game, "mordu à l", since) and not game.state.battle:
            # « Un POKéMON a mordu à l'hameçon ! » attend A une fois écrit : A jusqu'au combat
            hooked = True
            game.wait(40)
            if not game.state.battle:
                game.tap("A")
            continue
        if game.state.battle:
            result = "pris"
            break
        if saw_text(game, "Rien de rien", since) or saw_text(game, "reparti", since):
            result = "rien" if saw_text(game, "Rien de rien", since) else "parti"
            break
        game.wait(2)
    if result == "pris":
        wait_action_menu(game)
        game.tap("DOWN"); game.wait(10); game.tap("RIGHT"); game.wait(10); game.tap("A")
        for _ in range(40):
            if not game.state.battle:
                break
            game.tap("A"); game.wait(30)
    finish_dialog(game)
    return result


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.flag("FLAG_SYS_POKEMON_GET", 1)

    # Gourous sans canne, puis avec
    without = [(flag, talk_below(game, place, npc), word) for place, npc, rod, flag, word in GURUS]
    flags_without = [str(game.flag(flag)).strip() for _, _, _, flag, _ in GURUS]
    for _, _, rod, _, _ in GURUS:
        game.item(rod, 1)
    with_rod = [talk_below(game, place, npc) for place, npc, rod, flag, word in GURUS]
    flags_with = [str(game.flag(flag)).strip() for _, _, _, flag, _ in GURUS]

    # La série, MEGA CANNE améliorée, Carmin sur Mer (eau à gauche)
    game.dev("joueur.enregistre", names.number("ITEM_SUPER_ROD"))
    game.warp("VermilionCity", 8, 9); game.wait(40)
    game.press("LEFT", 1); game.wait(20)
    history = []
    seed = 1

    def broke_a_chain():
        """Un échec juste après une série d'au moins 2 prises."""
        return any(history[i][1] >= 2 and history[i + 1][0] != "pris" for i in range(len(history) - 1))

    while seed < 80 and not broke_a_chain():
        result = fish(game, seed)
        history.append((result, chain(game)))
        seed += 1
    game.note("pêches : " + " ; ".join(f"{r} {c}" for r, c in history))
    # un pas : la série repart de zéro à la pêche suivante
    while chain(game) == 0 and seed < 90:
        fish(game, seed); seed += 1
    before_step = chain(game)
    game.press("RIGHT", 16); game.wait(20); game.press("LEFT", 16); game.wait(20)
    while True:
        result = fish(game, seed); seed += 1
        if result == "pris" or seed > 120:
            break
    after_step = chain(game)
    log(game, "serie")

    # Vérifications
    for (flag, said, word), state in zip(without, flags_without):
        expect(game, word in said and state in ("0", "False"), f"sans canne : où la trouver ({word}) ; {flag} = {state}")
    expect(game, all("est améliorée" in said for said in with_rod) and all(s in ("1", "True") for s in flags_with),
           f"avec la canne : améliorée ({flags_with})")
    counts = [c for r, c in history if r == "pris"]
    expect(game, any(c >= 2 for c in counts), f"série : prises d'affilée au même endroit ({history})")
    expect(game, broke_a_chain() and all(c == 0 for r, c in history if r in ("rien", "parti")),
           f"« Rien de rien… » ou « Il est reparti… » brise une série en cours ({history})")
    expect(game, before_step >= 1 and after_step == 1, f"un pas : la série repart ({before_step} -> {after_step})")
