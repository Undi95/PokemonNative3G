# Options > PERSO = Red/Leaf, tous les visuels du joueur (docs/A-TESTER.md, 2026-11-03) : RED, LEAF puis BRICE (retour
# à Émeraude), chacun à pied, en courant, sur les deux vélos (roue arrière du VÉLO CROSS), en surfant, sous l'eau, en
# pêchant, pendant COUPE, avec le « ! » d'un dresseur qui le repère (Kanto) et la flèche de sortie d'une maison, sur sa
# carte de dresseur et de dos au début d'un combat (lancer de la Poké Ball). Captures « PERSO-étape » à revoir.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import maps
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, press_until_free
from poke_monture_moves import viridian_cut_tree

OPTION_CHARACTER = 6
PERSOS = (("red", 1, 0), ("leaf", 1, 1), ("brice", 0, 0))


def sprite(game):
    return int(re.search(r"sprite (\d+)", game.dev("joueur.avatar")).group(1))


def film(game, name, count, every):
    for i in range(count):
        game.shot(f"{name}-{i}"); game.wait(every)


def underwater_spot():
    grid = maps.load("Underwater_Route124")
    return next((x, y) for y, row in enumerate(grid.tiles) for x, c in enumerate(row) if c == "." and y > 5 and x > 5)


def one(game, who, perso, gender):
    game.dev("jeu.options", OPTION_CHARACTER, perso)
    game.dev("joueur.genre", gender)
    game.warp("PalletTown", 10, 9); game.wait(30)
    shown = sprite(game)
    game.shot(f"{who}-pied")
    game.press("LEFT", 5); game.shot(f"{who}-marche"); game.wait(20)
    game.press("B+LEFT", 5); game.shot(f"{who}-course"); game.wait(30)

    # Vélos : COURSE (en roulant), CROSS (roue arrière, B maintenu)
    game.dev("joueur.avatar", 1); game.wait(20)
    game.press("RIGHT", 6); game.shot(f"{who}-velo-course"); game.wait(30)
    game.warp("PalletTown", 10, 9); game.wait(30)
    game.dev("joueur.avatar", 2); game.wait(20)
    game.shot(f"{who}-velo-cross")
    game.press("RIGHT", 6); game.shot(f"{who}-velo-cross-roule"); game.wait(30)   # pédalage
    game.press("B", 60); game.shot(f"{who}-roue-arriere"); game.wait(30)
    game.press("B+LEFT", 10); game.shot(f"{who}-saut-cote"); game.wait(30)     # saut de côté en roue arrière

    # Surf (eau du sud de Bourg Palette), pêche depuis la rive
    game.warp("PalletTown", 8, 18); game.wait(30)
    game.dev("joueur.avatar", 3); game.wait(40)
    game.shot(f"{who}-surf")
    game.press("DOWN", 6); game.shot(f"{who}-surf-nage"); game.wait(40)
    game.warp("PalletTown", 8, 16); game.wait(30)
    game.press("DOWN", 1); game.wait(20)
    game.tap("SELECT"); game.wait(20)
    film(game, f"{who}-peche", 4, 15)
    press_until_free(game)

    # Sous l'eau (Route 124 de Hoenn)
    game.warp("Underwater_Route124", *underwater_spot()); game.wait(60)
    game.shot(f"{who}-plongee")
    game.press("UP", 6); game.shot(f"{who}-plongee-nage"); game.wait(30)

    # COUPE sur l'arbre de Jadielle : la pose de capacité
    tx, ty = viridian_cut_tree()
    game.warp("ViridianCity", tx, ty + 1); game.wait(30)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A")
    for _ in range(20):                                                  # « … COUPE. ▼ Voulez-vous… », puis OUI/NON
        game.wait(30)
        if any("OUI" in t for _, _, t in game.texts[since:]):
            break
        game.tap("A")
    game.wait(20); game.tap("A")                                         # OUI
    wait_text(game, "utilise COUPE", since)
    game.shot(f"{who}-reflet")                                           # le reflet du joueur dans l'eau, en dessous
    for _ in range(10):                                                  # le message fermé, la pose de capacité
        game.tap("A"); game.wait(16)
        if any("FieldMove" in game.function(t) or "ShowMon" in game.function(t) for t in game.state.tasks):
            break
    film(game, f"{who}-coupe", 16, 6)
    finish_dialog(game)

    # « ! » de Kent qui repère le joueur (Mt. Moon), puis le combat : le dos du joueur et son lancer
    game.flag(names.value("KANTO_TRAINER_FLAGS_START") + names.value("TRAINER_KANTO_BUG_CATCHER_KENT")
              - names.value("KANTO_TRAINERS_START"), 0)                  # Kent pas encore battu
    game.warp("MtMoon_1F", 7, 31); game.wait(30)
    game.press("UP", 16)
    film(game, f"{who}-exclamation", 6, 6)
    for _ in range(40):                                                   # sa réplique, puis le combat
        if game.state.battle:
            break
        game.tap("A"); game.wait(30)
    film(game, f"{who}-combat", 10, 20)
    for i in range(48):                                                  # « Un combat est lancé… » (A), puis le lancer
        if i % 6 == 0 and not game.state.free:
            game.tap("A")
        game.shot(f"{who}-lancer-{i}"); game.wait(8)
    fight_battle(game)
    finish_dialog(game)

    # « ! » de Deandre (Route 118, Hoenn), puis le combat
    game.flag(names.value("TRAINER_FLAGS_START") + names.value("TRAINER_ROSE_1"), 1)
    game.flag(names.value("TRAINER_FLAGS_START") + names.value("TRAINER_DEANDRE"), 0)
    game.warp("Route118", 6, 11); game.wait(30)
    game.press("RIGHT", 16)
    film(game, f"{who}-exclamation-hoenn", 6, 6)
    for _ in range(40):
        if game.state.battle:
            break
        game.tap("A"); game.wait(30)
    fight_battle(game)
    finish_dialog(game)

    # Flèche de sortie de la maison du joueur (sur le paillasson, face à la porte), à Kanto puis à Hoenn
    game.warp("PalletTown_PlayersHouse_1F", 4, 7); game.wait(30)
    game.press("DOWN", 1); game.wait(30)
    game.shot(f"{who}-fleche-sortie")
    game.warp("LittlerootTown_BrendansHouse_1F", 8, 7); game.wait(30)
    game.press("DOWN", 1); game.wait(30)
    game.shot(f"{who}-fleche-sortie-hoenn")

    # Carte de dresseur
    open_start_entry(game, "AAAAAAA"); game.wait(240)
    game.shot(f"{who}-carte")
    press_until_free(game)
    return shown


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.dev("joueur.capacite", 0, 0, names.value("MOVE_CUT"))
    game.dev("joueur.capacite", 0, 1, names.value("MOVE_PSYCHIC"))
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.flag("FLAG_KANTO_BADGE02_GET", 1)
    game.item("ITEM_OLD_ROD", 1)
    game.dev("joueur.enregistre", names.value("ITEM_OLD_ROD"))
    # RED et LEAF gardent les graphicsId de BRICE et FLORA (le dessin suit Options > PERSO) : on compare les captures
    sprites = {who: one(game, who, perso, gender) for who, perso, gender in PERSOS}
    game.note(f"SPRITES {sprites}")
    expect(game, sprites["red"] == sprites["brice"] != sprites["leaf"], f"graphicsId garçon / fille ({sprites})")
