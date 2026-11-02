# Défi : Tente de Combat de Lavandia (Arène, niveau 30). Le préposé, l'équipe, deux combats gagnés (test/headless/challenges.py) ; pas d'anomalie ni de
# plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    challenges.run(game, "FallarborTown_BattleTentLobby", "Attendant", party=3, battles=2, level=30)
