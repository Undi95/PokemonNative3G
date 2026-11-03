# CILEO relie le réseau à Hoenn (Île 1, 2026-11-03, docs/A-TESTER.md) : le SAPHIR récupéré et remis, la fin de la
# scène de RF (OneIsland_PokemonCenter_1F_EventScript_GiveCelioSapphire) :
# - drapeaux d'après-Ligue (SetPostgameFlags de RF) : specialSaveWarpFlags |= CHAMPION_SAVEWARP, gcnLinkFlags |= bits
#   1, 2, 3 et 15 ; FLAG_KANTO_SYS_CAN_LINK_WITH_RS ;
# - vagabonds (InitRoamer) : RAIKOU, ENTEI et SUICUNE lâchés tous les trois à Kanto, N.50 (la fusion les lâche tous).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import re
import names


def system(game):
    m = re.search(r"specialSaveWarpFlags (0x[0-9a-f]+|0), gcnLinkFlags (0x[0-9a-f]+|0)", game.dev("sys.etat"))
    return int(m.group(1), 0), int(m.group(2), 0)


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_PIKACHU", 30)
    game.var("VAR_KANTO_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F", 5)
    game.flag("FLAG_KANTO_RECOVERED_SAPPHIRE", 1)
    before = system(game)
    roamers_before = game.dev("jeu.errants")

    game.warp("OneIsland_PokemonCenter_1F", 15, 7); game.wait(40)
    wait_until(game, lambda s: s.free)
    talk_to(game, "UP")
    after = system(game)
    roamers = game.dev("jeu.errants")
    game.note(f"après-Ligue : {before} -> {after}")
    game.note("vagabonds :\n" + roamers)

    expect_var(game, "VAR_KANTO_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F", 6)
    expect_flag(game, "FLAG_KANTO_SYS_CAN_LINK_WITH_RS", 1)
    expect(game, after[1] & 0x800E == 0x800E and not before[1] & 0x800E,
           f"gcnLinkFlags : bits 1, 2, 3, 15 posés ({before[1]:#x} -> {after[1]:#x})")
    expect(game, after[0] & ~before[0], f"specialSaveWarpFlags : CHAMPION_SAVEWARP posé ({before[0]:#x} -> {after[0]:#x})")
    for species in ("RAIKOU", "ENTEI", "SUICUNE"):
        number = names.number(f"SPECIES_{species}")
        line = next((l for l in roamers.splitlines() if f"espece {number} " in l), "")
        expect(game, "niveau 50 actif 1" in line, f"{species} lâché, N.50 ({line.strip()})")
