# Build KANTO_DEBUG=1 : téléport PORT ÎLE 1 (devant le marin), destination ÎLE 2 : traversée du Seagallop
# (mer qui défile, ferry et sillage) puis arrivée au port de l'Île 2.
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
    debug_warp(game, 28); log(game, "port Île 1")
    game.tap("UP"); game.wait(30); game.tap("A"); game.wait(200); log(game, "marin")
    for _ in range(3):
        game.tap("A"); game.wait(120)
    log(game, "menu")
    game.tap("A"); game.wait(120)
    for _ in range(4):
        game.tap("A"); game.wait(120)
    log(game, "traversée")
    game.wait(600)
    for _ in range(10):
        if game.state.free:
            break
        game.tap("A"); game.wait(120)
    wait_until(game, lambda s: s.free); log(game, "arrivée")
