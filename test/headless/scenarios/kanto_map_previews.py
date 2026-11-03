# Aperçus des lieux de RF (docs/A-TESTER.md, 2026-11-03) : les 28 lieux de sMapPreviewScreenData
# (src/kanto_map_preview_screen.c). Pour chacun, le joueur se place sur l'entrée d'une carte voisine (autre section),
# puis le banc le fait entrer par cette entrée : l'aperçu s'affiche (grotte : Task_MapPreviewScreen_0 de
# fldeff_flash.c, image + nom puis transition ; forêt : Task_RunMapPreviewScreenForest, fondu sur la carte) avec le nom
# du lieu. Durée de RF (MapPreview_GetDuration) : 120 images à la première visite, 40 ensuite ; B passe l'aperçu d'une
# grotte. Aussi la CAVERNE ALTÉRÉE de l'Île 6 (section MAPSEC_ALTERING_CAVE_FRLG, corrigée le 2026-10-31) : lieu de
# capture et carte de Kanto.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import glob, json, os, re, sys
import driver
import maps
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from headless import REPO_DIR
from kanto_tour import log
from menu_helpers import texts, open_start_entry, pick
from region_maps import leave

OPTION_MENU_STYLE = 11
TASKS = {"MPS_TYPE_CAVE": "Task_MapPreviewScreen_0", "MPS_TYPE_FOREST": "Task_RunMapPreviewScreenForest"}


def previews():
    """[(mapsec, type, drapeau)] dans l'ordre de sMapPreviewScreenData."""
    with open(os.path.join(REPO_DIR, "src", "kanto_map_preview_screen.c"), encoding="utf-8") as f:
        source = f.read()
    table = source[source.index("sMapPreviewScreenData[MPS_COUNT]"):]
    return re.findall(r"\.mapsec = (\w+),\s*\.type = (\w+),\s*\.flagId = (\w+),", table)


def map_infos():
    infos = {}
    for path in glob.glob(os.path.join(REPO_DIR, "data", "maps", "*", "map.json")):
        with open(path, encoding="utf-8") as f:
            info = json.load(f)
        infos[info["id"]] = info
    return infos


def mapsec_number(mapsec):
    """Le numéro d'une section : sa place dans region_map_sections.json (l'en-tête des constantes en est généré)."""
    with open(os.path.join(REPO_DIR, "src", "data", "region_map", "region_map_sections.json"), encoding="utf-8") as f:
        return [section["id"] for section in json.load(f)["map_sections"]].index(mapsec)


def entrance(infos, mapsec):
    """(carte du lieu, x, y, carte voisine, x, y) : une entrée du lieu depuis une carte d'une autre section."""
    for info in sorted(infos.values(), key=lambda i: i["name"]):
        if info.get("region_map_section") != mapsec:
            continue
        for warp in info.get("warp_events") or []:
            outside = infos.get(warp["dest_map"])
            if outside is None or outside.get("region_map_section") == mapsec:
                continue
            # La case d'arrivée dehors : l'entrée de la carte voisine qui ramène ici
            back = outside["warp_events"][int(warp["dest_warp_id"])]
            return info["name"], warp["x"], warp["y"], outside["name"], back["x"], back["y"]
    raise KeyError(f"pas d'entrée pour {mapsec}")


def free(game):
    """Attend que le joueur soit libre (une scène d'arrivée éventuelle est lue jusqu'au bout)."""
    finish_dialog(game, limit=1500, settle=40)


def warp(game, name, x, y):
    group, num = maps.find_map(name)
    for _ in range(30):                 # libre pour le banc, mais un script de carte peut encore tourner
        try:
            return game.command("warp", group, num, x, y)
        except GameError as error:
            if "not free" not in str(error):
                raise
            free(game)
    game.command("warp", group, num, x, y)


def running(game, task):
    return any(game.function(t) == task for t in game.state.tasks)


