# Derniers objets en double (2026-11-03, docs/A-TESTER.md, docs/OBJETS-EN-DOUBLE.md ; tools/kanto_doubles.py) :
# - PASS OCEANE : LÉO (Route 25) le donne à la place du PASSE BATEAU d'Émeraude ;
# - AUTO-REPOUSSE : l'assistant de la Route 11 (30 POKéMON de Kanto) le donne à la place du CHERCH'OBJET ; à la fin
#   d'un REPOUSSE, il propose le plus faible du sac (OUI : utilisé, 100 pas ; NON : rien) ;
# - homme de la BOITE JETONS (Céladopole) : il a tout perdu ; avec 9999 jetons, les lui donner = LEVEINARD chromatique
#   N.25, puis il disparaît (FLAG_COIN_CASE_MAN_GONE) ;
# - POT POUDRE (Azuria) : sans celui de Hoenn, direction POIVRESSEL ; avec, des BAIES.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from menu_helpers import bag, open_start_entry, texts


def said(game, since):
    return " ".join(t for _, t in texts(game, since))


def last_party_mon(game):
    """(espèce, niveau, dresseur d'origine, ID du joueur, personnalité) du dernier POKéMON de l'équipe (joueur.equipe)."""
    lines = game.dev("joueur.equipe").splitlines()
    head = [i for i, line in enumerate(lines) if line[:1].isdigit()][-1]
    block = " ".join(lines[head:head + 3])
    species = block.split()[1]
    level = int(block.split("N.")[1].split()[0])
    ot = int(block.split("DO ")[1].split()[0])
    player = int(block.split("(joueur ")[1].split(")")[0])
    personality = int(block.split("perso ")[1].split()[0], 16)
    return species, level, ot, player, personality


