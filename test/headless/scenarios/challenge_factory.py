# Défi : Usine de Combat : Pokémon loués (écran de location), puis échange. Le préposé, l'équipe, deux combats gagnés (test/headless/challenges.py) ; pas d'anomalie ni de
# plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    challenges.run(game, "BattleFrontier_BattleFactoryLobby", "SinglesAttendant", party=3, rentals=True, level=50)
