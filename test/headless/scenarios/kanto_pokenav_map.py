# Build KANTO_DEBUG=1 : DEBUG « Deux Ligues finies » (POKéNAV), passage à Kanto, POKéMON de Kanto ; POKéNAV, onglet
# CARTE : carte de Kanto de RF (pas de plantage), B : retour au POKéNAV.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, talk_to


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 13, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    debug_warp(game, 35)
    talk_to(game, "UP")
    game.wait(60); log(game, "arrivée")
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(40); game.tap("DOWN", 3, gap=15); game.tap("A"); game.wait(200); log(game, "POKéNAV")
    game.tap("A"); game.wait(300); log(game, "CARTE")
    game.tap("B"); game.wait(300); log(game, "retour")
