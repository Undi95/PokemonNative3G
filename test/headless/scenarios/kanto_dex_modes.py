# Build KANTO_DEBUG=1 : MEWTWO, debug « Débloquer les 2 POKéDEX » (151 vus), Options > POKéDEX = KANTO, puis ouvre le Pokédex de Rouge Feu
# depuis le menu Start et parcourt : sommaire, liste numérique, fiche, zone, retour.
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
    game.tap("R"); game.wait(30); game.tap("DOWN", 7, gap=10); game.wait(20); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120); game.tap("B")
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("UP", 5, gap=10); game.wait(10); game.tap("A"); game.wait(240)
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(200); check_screen(game, "kanto_dex_modes-1er habitat")   # 1er habitat
    game.tap("A"); game.wait(200); check_screen(game, "kanto_dex_modes-fiche du 1er Pokémon")   # fiche du 1er Pokémon
    game.tap("A"); game.wait(200); check_screen(game, "kanto_dex_modes-page suivante (zone)")   # page suivante (zone)
    game.tap("B"); game.wait(150); game.tap("B"); game.wait(150); game.tap("B"); game.wait(200)
    game.tap("DOWN", 9, gap=10); game.wait(20)
    for i in range(4):                   # A à Z, type, poids, taille : liste puis 1re fiche
        game.tap("A"); game.wait(200); game.tap("A"); game.wait(200)
        game.tap("B"); game.wait(150); game.tap("B"); game.wait(200); game.tap("DOWN"); game.wait(20)
    game.tap("B"); game.wait(200)
