# Build KANTO_DEBUG=1 : Options > BOITES COMBAT = KANTO, puis combat contre le campeur de l'arène d'Argenta :
# barre de l'équipe (Poké Balls) de Rouge Feu au début du combat de dresseur (2026-10-30).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import fight_battle, leave_map, wait_until, walk_to
from kanto_tour import debug_warp, give_mewtwo, log


def show_bar(game):
    wait_until(game, lambda s: s.battle, limit=600)
    for _ in range(40):   # la barre glisse à l'écran quand le dresseur annonce le combat
        if any("veut se battre" in t for _, _, t in game.texts[-3:]):
            break
        game.wait(10)
    game.wait(20); log(game, "barre de l'équipe")
    fight_battle(game)


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    debug_warp(game, 2)
    game.wait(30); game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 3, gap=10); game.wait(20); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120); game.tap("B")
    wait_until(game, lambda s: s.free)
    walk_to(game, 15, 17); leave_map(game, "UP")
    walk_to(game, 6, 8, on_battle=show_bar)

    # Vérifications
    expect_battle(game, trainer="TRAINER_KANTO_CAMPER_LIAM", outcome="WON")
