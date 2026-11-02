# Terrain des métatuiles de Rouge Feu à Kanto (2026-11-02, tools/kanto_tile_attributes.py : bits 10-11 de l'attribut).
# - COUPE tond l'herbe de terrain « herbe » du carré de 3 × 3 autour du joueur, avec la table de RF
#   (SetCutGrassMetatileAt) : Route 11, l'herbe haute (0x00D -> 0x001) et les cimes d'arbre sur herbe en dessous
#   (0x00B -> 0x00E, 0x00C -> 0x00F). Avant : la Coupe d'Émeraude, qui ne tondait que l'herbe haute.
# - Face à l'eau (Surf, cannes) : RF regarde le terrain « eau » de la case (MetatileAtCoordsIsWaterTile). Sur la plage
#   de la Route 18, le rivage a le comportement « océan » mais pas le terrain « eau » : ni Surf ni pêche depuis la
#   plage (avant : Surf proposé). À Bourg Palette, l'eau du sud : Surf proposé.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, wait_until, mark, saw_text, wait_text
from kanto_tour import log

GRASS, MOWED = 0x00D, 0x001
TREE_TOPS = {0x00B: 0x00E, 0x00C: 0x00F}   # cimes larges gauche / droite sur herbe -> tondues


def metatiles(game, x, y):
    """Les métatuiles du carré de 3 × 3 autour de (x, y) : {(x, y): numéro}."""
    reply = game.dev("carte.metatuiles", x, y)
    return {(int(m.group(1)), int(m.group(2))): int(m.group(3), 16)
            for m in re.finditer(r"(-?\d+),(-?\d+) : metatuile 0x([0-9a-f]+)", reply)}


def facing_water_text(game, map_name, x, y, direction):
    """Se tourne vers l'eau et appuie sur A : le texte du Surf est-il venu ?"""
    game.warp(map_name, x, y); game.wait(30)
    game.press(direction, 2); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(120)
    log(game, map_name)
    seen = saw_text(game, "utiliser SURF", since)
    if seen:
        wait_text(game, "NON", since)
        game.wait(20); game.tap("B"); game.wait(60)   # NON
    wait_until(game, lambda s: s.free, limit=600)
    return seen


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)   # la sauvegarde « kanto » n'a pas d'équipe
    game.flag("FLAG_SYS_POKEMON_GET", 1)   # entrée POKéMON du menu Start (sous DEBUG)
    game.wait(30)
    game.dev("jeu.rencontres", 0)
    game.flag("FLAG_KANTO_BADGE02_GET", 1)   # COUPE à Kanto
    game.flag("FLAG_KANTO_BADGE05_GET", 1)   # SURF à Kanto
    game.dev("joueur.capacite", 0, 0, names.number("MOVE_CUT"))
    game.dev("joueur.capacite", 0, 1, names.number("MOVE_SURF"))

    # COUPE depuis l'équipe, au milieu de l'herbe haute de la Route 11
    game.warp("Route11", 41, 18); game.wait(30)
    before = metatiles(game, 41, 18)
    log(game, "route 11")
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("A"); game.wait(40); log(game, "sous-menu")
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(240)   # RESUME, COUPE, SURF…
    wait_until(game, lambda s: s.free, limit=900); game.wait(30)
    log(game, "herbe coupée")
    after = metatiles(game, 41, 18)

    no_surf = not facing_water_text(game, "Route18", 18, 7, "UP")
    surf = facing_water_text(game, "PalletTown", 7, 16, "DOWN")

    # Vérifications
    expected = {pos: MOWED if mid == GRASS else TREE_TOPS.get(mid, mid) for pos, mid in before.items()}
    expect(game, sorted(before.values()).count(GRASS) == 6 and all(before[(x, 19)] in TREE_TOPS for x in (40, 41, 42)),
           f"Route 11 : 6 herbes hautes et 3 cimes d'arbre sur herbe ({before})")
    expect(game, after == expected, f"herbe et cimes tondues comme dans RF ({after})")
    expect(game, no_surf, "Route 18 : pas de Surf depuis la plage (rivage sans terrain « eau »)")
    expect(game, surf, "Bourg Palette : Surf proposé face à l'eau")
