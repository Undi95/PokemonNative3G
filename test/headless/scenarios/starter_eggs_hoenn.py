# Œufs des starters manquants à Hoenn (assistant du PROF. SEKO, pension de la Route 117 ; fusion_events.c,
# 2026-11-03, docs/A-TESTER.md), sauvegarde « hoenn » :
# - avant la Ligue : « … Le MAÎTRE de la LIGUE POKéMON de HOENN, par exemple ! », pas d'œuf ;
# - après : l'œuf du 1er starter de Hoenn jamais attrapé, qui éclot dans la bonne espèce ;
# - équipe pleine : « Ton équipe est pleine… » ;
# - les trois de Hoenn donnés : rien de plus tant que le starter de Johto n'est pas reçu chez SEKO ; ensuite,
#   l'œuf de GERMIGNON (refusé : « Je comprends ») ;
# - Île 4 avant la Ligue de Kanto : « … Le MAÎTRE du PLATEAU INDIGO, par exemple ! ».
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "hoenn"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, wait_text, wait_until
from kanto_tour import log
from kanto_card_stickers import press_until_text
from menu_helpers import texts


def party(game):
    return [(int(m.group(1)), int(m.group(2))) for m in
            re.finditer(r"espece (\d+) .*\n.*oeuf (\d+)", game.dev("joueur.equipe"))]


def talk(game, what, refuse=False):
    """Parle à l'assistant (au-dessus du joueur) : A partout (OUI), ou B à la question OUI/NON (refuse)."""
    wait_until(game, lambda s: s.free)
    since = mark(game)
    game.tap("A"); game.wait(40)
    for _ in range(30):
        if game.state.free:
            break
        if refuse and saw_text(game, "NON", since):
            game.wait(20)
            game.tap("B"); game.wait(40)
            refuse = False
            continue
        game.tap("A"); game.wait(50)
    wait_until(game, lambda s: s.free, limit=900)
    log(game, what)
    return " ".join(t for _, t in texts(game, since))


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_GAME_CLEAR", 0)
    game.var("VAR_STARTER_EGGS_GIVEN", 0)
    game.var("VAR_DEX_UPGRADE_JOHTO_STARTER_STATE", 0)
    start = party(game)
    game.warp("Route117_PokemonDayCare", 9, 6); game.wait(40)
    game.press("UP", 2); game.wait(20)

    not_yet = talk(game, "avant la ligue")
    game.flag("FLAG_SYS_GAME_CLEAR", 1)
    given = talk(game, "oeuf recu")
    with_egg = party(game)
    egg_species = with_egg[-1][0]                      # VAR_0x8005 est déjà l'œuf suivant

    # Éclosion (joueur.oeuf : prêt à éclore ; EventScript_EggHatch)
    slot = len(with_egg) - 1
    game.dev("joueur.oeuf", slot)
    game.var("VAR_0x8004", slot)
    since = mark(game)
    game.script("EventScript_EggHatch")
    wait_text(game, "Hein", since, limit=600)
    press_until_text(game, "vient de sortir", since)
    game.wait(20); log(game, "eclosion")
    finish_dialog(game, answers={"surnom": "B"})
    hatched = party(game)[slot]

    # Équipe pleine
    while len(party(game)) < 6:
        game.give_mon("SPECIES_ZIGZAGOON", 5)
    full = talk(game, "equipe pleine")

    # Les trois de Hoenn donnés : rien avant le starter de Johto ; ensuite GERMIGNON
    game.var("VAR_STARTER_EGGS_GIVEN", 0x38)
    no_more = talk(game, "plus d'oeuf")
    game.var("VAR_DEX_UPGRADE_JOHTO_STARTER_STATE", 6)
    johto = talk(game, "johto refuse", refuse=True)
    johto_species = game.var("VAR_0x8005")

    # Kanto (Île 4) avant la Ligue de Kanto
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 0)
    game.warp("FourIsland_PokemonDayCare", 9, 6); game.wait(40)
    game.press("RIGHT", 2); game.wait(20)
    kanto_not_yet = talk(game, "kanto avant la ligue")

    # Vérifications
    expect(game, "MAÎTRE de la LIGUE POKéMON de HOENN" in not_yet.replace("  ", " ") or "LIGUE" in not_yet,
           f"avant la Ligue : pas d'œuf ({not_yet[-80:]})")
    expect(game, "reçoit l’OEUF" in given and len(with_egg) == len(start) + 1 and with_egg[-1][1] == 1,
           f"un œuf reçu ({given[-60:]} ; {with_egg})")
    expect(game, egg_species in [names.number(s) for s in ("SPECIES_TREECKO", "SPECIES_TORCHIC", "SPECIES_MUDKIP")]
           and hatched == (egg_species, 0), f"l'œuf éclot en {egg_species} ({hatched})")
    expect(game, "équipe est pleine" in full, f"équipe pleine ({full[-60:]})")
    expect(game, "Tu as tous les POKéMON de départ" in no_more, f"sans le starter de Johto : plus d'œuf ({no_more[-60:]})")
    expect(game, johto_species == names.number("SPECIES_CHIKORITA") and "Je comprends" in johto,
           f"avec le starter de Johto : GERMIGNON proposé, refusé ({johto_species} ; {johto[-50:]})")
    expect(game, "PLATEAU" in kanto_not_yet and "INDIGO" in kanto_not_yet,
           f"Île 4 avant la Ligue de Kanto : pas d'œuf ({kanto_not_yet[-60:]})")
