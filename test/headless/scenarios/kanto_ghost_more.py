# Combats contre un SPECTRE sans SCOPE SYLPHE (docs/A-TESTER.md, 2026-11-03 ; Tour Pokémon) :
# - une Poké Ball lancée sur un SPECTRE (3e étage) : « Il a évité la BALL! » (BattleScript_GhostBallDodge), la Ball
#   est perdue, le combat continue ; puis FUITE ;
# - OSSATUEUR (6e étage, case (11, 15)) : SPECTRE non identifié, FUITE, le joueur est repoussé d'un pas vers le haut
#   et la scène reste à faire (VAR_KANTO_MAP_SCENE_POKEMON_TOWER_6F = 0) ;
# - le Pokédex ne marque pas « vu » un SPECTRE non révélé (le nombre de vus ne change pas).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import re

OPTION_BAG = 13


def seen(game):
    return int(re.search(r"national : vus (\d+)", game.dev("jeu.pokedex")).group(1))


def menu_ready(game, since):
    for _ in range(30):
        if saw_text(game, "Que doit faire", since):
            return
        game.tap("A"); game.wait(40)


def run_away(game):
    for _ in range(10):
        if game.state.free or not game.state.battle:
            break
        game.tap("DOWN"); game.wait(20); game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(300)
    for _ in range(20):
        if game.state.free:
            break
        game.tap("A"); game.wait(40)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.item("ITEM_SILPH_SCOPE", 0)
    game.item("ITEM_POKE_BALL", 5)
    game.dev("jeu.options", OPTION_BAG, 1)              # sac de RF en combat : les Balls en 3e poche
    seen_before = seen(game)

    # Tour Pokémon 3e étage : un SPECTRE, une POKé BALL
    game.warp("PokemonTower_3F", 10, 7); game.wait(30)
    since = mark(game)
    for _ in range(200):
        if game.state.battle:
            break
        game.press("LEFT", 16); game.press("RIGHT", 16)
    menu_ready(game, since)
    balls = game.item("ITEM_POKE_BALL")
    game.wait(30)
    game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(240)          # SAC
    game.tap("RIGHT", 2, gap=90); game.wait(60)                              # Balls
    game.tap("A"); game.wait(60); game.tap("A")                              # UTILISER
    wait_text(game, "évité la BALL", since=since, limit=900)
    menu_ready(game, mark(game))                                             # le tour du SPECTRE, puis le menu
    game.wait(60)
    run_away(game)
    expect_text(game, "Le SPECTRE ne peut être identifié", since)
    expect_text(game, "Il a évité la BALL", since)
    expect(game, game.item("ITEM_POKE_BALL") == balls - 1, f"la Ball est perdue ({balls} -> {game.item('ITEM_POKE_BALL')})")

    # Tour Pokémon 6e étage : OSSATUEUR sans SCOPE SYLPHE
    game.var("VAR_KANTO_MAP_SCENE_POKEMON_TOWER_6F", 0)
    game.warp("PokemonTower_6F", 11, 14); game.wait(30)
    since = mark(game)
    game.press("DOWN", 16)
    for _ in range(40):
        if game.state.battle:
            break
        game.tap("A"); game.wait(30)
    menu_ready(game, since)
    run_away(game)
    wait_until(game, lambda s: s.free, limit=900)
    game.wait(60)
    game.note(f"OSSATUEUR : après la fuite en {game.state.pos}")
    expect_text(game, "Le SPECTRE ne peut être identifié", since)
    expect(game, game.state.pos == (11, 14), f"repoussé d'un pas vers le haut ({game.state.pos})")
    expect_var(game, "VAR_KANTO_MAP_SCENE_POKEMON_TOWER_6F", 0)

    expect(game, seen(game) == seen_before, f"SPECTRES non révélés pas « vus » au Pokédex ({seen_before} -> {seen(game)})")
