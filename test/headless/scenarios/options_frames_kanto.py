# Options > FENETRE, cadres 21 à 29 = cadres de Rouge Feu (docs/A-TESTER.md, 2026-11-03 ; src/text_window.c,
# sWindowFrames après les 20 d'Émeraude) : le menu Start avec chacun (capture), l'écran des options qui affiche
# « TYPE 29 » dans son propre cadre, et la question de SAUVER (OUI/NON et fenêtre d'infos dans le cadre choisi). Comme
# dans les deux jeux, la boîte de dialogue garde son cadre standard.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from menu_helpers import open_start_entry, press_until_free

OPTION_FRAME = 1


def play(game):
    continue_game(game)
    for frame in range(20, 29):
        game.dev("jeu.options", OPTION_FRAME, frame)
        wait_until(game, lambda s: s.free)
        game.tap("START"); game.wait(40)
        log(game, f"menu-cadre-{frame + 1}")
        press_until_free(game)

    # L'écran des options, avec le cadre 29
    since = mark(game)
    open_start_entry(game, "OPTIONS"); game.wait(120)
    log(game, "options-cadre-29")
    shown = [" ".join(text.split()) for _, _, text in game.texts[since:]]
    expect(game, "TYPE" in shown and shown[shown.index("TYPE") + 1] == "29", f"FENETRE : TYPE 29 ({shown})")
    press_until_free(game)

    # SAUVER : la question et la fenêtre d'infos dans le cadre 21
    game.dev("jeu.options", OPTION_FRAME, 20)
    since = mark(game)
    open_start_entry(game, "SAUVER"); game.wait(120)
    log(game, "sauver-cadre-21")
    expect_text(game, "sauvegarder", since)
    press_until_free(game)
