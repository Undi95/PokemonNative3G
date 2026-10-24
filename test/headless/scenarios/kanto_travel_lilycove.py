# Build KANTO_DEBUG=1 : comme kanto_travel, depuis le port de Nénucrique (PORT NENUCRIQUE).
# port propose KANTO (aller simple) : l'équipe part au PC, arrivée à Bourg Palette ; pancarte de la maison à vendre
# (pas assez d'argent), porte fermée à clé.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
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
    debug_warp(game, 36)
    log(game, "port")
    talk_to(game, "UP")
    game.wait(60); log(game, "arrivée")
    walk_to(game, 4, 8)
    talk_to(game, "UP"); log(game, "pancarte")
    walk_to(game, 6, 8)
