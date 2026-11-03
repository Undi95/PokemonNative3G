# PC objets de Rouge Feu (MENUS = KANTO, kanto_item_pc.c), cas restants (2026-11-03, docs/A-TESTER.md), sauvegarde
# « kanto » : 11 objets au PC (défilement, flèches), SELECT déplace un objet, DONNER un objet du PC à PIKACHU.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import pick, press_until_free, bag, texts

ITEMS = ("ITEM_ANTIDOTE", "ITEM_BURN_HEAL", "ITEM_ICE_HEAL", "ITEM_AWAKENING", "ITEM_PARALYZE_HEAL",
         "ITEM_FULL_RESTORE", "ITEM_MAX_POTION", "ITEM_HYPER_POTION", "ITEM_SUPER_POTION", "ITEM_REPEL")


def tasks(game):
    return " ".join(line for line in game.dev("jeu.etat").splitlines() if line.startswith("tache"))


def play(game):
    continue_game(game)
    game.dev("jeu.options", 11, 1)                     # MENUS = KANTO
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for item in ITEMS:
        game.dev("joueur.objetpc", names.number(item), 1)
    first = [n for _, n, _ in bag(game)["pc"]]

    # PC du joueur > OBJETS > RETIRER OBJET : le PC objets de RF
    game.warp("ViridianCity_PokemonCenter_1F", 11, 2); game.wait(30)
    wait_until(game, lambda s: s.free)
    game.press("UP", 4); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(120); game.tap("A"); game.wait(90)
    game.tap("DOWN"); game.wait(20); game.tap("A")
    for _ in range(10):
        game.tap("A"); game.wait(40)
        if saw_text(game, "BOITE LETTRE", since):
            break
    game.wait(30)
    since = mark(game)
    game.tap("A"); game.wait(60)                       # OBJETS
    pick(game, since, "RETIRER OBJET"); game.wait(300)
    log(game, "pc objets")

    # Défilement jusqu'en bas
    game.tap("DOWN", 11, gap=16); game.wait(60)
    log(game, "bas de la liste")

    # SELECT : la POTION (1re) posée plus bas
    game.tap("UP", 12, gap=10); game.wait(30)
    game.tap("SELECT"); game.wait(40)
    game.tap("DOWN", 3, gap=20); game.wait(30)
    log(game, "deplacer")
    game.tap("SELECT"); game.wait(60)
    moved = [n for _, n, _ in bag(game)["pc"]]

    # DONNER l'objet du haut à PIKACHU
    game.tap("UP", 12, gap=10); game.wait(30)
    top = moved[0]
    since = mark(game)
    game.tap("A"); game.wait(60)
    log(game, "menu objet")
    pick(game, since, "DONNER"); game.wait(240)
    game.tap("A"); game.wait(120)                      # PIKACHU
    for _ in range(8):
        if "Task_ItemPcMain" in tasks(game) or "ItemPc" in tasks(game):
            break
        game.tap("A"); game.wait(60)
    log(game, "donne")
    given = texts(game, since)
    held = re.search(r"objet (\d+)", game.dev("joueur.equipe")).group(1)
    after = [n for _, n, q in bag(game)["pc"]]
    for _ in range(4):
        game.tap("B"); game.wait(120)
    press_until_free(game)

    # Vérifications
    expect(game, len(first) == 11, f"11 objets au PC ({first})")
    expect(game, moved[:4] == first[1:3] + [first[0], first[3]],
           f"SELECT : POTION posée à la ligne rouge, au-dessus du 4e ({first[:5]} -> {moved[:5]})")
    expect(game, top == "ANTIDOTE" and held == str(names.number("ITEM_ANTIDOTE")) and top not in after,
           f"{top} donné à PIKACHU (objet {held} ; reste au PC {after})")
