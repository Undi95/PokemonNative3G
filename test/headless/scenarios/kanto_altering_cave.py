# Grotte Métamo de l'Île 6 (2026-11-03) : comme dans RF (wild_encounter.c, GetCurrentMapWildMonHeaderId), la table de
# rencontres suit VAR_ALTERING_CAVE_WILD_SET de RF (VAR_KANTO_ALTERING_CAVE_WILD_SET ; 0 : NOSFERAPTI, 1 : WATTOUAT) et
# non la variable de la Caverne Altérée de Hoenn ; la page ZONE du Pokédex de RF (wild_pokemon_area.c) lit la même :
# captures « zone-nosferapti-0 » (marque sur la grotte) et « zone-nosferapti-1 » (pas de marque) à revoir.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_unown import Battle, stop_at_battle, run_away
from menu_helpers import open_start_entry, press_until_free

OPTION_POKEDEX = 10


def encounter(game):
    """Allers-retours dans la grotte jusqu'à un combat : l'espèce sauvage."""
    game.warp("SixIsland_AlteringCave", 18, 15); game.wait(30)
    try:
        for i in range(60):
            walk_to(game, 16 if i % 2 == 0 else 30, 15, on_battle=stop_at_battle)
    except Battle:
        wait_until(game, lambda s: s.foe, limit=600)
        species = game.state.foe[0][0]
        run_away(game)
        return species
    return None


def zone_page(game, shot):
    """Pokédex de RF, MODE NUMERIQUE: KANTO, n° 41 (NOSFERAPTI), fiche puis page ZONE."""
    open_start_entry(game, "POKéDEX"); game.wait(240)
    game.tap("A"); game.wait(200)
    game.tap("DOWN", 40, hold=2, gap=4); game.wait(60)
    game.tap("A"); game.wait(200)
    game.tap("A"); game.wait(200)
    game.shot(shot)
    press_until_free(game)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.var("VAR_ALTERING_CAVE_WILD_SET", 0)

    game.var("VAR_KANTO_ALTERING_CAVE_WILD_SET", 1)
    first = encounter(game)
    game.var("VAR_KANTO_ALTERING_CAVE_WILD_SET", 0)
    second = encounter(game)
    game.note(f"GROTTE METAMO : table 1 -> {first}, table 0 -> {second}")
    expect(game, first == names.value("SPECIES_MAREEP"), f"table 1 : WATTOUAT ({first})")
    expect(game, second == names.value("SPECIES_ZUBAT"), f"table 0 : NOSFERAPTI ({second})")

    # Page ZONE de NOSFERAPTI, Île 6 débloquée : marque sur la grotte avec la table 0, pas avec la table 1
    game.flag("FLAG_SYS_POKEDEX_GET", 1)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    game.dev("jeu.pokedex", 41)
    game.dev("jeu.options", OPTION_POKEDEX, 1)
    game.flag("FLAG_KANTO_WORLD_MAP_SIX_ISLAND", 1)    # l'Île 6 dessinée sur la carte de la page ZONE
    zone_page(game, "zone-nosferapti-0")
    game.var("VAR_KANTO_ALTERING_CAVE_WILD_SET", 1)
    zone_page(game, "zone-nosferapti-1")
