# Scènes de Rouge Feu quand on utilise un objet sur un Pokémon hors combat (SAC = KANTO, kanto_pokemon_special_anim*.c,
# 2026-11-03, docs/A-TESTER.md), sauvegarde « kanto », PIKACHU N.20 à 10 PV :
# - POTION : scène, PV rendus ; HUILE : choix de la capacité, puis scène, PP rendus ;
# - CT24 (TONNERRE) sur la 4e place vide : scène ; CT34 (ONDE DE CHOC) avec 4 capacités : oubli de MIMI-QUEUE
#   (écran de la capacité à oublier), puis scène « 1, 2 et… Tadaa ! » ;
# - ANTIDOTE sans effet : message, pas de scène ; PIERRE FOUDRE : scène, puis évolution en RAICHU.
# La scène est l'écran CB2_PSA.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import open_start_entry, pick, press_until_free, bag, texts

THUNDER_SHOCK, QUICK_ATTACK, TAIL_WHIP, THUNDERBOLT, SHOCK_WAVE = 84, 98, 39, 85, 351


def tasks(game):
    return " ".join(line for line in game.dev("jeu.etat").splitlines() if line.startswith("tache"))


def until_task(game, name, limit=60, button="A"):
    """button jusqu'à ce que la tâche name tourne (retour au sac, à la Boîte à CT…)."""
    for _ in range(limit):
        if name in tasks(game):
            return True
        game.tap(button); game.wait(40)
    return False


def wait_task(game, name, limit=60):
    """Attend (sans appuyer) que la tâche name tourne."""
    for _ in range(limit):
        if name in tasks(game):
            game.wait(20)
            return True
        game.wait(10)
    return False


def moves(game):
    line = next(l for l in game.dev("joueur.equipe").splitlines() if "capacites" in l)
    return [tuple(int(x) for x in m.split("/")) for m in line.split()[1:]]


def first_mon(game):
    line = game.dev("joueur.equipe").splitlines()[0]
    species, hp = re.search(r"espece (\d+) .* PV (\d+)/", line).groups()
    return int(species), int(hp)


def bag_item_menu(game, name):
    """Sac de RF, poche OBJETS : l'objet name, son menu."""
    game.tap("LEFT", 3, gap=40); game.wait(60)
    names = [n for _, n, _ in bag(game)["poche 1"]]
    game.tap("UP", 12, gap=10); game.wait(30)
    index = names.index(name)
    if index:
        game.tap("DOWN", index, gap=20); game.wait(30)
    since = mark(game)
    game.tap("A"); game.wait(60)
    return since


def use_from_bag(game, name, what):
    """UTILIS., puis le 1er Pokémon de l'équipe : les écrans et textes jusqu'au retour au sac."""
    screens = len(game.cb2s)
    since = bag_item_menu(game, name)
    pick(game, since, "UTILIS."); game.wait(200)
    game.tap("A"); game.wait(90)
    log(game, what)
    return screens, since


