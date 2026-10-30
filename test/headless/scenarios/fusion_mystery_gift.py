# Build KANTO_DEBUG=1 : DEBUG « Carte de vol » (RUBIS et SAPHIR rendus à CÉLIO), sauvegarde, reset : le menu
# principal propose CADEAU MYST. ; les trois CARTES MYSTÈRE (TICKET AURORA, TICKET MYSTIK, VIEILLE CARTE), les objets
# reçus, la sauvegarde, retour à l'écran titre ; au menu principal suivant, l'option a disparu.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo
from redleaf_acro import close_menus
from driver import wait_until, save_game


def to_main_menu(game, extra=0):
    # extra : après un reset, l'intro et l'écran titre sont plus longs
    game.wait(300); game.tap("START"); game.wait(120 + extra); game.tap("START"); game.wait(200 + extra // 2)


def play(game):
    to_main_menu(game); game.tap("A"); game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 7, gap=10); game.tap("A")
    game.wait(240); game.tap("B"); game.wait(120); game.tap("B"); game.wait(120); close_menus(game)
    save_game(game, 4)
    log(game, "sauvé")
    game.press("A+B+START+SELECT", 1)
    to_main_menu(game, 400); log(game, "menu principal")
    game.tap("DOWN", 2, gap=20); game.wait(30); log(game, "curseur CADEAU")
    game.tap("A"); game.wait(240); log(game, "connexion")
    for k in range(3):
        game.tap("A"); game.wait(150); log(game, "carte %d" % k)
        game.tap("A"); game.wait(200); log(game, "reçu %d" % k)
        game.wait(200); game.tap("A"); game.wait(60); log(game, "rangé %d" % k)
        game.tap("A"); game.wait(60)
    log(game, "fin")
    for k in range(4):
        game.tap("A"); game.wait(150); log(game, "sauvegarde %d" % k)
    game.wait(300)
    to_main_menu(game, 400); log(game, "menu principal après")

    # Vérifications
    expect_item(game, "ITEM_AURORA_TICKET", 1)
    expect_item(game, "ITEM_MYSTIC_TICKET", 1)
    expect_item(game, "ITEM_OLD_SEA_MAP", 1)
    expect_flag(game, "FLAG_ENABLE_SHIP_FARAWAY_ISLAND")
    expect_text(game, "Tous les CADEAUX MYSTÈRE ont été reçus")
