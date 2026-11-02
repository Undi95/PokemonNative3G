# Options > TITRE = R.FEU : Haut + SELECT + B sur l'écran titre de Rouge Feu ouvre l'écran d'effacement de RF
# (kanto_clear_save_data_screen.c, 2026-11-02) : question dans le cadre standard de RF, OUI / NON de RF (NON par
# défaut). NON : retour au jeu (redémarrage) avec la sauvegarde ; OUI : « Effacement des données… », sauvegarde vide.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, save, saw_text, wait_text
from kanto_tour import log

OPTION_TITLE_SCREEN = 7   # jeu.options (src/debug_tools.c)


def to_clear_screen(game):
    since = mark(game)
    game.press("A+B+START+SELECT", 2)
    game.wait(300); game.tap("START"); game.wait(200)      # intro passée, écran titre de RF
    game.press("UP+SELECT+B", 30)
    wait_text(game, "Effacer toutes les données", since, limit=600)
    game.wait(60)
    return since


def play(game):
    continue_game(game)
    game.dev("jeu.options", OPTION_TITLE_SCREEN, 1)
    save(game)

    to_clear_screen(game); log(game, "question")
    since_no = mark(game)
    game.tap("A")                                           # NON (curseur par défaut)
    game.wait(120)
    expect(game, not saw_text(game, "Effacement", since_no), "NON : rien n'est effacé")

    to_clear_screen(game)
    since_yes = mark(game)
    game.tap("UP"); game.wait(10); log(game, "oui")
    game.tap("A")
    wait_text(game, "Effacement des données", since_yes, limit=300)
    game.wait(30); log(game, "effacement")
    for _ in range(40):                                     # redémarrage : sans sauvegarde, NOUVELLE PARTIE seule
        if saw_text(game, "NOUVELLE PARTIE", since_yes):
            break
        game.tap("START"); game.wait(60)
    expect_text(game, "NOUVELLE PARTIE", since_yes)
    expect(game, not saw_text(game, "CONTINUER", since_yes), "sauvegarde effacée : pas de CONTINUER")
