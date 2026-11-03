# Le Prof. CHEN en personne note le POKéDEX (2026-11-03, docs/A-TESTER.md ; data/kanto/data/scripts/pokedex_rating.inc,
# specials GetPokedexCount et GetProfOaksRatingMessage, qui ne faisaient rien avant le 2026-10-31) : au labo de Bourg
# Palette, « Niveau POKéDEX: 40 POKéMON vus et 40 POKéMON pris. », l'observation de CHEN pour ce nombre, la fanfare de
# RF ; puis avec le POKéDEX NATIONAL, la ligne du POKéDEX NATIONAL. (Les aides utilisent GetPokedexCount : l'assistant
# de la Route 11, scénario kanto_doubles.)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts


def rate(game):
    game.warp("PalletTown_ProfessorOaksLab", 6, 4); game.wait(30)
    since, sounds = mark(game), len(game.sounds)
    talk_to(game, "UP")
    return " ".join(t for _, t in texts(game, since)), [s for _, s in game.sounds[sounds:]]


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.flag("FLAG_KANTO_HIDE_OAK_IN_HIS_LAB", 0)
    game.var("VAR_KANTO_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB", 9)
    game.dev("jeu.pokedex", 40)

    said, sounds = rate(game)
    game.note(f"CHEN : {said[-200:]} ; sons {sounds}")
    expect(game, "40 POKéMON vus et 40 POKéMON pris" in said, f"CHEN compte 40 vus, 40 pris ({said[:120]})")
    rating = said.split("Observation du PROF. CHEN:")[-1].strip()
    expect(game, "Observation du PROF. CHEN" in said and len(rating) > 10, f"CHEN donne son observation ({rating[:80]})")
    expect(game, "MUS_RG_DEX_RATING" in sounds, f"fanfare de la note ({sounds})")
    expect(game, "NATIONAL" not in said, "pas de POKéDEX NATIONAL")

    # Plus de POKéMON : une autre observation ; POKéDEX NATIONAL : sa ligne en plus
    game.dev("jeu.pokedex", 151, 1)
    said2, _ = rate(game)
    game.note(f"CHEN : {said2[-240:]}")
    rating2 = said2.split("Observation du PROF. CHEN:")[-1]
    expect(game, rating2[:40] != rating[:40], f"151 : une autre observation ({rating2[:80]})")
    expect(game, "POKéDEX NATIONAL" in said2, f"POKéDEX NATIONAL : sa ligne ({said2[-120:]})")
