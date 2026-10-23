# Build KANTO_DEBUG=1 : DEBUG ARGENTA, Route 2, poste nord, entrée de la FORÊT DE JADE : aperçu « forêt » de RF
# (image + nom en fondu sur la carte, joueur bloqué pendant l'aperçu)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from driver import wait_until, walk_to, leave_map


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    debug_warp(game, 2)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 2); game.tap("A"); game.wait(40)
    game.tap("B", 3, gap=20); wait_until(game, lambda s: s.free)  # rencontres : NON
    walk_to(game, 21, 39); leave_map(game, "DOWN"); log(game, "route 2")
    walk_to(game, 5, 12); game.press("DOWN", 30); wait_until(game, lambda s: s.free); log(game, "poste")
    walk_to(game, 7, 9); game.press("DOWN", 30); game.wait(30); log(game, "forêt")
    game.wait(60); log(game, "aperçu")
    wait_until(game, lambda s: s.free); log(game, "libre")
