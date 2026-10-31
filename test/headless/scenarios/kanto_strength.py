# Build KANTO_DEBUG=1 : DEBUG « POKé MONTURE + badges », Route Victoire 1F (Kanto) : FORCE sur un rocher, puis on le
# pousse. Avant 2026-10-31, le script de RF posait FLAG_KANTO_SYS_USE_STRENGTH alors que le moteur lit
# FLAG_SYS_USE_STRENGTH, et le moteur ne reconnaissait que le rocher d'Émeraude (OBJ_EVENT_GFX_PUSHABLE_BOULDER) :
# on ne pouvait pas pousser les rochers à Kanto. Arbres, rochers et blocs de Force ont maintenant un seul jeu de
# scripts (badge de la région).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo
from redleaf_acro import close_menus
from driver import finish_dialog, mark, saw_text, wait_until

BOULDERS = ((7, 18), (4, 12), (16, 3))
SIDES = (("RIGHT", -1, 0), ("LEFT", 1, 0), ("DOWN", 0, -1), ("UP", 0, 1))


def try_push(game, boulder):
    """Force sur le rocher depuis chaque côté où l'on peut se tenir ; rend (FORCE proposée, côté qui a fait bouger)."""
    asked = False
    for direction, dx, dy in SIDES:
        start = (boulder[0] + dx, boulder[1] + dy)
        game.warp("KantoVictoryRoad_1F", *start); game.wait(30)
        if game.state.pos != start:
            continue
        game.press(direction, 1); game.wait(20)
        since = mark(game)
        game.tap("A"); game.wait(60)
        finish_dialog(game); game.wait(30)
        asked |= saw_text(game, "FORCE", since)
        game.press(direction, 16); game.wait(60)
        if boulder not in {o[:2] for o in game.state.objects}:
            log(game, "poussé")
            return asked, direction
    return asked, None


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 14, gap=10); game.tap("A")
    game.wait(60); close_menus(game)
    results = {}
    for boulder in BOULDERS:
        results[boulder] = try_push(game, boulder)
        if results[boulder][1]:
            break

    # Vérifications
    expect(game, any(asked for asked, _ in results.values()), "un rocher propose FORCE")
    expect(game, any(side for _, side in results.values()), f"un rocher de Kanto se pousse ({results})")
