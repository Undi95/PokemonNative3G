# Défi : Tente de Combat de Poivressel (Usine, Pokémon loués). Le préposé, l'équipe, deux combats gagnés (test/headless/challenges.py) ; pas d'anomalie ni de
# plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    challenges.run(game, "SlateportCity_BattleTentLobby", "Attendant", party=3, rentals=True, level=30)
