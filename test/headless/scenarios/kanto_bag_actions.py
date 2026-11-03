# Sac de Rouge Feu (SAC = KANTO) depuis le menu Start, sauvegarde « kanto » (2026-11-03, docs/A-TESTER.md) :
# - SELECT déplace un objet (POTION posée à la ligne rouge, au-dessus de REPOUSSE, comme RF) ;
# - JETER : 2 ANTIDOTE jetés (quantité, OUI/NON, message) ;
# - ENREG. dans les Objets rares : le CHERCH'OBJET, puis SELECT sur la carte l'utilise ;
# - Options > TOUCHES = L/R : R et L changent de poche (le sac se rouvre sur les Objets rares) ;
# - Boîte à CT et Sac à Baies enregistrés : SELECT sur la carte les ouvre, SELECT les referme (comme RF).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, wait_until, wait_text
from kanto_tour import log
from menu_helpers import open_start_entry, pick, press_until_free, bag, texts

ITEMFINDER, TM_CASE, BERRY_POUCH = 261, 364, 365


def open_bag(game):
    open_start_entry(game, "SAC")
    game.wait(200)


def register_key_item(game, index):
    """Objets rares (le sac se rouvre sur la dernière poche) : l'objet à la place index, ENREG."""
    open_bag(game)
    game.tap("UP", 8, gap=12); game.wait(20)
    if index:
        game.tap("DOWN", index, gap=20); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "ENREG."); game.wait(60)
    press_until_free(game)


def select_opens(game, what):
    """SELECT sur la carte ouvre l'objet enregistré ; SELECT le referme."""
    since = len(game.cb2s)
    game.tap("SELECT"); game.wait(200)
    cb2 = " ".join(name for _, name in game.cb2s[since:])
    log(game, f"{what} par SELECT")
    game.tap("SELECT"); game.wait(120)
    wait_until(game, lambda s: s.free, limit=600)
    return cb2


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for item, count in (("ITEM_POTION", 5), ("ITEM_ANTIDOTE", 3), ("ITEM_REPEL", 2), ("ITEM_ITEMFINDER", 1),
                        ("ITEM_TM_CASE", 1), ("ITEM_BERRY_POUCH", 1), ("ITEM_TM01", 1), ("ITEM_ORAN_BERRY", 4)):
        game.item(item, count)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    game.warp("PalletTown", 9, 12); game.wait(30)

    # SELECT : POTION déplacée sous REPOUSSE
    open_bag(game)
    log(game, "sac")
    game.tap("SELECT"); game.wait(40)
    game.tap("DOWN", 2, gap=20); game.wait(20)
    log(game, "deplacer")
    game.tap("SELECT"); game.wait(60)
    moved = [name for _, name, _ in bag(game)["poche 1"]]

    # JETER : 2 ANTIDOTE (curseur sur la POTION, en 3e place)
    game.tap("UP", 2, gap=20); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "JETER"); game.wait(60)
    game.tap("UP"); game.wait(20)
    log(game, "jeter combien")
    game.tap("A"); game.wait(60)
    wait_text(game, "NON", since=since)
    game.tap("A"); game.wait(60)
    tossed = texts(game, since)
    game.tap("A"); game.wait(60)
    antidote = [qty for num, _, qty in bag(game)["poche 1"] if num == 14]
    press_until_free(game)

    # ENREG. : CHERCH'OBJET (3e des Objets rares, après la Boîte à CT et le Sac à Baies), utilisé par SELECT
    open_bag(game)
    game.tap("RIGHT"); game.wait(90)
    game.tap("DOWN", 2, gap=20); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "ENREG."); game.wait(60)
    registered_finder = bag(game)["select"]
    press_until_free(game)
    since = mark(game)
    game.tap("SELECT"); game.wait(240)
    finder_texts = texts(game, since)
    press_until_free(game, "A")

    # Options > TOUCHES = L/R : R et L changent de poche (GetLRKeysPressed de RF ; sinon seulement ◀▶)
    game.dev("jeu.options", 5, 1)
    open_bag(game)
    since = mark(game)
    game.tap("R"); game.wait(90)
    r_pocket = texts(game, since)
    since = mark(game)
    game.tap("L"); game.wait(90)
    l_pocket = texts(game, since)
    press_until_free(game)
    game.dev("jeu.options", 5, 0)

    # Boîte à CT puis Sac à Baies, enregistrés et ouverts par SELECT
    register_key_item(game, 0)
    registered_tm = bag(game)["select"]
    tm_cb2 = select_opens(game, "boite a CT")
    register_key_item(game, 1)
    registered_berry = bag(game)["select"]
    berry_cb2 = select_opens(game, "sac a baies")

    # Vérifications
    expect(game, moved == ["ANTIDOTE", "POTION", "REPOUSSE"],
           f"SELECT : POTION posée à la ligne rouge, au-dessus de REPOUSSE ({moved})")
    expect(game, antidote == [1], f"2 ANTIDOTE jetés sur 3 ({antidote} ; {tossed})")
    expect(game, registered_finder == ITEMFINDER, f"CHERCH'OBJET enregistré ({registered_finder})")
    expect(game, any("Pas de réaction" in t for _, t in finder_texts),
           f"SELECT utilise le CHERCH'OBJET ({finder_texts})")
    expect(game, registered_tm == TM_CASE and "TMCase" in tm_cb2, f"Boîte à CT par SELECT ({registered_tm}, {tm_cb2})")
    expect(game, registered_berry == BERRY_POUCH and "BerryPouch" in berry_cb2,
           f"Sac à Baies par SELECT ({registered_berry}, {berry_cb2})")
    expect(game, game.state.free, "retour sur la carte")
    expect(game, any(t == "POKé BALLS" for _, t in r_pocket) and any(t == "OBJ. RARES" for _, t in l_pocket),
           f"TOUCHES = L/R : R puis L changent de poche ({r_pocket[:2]}, {l_pocket[:2]})")
