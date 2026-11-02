# Défi : Tour Dresseur de l'Île 7 (RF). La case d'entrée devant l'accueil, l'équipe, les dresseurs du 1er étage
# battus, puis l'étage suivant (test/headless/challenges.py) ; pas d'anomalie ni de plantage.
from driver import *
import challenges

FIXTURE = "kanto"


def play(game):
    # L'entrée se fait par la case (9, 7) devant l'accueil ; les adversaires au niveau du plus fort de l'équipe
    challenges.run(game, "TrainerTower_Lobby", party=3, battles=1, level=50, trigger=(9, 7), walking=True,
                   reach="TrainerTower_2F", team=challenges.HILL_TEAM)
