# Fabrique saves/windows-2026-11-04-kanto-sac.sav (scénario bag_old_save) : à jouer avec l'exe d'AVANT le sac sans
# limite (commit dad052c3b), dont le sac est dans l'ancien bloc « BAG1 » (Objets, Objets rares) et les Balls dans
# SaveBlock1. Objets sur deux lignes (150 POTIONS), objets rares, Balls sur deux lignes, CT, baies ; puis sauvegarde.
#   python test/headless/suite.py <ancien exe> save_old_bag_prepare   puis copier build/headless/suite/save_old_bag_prepare/game.sav
from driver import *
from driver import continue_game, save

SUITE = False
FIXTURE = "kanto"

GIVEN = [("ITEM_POTION", 150), ("ITEM_SUPER_POTION", 5), ("ITEM_ESCAPE_ROPE", 3), ("ITEM_COIN_CASE", 1),
         ("ITEM_OLD_ROD", 1), ("ITEM_POKE_BALL", 120), ("ITEM_GREAT_BALL", 7), ("ITEM_TM01", 2), ("ITEM_CHERI_BERRY", 5)]


def play(game):
    continue_game(game)
    for item, count in GIVEN:
        got = int(game.item(item, count))
        expect(game, got == count, f"{item} : {got}")
    save(game)
