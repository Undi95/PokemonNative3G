# Build KANTO_DEBUG=1 : téléport dans l'arène de Safrania, premier téléporteur (MB_REGULAR_WARP de RF).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import wait_until, walk_to
from kanto_tour import debug_warp, give_mewtwo, log


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    debug_warp(game, 23); log(game, "arène")
    walk_to(game, 18, 21); log(game, "devant le téléporteur")
    game.press("UP", 16)
    game.wait(20); log(game, "départ")
    wait_until(game, lambda s: s.free); game.wait(30); log(game, "arrivée")
