# Chaîne de pêche. Vérifié le 2026-10-24 avec une build de test (touche toujours ferrée : Fishing_CheckForBite
# et Fishing_WaitForA ; tirages en plus toujours gagnants dans FishingChain_TryShiny), sinon la touche est au hasard.
# Build KANTO_DEBUG=1 : objets du debug (CANNE), Carmin sur Mer : le GOUROU améliore la CANNE,
# puis pêches au même endroit (avec une build de test où la touche est sûre : la 2e prise doit être chromatique),
# puis un pas : la série est brisée.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, walk_to, talk_to, leave_map, finish_dialog


def fish(game, name, first=False):
    game.tap("START"); game.wait(30)
    if first:
        game.tap("DOWN", 2, gap=10)
    game.tap("A"); game.wait(200)
    if first:
        game.tap("RIGHT", 4, gap=30); game.wait(30); game.tap("DOWN", 3, gap=10); game.wait(30); log(game, "sac")
    game.tap("A"); game.wait(40); game.tap("A"); game.wait(120)
    for k in range(30):
        game.wait(30)
        if game.state.battle:
            break
    game.wait(200); log(game, name)
    finish_dialog(game); game.wait(60)


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    debug_warp(game, 7)
    walk_to(game, 9, 7); leave_map(game, "UP"); log(game, "maison")
    walk_to(game, 4, 6)
    game.press("UP", 1); game.wait(20); game.tap("A"); game.wait(60)
    for k in range(14):
        game.tap("A"); game.wait(50); log(game, "gourou %d" % k)
    finish_dialog(game)
    walk_to(game, 4, 7); leave_map(game, "DOWN"); finish_dialog(game)
    walk_to(game, 8, 9); game.press("LEFT", 1); game.wait(20)
    fish(game, "prise 1", first=True)
    fish(game, "prise 2 (chromatique)")
    walk_to(game, 9, 9); walk_to(game, 8, 9); game.press("LEFT", 1); game.wait(20)
    fish(game, "après un pas")

    # Vérifications
    expect_text(game, "est améliorée")
    expect_flag(game, "FLAG_OLD_ROD_UPGRADED")
