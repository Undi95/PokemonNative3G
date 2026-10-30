# Build KANTO_DEBUG=1 : MEWTWO (sans les objets du debug), téléport REPAIRE ROCKET (sous Giovanni), combat contre
# Giovanni, Scope Sylph ramassé à sa place, puis TOUR POKéMON 6 : Ossatueur doit être révélé par ce Scope Sylph.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp, give_mewtwo
from driver import wait_until


def press_until_free(game, n=250):
    for _ in range(n):
        if game.state.free:
            break
        game.tap("A"); game.wait(40)
    wait_until(game, lambda s: s.free)


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    give_mewtwo(game)
    debug_warp(game, 27); log(game, "Repaire")
    game.tap("UP"); game.wait(30); game.tap("A"); game.wait(120); log(game, "Giovanni")
    press_until_free(game); game.wait(60); log(game, "après Giovanni")
    game.tap("RIGHT"); game.wait(30); game.tap("A"); game.wait(200); log(game, "Scope Sylph")
    press_until_free(game); log(game, "ramassé")
    debug_warp(game, 26); log(game, "Tour 6")
    game.tap("DOWN", 3, hold=16, gap=20); game.wait(200)
    for _ in range(120):
        if game.state.battle:
            break
        game.tap("A"); game.wait(30)
    game.wait(300); log(game, "Ossatueur")
    press_until_free(game); log(game, "fini")

    # Vérifications
    expect_battle(game, trainer="TRAINER_KANTO_BOSS_GIOVANNI", outcome="WON")
    expect_item(game, "ITEM_SILPH_SCOPE", 1)
    expect_battle(game, foe="SPECIES_MAROWAK", outcome="WON")
    expect_map(game, "PokemonTower_6F")
