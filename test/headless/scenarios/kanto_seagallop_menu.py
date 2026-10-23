# Build KANTO_DEBUG=1 : DEBUG > Pass îles Sevii, téléport PORT ÎLE 1 : menu des destinations de RF
# (CARMIN SUR MER, ÎLE 2, 3, 4, AUTRES, RETOUR), AUTRES (ÎLE 5, 6, 7, AUTRES, RETOUR), ÎLE 7, traversée.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 9, gap=10); game.tap("A"); game.wait(60)
    game.tap("B"); game.wait(30); game.tap("B"); wait_until(game, lambda s: s.free)
    debug_warp(game, 28); log(game, "port Île 1")
    game.tap("DOWN"); game.wait(30); game.tap("A"); game.wait(400); log(game, "page 1")
    game.tap("DOWN", 4, gap=20); game.wait(30); game.tap("A"); game.wait(200); log(game, "page 2")
    game.tap("DOWN", 2, gap=20); game.wait(30); game.tap("A"); game.wait(200)
    for _ in range(4):
        game.tap("A"); game.wait(120)
    game.wait(600)
    wait_until(game, lambda s: s.free); log(game, "arrivée")
