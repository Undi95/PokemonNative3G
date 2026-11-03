# Intro d'Émeraude laissée jouer jusqu'au combat des légendaires (docs/A-TESTER.md, 2026-11-03 : « Intro de
# Groudon/Kyogre (fonds 8bpp) toujours correcte après la correction du rendu 8bpp ») : Groudon, Kyogre, nuages, éclairs
# et Rayquaza (src/intro.c, Task_Scene3_*), capturés à des instants fixes.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "hoenn"
OPTION_INTRO = 15
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log

SCENES = (("Task_Scene3_Groudon", (20, 120, 220)), ("Task_Scene3_Kyogre", (20, 120, 220)),
          ("Task_Scene3_Clouds", (40,)), ("Task_Scene3_Lightning", (10,)), ("Task_Scene3_Rayquaza", (40, 140)))


def running(game, task):
    return any(game.function(t) == task for t in game.state.tasks)


def play(game):
    # Options > INTRO = HOENN (l'intro de RF par défaut), sauvegarde, reset : l'intro d'Émeraude
    continue_game(game)
    game.dev("jeu.options", OPTION_INTRO, 1)
    save(game)
    game.press("A+B+START+SELECT", 1)
    seen = []
    for task, moments in SCENES:
        wait_until(game, lambda s: running(game, task), step=1, limit=8000)
        start = game.frames
        seen.append(task)
        for moment in moments:
            game.wait(start + moment - game.frames)
            log(game, f"{task[12:].lower()}-{moment}")
    expect(game, len(seen) == len(SCENES), f"les scènes des légendaires ({seen})")
