# Build KANTO_DEBUG=1 : MEWTWO, option MENUS = KANTO, objets du debug (champignons), Île 2, Maître des capacités :
# écran du Maître des capacités de RF (learn_move.c).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp, give_mewtwo
from redleaf_acro import close_menus
from driver import wait_until, walk_to


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    # Options > MENUS = KANTO
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 5, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    # DEBUG > objets (POKéMON dans le menu : OPTIONS est la 6e ligne)
    game.tap("START"); game.wait(30); game.tap("UP", 5, gap=10); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    debug_warp(game, 14); log(game, "île 2")
    walk_to(game, 33, 10); game.press("UP", 20); wait_until(game, lambda s: s.free); log(game, "maison")
    walk_to(game, 7, 6); game.press("UP", 4); game.wait(20)
    for k in range(26):
        game.tap("A"); game.wait(90); log(game, "A %d" % k)
    game.wait(120); log(game, "écran rf")
    game.tap("DOWN"); game.wait(40); log(game, "bas")

    # Vérifications
    expect_text(game, "Je suis le DINGUE DES CAPACITES")
    expect_text(game, "Quelle attaque dois-je enseigner")
