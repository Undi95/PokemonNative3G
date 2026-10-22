# Build KANTO_DEBUG=1 : Options > INTRO = KANTO, sauvegarde, reset (A+B+START+SELECT) :
# après le copyright d'Émeraude, l'intro de Rouge Feu (Game Freak, Nidorino contre Ectoplasma).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import wait_until
from kanto_tour import log
from redleaf_acro import close_menus


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("DOWN", 8, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    # SAUVER (le menu Start se rouvre sur OPTIONS, un cran en dessous de SAUVER)
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(90)
    game.tap("A"); game.wait(400); game.tap("A", 3, gap=120)
    close_menus(game); log(game, "sauvé")
    game.press("A+B+START+SELECT", 1)
    game.wait(3000); log(game, "intro")
