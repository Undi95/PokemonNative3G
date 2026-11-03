# Cottage de LÉO, Route 25 (docs/A-TESTER.md, 2026-11-03 ; Route25_SeaCottage/scripts.inc) : LÉO en MÉLOFÉE demande de
# l'aide, entre dans le téléporteur (porte 10,3) ; l'ordinateur (4,5) lance le séparateur : la caméra glisse vers les
# téléporteurs, AnimateTeleporterHousing et AnimateTeleporterCable (captures « teleporteurs-N » à revoir), LÉO sort de
# l'autre (porte 3,3) en humain ; FLAG_KANTO_HELPED_BILL_IN_SEA_COTTAGE posé.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts


def play(game):
    continue_game(game)
    game.flag("FLAG_KANTO_HELPED_BILL_IN_SEA_COTTAGE", 0)
    game.flag("FLAG_KANTO_GOT_SS_TICKET", 0)
    game.flag("FLAG_KANTO_HIDE_BILL_HUMAN_SEA_COTTAGE", 1)
    game.item("ITEM_SS_TICKET", 0)

    # LÉO en MÉLOFÉE (10, 6), parlé depuis le dessous
    game.warp("Route25_SeaCottage", 10, 7); game.wait(40)
    finish_dialog(game, settle=20)
    since = mark(game)
    talk_to(game, "UP", finish=False)
    finish_dialog(game, limit=600)
    asked = " ".join(t for _, t in texts(game, since))
    game.note(f"LÉO : {asked[:200]}")
    expect_flag(game, "FLAG_TEMP_2", 1)                 # BILL_IN_TELEPORTER

    # L'ordinateur (4, 5), à pied (un téléport ferait revenir MÉLOFÉE et effacerait BILL_IN_TELEPORTER) : le séparateur
    walk_to(game, 4, 6)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    sounds = len(game.sounds)
    game.tap("A")
    for _ in range(30):                                 # le message, jusqu'au premier bip (la caméra a glissé)
        game.wait(30)
        if "SE_PIN" in [s for _, s in game.sounds[sounds:]]:
            break
        game.tap("A")
    for i in range(40):
        game.shot(f"teleporteurs-{i}"); game.wait(10)
    finish_dialog(game, limit=600)
    played = [s for _, s in game.sounds[sounds:]]
    game.note(f"SÉPARATEUR : {played}")
    expect_flag(game, "FLAG_KANTO_HELPED_BILL_IN_SEA_COTTAGE", 1)
    expect(game, "SE_WARP_IN" in played, f"le câble du téléporteur (SE_WARP_IN) ({played})")

    # LÉO humain sorti du téléporteur, au milieu de la pièce
    game.note(f"OBJETS {game.dev('carte.objets')}")
    expect_flag(game, "FLAG_KANTO_HIDE_BILL_HUMAN_SEA_COTTAGE", 0)


def printer_waits_any(game):
    """Un message attend A (texte.imprimantes : état d'attente)."""
    return any(f" etat {state} " in line for line in game.dev("texte.imprimantes").splitlines() for state in (1, 2, 3))
