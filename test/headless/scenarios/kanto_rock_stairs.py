# Build KANTO_DEBUG=1 : Plateau Indigo, descente des escaliers de roche (MB_ROCK_STAIRS de RF) en
# marchant puis en courant. Hors escalier : 16 frames par case (marche), 8 (course) ;
# sur l'escalier : 24 (marche lente de RF) et ~11 (course lente).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import wait_until, walk_to
from kanto_tour import debug_warp, give_mewtwo, log


def trace(game, buttons, frames):
    last = None
    for f in range(frames):
        game.press(buttons, 1)
        pos = game.state.pos
        if pos != last:
            print(f"  frame {game.state.frame}: {pos}", flush=True)
            last = pos


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    debug_warp(game, 12); log(game, "Plateau Indigo")
    walk_to(game, 11, 11); log(game, "en haut")
    trace(game, "DOWN", 200); log(game, "en bas (marche)")
    walk_to(game, 11, 11); log(game, "en haut")
    trace(game, "DOWN+B", 120); log(game, "en bas (course)")
