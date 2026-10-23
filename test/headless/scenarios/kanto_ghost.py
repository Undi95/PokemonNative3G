# Build KANTO_DEBUG=1 : MEWTWO, sans Scope Sylph, téléport TOUR POKéMON 3 : rencontre d'un SPECTRE
# (« Le SPECTRE apparaît ! Mince ! Le SPECTRE ne peut être identifié ! »), MEWTWO a peur de bouger,
# « SPECTRE : Va t'en… Dehors… », puis FUITE (toujours réussie).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp, give_mewtwo
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    give_mewtwo(game)
    debug_warp(game, 25); log(game, "Tour 3")
    for _ in range(200):
        if game.state.battle:
            break
        game.tap("UP", hold=16, gap=2); game.tap("DOWN", hold=16, gap=2)
    game.wait(400); log(game, "rencontre")
    game.tap("A", 4, gap=60); game.wait(60); log(game, "menu")
    game.tap("A"); game.wait(40); game.tap("A"); game.wait(600); log(game, "attaque")
    game.tap("A", 3, gap=60); game.wait(200)
    game.tap("DOWN"); game.wait(20); game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(200); log(game, "fuite")
    for _ in range(10):
        if game.state.free:
            break
        game.tap("A"); game.wait(60)
    wait_until(game, lambda s: s.free); log(game, "fini")
