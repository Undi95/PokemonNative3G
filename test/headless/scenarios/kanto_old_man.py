# Build KANTO_DEBUG=1 : DEBUG « VIEIL HOMME JADIELLE » (colis remis), téléport à Jadielle,
# le vieil homme montre comment attraper un POKéMON (combat de démonstration de RF).
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import finish_dialog, wait_until, walk_to
from kanto_tour import debug_warp, give_mewtwo, log


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    give_mewtwo(game)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 15, gap=10); game.tap("A")
    game.wait(60); game.tap("B"); game.wait(30); wait_until(game, lambda s: s.free)
    debug_warp(game, 1); log(game, "Jadielle")
    walk_to(game, 20, 9); log(game, "devant le vieil homme")
    game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(60)
    for _ in range(4000):
        s = game.state
        if s.free:
            break
        if s.battle:
            game.wait(10)        # combat simulé : on regarde
        else:
            game.tap("A"); game.wait(20)
    log(game, "après la démonstration")

    # Vérifications
    expect_battle(game, foe="SPECIES_WEEDLE", outcome="CAUGHT")
    expect_text(game, "ASPICOT est attrapé")
    expect_item(game, "ITEM_TEACHY_TV", 1)
    expect_item(game, "ITEM_POKE_BALL", 0)
    expect(game, [m[0] for m in game.state.party] == [names.value("SPECIES_MEWTWO"), names.value("SPECIES_KADABRA")], "l'ASPICOT du vieil homme n'est pas dans l'équipe")
