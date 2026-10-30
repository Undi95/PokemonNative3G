# Build KANTO_DEBUG=1 : DEBUG > POKéDEX Kanto complet, téléport GAME FREAK (Céladopole), le designer remet
# le diplôme de RF. Avant, le jeu se bloquait (stub + waitstate).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 11, gap=10); game.tap("A"); game.wait(60)
    game.tap("B"); game.wait(30); game.tap("B"); wait_until(game, lambda s: s.free)
    debug_warp(game, 29); log(game, "Game Freak")
    game.tap("UP"); game.wait(30); game.tap("A"); game.wait(200)
    for _ in range(4):
        game.tap("A"); game.wait(150)
    game.wait(600); log(game, "diplôme")
    game.tap("A"); game.wait(200)
    wait_until(game, lambda s: s.free); log(game, "fin")

    # Vérifications
    expect_text(game, "Tu as complété ton POKéDEX")
    expect_text(game, "Ce document certifie")
