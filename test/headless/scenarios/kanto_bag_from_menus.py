# Sac de Rouge Feu (SAC = KANTO) ouvert par d'autres écrans, sauvegarde « kanto » (2026-11-03, docs/A-TESTER.md) :
# - équipe > OBJET > DONNER : POTION donnée à PIKACHU ;
# - PC du joueur > OBJETS > DÉPOSER : 2 ANTIDOTE déposés ;
# - boutique d'Argenta (MENUS = KANTO) > VENDRE : POTION vendue, puis une CT par la Boîte à CT et une BAIE ORAN par
#   le Sac à Baies, chacun ouvert depuis le sac en mode vente ;
# - PC de ??? > DÉPLACER OBJETS (stockage d'Émeraude) > DONNER : le sac de RF, POTION donnée au PIKACHU de la boîte.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import open_start_entry, pick, press_until_free, bag, texts

POTION, ANTIDOTE, ORAN, TM01 = 13, 14, 139, 289


def answer_yes_until(game, since, words, limit=12):
    """A jusqu'à ce que words soit écrit (messages, OUI des confirmations)."""
    for _ in range(limit):
        if saw_text(game, words, since):
            return True
        game.tap("A"); game.wait(50)
    return saw_text(game, words, since)


def sell(game, limit=10):
    """Quantité 1 puis OUI : A jusqu'à ce que l'argent change, puis le message de la vente (▼) refermé."""
    money = game.money()
    for _ in range(limit):
        game.tap("A"); game.wait(50)
        if game.money() != money:
            break
    sold = game.money() != money
    for _ in range(6):                                 # RF attend A ou B après le message de la vente
        game.wait(40)
        tasks = [line for line in game.dev("jeu.etat").splitlines() if line.startswith("tache")]
        waiting = [t for t in tasks if "Sell" in t or "Sale" in t or "WaitPress" in t or "WaitAB" in t]
        game.note("TÂCHES " + " | ".join(t.split(" prio")[0] for t in tasks))
        if not waiting:
            break
        game.tap("A")
    return sold


