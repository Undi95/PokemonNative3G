# Build KANTO_DEBUG=1 : DEBUG « Deux Ligues finies », téléport FORÊT BAIES, autel : CELEBI apparaît, combat
# légendaire (Mewtwo du debug), CELEBI vaincu s'enfuit ; l'autel redevient silencieux.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, walk_to, talk_to, finish_dialog


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 13, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    debug_warp(game, 33)
    log(game, "forêt")
    walk_to(game, 45, 6)
    game.press("UP", 1); game.wait(20); game.tap("A"); game.wait(60); log(game, "autel")
    for k in range(5):
        game.tap("A"); game.wait(60)
    log(game, "présence")
    for k in range(12):
        game.wait(40); log(game, "apparition %d" % k)
        if game.state.battle:
            break
    finish_dialog(game); log(game, "après combat")
    talk_to(game, "UP"); log(game, "autel silencieux")
