# Objets « clone » de RF (2026-10-31) : sur la Route 2, l'arbre à Couper de Jadielle (5 cases après la jonction) est
# chargé avant de franchir la jonction (clone en 6,85 de la Route 2, hors de l'écran depuis le bas de la route) ;
# en entrant dans Jadielle, c'est le même objet qui devient l'arbre de Jadielle (18,5), sans doublon. Avant, il
# n'apparaissait qu'en entrant dans Jadielle.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, walk_to, wait_until
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log


def play(game):
    continue_game(game)
    game.warp("Route2", 8, 76); game.wait(30)
    on_route = list(game.state.objects)
    walk_to(game, 8, 79); game.wait(20)
    log(game, "route 2, en bas")
    game.press("DOWN", 16); game.wait(40)
    wait_until(game, lambda s: s.free)
    in_city = [o[:2] for o in game.state.objects]
    log(game, "jadielle")

    # Téléporté en bas de la Route 2 (8, 79), l'arbre est déjà dans le champ de vision : pas de clone. En descendant à
    # Jadielle, le joueur arrive sur la rangée du bord (y 0) : RF ne crée pas l'arbre à moins de 7 cases de ce bord et
    # met son drapeau temporaire (TemplateIsObstacleAndVisibleFromConnectingMap, 2026-11-02)
    game.warp("Route2", 8, 79); game.wait(30)
    no_clone = [o[:2] for o in game.state.objects]
    game.press("DOWN", 16); game.wait(40)
    wait_until(game, lambda s: s.free)
    reloaded = [o[:2] for o in game.state.objects]
    hidden_flag = game.flag("FLAG_TEMP_12")

    # Vérifications
    expect(game, (6, 85) in [o[:2] for o in on_route], f"clone de l'arbre en 6,85 sur la Route 2 ({on_route})")
    expect_map(game, "ViridianCity")
    expect(game, in_city.count((18, 5)) == 1, f"un seul arbre en 18,5 à Jadielle ({in_city})")
    expect(game, (6, 85) not in no_clone, f"arbre dans le champ de vision : pas de clone ({no_clone})")
    expect(game, (18, 5) not in reloaded and hidden_flag == 1,
           f"arrivée par le bord sans clone : l'arbre n'est pas créé, FLAG_TEMP_12 mis ({reloaded}, {hidden_flag})")
