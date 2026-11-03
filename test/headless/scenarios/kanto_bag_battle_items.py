# Sac de Rouge Feu (SAC = KANTO) en combat sauvage, sauvegarde « kanto » (2026-11-03, docs/A-TESTER.md) :
# POTION sur PIKACHU (UTILIS., choix du Pokémon, PV rendus, tour de l'adversaire), puis le Sac à Baies des Objets
# rares (OUVRIR) : BAIE ORAN sur PIKACHU ; enfin FUITE.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, wait_until, wait_text
from kanto_tour import log
from menu_helpers import wild_battle, wait_action_menu, pick, bag, texts


def open_battle_bag(game):
    game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(240)


def use_on_first_mon(game, since, what):
    """UTILIS. dans le menu de l'objet, puis le 1er Pokémon de l'équipe."""
    pick(game, since, "UTILIS."); game.wait(200)
    log(game, f"equipe {what}")
    game.tap("A"); game.wait(120)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("joueur.pv", 0, 10)
    game.item("ITEM_POTION", 5)
    game.item("ITEM_BERRY_POUCH", 1)
    game.item("ITEM_ORAN_BERRY", 4)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    wild_battle(game)
    wait_action_menu(game)

    # POTION
    open_battle_bag(game)
    log(game, "sac")
    since = mark(game)
    game.tap("A"); game.wait(60)
    use_on_first_mon(game, since, "potion")
    potion_texts = texts(game, since)
    wait_action_menu(game, since)

    # Sac à Baies (Objets rares)
    open_battle_bag(game)
    game.tap("RIGHT"); game.wait(90)
    game.tap("DOWN"); game.wait(30)                   # BOITE CT, puis SAC BAIES
    log(game, "objets rares")
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "OUVRIR"); game.wait(240)
    log(game, "sac a baies")
    since = mark(game)
    game.tap("A"); game.wait(60)
    use_on_first_mon(game, since, "baie")
    berry_texts = texts(game, since)
    wait_action_menu(game, since)
    items = bag(game)

    # FUITE
    game.tap("DOWN"); game.wait(10); game.tap("RIGHT"); game.wait(10); game.tap("A")
    for _ in range(40):
        if not game.state.battle:
            break
        game.tap("A"); game.wait(40)
    wait_until(game, lambda s: s.free, limit=900)

    # Vérifications
    potions = [qty for num, _, qty in items["poche 1"] if num == 13]
    orans = [qty for num, _, qty in items["poche 4"] if num == 139]
    expect(game, potions == [4], f"une POTION utilisée ({potions} ; {potion_texts})")
    expect(game, any("PIKACHU" in t and "20" in t for _, t in potion_texts), f"PIKACHU récupère 20 PV ({potion_texts})")
    expect(game, orans == [3], f"une BAIE ORAN utilisée ({orans} ; {berry_texts})")
    expect(game, any("PIKACHU" in t and "10" in t for _, t in berry_texts), f"PIKACHU récupère 10 PV ({berry_texts})")
    expect_battle(game, outcome="RAN")
