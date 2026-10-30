# Build KANTO_DEBUG=1 : téléport GROTTE GLACÉE 1F (38), marche sur la glace fragile : elle se fissure, puis casse.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    debug_warp(game, 38); log(game, "grotte")
    for d in ("DOWN", "DOWN", "LEFT", "RIGHT"):        # (9,9) : glace fragile -> fissurée
        game.press(d, 16); game.wait(40); log(game, d)
    game.press("LEFT", 16); game.wait(200); log(game, "trou")   # glace fissurée -> trou, chute au sous-sol

    # Vérifications
    expect_map(game, "FourIsland_IcefallCave_B1F")
