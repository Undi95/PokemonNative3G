# K.O. à Kanto comme dans Rouge Feu (2026-10-31) : perte d'argent annoncée en combat (« panique et perd X¥ ») et égale à
# celle retirée, reprise devant l'infirmière du dernier Centre visité (message sur fond noir, puis soins), Ligue de Kanto
# et Piste Cyclable remises à zéro. Dernier soin à Hoenn (celui de la sauvegarde de test) : reprise d'Émeraude.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, fight_battle, finish_dialog, mark, talk_to, wait_until
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log


def lose_wild_battle(game):
    """Sur le sable du Mt. Moon, jusqu'à une rencontre, perdue avec Magicarpe (Trempette)."""
    game.warp("MtMoon_1F", 21, 2); game.wait(30)
    for _ in range(150):
        game.press("RIGHT", 16); game.wait(4)
        game.press("LEFT", 16); game.wait(4)
        if game.state.battle:
            break
    since = mark(game)
    money = game.money()
    fight_battle(game)
    return since, money


def lost_money(game, since):
    found = [re.search(r"perd (\d+)¥", t) for _, _w, t in game.texts[since:]]
    found = [int(m.group(1)) for m in found if m]
    return found[0] if found else None


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MAGIKARP", 2)   # la sauvegarde de test arrive à Kanto sans équipe
    game.money(10000)

    # 1. Dernier soin à Hoenn (sauvegarde de test) : reprise d'Émeraude, sans le message de RF
    since, _ = lose_wild_battle(game)
    first_map = game.state.map_name
    first_rf_text = saw_text(game, "se hâte vers un CENTRE", since)
    finish_dialog(game)

    # 2. Soins à Jadielle, puis K.O. avec la Ligue et la Piste Cyclable en cours
    game.warp("ViridianCity_PokemonCenter_1F", 7, 4); game.wait(30)
    talk_to(game, "UP")
    game.flag("FLAG_KANTO_DEFEATED_LORELEI", 1)
    game.flag("FLAG_KANTO_SYS_ON_CYCLING_ROAD", 1)
    since, money = lose_wild_battle(game)
    lost = lost_money(game, since)
    after = game.money()
    respawn = (game.state.map_name, game.state.pos)
    scurried = wait_text(game, "se hâte vers un CENTRE", since)
    game.wait(180)   # fin de l'affichage
    log(game, "message de reprise")
    finish_dialog(game)   # A : le message se termine sur une attente de touche
    nurse = saw_text(game, "Avant toute chose", since)
    healed = saw_text(game, "ont été soignés", since)

    # Vérifications
    expect(game, first_map == "PetalburgCity", f"dernier soin à Hoenn, reprise d'Émeraude ({first_map})")
    expect(game, not first_rf_text, "dernier soin à Hoenn, pas de message de RF")
    expect(game, lost is not None and lost > 0, f"perte annoncée en combat ({lost})")
    expect(game, lost == money - after, f"perte annoncée = perte réelle ({lost} / {money} -> {after})")
    expect(game, respawn == ("ViridianCity_PokemonCenter_1F", (7, 4)), f"reprise devant l'infirmière de Jadielle ({respawn})")
    expect(game, scurried, "message « se hâte vers un CENTRE POKéMON »")
    expect(game, nurse and healed, "l'infirmière soigne l'équipe")
    expect_flag(game, "FLAG_KANTO_DEFEATED_LORELEI", 0)
    expect_flag(game, "FLAG_KANTO_SYS_ON_CYCLING_ROAD", 0)
