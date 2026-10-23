# Build KANTO_DEBUG=1 : option MENUS = KANTO, Centre Pokémon de Jadielle, PC du joueur > objets > RETIRER :
# PC objets plein écran de RF (item_pc.c), POTION de départ retirée, retour au sous-menu du PC.
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
    # Options > MENUS = KANTO
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 4, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    game.tap("START"); game.wait(30); game.tap("UP", 4, gap=10); game.tap("B"); game.wait(30)  # menu Start : curseur sur DEBUG
    debug_warp(game, 1)
    walk_to(game, 26, 26); wait_until(game, lambda s: s.free); log(game, "centre")
    walk_to(game, 11, 2); game.press("UP", 4); game.wait(20)
    game.tap("A"); game.wait(120); game.tap("A"); game.wait(90); log(game, "menu pc")
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(90); log(game, "pc joueur")
    game.tap("A"); game.wait(60); log(game, "objets")
    game.tap("A"); game.wait(240); log(game, "pc objets rf")
    game.tap("A"); game.wait(60); log(game, "menu objet")
    game.tap("A"); game.wait(60); log(game, "quantité")
    game.tap("A"); game.wait(120); log(game, "retiré")
    game.tap("A", 2, gap=60); game.tap("B"); game.wait(240); log(game, "retour")
