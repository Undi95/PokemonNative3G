# Défi : Mont Combat : étages de dresseurs. Le préposé, l'équipe, un combat (test/headless/challenges.py) ; pas d'anomalie ni de plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    # L'entrée se fait par la case (9, 6) devant le comptoir, après la Ligue. Les étages sont générés en jeu
    # (carte.grille) avec des rebords à sauter ; l'escalier du 2e ne sert qu'après avoir battu les dresseurs
    challenges.run(game, "TrainerHill_Entrance", party=3, battles=1, level=50, trigger=(9, 6),
                   flags=["FLAG_SYS_GAME_CLEAR"], walking=True, reach="TrainerHill_2F", team=challenges.HILL_TEAM)
