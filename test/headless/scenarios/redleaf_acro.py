# Build KANTO_DEBUG=1 : option PERSO = Red, objets du debug, Vélo Cross depuis le sac,
# roue arrière (B maintenu) sur place puis en roulant : sprites de Red faits pour le Vélo Cross.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import wait_until
from kanto_tour import log

ACRO_BIKE_ROW = 12   # place du Vélo Cross dans la poche Objets Rares, une fois tous les objets donnés


def close_menus(game):
    for _ in range(10):
        if game.state.free:
            break
        game.tap("B"); game.wait(40)
    wait_until(game, lambda s: s.free); game.wait(30)


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    # Options > PERSO = Red
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    # DEBUG > objets (le menu Start se rouvre sur OPTIONS)
    game.tap("START"); game.wait(30); game.tap("UP", 4, gap=10); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    # Sac > Objets Rares > Vélo Cross > Utiliser
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(150)
    game.tap("RIGHT", 4, gap=40); game.wait(60); game.tap("DOWN", ACRO_BIKE_ROW, gap=10); game.wait(60)
    log(game, "sac")
    game.tap("A"); game.wait(30); game.tap("A"); game.wait(200)
    wait_until(game, lambda s: s.free); log(game, "à vélo")
    game.press("B", 120); log(game, "roue arrière")
    game.press("B+RIGHT", 60); game.press("B+DOWN", 60); game.press("B+LEFT", 60); game.press("B+UP", 60)
    game.press("B", 60); game.wait(60); log(game, "fin")

    # Vérifications
    expect_text(game, "VELO CROSS est sélectionné")
