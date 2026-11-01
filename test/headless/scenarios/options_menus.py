# Build KANTO_DEBUG=1 : MEWTWO, 2 POKéDEX (menu Start à 8 entrées), Options > MENUS = KANTO, puis menu Start (description de RF en bas)
# et équipe (couleurs de RF).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import wait_until
from kanto_tour import give_mewtwo


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30)       # menu DEBUG : Débloquer les 2 POKéDEX
    game.tap("DOWN", 6); game.tap("A"); game.wait(30); game.tap("B"); game.wait(30)
    wait_until(game, lambda s: s.free)
    game.wait(30); game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 5, gap=10); game.wait(20); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    game.wait(120); game.tap("UP", 4, gap=40); game.wait(60)   # menu Start : POKéMON
    game.tap("A"); game.wait(240); check_screen(game, "options_menus-équipe")   # équipe
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(240); check_screen(game, "options_menus-RÉSUMÉ")   # RÉSUMÉ
    game.tap("B"); game.wait(200); game.tap("B"); game.wait(200)
    game.tap("UP"); game.wait(30); game.tap("A"); game.wait(240); check_screen(game, "options_menus-SAC")   # SAC
    game.tap("B"); game.wait(200); game.tap("B"); game.wait(100)
