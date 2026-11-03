# Vélos à Kanto (2026-11-03, docs/A-TESTER.md ; data/scripts/fusion_bike.inc, GetOnOffBike) :
# - vendeur d'Azuria sans vélo : il envoie au magasin de LAVANDIA (Hoenn), rien de donné ;
# - avec le VELO COURSE de Hoenn : il donne le VELO CROSS (FLAG_KANTO_GOT_BICYCLE), puis demande comment il roule ;
# - en roulant sur le VELO COURSE, UTILIS. le VELO CROSS depuis le SAC : on change de vélo sans descendre.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, pick, texts, bag

MACH, ACRO = 0x02, 0x04


def avatar(game):
    return int(game.dev("carte.info").splitlines()[2].split("avatar ")[1].split(",")[0], 16)


def talk_clerk(game):
    game.warp("CeruleanCity_BikeShop", 9, 5); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(40)
    finish_dialog(game)
    return " ".join(t for _, t in texts(game, since))


def use_from_bag(game, item_name):
    """SAC (KANTO) > Objets rares > item_name > UTILIS."""
    open_start_entry(game, "SAC"); game.wait(240)
    keys = [n for _, n, _ in bag(game)["poche 5"]]
    game.tap("LEFT", 3, gap=40); game.wait(30); game.tap("RIGHT"); game.wait(90)
    game.tap("UP", 10, gap=10); game.wait(20)
    index = next(i for i, n in enumerate(keys) if n.startswith(item_name))
    if index:
        game.tap("DOWN", index, gap=20); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    pick(game, since, "UTILIS.")
    game.wait(120)
    wait_until(game, lambda s: s.free, limit=900)


def play(game):
    continue_game(game)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    no_bike = talk_clerk(game)
    expect(game, "LAVANDIA" in no_bike and game.item("ITEM_ACRO_BIKE") == 0 and game.item("ITEM_MACH_BIKE") == 0,
           f"sans vélo : direction LAVANDIA, rien de donné ({no_bike[-70:]})")

    game.item("ITEM_MACH_BIKE", 1)
    game.flag("FLAG_RECEIVED_BIKE", 1)
    given = talk_clerk(game)
    expect(game, game.item("ITEM_ACRO_BIKE") == 1, f"avec le VELO COURSE : VELO CROSS donné ({given[-70:]})")
    expect_flag(game, "FLAG_KANTO_GOT_BICYCLE", 1)
    again = talk_clerk(game)
    expect(game, game.item("ITEM_ACRO_BIKE") == 1 and game.item("ITEM_MACH_BIKE") == 1,
           f"ensuite : rien de plus ({again[-60:]})")

    # Sur le VELO COURSE, puis le VELO CROSS depuis le SAC sans descendre, puis de nouveau le VELO COURSE
    game.warp("CeruleanCity", 20, 20); game.wait(40)
    game.dev("joueur.enregistre", names.number("ITEM_MACH_BIKE"))
    game.tap("SELECT", hold=4); game.wait(40)
    wait_until(game, lambda s: s.free)
    on_mach = avatar(game)
    use_from_bag(game, "VELO CROSS")
    on_acro = avatar(game)
    use_from_bag(game, "VELO COURSE")
    back = avatar(game)
    game.note(f"avatar : {on_mach:#x} -> {on_acro:#x} -> {back:#x}")
    expect(game, on_mach & MACH, f"à VELO COURSE ({on_mach:#x})")
    expect(game, on_acro & ACRO and not on_acro & MACH, f"SAC > VELO CROSS en roulant : sur le VELO CROSS ({on_acro:#x})")
    expect(game, back & MACH and not back & ACRO, f"SAC > VELO COURSE : de nouveau sur le VELO COURSE ({back:#x})")
