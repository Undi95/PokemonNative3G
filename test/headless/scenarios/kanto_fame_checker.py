# Build KANTO_DEBUG=1 : DEBUG « MEMORYDEX complet », puis MEMORYDEX depuis le sac (Objets rares) :
# liste des 16 personnes, portrait, fiches (PNJ), lecture d'une fiche, retour au sac.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from redleaf_acro import close_menus
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 12, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(200)
    game.tap("RIGHT", 4, gap=40); game.wait(60)
    game.tap("UP", 30, gap=4); game.wait(30); log(game, "sac")
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(240); log(game, "memorydex")
    game.tap("DOWN", 2, gap=30); game.wait(60); log(game, "pierre")
    game.tap("START"); game.wait(120); log(game, "portrait")
    game.tap("START"); game.wait(90)
    game.tap("A"); game.wait(90); log(game, "fiches")
    game.tap("A"); game.wait(120); log(game, "lecture")
    game.tap("A", 4, gap=60); game.wait(60)
    game.tap("B"); game.wait(60); game.tap("B"); game.wait(180); log(game, "retour sac")

    # Vérifications
    expect_text(game, "MEMORYDEX est sélectionné")
    expect_text(game, "CHAMPION d’ARENE d’ARGENTA: PIERRE")
