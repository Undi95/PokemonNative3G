# Build KANTO_DEBUG=1 : comme kanto_travel, puis PC du Centre de Jadielle : MEWTWO (parti au PC au départ) est grisé et
# RETIRER est refusé (« Aucune connexion avec HOENN… »). Vérifier l'image de fin.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp, ferry_to_kanto
from redleaf_acro import close_menus
from driver import wait_until, walk_to, talk_to, leave_map


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
    give_mewtwo(game); log(game, "POKéMON de Kanto (comme le starter de Kanto : pas de PC avec une équipe vide)")
    debug_warp(game, 1)
    walk_to(game, 26, 27); leave_map(game, "UP"); log(game, "Centre")
    walk_to(game, 11, 2); game.tap("UP"); game.wait(20); game.tap("A"); game.wait(240); log(game, "PC")
    for k in range(3):
        game.tap("A"); game.wait(120)
    game.wait(120); log(game, "boîte")
    game.wait(700); game.press("DOWN", 4); game.wait(30)
    game.press("A", 4); game.wait(60); game.press("A", 4); game.wait(120); log(game, "retirer (refusé)")
    game.wait(300); game.press("A", 4); game.wait(60); game.press("A", 4); game.wait(150); log(game, "fin")
    game.wait(120); game.press("A", 4); game.wait(60)
    for k in range(8):
        game.press("B", 4); game.wait(90)
    wait_until(game, lambda s: s.free, limit=1500); log(game, "sorti du PC (pas de gel)")

    # Vérifications
    expect_text(game, "Gestion de Stocks de POKéMON en ligne")
    expect_map(game, "ViridianCity_PokemonCenter_1F")
