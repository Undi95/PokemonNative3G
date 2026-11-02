# Carte Dresseur de Kanto = celle de RF : photo du Casino de Céladopole (icônes de l'équipe au dos), autocollant de
# l'homme de l'Île 4 (Panthéon), étoiles de RF (Panthéon, Pokédex de Kanto, Pokédex national, baies et sauts).
# Avant le 2026-11-02, la carte de Kanto prenait les données d'Émeraude : ni photo ni autocollant, étoiles d'Émeraude.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
sys.path.insert(0, os.path.dirname(driver.__file__))
from driver import continue_game, finish_dialog, mark, saw_text, wait_text, wait_until
from kanto_tour import log
from redleaf_acro import close_menus
from matrix import MENU_PLAYER, open_start_entry
import names


def press_until_text(game, words, since):
    """A jusqu'au message (les pages du texte précédent défilent)."""
    for _ in range(12):
        if saw_text(game, words, since):
            break
        game.wait(60); game.tap("A")
    wait_text(game, words, since)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.give_mon("SPECIES_SNORLAX", 30)
    game.money(1000)
    game.wait(30)

    # Sans Panthéon : 0 étoile, carte bleue de RF ; au dos, ni photo ni autocollant
    open_start_entry(game, MENU_PLAYER)
    game.wait(150); log(game, "carte sans etoile")
    game.tap("B"); game.wait(90)
    close_menus(game)                       # la carte fermée, le menu Start revient

    # 3 entrées au Panthéon (autocollant le plus bas), la première à 12:34:56 : 1 étoile, carte verte de RF
    game.dev("jeu.stat", names.number("GAME_STAT_ENTERED_HOF"), 3)
    game.dev("jeu.stat", names.number("GAME_STAT_FIRST_HOF_PLAY_TIME"), (12 << 16) | (34 << 8) | 56)

    # Casino de Céladopole : l'imprimante photo (50 $), impression normale
    game.warp("CeladonCity_GameCorner", 16, 13); game.wait(30)
    since = mark(game)
    game.tap("RIGHT"); game.wait(10); game.tap("A")
    wait_text(game, "IMPRIMANTE", since)
    press_until_text(game, "Veuillez choisir", since)   # les pages, puis OUI ; ensuite le choix de l'impression
    wait_text(game, "SEPIA", since)
    game.wait(30); log(game, "impression")
    game.tap("A")
    finish_dialog(game)
    expect(game, game.var("VAR_KANTO_TRAINER_CARD_MON_ICON_1") != 0, "photo : icône du 1er Pokémon")

    # Île 4 : l'homme aux autocollants, Panthéon
    game.warp("FourIsland_House2", 4, 5); game.wait(30)
    since_man = mark(game)
    game.tap("UP"); game.wait(10); game.tap("A")
    wait_text(game, "STICKERS", since_man)
    press_until_text(game, "Oh, excellent", since_man)
    press_until_text(game, "QUITTER", since_man)   # les 7 pages, puis le choix PANTHEON / QUITTER
    game.wait(30); log(game, "vantardise")
    game.tap("A")                          # PANTHEON
    finish_dialog(game)
    expect(game, game.var("VAR_KANTO_HOF_BRAG_STATE") != 0, "autocollant du Panthéon")

    # La carte de Kanto : face, puis dos (icônes de la photo, autocollant)
    open_start_entry(game, MENU_PLAYER)
    game.wait(150); log(game, "carte")
    game.tap("A"); game.wait(90); log(game, "dos")
    expect_text(game, "12:34:56")
    game.tap("A"); game.wait(90)            # au dos, A ferme la carte (B la retourne)
    close_menus(game)
