# Build KANTO_DEBUG=1 : option SAC = KANTO, objets du debug, combat sauvage sur la Route 1 :
# capture, surnom : écran de nom de Rouge Feu (option MENUS = KANTO).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import GameError, leave_map, wait_until, walk_to
from kanto_tour import debug_warp, give_mewtwo, log
from kanto_wild import Battle, stop_at_battle
from redleaf_acro import close_menus


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    give_mewtwo(game)
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 4, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    game.tap("START"); game.wait(30); game.tap("UP", 5, gap=10); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
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
    game.wait(500); game.tap("A", 3, gap=60); game.wait(120)       # messages d'entrée
    game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(240); log(game, "sac en combat")
    game.tap("RIGHT", 1, gap=90); game.wait(60); log(game, "balls")
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(400); log(game, "balle lancée")
    game.tap("A", 14, gap=100); game.wait(60); log(game, "écran de nom")   # OUI au surnom, puis des lettres
    game.press("START", 2); game.wait(30); game.tap("A"); game.wait(300)
    for _ in range(40):
        if not game.state.battle:
            break
        game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free); log(game, "fin")

    # Vérifications
    expect_battle(game, foe="SPECIES_PIDGEY", outcome="CAUGHT")
    expect_party(game, "SPECIES_PIDGEY", 2)
    expect_text(game, "Donner un surnom au ROUCOOL capturé")
