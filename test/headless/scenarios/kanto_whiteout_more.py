# K.O. de RF, les cas de kanto_whiteout en plus (2026-11-03, docs/A-TESTER.md) :
# - K.O. par le poison hors combat (EventScript_FieldWhiteOut) : « panique et perd X¥ », X = l'argent retiré ;
# - avec les badges de la région : perte plus forte (sWhiteOutMoneyLossMultipliers), conseils courts de l'infirmière ;
# - sans argent : « n'a plus de POKéMON », sans perte ;
# - défaite contre un dresseur : « paye X¥ comme récompense », X = l'argent retiré ;
# - Mt. Cheminée (FLAG_WHITEOUT_TO_LAVARIDGE) : reprise au Centre de Vermilava ;
# - Centre de l'Île 1 : reprise devant son infirmière.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
sys.path.insert(0, os.path.dirname(driver.__file__))
from menu_helpers import texts
from matrix import talk_at

POISON = 8          # STATUS1_POISON


def said(game, since):
    return " ".join(t for _, t in texts(game, since))


def amount(text, words):
    found = re.search(words + r" (\d+)¥", text)
    return int(found.group(1)) if found else None


def heal_at(game, place):
    game.warp(*place); game.wait(30)
    talk_to(game, "UP")


def poison_white_out(game, map_name, x, y):
    """MAGICARPE empoisonné à 1 PV, des pas jusqu'au K.O. ; (textes, argent avant, argent après, carte d'arrivée)."""
    game.warp(map_name, x, y); game.wait(30)
    wait_until(game, lambda s: s.free)
    game.dev("joueur.pv", 0, 1)
    game.dev("joueur.statut", 0, POISON)
    money = game.money()
    since = mark(game)
    for i in range(40):
        game.press("RIGHT" if i % 2 == 0 else "LEFT", 16); game.wait(8)
        if saw_text(game, "plus de POKéMON", since):
            break
    finish_dialog(game, limit=200)
    return said(game, since), money, game.money(), game.state.map_name


def set_badges(game, prefix, count):
    for i in range(8):
        game.flag(f"{prefix}0{i + 1}_GET", int(i < count))


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_MAGIKARP", 2)              # perte : niveau 2 × 4 × multiplicateur des badges
    game.dev("jeu.rencontres", 0)
    set_badges(game, "FLAG_BADGE", 0)
    set_badges(game, "FLAG_KANTO_BADGE", 0)
    heal_at(game, ("ViridianCity_PokemonCenter_1F", 7, 4))

    # Poison, sans badge de Kanto : 2 × 4 × 2 = 16 ¥, conseils longs de l'infirmière
    game.money(10000)
    text, before, after, where = poison_white_out(game, "Route1", 12, 9)
    lost = amount(text, "panique et perd")
    game.note(f"poison, 0 badge : {lost} ¥ annoncés, {before - after} retirés, reprise {where}")
    expect(game, lost == 16 and before - after == 16, f"poison, 0 badge : 16 ¥ annoncés et retirés ({lost}, {before - after})")
    expect(game, where == "ViridianCity_PokemonCenter_1F", f"reprise au Centre de Jadielle ({where})")
    expect(game, "partir loin" in text, f"0 badge : les conseils longs de l'infirmière ({text[-80:]})")

    # Poison, 8 badges de Kanto : 2 × 4 × 30 = 240 ¥, conseils courts
    set_badges(game, "FLAG_KANTO_BADGE", 8)
    text, before, after, where = poison_white_out(game, "Route1", 12, 9)
    lost = amount(text, "panique et perd")
    expect(game, lost == 240 and before - after == 240, f"poison, 8 badges : 240 ¥ annoncés et retirés ({lost}, {before - after})")
    expect(game, "bonne chance" in text and "partir loin" not in text, f"8 badges : conseils courts ({text[-80:]})")

    # Sans argent : pas de perte
    game.money(0)
    text, before, after, where = poison_white_out(game, "Route1", 12, 9)
    expect(game, "plus de POKéMON" in text and "panique" not in text and after == 0,
           f"sans argent : « n'a plus de POKéMON », pas de perte ({text[:80]})")

    # Défaite contre un dresseur de Hoenn (0 badge de Hoenn) : « paye X¥ comme récompense »
    game.money(10000)
    heal_at(game, ("OldaleTown_PokemonCenter_1F", 7, 4))
    game.dev("joueur.pv", 0, 1)
    talk_at(game, "Route102", 33, 14)
    since = mark(game)
    before = game.money()
    for _ in range(80):
        if game.state.battle:
            break
        game.tap("A", hold=2, gap=4)
    fight_battle(game)
    finish_dialog(game, limit=200)
    text = said(game, since)
    lost = amount(text, "paye")
    expect(game, game.battles and game.battles[-1]["trainer"] and game.battles[-1]["outcome"] == "LOST",
           f"défaite contre un dresseur ({game.battles[-1:]})")
    expect(game, "comme récompense" in text and lost == 16 and before - game.money() == 16,
           f"dresseur : « paye 16¥ comme récompense », 16 retirés ({lost}, {before - game.money()})")
    expect(game, game.state.map_name == "OldaleTown_PokemonCenter_1F", f"reprise à Rosyères ({game.state.map_name})")

    # Mt. Cheminée : reprise au Centre de Vermilava
    game.flag("FLAG_WHITEOUT_TO_LAVARIDGE", 1)
    text, before, after, where = poison_white_out(game, "MtChimney", 28, 11)
    expect(game, where == "LavaridgeTown_PokemonCenter_1F", f"Mt. Cheminée : reprise à Vermilava ({where})")
    game.flag("FLAG_WHITEOUT_TO_LAVARIDGE", 0)

    # Île 1 : soins, puis K.O. sur l'île : reprise devant son infirmière
    game.var("VAR_KANTO_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F", 5)
    heal_at(game, ("OneIsland_PokemonCenter_1F", 5, 4))
    text, before, after, where = poison_white_out(game, "OneIsland", 10, 13)
    expect(game, where == "OneIsland_PokemonCenter_1F" and "ont été soignés" in text,
           f"Île 1 : reprise devant l'infirmière ({where}, {text[-60:]})")

    # Avant tout Centre : la chambre de Bourg Palette pose la reprise à la maison (HEAL_LOCATION_PALLET_TOWN, comme au
    # début d'une partie de RF) ; K.O. sur la Route 1 : retour devant la maison (la fusion n'y met pas de MAMAN :
    # reprise d'Émeraude, field_screen_effect.c), l'équipe soignée
    game.var("VAR_KANTO_MAP_SCENE_PALLET_TOWN_PLAYERS_HOUSE_2F", 0)
    game.warp("PalletTown_PlayersHouse_2F", 6, 6); game.wait(30)
    text, before, after, where = poison_white_out(game, "Route1", 12, 9)
    expect(game, (where, game.state.pos) == ("PalletTown", (6, 8)), f"avant tout Centre : devant la maison ({where} {game.state.pos})")
    species, level, hp, max_hp, status = game.state.party[0][:5]
    expect(game, hp == max_hp and status == 0, f"MAGICARPE soigné, sans poison ({hp}/{max_hp}, statut {status:#x})")
