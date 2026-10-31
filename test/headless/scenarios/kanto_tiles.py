# Tuiles de Rouge Feu perdues à l'import et rétablies (tools/kanto_tile_attributes.py, 2026-10-31) :
# objets d'intérieur à examiner (placard, lampes, machine, bibliothèque et télé de Kanto), dalle tournante de l'Arène de
# Jadielle (le joueur glisse jusqu'à la dalle d'arrêt), rencontres sur le sable du Mt. Moon (type de rencontre de RF).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, fight_battle, mark, saw_text, wait_until
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log

# (carte, case d'où l'on regarde vers le haut, texte de RF attendu) ; tuiles sans événement de carte
FURNITURE = (("PalletTown_RivalsHouse", 2, 2, "De la vaisselle est rangée"),
             ("PalletTown_RivalsHouse", 5, 2, "Une émission avec des POKéMON"),
             ("PalletTown_ProfessorOaksLab", 1, 2, "Il y a plein de petites lampes"),
             ("PalletTown_ProfessorOaksLab", 1, 6, "A quoi ça peut bien servir"),
             ("PalletTown_ProfessorOaksLab", 10, 2, "Des bouquins sur les POKéMON"))


def examine(game, map_name, x, y):
    """Regarde vers le haut depuis (x, y) et appuie sur A, puis referme le message."""
    game.warp(map_name, x, y); game.wait(30)
    game.tap("UP"); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(90)
    for _ in range(10):
        if game.state.free:
            break
        game.tap("A"); game.wait(30)
    return [t for _, _w, t in game.texts[since:]]


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)   # la sauvegarde de test arrive à Kanto sans équipe

    # Objets d'intérieur (field_control_avatar.c, flavor_text.inc de RF)
    seen = {}
    for map_name, x, y, words in FURNITURE:
        seen[words] = any(words in t for t in examine(game, map_name, x, y))
    wait_until(game, lambda s: s.free)

    # Dalle tournante : un pas à gauche sur la dalle (13, 22), glissade jusqu'à la dalle d'arrêt (1, 22)
    game.warp("ViridianCity_Gym", 14, 22); game.wait(30)
    game.press("LEFT", 16); game.wait(20)
    log(game, "glissade")
    wait_until(game, lambda s: s.free and s.pos == (1, 22), limit=300)
    spin_end = game.state.pos

    # Sable du Mt. Moon : rencontres en allant et venant sur (21, 2) - (22, 2)
    game.warp("MtMoon_1F", 21, 2); game.wait(30)
    met = False
    for _ in range(150):
        game.press("RIGHT", 16); game.wait(4)
        game.press("LEFT", 16); game.wait(4)
        if game.state.battle:
            met = True
            break
    tile = game.state.pos
    if met:
        fight_battle(game)

    # Vérifications
    for _m, _x, _y, words in FURNITURE:
        expect(game, seen[words], f"texte « {words} »")
    expect(game, spin_end == (1, 22), f"glissade jusqu'à la dalle d'arrêt (1, 22) (arrêt en {spin_end})")
    expect(game, met, f"rencontre sur le sable du Mt. Moon ({tile})")
