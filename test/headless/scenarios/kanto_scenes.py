# Build KANTO_DEBUG=1 : MUSÉE ARGENTA (image du fossile d'Ptéra dans un cadre, avec le texte), puis LIGUE : OLGA
# (éclairage de la salle : les couleurs du sol changent en boucle).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    debug_warp(game, 30); log(game, "musée")
    game.tap("UP"); game.wait(30); game.tap("A"); game.wait(200); log(game, "fossile")
    game.tap("A"); game.wait(100); game.tap("A"); game.wait(100)
    wait_until(game, lambda s: s.free); log(game, "fermé")
    debug_warp(game, 31); log(game, "Olga")
    game.wait(400); log(game, "éclairage")
