# Build KANTO_DEBUG=1 : comme kanto_travel, puis DEBUG « carte de vol » (Ligue de Kanto + Rubis/Saphir), téléport
# Carmin sur Mer, marin du port : bateau pour POIVRESSEL ; là-bas, l'employé propose CARMIN SUR MER.
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
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 7, gap=10); game.tap("A")
    game.wait(240); game.tap("B", 3, gap=60); game.wait(200)
    wait_until(game, lambda s: s.free); log(game, "flags de liaison")
    debug_warp(game, 7)
    walk_to(game, 24, 32)
    talk_to(game, "DOWN"); game.wait(120); log(game, "Poivressel"); expect_map(game, "SlateportCity_Harbor", (8, 11))
    ferry_to_kanto(game); game.wait(120); log(game, "Carmin"); expect_map(game, "VermilionCity", (24, 32))

    # Vérifications
    expect_flag(game, "FLAG_KANTO_SYS_CAN_LINK_WITH_RS")
    expect_text(game, "Un navire part pour POIVRESSEL, à HOENN")
    expect_text(game, "Cap sur CARMIN SUR MER, à KANTO")
