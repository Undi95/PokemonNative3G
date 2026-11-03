# Cartes des deux régions (2026-11-03, docs/A-TESTER.md : « Régions après homogénéisation », « Objet CARTE ») :
# la carte de Vol depuis l'équipe (VOL) et depuis le sac (POKé MONTURE), l'objet CARTE depuis le sac et enregistré sur
# SELECT ; à Kanto la carte de Kanto (RF, kanto_region_map.c), à Hoenn celle de Hoenn (Émeraude, region_map.c et
# field_region_map.c). Le choix se fait par Fusion_IsInKanto (CB2_OpenFlyMapOfRegion, ItemUseOutOfBattle_TownMap).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from menu_helpers import open_start_entry, pick, bag, texts
from poke_monture_moves import HM_FLAGS

# L'écran attendu (callback 2) dans chaque région : carte de Vol, carte de l'objet CARTE
SCREENS_BY_REGION = {
    "kanto": {"vol": "KantoCB2_OpenFlyMap", "carte": "CB2_RegionMap"},
    "hoenn": {"vol": "CB2_OpenFlyMap", "carte": "MCB2_FieldUpdateRegionMap"},
}
PLACES = {"kanto": ("PalletTown", 9, 12), "hoenn": ("LittlerootTown", 10, 10)}


def screens_since(game, frame):
    return [name for f, name in game.cb2s if f >= frame]


def leave(game):
    for _ in range(12):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free, limit=900)


def fly_from_party(game):
    open_start_entry(game, "POKéMON"); game.wait(90)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "VOL")


def key_item_from_bag(game, label):
    """Sac > Objets rares (2e poche avec SAC = KANTO) > label > UTILIS."""
    open_start_entry(game, "SAC"); game.wait(240)
    keys = [n for _, n, _ in bag(game)["poche 5"]]
    game.tap("LEFT", 3, gap=40); game.wait(30); game.tap("RIGHT"); game.wait(90)
    game.tap("UP", 10, gap=10); game.wait(20)
    index = next(i for i, n in enumerate(keys) if n.startswith(label))
    if index:
        game.tap("DOWN", index, gap=20); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "UTILIS.")


def town_map_on_select(game):
    game.tap("SELECT", hold=4)


WAYS = (("vol", "equipe", fly_from_party), ("vol", "sac", lambda game: key_item_from_bag(game, "POKé MONTURE")),
        ("carte", "sac", lambda game: key_item_from_bag(game, "CARTE")), ("carte", "SELECT", town_map_on_select))


def play(game):
    continue_game(game)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO (objets rares dans la 2e poche)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_DRAGONITE", 60)
    game.dev("joueur.capacite", 0, 0, names.number("MOVE_FLY"))
    game.item("ITEM_POKE_MONTURE", 1)
    game.item("ITEM_TOWN_MAP", 1)
    game.dev("joueur.enregistre", names.number("ITEM_TOWN_MAP"))
    for flag in HM_FLAGS:
        game.flag(flag, 1)
    for i in range(8):
        game.flag(f"FLAG_KANTO_BADGE0{i + 1}_GET", 1)
        game.flag(f"FLAG_BADGE0{i + 1}_GET", 1)

    for region in ("kanto", "hoenn"):
        for kind, way, open_map in WAYS:
            game.warp(*PLACES[region]); game.wait(40)
            start = game.frames
            open_map(game)
            game.wait(240)
            log(game, f"{region} {kind} {way}")
            seen = screens_since(game, start)
            wanted = SCREENS_BY_REGION[region][kind]
            other = SCREENS_BY_REGION["hoenn" if region == "kanto" else "kanto"][kind]
            expect(game, wanted in seen and other not in seen,
                   f"{region}, {kind} depuis {way} : {wanted} ({' > '.join(seen[-4:])})")
            leave(game)

    kanto_map_extras(game)


def kanto_map_extras(game):
    """Carte de Kanto (objet CARTE, curseur sur BOURG PALETTE, case 4,11 de sRegionMapSections_Kanto) : A sur le
    MONT SELENITE visité (case 9,3) = aperçu du donjon ; A sur le bouton en bas à droite (SWITCH_BUTTON_X/Y 21,11) =
    choix de la carte, puis les ÎLES 1-2-3."""
    game.flag("FLAG_KANTO_WORLD_MAP_MT_MOON_1F", 1)
    game.flag("FLAG_KANTO_SYS_SEVII_MAP_123", 1)       # le bouton de choix de la carte, et les îles
    game.flag("FLAG_KANTO_SYS_SEVII_MAP_4567", 1)
    game.warp(*PLACES["kanto"]); game.wait(40)
    town_map_on_select(game); game.wait(240)
    since = mark(game)
    game.tap("RIGHT", 5, gap=16); game.tap("UP", 8, gap=16); game.wait(40)
    said = " ".join(t for _, t in texts(game, since))
    expect(game, "SELENITE" in said, f"curseur sur le MONT SELENITE ({said[-80:]})")
    game.tap("A"); game.wait(240)
    log(game, "kanto apercu mont selenite")
    game.tap("B"); game.wait(150)
    log(game, "kanto apres apercu")
    game.tap("RIGHT", 12, gap=16); game.tap("DOWN", 8, gap=16); game.wait(40)
    game.tap("A"); game.wait(120)
    log(game, "kanto choix de la carte")
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(200)
    log(game, "kanto iles 1-2-3")
    game.tap("A"); game.wait(120)                     # le curseur reste sur le bouton
    game.tap("DOWN", 2, gap=20); game.wait(20); game.tap("A"); game.wait(200)
    log(game, "kanto iles 6-7")
    leave(game)
