# Specials de RF (scripts de Kanto), 1re série (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto » :
# - ascenseur du Centre Commercial de Céladopole : entré par le RC, fenêtre « Niveau: RC », curseur sur RC, 4ᵉ choisi,
#   l'ascenseur tremble, on sort au 5F ;
# - poubelles de l'arène de Carmin : les deux interrupteurs (VAR_TEMP_0 / VAR_TEMP_1 tirés à l'arrivée) ouvrent la porte ;
# - pension de la Route 5 : PIKACHU déposé, des pas, sauvegarde et redémarrage, il a grandi, repris contre de l'argent ;
# - records de taille : MAGICARPE (Route 12 : record, même taille, plus petit) et SCARABRUTE (Île 6, Chemin des Eaux).
# Chaque partie est isolée : une erreur est notée et la suite continue.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys, traceback
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, save, wait_until, wait_text, walk_to
from kanto_tour import log
from menu_helpers import pick, texts, printer_waits

RESULTS = {}


def part(name):
    def wrap(fn):
        def run(game):
            try:
                RESULTS[name] = fn(game)
            except Exception as e:
                RESULTS[name] = f"ERREUR {e}"
                game.note(f"ERREUR dans {name} : {traceback.format_exc()[-300:]}")
                for _ in range(20):
                    if game.state.free:
                        break
                    game.tap("B"); game.wait(30)
        return run
    return wrap


def joined(game, since):
    return " ".join(t for _, t in texts(game, since))


