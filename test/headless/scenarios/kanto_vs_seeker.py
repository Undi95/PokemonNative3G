# Build KANTO_DEBUG=1 : objets du debug, puis CHERCHE VS depuis le sac (Objets rares) à Bourg Palette :
# message de la batterie à recharger (ou pas de dresseur), sans plantage ; 100 pas puis nouvel essai.
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from redleaf_acro import close_menus
from driver import wait_until


def use_vs_seeker(game, tag, down):
    # le menu Start garde sa position (SAC après la 1re fois)
    game.tap("START"); game.wait(30); game.tap("DOWN", down, gap=10); game.wait(10); game.tap("A"); game.wait(200)
    if down:  # 1re fois ; ensuite le sac se rouvre sur le CHERCHE VS
        game.tap("RIGHT", 4, gap=40); game.wait(60)
        game.tap("UP", 60, gap=4); game.tap("DOWN", 42, gap=8)
    game.wait(30); log(game, tag + " : curseur")
    game.tap("A"); game.wait(60); game.tap("A"); game.wait(200); log(game, tag + " : utilisé")
    for _ in range(12):
        if game.state.free:
            break
        game.tap("A"); game.wait(60)
    wait_until(game, lambda s: s.free); log(game, tag + " : fini")


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    use_vs_seeker(game, "1", 1)
    for _ in range(25):
        game.tap("LEFT", hold=16, gap=2); game.tap("RIGHT", hold=16, gap=2)
    use_vs_seeker(game, "2", 0)
