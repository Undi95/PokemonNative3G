# Build KANTO_DEBUG=1 : option SAC = KANTO, objets du debug, Sac à Baies de Rouge Feu depuis le sac
# (poche Baies d'Émeraude) : liste, menu d'une baie, l'utiliser sur MEWTWO (message d'item_use.c), retour.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo
from redleaf_acro import close_menus
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    give_mewtwo(game)
    # Options > SAC = KANTO (menu Start : DEBUG, POKéMON, SAC... ; Options 2 crans au-dessus du bas)
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 6, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    # DEBUG > objets
    game.tap("START"); game.wait(30); game.tap("UP", 5, gap=10); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    # Sac > Objets rares > SAC A BAIES > OUVRIR
    game.tap("START"); game.wait(30); game.tap("DOWN", 2, gap=10); game.wait(10); game.tap("A"); game.wait(200)
    log(game, "sac")
    game.tap("RIGHT"); game.wait(90); game.tap("DOWN"); game.wait(30); game.tap("A"); game.wait(60); game.tap("A"); game.wait(240)
    log(game, "sac à baies")
    game.tap("DOWN", 6, gap=20); game.wait(30); log(game, "baie")
    game.tap("A"); game.wait(60); log(game, "menu baie")
    game.tap("A"); game.wait(240); log(game, "équipe ou message")
    game.tap("A", 4, gap=70); game.wait(200); log(game, "après")
    game.tap("B", 2, gap=120); game.wait(200); log(game, "retour")
    close_menus(game); log(game, "fin")

    # Vérifications
    expect_text(game, "SAC A BAIES est sélectionné")
    expect_text(game, "BAIE ORAN est sélectionné")
    expect_text(game, "aura aucun effet")
