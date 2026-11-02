# Défi : Tour de Combat, combats doubles (4 Pokémon). Le préposé, l'équipe, deux combats gagnés (test/headless/challenges.py) ; pas d'anomalie ni de
# plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    challenges.run(game, "BattleFrontier_BattleTowerLobby", "DoublesAttendant", party=4, battles=2, level=50)
