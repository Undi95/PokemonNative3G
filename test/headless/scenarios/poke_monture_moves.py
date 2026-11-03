# POKé MONTURE, les capacités (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto », PIKACHU sans CS, les 7 capacités
# débloquées, badges des deux régions :
# - FORCE (Route Victoire de Kanto), ÉCLATE-ROC (Caverne Azurée), FLASH depuis le sac dans une grotte sombre
#   (Grotte), SURF puis CASCADE (Cap Falaise), VOL depuis le sac jusqu'au bout (atterrissage à Jadielle) ;
# - à Hoenn, COUPE (Route 104) avec le POKéMON de Hoenn (ABSOL) ;
# - sans le badge de COUPE de Kanto, l'arbre ne se coupe pas.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import json, os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from kanto_strength import try_push, BOULDERS
from menu_helpers import open_start_entry, pick, press_until_free, bag, texts

HM_FLAGS = ("FLAG_KANTO_GOT_HM01", "FLAG_KANTO_GOT_HM02", "FLAG_KANTO_GOT_HM03", "FLAG_KANTO_GOT_HM04",
            "FLAG_KANTO_GOT_HM05", "FLAG_KANTO_GOT_HM06", "FLAG_KANTO_HIDE_FOUR_ISLAND_ICEFALL_CAVE_1F_HM07")


def viridian_cut_tree():
    """L'arbre à couper de Jadielle (map.json)."""
    path = os.path.join(os.path.dirname(driver.__file__), "..", "..", "data", "maps", "ViridianCity", "map.json")
    return next((o["x"], o["y"]) for o in json.load(open(path, encoding="utf-8"))["object_events"]
                if o["graphics_id"] == "OBJ_EVENT_GFX_KANTO_CUT_TREE")


def joined(game, since):
    return " ".join(t for _, t in texts(game, since))


def interact(game, place, spot, face):
    """Face à l'obstacle, A, OUI à « Voulez-vous utiliser … ? », jusqu'au retour au jeu."""
    game.warp(place, *spot); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press(face, 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(40)
    finish_dialog(game)
    game.wait(30)
    return since


def monture_from_bag(game):
    """Sac > Objets rares (2e poche) > POKé MONTURE > UTILIS."""
    open_start_entry(game, "SAC"); game.wait(240)
    keys = [n for _, n, _ in bag(game)["poche 5"]]
    game.tap("LEFT", 3, gap=40); game.wait(30); game.tap("RIGHT"); game.wait(90)
    game.tap("UP", 10, gap=10); game.wait(20)
    index = next(i for i, n in enumerate(keys) if n.startswith("POKé MONTURE"))
    if index:
        game.tap("DOWN", index, gap=20); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "UTILIS."); game.wait(120)
    return since


def play(game):
    continue_game(game)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO (POKé MONTURE dans les Objets rares)
    game.give_mon("SPECIES_PIKACHU", 30)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.item("ITEM_POKE_MONTURE", 1)
    for flag in HM_FLAGS:
        game.flag(flag, 1)
    for i in range(8):
        game.flag(f"FLAG_KANTO_BADGE0{i + 1}_GET", 1)
        game.flag(f"FLAG_BADGE0{i + 1}_GET", 1)
    game.flag("FLAG_KANTO_WORLD_MAP_VIRIDIAN_CITY", 1)

    # FORCE
    asked, pushed = try_push(game, BOULDERS[0])
    # ÉCLATE-ROC
    since = interact(game, "CeruleanCave_1F", (8, 21), "LEFT")
    smash = joined(game, since)
    rock_gone = "en 7,21" not in game.dev("carte.objets")
    log(game, "eclate roc")
    # FLASH depuis le sac, dans la Grotte (sombre)
    game.warp("RockTunnel_1F", 17, 3); game.wait(60)
    dark = str(game.flag("FLAG_SYS_USE_FLASH")).strip()
    sounds = len(game.sounds)
    since = monture_from_bag(game)
    finish_dialog(game); game.wait(60)
    flash = (any(s == "SE_M_REFLECT" for _, s in game.sounds[sounds:]), str(game.flag("FLAG_SYS_USE_FLASH")).strip())
    log(game, "flash")
    # SURF puis CASCADE (Cap Falaise)
    since = interact(game, "TwoIsland_CapeBrink", (12, 35), "UP")
    surf = joined(game, since)
    for _ in range(12):
        if game.state.pos[1] <= 26:
            break
        game.press("UP", 16); game.wait(8)
    since = mark(game)
    game.tap("A"); game.wait(40)
    finish_dialog(game); game.wait(60)
    waterfall = (joined(game, since), game.state.pos)
    log(game, "cascade")
    # VOL depuis le sac, jusqu'à Jadielle
    game.warp("PalletTown", 9, 12); game.wait(40)
    since = monture_from_bag(game)
    game.wait(200)
    for _ in range(8):
        if saw_text(game, "JADIELLE", since):
            break
        game.tap("UP"); game.wait(40)
    log(game, "carte de vol")
    game.tap("A"); game.wait(60)
    finish_dialog(game)
    wait_until(game, lambda s: s.free and s.map_name == "ViridianCity", limit=1500)
    flew = game.state.map_name
    # COUPE à Hoenn
    since = interact(game, "Route104", (34, 22), "RIGHT")
    hoenn_cut = (joined(game, since), "en 35,22" not in game.dev("carte.objets"))
    log(game, "coupe hoenn")
    # Sans le badge de COUPE de Kanto (CASCADE, 2e badge) : l'arbre reste
    game.flag("FLAG_KANTO_BADGE02_GET", 0)
    tree = viridian_cut_tree()
    since = interact(game, "ViridianCity", (tree[0], tree[1] + 1), "UP")
    no_badge = (joined(game, since), f"en {tree[0]},{tree[1]}" in game.dev("carte.objets"))

    # Vérifications
    expect(game, asked and pushed, f"FORCE : proposée, rocher poussé ({asked}, {pushed})")
    expect(game, "ECLATE-ROC" in smash.replace("ÉCLATE", "ECLATE") and rock_gone, f"ÉCLATE-ROC : rocher brisé ({smash[-80:]})")
    # FLASH : comme Émeraude, le POKéMON se montre puis l'écran s'éclaire (SE_M_REFLECT), sans message
    expect(game, dark in ("0", "False") and flash[1] in ("1", "True") and flash[0], f"FLASH depuis le sac ({flash})")
    expect(game, "SURF" in surf and "CASCADE" in waterfall[0] and waterfall[1][1] < 23,
           f"SURF puis CASCADE : en haut de la cascade ({waterfall[1]} ; {waterfall[0][-80:]})")
    expect(game, flew == "ViridianCity", f"VOL : atterrissage à Jadielle ({flew})")
    expect(game, "ABSOL" in hoenn_cut[0] and hoenn_cut[1], f"Hoenn : ABSOL utilise COUPE ({hoenn_cut[0][-60:]})")
    expect(game, no_badge[1], f"sans le badge : l'arbre reste ({no_badge[0][-80:]})")
