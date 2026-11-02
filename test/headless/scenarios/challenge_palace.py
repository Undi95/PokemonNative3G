# Défi : Palais de Combat : les Pokémon choisissent seuls leurs attaques. Le préposé, l'équipe, deux combats gagnés (test/headless/challenges.py) ; pas d'anomalie ni de
# plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    challenges.run(game, "BattleFrontier_BattlePalaceLobby", "SinglesAttendant", party=3, battles=2, level=50)
