# POKéDEX NATIONAL donné une seule fois (choix de l'utilisateur, 2026-11-03) : le PROF. SEKO (après la Ligue de Hoenn)
# et le PROF. CHEN (après la Ligue de Kanto, 60 POKéMON de Kanto, Île 1 visitée) ne le redonnent pas s'il est déjà là,
# sans casser la suite : chez SEKO, VAR_DEX_UPGRADE_JOHTO_STARTER_STATE passe à 2 et l'appel de SCOTT est armé
# (FLAG_SCOTT_CALL_BATTLE_FRONTIER) ; chez CHEN, la scène est finie (VAR_KANTO_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB
# = 9). Sans le POKéDEX NATIONAL, les deux scènes d'origine le donnent toujours.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import maps
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts


def said(game, since):
    return " ".join(t for _, t in texts(game, since))


def national(game):
    return "national 1" in game.dev("jeu.pokedex").splitlines()[0]


def clear_national(game):
    game.flag("FLAG_SYS_NATIONAL_DEX", 0)
    game.var("VAR_NATIONAL_DEX", 0)


def oak(game):
    """CHEN au labo, la Ligue de Kanto finie, 60 POKéMON de Kanto, Île 1 visitée : les textes jusqu'au retour."""
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 1)
    game.flag("FLAG_KANTO_WORLD_MAP_ONE_ISLAND", 1)
    game.flag("FLAG_KANTO_HIDE_OAK_IN_HIS_LAB", 0)
    game.flag("FLAG_KANTO_HIDE_RIVAL_IN_LAB", 1)       # BLUE est parti depuis le choix des starters (la scène l'ajoute)
    game.var("VAR_KANTO_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB", 6)
    game.warp("PalletTown_ProfessorOaksLab", 6, 4); game.wait(30)
    since = mark(game)
    talk_to(game, "UP", finish=False)
    finish_dialog(game, limit=1500)                     # la scène du POKéDEX NATIONAL est longue
    return said(game, since)


def birch(game):
    """Le retour au labo de SEKO après la Ligue de Hoenn (VAR_DEX_UPGRADE_JOHTO_STARTER_STATE = 1) : les textes."""
    game.var("VAR_DEX_UPGRADE_JOHTO_STARTER_STATE", 1)
    game.flag("FLAG_SCOTT_CALL_BATTLE_FRONTIER", 0)
    since = mark(game)
    group, num = maps.find_map("LittlerootTown_ProfessorBirchsLab")
    game.command("warp", group, num, 6, 5)
    game.wait(60)
    finish_dialog(game, limit=300)
    return said(game, since)


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_PIKACHU", 20)

    # Kanto, déjà reçu (à Hoenn) : CHEN note le POKéDEX, pas de 2e don, la scène est finie
    game.dev("jeu.pokedex", 151, 1)
    text = oak(game)
    expect(game, "POKéDEX NATIONAL est" in text and "Hum" not in text and "Bulbizarre" not in text,
           f"CHEN, national déjà reçu : la note seulement ({text[-120:]})")
    expect(game, "a été amélioré" not in text and "amélioré" not in text, f"CHEN : pas de 2e don ({text[-80:]})")
    expect_var(game, "VAR_KANTO_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB", 9)

    # Hoenn, déjà reçu (à Kanto) : SEKO le dit, la suite est armée
    text = birch(game)
    expect(game, "déjà fait" in text and "PROF. CHEN" in text, f"SEKO, national déjà reçu : il le dit ({text[:120]})")
    expect_var(game, "VAR_DEX_UPGRADE_JOHTO_STARTER_STATE", 2)
    expect_flag(game, "FLAG_SCOTT_CALL_BATTLE_FRONTIER", 1)

    # Sans le POKéDEX NATIONAL : SEKO le donne toujours (scène d'Émeraude)
    clear_national(game)
    expect(game, not national(game), "POKéDEX NATIONAL retiré pour la suite")
    text = birch(game)
    expect(game, national(game) and "déjà fait" not in text, f"SEKO, sans le national : il le donne ({text[-100:]})")
    expect_var(game, "VAR_DEX_UPGRADE_JOHTO_STARTER_STATE", 2)

    # Sans le POKéDEX NATIONAL : CHEN lance sa scène et le donne
    clear_national(game)
    text = oak(game)
    expect(game, national(game), f"CHEN, sans le national : il le donne ({text[-100:]})")
    expect_var(game, "VAR_KANTO_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB", 8)
