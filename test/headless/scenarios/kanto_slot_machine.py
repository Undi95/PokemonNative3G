# Build KANTO_DEBUG=1 : objets du debug (étui à jetons, 500 jetons), Casino de Céladopole, machine à sous de RF :
# mise (BAS), arrêt des rouleaux (A), sortie (B).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, walk_to


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    debug_warp(game, 8); log(game, "céladopole")
    walk_to(game, 34, 22); game.press("UP", 20); wait_until(game, lambda s: s.free); log(game, "casino")
    walk_to(game, 4, 6); game.press("RIGHT", 4); game.wait(20)
    game.tap("A"); game.wait(120); log(game, "jouer ?")
    game.tap("A"); game.wait(400); log(game, "machine")
    game.tap("DOWN"); game.wait(60); game.tap("DOWN"); game.wait(60); log(game, "mise")
    game.tap("A"); game.wait(40); game.tap("A"); game.wait(40); game.tap("A"); game.wait(200); log(game, "rouleaux")
    game.tap("A", 3, gap=60); game.wait(60)
    game.tap("B"); game.wait(90); log(game, "quitter ?")
    game.tap("A"); game.wait(300); log(game, "fin")
