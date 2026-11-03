# Braille avec Options > DIALOGUE = HOENN (docs/A-TESTER.md, 2026-11-03) : comme dans Émeraude, pas de flèche d'attente
# au bout du message braille ; avec DIALOGUE = KANTO, la flèche de RF (CreateTextCursorSprite) est un sprite de plus.
# Chemin Rubis du Mont Braise (braille de Kanto) ; captures « braille-STYLE ».
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)

OPTION_DIALOGUE = 8


def sprites(game):
    return [l for l in game.dev("gfx.sprites").splitlines() if l.startswith("sprite")]


def read(game, style):
    game.dev("jeu.options", OPTION_DIALOGUE, style)
    game.warp("MtEmber_RubyPath_B5F", 7, 3); game.wait(30)
    finish_dialog(game, settle=20)
    before = sprites(game)
    game.press("UP", 4); game.wait(20)
    game.tap("A"); game.wait(150)
    shown = sprites(game)
    game.shot(f"braille-{'kanto' if style else 'hoenn'}")
    for _ in range(20):
        if game.state.free:
            break
        game.tap("A"); game.wait(60)
    return len(shown) - len(before)


def play(game):
    continue_game(game)
    hoenn = read(game, 0)
    kanto = read(game, 1)
    game.note(f"SPRITES EN PLUS : HOENN {hoenn}, KANTO {kanto}")
    expect(game, kanto == hoenn + 1, f"la flèche de RF seulement avec DIALOGUE = KANTO ({hoenn}, {kanto})")
