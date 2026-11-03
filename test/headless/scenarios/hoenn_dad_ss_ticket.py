# Départ pour Kanto (2026-11-03, docs/A-TESTER.md) : après la Ligue de Hoenn, en rentrant à la maison, PAPA donne le
# PASSE BATEAU de M. MARCO et parle du navire qui part maintenant pour KANTO (PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV,
# VAR_LITTLEROOT_HOUSES_STATE_MAY = 3). La suite (menu du ferry, voyage) : kanto_travel*.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import maps


def play(game):
    continue_game(game)
    game.var("VAR_LITTLEROOT_HOUSES_STATE_MAY", 3)
    game.flag("FLAG_RECEIVED_SS_TICKET", 0)
    game.flag("FLAG_HIDE_PLAYERS_HOUSE_DAD", 0)
    game.item("ITEM_SS_TICKET", -game.item("ITEM_SS_TICKET"))
    since = mark(game)
    group, num = maps.find_map("LittlerootTown_BrendansHouse_1F")
    game.command("warp", group, num, 8, 2)            # l'escalier : après le Panthéon, on descend de la chambre
    game.wait(60)
    finish_dialog(game, limit=800)
    expect(game, game.state.pos[0] < 11 and game.state.pos[1] < 9,
           f"après la scène, le joueur est dans la maison (11 × 9 cases : {game.state.pos})")
    expect(game, saw_text(game, "M. MARCO", since), "PAPA : un PASSE de M. MARCO")
    expect(game, saw_text(game, "un navire part maintenant pour KANTO", since), "PAPA parle du navire pour KANTO")
    expect_item(game, "ITEM_SS_TICKET", 1)
    expect_flag(game, "FLAG_RECEIVED_SS_TICKET", 1)
    expect(game, game.var("VAR_LITTLEROOT_HOUSES_STATE_MAY") != 3, "la scène ne se rejoue pas")
