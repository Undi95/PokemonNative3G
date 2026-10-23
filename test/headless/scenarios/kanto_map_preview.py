# Build KANTO_DEBUG=1 : DEBUG ROUTE 4, entrée du MONT SÉLÉNITE : aperçu du lieu de RF (image + nom), puis la grotte
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from driver import wait_until, walk_to


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    debug_warp(game, 3); log(game, "route 4")
    walk_to(game, 19, 6); log(game, "devant")
    game.press("UP", 30); game.wait(60); log(game, "aperçu")
    game.wait(200); log(game, "aperçu 2")
    wait_until(game, lambda s: s.free); log(game, "grotte")
