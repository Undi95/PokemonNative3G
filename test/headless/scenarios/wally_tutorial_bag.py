# Tutoriel de capture de TIMMY (Route 102, StartWallyTutorialBattle) : son sac (PrepareBagForWallyTutorial, item_menu.c)
# ne montre qu'une POTION et une POKé BALL, puis le sac du joueur revient tel quel. Depuis le sac sans limite (2026-11-04), les poches
# sont dans gSaveBlockBag (gBagPockets) : avant, la copie prenait les anciennes poches de SaveBlock1 (vides), et le
# tutoriel montrait les vrais objets du joueur.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "hoenn"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, wait_until
from kanto_tour import log
from menu_helpers import bag


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_ZIGZAGOON", 5)
    game.item("ITEM_POTION", 5)
    game.item("ITEM_GREAT_BALL", 3)
    before = bag(game)
    game.special("StartWallyTutorialBattle")
    shown = False
    for _ in range(400):
        game.wait(20)
        if not shown:
            game.tap("A")                              # les messages du combat ; le sac, lui, est piloté par TIMMY
        if not shown and "Bag" in game.function(game.state.cb2):
            game.wait(90)
            log(game, "sac de timmy")
            shown = bag(game)
        if game.state.free and len(game.cb2s) > 3 and "Overworld" in game.function(game.state.cb2):
            break
        if shown:
            game.tap("A")
    wait_until(game, lambda s: s.free, limit=1200)
    after = bag(game)

    ids = lambda b, p: [(n, q) for n, _, q in b.get(p, [])]
    expect(game, shown and ids(shown, "poche 1") == [(names.number("ITEM_POTION"), 1)]
           and ids(shown, "poche 2") == [(names.number("ITEM_POKE_BALL"), 1)],
           f"sac de TIMMY : une POTION et une POKé BALL (DoWallyTutorialBagMenu), pas les objets du joueur "
           f"({shown and (ids(shown, 'poche 1'), ids(shown, 'poche 2'))})")
    expect(game, ids(after, "poche 1") == ids(before, "poche 1") and ids(after, "poche 2") == ids(before, "poche 2"),
           f"sac du joueur rendu ({ids(after, 'poche 1')}, {ids(after, 'poche 2')})")
