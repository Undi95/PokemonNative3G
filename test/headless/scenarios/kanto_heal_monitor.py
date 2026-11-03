# Centre Pokémon de Kanto (docs/A-TESTER.md, 2026-11-03) : pendant le soin, le moniteur de RF (32x16, 4 images,
# field_effect.c) clignote au-dessus de la machine ; captures « soin-N » toutes les 8 images à revoir, et l'image du
# sprite du moniteur change (gfx.sprites).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import re


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.heal()
    game.warp("ViridianCity_PokemonCenter_1F", 7, 4); game.wait(30)
    since = len(game.sounds)
    talk_to(game, "UP", finish=False)
    for _ in range(30):                                     # jusqu'au début du soin (les Poké Balls sur la machine)
        if any("HEAL" in s or "BALL" in s for _, s in game.sounds[since:]):
            break
        game.tap("A"); game.wait(30)
    sprites = set()
    for i in range(12):
        game.shot(f"soin-{i}")
        sprites.add(game.dev("gfx.sprites"))
        game.wait(8)
    finish_dialog(game)
    game.note(f"SONS {[s for _, s in game.sounds[since:]]}")
    expect(game, len(sprites) >= 3, f"les sprites changent pendant le soin ({len(sprites)} états)")
