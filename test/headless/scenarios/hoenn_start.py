# Départ d'Émeraude, depuis la sauvegarde « hoenn » (chambre, horloge réglée) : maison de Flora (sa maman,
# sa POKé BALL, Flora arrive), sortie nord de Bourg-en-Vol, Route 101 : le PROF. SEKO poursuivi par un
# ZIGZATON, le sac, choix du starter, premier combat gagné, puis le labo.
from driver import *

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    continue_game(game)
    expect_map(game, "LittlerootTown_BrendansHouse_2F")
    take_warp(game, "LittlerootTown_BrendansHouse_1F")
    finish_dialog(game)
    take_warp(game, "LittlerootTown")
    finish_dialog(game)
    take_warp(game, "LittlerootTown_MaysHouse_1F")
    finish_dialog(game)                             # la maman de Flora
    expect_flag(game, "FLAG_MET_RIVAL_MOM")
    take_warp(game, "LittlerootTown_MaysHouse_2F")
    finish_dialog(game)
    talk_to_object(game, 5, 4)                      # la POKé BALL de Flora : Flora arrive
    expect_text(game, "FLORA")
    take_warp(game, "LittlerootTown_MaysHouse_1F")
    finish_dialog(game)
    take_warp(game, "LittlerootTown")
    finish_dialog(game)

    walk_to(game, 11, 2)                            # sortie nord : « A… A l’aide ! »
    leave_map(game, "UP")
    finish_dialog(game)
    expect_map(game, "Route101")
    expect_text(game, "Aide-moi! Dans mon SAC")
    expect_song(game, "MUS_HELP")

    since = mark(game)
    talk_to_object(game, 7, 14, finish=False)       # le sac du PROF. SEKO
    for _ in range(60):                             # écran du choix, puis « Tu choisis ce POKéMON ? » OUI
        if game.state.battle:
            break
        game.tap("A", hold=4, gap=26)
    expect(game, game.state.battle, "le premier combat commence")
    fight_battle(game)
    finish_dialog(game, answers={"surnom": "B"})    # pas de surnom, OUI pour aller voir Flora
    expect_battle(game, foe="SPECIES_ZIGZAGOON", outcome="WON")
    expect(game, len(game.state.party) == 1, "un starter dans l'équipe")
    expect_flag(game, "FLAG_SYS_POKEMON_GET")
    expect_map(game, "LittlerootTown_ProfessorBirchsLab")
