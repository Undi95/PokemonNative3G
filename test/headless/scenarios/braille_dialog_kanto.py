# Braille avec Options > DIALOGUE = KANTO : la boîte de dialogue de RF, avec la flèche d'attente de RF
# (CreateTextCursorSprite, 2026-10-31) sur le braille de Kanto (Chemin Rubis), et le braille de Hoenn (Caveau
# Scellé, plusieurs lignes).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from kanto_dotted_hole_rf import set_dialog_kanto
from driver import wait_until


def read_braille(game, map_name, x, y):
    game.warp(map_name, x, y); game.wait(30)
    game.press("UP", 4); game.wait(20)
    game.tap("A"); game.wait(90)


def skip_to_end(game):
    for _ in range(20):
        if game.state.free:
            return
        game.tap("A"); game.wait(60)


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    set_dialog_kanto(game)

    read_braille(game, "MtEmber_RubyPath_B5F", 7, 3)
    log(game, "kanto braille fleche")
    game.tap("A"); game.wait(90)
    log(game, "kanto braille 2")
    skip_to_end(game)

    read_braille(game, "SealedChamber_InnerRoom", 6, 9)
    log(game, "hoenn braille")
    skip_to_end(game)
    log(game, "fini")

    # Vérifications
    expect_map(game, "SealedChamber_InnerRoom")
