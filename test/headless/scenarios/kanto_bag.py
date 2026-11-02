# Build KANTO_DEBUG=1 : option SAC = KANTO, objets du debug, puis le sac de Rouge Feu : poches,
# menu d'un objet, Vélo depuis le sac (passe par item_use.c d'Émeraude), retour au sac.
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
    # Options > SAC = KANTO
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 6, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    # DEBUG > objets (le menu Start se rouvre sur OPTIONS)
    game.tap("START"); game.wait(30); game.tap("UP", 4, gap=10); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    # Sac
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(200)
    log(game, "sac ouvert")
    game.tap("DOWN", 3, gap=20); game.wait(30); game.tap("A"); game.wait(60); log(game, "menu objet")
    game.tap("B"); game.wait(60)
    game.tap("RIGHT"); game.wait(90); log(game, "objets rares")
    game.tap("DOWN", 2, gap=20); game.wait(30)
    game.tap("RIGHT"); game.wait(90); log(game, "balls")
    game.tap("LEFT"); game.wait(90)
    log(game, "vélo")                    # curseur resté sur le VÉLO COURSE
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(240)
    wait_until(game, lambda s: s.free); log(game, "à vélo")
    game.wait(60)
    # Le sac se rouvre sur les Objets rares : Seau Wailmer (message d'item_use.c d'Émeraude dans le sac de RF)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(200)
    game.tap("DOWN", 8, gap=20); game.wait(30); game.tap("A"); game.wait(60); game.tap("A"); game.wait(120)
    log(game, "seau")
    game.tap("A", 2, gap=60); game.wait(60); log(game, "retour liste")
    close_menus(game); log(game, "fin")

    # Vérifications
    expect_text(game, "VELO COURSE est sélectionné")
    expect_song(game, "MUS_RG_CYCLING")     # MUS_CYCLING de RF (MUS_CYCLING d'Émeraude : le vélo de Hoenn)
