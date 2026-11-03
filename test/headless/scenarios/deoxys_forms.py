# Formes de DEOXYS (2026-11-03, docs/A-TESTER.md ; party_menu.c CursorCb_DeoxysSetForm, pokemon.c GetDeoxysStat) :
# menu de l'équipe > FORME > NORMALE / ATTAQUE / DÉFENSE / VITESSE : « DEOXYS prend la forme X ! », stats de la forme
# (sDeoxysBaseStats), image de la forme dans le résumé ; VITESSE par défaut (comme Émeraude) ; la forme est commune à
# tous les DEOXYS du joueur.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from menu_helpers import open_start_entry, pick, texts

FORMS = ("NORMALE", "ATTAQUE", "DÉFENSE", "VITESSE")


def stats(game, slot):
    """{ATQ, DEF, VIT, ATS, DFS} du POKéMON slot (ligne « stats » de joueur.equipe)."""
    lines = game.dev("joueur.equipe").splitlines()
    heads = [i for i, line in enumerate(lines) if line[:1].isdigit()]
    block = " ".join(lines[heads[slot]:heads[slot + 1] if slot + 1 < len(heads) else None])
    return {k: int(v) for k, v in re.findall(r"(ATQ|DEF|VIT|ATS|DFS) (\d+)", block)}


def back_to_field(game):
    for _ in range(10):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free, limit=900)


def set_form(game, form):
    """Équipe > DEOXYS (1er) > FORME > form ; rend le message, puis le résumé (capture)."""
    open_start_entry(game, "POKéMON"); game.wait(90)
    since = mark(game)
    game.tap("A"); game.wait(40)
    forms = mark(game)
    pick(game, since, "FORME"); game.wait(40)
    since = mark(game)
    pick(game, forms, form); game.wait(90)
    message = " ".join(t for _, t in texts(game, since))
    game.tap("A"); game.wait(60)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, "RESUME"); game.wait(200)
    log(game, f"resume {form}")
    back_to_field(game)
    return message


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_DEOXYS", 50)
    game.give_mon("SPECIES_DEOXYS", 30)
    default = stats(game, 0)
    expect(game, default["VIT"] > default["ATQ"] and default["VIT"] > default["DEF"],
           f"par défaut, forme VITESSE : la VITESSE en tête ({default})")

    seen = {}
    for form in FORMS:
        message = set_form(game, form)
        seen[form] = stats(game, 0)
        game.note(f"{form} : {seen[form]} ; {message[-60:]}")
        expect(game, f"prend la forme {form}" in message.replace(" ", " "), f"{form} : message ({message[-60:]})")
    expect(game, seen["ATTAQUE"]["ATQ"] > seen["NORMALE"]["ATQ"] > seen["VITESSE"]["ATQ"] > seen["DÉFENSE"]["ATQ"],
           f"ATTAQUE : ATQ la plus forte, DÉFENSE la plus faible ({ {f: s['ATQ'] for f, s in seen.items()} })")
    expect(game, seen["DÉFENSE"]["DEF"] > seen["VITESSE"]["DEF"] > seen["NORMALE"]["DEF"] > seen["ATTAQUE"]["DEF"],
           f"DÉFENSE : DEF la plus forte ({ {f: s['DEF'] for f, s in seen.items()} })")
    expect(game, seen["VITESSE"] == default, f"retour à VITESSE : les stats du début ({seen['VITESSE']}, {default})")
    other = stats(game, 1)
    game.note(f"2e DEOXYS : {other}")
    expect(game, other["VIT"] > other["ATQ"], f"la forme est commune : le 2e DEOXYS aussi en VITESSE ({other})")