def enter(game, place, task, shot=None, hold_b=False, walk=False):
    """Entre dans le lieu depuis la carte voisine : (images de l'aperçu, nom écrit). Avec walk, à pied par l'entrée
    (le jeu note alors la sortie de secours, la place du joueur sur la carte de Kanto quand il est sous terre)."""
    name, x, y, outside, ox, oy = place
    free(game)
    warp(game, outside, ox, oy)
    free(game)
    since = mark(game)
    if walk:
        grid = maps.load(outside)
        direction, (dx, dy) = next((d, v) for d, v in maps.DIRECTIONS.items() if grid.tile(ox - v[0], oy - v[1]) == ".")
        walk_to(game, ox - dx, oy - dy)
        game.press(direction, 30)
    else:
        warp(game, name, x, y)
    wait_until(game, lambda s: running(game, task), step=1, limit=400)
    start = game.frames
    if shot:
        game.wait(70)                   # grotte : fondu fini, image + nom ; forêt : nom sur la carte
        log(game, shot)
    while running(game, task):
        if game.frames - start > 900:
            raise GameError(f"aperçu sans fin : {game.describe()}")
        if hold_b:
            game.press("B", 2)
        else:
            game.wait(1)
    frames = game.frames - start
    written = [t for _, t in texts(game, since)]
    free(game)
    expect_map(game, name)
    return frames, written


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    infos = map_infos()
    table = previews()
    expect(game, len(table) == 28, f"28 lieux à aperçu ({len(table)})")

    # Chaque lieu à sa première visite (drapeau de carte remis à zéro) : aperçu de 120 images
    long_frames = {}
    for mapsec, kind, flag in table:
        place = entrance(infos, mapsec)
        game.flag(flag, 0)
        frames, written = enter(game, place, TASKS[kind], shot=mapsec[7:].lower())
        game.note(f"APERÇU {mapsec} ({kind[9:].lower()}) : {place[0]} depuis {place[3]}, {frames} images, "
                  f"nom {written}")
        expect(game, written != [], f"{mapsec} : nom du lieu écrit")
        long_frames[mapsec] = frames

    # Deuxième visite : 40 images au lieu de 120 (grotte : drapeau de la carte posé ; forêt : sHasVisitedMapBefore)
    for mapsec, kind in (("MAPSEC_MT_MOON", "MPS_TYPE_CAVE"), ("MAPSEC_VIRIDIAN_FOREST", "MPS_TYPE_FOREST")):
        frames, _ = enter(game, entrance(infos, mapsec), TASKS[kind])
        game.note(f"2e VISITE {mapsec} : {frames} images (1re : {long_frames[mapsec]})")
        expect(game, 70 <= long_frames[mapsec] - frames <= 90, f"{mapsec} : 80 images de moins à la 2e visite "
               f"({long_frames[mapsec]} → {frames})")

    # B passe l'aperçu d'une grotte dès la fin du fondu d'entrée
    short, _ = enter(game, entrance(infos, "MAPSEC_MT_MOON"), TASKS["MPS_TYPE_CAVE"])
    skipped, _ = enter(game, entrance(infos, "MAPSEC_MT_MOON"), TASKS["MPS_TYPE_CAVE"], hold_b=True)
    game.note(f"B : {skipped} images (sans B : {short})")
    expect(game, short - skipped >= 35, f"B passe l'aperçu ({short} → {skipped})")

    # CAVERNE ALTÉRÉE de l'Île 6 : lieu de capture de Kanto, joueur sur la carte de Kanto
    expect_map(game, "MtMoon_1F")
    enter(game, entrance(infos, "MAPSEC_ALTERING_CAVE_FRLG"), TASKS["MPS_TYPE_CAVE"], walk=True)
    game.give_mon("SPECIES_ZUBAT", 10)
    places = [int(n) for n in re.findall(r"lieu (\d+)", game.dev("joueur.equipe"))]
    expect(game, places[-1:] == [mapsec_number("MAPSEC_ALTERING_CAVE_FRLG")],
           f"lieu de capture : CAVERNE ALTÉRÉE de Kanto ({places})")

    # Sa fiche de RF (MENUS = KANTO) nomme le lieu
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    open_start_entry(game, "POKéMON"); game.wait(90)
    game.tap("DOWN", len(places) - 1, gap=20); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "RESUME"); game.wait(240)          # menu de l'équipe de RF
    log(game, "fiche-caverne-alteree")
    expect_text(game, "GROTTE METAMO", since)           # le nom de RF (CAVERNE ALTÉRÉE est celle de Hoenn)
    leave(game)

    # L'objet CARTE (SELECT) : la carte de Kanto, le joueur sur l'Île 6
    game.item("ITEM_TOWN_MAP", 1)
    game.dev("joueur.enregistre", names.number("ITEM_TOWN_MAP"))
    game.tap("SELECT", hold=4); game.wait(240)
    expect(game, game.function(game.state.cb2) == "CB2_RegionMap", f"carte de Kanto ({game.describe()})")
    log(game, "carte-caverne-alteree")
    leave(game)
