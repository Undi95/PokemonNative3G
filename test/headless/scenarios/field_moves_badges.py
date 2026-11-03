# CS selon les badges de la région (2026-11-03, docs/A-TESTER.md), depuis le menu de l'équipe : sans le badge, « il
# faut un nouveau BADGE » ; avec ce seul badge, plus ce message (la capacité s'utilise, ou « pas ici »).
# Kanto (badges de Kanto) : ROCHE = FLASH, CASCADE = COUPE, FOUDRE = VOL, PRISME = FORCE, ÂME = SURF,
# MARAIS = ÉCLATE-ROC, VOLCAN = CASCADE. Hoenn (badges de Hoenn, comme Émeraude) : ROCHE = COUPE, POING = FLASH,
# DYNAMO = ÉCLATE-ROC, CHALEUR = FORCE, BALANCE = SURF, PLUME = VOL, ESPRIT = PLONGÉE, PLUIE = CASCADE.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import open_start_entry, pick, texts

# capacité, nom au menu, badge à Kanto, badge à Hoenn
MOVES = (("MOVE_CUT", "COUPE", 2, 1), ("MOVE_FLASH", "FLASH", 1, 2), ("MOVE_ROCK_SMASH", "ECLATE-ROC", 6, 3),
         ("MOVE_STRENGTH", "FORCE", 4, 4), ("MOVE_SURF", "SURF", 5, 5), ("MOVE_FLY", "VOL", 3, 6),
         ("MOVE_WATERFALL", "CASCADE", 7, 8))


def set_badges(game, prefix, only):
    for i in range(1, 9):
        game.flag(f"{prefix}0{i}_GET", int(i == only))


def try_move(game, slot, label):
    """Menu de l'équipe, POKéMON slot, la capacité label : les textes écrits jusqu'au retour au jeu."""
    open_start_entry(game, "POKéMON"); game.wait(90)
    if slot:
        game.tap("DOWN", slot, gap=12); game.wait(10)
    since = mark(game)
    game.tap("A"); game.wait(40)
    pick(game, since, label)
    game.wait(90)
    shown = " ".join(t for _, t in texts(game, since))
    for _ in range(12):
        if game.state.free:
            break
        game.tap("B"); game.wait(40)
    wait_until(game, lambda s: s.free, limit=900)
    return shown


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_TAUROS", 50)             # COUPE, FLASH, ÉCLATE-ROC, FORCE
    game.give_mon("SPECIES_DRAGONITE", 60)          # SURF, VOL, CASCADE
    for place, move in enumerate(("MOVE_CUT", "MOVE_FLASH", "MOVE_ROCK_SMASH", "MOVE_STRENGTH")):
        game.dev("joueur.capacite", 0, place, names.number(move))
    for place, move in enumerate(("MOVE_SURF", "MOVE_FLY", "MOVE_WATERFALL", "MOVE_SPLASH")):
        game.dev("joueur.capacite", 1, place, names.number(move))

    for region, place, prefix, badge_index in (("Kanto", ("Route1", 12, 20), "FLAG_KANTO_BADGE", 2),
                                               ("Hoenn", ("Route102", 20, 8), "FLAG_BADGE", 3)):
        for move, label, kanto_badge, hoenn_badge in MOVES:
            badge = kanto_badge if region == "Kanto" else hoenn_badge
            slot = 0 if move in ("MOVE_CUT", "MOVE_FLASH", "MOVE_ROCK_SMASH", "MOVE_STRENGTH") else 1
            game.warp(*place); game.wait(30)
            set_badges(game, "FLAG_BADGE", 0)
            set_badges(game, "FLAG_KANTO_BADGE", 0)
            other = 1 if badge != 1 else 2                  # un autre badge de la région, pas le bon
            set_badges(game, prefix, other)
            locked = try_move(game, slot, label)
            game.warp(*place); game.wait(30)
            set_badges(game, prefix, badge)
            unlocked = try_move(game, slot, label)
            game.note(f"{region} {label} : sans badge {badge} « {locked[-70:]} » / avec « {unlocked[-70:]} »")
            expect(game, "BADGE" in locked.upper(), f"{region} {label} : refusé sans le badge {badge} ({locked[-60:]})")
            expect(game, "BADGE" not in unlocked.upper(), f"{region} {label} : accepté avec le badge {badge} ({unlocked[-60:]})")
            if game.state.map_name != place[0]:
                game.warp(*place); game.wait(30)

    # Sur l'eau, à Kanto (Cap Falaise) : SURF face à la mer (ÂME), puis CASCADE face à la chute (VOLCAN)
    def face_and_ask(spot, face, badges):
        set_badges(game, "FLAG_BADGE", 0)
        set_badges(game, "FLAG_KANTO_BADGE", 0)
        for badge in badges:
            game.flag(f"FLAG_KANTO_BADGE0{badge}_GET", 1)
        game.warp("TwoIsland_CapeBrink", *spot); game.wait(40)
        wait_until(game, lambda s: s.free)
        game.press(face, 1); game.wait(20)
        since = mark(game)
        game.tap("A"); game.wait(60)
        shown = " ".join(t for _, t in texts(game, since))
        finish_dialog(game, answers={"utiliser": "B"})
        return shown
    surf_without = face_and_ask((12, 35), "UP", (1, 2, 3, 4, 6, 7, 8))
    surf_with = face_and_ask((12, 35), "UP", (5,))
    expect(game, "SURF" not in surf_without, f"eau sans ÂME : pas de SURF proposé ({surf_without[-60:]})")
    expect(game, "SURF" in surf_with, f"eau avec ÂME : SURF proposé ({surf_with[-60:]})")
    # La cascade : en surfant au pied de la chute (comme poke_monture_moves), avec ou sans VOLCAN
    for badges, wanted in (((5,), False), ((5, 7), True)):
        set_badges(game, "FLAG_KANTO_BADGE", 0)
        for badge in badges:
            game.flag(f"FLAG_KANTO_BADGE0{badge}_GET", 1)
        game.warp("TwoIsland_CapeBrink", 12, 35); game.wait(40)
        game.press("UP", 1); game.wait(20)
        game.tap("A"); game.wait(60)
        finish_dialog(game)                          # OUI : SURF
        for _ in range(12):
            if game.state.pos[1] <= 26:
                break
            game.press("UP", 16); game.wait(8)
        since = mark(game)
        game.tap("A"); game.wait(60)
        shown = " ".join(t for _, t in texts(game, since))
        finish_dialog(game, answers={"utiliser": "B"})
        expect(game, ("CASCADE" in shown) == wanted,
               f"cascade {'avec' if wanted else 'sans'} VOLCAN : CASCADE {'proposée' if wanted else 'pas proposée'} ({shown[-60:]})")
