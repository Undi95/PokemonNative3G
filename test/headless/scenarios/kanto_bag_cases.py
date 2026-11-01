# Build KANTO_DEBUG=1 : option SAC = KANTO, objets du debug, puis SELECT dans les Objets rares du sac de Rouge Feu :
# la Boîte à CT et le Sac à Baies (toujours en tête, EnsureCases) ne se déplacent pas, et un objet posé au-dessus
# d'eux va juste après (2026-10-31).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from redleaf_acro import close_menus
from driver import mark, saw_text, wait_until

MOVE = "Où voulez-vous placer"


def list_order(game, since):
    """Les objets de la poche, dans l'ordre où la liste vient d'être affichée."""
    names = [t for _, w, t in game.texts[since:] if w == 0 and t.strip() and not t.startswith("×")]
    return names


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    # Options > SAC = KANTO
    game.tap("START"); game.wait(30); game.tap("UP"); game.wait(10); game.tap("UP"); game.wait(10); game.tap("A"); game.wait(120)
    game.tap("R"); game.wait(30); game.tap("DOWN", 6, gap=10); game.wait(30); game.tap("RIGHT"); game.wait(60); game.tap("B"); game.wait(120)
    close_menus(game)
    # DEBUG > objets (le menu Start se rouvre sur OPTIONS)
    game.tap("START"); game.wait(30); game.tap("UP", 4, gap=10); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    # Sac > Objets rares, curseur sur la Boîte à CT
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(200)
    since = mark(game)
    game.tap("RIGHT"); game.wait(90)
    top = list_order(game, since)[:2]
    case_select = mark(game)
    game.tap("SELECT"); game.wait(40)
    case_moved = saw_text(game, MOVE, case_select)
    game.tap("DOWN"); game.wait(20)
    game.tap("SELECT"); game.wait(40)
    pouch_moved = saw_text(game, MOVE, case_select)
    # Le 4e objet, posé tout en haut
    game.tap("DOWN", 2, gap=20); game.wait(20)
    picked = mark(game)
    game.tap("SELECT"); game.wait(40)
    moving = [t for _, _w, t in game.texts[picked:] if MOVE in t]
    item = moving[0].split("\n")[1].rstrip("?") if moving else None
    game.tap("UP", 3, gap=20); game.wait(20)
    dropped = mark(game)
    game.tap("SELECT"); game.wait(60)
    log(game, "objet posé sous les boîtes")
    order = list_order(game, dropped)
    close_menus(game)

    # Vérifications
    expect(game, top == ["BOITE CT", "SAC A BAIES"], f"boîtes en tête des Objets rares ({top})")
    expect(game, not case_moved, "SELECT ne déplace pas la Boîte à CT")
    expect(game, not pouch_moved, "SELECT ne déplace pas le Sac à Baies")
    expect(game, item is not None, "SELECT déplace un autre objet")
    expect(game, order[:3] == ["BOITE CT", "SAC A BAIES", item], f"objet posé juste après les boîtes ({order[:4]})")
