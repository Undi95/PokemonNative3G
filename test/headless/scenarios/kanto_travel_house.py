# Build KANTO_DEBUG=1 : comme kanto_travel (DEBUG « Deux Ligues finies » donne aussi 999999¥), puis achat de la maison
# de Bourg Palette : fondu au noir, porte ouverte, boîte aux lettres revenue ; on entre (pas de maman).
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp, ferry_to_kanto
from redleaf_acro import close_menus
from driver import wait_until, walk_to, talk_to


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 13, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    debug_warp(game, 35)
    ferry_to_kanto(game)
    game.wait(60); log(game, "arrivée")
    walk_to(game, 4, 8)
    talk_to(game, "UP"); log(game, "achat")
    walk_to(game, 6, 8)
    game.press("UP", 1); game.wait(20); game.press("UP", 8); game.wait(120); log(game, "entrée (doit être dans la maison)")

    # Vérifications
    expect_flag(game, "FLAG_PALLET_HOUSE_BOUGHT")
    expect_text(game, "achète la maison")
    expect_map(game, "PalletTown_PlayersHouse_1F")
