# Pension de l'Île 4 (2026-11-03, docs/A-TESTER.md), celle d'Émeraude (deux POKéMON) : ZIGZATON N.2 déposé avec une
# LETTRE ORANGE, des pas (1 point d'expérience chacun), puis repris : il a pris des niveaux, le prix est
# 100¥ + 100¥ par niveau (GetDaycareCost), et il revient avec sa lettre (la pension la garde : daycare mail).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts

LADY_SPOT = (2, 4)


def party(game):
    """[(espèce, niveau, objet tenu), ...]"""
    return [(int(s), int(l), int(i)) for s, l, i in
            re.findall(r"espece (\d+) N\.(\d+) PV \d+/\d+ statut \S+ objet (\d+)", game.dev("joueur.equipe"))]


def joined(game, since):
    return " ".join(t for _, t in texts(game, since))


def talk_lady(game):
    game.warp("FourIsland_PokemonDayCare", *LADY_SPOT); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(60)
    return since


def play(game):
    continue_game(game)
    game.var("VAR_KANTO_MAP_SCENE_FOUR_ISLAND", 1)      # scène du rival déjà vue
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_PIKACHU", 10)
    game.give_mon("SPECIES_ZIGZAGOON", 2)
    game.dev("joueur.lettre", 1, names.number("ITEM_ORANGE_MAIL"))
    game.money(10000)
    before = party(game)

    # Dépôt : OUI, puis le 2e POKéMON de l'équipe, puis NON (pas un autre)
    since = talk_lady(game)
    for _ in range(20):
        if "PartyMenu" in game.function(game.state.cb2):
            break
        game.tap("A"); game.wait(40)
    game.wait(60)
    game.tap("DOWN"); game.wait(20)
    game.tap("A"); game.wait(120)
    finish_dialog(game, answers={"autre": "B"})
    deposit = joined(game, since)
    after_deposit = party(game)

    # Des pas sur l'île
    game.warp("FourIsland", 16, 20); game.wait(40)
    for i in range(220):
        game.press("LEFT" if i % 2 == 0 else "RIGHT", 16); game.wait(2)

    # Retrait
    money = game.money()
    since = talk_lady(game)
    finish_dialog(game, answers={"autre": "B"})          # pas un autre : elle propose de le reprendre
    withdraw = joined(game, since)
    after = party(game)
    paid = money - game.money()
    game.note(f"pension : {before} -> {after_deposit} -> {after}, payé {paid}")

    zigzagoon = [m for m in after if m[0] == names.number("SPECIES_ZIGZAGOON")]
    levels = zigzagoon[0][1] - 2 if zigzagoon else 0
    expect(game, len(after_deposit) == 1, f"ZIGZATON déposé ({after_deposit} ; {deposit[-120:]})")
    expect(game, zigzagoon and levels >= 2, f"il a grandi ({zigzagoon})")
    expect(game, paid == 100 + 100 * levels, f"prix : 100 + 100 x {levels} niveaux = {100 + 100 * levels} ({paid})")
    expect(game, zigzagoon and zigzagoon[0][2] == names.number("ITEM_ORANGE_MAIL"),
           f"revenu avec sa LETTRE ORANGE ({zigzagoon} ; {withdraw[-120:]})")
