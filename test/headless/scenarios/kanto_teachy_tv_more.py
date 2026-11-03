# Télé Pokémon de Rouge Feu, cas restants (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto », SAC = KANTO :
# - depuis le sac de RF, sans CT ni CS : quatre émissions seulement ;
# - B pendant une démonstration : retour au menu de la télé ;
# - TV ABC enregistrée sur SELECT : SELECT l'allume depuis la carte, SELECT la referme (comme RF) ;
# - avec une CT (six émissions) et le CHERCH'OBJET enregistré : l'émission 6 (enregistrer un objet) rend l'objet
#   enregistré du joueur.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from kanto_teachy_tv import EPISODES, in_menu
from menu_helpers import open_start_entry, pick, press_until_free, bag, texts

TEACHY_TV, ITEMFINDER = 366, 261


def key_item_menu(game, name):
    """Sac de RF > Objets rares > l'objet name : son menu (UTILIS., ENREG., SORTIR)."""
    open_start_entry(game, "SAC"); game.wait(240)
    game.tap("RIGHT", 2, gap=40); game.wait(60)
    game.tap("LEFT"); game.wait(90)                   # Objets rares, quelle que soit la poche retenue
    keys = [n for _, n, _ in bag(game)["poche 5"]]
    game.tap("UP", 10, gap=10); game.wait(30)
    index = next(i for i, n in enumerate(keys) if n.startswith(name))
    if index:
        game.tap("DOWN", index, gap=20); game.wait(30)
    since = mark(game)
    game.tap("A"); game.wait(60)
    return since


def wait_menu(game, limit=600):
    for _ in range(limit // 10):
        if in_menu(game):
            return True
        game.wait(10)
    return False


def play(game):
    continue_game(game)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    game.item("ITEM_TEACHY_TV", 1)
    game.item("ITEM_ITEMFINDER", 1)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.warp("PalletTown", 9, 12); game.wait(30)

    # Depuis le sac de RF, sans CT : quatre émissions
    since = key_item_menu(game, "TV ABC")
    pick(game, since, "UTILIS."); game.wait(300)
    wait_text(game, EPISODES[0], since)
    game.wait(60)
    log(game, "menu sans CT")
    shown = [t for _, t in texts(game, since)]

    # B pendant la démonstration de l'émission 1
    since = mark(game)
    game.tap("A")
    for _ in range(300):
        if any(w == 24 for _, w, _t in game.texts[since:]):
            break
        game.wait(4)
    game.wait(60)
    log(game, "demonstration")
    game.tap("B")
    back_after_b = wait_menu(game)
    log(game, "retour menu apres B")
    game.tap("B"); game.wait(240)                      # retour au sac
    tv_closed_to_bag = [name for _, name in game.cb2s[-3:]]
    press_until_free(game)

    # TV ABC enregistrée sur SELECT
    since = key_item_menu(game, "TV ABC")
    pick(game, since, "ENREG."); game.wait(60)
    press_until_free(game)
    registered_tv = bag(game)["select"]
    game.tap("SELECT"); game.wait(300)
    select_opened = wait_menu(game)
    log(game, "tv par SELECT")
    game.tap("SELECT"); game.wait(200)
    wait_until(game, lambda s: s.free, limit=900)
    select_closed = game.state.free

    # Une CT : six émissions ; CHERCH'OBJET enregistré, puis l'émission 6
    game.item("ITEM_TM39", 1)
    since = key_item_menu(game, "CHERCH")
    pick(game, since, "ENREG."); game.wait(60)
    press_until_free(game)
    before = bag(game)["select"]
    since = key_item_menu(game, "TV ABC")
    pick(game, since, "UTILIS."); game.wait(300)
    wait_text(game, EPISODES[5], since)
    game.wait(60)
    log(game, "menu avec CT")
    game.tap("DOWN", 5, gap=20); game.wait(30)
    since = mark(game)
    game.tap("A"); game.wait(60)
    for _ in range(600):
        if any(w == 3 and t == "ENREG." for _, w, t in game.texts[since:]) and in_menu(game):
            break
        game.tap("A"); game.wait(30)
    episode6 = in_menu(game)
    game.tap("B"); game.wait(240)
    press_until_free(game)
    after = bag(game)["select"]

    # Vérifications
    listed = " | ".join(shown)
    expect(game, all(e in listed for e in EPISODES[:4]) and not any(e in listed for e in EPISODES[4:]),
           f"sans CT ni CS : quatre émissions ({shown})")
    expect(game, back_after_b, "B pendant la démonstration : retour au menu de la télé")
    expect(game, registered_tv == TEACHY_TV and select_opened and select_closed,
           f"TV ABC par SELECT ({registered_tv}, allumée {select_opened}, refermée {select_closed})")
    expect(game, before == ITEMFINDER and episode6 and after == ITEMFINDER,
           f"objet enregistré rendu après l'émission 6 ({before} -> {after})")
    expect_item(game, "ITEM_TM39", 1)
