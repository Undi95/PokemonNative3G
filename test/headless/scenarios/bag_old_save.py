# Une sauvegarde d'avant le sac sans limite (saves/windows-2026-11-04-kanto-sac.sav, faite par save_old_bag_prepare avec
# l'exe du commit dad052c3b) se continue avec tout son sac : Objets et Objets rares de l'ancien bloc « BAG1 », Balls de
# SaveBlock1 (BagSave_Read) ; une fois resauvegardée, le sac est dans le nouveau bloc « BAG2 » et le reste après un
# redémarrage, avec des Balls au-delà des 16 places d'avant.
from driver import *
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, save
from menu_helpers import bag
from save_old_bag_prepare import GIVEN

SAVE = "windows-2026-11-04-kanto-sac.sav"


def counts(game):
    b = bag(game)
    total = {}
    for pocket in ("poche 1", "poche 2", "poche 3", "poche 4", "poche 5"):
        for n, _, q in b.get(pocket, []):
            total[n] = total.get(n, 0) + q
    return total, b


def play(game):
    continue_game(game)
    before, rows = counts(game)
    potion_lines = [r for r in rows.get("poche 1", []) if r[0] == names.number("ITEM_POTION")]
    game.item("ITEM_POKE_BALL", 5000)
    save(game)
    game.press("A+B+START+SELECT", 2)
    continue_game(game)
    after, rows = counts(game)
    ball_lines = [r for r in rows.get("poche 2", []) if r[0] == names.number("ITEM_POKE_BALL")]

    missing = [(item, count, before.get(names.number(item), 0)) for item, count in GIVEN
               if before.get(names.number(item), 0) != count]
    expect(game, not missing, f"ancien sac repris en entier (écarts : {missing})")
    expect(game, len(potion_lines) == 2, f"150 POTIONS sur deux lignes ({potion_lines})")
    expect(game, after.get(names.number("ITEM_POKE_BALL")) == 5120 and len(ball_lines) > 16,
           f"après sauvegarde et redémarrage : 5 120 POKé BALLS ({after.get(names.number('ITEM_POKE_BALL'))}, "
           f"{len(ball_lines)} lignes)")
    kept = [(item, count) for item, count in GIVEN if item != "ITEM_POKE_BALL" and after.get(names.number(item)) != count]
    expect(game, not kept, f"le reste aussi (écarts : {kept})")
