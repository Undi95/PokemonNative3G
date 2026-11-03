# MEMORYDEX (Fame Checker de RF), ce que kanto_fame_checker ne fait pas (2026-11-03, docs/A-TESTER.md) :
# - enregistré sur SELECT : il s'ouvre depuis la carte, et SELECT le referme (retour sur la carte) ;
# - une fiche se débloque en lisant un panneau (panneau de l'arène d'Argenta : famechecker FAMECHECKER_BROCK, 0) ;
# - GIOVANNI change de place dans la liste une fois battu à l'arène de Jadielle (AdjustGiovanniIndexIfBeatenInGym).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts

DEBUG_FAME_CHECKER = 12           # menu DEBUG : « MEMORYDEX complet » (src/debug_menu.c)


def open_list(game, scroll=0):
    """SELECT (MEMORYDEX enregistré), la liste défilée de scroll lignes, SELECT : (noms dans l'ordre, revenu ?)."""
    wait_until(game, lambda s: s.free)
    since = mark(game)
    game.tap("SELECT", hold=4); game.wait(240)
    for _ in range(scroll):
        game.tap("DOWN", gap=16)
    game.wait(30)
    shown = []
    for window, text in texts(game, since):
        if text not in shown:
            shown.append(text)
    game.tap("SELECT", hold=4); game.wait(150)
    back = game.state.free
    for _ in range(6):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    return shown, back


def play(game):
    continue_game(game)
    game.item("ITEM_FAME_CHECKER", 1)
    game.dev("joueur.enregistre", names.number("ITEM_FAME_CHECKER"))

    # Le panneau de l'arène d'Argenta débloque PIERRE
    game.warp("PewterCity", 11, 17); game.wait(30)
    before, back = open_list(game)
    expect(game, back, "SELECT referme le MEMORYDEX : retour sur la carte")
    game.press("UP", 1); game.wait(12)
    talk_to(game, "UP")
    after, _ = open_list(game)
    game.note(f"avant le panneau : {before}")
    game.note(f"après : {after}")
    expect(game, not any("PIERRE" in t for t in before) and any("PIERRE" in t for t in after),
           "le panneau de l'arène débloque PIERRE dans le MEMORYDEX")

    # GIOVANNI : à la fin de la liste, puis à la 10e place une fois battu à l'arène de Jadielle
    game.dev("jeu.debug", DEBUG_FAME_CHECKER)
    order, _ = open_list(game, scroll=16)
    flag = names.value("KANTO_TRAINER_FLAGS_START") + names.value("TRAINER_KANTO_LEADER_GIOVANNI") - names.value("KANTO_TRAINERS_START")
    game.flag(flag, 1)
    order_beaten, _ = open_list(game, scroll=16)
    game.note(f"liste : {order}")
    game.note(f"GIOVANNI battu : {order_beaten}")
    index = [i for i, t in enumerate(order) if "GIOVANNI" in t]
    index_beaten = [i for i, t in enumerate(order_beaten) if "GIOVANNI" in t]
    expect(game, index and index_beaten and index_beaten[0] < index[0],
           f"GIOVANNI battu à l'arène : plus haut dans la liste ({index} -> {index_beaten})")
