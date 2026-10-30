# Build KANTO_DEBUG=1 : MEWTWO, téléport à Argenta, arène : le campeur (dresseur qui repère
# le joueur) puis PIERRE (champion).
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import leave_map, talk_to, wait_until, walk_to
from kanto_tour import debug_warp, give_mewtwo, log


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    debug_warp(game, 2); log(game, "Argenta")
    walk_to(game, 15, 17); leave_map(game, "UP"); log(game, "arène")
    walk_to(game, 6, 8); log(game, "après le campeur")
    walk_to(game, 6, 6); talk_to(game, "UP"); log(game, "après PIERRE")

    # Vérifications
    expect_battle(game, trainer="TRAINER_KANTO_CAMPER_LIAM", outcome="WON")
    expect_battle(game, trainer="TRAINER_KANTO_LEADER_BROCK", outcome="WON")
    expect_text(game, "Tu es encore loin de pouvoir te battre contre PIERRE")
