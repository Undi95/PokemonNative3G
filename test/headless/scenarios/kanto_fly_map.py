# Build KANTO_DEBUG=1 : menu DEBUG > Carte VOL (2 régions) à Bourg Palette : carte de Kanto (RF),
# SELECT -> carte de Hoenn (Émeraude), SELECT -> Kanto ; puis la même chose depuis Bourg-en-Vol.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from driver import wait_until


def fly_map(game, where):
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30)
    game.tap("DOWN", 7); game.tap("A"); game.wait(240)
    log(game, where + " : carte")
    game.tap("SELECT"); game.wait(180); log(game, where + " : SELECT")
    game.tap("SELECT"); game.wait(180); log(game, where + " : SELECT x2")
    game.tap("B"); game.wait(150); game.tap("B"); game.wait(150); game.tap("B"); game.wait(150)
    log(game, where + " : retour")


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    fly_map(game, "Kanto")
    debug_warp(game, 20); log(game, "Bourg-en-Vol")
    fly_map(game, "Hoenn")
