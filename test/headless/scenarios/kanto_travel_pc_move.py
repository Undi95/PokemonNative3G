# Build KANTO_DEBUG=1 : comme kanto_travel_pc, en DÉPLACER POKéMON : MEWTWO pris en main puis posé dans l'équipe : MEWTWO (parti au PC au départ) est grisé et
# RETIRER est refusé (« Aucune connexion avec HOENN… »). Vérifier l'image de fin.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
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
    talk_to(game, "UP")
    game.wait(60); log(game, "arrivée")
    debug_warp(game, 1)
    walk_to(game, 26, 27); leave_map(game, "UP"); log(game, "Centre")
    walk_to(game, 11, 2); game.tap("UP"); game.wait(20); game.tap("A"); game.wait(240); log(game, "PC")
    for k in range(3):
        game.tap("A"); game.wait(150)
    game.wait(400); game.press("DOWN", 4); game.wait(60); game.press("DOWN", 4); game.wait(60)
    game.press("A", 4); game.wait(400); log(game, "boîte (déplacer)")
    game.press("DOWN", 4); game.wait(60); game.press("A", 4); game.wait(200); game.press("A", 4); game.wait(200)
    log(game, "MEWTWO en main")
    game.press("UP", 4); game.wait(60); game.press("UP", 4); game.wait(60); game.press("A", 4); game.wait(300)
    log(game, "équipe ouverte")
    game.press("A", 4); game.wait(200); log(game, "posé (refusé)")
    game.wait(120); game.press("A", 4); game.wait(60)
