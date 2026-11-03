# Fenêtre d'infos de la sauvegarde (menu Start > SAUVER, 2026-11-03) :
# - Options > MENUS = KANTO : celle de Rouge Feu (PrintSaveStats et SaveStatToString de RF : 14 × 9, lieu centré,
#   JOUEUR / BADGES / POKéDEX / DUREE JEU en petite police, cadre standard de RF) ; badges et Pokédex de la région
#   où l'on sauvegarde (RF : ceux de Kanto) ; la ligne POKéDEX seulement si la région a donné son Pokédex ;
# - MENUS = HOENN : celle d'Émeraude (14 × 10, ou 14 × 8 sans Pokédex).
# On répond NON : la sauvegarde n'est pas faite, la fenêtre se ferme.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, wait_until, wait_text, mark
from kanto_tour import log

OPTION_MENU_STYLE = 11   # jeu.options (src/debug_tools.c)


def windows(game):
    """Les fenêtres ouvertes : {(x, y): (largeur, hauteur)}."""
    return {(int(m.group(1)), int(m.group(2))): (int(m.group(3)), int(m.group(4)))
            for m in re.finditer(r"en (-?\d+),(-?\d+) taille (\d+)x(\d+)", game.dev("gfx.fenetres"))}


def save_window(game, what):
    """Menu Start > SAUVER, la fenêtre d'infos, puis NON."""
    wait_until(game, lambda s: s.free)
    since = mark(game)
    game.tap("START"); game.wait(40)
    entries, cursor = game.start_menu()
    target = next(i for i, (_, name) in enumerate(entries) if "SAUVER" in name)
    down = (target - cursor) % len(entries)
    if down:
        game.tap("DOWN", down); game.wait(10)
    game.tap("A")
    wait_text(game, "sauvegarder", since=since)
    wait_text(game, "NON", since=since)
    game.wait(30)
    log(game, f"{what}")
    shown = windows(game)
    texts = [" ".join(text.split()) for _, _, text in game.texts[since:]]
    game.tap("B"); game.wait(60)                       # NON : retour au menu Start
    after = windows(game)
    for _ in range(10):
        if game.state.free:
            break
        game.tap("B"); game.wait(30)
    wait_until(game, lambda s: s.free, limit=600)
    return shown, texts, after


def play(game):
    continue_game(game)
    for i in range(8):
        game.flag(f"FLAG_KANTO_BADGE0{i + 1}_GET", 1 if i < 3 else 0)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 0)
    game.warp("PalletTown", 9, 12); game.wait(30)

    game.dev("jeu.options", OPTION_MENU_STYLE, 0)
    hoenn, hoenn_texts, hoenn_after = save_window(game, "hoenn")
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    kanto, kanto_texts, kanto_after = save_window(game, "kanto sans pokedex")
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    kanto_dex, kanto_dex_texts, _ = save_window(game, "kanto pokedex")
    game.warp("LittlerootTown", 10, 10); game.wait(60)   # Hoenn
    littleroot, littleroot_texts, _ = save_window(game, "kanto a hoenn")
    hoenn_badges = sum(1 for i in range(8) if str(game.flag(f"FLAG_BADGE0{i + 1}_GET")).strip() in ("1", "True"))

    # Vérifications
    expect(game, (1, 1) in hoenn and hoenn[(1, 1)][0] == 14 and hoenn[(1, 1)][1] in (8, 10),
           f"MENUS = HOENN : fenêtre d'Émeraude 14 × 10 (ou 8) en 1, 1 ({hoenn})")
    expect(game, kanto.get((1, 1)) == (14, 9) and kanto_dex.get((1, 1)) == (14, 9),
           f"MENUS = KANTO : fenêtre de RF 14 × 9 en 1, 1 ({kanto}, {kanto_dex})")
    expect(game, any("BOURG PALETTE" in t for t in kanto_texts), "le lieu (BOURG PALETTE)")
    expect(game, any(t.startswith("DUREE JEU") for t in kanto_texts) and any(t == "BADGES" for t in kanto_texts),
           f"les libellés de RF ({kanto_texts})")
    expect(game, not any(t == "POKéDEX" for t in kanto_texts), "pas de ligne POKéDEX sans le Pokédex de Kanto")
    expect(game, any(t == "POKéDEX" for t in kanto_dex_texts), "ligne POKéDEX avec le Pokédex de Kanto")
    expect(game, any(re.match(r"^3\W?$", t) for t in kanto_texts), f"3 badges de Kanto ({kanto_texts})")
    expect(game, any(re.match(rf"^{hoenn_badges}\W?$", t) for t in littleroot_texts),
           f"à Hoenn : {hoenn_badges} badges de Hoenn ({littleroot_texts})")
    expect(game, (1, 1) not in hoenn_after and (1, 1) not in kanto_after, "fenêtre fermée après NON")
