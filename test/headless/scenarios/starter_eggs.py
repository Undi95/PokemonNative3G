# Build KANTO_DEBUG=1 : DEBUG « Carte de vol » (Ligue de Kanto finie), téléport ÎLE 4, pension : l'assistant du
# PROF. CHEN donne les trois œufs des starters de Kanto (aucun attrapé), un par visite, puis plus rien.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo, debug_warp
from redleaf_acro import close_menus
from driver import wait_until, walk_to, talk_to, leave_map, finish_dialog


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 7, gap=10); game.tap("A")
    game.wait(240); game.tap("B"); game.wait(120); game.tap("B"); game.wait(120); close_menus(game)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("A"); game.wait(30)
    game.tap("DOWN", 16); game.tap("A"); game.wait(300)
    finish_dialog(game)  # scène de BLUE à l'arrivée
    log(game, "île 4")
    walk_to(game, 12, 14); leave_map(game, "UP"); log(game, "pension")
    walk_to(game, 9, 6)
    game.press("RIGHT", 1); game.wait(20); game.tap("A"); game.wait(40)
    for k in range(4):
        game.tap("A"); game.wait(40)
    log(game, "question")
    finish_dialog(game); log(game, "œuf 1")
    for k in range(2, 5):
        talk_to(game, "RIGHT"); game.wait(30); log(game, "visite %d" % k)
    game.tap("START"); game.wait(30); game.tap("DOWN", 1, gap=10); game.tap("A"); game.wait(120); log(game, "équipe")

    # Vérifications
    expect_party(game, "SPECIES_BULBASAUR")
    expect_party(game, "SPECIES_CHARMANDER")
    expect_party(game, "SPECIES_SQUIRTLE")
    expect_text(game, "C’était le dernier OEUF")
