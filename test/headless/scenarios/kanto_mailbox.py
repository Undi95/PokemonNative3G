# Boîte aux lettres du PC du joueur avec Options > MENUS = KANTO (2026-11-02) : fenêtres et liste de Rouge Feu
# (mailbox_pc.c) ; avec plus de 7 lettres, les flèches de défilement au milieu de la liste de RF
# (MailboxPC_AddScrollIndicatorArrows, x 0xC2 ; avant : 0xC8, le milieu de la liste d'Émeraude, 2 cases plus à droite).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until
from kanto_tour import log

OPTION_MENU_STYLE = 11   # jeu.options (src/debug_tools.c)
MAILS = 10


def arrows(game):
    """Les flèches de défilement visibles : (x, y) des sprites en haut (y 12) et en bas (y 148) de la liste."""
    out = []
    for line in game.dev("gfx.sprites").splitlines():
        m = re.match(r"sprite \d+ en (-?\d+),(-?\d+) ", line)
        if m and int(m.group(2)) in (12, 148) and " invisible" not in line:
            out.append((int(m.group(1)), int(m.group(2))))
    return sorted(out)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)   # la sauvegarde « kanto » n'a pas d'équipe
    game.wait(30)
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    sent = [game.dev("joueur.lettre", 0, names.number("ITEM_ORANGE_MAIL"), 2) for _ in range(MAILS)]
    game.warp("ViridianCity_PokemonCenter_1F", 11, 2); game.wait(30)
    wait_until(game, lambda s: s.free)
    game.press("UP", 4); game.wait(20)
    game.tap("A"); game.wait(120); game.tap("A"); game.wait(90); log(game, "menu pc")
    game.tap("DOWN"); game.wait(20); game.tap("A")
    since = mark(game)
    for _ in range(10):   # « PC personnel connecté. » puis le menu du PC du joueur
        game.tap("A"); game.wait(40)
        if saw_text(game, "BOITE LETTRE", since):
            break
    game.wait(30); log(game, "pc joueur")
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(120); log(game, "boite aux lettres")
    first = arrows(game)
    game.tap("DOWN", MAILS, gap=12); game.wait(60); log(game, "bas de la liste")   # sur ANNULER
    scrolled = arrows(game)
    game.tap("B"); game.wait(60); log(game, "retour au pc")

    # Vérifications
    expect(game, all("envoyee au PC" in r for r in sent), f"{MAILS} lettres envoyées au PC ({sent[-1].strip()})")
    expect(game, first == [(0xC2, 148)], f"flèche du bas au milieu de la liste de RF ({first})")
    expect(game, scrolled == [(0xC2, 12)], f"en bas : flèche du haut au milieu de la liste de RF ({scrolled})")
