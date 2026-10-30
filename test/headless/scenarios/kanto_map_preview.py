# Build KANTO_DEBUG=1 : DEBUG ROUTE 4, entrée du MONT SÉLÉNITE : aperçu du lieu de RF (image + nom), puis la grotte
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
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
    game.press("UP", 30)
    # L'aperçu s'affiche pendant CB2_ChangeMapMain, après le fondu
    wait_until(game, lambda s: game.function(s.cb2) == "CB2_ChangeMapMain", step=1, limit=300)
    game.wait(90); log(game, "aperçu")
    wait_until(game, lambda s: s.free); log(game, "grotte")

    # Vérifications
    expect_map(game, "MtMoon_1F")
