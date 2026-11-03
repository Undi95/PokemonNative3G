# Menu d'équipe avec MENUS = KANTO (docs/A-TESTER.md, 2026-11-03 ; ToggleFieldMoveDescriptionWindow de party_menu.c) :
# les 13 capacités de terrain réparties sur 4 Pokémon ; le curseur passe de RÉSUMÉ à chaque capacité : sa description
# de RF s'écrit dans la bande (captures « PKMN-N » à revoir : texte entier dans la bande, Plongée et Force Cachée
# comprises), puis revient sur RÉSUMÉ (la bande disparaît, capture « PKMN-resume »).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, press_until_free

OPTION_MENU_STYLE = 11
TEAM = (("SPECIES_MEWTWO", ("MOVE_CUT", "MOVE_FLASH", "MOVE_ROCK_SMASH", "MOVE_STRENGTH")),
        ("SPECIES_LAPRAS", ("MOVE_SURF", "MOVE_DIVE", "MOVE_WATERFALL", "MOVE_SECRET_POWER")),
        ("SPECIES_PIDGEOT", ("MOVE_FLY", "MOVE_TELEPORT", "MOVE_DIG", "MOVE_SWEET_SCENT")),
        ("SPECIES_MILTANK", ("MOVE_MILK_DRINK", "MOVE_SOFT_BOILED", "MOVE_TACKLE", "MOVE_GROWL")))
DESCRIPTIONS = {"MOVE_CUT": "Couper arbre/herbe.", "MOVE_FLASH": "Eclairer les ténèbres.",
                "MOVE_ROCK_SMASH": "Eclater rochers fissurés.", "MOVE_STRENGTH": "Bouger de gros rochers.",
                "MOVE_SURF": "Voyager sur l'eau.", "MOVE_DIVE": "Plonger en eau profonde.",
                "MOVE_WATERFALL": "Franchir chutes d'eau.", "MOVE_SECRET_POWER": "Ouvrir une base secrète.",
                "MOVE_FLY": "Vol vers une cité connue.", "MOVE_TELEPORT": "Retour lieu de soins.",
                "MOVE_DIG": "Fuir d'un endroit.", "MOVE_SWEET_SCENT": "Attirer PKMN sauvages.",
                "MOVE_MILK_DRINK": "Partager les PV.", "MOVE_SOFT_BOILED": "Partager les PV."}


def norm(text):
    return " ".join(text.replace("’", "'").split())


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for slot, (species, moves) in enumerate(TEAM):
        game.give_mon(species, 60)
        for place, move in enumerate(moves):
            game.dev("joueur.capacite", slot, place, names.value(move))
    game.dev("jeu.options", OPTION_MENU_STYLE, 1)
    open_start_entry(game, "POKéMON"); game.wait(120)
    seen = {}
    party = [species for species, *_ in game.state.party]
    expect(game, party == [names.value(s) for s, _ in TEAM], f"l'équipe dans l'ordre ({party})")
    for slot, (species, moves) in enumerate(TEAM):
        if slot:
            game.tap("DOWN"); game.wait(20)                      # le Pokémon suivant (le curseur reste sur le dernier)
        game.tap("A"); game.wait(40)                             # ses actions : RÉSUMÉ, puis ses capacités de terrain
        shown = [m for m in moves if m in DESCRIPTIONS]
        for n, move in enumerate(shown):
            since = mark(game)
            game.tap("DOWN"); game.wait(30)
            game.shot(f"{species[8:].lower()}-{n}")
            seen[move] = [norm(t) for _, _, t in game.texts[since:]]
        game.tap("UP", len(shown), gap=12); game.wait(30)         # retour sur RÉSUMÉ
        game.shot(f"{species[8:].lower()}-resume")
        game.tap("B"); game.wait(40)
    press_until_free(game)

    for move, description in DESCRIPTIONS.items():
        expect(game, norm(description) in seen.get(move, []), f"{move} : « {description} » ({seen.get(move)})")
