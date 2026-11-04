# CORDE SORTIE à Kanto (UpdateEscapeWarp de RF, 2026-11-04), sauvegarde « kanto », SAC = KANTO :
# - le joueur entre dans le poste nord de la FORÊT DE JADE en marchant vers le bas (Route 2, porte en 5,13) ; la CORDE
#   SORTIE utilisée dans la forêt le ramène sur la case de la porte, pas sur celle d'en dessous (5,14 : le mur du poste,
#   ce que faisait le calcul d'Émeraude) ;
# - sorti de la forêt par son poste sud, puis revenu dans la forêt, la CORDE SORTIE le ramène toujours au même endroit :
#   la forêt ne pose pas de point de retour (RF l'exclut).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, live_map, wait_until
from menu_helpers import open_start_entry, pick, press_until_free
from kanto_item_use_scenes import bag_item_menu


def walk_into(game, place, spot, direction):
    """Sur spot, un pas vers direction : le joueur passe la porte."""
    game.warp(place, *spot); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press(direction, 48)
    wait_until(game, lambda s: s.map_name != place and s.free, limit=600)
    game.wait(30)


def escape_rope(game):
    """SAC > OBJETS > CORDE SORTIE > UTILIS., jusqu'au retour au jeu."""
    open_start_entry(game, "SAC"); game.wait(240)
    since = bag_item_menu(game, "CORDE SORTIE")
    pick(game, since, "UTILIS."); game.wait(60)
    finish_dialog(game)
    wait_until(game, lambda s: s.map_name != "ViridianForest" and s.free, limit=900)
    game.wait(30)
    state = game.state
    return state.map_name, state.pos


def play(game):
    continue_game(game)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    game.item("ITEM_ESCAPE_ROPE", 3)

    # Route 2 -> poste nord de la forêt, en descendant
    walk_into(game, "Route2", (5, 12), "DOWN")
    gate = game.state.map_name
    game.warp("ViridianForest", 5, 10); game.wait(40)
    first = escape_rope(game)
    cell = live_map(game).tile(*first[1])              # lettres de maps.py : '#' bloqué

    # forêt -> poste sud, puis retour dans la forêt : la corde ramène toujours à la Route 2
    walk_into(game, "ViridianForest", (29, 61), "DOWN")
    south_gate = game.state.map_name
    game.warp("ViridianForest", 5, 10); game.wait(40)
    second = escape_rope(game)

    game.note(f"poste nord {gate} ; corde : {first} (case {cell!r}) ; poste sud {south_gate} ; corde : {second}")
    expect(game, gate == "Route2_ViridianForest_NorthEntrance", f"porte du poste nord prise en descendant ({gate})")
    expect(game, first == ("Route2", (5, 13)), f"CORDE SORTIE : sur la porte du poste, Route 2 en 5,13 ({first})")
    expect(game, cell != "#", f"la case d'arrivée n'est pas bloquée ({cell!r})")
    expect(game, south_gate == "Route2_ViridianForest_SouthEntrance", f"poste sud pris ({south_gate})")
    expect(game, second == first, f"après le poste sud, la corde ramène toujours au même endroit ({second})")
