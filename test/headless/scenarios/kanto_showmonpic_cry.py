# showmonpic à Kanto (ScrCmd_showmonpic de RF, 2026-11-04), sauvegarde « kanto » : au panneau de la statue de
# LEVEINARD de Parmanie, l'image du Pokémon s'affiche et il crie (RF : PlayCry_Script dans showmonpic ; ses scripts
# n'ont pas de playmoncry). À Hoenn, showmonpic reste muet (Émeraude).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, finish_dialog, mark, wait_text, wait_until


def play(game):
    continue_game(game)
    game.warp("FuchsiaCity", 41, 11); game.wait(40)
    wait_until(game, lambda s: s.free)
    game.press("UP", 1); game.wait(20)
    cries = len(game.cries)
    since = mark(game)
    game.tap("A")
    wait_text(game, "LEVEINARD", since)
    game.wait(30)
    heard = [species for _, species in game.cries[cries:]]
    game.shot("statue")
    finish_dialog(game)
    game.note(f"cris : {heard}")
    expect(game, "SPECIES_CHANSEY" in heard, f"LEVEINARD crie avec son image ({heard})")
