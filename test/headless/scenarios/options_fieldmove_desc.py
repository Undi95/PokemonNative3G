# Build KANTO_DEBUG=1 : menu d'équipe, curseur sur une capacité de terrain (TÉLÉPORT d'Abra) : avec MENUS = KANTO,
# la description de Rouge Feu s'affiche au-dessus du message (« Retour lieu de soins. ») ; avec MENUS = HOENN, rien
# (2026-10-31).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from redleaf_acro import close_menus
from driver import mark, saw_text, wait_until

DESCRIPTION = "Retour lieu de soins."


def cursor_on_teleport(game, shot):
    """Équipe > Abra > curseur sur TÉLÉPORT (2e action) ; rend vrai si la description a été écrite."""
    game.tap("A"); game.wait(90)        # POKéMON
    game.tap("A"); game.wait(40)        # Abra : menu des actions
    since = mark(game)
    game.tap("DOWN"); game.wait(30)     # RÉSUMÉ -> TÉLÉPORT
    log(game, shot)
    shown = saw_text(game, DESCRIPTION, since)
    game.tap("B"); game.wait(30); game.tap("B"); game.wait(90)
    close_menus(game)
    return shown


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.give_mon("SPECIES_ABRA", 10)
    game.flag("FLAG_SYS_POKEMON_GET", 1)   # POKéMON dans le menu Start
    # Menu Start : DEBUG, POKéMON, SAC, nom, SAUVER, OPTIONS, RETOUR (le curseur reste sur le dernier choix)
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10)
    hoenn = cursor_on_teleport(game, "MENUS HOENN")
    # Options > page 2 > MENUS = KANTO
    game.tap("START"); game.wait(30); game.tap("DOWN", 4, gap=10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 4, gap=10); game.wait(20); game.tap("RIGHT"); game.wait(60)
    game.tap("B"); game.wait(120)
    close_menus(game)
    game.tap("START"); game.wait(30); game.tap("UP", 4, gap=10); game.wait(10)
    kanto = cursor_on_teleport(game, "MENUS KANTO")

    # Vérifications
    expect(game, not hoenn, "MENUS = HOENN : pas de description")
    expect(game, kanto, f"MENUS = KANTO : description « {DESCRIPTION} »")
