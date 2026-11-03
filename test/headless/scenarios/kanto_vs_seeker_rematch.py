# CHERCHE VS à Kanto (2026-11-03, docs/A-TESTER.md ; kanto_vs_seeker.c) : Route 3, ses dresseurs déjà battus, 100 pas
# pour la recharge, CHERCHE VS sur SELECT : des dresseurs à l'écran lèvent la main (MOVEMENT_TYPE_RAISE_HAND_*, « !! »)
# ou refusent (« X ») ; en parler à un qui lève la main = revanche avec l'équipe de RF (un autre dresseur, *_2) ; au
# changement de carte, ils se calment.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.dirname(driver.__file__))
import crawl

SPOT = ("Route3", 25, 9)
JANICE = (19, 9)
RAISE_HAND = {names.value("MOVEMENT_TYPE_RAISE_HAND_AND_STOP"), names.value("MOVEMENT_TYPE_RAISE_HAND_AND_JUMP"),
              names.value("MOVEMENT_TYPE_RAISE_HAND_AND_SWIM")}


def route3_trainers():
    path = os.path.join(os.path.dirname(driver.__file__), "..", "..", "data", "kanto", "data", "scripts", "trainers.inc")
    return re.findall(r"Route3_EventScript_\w+::\n\ttrainerbattle\w* (TRAINER_\w+)", open(path, encoding="utf-8").read())


def objects(game):
    """{(x, y): mouvement} des objets de la carte (carte.objets), le joueur exclu."""
    found = {}
    for line in game.dev("carte.objets").splitlines():
        m = re.search(r"en (\d+),(\d+) mouvement (\d+)", line)
        if m and "joueur" not in line:
            found[(int(m.group(1)), int(m.group(2)))] = int(m.group(3))
    return found


def walk_steps(game, count):
    """count pas en allant et venant sur la rangée 9 (x 23 à 29) : la recharge du CHERCHE VS."""
    for i in range(count):
        x = game.state.pos[0]
        direction = "RIGHT" if (i // 6) % 2 == 0 else "LEFT"
        if (direction == "RIGHT" and x >= 29) or (direction == "LEFT" and x <= 23):
            direction = "LEFT" if direction == "RIGHT" else "RIGHT"
        game.press(direction, 16); game.wait(2)


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    crawl.give_mewtwo(game)
    game.dev("jeu.rencontres", 0)
    trainers = route3_trainers()
    for trainer in trainers:
        game.flag(names.value("KANTO_TRAINER_FLAGS_START") + names.value(trainer) - names.value("KANTO_TRAINERS_START"), 1)
    game.item("ITEM_VS_SEEKER", 1)
    game.flag("FLAG_KANTO_GOT_VS_SEEKER", 1)           # sans lui, pas d'équipe de revanche (TryGetRematchTrainerIdGivenGameState)
    game.dev("joueur.enregistre", names.number("ITEM_VS_SEEKER"))
    game.warp(*SPOT); game.wait(30)
    walk_steps(game, 110)
    game.warp(*SPOT); game.wait(30)
    before = objects(game)
    game.dev("jeu.hasard", 7)
    since = mark(game)
    game.tap("SELECT", hold=4); game.wait(400)
    finish_dialog(game, limit=100)
    after = objects(game)
    raised = [pos for pos, movement in after.items() if movement in RAISE_HAND]
    game.note(f"avant {before} ; après {after} ; textes {[t for _, _, t in game.texts[since:]]}")
    expect(game, raised, f"des dresseurs lèvent la main ({after})")

    # Revanche avec JANICE (19, 9) : son équipe de revanche de RF (TRAINER_KANTO_LASS_JANICE_2 ; JAMES, lui, n'en a pas
    # d'autre dans sVsSeekerData)
    expect(game, (19, 9) in raised, f"JANICE lève la main ({raised})")
    x, y = JANICE
    talk_to_object(game, x, y, finish=False)
    for _ in range(80):
        if game.state.battle:
            break
        game.tap("A", hold=2, gap=4)
    fight_battle(game, limit=1500)
    finish_dialog(game, limit=200)
    rematch = game.battles[-1] if game.battles else {}
    game.note(f"revanche : {rematch}")
    expect(game, (rematch.get("trainer") or "").startswith("TRAINER_KANTO_LASS_JANICE_") and rematch.get("outcome") == "WON",
           f"revanche contre JANICE et son équipe de revanche ({rematch.get('trainer')}, {rematch.get('foes')})")

    # Au changement de carte, plus personne ne lève la main
    game.warp("PewterCity", 10, 30); game.wait(30)
    game.warp(*SPOT); game.wait(30)
    calm = objects(game)
    expect(game, not [p for p, m in calm.items() if m in RAISE_HAND], f"retour sur la Route 3 : ils se sont calmés ({calm})")
