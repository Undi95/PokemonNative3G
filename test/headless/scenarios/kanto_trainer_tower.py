# Build KANTO_DEBUG=1 : MEWTWO, DEBUG « TOUR DRESSEURS » (hall), défi SIMPLES (accueil), 1er étage,
# début du combat contre le dresseur (type Colline + aiguillage Tour : nom, classe, image, répliques).
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp, give_mewtwo
from driver import wait_until, walk_to, finish_dialog


class BattleStarted(Exception):
    pass


def battle_started(game):
    game.wait(400); log(game, "combat lancé")   # l'issue dépend du hasard (niveau 70 contre MEWTWO seul) : on s'arrête là
    raise BattleStarted


def play(game):
    try:
        run(game)
    except BattleStarted:
        pass


def run(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    give_mewtwo(game)
    debug_warp(game, 32); log(game, "hall")
    walk_to(game, 9, 7, on_battle=battle_started); log(game, "défi")
    walk_to(game, 9, 2, on_battle=battle_started); game.press("RIGHT", 20); wait_until(game, lambda s: s.free and s.map_name != "TrainerTower_Lobby"); log(game, "1er étage")
    game.wait(60)
    walk_to(game, 10, 12, on_battle=battle_started); log(game, "avant combat")
    game.press("DOWN", 4); game.wait(30)
    for _ in range(40):
        if game.state.battle:
            break
        game.tap("A", hold=2, gap=20)
    battle_started(game)
