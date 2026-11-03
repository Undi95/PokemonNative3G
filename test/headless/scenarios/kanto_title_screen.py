# Écran titre de Rouge Feu (Options > TITRE = R.FEU, 2026-11-03, docs/A-TESTER.md ; CB2_InitKantoTitleScreen) : après
# la sauvegarde et un reset, l'intro de RF puis l'écran titre de RF (DRACAUFEU, flammes, MUS_RG_TITLE) ; laissé sans
# toucher, il revient à l'intro ; START : le cri de DRACAUFEU puis le menu principal de RF (kanto_main_menu).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log

OPTION_TITLE_SCREEN = 7   # jeu.options (src/debug_tools.c)


def screens_since(game, frame):
    return [name for f, name in game.cb2s if f >= frame]


def reset_to_title(game):
    start = game.frames
    game.press("A+B+START+SELECT", 2)
    wait_until(game, lambda s: "CB2_TitleScreenRun" in screens_since(game, start), limit=2000)
    return start


def play(game):
    continue_game(game)
    game.dev("jeu.options", OPTION_TITLE_SCREEN, 1)
    save(game)

    # L'écran titre de RF, à trois moments de son animation
    start = reset_to_title(game)
    for step, frames in enumerate((40, 120, 240)):
        game.wait(frames)
        log(game, f"titre {step + 1}")
    expect(game, "CB2_InitKantoTitleScreen" in screens_since(game, start), "écran titre de RF (CB2_InitKantoTitleScreen)")
    expect(game, game.state.bgm == names.value("MUS_RG_TITLE") if hasattr(game.state, "bgm") else True,
           "musique de l'écran titre de RF")

    # Sans toucher : retour à l'intro
    idle = game.frames
    for _ in range(80):
        if "KantoIntro_Start" in screens_since(game, idle) or "CB2_InitCopyrightScreenAfterBootup" in screens_since(game, idle):
            break
        game.wait(100)
    seen = screens_since(game, idle)
    expect(game, "KantoIntro_Start" in seen or "CB2_SetUpIntro" in seen,
           f"sans toucher : retour à l'intro au bout de {game.frames - idle} images ({' > '.join(seen[:4])})")

    # START : le cri de DRACAUFEU, puis le menu principal de RF
    start = reset_to_title(game)
    cries = len(game.cries)
    for _ in range(20):                               # l'écran titre n'écoute START qu'une fois son entrée finie
        if "CB2_InitKantoMainMenu" in screens_since(game, start):
            break
        game.tap("START"); game.wait(40)
    heard = [s for _, s in game.cries[cries:]]
    expect(game, heard == ["SPECIES_CHARIZARD"], f"START : le cri de DRACAUFEU ({heard})")
    expect(game, "CB2_InitKantoMainMenu" in screens_since(game, start), "START : le menu principal de RF")
