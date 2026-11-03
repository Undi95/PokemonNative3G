# Pokédex de RF, page ZONE des chiens errants (docs/A-TESTER.md, 2026-11-03 ; GetRoamerPokedexAreaMarkers de
# wild_pokemon_area.c, les 3 errants dans la fusion) : RAIKOU, ENTEI et SUICUNE lâchés (jeu.errants 1, comme le script
# du Centre de l'Île 1), chacun a une seule marque, sur la route où il se trouve (captures « zone-ESPECE » à comparer
# aux cartes notées par jeu.errants).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, press_until_free

OPTION_POKEDEX = 10
ROAMERS = ("raikou", "entei", "suicune")      # n° 243 à 245


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    roamers = game.dev("jeu.errants", 1)
    game.note(f"ERRANTS {roamers}")
    expect(game, len(re.findall(r"actif 1", roamers)) == 3, f"3 errants lâchés ({roamers})")

    game.flag("FLAG_SYS_POKEDEX_GET", 1)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    game.dev("jeu.pokedex", 245, 1)
    game.dev("jeu.options", OPTION_POKEDEX, 1)
    open_start_entry(game, "POKéDEX"); game.wait(240)
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(200)            # MODE NUMERIQUE: NATIONAL
    game.tap("DOWN", 242, hold=2, gap=4); game.wait(60)
    for name in ROAMERS:
        since = mark(game)
        game.tap("A"); game.wait(200); game.tap("A"); game.wait(200)          # fiche, puis page ZONE
        game.shot(f"zone-{name}")
        expect_text(game, name.upper(), since)
        game.tap("B"); game.wait(150); game.tap("B"); game.wait(150)
        game.tap("DOWN"); game.wait(30)
    press_until_free(game)
