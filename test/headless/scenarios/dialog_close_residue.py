# Boîte de dialogue fermée sans reste (2026-11-03, docs/A-TESTER.md) : avec DIALOGUE = HOENN puis KANTO, l'écran
# après la boîte (télé de la maison de Bourg Palette, un intérieur sans tuiles animées) est le même qu'avant : pas de
# morceau de cadre ni de texte laissé sur la carte.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from PIL import Image, ImageChops

OPTION_DIALOG_STYLE = 8


def play(game):
    continue_game(game)
    for style, name in ((0, "hoenn"), (1, "kanto")):
        game.dev("jeu.options", OPTION_DIALOG_STYLE, style)
        game.warp("PalletTown_PlayersHouse_1F", 6, 2); game.wait(30)
        game.press("UP", 1); game.wait(30)
        before = Image.open(game.shot(f"avant-{name}")).convert("RGB")
        since = mark(game)
        talk_to(game, "UP")
        game.wait(30)
        after = Image.open(game.shot(f"apres-{name}")).convert("RGB")
        diff = ImageChops.difference(before, after).getbbox()
        expect(game, saw_text(game, "", since) and len(game.texts) > since, f"{name} : la télé parle")
        expect(game, diff is None, f"DIALOGUE = {name.upper()} : écran identique après la boîte (différence : {diff})")
