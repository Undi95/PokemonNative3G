# Build KANTO_DEBUG=1 : objets du debug, MEWTWO, DEBUG > Revanches PokéNav, téléport Route 102 (à côté de
# Calvin), CHERCHE VS : Calvin (revanche du PokéNav) répond « !! » et saute, Rick (pas de revanche, jamais
# combattu) « ! ». Puis on parle à Calvin : combat de revanche, et il cesse de sauter après.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp, give_mewtwo
from kanto_vs_seeker import use_vs_seeker
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
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 8, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    debug_warp(game, 22); log(game, "Route 102")
    use_vs_seeker(game, "VS", 1)
    game.wait(120); log(game, "réponses")
    game.tap("RIGHT", hold=16); game.wait(30); game.tap("RIGHT"); game.wait(20)
    game.tap("A"); game.wait(400); log(game, "Calvin")
    for _ in range(80):
        if game.state.free:
            break
        game.tap("A"); game.wait(60)
    wait_until(game, lambda s: s.free); game.wait(200); log(game, "après le combat")
