# Build KANTO_DEBUG=1 : MEWTWO, Jadielle, Centre Pokémon : la carte murale (à droite du PC) montre Kanto (RF).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import leave_map, walk_to, wait_until
from kanto_tour import debug_warp, give_mewtwo, log


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    debug_warp(game, 1)
    walk_to(game, 26, 27); leave_map(game, "UP"); log(game, "Centre Pokémon")
    walk_to(game, 12, 2); game.tap("UP"); game.wait(20); game.tap("A"); game.wait(120)
    game.tap("A"); game.wait(300); log(game, "carte murale")
    game.tap("B"); game.wait(200)
    wait_until(game, lambda s: s.free); log(game, "retour")
