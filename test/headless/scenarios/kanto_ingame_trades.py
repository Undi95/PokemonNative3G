# Échanges in-game de Kanto dont les données dépendent de la version (src/data/kanto_ingame_trades_entries.h, version
# Rouge Feu, FIRERED ; 2026-11-03) : NIDORAN♂ contre la NIDORAN♀ de Saige (souterrain, entrée nord), GOLDUCK contre
# l'EXCELANGUE de Haden (Route 18) ; le Pokémon reçu a l'espèce et le dresseur d'origine de RF. Puis un échange de
# Hoenn (TARSAL contre GRAINIPIOT, Mérouville) : l'animation se termine sans planter (fin de sTradeAnim, UBFIX).
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.dirname(driver.__file__))
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
import crawl
from menu_helpers import texts

# (carte, PNJ, espèce donnée, espèce reçue, DO de RF)
TRADES = (("UndergroundPath_NorthEntrance", (5, 6), "SPECIES_NIDORAN_M", "SPECIES_NIDORAN_F", 63184),
          ("Route18_EastEntrance_2F", (5, 3), "SPECIES_GOLDUCK", "SPECIES_LICKITUNG", 1239),
          ("RustboroCity_House1", (6, 4), "SPECIES_RALTS", "SPECIES_SEEDOT", 38726))      # (Hoenn, même animation)


def trade(game, place, spot, slot):
    """Parle au PNJ, OUI, le Pokémon de la place slot de l'équipe, l'animation de l'échange, merci : les textes."""
    for sx, sy, direction in crawl.spots(place, *spot):
        game.warp(place, sx, sy); game.wait(30)
        since = mark(game)
        talk_to(game, direction, finish=False)
        if not game.state.free:
            break
    chosen = False
    for _ in range(400):
        if game.state.free:
            break
        if "PartyMenu" in game.function(game.state.cb2) and not chosen:
            # pas de A pendant que le menu s'ouvre (il choisirait le 1er) : le menu prêt, puis la place
            wait_until(game, lambda s: game.function(s.cb2) == "CB2_UpdatePartyMenu", step=1, limit=300)
            game.wait(60)
            if slot:
                game.tap("DOWN", slot, gap=12); game.wait(10)
            chosen = True
        game.tap("A"); game.wait(20)
    finish_dialog(game, limit=200)
    return " ".join(t for _, t in texts(game, since))


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for place, spot, give, get, ot in TRADES:
        game.give_mon(give, 20)
        slot = len(re.findall(r"(?m)^\d+ ", game.dev("joueur.equipe"))) - 1     # (l'état du banc a une image de retard)
        said = trade(game, place, spot, slot)
        team = game.dev("joueur.equipe")
        game.note(f"ÉCHANGE {place} : {said[-160:]} ; {team}")
        got = [int(n) for n in re.findall(r"espece (\d+)", team)]
        expect(game, names.value(get) in got and names.value(give) not in got, f"{place} : {get} reçu ({got})")
        expect(game, f"DO {ot} " in team, f"{place} : dresseur d'origine {ot} de RF")
