# La fiche d'Émeraude (MENUS = HOENN) sans POKéDEX NATIONAL (décision du 2026-11-04, la même que pour la fiche de RF) :
# un POKéMON du POKéDEX de Kanto (MEWTWO) a son numéro (« 150 ») quand on a le POKéDEX de Kanto, aucun sans lui ; un
# POKéMON de Johto (GERMIGNON), jamais (SpeciesToPokedexNum, pokemon.c).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, pick, texts, press_until_free

OPTION_MENU_STYLE = 11


def summary(game, shot):
    """Menu Start > POKéMON > le 1er > RÉSUMÉ, puis le 2e (bas) : les textes de chaque fiche."""
    open_start_entry(game, "POKéMON"); game.wait(240)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "RESUME"); game.wait(300)
    game.shot(f"{shot}-mewtwo")
    first = " ".join(t for _, t in texts(game, since))
    second_mark = mark(game)
    game.tap("DOWN"); game.wait(120)
    game.shot(f"{shot}-germignon")
    second = " ".join(t for _, t in texts(game, second_mark))
    for _ in range(6):
        game.tap("B"); game.wait(90)
        if game.state.free:
            break
    press_until_free(game)
    return first, second


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 5)
    game.give_mon("SPECIES_CHIKORITA", 5)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("jeu.options", OPTION_MENU_STYLE, 0)       # la fiche d'Émeraude
    national = game.dev("jeu.pokedex")
    expect(game, "national 0" in national, f"sans le national ({national.splitlines()[0]})")

    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    first, second = summary(game, "avec-pokedex-kanto")
    game.note(f"AVEC le Pokédex de Kanto : MEWTWO « {first[:120]} » ; GERMIGNON « {second[:120]} »")
    expect(game, "150" in first, f"MEWTWO : numéro 150 ({first[:100]})")
    expect(game, "152" not in second, f"GERMIGNON : pas de numéro ({second[:100]})")

    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 0)
    first, _ = summary(game, "sans-pokedex-kanto")
    game.note(f"SANS le Pokédex de Kanto : MEWTWO « {first[:120]} »")
    expect(game, "150" not in first, f"MEWTWO : pas de numéro sans le Pokédex de Kanto ({first[:100]})")
