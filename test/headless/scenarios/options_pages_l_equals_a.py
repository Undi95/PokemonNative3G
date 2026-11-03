# Menu Options en 2 pages avec le mode de touches L=A (2026-11-03, docs/A-TESTER.md ; option_menu.c) : L sert de A
# (il ne change pas de page), R change toujours de page ; RETOUR sur chaque page ferme le menu (avec L comme avec A),
# et le jeu revient sur la carte, menu Start ouvert.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, texts

OPTION_BUTTON_MODE, BUTTON_MODE_L_EQUALS_A = 5, 2


def said(game, since):
    return " ".join(t for _, t in texts(game, since))


def closed_with_l(game):
    """L sur la ligne choisie : le menu Options se ferme (retour sur la carte, menu Start ouvert) ?"""
    start = game.frames
    game.tap("L"); game.wait(120)
    closed = any(f >= start and name == "CB2_ReturnToFieldWithOpenMenu" for f, name in game.cb2s)
    for _ in range(6):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    return closed


def play(game):
    continue_game(game)
    game.dev("jeu.options", OPTION_BUTTON_MODE, BUTTON_MODE_L_EQUALS_A)

    # Page 1 : L (= A) ne change pas de page ; R, si
    open_start_entry(game, "OPTIONS"); game.wait(150)
    since = mark(game)
    game.tap("L"); game.wait(60)
    expect(game, "2/2" not in said(game, since), f"L=A : L ne change pas de page ({said(game, since)[-60:]})")
    since = mark(game)
    game.tap("R"); game.wait(60)
    expect(game, "2/2" in said(game, since), f"R : page 2 ({said(game, since)[-60:]})")

    # Page 2 : RETOUR (HAUT depuis la 1re ligne : la liste boucle sur RETOUR) avec L ferme le menu
    game.tap("UP"); game.wait(30)
    expect(game, closed_with_l(game), "L sur RETOUR (page 2) ferme le menu Options")

    # Page 1 : de même
    open_start_entry(game, "OPTIONS"); game.wait(150)
    since = mark(game)
    game.tap("UP"); game.wait(30)
    expect(game, "2/2" not in said(game, since), "page 1 à la réouverture")
    expect(game, closed_with_l(game), "L sur RETOUR (page 1) ferme le menu Options")
