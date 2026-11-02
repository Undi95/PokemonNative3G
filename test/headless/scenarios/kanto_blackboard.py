# Tableau noir de l'école de Jadielle : seule grille de choix (multichoicegrid) d'un script de Kanto.
# La grille passe par ScriptMenu_MultichoiceGrid d'Émeraude (code commun) : 3 colonnes, 2 lignes, choix et retour.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_text, wait_until
from kanto_tour import log


def press_until_text(game, words, since):
    """A jusqu'au message (les pages du texte précédent défilent)."""
    for _ in range(10):
        if saw_text(game, words, since):
            break
        game.wait(90); game.tap("A")
    wait_text(game, words, since)


def play(game):
    continue_game(game)
    game.warp("ViridianCity_School", 4, 2); game.wait(30)
    since = mark(game)
    game.tap("UP"); game.wait(10); game.tap("A")
    wait_text(game, "STATUT", since)
    press_until_text(game, "Lire quel sujet", since)
    game.wait(60); log(game, "grille")
    # Droite puis bas : 5e case (GEL), lue puis retour à la grille
    game.tap("RIGHT"); game.wait(10); game.tap("DOWN"); game.wait(10); log(game, "curseur")
    since_read = mark(game)
    game.tap("A")
    wait_text(game, "gelé", since_read)
    press_until_text(game, "Lire quel sujet", since_read)
    game.wait(60); log(game, "retour grille")
    # B ne ferme pas (ignoreBPress = FALSE : B annule, case 127) ; on sort
    game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free, limit=300)
    log(game, "fin")
    expect(game, game.state.free, "tableau refermé avec B")
