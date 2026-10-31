# Pokémon offert à Kanto avec l'équipe pleine (Évoli du toit de Céladopole) : envoyé au PC, message du script commun
# (2026-10-31) avec le PC de LÉO et la BOITE où il est vraiment allé. Avant, le script de RF lisait
# VAR_KANTO_PC_BOX_TO_SEND_MON, que rien ne remplissait (toujours le nom de la première boîte).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, finish_dialog, mark, saw_text, talk_to
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log


def play(game):
    continue_game(game)
    for _ in range(6):
        game.give_mon("SPECIES_RATTATA", 5)   # équipe pleine
    game.flag("FLAG_KANTO_SYS_NOT_SOMEONES_PC", 1)   # LÉO rencontré
    game.warp("CeladonCity_Condominiums_RoofRoom", 7, 4); game.wait(30)
    since = mark(game)
    talk_to(game, "UP", finish=False)
    finish_dialog(game, answers={"surnom": "B"})
    texts = [t for _, _w, t in game.texts[since:]]
    sent = next((t for t in texts if "PC de LEO" in t), None)
    box = re.search(r"“(.+?)”", sent or "")
    log(game, "fini")

    # Vérifications
    expect(game, sent is not None, f"message du PC de LÉO ({texts[-3:]})")
    expect(game, box is not None and box.group(1).strip() != "", f"nom de la boîte ({sent})")
