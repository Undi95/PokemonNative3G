# Défi : Dôme de Combat, tournoi simple : le tableau, puis les matchs. Le préposé, l'équipe, deux combats gagnés (test/headless/challenges.py) ; pas d'anomalie ni de
# plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    # Un tour du tournoi est long (le tableau, les matchs des autres) : 250 000 images
    challenges.run(game, "BattleFrontier_BattleDomeLobby", "SinglesAttendant", party=3, battles=2, level=50,
                   frames=250000)
