# Build KANTO_DEBUG=1 : MEWTWO, téléport à Jadielle, Options > BOITES COMBAT = KANTO,
# puis combat sauvage sur la Route 1 (comme kanto_wild).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import GameError, fight_battle, leave_map, wait_until, walk_to
from kanto_tour import debug_warp, give_mewtwo, log


class Battle(Exception):
    pass


def stop_at_battle(game):
    raise Battle


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    debug_warp(game, 1); log(game, "Jadielle")
    game.wait(30); game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 4, gap=10); game.wait(20); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120); game.tap("B")
    wait_until(game, lambda s: s.free)
    walk_to(game, 23, 39); leave_map(game, "DOWN"); log(game, "Route 1")
    try:
        walk_to(game, 12, 9, on_battle=stop_at_battle)
    except Battle:
        pass
    for _ in range(60):
        if game.state.battle:
            break
        game.press("UP" if game.state.pos[1] == 9 else "DOWN", 16)
        game.wait(8)
    if not game.state.battle:
        raise GameError(f"pas de combat sauvage : {game.state}")
    game.wait(500)
    fight_battle(game)
    log(game, "après le combat")

    # Vérifications
    expect_text(game, "PAGE 2/2 : HOENN/KANTO")
    expect_battle(game, foe="SPECIES_PIDGEY", outcome="WON")
