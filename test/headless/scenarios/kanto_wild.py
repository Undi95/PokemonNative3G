# Build KANTO_DEBUG=1 : nouvelle partie, MEWTWO, téléport à Jadielle, Route 1 au sud,
# puis allers-retours dans les hautes herbes jusqu'à un combat sauvage, gagné avec la 1re attaque
# (PSYKO : le MEWTWO du menu DEBUG l'a en premier).
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
    log(game, "combat")
    fight_battle(game)
    log(game, "après le combat")

    # Vérifications
    expect_battle(game, foe="SPECIES_RATTATA", outcome="WON")
