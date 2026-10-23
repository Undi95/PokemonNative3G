# Build KANTO_DEBUG=1 : MEWTWO, DEBUG « TOUR DRESSEURS » (hall), défi SIMPLES (accueil), 1er étage,
# combat contre le dresseur (type Colline + aiguillage Tour : nom, classe, image, répliques), montée au 2e.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp, give_mewtwo
from driver import wait_until, walk_to, finish_dialog


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    debug_warp(game, 32); log(game, "hall")
    walk_to(game, 9, 7); log(game, "défi")
    walk_to(game, 9, 3); game.press("UP", 20); wait_until(game, lambda s: s.free); log(game, "1er étage")
    game.wait(60)
    walk_to(game, 10, 12); log(game, "avant combat")
    game.press("DOWN", 4); game.wait(30)
    for _ in range(40):
        if game.state.battle:
            break
        game.tap("A", hold=2, gap=20)
    log(game, "combat")
    finish_dialog(game); log(game, "après combat")
