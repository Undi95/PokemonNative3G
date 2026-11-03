# Maître des capacités avec MENUS = KANTO (écran de RF, kanto_learn_move.c), cas restants (2026-11-03,
# docs/A-TESTER.md), sauvegarde « kanto », PIKACHU N.20 à 4 capacités :
# - Île 2 (DINGUE DES CAPACITES) : la 1re capacité de la liste, oubli d'une capacité (écran du résumé), apprise ;
#   le GROS CHAMPI est donné ;
# - Vergazon (Hoenn) : le même écran de RF, oubli, apprise ; l'ÉCAILLE CŒUR est donnée.
# L'écran de RF s'ouvre par CB2_MoveRelearner_Init, celui d'Émeraude par CB2_InitLearnMove.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import press_until_free, bag, texts


def moves(game):
    line = next(l for l in game.dev("joueur.equipe").splitlines() if "capacites" in l)
    return [int(m.split("/")[0]) for m in line.split()[1:]]


def relearn(game, place, x, y, what):
    game.warp(place, x, y); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("UP", 4); game.wait(20)
    before = moves(game)
    since = mark(game)
    screens = len(game.cb2s)
    learn_screen = summary = False
    game.tap("A"); game.wait(60)
    for _ in range(80):
        current = game.function(game.state.cb2)
        if not learn_screen and current == "CB2_MoveRelearner":
            game.wait(120)
            log(game, f"{what} liste")
            learn_screen = True
        elif learn_screen and not summary and "Summary" in current:
            game.wait(200)
            game.tap("DOWN", 2, gap=30); game.wait(30)
            log(game, f"{what} oublier")
            summary = True
        elif learn_screen and game.state.free:
            break
        game.tap("A"); game.wait(40)
    press_until_free(game, "A")
    opened = [name for _, name in game.cb2s[screens:]]
    return before, moves(game), opened, saw_text(game, "Tadaa", since), texts(game, since)


def play(game):
    continue_game(game)
    game.dev("jeu.options", 11, 1)                     # MENUS = KANTO
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.item("ITEM_BIG_MUSHROOM", 1)
    game.item("ITEM_HEART_SCALE", 1)

    two_island = relearn(game, "TwoIsland_House", 7, 6, "ile 2")
    fallarbor = relearn(game, "FallarborTown_MoveRelearnersHouse", 4, 5, "vergazon")
    items = bag(game)

    # Vérifications
    for what, (before, after, opened, tadaa, shown) in (("Île 2", two_island), ("Vergazon", fallarbor)):
        expect(game, "CB2_MoveRelearner_Init" in opened and "CB2_InitLearnMove" not in opened,
               f"{what} : écran de RF ({opened})")
        expect(game, any("Summary" in n for n in opened) and tadaa, f"{what} : oubli d'une capacité, « Tadaa »")
        expect(game, before != after and before[2] != after[2] and before[:2] == after[:2],
               f"{what} : 3e capacité remplacée ({before} -> {after})")
    expect_item(game, "ITEM_BIG_MUSHROOM", 0)
    expect_item(game, "ITEM_HEART_SCALE", 0)
