# OVO-CHRONO, CHARME CHROMA et CHARME OVALE (2026-11-03, docs/A-TESTER.md ; data/scripts/fusion_charms.inc,
# src/fusion_events.c) :
# - le président du Fan Club de Carmin sur Mer donne l'OVO-CHRONO (à la place du BON COMMANDE) ; avec lui, un OEUF de
#   l'équipe perd 2 cycles d'éclosion tous les 256 pas au lieu d'un (OvoChrono_EggCycles) ;
# - POKéDEX NATIONAL complet : le concepteur du Motel de Nénucrique donne le CHARME CHROMA avant son diplôme, celui de
#   Céladopole le CHARME OVALE ; une seule fois chacun.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from menu_helpers import open_start_entry, bag

GAME_STAT_STEPS = names.number("GAME_STAT_STEPS")


def steps(game):
    return int(game.dev("jeu.stat", GAME_STAT_STEPS).split("=")[1])


def walk_exact_steps(game, count):
    """Exactement count pas (statistique GAME_STAT_STEPS), un pas à la fois, en allant et venant sur la rangée 9 de
    Bourg Palette (libre de x = 2 à 21)."""
    start = steps(game)
    direction, blocked = "RIGHT", 0
    while steps(game) - start < count:
        x = game.state.pos[0]
        if (direction == "RIGHT" and x >= 19) or (direction == "LEFT" and x <= 4) or blocked >= 3:
            direction, blocked = ("LEFT" if direction == "RIGHT" else "RIGHT"), 0
        before = steps(game)
        game.press(direction, 1)
        game.wait(20)                                   # un pas : 16 images (« libre » reste vrai pendant le pas)
        blocked = blocked + 1 if steps(game) == before else 0
    return steps(game) - start


def egg_cycles(game, slot):
    return int(game.dev("joueur.amitie", slot).split("amitie")[1])


def egg_cycles_lost(game, slot):
    """Cycles d'éclosion perdus en 256 pas : un seul passage du compteur de la pension (u8, « ++stepCounter == 255 »
    d'Émeraude, qui revient à 255 tous les 256 pas)."""
    game.dev("joueur.amitie", slot, 20)
    game.warp("PalletTown", 10, 9); game.wait(30)
    walked = walk_exact_steps(game, 256)
    lost = 20 - egg_cycles(game, slot)
    game.note(f"{walked} pas : {lost} cycles perdus")
    return lost


def party_slot(game, species):
    number = names.number(species)
    game.wait(2)                                        # l'état du banc suit l'équipe à l'image suivante
    slots = [i for i, mon in enumerate(game.state.party) if mon[0] == number]
    if not slots:
        raise GameError(f"{species} pas dans l'équipe : {game.state.party}")
    return slots[0]


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.dev("jeu.rencontres", 0)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO (objets rares dans la 2e poche)
    game.give_mon("SPECIES_TOGEPI", 5)
    slot = party_slot(game, "SPECIES_TOGEPI")
    game.dev("joueur.oeuf", slot)

    # Sans l'OVO-CHRONO : 1 cycle tous les 256 pas
    expect(game, game.item("ITEM_OVO_CHRONO") == 0, "pas d'OVO-CHRONO au départ")
    without = egg_cycles_lost(game, slot)
    expect(game, without == 1, f"sans OVO-CHRONO : 1 cycle perdu en 256 pas ({without})")

    # Le président du Fan Club : son histoire (OUI), puis l'OVO-CHRONO
    game.warp("VermilionCity_PokemonFanClub", 5, 5); game.wait(30)
    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "OVO-CHRONO", since), "le président donne l'OVO-CHRONO")
    expect(game, saw_text(game, "deux fois plus vite", since), "le président explique l'OVO-CHRONO")
    expect_item(game, "ITEM_OVO_CHRONO", 1)
    expect_flag(game, "FLAG_KANTO_GOT_BIKE_VOUCHER", 1)
    since = mark(game)
    talk_to(game, "UP")
    expect(game, not saw_text(game, "OVO-CHRONO!", since), "une seule fois")
    expect_item(game, "ITEM_OVO_CHRONO", 1)

    # Avec l'OVO-CHRONO : 2 cycles tous les 256 pas
    with_item = egg_cycles_lost(game, slot)
    expect(game, with_item == 2, f"avec l'OVO-CHRONO : 2 cycles perdus en 256 pas ({with_item})")

    # Les charmes : sans le POKéDEX NATIONAL complet, rien
    game.dev("jeu.pokedex", 151)                        # POKéDEX de Kanto complet (diplôme de Céladopole)
    game.warp("CeladonCity_Condominiums_3F", 3, 9); game.wait(30)
    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "", since) and game.item("ITEM_OVAL_CHARM") == 0,
           "Céladopole, POKéDEX de Kanto seul : pas de CHARME OVALE")
    game.dev("jeu.pokedex", 386)                        # POKéDEX NATIONAL complet

    # Céladopole : CHARME OVALE, puis le diplôme
    game.warp("CeladonCity_Condominiums_3F", 3, 9); game.wait(30)
    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "CHARME OVALE", since), "Céladopole : le concepteur donne le CHARME OVALE")
    expect_item(game, "ITEM_OVAL_CHARM", 1)
    expect_flag(game, "FLAG_GOT_OVAL_CHARM", 1)
    since = mark(game)
    talk_to(game, "UP", finish=False)
    for _ in range(20):                                 # les pages, jusqu'au diplôme de RF
        if saw_text(game, "Ce document", since):
            break
        game.tap("A"); game.wait(40)
    game.wait(60); log(game, "diplome national celadopole")
    expect(game, saw_text(game, "POKéDEX NATIONAL", since), "Céladopole : diplôme du POKéDEX NATIONAL")
    finish_dialog(game)
    expect_item(game, "ITEM_OVAL_CHARM", 1)

    # Les icônes dessinées (OVO-CHRONO, charmes) : SAC > objets rares
    open_start_entry(game, "SAC"); game.wait(240)
    game.tap("LEFT", 3, gap=40); game.wait(30); game.tap("RIGHT"); game.wait(90)
    keys = [n for _, n, _ in bag(game)["poche 5"]]
    game.tap("UP", 10, gap=10); game.wait(20)
    for label in ("OVO-CHRONO", "CHARME OVALE"):
        index = next(i for i, n in enumerate(keys) if n.startswith(label))
        game.tap("UP", 10, gap=10); game.wait(20)
        if index:
            game.tap("DOWN", index, gap=20)
        game.wait(60); log(game, f"sac {label}")
    for _ in range(6):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)

    # Nénucrique : CHARME CHROMA, puis le diplôme
    game.flag("FLAG_HIDE_LILYCOVE_MOTEL_GAME_DESIGNERS", 0)
    game.warp("LilycoveCity_CoveLilyMotel_2F", 4, 7); game.wait(30)
    since = mark(game)
    talk_to(game, "UP")
    expect(game, saw_text(game, "CHARME CHROMA", since), "Nénucrique : le concepteur donne le CHARME CHROMA")
    expect_item(game, "ITEM_SHINY_CHARM", 1)
    expect_flag(game, "FLAG_GOT_SHINY_CHARM", 1)
    game.warp("LilycoveCity_CoveLilyMotel_2F", 4, 7); game.wait(30)
    talk_to(game, "UP")
    expect_item(game, "ITEM_SHINY_CHARM", 1)
