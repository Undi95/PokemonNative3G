# Fan Club des Dresseurs de Safrania (2026-11-03, docs/A-TESTER.md ; kanto_trainer_fan_club.c, trainer_fan_club.c de
# RF) :
# - avant la Ligue : les membres parlent des dresseurs en général ;
# - Ligue de Kanto finie (EventScript_SetDefeatedEliteFourFlagsVars) : 3 fans (membres 1 à 3), les autres membres
#   arrivent ; en entrant, la rencontre (« C'est toi, … ! ») ;
# - fans gagnés : Script_TryGainNewFanFromCounter (victoire contre PETER, +2) à 20 et moins de 3 fans : un fan de plus ;
# - fans perdus : avec 5 fans ou plus, un de moins toutes les 12 h de jeu (en entrant) ;
# - noms : un membre qui n'est plus fan parle du rival (nom du rival de Kanto, STR_VAR_1).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import maps
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts

CRUSH_GIRL = (7, 14, "UP")       # membre 1, en (7, 13)


def said(game, since):
    return " ".join(t for _, t in texts(game, since))


def fan_club(game):
    """(compteur, gotInitialFans, drapeaux des fans) : VAR_KANTO_FANCLUB_FAN_COUNTER (struct TrainerFanClub de RF)."""
    value = game.var("VAR_KANTO_FANCLUB_FAN_COUNTER")
    return value & 0x7F, value >> 7 & 1, value >> 8


def fans(game):
    return bin(fan_club(game)[2]).count("1")


def enter(game):
    """Entre dans le Fan Club (warp de la porte) : la carte se charge, scripts d'entrée compris."""
    since = mark(game)
    group, num = maps.find_map("SaffronCity_PokemonTrainerFanClub")
    game.command("warp", group, num, 5, 14)
    game.wait(60)
    finish_dialog(game)
    return said(game, since)


def talk(game, spot):
    x, y, direction = spot
    game.warp("SaffronCity_PokemonTrainerFanClub", x, y); game.wait(30)
    since = mark(game)
    talk_to(game, direction)
    return said(game, since)


def play(game):
    continue_game(game)
    game.var("VAR_KANTO_FANCLUB_FAN_COUNTER", 0)
    game.var("VAR_KANTO_FANCLUB_LOSE_FAN_TIMER", 0)
    game.var("VAR_KANTO_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB", 0)

    # Avant la Ligue de Kanto
    before = talk(game, CRUSH_GIRL)
    expect(game, "siiiii cool" in before, f"avant la Ligue : les DRESSEURS en général ({before[-80:]})")

    # La Ligue finie : 3 fans, la rencontre en entrant
    game.special("Script_UpdateTrainerFanClubGameClear")      # EventScript_SetDefeatedEliteFourFlagsVars (Panthéon)
    expect(game, fan_club(game) == (0, 1, 0b111), f"Ligue finie : 3 fans, membres 1 à 3 ({fan_club(game)})")
    expect_var(game, "VAR_KANTO_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB", 1)
    meeting = enter(game)
    expect(game, "C'est toi" in meeting.replace("’", "'") and "On parlait justement de toi" in meeting,
           f"la rencontre des premiers fans ({meeting[-100:]})")
    expect_var(game, "VAR_KANTO_MAP_SCENE_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB", 2)
    fan = talk(game, CRUSH_GIRL)
    expect(game, "Je te soutiendrai toujours" in fan, f"membre 1, fan : « Je te soutiendrai toujours » ({fan[-80:]})")

    # Fans gagnés : avec 1 fan et le compteur à 19, la victoire contre PETER (+2) en donne un
    game.var("VAR_KANTO_FANCLUB_FAN_COUNTER", 0x80 | 19 | (0b1 << 8))
    game.special("Script_TryGainNewFanFromCounter", 0)
    expect(game, fans(game) == 2 and fan_club(game)[0] == 0, f"fan gagné : 2 fans, compteur à 0 ({fan_club(game)})")
    # Avec 3 fans, pas de fan de plus (le compteur reste à 20)
    game.var("VAR_KANTO_FANCLUB_FAN_COUNTER", 0x80 | 19 | (0b111 << 8))
    game.special("Script_TryGainNewFanFromCounter", 0)
    expect(game, fans(game) == 3 and fan_club(game)[0] == 20, f"3 fans : pas de plus, compteur 20 ({fan_club(game)})")

    # Fans perdus : les 8 fans, 25 h de jeu depuis le dernier compte : 2 de moins en entrant (toutes les 12 h)
    game.var("VAR_KANTO_FANCLUB_FAN_COUNTER", 0x80 | (0xFF << 8))
    game.dev("jeu.duree", 30)
    game.var("VAR_KANTO_FANCLUB_LOSE_FAN_TIMER", 5)
    enter(game)
    expect(game, fans(game) == 6, f"25 h : 2 fans perdus ({fans(game)} fans, {fan_club(game)})")
    expect_var(game, "VAR_KANTO_FANCLUB_LOSE_FAN_TIMER", 29)

    # Noms : le membre 1 n'est plus fan ; à l'entrée, il va à la table du fond (MoveMember1ToFarTable : 5, 2) et parle
    # du rival
    game.var("VAR_KANTO_FANCLUB_FAN_COUNTER", 0x80 | (0b110 << 8))
    former = talk(game, (5, 3, "UP"))
    game.note(f"ancien fan : {former}")
    expect(game, "plus" in former and "D'ailleurs, je trouve que BLUE" in former.replace("’", "'"),
           f"membre 1, plus fan : il parle du rival BLUE ({former[-120:]})")