def is_shiny(ot, personality):
    return ((ot >> 16) ^ (ot & 0xFFFF) ^ (personality >> 16) ^ (personality & 0xFFFF)) < 8


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("jeu.rencontres", 0)

    # PASS OCEANE : le don de LÉO, une fois redevenu humain
    game.flag("FLAG_KANTO_HIDE_BILL_HUMAN_SEA_COTTAGE", 0)
    game.warp("Route25_SeaCottage", 7, 6); game.wait(30)
    since = mark(game)
    game.script("Route25_SeaCottage_EventScript_BillGiveSSTicket")
    finish_dialog(game)
    expect(game, saw_text(game, "PASS OCEANE", since), f"LÉO : le PASS OCEANE ({said(game, since)[-80:]})")
    expect_item(game, "ITEM_OCEAN_PASS", 1)
    expect_item(game, "ITEM_SS_TICKET", game.item("ITEM_SS_TICKET"))   # le PASSE BATEAU d'Émeraude n'est pas donné
    expect_flag(game, "FLAG_KANTO_GOT_SS_TICKET", 1)

    # AUTO-REPOUSSE : l'assistant de la Route 11, avec 30 POKéMON de Kanto
    game.dev("jeu.pokedex", 30)
    game.warp("Route11_EastEntrance_2F", 2, 7); game.wait(30)
    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "AUTO-REPOUSSE", since), f"assistant : l'AUTO-REPOUSSE ({said(game, since)[-80:]})")
    expect_item(game, "ITEM_AUTO_REPEL", 1)
    expect_item(game, "ITEM_ITEMFINDER", game.item("ITEM_ITEMFINDER"))
    expect_flag(game, "FLAG_KANTO_GOT_ITEMFINDER", 1)

    # Fin d'un REPOUSSE : il propose le plus faible du sac (REPOUSSE avant SUPEREPOUSSE)
    game.item("ITEM_REPEL", 2)
    game.item("ITEM_SUPER_REPEL", 1)
    repels = game.item("ITEM_REPEL")
    for answer, wanted in (("A", "OUI"), ("B", "NON")):
        game.warp("PalletTown", 10, 9); game.wait(30)
        game.var("VAR_REPEL_STEP_COUNT", 1)
        since = mark(game)
        game.press("RIGHT", 1); game.wait(20)
        game.press("RIGHT", 1); game.wait(30)
        wait_text(game, "AUTO-REPOUSSE", since)
        finish_dialog(game, button=answer)
        text = said(game, since)
        expect(game, "REPOUSSE?" in text and "SUPEREPOUSSE?" not in text,
               f"{wanted} : AUTO-REPOUSSE propose le REPOUSSE, le plus faible ({text[-90:]})")
        if answer == "A":
            expect_item(game, "ITEM_REPEL", repels - 1)
            expect_var(game, "VAR_REPEL_STEP_COUNT", 100)
        else:
            expect_item(game, "ITEM_REPEL", repels - 1)
            expect_var(game, "VAR_REPEL_STEP_COUNT", 0)

    # L'homme de la BOITE JETONS : sans 9999 jetons, il est triste
    game.item("ITEM_COIN_CASE", 1)
    game.dev("joueur.jetons", 100)
    game.warp("CeladonCity_Restaurant", 1, 3); game.wait(30)
    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "tout perdu", since) and not saw_text(game, "donnerais", since),
           f"100 jetons : il est triste, rien de plus ({said(game, since)[-80:]})")
    # Avec 9999 jetons : OUI, LEVEINARD chromatique N.25, puis il s'en va
    game.dev("joueur.jetons", 9999)
    since = mark(game)
    talk_to(game, "UP")
    species, level, ot, player, personality = last_party_mon(game)
    expect(game, saw_text(game, "donnerais", since), "9999 jetons : il les demande")
    expect(game, species == "LEVEINARD" and level == 25 and ot == player and is_shiny(ot, personality),
           f"LEVEINARD chromatique N.25 au joueur ({species} N.{level}, DO {ot}/{player}, perso {personality:#x})")
    expect(game, "jetons 0" in game.dev("joueur.jetons").replace(":", ""), f"jetons donnés ({game.dev('joueur.jetons').strip()})")
    expect_flag(game, "FLAG_COIN_CASE_MAN_GONE", 1)
    expect(game, "113" in game.dev("jeu.pokedex").split("numeros nationaux) :")[1].split(),
           "LEVEINARD attrapé au POKéDEX")

    # POT POUDRE : sans celui de Hoenn, direction POIVRESSEL ; avec, des BAIES
    game.item("ITEM_POWDER_JAR", -game.item("ITEM_POWDER_JAR"))
    game.warp("CeruleanCity_House5", 7, 5); game.wait(30)
    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "POIVRESSEL", since), f"sans POT POUDRE : direction POIVRESSEL ({said(game, since)[-80:]})")
    expect_flag(game, "FLAG_KANTO_GOT_POWDER_JAR", 0)
    game.item("ITEM_POWDER_JAR", 1)
    sitrus = game.item("ITEM_SITRUS_BERRY")
    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "connaisseur", since), f"avec le POT POUDRE : des BAIES ({said(game, since)[-80:]})")
    expect_item(game, "ITEM_SITRUS_BERRY", sitrus + 3)
    expect_flag(game, "FLAG_KANTO_GOT_POWDER_JAR", 1)

    # Les deux MÉTÉORITES dans le sac : celle de Kanto rougeâtre (tools/kanto_meteorite.py)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO (objets rares dans la 2e poche)
    game.item("ITEM_METEORITE", 1)
    game.item("ITEM_KANTO_METEORITE", 1)
    open_start_entry(game, "SAC"); game.wait(240)
    game.tap("LEFT", 3, gap=40); game.wait(30); game.tap("RIGHT"); game.wait(90)
    keys = [n for _, n, _ in bag(game)["poche 5"]]
    numbers = [number for number, _, _ in bag(game)["poche 5"]]
    for item in ("ITEM_METEORITE", "ITEM_KANTO_METEORITE"):
        index = numbers.index(names.number(item))
        game.tap("UP", 12, gap=10); game.wait(20)
        if index:
            game.tap("DOWN", index, gap=20)
        game.wait(60); log(game, f"sac {item}")
    expect(game, keys.count("METEORITE") == 2, f"deux MÉTÉORITES distinctes dans les objets rares ({keys})")
