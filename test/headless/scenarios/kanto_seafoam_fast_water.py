# Courant rapide des Îles Écume (MB_FAST_WATER de RF, 2026-11-04), sauvegarde « kanto », courant de B3F actif :
# - face au courant (B3F, case 20,11 en dessous), A : « Le courant est trop fort. SURF ne peut pas être utilisé ici. »
#   (EventScript_CurrentTooFast de RF), pas de proposition de SURF. Avant, l'import en avait fait de l'eau de mer :
#   on y surfait sans arrêter le courant avec les rochers ;
# - SURF depuis l'équipe au même endroit : « Le courant est trop rapide! » (DisplayCantUseSurfMessage de RF) ;
# - SURF depuis l'équipe sur la Piste Cyclable (Route 17), loin de l'eau : « C'est parti pour une balade! ».
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, wait_text, wait_until
from menu_helpers import open_start_entry, pick, press_until_free


def surf_from_party(game, words):
    """Menu Start > POKéMON > le 1er > SURF : le message de l'équipe contient-il words ?"""
    open_start_entry(game, "POKéMON"); game.wait(120)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "SURF"); game.wait(60)
    seen = saw_text(game, words, since)
    game.tap("A"); game.wait(30)
    press_until_free(game)
    return seen


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("jeu.rencontres", 0)
    game.flag("FLAG_KANTO_BADGE05_GET", 1)                  # SURF à Kanto
    game.dev("joueur.capacite", 0, 0, names.number("MOVE_SURF"))
    game.flag("FLAG_KANTO_HIDE_SEAFOAM_B3F_BOULDER_1", 1)   # rochers encore à B2F : le courant de B3F coule
    game.flag("FLAG_KANTO_HIDE_SEAFOAM_B3F_BOULDER_2", 1)
    game.flag("FLAG_KANTO_STOPPED_SEAFOAM_B3F_CURRENT", 0)

    # A face au courant
    game.warp("SeafoamIslands_B3F", 20, 10); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("DOWN", 2); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(90)
    too_strong = saw_text(game, "courant est trop fort", since)
    surf_asked = saw_text(game, "utiliser SURF", since)
    finish_dialog(game); game.wait(30)
    still_on_foot = game.state.pos == (20, 10)

    # SURF depuis l'équipe, au même endroit, puis sur la Piste Cyclable
    too_fast = surf_from_party(game, "trop rapide")
    game.warp("Route17", 5, 40); game.wait(40)
    cycling = surf_from_party(game, "balade")

    game.note(f"A : trop fort {too_strong}, SURF proposé {surf_asked} ; équipe : trop rapide {too_fast}, "
              f"balade {cycling}")
    expect(game, too_strong and not surf_asked, "face au courant : « Le courant est trop fort », pas de SURF")
    expect(game, still_on_foot, f"le joueur reste à pied ({game.state.pos})")
    expect(game, too_fast, "SURF depuis l'équipe : « Le courant est trop rapide! »")
    expect(game, cycling, "Piste Cyclable : « C'est parti pour une balade! »")
