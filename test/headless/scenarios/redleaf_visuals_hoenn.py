# Options > PERSO = Red/Leaf à Hoenn (v1.1, 2026-11-04) : le joueur en style Émeraude (sprites dessinés à la main,
# src/data/object_events/hoenn_player_red_leaf.h). RED puis LEAF, chacun à pied, en courant, sur les deux vélos (roue
# arrière, saut de côté), en surfant (la monture garde les couleurs de Brice), en pêchant, pendant COUPE, sous l'eau
# et avec l'oiseau du VOL. Captures « PERSO-étape » à revoir. L'arrosoir : redleaf_watering.py.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import json, os, re, sys
import driver
import maps
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, pick, press_until_free

OPTION_CHARACTER = 6
PERSOS = (("red", 1, 0), ("leaf", 1, 1), ("brice", 0, 0))   # BRICE : le joueur d'Émeraude, pour comparer
PLACE = "Route104"


def sprite(game):
    return int(re.search(r"sprite (\d+)", game.dev("joueur.avatar")).group(1))


def film(game, name, count, every):
    for i in range(count):
        game.shot(f"{name}-{i}"); game.wait(every)


def free_row(grid, length):
    """une case d'où l'on peut marcher `length` cases vers la droite"""
    return next((x, y) for y, row in enumerate(grid.tiles) for x in range(len(row) - length)
                if y > 3 and all(c == "." for c in row[x:x + length + 1]))


def water_column(grid, length):
    """une case d'eau d'où l'on peut surfer `length` cases vers le bas"""
    return next((x, y) for y in range(4, len(grid.tiles) - length) for x in range(4, len(grid.tiles[y]))
                if all(grid.tiles[y + k][x] == "~" for k in range(length + 1)))


def shore(grid):
    """une case de rive, l'eau juste en dessous (pêche)"""
    return next((x, y) for y in range(4, len(grid.tiles) - 2) for x in range(4, len(grid.tiles[y]))
                if grid.tiles[y][x] == "." and grid.tiles[y + 1][x] == "~" and grid.tiles[y + 2][x] == "~")


def cut_tree(place):
    path = os.path.join(os.path.dirname(driver.__file__), "..", "..", "data", "maps", place, "map.json")
    return next((o["x"], o["y"]) for o in json.load(open(path, encoding="utf-8"))["object_events"]
                if o["graphics_id"] == "OBJ_EVENT_GFX_CUTTABLE_TREE")


def underwater_spot():
    grid = maps.load("Underwater_Route124")
    return next((x, y) for y, row in enumerate(grid.tiles) for x, c in enumerate(row) if c == "." and y > 5 and x > 5)


def one(game, who, perso, gender):
    grid = maps.load(PLACE)
    game.dev("jeu.options", OPTION_CHARACTER, perso)
    game.dev("joueur.genre", gender)
    walk = free_row(grid, 8)
    game.warp(PLACE, *walk); game.wait(30)
    shown = sprite(game)
    game.shot(f"{who}-pied")
    game.press("RIGHT", 4); game.shot(f"{who}-marche"); game.wait(20)
    game.press("B+LEFT", 4); game.shot(f"{who}-course"); game.wait(30)

    # Vélos : COURSE (en roulant), CROSS (roue arrière, B maintenu, saut de côté)
    game.warp(PLACE, *walk); game.wait(30)
    game.dev("joueur.avatar", 1); game.wait(20)
    game.press("RIGHT", 6); game.shot(f"{who}-velo-course"); game.wait(30)
    game.warp(PLACE, *walk); game.wait(30)
    game.dev("joueur.avatar", 2); game.wait(20)
    game.shot(f"{who}-velo-cross")
    game.press("RIGHT", 6); game.shot(f"{who}-velo-cross-roule"); game.wait(30)
    game.press("B", 60); game.shot(f"{who}-roue-arriere"); game.wait(30)
    game.press("B+LEFT", 10); game.shot(f"{who}-saut-cote"); game.wait(30)
    game.press("B+UP", 10); game.shot(f"{who}-saut-dos"); game.wait(30)

    # Surf (la monture aux couleurs de Brice), pêche depuis la rive
    game.warp(PLACE, *water_column(grid, 6)); game.wait(30)
    game.dev("joueur.avatar", 3); game.wait(40)
    game.shot(f"{who}-surf")
    game.press("DOWN", 6); game.shot(f"{who}-surf-nage"); game.wait(40)
    game.press("LEFT", 2); game.shot(f"{who}-surf-cote"); game.wait(40)
    game.warp(PLACE, *shore(grid)); game.wait(30)
    game.press("DOWN", 1); game.wait(20)
    game.tap("SELECT"); game.wait(20)
    film(game, f"{who}-peche", 6, 15)
    press_until_free(game)

    # COUPE sur l'arbre de la Route 104 : la pose de capacité
    tx, ty = cut_tree(PLACE)
    game.warp(PLACE, tx, ty + 1); game.wait(30)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A")
    for _ in range(20):                                                  # « … COUPE. ▼ Voulez-vous… », puis OUI/NON
        game.wait(30)
        if any("OUI" in t for _, _, t in game.texts[since:]):
            break
        game.tap("A")
    game.wait(20); game.tap("A")                                         # OUI
    for _ in range(10):                                                  # le message fermé, la pose de capacité
        game.tap("A"); game.wait(16)
        if any("FieldMove" in game.function(t) or "ShowMon" in game.function(t) for t in game.state.tasks):
            break
    film(game, f"{who}-coupe", 16, 6)
    finish_dialog(game)

    # Sous l'eau (Route 124)
    game.warp("Underwater_Route124", *underwater_spot()); game.wait(60)
    game.shot(f"{who}-plongee")
    game.press("UP", 6); game.shot(f"{who}-plongee-nage"); game.wait(30)
    game.press("LEFT", 4); game.shot(f"{who}-plongee-cote"); game.wait(30)

    # VOL depuis Bourg-en-Vol (vers Bourg-en-Vol) : l'oiseau qui emporte le joueur
    game.warp("LittlerootTown", 10, 10); game.wait(30)
    open_start_entry(game, "POKéMON"); game.wait(90)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "VOL"); game.wait(240)
    game.tap("A")
    film(game, f"{who}-vol", 48, 6)
    wait_until(game, lambda s: s.free, limit=1500)
    return shown


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.dev("joueur.capacite", 0, 0, names.value("MOVE_CUT"))
    game.dev("joueur.capacite", 0, 1, names.value("MOVE_PSYCHIC"))
    game.dev("joueur.capacite", 0, 2, names.value("MOVE_FLY"))
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for badge in ("FLAG_BADGE01_GET", "FLAG_BADGE05_GET", "FLAG_BADGE06_GET"):
        game.flag(badge, 1)
    game.flag("FLAG_VISITED_LITTLEROOT_TOWN", 1)
    game.item("ITEM_OLD_ROD", 1)
    game.dev("joueur.enregistre", names.value("ITEM_OLD_ROD"))
    sprites = {who: one(game, who, perso, gender) for who, perso, gender in PERSOS}
    game.note(f"SPRITES {sprites}")
    # RED et LEAF gardent les graphicsId de BRICE et FLORA (le dessin suit Options > PERSO et la région)
    expect(game, sprites["red"] == names.value("OBJ_EVENT_GFX_BRENDAN_NORMAL")
           and sprites["leaf"] == names.value("OBJ_EVENT_GFX_MAY_NORMAL"), f"graphicsId garçon / fille ({sprites})")
