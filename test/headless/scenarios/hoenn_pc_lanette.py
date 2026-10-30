# Build KANTO_DEBUG=1 : DEBUG « Deux Ligues finies » (ANNETTE et LÉO rencontrés), Centre Pokémon de Nénucrique :
# le PC affiche « PC d'ANNETTE » à Hoenn (et pas LÉO).
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, walk_to, leave_map


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 13, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    debug_warp(game, 21)
    walk_to(game, 24, 15); leave_map(game, "UP"); log(game, "Centre")
    walk_to(game, 10, 2); game.tap("UP"); game.wait(20); game.tap("A"); game.wait(150)
    game.tap("A"); game.wait(150); log(game, "PC")

    # Vérifications
    expect_text(game, "PC d’ANNETTE")
    expect_no_text(game, "PC de LÉO")
