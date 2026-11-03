# Îles du Sud (2026-11-03, docs/A-TESTER.md) : avec le PASSE ÉON (FLAG_ENABLE_SHIP_SOUTHERN_ISLAND), la pierre
# du fond lance le combat contre LATIOS ou LATIAS, celui que le joueur n'a pas choisi à la télé (VAR_ROAMER_POKEMON :
# 0 = LATIAS errant, donc LATIOS ici ; sinon LATIAS ici). Combat perdu (1 PV) : la rencontre reste à faire.
FIXTURE = "hoenn"
from driver import *  # les vérifications (expect...)


def encounter(game, roamer, species):
    game.var("VAR_ROAMER_POKEMON", roamer)
    game.dev("joueur.pv", 0, 1)
    since = mark(game)
    game.warp("SouthernIsland_Interior", 13, 12); game.wait(60)
    talk_to(game, "UP", finish=False)
    battled = []
    finish_dialog(game, on_battle=lambda g: (battled.append(True), fight_battle(g)))
    expect(game, battled, f"VAR_ROAMER_POKEMON {roamer} : combat lancé par la pierre")
    expect_battle(game, foe=species, outcome="LOST")
    expect_flag(game, "FLAG_ENCOUNTERED_LATIAS_OR_LATIOS", 1)
    expect_flag(game, "FLAG_DEFEATED_LATIAS_OR_LATIOS", 0)
    return since


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MAGIKARP", 5)
    game.flag("FLAG_ENABLE_SHIP_SOUTHERN_ISLAND", 1)
    encounter(game, 0, "SPECIES_LATIOS")
    encounter(game, 1, "SPECIES_LATIAS")
    # Sans le passe : la pierre n'est qu'une inscription
    game.flag("FLAG_ENABLE_SHIP_SOUTHERN_ISLAND", 0)
    game.warp("SouthernIsland_Interior", 13, 12); game.wait(60)
    talk_to(game, "UP")
    expect(game, len(game.battles) == 2, "sans le PASSE ÉON, pas de combat")
