# Option POKéDEX (2026-11-03, docs/A-TESTER.md ; option_menu.c, IsOptionHidden) : absente de la 2e page des Options
# tant que le Prof. CHEN n'a pas donné son POKéDEX (FLAG_KANTO_SYS_POKEDEX_GET), présente ensuite ; les autres choix
# HOENN/KANTO y sont toujours.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, texts


def page2(game):
    """Les textes de la 2e page des Options, défilée jusqu'à RETOUR."""
    open_start_entry(game, "OPTIONS"); game.wait(150)
    since = mark(game)
    game.tap("R"); game.wait(60)
    game.tap("DOWN", 12, gap=12); game.wait(60)
    shown = [t for _, t in texts(game, since)]
    for _ in range(6):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free, limit=900)
    return shown


def play(game):
    continue_game(game)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 0)
    without = page2(game)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    with_dex = page2(game)
    game.note(f"sans : {without}")
    game.note(f"avec : {with_dex}")
    expect(game, "PERSO" in without and "POKéDEX" not in without, f"sans le POKéDEX de CHEN : pas d'option POKéDEX")
    expect(game, "PERSO" in with_dex and "POKéDEX" in with_dex, f"avec : l'option POKéDEX")
