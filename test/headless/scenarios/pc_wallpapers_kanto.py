# PC > DÉPLACER POKéMON > titre de la boîte > FONDS > KANTO > KANTO 1 à 4 (docs/A-TESTER.md, 2026-11-03) : les 16 fonds
# de Rouge Feu (src/data/wallpapers.h, WALLPAPER_KANTO_FOREST à WALLPAPER_KANTO_SIMPLE), chacun posé sur la BOITE 1
# par le menu (captures : dessin, couleurs et titre de la boîte lisible), puis gardés par la sauvegarde (reset, CONTINUER).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from menu_helpers import pick, press_until_free

SETS = {"KANTO 1": ("FORET", "VILLE", "DESERT", "SAVANE"), "KANTO 2": ("ROCHERS", "VOLCAN", "NEIGE", "GROTTE"),
        "KANTO 3": ("PLAGE", "MER", "RIVIERE", "CIEL"), "KANTO 4": ("ETOILES", "CENTRE PKMN", "CARREAUX", "UNI")}
FIRST_KANTO_WALLPAPER = 17      # WALLPAPER_KANTO_FOREST, après les 17 fonds d'Émeraude


def wallpaper(game, box=0):
    line = game.dev("joueur.boites").splitlines()[1 + box]
    return int(re.search(r"fond (\d+)", line).group(1))


def open_boxes(game):
    """PC du Centre de Jadielle > PC de ??? > DÉPLACER POKéMON."""
    game.warp("ViridianCity_PokemonCenter_1F", 11, 2); game.wait(30)
    wait_until(game, lambda s: s.free)
    game.press("UP", 4); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(120); game.tap("A"); game.wait(90)
    for _ in range(6):
        game.tap("A"); game.wait(40)
        if saw_text(game, "DEPLACER OBJETS", since):
            break
    game.wait(30)
    pick(game, since, "DEPLACER POKéMON", first="RETIRER POKéMON"); game.wait(300)


def choose(game, set_name, name):
    """Le curseur sur le titre de la boîte : A > FONDS > KANTO > set_name > name."""
    since = mark(game)
    game.tap("A"); game.wait(60)
    for label in ("FONDS", "KANTO", set_name, name):
        menu = mark(game)                               # le menu suivant s'écrit pendant le A de pick
        pick(game, since, label); game.wait(60)
        since = menu
    game.wait(120)


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_PIKACHU", 20)
    before = wallpaper(game)
    open_boxes(game)
    game.tap("UP"); game.wait(30)                      # le curseur sur le titre de la boîte
    log(game, "boite")

    chosen = []
    for set_name, names_ in SETS.items():
        for name in names_:
            choose(game, set_name, name)
            chosen.append(wallpaper(game))
            log(game, name.lower().replace(" ", "_").replace("é", "e"))
    game.note(f"FONDS {chosen}")
    for _ in range(4):
        game.tap("B"); game.wait(120)
        if game.state.free:
            break
    press_until_free(game)

    # La sauvegarde, un reset, CONTINUER : la BOITE 1 garde le dernier fond
    save(game)
    game.press("A+B+START+SELECT", 1)
    game.wait(400)
    continue_game(game)
    after = wallpaper(game)

    # Vérifications
    expect(game, chosen == list(range(FIRST_KANTO_WALLPAPER, FIRST_KANTO_WALLPAPER + 16)),
           f"les 16 fonds de Rouge Feu dans l'ordre des menus ({chosen}, avant : {before})")
    expect(game, after == FIRST_KANTO_WALLPAPER + 15, f"fond SIMPLE de Kanto sauvegardé ({after})")
