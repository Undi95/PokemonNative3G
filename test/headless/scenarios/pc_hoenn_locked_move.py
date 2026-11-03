# POKéMON de Hoenn retenus au PC pendant le voyage à Kanto, dans DÉPLACER POKéMON (docs/A-TESTER.md, 2026-11-03 ;
# Task_PlaceMon et Task_ShiftMon, Fusion_IsBoxMonLockedInHoenn) : le PIKACHU marqué « de Hoenn » de la BOITE 1, pris
# avec DEPLACER, puis posé dans l'équipe sur une place vide (PLACER) et sur MEWTWO (CHANGER) : deux fois « Aucun lien
# avec HOENN! », l'équipe ne change pas. Sans le verrou (FLAG_FUSION_KANTO_VISITED à 0), PLACER le met dans l'équipe.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import pick, texts
from pc_wallpapers_kanto import open_boxes

BOX_ROWS = 5            # IN_BOX_ROWS : sous la dernière rangée, les boutons ÉQUIPE et FERMER


def party_count(game):
    return len(re.findall(r"(?m)^\d+ ", game.dev("joueur.equipe")))


def drop(game, label, shot):
    """A sur la place de l'équipe sous le curseur, label (PLACER ou CHANGER), capture shot (un nom par appel : un
    nom repris écrase la capture d'avant) : les textes, puis le message fermé."""
    since = mark(game)
    game.tap("A"); game.wait(60)
    shown = [t for _, t in texts(game, since)]
    if label not in shown:
        return " ".join(shown)
    pick(game, since, label); game.wait(90)
    game.shot(shot)
    said = " ".join(t for _, t in texts(game, since))
    game.tap("B"); game.wait(40)                        # (le message se ferme sur A, B ou une flèche)
    return said


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.flag("FLAG_FUSION_KANTO_VISITED", 1)
    game.give_mon("SPECIES_MEWTWO", 70)
    game.give_mon("SPECIES_PIKACHU", 20)
    deposit = game.dev("joueur.pc", 1)                  # le PIKACHU au PC, 1er de la BOITE 1
    status = game.dev("joueur.hoenn", 0, 0, 1)
    game.note(f"DÉPÔT {deposit.strip()} ; MARQUE {status.strip()}")
    expect(game, "boite 0 place 0" in deposit and "retenu au PC 1" in status, f"PIKACHU de Hoenn ({deposit} ; {status})")

    open_boxes(game)
    since = mark(game)
    game.tap("A"); game.wait(60)                        # le PIKACHU : son menu
    pick(game, since, "DEPLACER"); game.wait(60)
    game.tap("DOWN", BOX_ROWS, gap=12); game.wait(20)   # le bouton ÉQUIPE
    game.tap("A"); game.wait(120)                       # l'équipe s'ouvre, le curseur sur la 1re place vide
    game.shot("equipe")
    placed = drop(game, "PLACER", "refus-placer")
    game.note(f"PLACER : {placed[-120:]}")
    game.tap("LEFT"); game.wait(30)                     # MEWTWO
    shifted = drop(game, "CHANGER", "refus-changer")
    game.note(f"CHANGER : {shifted[-120:]}")
    count = party_count(game)
    expect(game, "Aucun lien avec HOENN" in placed, f"PLACER refusé ({placed[-100:]})")
    expect(game, "Aucun lien avec HOENN" in shifted, f"CHANGER refusé ({shifted[-100:]})")
    expect(game, count == 1, f"l'équipe ne change pas ({count} POKéMON)")

    # Sans le verrou (la marque est dans le POKéMON tenu : on lève le voyage à Kanto) : PLACER le met dans l'équipe
    game.flag("FLAG_FUSION_KANTO_VISITED", 0)
    game.tap("RIGHT"); game.wait(30)                    # la place vide
    placed = drop(game, "PLACER", "place-sans-verrou")
    game.wait(60)
    count = party_count(game)
    game.note(f"PLACER (sans verrou) : {placed[-120:]} ; équipe {count}")
    expect(game, "Aucun lien avec HOENN" not in placed and count == 2, f"sans le verrou, il est placé ({count} ; {placed[-100:]})")
