# Défi : Antre de Combat : trois portes par salle. Le préposé, l'équipe, un combat (test/headless/challenges.py) ; pas d'anomalie ni de plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    challenges.run(game, "BattleFrontier_BattlePikeLobby", "Attendant", party=3, battles=1, level=50, walking=True)
