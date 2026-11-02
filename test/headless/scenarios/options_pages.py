# Menu Options en deux pages : page 1 = réglages d'Émeraude, R = page 2 (choix HOENN/KANTO, défile jusqu'à
# RETOUR), L = retour à la page 1. Le titre affiche la page et les touches L/R.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(150)
    log(game, "page 1"); game.wait(30)
    game.tap("R"); game.wait(60); log(game, "page 2"); game.wait(30)
    game.tap("DOWN", 9, gap=12); game.wait(60); log(game, "page 2 bas"); game.wait(30)
    game.tap("L"); game.wait(60); log(game, "page 1 de nouveau"); game.wait(30)
    game.tap("B"); game.wait(120)

    # Vérifications
    expect_text(game, "2/2 : HOENN/KANTO")
