# Build KANTO_DEBUG=1 : option MENUS = KANTO, boutique d'Argenta : menu ACHETER/VENDRE/SORTIR et écran d'achat de RF
# (shop.c de RF), achat d'une POKé BALL, sortie.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, walk_to


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    # Options > MENUS = KANTO
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 4, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    game.tap("START"); game.wait(30); game.tap("UP", 4, gap=10); game.tap("B"); game.wait(30)  # menu Start : curseur sur DEBUG
    debug_warp(game, 2)
    walk_to(game, 28, 19); game.press("UP", 20); wait_until(game, lambda s: s.free); log(game, "boutique")
    walk_to(game, 4, 3); game.press("LEFT", 4); game.wait(20)
    game.tap("A"); game.wait(150); log(game, "menu")
    game.tap("A"); game.wait(200); log(game, "achat")
    game.tap("A"); game.wait(60); log(game, "combien")
    game.tap("A"); game.wait(60); log(game, "confirmer")
    game.tap("A"); game.wait(120); log(game, "acheté")
    game.tap("A"); game.wait(60); game.tap("B"); game.wait(200); log(game, "retour menu")
    game.tap("B"); game.wait(120); log(game, "fin")

    # Vérifications
    expect_text(game, "POKé BALL? Vous en voulez 1? Ça fera 200¥")
