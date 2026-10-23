# Build KANTO_DEBUG=1 : MEWTWO, option SAC = KANTO, objets du debug, SUPER BONBON depuis le sac de RF :
# scène de RF (pokemon_special_anim : Pokémon, objet, « Le niveau de MEWTWO augmente ! »), puis le menu d'équipe.
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
    # Options > SAC = KANTO
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 5, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    # DEBUG > objets
    game.tap("START"); game.wait(30); game.tap("UP", 5, gap=10); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    # Sac de RF, poche Objets : SUPER BONBON
    game.tap("START"); game.wait(30); game.tap("DOWN", 2, gap=10); game.wait(10); game.tap("A"); game.wait(200)
    game.tap("UP", 3, gap=10); game.tap("DOWN", 44, gap=6); game.wait(30); log(game, "bonbon")
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(200); log(game, "équipe")
    game.tap("A"); game.wait(120); log(game, "scène")
    game.wait(240); log(game, "scène 2")
    for _ in range(8):
        game.tap("A"); game.wait(60)
    log(game, "fin")