def talk(game, place, spot, face):
    game.warp(place, *spot); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press(face, 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(40)
    return since


def party(game):
    return [(int(a), int(b)) for a, b in re.findall(r"espece (\d+) N\.(\d+)", game.dev("joueur.equipe"))]


@part("ascenseur")
def elevator(game):
    game.warp("CeladonCity_DepartmentStore_1F", 6, 2); game.wait(40)
    game.press("UP", 16); game.wait(60)               # porte de l'ascenseur (6,1)
    wait_until(game, lambda s: s.free and s.map_name == "CeladonCity_DepartmentStore_Elevator", limit=600)
    game.warp("CeladonCity_DepartmentStore_Elevator", 0, 3); game.wait(20)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(200)
    log(game, "ascenseur etages")
    shown = joined(game, since)
    pick(game, since, "4ᵉ", cursor=4)                  # le curseur part de RC (5e entrée)
    sounds = len(game.sounds)
    for _ in range(40):
        if game.state.free:
            break
        game.wait(30)
    shook = [s for _, s in game.sounds[sounds:]]
    game.warp("CeladonCity_DepartmentStore_Elevator", 2, 4); game.wait(20)
    for _ in range(4):                                 # la porte (2,5) : une flèche vers le bas
        if game.state.map_name != "CeladonCity_DepartmentStore_Elevator":
            break
        game.press("DOWN", 16); game.wait(60)
    wait_until(game, lambda s: s.free and s.map_name != "CeladonCity_DepartmentStore_Elevator", limit=900)
    return shown, shook, game.state.map_name


@part("poubelles")
def trash_cans(game):
    game.warp("VermilionCity_Gym", 5, 16); game.wait(60)
    switches = (game.var("VAR_TEMP_0"), game.var("VAR_TEMP_1"))   # tirés à l'arrivée : plus de téléport ensuite
    said = []
    for can in switches:
        x, y = 1 + 2 * ((can - 1) % 5), 10 + 2 * ((can - 1) // 5)
        walk_to(game, x, y + 1)
        game.press("UP", 1); game.wait(20)
        since = mark(game)
        game.tap("A"); game.wait(40)
        finish_dialog(game)
        said.append(joined(game, since))
    log(game, "poubelles")
    return switches, said, str(game.flag("FLAG_KANTO_FOUND_BOTH_VERMILION_GYM_SWITCHES")).strip()


@part("pension")
def daycare(game):
    game.give_mon("SPECIES_ZIGZAGOON", 30)             # il faut deux POKéMON
    game.money(10000)
    before = party(game)
    since = talk(game, "Route5_PokemonDayCare", (4, 5), "UP")
    finish_dialog(game)
    deposited = (joined(game, since), party(game))
    game.warp("Route5", 20, 20); game.wait(40)
    for i in range(150):                               # des pas (1 point d'expérience chacun)
        game.press("UP" if i % 2 == 0 else "DOWN", 16); game.wait(4)
    save(game)
    game.press("A+B+START+SELECT", 1)
    continue_game(game)
    money = game.money()
    since = talk(game, "Route5_PokemonDayCare", (4, 5), "UP")
    finish_dialog(game)
    log(game, "pension reprise")
    return before, deposited, joined(game, since), party(game), money - game.money()


def show_magikarp(game, slot):
    since = talk(game, "Route12_FishingHouse", (4, 5), "UP")
    for _ in range(40):                                # A jusqu'au menu d'équipe, puis le MAGICARPE
        if "PartyMenu" in game.function(game.state.cb2):
            break
        game.tap("A"); game.wait(40)
    game.wait(120)
    game.tap("DOWN", slot, gap=20); game.wait(20); game.tap("A"); game.wait(60)
    finish_dialog(game)
    return joined(game, since)


@part("magicarpe")
def magikarp(game):
    # Kanto_CompareMonSize (CompareMonSize de RF, 2026-11-04) : le même MAGICARPE une 2e fois = « même taille » (4) ;
    # un plus petit que le record = « Rien à voir avec celui de {STR_VAR_3} cm » (le record)
    game.give_mon("SPECIES_MAGIKARP", 10)
    game.give_mon("SPECIES_MAGIKARP", 10)
    game.flag("FLAG_KANTO_GOT_SUPER_ROD", 1)
    a = len(party(game)) - 2
    first = show_magikarp(game, a)
    tie = show_magikarp(game, a)
    other = show_magikarp(game, a + 1)                 # plus grand (nouveau record) ou plus petit
    smaller = other if "Rien à voir" in other else show_magikarp(game, a)
    return first, tie, other, smaller


@part("scarabrute")
def heracross(game):
    game.give_mon("SPECIES_HERACROSS", 20)
    slot = len(party(game)) - 1
    since = talk(game, "SixIsland_WaterPath_House1", (3, 5), "UP")
    for _ in range(40):
        if "PartyMenu" in game.function(game.state.cb2):
            break
        game.tap("A"); game.wait(40)
    game.wait(120)
    game.tap("DOWN", slot, gap=20); game.wait(20); game.tap("A"); game.wait(60)
    finish_dialog(game)
    return joined(game, since)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 5)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for run in (elevator, trash_cans, daycare, magikarp, heracross):
        run(game)
    game.note("résultats : " + " | ".join(f"{k} = {str(v)[:200]}" for k, v in RESULTS.items()))

    # Vérifications
    shown, shook, floor = RESULTS["ascenseur"] if isinstance(RESULTS["ascenseur"], tuple) else ("", [], RESULTS["ascenseur"])
    expect(game, "Niveau" in shown and "RC" in shown and floor == "CeladonCity_DepartmentStore_5F",
           f"ascenseur : RC -> 4ᵉ, sortie au 5F ({floor} ; sons {shook[:6]})")
    r = RESULTS["poubelles"]
    expect(game, isinstance(r, tuple) and r[2] in ("1", "True"), f"poubelles : les deux interrupteurs ({r})")
    r = RESULTS["pension"]
    ok = isinstance(r, tuple)
    expect(game, ok and len(r[1][1]) == len(r[0]) - 1 and r[3][-1][0] == names.number("SPECIES_PIKACHU")
           and r[3][-1][1] > 5 and r[4] > 0, f"pension : déposé, sauvegarde, il a grandi, repris contre de l'argent ({r})")
    r = RESULTS["scarabrute"]
    expect(game, isinstance(r, str) and not r.startswith("ERREUR") and ("record" in r.lower() or "cm" in r),
           f"scarabrute : mesuré ({str(r)[-120:]})")
    r = RESULTS["magicarpe"]
    ok = isinstance(r, tuple)
    expect(game, ok and "Waouh" in r[0], f"magicarpe : 1er record ({str(r)[:160]})")
    expect(game, ok and "même taille" in r[1], f"magicarpe : le même une 2e fois, « même taille » ({str(r[1] if ok else r)[-120:]})")
    records = re.findall(r"Waouh! ?(\d+[,.]\d+) ?cm", " ".join(r[:3])) if ok else []
    small = re.search(r"celui de (\d+[,.]\d+) cm", r[3]) if ok else None
    expect(game, small is not None and records and small.group(1) == records[-1],
           f"magicarpe : plus petit, le record dans {{STR_VAR_3}} ({records}, {str(r[3] if ok else r)[-140:]})")
