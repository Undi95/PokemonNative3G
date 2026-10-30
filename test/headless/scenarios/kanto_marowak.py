# Build KANTO_DEBUG=1 : objets du debug (dont le Scope Sylph), MEWTWO, téléport TOUR POKéMON 6, trois pas vers
# le bas : Ossatueur. Le Scope Sylph révèle le SPECTRE (« Le SPECTRE était OSSATUEUR ! »), combat, puis le
# script continue (« Le SPECTRE était la mère d'OSSELAIT… »).
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp, give_mewtwo
from redleaf_acro import close_menus
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    give_mewtwo(game)
    debug_warp(game, 26); log(game, "Tour 6")
    game.tap("DOWN", 3, hold=16, gap=20); game.wait(200); log(game, "Ossatueur")
    for _ in range(120):
        if game.state.battle:
            break
        game.tap("A"); game.wait(30)
    game.wait(300); log(game, "combat")
    for _ in range(200):
        if game.state.free:
            break
        game.tap("A"); game.wait(40)
    wait_until(game, lambda s: s.free); log(game, "fini")

    # Vérifications
    expect_battle(game, foe="SPECIES_MAROWAK", outcome="WON")
    expect_text(game, "Le SCOPE SYLPHE révèle l’identité du SPECTRE")
    expect_text(game, "Le SPECTRE était OSSATUEUR")
