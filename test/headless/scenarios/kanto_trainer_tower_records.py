# Build KANTO_DEBUG=1 : DEBUG « TOUR DRESSEURS », tableau des temps du hall (special ShowBattleRecords de RF, VAR_0x8004 = 1)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from driver import wait_until, walk_to


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    debug_warp(game, 32)
    walk_to(game, 8, 11); game.press("UP", 4); game.wait(20)
    game.tap("A"); game.wait(150); log(game, "records")
    game.tap("A"); game.wait(120); wait_until(game, lambda s: s.free); log(game, "retour")
