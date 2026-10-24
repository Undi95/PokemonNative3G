# Build KANTO_DEBUG=1 : DEBUG objets (POKé FLÛTE), « Deux Ligues finies », téléport CHUTES MÉTÉORE : météorite,
# POKé FLÛTE, JIRACHI se réveille, combat légendaire (Mewtwo du debug), vaincu : la météorite ne brille plus.
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
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A")
    game.wait(60); game.tap("DOWN", 8, gap=10); game.tap("A"); game.wait(60); close_menus(game)
    debug_warp(game, 34)
    log(game, "chutes")
    walk_to(game, 7, 4)
    game.press("UP", 1); game.wait(20); game.tap("A"); game.wait(60); log(game, "météorite")
    for k in range(4):
        game.tap("A"); game.wait(50)
    log(game, "flûte ?")
    game.tap("A"); game.wait(60); log(game, "oui")
    for k in range(16):
        game.wait(60); log(game, "réveil %d" % k)
        if game.state.battle:
            break
        game.tap("A")
    finish_dialog(game); log(game, "après combat")
    talk_to(game, "UP"); log(game, "météorite éteinte")
