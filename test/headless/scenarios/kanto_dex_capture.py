# Options > POKéDEX = KANTO, capture d'une espèce encore inconnue (docs/A-TESTER.md, 2026-11-03) : après « RATTATA est
# attrapé! » et « Les données de RATTATA sont ajoutées au POKéDEX. », la fiche s'ouvre dans le Pokédex de RF
# (enregistrement façon RF, capture « enregistrement » à revoir), puis le surnom ; RATTATA est ensuite attrapé dans le
# Pokédex.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_unown import Battle, stop_at_battle

# Une graine où la rencontre est un RATTATA (jeu.hasard, posée sur la Route 1 juste avant les pas)
SEED = int(os.environ.get("KANTO_DEX_CAPTURE_SEED", "2"))

OPTION_POKEDEX = 10
OPTION_BAG = 13


def caught(game, species):
    line = next(l for l in game.dev("jeu.pokedex").splitlines() if l.startswith("attrapes"))
    return str(names.value(species)) in line.split(":")[1].split()


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.item("ITEM_MASTER_BALL", 5)
    game.flag("FLAG_SYS_POKEDEX_GET", 1)
    game.flag("FLAG_KANTO_SYS_POKEDEX_GET", 1)
    game.dev("jeu.options", OPTION_POKEDEX, 1)
    game.dev("jeu.options", OPTION_BAG, 1)                 # sac de RF : les Balls en 3e poche
    expect(game, not caught(game, "SPECIES_RATTATA"), "RATTATA pas encore attrapé")

    game.warp("Route1", 12, 9); game.wait(30)
    game.dev("jeu.hasard", SEED)                           # la rencontre : un RATTATA
    since = mark(game)
    try:
        for i in range(60):
            walk_to(game, 12, 9 if i % 2 else 10, on_battle=stop_at_battle)
    except Battle:
        pass
    wait_text(game, "sauvage apparaît", since=since, limit=900)
    for _ in range(20):                                     # le message d'entrée attend A
        if saw_text(game, "Que doit faire", since):
            break
        game.tap("A"); game.wait(40)
    game.wait(30)
    game.tap("RIGHT"); game.wait(20); game.tap("A"); game.wait(240)      # SAC
    game.tap("RIGHT", 2, gap=90); game.wait(60)                          # poche des Balls : MASTER BALL
    game.tap("A"); game.wait(60); game.tap("A")                          # UTILISER
    wait_text(game, "est attrapé", since=since, limit=1500)
    for _ in range(30):                                                  # « attrapé! », puis « ajoutées au POKéDEX. »
        if saw_text(game, "ajoutées au POKéDEX", since):
            break
        game.wait(60); game.tap("A")
    # La fiche du Pokédex de RF (Task_DexScreen_RegisterMonToPokedex, l'écran de combat reste BattleMainCB2)
    register = lambda s: any("RegisterMonToPokedex" in game.function(t) for t in s.tasks)
    for _ in range(15):
        try:
            wait_until(game, register, limit=60)
            break
        except GameError:
            game.tap("A")                                                # le message attend encore A
    expect(game, register(game.state), "fiche du Pokédex de RF")
    game.wait(240)
    game.shot("enregistrement")
    game.note(f"ÉCRAN {game.describe()}")
    for _ in range(40):
        if game.state.free:
            break
        game.tap("B"); game.wait(60)
    wait_until(game, lambda s: s.free)

    expect_battle(game, foe="SPECIES_RATTATA", outcome="CAUGHT")
    expect(game, caught(game, "SPECIES_RATTATA"), "RATTATA attrapé dans le Pokédex")
