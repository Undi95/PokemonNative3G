# ZARBI des Ruines de Tanoby (docs/A-TESTER.md, 2026-11-03) : une rencontre dans chacune des 7 chambres, la lettre lue
# dans la personnalité (GET_UNOWN_LETTER) est une de celles de la chambre (sUnownLetterSlots de wild_encounter.c) et le
# sprite en combat la montre (captures « combat-CHAMBRE-LETTRE » à revoir) ; le Pokédex de RF montre le ZARBI du
# premier vu (pokedex.unownPersonality, comme dans les deux jeux), capture « pokedex ».
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_unown import pace, run_away, unown_letter
from menu_helpers import open_start_entry, press_until_free

CHAMBERS = (("Monean", "A?"), ("Liptoo", "CDHUO"), ("Weepth", "NSIE"), ("Dilford", "PLJRQ"), ("Scufib", "YTGFK"),
            ("Rixy", "VWXMB"), ("Viapois", "Z!"))
LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!?"
OPTION_POKEDEX = 10


def dex_letter(game):
    seen, letter = re.search(r"zarbi : vu (\d+), lettre (\d+)", game.dev("jeu.pokedex")).groups()
    return int(seen), LETTERS[int(letter)]


def encounter(game, chamber):
    """Une rencontre dans la chambre : la lettre du ZARBI (None si un autre Pokémon)."""
    game.warp(f"SevenIsland_TanobyRuins_{chamber}Chamber", 11, 14); game.wait(30)
    for _ in range(4):
        since = mark(game)
        expect(game, pace(game, 40), f"une rencontre à {chamber}")
        wait_until(game, lambda s: s.foe, limit=600)
        foe = game.state.foe[0]
        if foe[0] == names.value("SPECIES_UNOWN"):
            letter = LETTERS[unown_letter(foe[6])]
            wait_text(game, "sauvage apparaît", since=since)    # la transition finie, le ZARBI en place
            game.wait(30)
            game.shot(f"combat-{chamber.lower()}-{letter}")
            run_away(game)
            return letter
        run_away(game)
    return None


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.flag("FLAG_KANTO_SYS_UNLOCKED_TANOBY_RUINS", 1)
    expect(game, dex_letter(game)[0] == 0, "aucun ZARBI vu au départ")

    seen = []
    for chamber, allowed in CHAMBERS:
        letter = encounter(game, chamber)
        game.note(f"ZARBI {chamber} : {letter}")
        expect(game, letter is not None and letter in allowed, f"{chamber} : lettre {letter} parmi {allowed}")
        seen.append(letter)
    expect(game, dex_letter(game) == (1, seen[0]), f"Pokédex : le premier ZARBI vu, {seen[0]} ({dex_letter(game)})")

    # Pokédex de RF (POKéDEX = KANTO), MODE NUMERIQUE: NATIONAL, n° 201 : la fiche de ZARBI
    game.flag("FLAG_SYS_POKEDEX_GET", 1)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    game.dev("jeu.pokedex", 0, 1)
    game.dev("jeu.options", OPTION_POKEDEX, 1)
    open_start_entry(game, "POKéDEX"); game.wait(240)
    game.tap("DOWN"); game.wait(20); game.tap("A"); game.wait(200)            # MODE NUMERIQUE: NATIONAL
    game.tap("DOWN", 200, hold=2, gap=4); game.wait(60)
    since = mark(game)
    game.tap("A"); game.wait(200)
    game.shot("pokedex")
    expect_text(game, "ZARBI", since)
    press_until_free(game)
