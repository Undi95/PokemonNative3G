# Pokédex de RF, pages d'habitat (docs/A-TESTER.md, 2026-11-03) : les 151 de Kanto vus et attrapés, habitat « Champs »
# (1er du sommaire), DROITE tourne les pages, GAUCHE revient ; chaque page a ses Pokémon (noms différents), la fiche
# s'ouvre depuis une page tournée. Captures « page-1 », « page-2 », « page-3 », « retour-2 », « fiche » à revoir.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, press_until_free

OPTION_POKEDEX = 10


def page(game, shot, button=None, number=None):
    """GAUCHE/DROITE déplacent le curseur entre les Pokémon de la page et tournent la page au bord (RF) : appuie
    jusqu'à « PAGE number/... »."""
    since = mark(game)
    for _ in range(6 if button else 0):
        game.tap(button); game.wait(60)
        if any(f"PAGE {number}/" in t for _, _, t in game.texts[since:]):
            break
    game.wait(60)
    game.shot(shot)
    return [" ".join(t.split()) for _, _, t in game.texts[since:] if t.strip()]


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEDEX_GET", 1)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    game.dev("jeu.pokedex", 151)
    game.dev("jeu.options", OPTION_POKEDEX, 1)
    open_start_entry(game, "POKéDEX"); game.wait(240)
    game.tap("DOWN"); game.wait(20)
    game.tap("A"); game.wait(240)                                       # habitat « Champs »
    first = page(game, "page-1")
    second = page(game, "page-2", "RIGHT", 2)
    third = page(game, "page-3", "RIGHT", 3)
    back = page(game, "retour-2", "LEFT", 2)
    game.note(f"PAGES {second} / {third} / {back}")
    since = mark(game)
    game.tap("A"); game.wait(240)
    game.shot("fiche")
    shown = " ".join(" ".join(t.split()) for _, _, t in game.texts[since:])
    press_until_free(game)

    expect(game, "PAGE 2/17" in second and "PAGE 3/17" in third and second[3:] != third[3:],
           f"pages 2 et 3 différentes ({second} / {third})")
    expect(game, "PAGE 2/17" in back and back[3:] == second[3:], f"GAUCHE revient à la page 2 ({back})")
    expect(game, "NIDOQUEEN" in shown and "HAUT." in shown, f"fiche du dernier de la page 2 ({shown[:80]})")
