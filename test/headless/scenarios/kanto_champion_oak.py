# Salle du champion de Kanto (2026-11-03, docs/A-TESTER.md) : après la victoire contre le rival, le Prof. CHEN rappelle
# le starter choisi à KANTO (« Tu as tant changé depuis ton départ avec SALAMECHE. »), pas celui de Hoenn : special
# GetStarterSpecies lit VAR_KANTO_STARTER_MON (VAR_STARTER_MON = celui de Hoenn). Le rival a le starter fort contre
# celui du joueur (CARAPUCE contre SALAMECHE).
# Au retour du combat, la musique de victoire continue (Overworld_PlaySpecialMapMusic de RF, 2026-11-04) : lancée une
# seule fois, par le combat, et non relancée depuis le début par le savebgm du script.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import maps
sys.path.insert(0, os.path.dirname(driver.__file__))
import crawl


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    crawl.give_mewtwo(game)
    game.var("VAR_KANTO_STARTER_MON", 2)              # SALAMECHE à Kanto (sStarterSpecies de RF)
    game.var("VAR_STARTER_MON", 0)                    # GRIKO à Hoenn ; lu par erreur dans RF, ce serait BULBIZARRE
    since = mark(game)
    sounds = len(game.sounds)
    group, num = maps.find_map("PokemonLeague_ChampionsRoom")
    game.command("warp", group, num, 6, 18)
    for _ in range(600):
        if saw_text(game, "départ avec", since):
            break
        if game.state.battle:
            fight_battle(game, limit=3000)              # 6 POKéMON
        else:
            game.tap("A"); game.wait(20)
    game.wait(60)
    foes = [battle["foes"] for battle in game.battles]
    expect(game, game.battles and game.battles[-1]["outcome"] == "WON", f"le rival battu ({game.battles[-1:]})")
    expect(game, any("SPECIES_SQUIRTLE" in f or "SPECIES_BLASTOISE" in f for f in foes),
           f"le rival a le starter fort contre SALAMECHE ({foes})")
    expect(game, saw_text(game, "départ avec SALAMECHE", since),
           "CHEN : « ton départ avec SALAMECHE » (starter de Kanto)")
    victory = [frame for frame, sound in game.sounds[sounds:] if sound == "MUS_RG_VICTORY_GYM_LEADER"]
    expect(game, len(victory) == 1, f"musique de victoire lancée une seule fois, pas relancée au retour ({victory})")
