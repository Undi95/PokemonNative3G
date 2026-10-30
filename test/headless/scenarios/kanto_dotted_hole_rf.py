# Comme kanto_dotted_hole, avec Options > DIALOGUE = KANTO : le braille s'écrit dans la boîte de dialogue de RF.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
import kanto_dotted_hole
from driver import wait_until


def set_dialog_kanto(game):
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 2, gap=10); game.wait(20); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    game.tap("DOWN", 2, gap=20); game.wait(20); game.tap("B"); game.wait(60)   # curseur du menu Start remis sur DEBUG
    wait_until(game, lambda s: s.free)


def play(game):
    kanto_dotted_hole.play(game, at_start=set_dialog_kanto)

    # Vérifications
    expect_flag(game, "FLAG_KANTO_USED_CUT_ON_RUIN_VALLEY_BRAILLE")
    expect_map(game, "SixIsland_DottedHole_1F")
