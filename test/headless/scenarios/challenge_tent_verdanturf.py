# Défi : Tente de Combat de Vergazon (Palais, niveau 30). Le préposé, l'équipe, deux combats gagnés (test/headless/challenges.py) ; pas d'anomalie ni de
# plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    challenges.run(game, "VerdanturfTown_BattleTentLobby", "Attendant", party=3, battles=2, level=30)
