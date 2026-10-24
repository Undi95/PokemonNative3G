# Build KANTO_DEBUG=1 : DEBUG « MEWTWO + KADABRA », objets du debug, CÂBLE LINK (sac d'Émeraude) sur KADABRA :
# évolution en ALAKAZAM comme après un échange.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, give_mewtwo
from redleaf_acro import close_menus
from driver import wait_until


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    game.tap("START"); game.wait(30); game.tap("DOWN", 2, gap=10); game.tap("A"); game.wait(200)
    game.tap("DOWN", 139, gap=4); game.wait(30); log(game, "câble")
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(200); log(game, "équipe")
    game.tap("DOWN"); game.wait(30); game.tap("A"); game.wait(240); log(game, "évolution")
    for k in range(14):
        game.tap("A"); game.wait(90)
    log(game, "fin")
