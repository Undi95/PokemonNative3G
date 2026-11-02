# Dôme de Combat : le panneau du hall montre le tableau du tournoi précédent, même sans tournoi joué (sauvegarde de
# début de partie). Trouvé par l'explorateur le 2026-11-02 : le jeu plantait (0xc0000005) en ouvrant le tableau.
from driver import *

FIXTURE = "hoenn"
KANTO_START = 0


def play(game):
    continue_game(game)
    game.warp("BattleFrontier_BattleDomeLobby", 7, 11)      # sous le panneau (7, 10)
    since = mark(game)
    talk_to(game, "UP", finish=False)
    for _ in range(40):                 # le nom du tournoi, puis le tableau
        if "TourneyTree" in game.function(game.state.cb2):
            break
        game.tap("A", gap=20)
    game.wait(120)
    check_screen(game, "frontier_dome_tree-tableau")
    expect(game, "TourneyTree" in game.function(game.state.cb2), f"tableau du tournoi ouvert ({game.describe()})")
    game.tap("A")                       # la fiche du dresseur sous le curseur (le plantage)
    game.wait(120)
    check_screen(game, "frontier_dome_tree-fiche")
    for direction in ("DOWN", "UP", "RIGHT", "LEFT", "LEFT"):     # les fiches voisines (et les flèches)
        game.tap(direction)
        game.wait(60)
    game.tap("B")                       # le tableau (les flèches de la fiche vivent encore une image)
    game.wait(120)
    game.tap("RIGHT")                   # un match du tableau, et sa fiche
    game.wait(20)
    game.tap("A")
    game.wait(120)
    check_screen(game, "frontier_dome_tree-match")
    for direction in ("UP", "DOWN", "DOWN"):
        game.tap(direction)
        game.wait(60)
    game.tap("B")
    game.wait(120)
    game.tap("B")
    finish_dialog(game)
    expect_map(game, "BattleFrontier_BattleDomeLobby")
    expect_text(game, "TOURNOI", since)
