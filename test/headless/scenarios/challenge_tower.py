# Défi de la Tour de Combat (Zone de Combat), simple, niveau 50 : le préposé, le choix de 3 Pokémon, deux combats
# gagnés (test/headless/challenges.py). Pas d'anomalie ni de plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    continue_game(game)
    challenges.give_team(game)
    game.dev("jeu.options", 3, 1)       # STYLE COMBAT : DEFINI
    played = challenges.play_challenge(game, "BattleFrontier_BattleTowerLobby", "SinglesAttendant", party=3,
                                       battles=2)
    expect(game, len([b for b in played if b["outcome"] == "WON"]) >= 2, f"2 combats gagnés ({played})")
