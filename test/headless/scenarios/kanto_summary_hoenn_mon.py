# Option MENUS = KANTO : la fiche de Rouge Feu d'un Pokémon reçu à Hoenn (Bourg-en-Vol) dit où il a été rencontré
# (bug Android du 2026-11-01 : « Rencontré à un échange », RF ne nommait que les lieux de Kanto), et son sprite
# animé d'Émeraude (option POKéMON = HOENN) revient à l'image de repos (détecteur « Pokémon figé »).
# Sans POKéDEX NATIONAL, le numéro (décisions du 2026-11-03 et du 2026-11-04) : celui des POKéMON du POKéDEX de HOENN
# (TORCHIC, 255) quand on a ce POKéDEX, « ??? » sans lui ; « ??? » pour ceux de Johto (GERMIGNON).
from driver import *
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, pick, press_until_free

FIXTURE = "hoenn"
KANTO_START = 0
OPTION_MENU_STYLE = 11


def open_summary(game):
    """Menu Start > POKéMON > le 1er > RÉSUMÉ ; la marque d'avant."""
    open_start_entry(game, "POKéMON"); game.wait(240)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "RESUME"); game.wait(300)
    return since


def close(game):
    for _ in range(4):
        game.tap("B"); game.wait(120)
        if game.state.free:
            break
    press_until_free(game)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_TORCHIC", 5)
    game.give_mon("SPECIES_CHIKORITA", 5)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.flag("FLAG_SYS_POKEDEX_GET", 1)
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    national = game.dev("jeu.pokedex")
    since = open_summary(game)
    game.shot("fiche")
    expect_text(game, "BOURG-EN-VOL", since)
    expect_no_text(game, "échange", since)
    expect(game, "national 0" in national, f"sans le national ({national.splitlines()[0]})")
    expect_text(game, "255", since)
    expect_no_text(game, "???", since)
    game.wait(200)                                                      # l'animation finie
    game.shot("fiche_apres_animation")
    since = mark(game)
    game.tap("DOWN"); game.wait(120)                                    # GERMIGNON
    game.shot("fiche_johto")
    expect_text(game, "???", since)
    close(game)

    game.flag("FLAG_SYS_POKEDEX_GET", 0)                                # sans le POKéDEX de HOENN
    since = open_summary(game)
    game.shot("fiche_sans_pokedex")
    expect_text(game, "???", since)
    close(game)
