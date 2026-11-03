# Build KANTO_DEBUG=1 : objets du debug, MEWTWO, DEBUG > Revanches PokéNav, téléport Route 102 (à côté de
# Calvin), CHERCHE VS : Calvin (revanche du PokéNav) répond « !! » et saute, Rick (pas de revanche, jamais
# combattu) « ! ». Puis on parle à Calvin : combat de revanche, et il cesse de sauter après.
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log, debug_warp, give_mewtwo
from kanto_vs_seeker import use_vs_seeker
from redleaf_acro import close_menus
from driver import finish_dialog, wait_until
import re
import names
from menu_helpers import open_start_entry


def calvin_movement(game):
    """Le type de mouvement de Calvin (Route 102, en 33,14) : saut du Cherche VS ou le sien."""
    for line in game.dev("carte.objets").splitlines():
        m = re.search(r"en 33,14 mouvement (\d+)", line)
        if m:
            return int(m.group(1))
    return None


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 5, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    give_mewtwo(game)
    game.tap("START"); game.wait(30); game.tap("A"); game.wait(30); game.tap("DOWN", 8, gap=10); game.tap("A"); game.wait(60)
    close_menus(game)
    debug_warp(game, 22); log(game, "Route 102")
    for slot in range(len(game.state.party)):           # TONNERRE en 1re capacité : PSYKO n'agit pas sur GRAHYENA
        game.dev("joueur.capacite", slot, 0, names.value("MOVE_THUNDERBOLT"))
    game.flag("FLAG_SYS_POKENAV_GET", 1)                # (POKéNAV vient après SAC dans le menu Start)
    game.flag("FLAG_ADDED_MATCH_CALL_TO_POKENAV", 1)
    use_vs_seeker(game, "VS", 2)  # menu Start : DEBUG, POKéMON, SAC
    game.wait(120); log(game, "réponses")
    calvin_jumping = calvin_movement(game)

    # PokéNav > APPELS : Calvin dans la liste, prêt pour une revanche (capture « pokenav-appels ») ; de retour sur la
    # carte, il saute toujours
    since = mark(game)
    open_start_entry(game, "POKéNAV"); game.wait(300)
    game.tap("DOWN", 2, gap=20); game.wait(20); game.tap("A"); game.wait(300)
    for _ in range(70):                                 # la liste défile jusqu'à Calvin
        if saw_text(game, "CALVIN", since):
            break
        game.tap("DOWN"); game.wait(12)
    game.wait(30)
    game.shot("pokenav-appels")
    pokenav = " ".join(t for _, _, t in game.texts[since:])
    game.note(f"POKéNAV : {pokenav[-200:]}")
    expect(game, "CALVIN" in pokenav, "Calvin dans les appels du PokéNav")
    for _ in range(10):
        if game.state.free:
            break
        game.tap("B"); game.wait(120)
    wait_until(game, lambda s: s.free); game.wait(30)
    expect(game, calvin_movement(game) == calvin_jumping, "Calvin saute toujours après le PokéNav")
    game.tap("RIGHT", hold=16); game.wait(30); game.tap("RIGHT"); game.wait(20)
    game.tap("A"); game.wait(400); log(game, "Calvin")
    finish_dialog(game)
    wait_until(game, lambda s: s.free); game.wait(200); log(game, "après le combat")
    calvin_after = calvin_movement(game)
    game.note(f"CALVIN : mouvement {calvin_jumping} avec le CHERCHE VS, {calvin_after} après la revanche gagnée")

    # Vérifications
    expect_battle(game, trainer="TRAINER_CALVIN_2", outcome="WON")
    # Après le combat, il reste tourné vers le joueur (MOVEMENT_TYPE_FACE_*, comme tout dresseur battu)
    facing = {names.value(f"MOVEMENT_TYPE_FACE_{d}") for d in ("UP", "DOWN", "LEFT", "RIGHT")}
    expect(game, calvin_jumping == names.value("MOVEMENT_TYPE_RAISE_HAND_AND_JUMP") and calvin_after in facing,
           f"Calvin saute avec le CHERCHE VS puis cesse après la revanche gagnée ({calvin_jumping} -> {calvin_after})")