def play(game):
    continue_game(game)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("joueur.pv", 0, 10)
    for slot, move, pp in ((0, THUNDER_SHOCK, 5), (1, QUICK_ATTACK, -1), (2, TAIL_WHIP, -1), (3, 0, -1)):
        game.dev("joueur.capacite", 0, slot, move, pp)
    for item, count in (("ITEM_POTION", 2), ("ITEM_ETHER", 1), ("ITEM_ANTIDOTE", 1), ("ITEM_THUNDER_STONE", 1),
                        ("ITEM_TM24", 1), ("ITEM_TM34", 1)):
        game.item(item, count)
    game.warp("PalletTown", 9, 12); game.wait(30)
    open_start_entry(game, "SAC"); game.wait(240)

    # POTION
    screens, since = use_from_bag(game, "POTION", "potion scene")
    until_task(game, "Task_BagMenu_HandleInput")
    potion = (["CB2_PSA" in n for _, n in game.cb2s[screens:]].count(True), first_mon(game)[1], texts(game, since))

    # HUILE : la capacité, puis la scène
    screens, since = use_from_bag(game, "HUILE", "huile capacite")
    game.tap("A"); game.wait(120)                      # ÉCLAIR (1re)
    log(game, "huile scene")
    until_task(game, "Task_BagMenu_HandleInput")
    ether = (["CB2_PSA" in n for _, n in game.cb2s[screens:]].count(True), moves(game)[0], texts(game, since))

    # ANTIDOTE sans effet
    screens, since = use_from_bag(game, "ANTIDOTE", "antidote")
    until_task(game, "Task_BagMenu_HandleInput")
    antidote = (["CB2_PSA" in n for _, n in game.cb2s[screens:]].count(True), texts(game, since))

    # CT24 sur la place vide, depuis la Boîte à CT (Objets rares)
    game.tap("RIGHT"); game.wait(90)
    game.tap("UP", 6, gap=10); game.wait(30)
    since = mark(game)
    game.tap("A"); game.wait(60)                       # BOITE CT : OUVRIR
    pick(game, since, "OUVRIR")
    wait_task(game, "Task_HandleListInput")
    screens = len(game.cb2s)
    since = mark(game)
    game.tap("UP", 6, gap=10); game.wait(30)
    game.tap("A"); game.wait(60)
    pick(game, since, "UTILIS."); game.wait(120)
    until_task(game, "PartyMenu", limit=8)
    game.wait(60)
    game.tap("A"); game.wait(120)
    log(game, "CT place vide")
    until_task(game, "Task_HandleListInput")
    tm_free = (["CB2_PSA" in n for _, n in game.cb2s[screens:]].count(True), moves(game), texts(game, since))

    # CT34 avec 4 capacités : oublier MIMI-QUEUE (3e)
    screens = len(game.cb2s)
    since = mark(game)
    game.tap("UP", 6, gap=10); game.wait(30)
    game.tap("A"); game.wait(60)
    pick(game, since, "UTILIS."); game.wait(120)
    until_task(game, "PartyMenu", limit=8)
    game.wait(60)
    game.tap("A"); game.wait(120)
    for _ in range(20):                                # « … oublier une capacité ? » OUI, puis l'écran du résumé
        if any("Summary" in n for _, n in game.cb2s[screens:]):
            break
        game.tap("A"); game.wait(60)
    game.wait(120)
    game.tap("DOWN", 2, gap=30); game.wait(30)
    log(game, "CT oublier")
    game.tap("A"); game.wait(120)
    tadaa = False
    for _ in range(40):
        tadaa = tadaa or saw_text(game, "Tadaa", since)
        if tadaa and "CB2_PSA" in game.function(game.state.cb2):
            break
        game.tap("A"); game.wait(40)
    log(game, "CT tadaa")
    until_task(game, "Task_HandleListInput")
    tm_replace = (["CB2_PSA" in n for _, n in game.cb2s[screens:]].count(True), moves(game), texts(game, since))
    game.tap("B"); game.wait(240)                      # retour au sac

    # PIERRE FOUDRE : scène puis évolution (A seulement : B l'annulerait)
    game.tap("LEFT"); game.wait(90)
    screens, since = use_from_bag(game, "PIERREFOUDRE", "pierre scene")
    for _ in range(60):
        if any("Evolution" in n or "EvoScene" in n for _, n in game.cb2s[screens:]):
            break
        game.tap("A"); game.wait(40)
    game.wait(300)
    log(game, "evolution")
    until_task(game, "Task_BagMenu_HandleInput", limit=120)
    stone = (["CB2_PSA" in n for _, n in game.cb2s[screens:]].count(True), first_mon(game)[0])
    press_until_free(game)

    # Vérifications
    expect(game, potion[0] and potion[1] == 30, f"POTION : scène et 30 PV ({potion[:2]})")
    expect(game, ether[0] and ether[1] == (THUNDER_SHOCK, 15), f"HUILE : scène et 15 PP à ÉCLAIR ({ether[:2]})")
    expect(game, not antidote[0] and any("aucun effet" in t for _, t in antidote[1]),
           f"ANTIDOTE sans effet : message sans scène ({antidote})")
    expect(game, tm_free[0] and tm_free[1][3][0] == THUNDERBOLT, f"CT24 : scène et TONNERRE en 4e place ({tm_free[:2]})")
    expect(game, tadaa and tm_replace[0] and tm_replace[1][2][0] == SHOCK_WAVE,
           f"CT34 : MIMI-QUEUE oubliée, « Tadaa » dans la scène, ONDE DE CHOC en 3e ({tm_replace[:2]})")
    expect(game, stone[0] and stone[1] == names.number("SPECIES_RAICHU"), f"PIERRE FOUDRE : scène puis RAICHU ({stone})")
