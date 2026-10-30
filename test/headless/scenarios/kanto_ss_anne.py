# Build KANTO_DEBUG=1 : DEBUG > Départ S.S. Anne : sur le pont, le S.S. Anne quitte Carmin sur Mer (corne, fumée,
# sillage), puis le joueur revient à quai. Avant, le jeu se bloquait (stub + waitstate).
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
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 10, gap=10); game.tap("A")
    game.wait(300); log(game, "pont")
    wait_until(game, lambda s: s.free); log(game, "fin")

    # Vérifications
    expect_flag(game, "FLAG_KANTO_HIDE_SS_ANNE")
    expect_map(game, "VermilionCity")
