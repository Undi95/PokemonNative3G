# Défi : concours Pokémon de Nénucrique, rang Normal, catégorie Sang-froid. L'hôtesse, un Pokémon inscrit, la salle
# du concours (présentation, cinq tours d'appels, résultats), puis le retour au hall (test/headless/challenges.py) ;
# pas d'anomalie ni de plantage.
from driver import *
import challenges

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    # Le concours n'a pas de combat : la preuve, c'est le passage par la salle de la catégorie (Sang-froid : la
    # première du menu) et le retour au hall
    challenges.run(game, "LilycoveCity_ContestLobby", "_EventScript_ContestReceptionist", party=1, battles=0,
                   level=50, reach=("ContestHallCool", "LilycoveCity_ContestLobby"))
