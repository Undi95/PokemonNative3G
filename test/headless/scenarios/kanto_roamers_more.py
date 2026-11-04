# Vagabonds de Kanto, cas restants (2026-11-03, docs/A-TESTER.md) :
# - lâchés (InitRoamer) : RAIKOU, ENTEI, SUICUNE actifs, N.50, IV complets (pas seulement PV/Attaque : bits 10 à 29) ;
# - ils changent de route quand le joueur change de carte ;
# - une rencontre : touché (ÉCRAS'FACE), il fuit ; ses PV sont gardés, et la rencontre suivante repart de ces PV ;
# - piégé par REGARD NOIR, il ne peut plus fuir : quand il utilise HURLEMENT, le combat finit et il reste en liberté
#   (avant : disparu pour toujours) ;
# - Hoenn : LATIAS (ou LATIOS) errant reste actif, indépendant des chiens.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import re
import names

DOGS = {names.number(f"SPECIES_{s}"): s for s in ("RAIKOU", "ENTEI", "SUICUNE")}
ROAMER_RE = (r"errant (\d+) espece (\d+) niveau (\d+) actif (\d+) carte (\S+) PV (\d+) statut (0x[0-9a-f]+|0) "
             r"ivs (0x[0-9a-f]+|0)")


def roamers(game):
    return {int(m.group(2)): {"level": int(m.group(3)), "active": int(m.group(4)), "map": m.group(5),
                              "hp": int(m.group(6)), "ivs": int(m.group(8), 0)}
            for m in re.finditer(ROAMER_RE, game.dev("jeu.errants"))}


def flee(game):
    """FUITE (en bas à droite du menu d'action)."""
    for _ in range(200):
        if not game.state.battle:
            return
        if saw_text(game, "Que doit faire", max(0, len(game.texts) - 3)):
            game.tap("RIGHT"); game.tap("DOWN"); game.tap("A"); game.wait(60)
        else:
            game.tap("A"); game.wait(30)


def meet_dog(game, on_dog, wanted=None):
    """Marche dans l'herbe de la Route 1 (chiens mis sur la carte) jusqu'à un chien (de wanted s'il est donné) ;
    les autres combats : FUITE."""
    met = []

    def battle(g):
        foe = g.state.foe[0][0] if g.state.foe else None
        if foe in (wanted or DOGS) and not met:
            met.append((foe, g.state.foe[0][2], g.state.foe[0][3]))
            on_dog(g)
        else:
            flee(g)
    game.warp("Route1", 12, 9); game.wait(30)
    game.dev("jeu.errants", 2)
    for i in range(1200):
        if met:
            break
        game.press("UP" if i % 2 == 0 else "DOWN", 16); game.wait(2)
        if game.state.battle:
            battle(game)
            finish_dialog(game, on_battle=battle)
    return met[0] if met else None


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_MEWTWO", 100)
    game.dev("joueur.capacite", 0, 0, names.number("MOVE_POUND"))
    for place in (1, 2, 3):
        game.dev("joueur.capacite", 0, place, 0)
    # Hoenn d'abord : l'errant du choix à la télé (InitRoamer à Hoenn, comme son script)
    game.warp("Route101", 10, 10); game.wait(30)
    hoenn_before = game.dev("jeu.errants", 1)
    game.note(f"Hoenn avant : {hoenn_before}")
    game.warp("Route1", 12, 9); game.wait(30)
    game.dev("jeu.errants", 1)
    start = roamers(game)
    game.note(f"lâchés : {start}")
    for number, name in DOGS.items():
        dog = start.get(number, {})
        expect(game, dog.get("active") == 1 and dog.get("level") == 50, f"{name} : actif, N.50 ({dog})")
        expect(game, dog.get("ivs", 0) >> 10, f"{name} : IV complets ({dog.get('ivs', 0):#x})")

    # Ils changent de route
    maps_seen = {number: {dog["map"]} for number, dog in start.items()}
    for place in (("ViridianCity", 20, 20), ("Route2", 7, 50), ("PewterCity", 15, 20), ("Route1", 12, 9),
                  ("PalletTown", 10, 8), ("Route22", 30, 10)):
        game.warp(*place); game.wait(20)
        for number, dog in roamers(game).items():
            maps_seen.setdefault(number, set()).add(dog["map"])
    expect(game, any(len(seen) > 1 for seen in maps_seen.values()), f"ils changent de route ({maps_seen})")

    # Touché puis il fuit : PV gardés, repris à la rencontre suivante
    game.dev("jeu.hasard", 7)
    first = meet_dog(game, lambda g: fight_battle(g))
    after = roamers(game)
    expect(game, first is not None, "un chien rencontré dans l'herbe")
    if first:
        dog = after[first[0]]
        expect(game, dog["active"] == 1 and 0 < dog["hp"] < first[2],
               f"{DOGS[first[0]]} : toujours libre, PV gardés ({first[1]}/{first[2]} -> {dog['hp']})")
        # Le même chien, de nouveau : le combat repart de ces PV (on fuit)
        again = meet_dog(game, flee, [first[0]])
        expect(game, again is not None and again[1] == dog["hp"],
               f"{DOGS[first[0]]} rencontré de nouveau : {again[1] if again else None} PV, ceux gardés ({dog['hp']})")

    # REGARD NOIR puis HURLEMENT du chien : il reste libre
    # REGARD NOIR (5 PP), puis TREMPETTE (40 PP, sans effet) : le chien a le temps de tirer HURLEMENT (1 chance sur 4
    # par tour, ses 4 capacités au hasard) sans être mis K.O.
    game.dev("joueur.capacite", 0, 0, names.number("MOVE_MEAN_LOOK"))
    game.dev("joueur.capacite", 0, 1, names.number("MOVE_SPLASH"))
    game.dev("joueur.pv", 0, 999)
    # RAIKOU et ENTEI ont HURLEMENT au N.50 (SUICUNE non)
    roarers = [n for n, s in DOGS.items() if s in ("RAIKOU", "ENTEI")]
    # une graine où le chien tire HURLEMENT avant de mettre K.O. le POKéMON du joueur (sinon : combat perdu)
    game.dev("jeu.hasard", int(os.environ.get("KANTO_ROAR_SEED", "1")))
    second = meet_dog(game, lambda g: fight_battle(g, limit=1500), roarers)
    end = roamers(game)
    roared = saw_text(game, "HURLEMENT")
    game.note(f"2e rencontre : {second}, HURLEMENT vu : {roared}, issue {game.battles[-1:]}")
    expect(game, second is not None and roared, f"le chien piégé finit par utiliser HURLEMENT ({second})")
    if second:
        expect(game, end[second[0]]["active"] == 1, f"{DOGS[second[0]]} : toujours libre après HURLEMENT ({end[second[0]]})")

    # Hoenn : l'errant de Hoenn reste actif, indépendant des chiens
    game.warp("Route101", 10, 10); game.wait(30)
    hoenn = game.dev("jeu.errants")
    game.note(f"Hoenn : {hoenn}")
    lati = hoenn_before.split(" niveau")[0]
    expect(game, "actif 1" in hoenn_before and lati in hoenn and "actif 1" in hoenn
           and not any(f"espece {n} " in hoenn for n in DOGS),
           f"Hoenn : LATIAS / LATIOS toujours actif, sans les chiens ({hoenn_before.strip()[:60]} -> {hoenn.strip()[:60]})")
