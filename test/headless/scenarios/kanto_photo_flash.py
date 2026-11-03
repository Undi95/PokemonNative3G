# Flash de la photo du Casino de Céladopole (FLDEFF_PHOTO_FLASH de RF, 2026-11-03, docs/A-TESTER.md) : après
# « Un… Deux… Et trois ! », l'écran blanchit au son MUS_RG_PHOTO puis revient en une dizaine d'images. Le script ne
# l'attend pas (pas de waitfieldeffect) : la luminosité moyenne de l'écran est mesurée toutes les 2 images.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, wait_text, wait_until
from kanto_card_stickers import press_until_text
from PIL import Image


def brightness(game, name):
    image = Image.open(game.shot(name)).convert("L")
    return sum(image.getdata()) / (image.width * image.height)


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.money(1000)
    game.warp("CeladonCity_GameCorner", 16, 13); game.wait(30)
    before = brightness(game, "avant")
    since = mark(game)
    game.tap("RIGHT"); game.wait(10); game.tap("A")
    wait_text(game, "IMPRIMANTE", since)
    press_until_text(game, "Veuillez choisir", since)
    wait_text(game, "SEPIA", since)
    game.wait(30)
    game.tap("A")                                      # impression normale
    wait_text(game, "Et trois", since)
    sounds = len(game.sounds)
    wait_until(game, lambda s: any(sound == "MUS_RG_PHOTO" for _, sound in game.sounds[sounds:]), step=1, limit=900)
    peak = brightness(game, "son")                     # le flash part avec le son
    levels = []
    for n in range(30):
        game.wait(2)
        levels.append(round(brightness(game, f"flash_{n:02}")))
    game.note(f"luminosité : avant {before:.0f}, au son {peak:.0f}, ensuite {levels}")
    finish_dialog(game)
    after = brightness(game, "apres")

    # Vérifications
    settled = levels[-1]                               # l'écran du message, après le flash
    expect(game, peak > settled + 60, f"le flash blanchit l'écran ({peak:.0f}, puis {settled})")
    expect(game, levels == sorted(levels, reverse=True) and levels[-10:] == [settled] * 10,
           f"puis s'efface ({levels})")
    expect(game, abs(after - before) < 5, f"l'écran revient comme avant ({before:.0f} -> {after:.0f})")
