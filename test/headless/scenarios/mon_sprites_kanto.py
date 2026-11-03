# Options > POKéMON = KANTO (2026-11-03, docs/A-TESTER.md) : sprites de Rouge Feu, sans animation, là où la grille
# (matrix.py : combats, résumé, PC) ne va pas : évolution (PIERRE FOUDRE sur PIKACHU), éclosion, et un POKéMON
# chromatique (LEVEINARD de GiveShinyChansey) dans le résumé. Écrans à regarder.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from menu_helpers import bag, open_start_entry, pick
from kanto_item_use_scenes import bag_item_menu
from egg_hatch_kanto import hatch

OPTION_MON_SPRITES, OPTION_BAG_STYLE = 14, 13


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("jeu.options", OPTION_MON_SPRITES, 1)
    game.dev("jeu.options", OPTION_BAG_STYLE, 1)       # le sac de RF (bag_item_menu)

    # Éclosion
    game.give_mon("SPECIES_PIKACHU", 5)
    hatch(game, "eclosion")

    # Évolution : PIERRE FOUDRE sur PIKACHU
    game.item("ITEM_THUNDER_STONE", 1)
    open_start_entry(game, "SAC"); game.wait(240)
    stone = next(n for _, n, _ in bag(game)["poche 1"] if n.startswith("PIERRE"))
    since = bag_item_menu(game, stone)
    pick(game, since, "UTILIS."); game.wait(200)
    game.tap("A"); game.wait(300)                        # PIKACHU, puis la scène de l'objet
    for step in range(60):
        if any(name.startswith("CB2_EvolutionScene") or name == "CB2_BeginEvolutionScene" for _, name in game.cb2s):
            break
        game.tap("A"); game.wait(40)
    game.wait(200); log(game, "evolution debut")
    for _ in range(40):
        if game.state.party and game.state.party[0][0] == names.number("SPECIES_RAICHU"):
            break
        game.tap("A"); game.wait(40)
    game.wait(60); log(game, "evolution fin")
    for _ in range(12):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    expect(game, game.state.party[0][0] == names.number("SPECIES_RAICHU"), "PIKACHU évolue en RAICHU")

    # Chromatique : LEVEINARD, son résumé
    game.special("GiveShinyChansey")
    open_start_entry(game, "POKéMON"); game.wait(90)
    game.tap("DOWN"); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "RESUME"); game.wait(200)
    log(game, "chromatique")
    for _ in range(10):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
