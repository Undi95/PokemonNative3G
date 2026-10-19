# Build KANTO_DEBUG=1 : nouvelle partie à Bourg Palette, scène de CHEN, choix de CARAPUCE au labo
# (sans surnom), puis le premier combat contre le rival (TRAINER_BATTLE_EARLY_RIVAL).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import fight_battle, finish_dialog, wait_until, walk_to
from kanto_tour import log


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free)
    walk_to(game, 12, 2); game.tap("UP"); game.wait(20); game.tap("UP"); game.wait(60)
    finish_dialog(game); log(game, "labo")
    walk_to(game, 9, 5); game.tap("UP"); game.wait(20)
    # « Tu veux CARAPUCE ? » : OUI ; ensuite B partout (refuse le surnom)
    for _ in range(12):
        game.tap("A"); game.wait(50)
    for _ in range(300):
        if game.state.free:
            break
        game.tap("B"); game.wait(10)
    log(game, "starter choisi")
    walk_to(game, 6, 8, on_battle=fight_battle); log(game, "déclencheur")
    finish_dialog(game); log(game, "après le combat")