def advance_messages(game, rounds=6):
    """A sur le dernier message tant qu'il attend (▼) : deux appuis au plus par message (le 1er peut seulement
    finir de l'écrire)."""
    for _ in range(rounds):
        game.wait(40)
        last = len(game.texts)
        shown = [t for _, _, t in game.texts if t.strip() not in ("", "▶")]
        if not shown or not shown[-1].rstrip().endswith("▼"):
            return
        for _ in range(2):
            game.tap("A"); game.wait(40)
            if len(game.texts) != last:
                break


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for item, count in (("ITEM_POTION", 5), ("ITEM_ANTIDOTE", 3), ("ITEM_TM_CASE", 1), ("ITEM_BERRY_POUCH", 1),
                        ("ITEM_TM01", 2), ("ITEM_ORAN_BERRY", 4)):
        game.item(item, count)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    game.warp("PalletTown", 9, 12); game.wait(30)

    # Équipe > OBJET > DONNER
    open_start_entry(game, "POKéMON"); game.wait(200)
    since = mark(game)
    game.tap("A"); game.wait(60)
    item_menu = mark(game)
    pick(game, since, "OBJET", first="RESUME"); game.wait(60)
    pick(game, item_menu, "DONNER"); game.wait(240)
    log(game, "donner sac")
    game.tap("A"); game.wait(60)
    given = answer_yes_until(game, since, "doit tenir POTION", limit=3)
    team = game.dev("joueur.equipe")
    press_until_free(game)

    # PC du joueur > OBJETS > DÉPOSER
    game.warp("ViridianCity_PokemonCenter_1F", 11, 2); game.wait(30)
    wait_until(game, lambda s: s.free)
    game.press("UP", 4); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(120); game.tap("A"); game.wait(90)
    game.tap("DOWN"); game.wait(20); game.tap("A")
    for _ in range(10):   # « PC personnel connecté. » puis le menu du PC du joueur
        game.tap("A"); game.wait(40)
        if saw_text(game, "BOITE LETTRE", since):
            break
    game.wait(30)
    pc_menu = texts(game, since)
    since = mark(game)
    game.tap("A"); game.wait(60)                       # OBJETS (1re entrée)
    pick(game, since, "DEPOSER OBJET"); game.wait(240)
    log(game, "deposer sac")
    since = mark(game)
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(60)   # ANTIDOTE (la POTION est chez PIKACHU... 4 restent)
    game.tap("UP"); game.wait(20)
    log(game, "deposer combien")
    deposited = answer_yes_until(game, since, "déposé")
    deposit_texts = texts(game, since)
    press_until_free(game)
    after_pc = bag(game)

    # Boutique d'Argenta (MENUS = KANTO) > VENDRE
    game.dev("jeu.options", 11, 1)
    money = game.money()
    game.warp("PewterCity_Mart", 4, 3); game.wait(30)
    game.press("LEFT", 4); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(150)
    pick(game, since, "VENDRE"); game.wait(240)
    log(game, "vendre sac")
    game.tap("UP", 10, gap=10); game.wait(30)         # le sac se rouvre sur le dernier objet visé (ANTIDOTE)
    since = mark(game)
    game.tap("A"); game.wait(60)                       # POTION
    log(game, "vendre combien")
    sold_potion = sell(game)
    sell_texts = texts(game, since)
    money_potion = game.money()
    # Boîte à CT depuis les Objets rares
    since = mark(game)
    game.tap("RIGHT")
    wait_text(game, "OBJ. RARES", since=since)
    game.wait(60)
    game.tap("UP", 10, gap=10); game.wait(30)
    game.tap("A"); game.wait(240)
    log(game, "vendre boite CT")
    game.tap("UP", 10, gap=10); game.wait(30)
    game.tap("A"); game.wait(60)
    sold_tm = sell(game)
    tm_texts = texts(game, since)
    since = mark(game)
    game.tap("B")                                      # retour au sac
    wait_text(game, "OBJ. RARES", since=since)
    game.wait(60)
    log(game, "retour au sac")
    # Sac à Baies
    game.tap("DOWN"); game.wait(30)
    since = mark(game)
    game.tap("A"); game.wait(240)
    log(game, "vendre sac a baies")
    game.tap("UP", 10, gap=10); game.wait(30)
    game.tap("A"); game.wait(60)
    sold_berry = sell(game)
    berry_texts = texts(game, since)
    game.tap("B"); game.wait(240)                      # retour au sac
    game.tap("B"); game.wait(240)                      # retour à la boutique
    press_until_free(game)
    items = bag(game)

    # PC de ??? > DÉPLACER OBJETS : DONNER une POTION au PIKACHU de la BOITE 1
    for _ in range(6):                                 # équipe pleine : le 7e va dans la BOITE 1
        game.give_mon("SPECIES_PIKACHU", 20)
    game.warp("ViridianCity_PokemonCenter_1F", 11, 2); game.wait(30)
    wait_until(game, lambda s: s.free)
    game.press("UP", 4); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(120); game.tap("A"); game.wait(90)   # PC de ??? (1re entrée)
    for _ in range(6):
        game.tap("A"); game.wait(40)
        if saw_text(game, "DEPLACER OBJETS", since):
            break
    game.wait(30)
    pick(game, since, "DEPLACER OBJETS", first="RETIRER POKéMON"); game.wait(300)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "DONNER"); game.wait(300)
    game.tap("LEFT", 3, gap=40); game.wait(60)         # poche OBJETS (le sac se rouvre sur la dernière)
    game.tap("UP", 10, gap=10); game.wait(30)
    log(game, "pc boite sac")
    game.tap("A"); game.wait(300)
    log(game, "pc boite tenu")
    held = saw_text(game, "POTION tenu", since)
    box_texts = texts(game, since)
    potions_after_box = [q for n, _, q in bag(game)["poche 1"] if n == POTION]
    for _ in range(3):
        game.tap("B"); game.wait(120)
    press_until_free(game)

    # Vérifications
    expect(game, given and f"objet {POTION}\n" in team, f"POTION donnée à PIKACHU ({team.strip()})")
    expect(game, deposited and [q for n, _, q in after_pc["pc"] if n == ANTIDOTE] == [2],
           f"2 ANTIDOTE déposés au PC ({after_pc['pc']} ; {deposit_texts})")
    expect(game, sold_potion and [q for n, _, q in items["poche 1"] if n == POTION] == [3],
           f"une POTION vendue ({items['poche 1']} ; {sell_texts})")
    expect(game, sold_tm and [q for n, _, q in items["poche 3"] if n == TM01] == [1],
           f"une CT vendue par la Boîte à CT ({items['poche 3']} ; {tm_texts})")
    expect(game, sold_berry and [q for n, _, q in items["poche 4"] if n == ORAN] == [3],
           f"une BAIE ORAN vendue par le Sac à Baies ({items['poche 4']} ; {berry_texts})")
    expect(game, game.money() > money_potion > money, f"argent des ventes ({money} -> {money_potion} -> {game.money()})")
    expect(game, held and potions_after_box == [2], f"POTION donnée au PIKACHU de la boîte ({potions_after_box} ; {box_texts})")
