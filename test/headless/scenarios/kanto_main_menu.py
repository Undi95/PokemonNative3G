# Options > TITRE = R.FEU : après l'écran titre de Rouge Feu, le menu principal de Rouge Feu (kanto_main_menu.c, choix
# user 2026-11-02) : CONTINUER avec JOUEUR / DUREE JEU / POKéDEX / BADGES (de la région de la sauvegarde), NOUVELLE
# PARTIE, cadre de l'option FENETRE, fenêtre choisie éclairée (WIN0). B revient à l'écran titre ; CONTINUER reprend la
# partie ; NOUVELLE PARTIE ouvre le discours du Prof. Seko (celui du Prof. Chen est écarté : Kanto = post-game).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, save, saw_text, wait_text, wait_until
from kanto_tour import log

OPTION_TITLE_SCREEN = 7   # jeu.options (src/debug_tools.c)


def to_main_menu(game, since):
    """Du reset (ou de l'écran titre) au menu principal de RF."""
    for _ in range(40):
        if saw_text(game, "CONTINUER", since):
            break
        game.tap("START"); game.wait(60)
    else:
        raise GameError(f"pas de menu principal : {game.describe()}")
    game.wait(60)


def play(game):
    continue_game(game)
    game.dev("jeu.options", OPTION_TITLE_SCREEN, 1)
    save(game)
    map_name = game.state.map_name

    since = mark(game)
    game.press("A+B+START+SELECT", 2)
    to_main_menu(game, since)
    log(game, "menu")
    expect_text(game, "JOUEUR", since)
    expect_text(game, "BADGES", since)
    game.tap("DOWN"); game.wait(20); log(game, "nouvelle partie")
    game.tap("UP"); game.wait(20)

    # B : retour à l'écran titre (de RF), puis de nouveau le menu
    since_title = mark(game)
    game.tap("B"); game.wait(120)
    expect(game, not saw_text(game, "CONTINUER", since_title), "B : retour à l'écran titre")
    to_main_menu(game, since_title)

    # CONTINUER : la partie reprend là où elle a été sauvegardée
    game.tap("A")
    wait_until(game, lambda s: s.free, limit=900)
    expect(game, game.state.map_name == map_name, f"CONTINUER : retour à {map_name} ({game.state.map_name})")
    log(game, "partie")

    # NOUVELLE PARTIE : discours du Prof. Seko
    since_new = mark(game)
    game.press("A+B+START+SELECT", 2)
    to_main_menu(game, since_new)
    game.tap("DOWN"); game.wait(20); game.tap("A")
    for _ in range(60):
        if saw_text(game, "Bonjour", since_new):
            break
        game.tap("A", hold=4, gap=26)
    wait_text(game, "Bonjour", since_new)
    game.wait(60); log(game, "seko")
