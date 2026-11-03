# POKéMON de Hoenn retenus au PC pendant le voyage à Kanto (docs/A-TESTER.md, 2026-11-03 ; Fusion_IsBoxMonLockedInHoenn) :
# un PIKACHU de la BOITE 1 avec la marque « de Hoenn » (outil joueur.hoenn) : PC de Jadielle > RETIRER POKéMON > le
# PIKACHU > RETIRER : « Aucun lien avec HOENN! », il reste au PC ; sans la marque, il est retiré.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import pick, texts, press_until_free


def withdraw(game):
    """PC de Jadielle > PC de ??? > RETIRER POKéMON, le 1er de la BOITE 1, RETIRER : les textes."""
    game.warp("ViridianCity_PokemonCenter_1F", 11, 2); game.wait(30)
    wait_until(game, lambda s: s.free)
    game.press("UP", 4); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(120); game.tap("A"); game.wait(90)
    for _ in range(6):
        game.tap("A"); game.wait(40)
        if saw_text(game, "RETIRER POKéMON", since):
            break
    game.wait(30)
    pick(game, since, "RETIRER POKéMON"); game.wait(300)
    menu = mark(game)
    game.tap("A"); game.wait(60)                        # le 1er POKéMON de la boîte : son menu
    pick(game, menu, "RETIRER"); game.wait(120)
    game.shot(f"retirer-{len(game.state.party)}")
    shown = " ".join(t for _, t in texts(game, since))
    for _ in range(12):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    press_until_free(game)
    return shown


def play(game):
    continue_game(game)
    game.flag("FLAG_FUSION_KANTO_VISITED", 1)
    game.give_mon("SPECIES_MEWTWO", 70)
    game.give_mon("SPECIES_PIKACHU", 20)
    deposit = game.dev("joueur.pc", 1)                  # le PIKACHU au PC
    game.note(f"DÉPÔT {deposit}")
    expect(game, "boite 0 place 0" in deposit, f"PIKACHU 1er de la BOITE 1 ({deposit})")
    status = game.dev("joueur.hoenn", 0, 0, 1)
    game.note(f"MARQUE {status}")
    expect(game, "retenu au PC 1" in status, f"PIKACHU de Hoenn retenu au PC ({status})")
    shown = withdraw(game)
    game.note(f"RETIRER (marqué) : {shown[-160:]}")
    expect(game, "Aucun lien avec HOENN" in shown and len(game.state.party) == 1,
           f"« Aucun lien avec HOENN! », il reste au PC ({len(game.state.party)} ; {shown[-100:]})")

    game.dev("joueur.hoenn", 0, 0, 0)
    shown = withdraw(game)
    game.note(f"RETIRER (sans marque) : {shown[-160:]}")
    expect(game, "Aucun lien avec HOENN" not in shown and len(game.state.party) == 2,
           f"sans la marque, il est retiré ({len(game.state.party)} ; {shown[-100:]})")
