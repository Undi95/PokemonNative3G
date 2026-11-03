# Obéissance selon les badges de la région où l'on se bat (2026-11-03, docs/A-TESTER.md ; IsMonDisobedient,
# OBEDIENCE_BADGE) : RATTATA N.60 échangé (dresseur d'origine changé), seule capacité TREMPETTE, 10 tours contre un
# Pokémon sauvage. À Kanto, paliers des badges de Kanto (2 = N.30, 4 = N.50, 6 = N.70, 8 = tous) ; à Hoenn, ceux de
# Hoenn. Désobéissance = des tours sans « RATTATA utilise TREMPETTE ».
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import wait_action_menu

TURNS = 10


def set_badges(game, kanto, hoenn):
    for i in range(8):
        game.flag(f"FLAG_KANTO_BADGE0{i + 1}_GET", int(i < kanto))
        game.flag(f"FLAG_BADGE0{i + 1}_GET", int(i < hoenn))


def obeyed_turns(game, place):
    """Combat sauvage dans l'herbe de place, TURNS tours de TREMPETTE, puis FUITE : tours où il a obéi."""
    game.warp(*place); game.wait(30)
    game.dev("jeu.hasard", 11)
    since = mark(game)
    steps = ("UP", "DOWN") if place[0] == "Route1" else ("RIGHT", "LEFT")
    for i in range(300):
        if game.state.battle:
            break
        game.press(steps[i % 2], 16); game.wait(2)
    obeyed = 0
    for turn in range(TURNS):
        wait_action_menu(game, since)              # le menu de ce tour (écrit après since)
        game.tap("A"); game.wait(20)               # ATTAQUE
        since = mark(game)
        game.tap("A"); game.wait(30)               # TREMPETTE
        for _ in range(60):
            if saw_text(game, "Que doit faire", since) or not game.state.battle:
                break
            game.tap("A"); game.wait(20)
        obeyed += saw_text(game, "RATTATA utilise", since)
    wait_action_menu(game, since)
    game.tap("RIGHT"); game.tap("DOWN"); game.tap("A"); game.wait(60)   # FUITE
    finish_dialog(game)
    return obeyed


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_RATTATA", 60)
    game.dev("joueur.capacite", 0, 0, names.number("MOVE_SPLASH"))
    for place in (1, 2, 3):
        game.dev("joueur.capacite", 0, place, 0)
    game.dev("joueur.dresseur", 0, 54321)           # échangé

    results = {}
    for label, kanto, hoenn, place in (("Kanto, 4 badges de Kanto", 4, 8, ("Route1", 12, 9)),
                                       ("Kanto, 6 badges de Kanto", 6, 0, ("Route1", 12, 9)),
                                       ("Hoenn, 0 badge de Hoenn", 8, 0, ("Route102", 8, 2)),
                                       ("Hoenn, 6 badges de Hoenn", 0, 6, ("Route102", 8, 2))):
        set_badges(game, kanto, hoenn)
        results[label] = obeyed_turns(game, place)
        game.note(f"{label} : {results[label]}/{TURNS} tours obéis")
    expect(game, results["Kanto, 4 badges de Kanto"] < TURNS, f"Kanto, 4 badges (N.50) : il désobéit parfois ({results})")
    expect(game, results["Kanto, 6 badges de Kanto"] == TURNS, f"Kanto, 6 badges (N.70) : il obéit ({results})")
    expect(game, results["Hoenn, 0 badge de Hoenn"] < TURNS, f"Hoenn sans badge de Hoenn : il désobéit ({results})")
    expect(game, results["Hoenn, 6 badges de Hoenn"] == TURNS, f"Hoenn, 6 badges de Hoenn : il obéit ({results})")
