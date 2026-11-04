# Sac sans limite (décision du user, 2026-11-04 ; constants/global.h BIG_BAG_*), sauvegarde « kanto » (la reprise
# d'un ancien sac est dans bag_old_save) :
# - tous les objets de la poche Objets (140 différents), 1 de chaque ;
# - 20 000 POTIONS (des lignes de 99 : plus de 160 lignes, la limite d'avant) et 5 000 POKé BALLS (16 places avant) ;
# - CT et Baies : une seule ligne par objet (BOITE CT, BOITE BAIES de RF) : 99 CT01 puis une de plus refusée,
#   999 BAIES CERISE puis une de plus refusée ;
# - le sac d'Émeraude puis celui de RF (SAC = KANTO) s'ouvrent sur ces poches, défilent jusqu'en bas ;
# - sauvegarde, redémarrage : tout est encore là (nouveau bloc du sac).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, save, wait_until
from kanto_tour import log
from menu_helpers import open_start_entry, press_until_free, bag

OPTION_BAG_STYLE = 13
ITEMS_H = os.path.join(os.path.dirname(driver.__file__), '..', '..', 'src', 'data', 'items.h')


def pocket_items(pocket):
    """Les objets de src/data/items.h rangés dans cette poche (POCKET_ITEMS…), sans les places vides d'Émeraude
    (nom « ???????? »)."""
    text = open(ITEMS_H, encoding='utf-8').read()
    found = []
    parts = re.split(r'\n    \[(ITEM_\w+)\] =', text)
    for name, body in zip(parts[1::2], parts[2::2]):
        if (re.search(r'\.pocket\s*=\s*' + pocket + r'\b', body) and name != "ITEM_NONE"
                and '_("????????")' not in body):
            found.append(name)
    return found


def lines(game, pocket, item=None):
    rows = bag(game).get(pocket, [])
    return [r for r in rows if item is None or r[0] == names.number(item)]


def scroll_bag(game, what):
    """Le sac ouvert : la poche Objets (1re), défilée jusqu'en bas ; capture."""
    open_start_entry(game, "SAC"); game.wait(240)
    game.tap("LEFT", 5, gap=30); game.wait(60)
    for _ in range(40):
        game.press("DOWN", 30); game.wait(2)
    game.wait(30)
    log(game, what)
    press_until_free(game)


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)

    # Tous les objets de la poche Objets, 1 de chaque
    all_items = pocket_items("POCKET_ITEMS")
    refused = [n for n in all_items if int(game.item(n, 1)) < 1]
    distinct = {r[0] for r in lines(game, "poche 1")}

    # Beaucoup d'un même objet : des lignes de 99
    potions = int(game.item("ITEM_POTION", 20000))
    potion_lines = lines(game, "poche 1", "ITEM_POTION")
    item_lines = len(lines(game, "poche 1"))
    balls_before = int(game.item("ITEM_POKE_BALL"))
    balls = int(game.item("ITEM_POKE_BALL", 5000))
    ball_lines = lines(game, "poche 2", "ITEM_POKE_BALL")

    # CT et Baies : une seule ligne
    tm = int(game.item("ITEM_TM01"))
    if tm < 99:
        tm = int(game.item("ITEM_TM01", 99 - tm))
    tm_more = int(game.item("ITEM_TM01", 1))
    berry = int(game.item("ITEM_CHERI_BERRY"))
    if berry < 999:
        berry = int(game.item("ITEM_CHERI_BERRY", 999 - berry))
    berry_more = int(game.item("ITEM_CHERI_BERRY", 1))

    # Les deux sacs
    game.warp("PalletTown", 9, 12); game.wait(30)
    scroll_bag(game, "sac hoenn")
    game.dev("jeu.options", OPTION_BAG_STYLE, 1)        # SAC = KANTO
    scroll_bag(game, "sac kanto")
    game.dev("jeu.options", OPTION_BAG_STYLE, 0)

    # Sauvegarde, redémarrage
    save(game)
    game.press("A+B+START+SELECT", 1)
    continue_game(game)
    after = bag(game)

    # Vérifications
    expect(game, not refused and set(names.number(n) for n in all_items) <= distinct,
           f"les {len(all_items)} objets de la poche Objets, 1 de chaque (refusés : {refused[:5]})")
    expect(game, potions >= 20000 and len(potion_lines) >= 20000 // 99 and all(q <= 99 for _, _, q in potion_lines)
           and item_lines > 160,
           f"20 000 POTIONS en lignes de 99 ({potions}, {len(potion_lines)} lignes ; {item_lines} lignes, 160 avant)")
    expect(game, balls == balls_before + 5000 and len(ball_lines) > 16,
           f"5 000 POKé BALLS ({balls}, {len(ball_lines)} lignes, 16 places avant)")
    expect(game, tm == 99 and tm_more == 99 and len(lines(game, "poche 3", "ITEM_TM01")) == 1,
           f"CT01 : une seule ligne, la 100e refusée ({tm}, {tm_more})")
    expect(game, berry == 999 and berry_more == 999 and len(lines(game, "poche 4", "ITEM_CHERI_BERRY")) == 1,
           f"BAIE CERISE : une seule ligne, la 1000e refusée ({berry}, {berry_more})")
    total = lambda b, item: sum(q for n, _, q in b.get("poche 1", []) + b.get("poche 2", []) if n == names.number(item))
    expect(game, total(after, "ITEM_POTION") == potions and total(after, "ITEM_POKE_BALL") == balls
           and len({r[0] for r in after.get("poche 1", [])}) == len(distinct),
           f"après redémarrage : tout est là (POTIONS {total(after, 'ITEM_POTION')}, BALLS {total(after, 'ITEM_POKE_BALL')})")
