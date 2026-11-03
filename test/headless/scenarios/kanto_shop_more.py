# Boutiques de Rouge Feu (MENUS = KANTO, kanto_shop.c), cas restants (2026-11-03, docs/A-TESTER.md), sauvegarde
# « kanto » :
# - Argenta : achat de 3 POKé BALLS (quantité, prix, argent retiré, objets dans le sac) ;
# - Centre Commercial de Céladopole 2F, comptoir des CT : la liste des CT (fenêtre de la CT), achat d'une CT ;
# - Rosyères (Hoenn) : la boutique de RF aussi, achat d'une POTION.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import pick, press_until_free, bag, texts


def tasks(game):
    return " ".join(line for line in game.dev("jeu.etat").splitlines() if line.startswith("tache"))


def talk_to_clerk(game, place, x, y, what):
    game.warp(place, x, y); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("LEFT", 4); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(150)
    for _ in range(6):                                 # Hoenn : « Bienvenue ! ▼ » avant le menu
        if saw_text(game, "ACHETER", since):
            break
        game.tap("A"); game.wait(60)
    game.wait(30)
    log(game, f"{what} menu")
    pick(game, since, "ACHETER"); game.wait(300)
    log(game, f"{what} liste")


def buy(game, count=1, limit=12):
    """A sur l'objet visé, count au compteur, puis A jusqu'à ce que l'argent change ; message de fin refermé."""
    money = game.money()
    since = mark(game)
    game.tap("A")
    wait_text(game, "×01", since=since)                # le compteur, après « Combien en voulez-vous ? »
    game.wait(30)
    if count > 1:
        game.tap("UP", count - 1, gap=16); game.wait(20)
    for _ in range(limit):
        game.tap("A"); game.wait(50)
        if game.money() != money:
            break
    paid = money - game.money()
    for _ in range(6):                                 # « Voilà ! » : A jusqu'au retour à la liste (Task_BuyMenu)
        game.wait(40)
        if "Task_BuyMenu" in tasks(game):
            break
        game.tap("A")
    return paid


def leave_shop(game):
    game.tap("B"); game.wait(200)                      # liste -> menu
    press_until_free(game)


def play(game):
    continue_game(game)
    game.dev("jeu.options", 11, 1)                     # MENUS = KANTO
    game.money(10000)

    talk_to_clerk(game, "PewterCity_Mart", 4, 3, "argenta")
    balls = buy(game, 3)
    leave_shop(game)
    after_balls = bag(game)

    talk_to_clerk(game, "CeladonCity_DepartmentStore_2F", 3, 6, "celadopole CT")
    tm_list = [t for _, t in texts(game)[-30:]]
    tm_paid = buy(game, 1)
    leave_shop(game)
    after_tm = bag(game)

    talk_to_clerk(game, "OldaleTown_Mart", 3, 3, "rosyeres")
    potion_paid = buy(game, 1)
    leave_shop(game)
    after_potion = bag(game)

    # Vérifications
    balls_count = [q for n, _, q in after_balls["poche 2"] if n == names.number("ITEM_POKE_BALL")]
    expect(game, balls == 600 and balls_count == [3], f"3 POKé BALLS pour 600 ¥ ({balls} ¥, {after_balls['poche 2']})")
    expect(game, tm_paid > 0 and len(after_tm["poche 3"]) == 1, f"une CT achetée ({tm_paid} ¥, {after_tm['poche 3']})")
    potions = [q for n, _, q in after_potion["poche 1"] if n == names.number("ITEM_POTION")]
    expect(game, potion_paid == 300 and potions == [1], f"Hoenn : POTION achetée à la boutique de RF ({potion_paid} ¥, {potions})")
    expect(game, game.money() == 10000 - 600 - tm_paid - 300, f"argent ({game.money()})")
