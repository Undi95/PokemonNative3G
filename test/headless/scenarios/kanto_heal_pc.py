# Build KANTO_DEBUG=1 : MEWTWO, Jadielle, Centre Pokémon : soin (moniteur de RF) puis PC (écran de RF).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import leave_map, talk_to, walk_to, wait_until
from kanto_tour import debug_warp, give_mewtwo, log


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    debug_warp(game, 1)
    walk_to(game, 26, 27); leave_map(game, "UP"); log(game, "Centre Pokémon")
    walk_to(game, 7, 4); talk_to(game, "UP"); log(game, "soin")
    walk_to(game, 11, 2); game.tap("UP"); game.wait(20); game.tap("A"); game.wait(240); log(game, "PC")
    game.tap("B", 4, gap=60); game.wait(120)

    # Vérifications
    expect_text(game, "Vos POKéMON sont en super forme")
    expect_text(game, "allume le PC")
    expect(game, all(m[2] == m[3] for m in game.state.party), "équipe soignée (PV au max)")
