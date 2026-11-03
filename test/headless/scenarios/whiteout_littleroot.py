# K.O. à Hoenn avant tout Centre Pokémon (docs/A-TESTER.md, 2026-11-03) : la reprise est la maison de Bourg-en-Vol
# (HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, posée par le camion du début d'Émeraude ; outil carte.reprise) :
# K.O. par le poison sur la Route 101, retour dans la maison, MAMAN soigne l'équipe.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import json, os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from headless import REPO_DIR
from kanto_whiteout_more import poison_white_out


def heal_location(name):
    with open(os.path.join(REPO_DIR, "src", "data", "heal_locations.json"), encoding="utf-8") as f:
        ids = [h["id"] for h in json.load(f)["heal_locations"]]
    return ids.index(name) + 1                         # après HEAL_LOCATION_NONE


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MAGIKARP", 5)
    game.dev("joueur.genre", 0)
    game.dev("carte.reprise", heal_location("HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F"))
    game.note(f"REPRISE {game.dev('carte.reprise')}")
    text, before, after, where = poison_white_out(game, "Route101", 10, 10)
    game.note(f"K.O. : {where} {game.state.pos} ; {text[-200:]}")
    expect(game, where.startswith("LittlerootTown_BrendansHouse"), f"reprise dans la maison de Bourg-en-Vol ({where})")
    species, level, hp, max_hp, status = game.state.party[0][:5]
    expect(game, hp == max_hp and status == 0, f"équipe soignée ({hp}/{max_hp}, statut {status:#x})")
