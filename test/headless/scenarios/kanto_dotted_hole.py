# Build KANTO_DEBUG=1 : DEBUG « MEWTWO + KADABRA », « POKé MONTURE + badges » et « Deux Ligues finies » (scientifique parti), téléport VALLÉE RUINE (37) :
# porte du Trou Pointé, braille, puis COUPE depuis le menu de l'équipe (KADABRA, COUPE en debug) -> porte ouverte, on entre.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, finish_dialog


def play(game, before_warp=None, at_start=None):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    if at_start:
        at_start(game)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 14, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 13, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    if before_warp:
        before_warp(game)
    debug_warp(game, 37); log(game, "vallée")
    game.press("UP", 16); game.wait(30); game.press("UP", 2); game.wait(20); log(game, "devant la porte")
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(60)          # examiner : OUI
    game.tap("A"); game.wait(90); game.tap("A"); game.wait(90)          # points, braille
    game.wait(60); log(game, "braille")
    game.tap("A"); game.wait(60); finish_dialog(game); game.wait(30)
    # COUPE depuis l'équipe : KADABRA (2e), 2e ligne du sous-menu = COUPE
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(40); game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(200)
    log(game, "coupe utilisée")
    game.press("UP", 16); game.wait(200); log(game, "entré")
