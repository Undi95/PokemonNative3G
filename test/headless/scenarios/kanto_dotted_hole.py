# Build KANTO_DEBUG=1 : DEBUG « MEWTWO + KADABRA » et « POKé MONTURE + badges », téléport VALLÉE RUINE (37) :
# porte du Trou Pointé, braille, COUPE proposée (POKé MONTURE) -> porte ouverte, on entre.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, finish_dialog


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 14, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    debug_warp(game, 37); log(game, "vallée")
    game.press("UP", 8); game.wait(30); log(game, "devant la porte")
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(60)          # examiner : OUI
    game.tap("A"); game.wait(90); game.tap("A"); game.wait(90)          # points, braille
    game.tap("A"); game.wait(60); log(game, "coupe ?")
    game.tap("A"); game.wait(60)                                         # OUI
    finish_dialog(game); game.wait(90); log(game, "porte ouverte")
    game.press("UP", 16); game.wait(200); log(game, "entré")
