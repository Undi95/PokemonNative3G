# Télé Pokémon de Rouge Feu (TV ABC, 2026-10-30) : depuis le sac, les six émissions du Pokédude l'une après l'autre.
# Combat, statut, types, capture : combats de démonstration (les deux camps jouent seuls, voix off en fenêtre 24) ;
# CT : Boîte à CT de démonstration ; objet : sac de démonstration (enregistrer un objet). Retour au menu après chacune.
# Les deux dernières n'apparaissent qu'avec une CT ou une CS dans le sac (RF : la Boîte à CT vient avec la première CT).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
from driver import continue_game, mark, wait_text, wait_until
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log

EPISODES = ("Comment combattre", "Les problèmes de statut", "Rapports entre les types", "Attraper des POKéMON",
            "Les CT", "Enregistrer un objet")


def open_teachy_tv(game):
    """Sac (d'Émeraude) > OBJ. RARES > TV ABC > UTILISER."""
    game.tap("START"); game.wait(30); game.tap("DOWN"); game.wait(10); game.tap("A"); game.wait(200)
    game.tap("RIGHT", 4, gap=40); game.wait(60)
    game.tap("A"); game.wait(40); game.tap("A"); game.wait(300)


def in_menu(game):
    """La liste des émissions attend un choix."""
    return any(game.function(t) == "TeachyTvOptionListController" for t in game.state.tasks)


def play(game):
    continue_game(game)
    game.item("ITEM_TEACHY_TV", 1)
    game.item("ITEM_TM39", 1)
    party = list(game.state.party)
    bag = {item: game.item(item) for item in ("ITEM_POTION", "ITEM_ANTIDOTE", "ITEM_POKE_BALL", "ITEM_GREAT_BALL",
                                              "ITEM_NEST_BALL", "ITEM_TM_CASE", "ITEM_BICYCLE")}
    since = mark(game)
    open_teachy_tv(game)
    wait_text(game, EPISODES[0], since)
    log(game, "menu")
    for n, title in enumerate(EPISODES):
        since = mark(game)
        game.tap("A"); game.wait(60)
        voice = None
        for _ in range(600):
            if voice is None and any(w == 24 for _, w, _t in game.texts[since:]):
                voice = len(game.texts)
                game.wait(40)
                if n < 4:
                    log(game, f"emission {n + 1} voix off")
            if voice is None and n == 4 and any(w == 6 for _, w, _t in game.texts[since:]):   # Boîte à CT
                voice = len(game.texts)
                game.wait(40); log(game, "emission 5 boite CT")
            if voice is None and n == 5 and any(w == 3 and t == "ENREG." for _, w, t in game.texts[since:]):
                voice = len(game.texts)
                game.wait(20); log(game, "emission 6 sac")
            if voice is not None and in_menu(game):
                break
            game.tap("A"); game.wait(30)
        game.note(f"émission {n + 1} finie ({title})")
        game.wait(60)
        game.tap("DOWN"); game.wait(20)
    game.tap("B"); game.wait(200)   # retour au sac d'où la télé a été allumée
    expect(game, game.function(game.state.cb2) == "CB2_BagMenuRun", "retour au sac du joueur")
    game.tap("B"); game.wait(120); game.tap("B")
    wait_until(game, lambda s: s.free, limit=900)

    # Vérifications
    expect(game, sum(1 for b in game.battles if b["outcome"]) >= 4, "quatre combats de démonstration")
    expect(game, game.state.party == party, "équipe du joueur rendue après les démonstrations")
    expect_item(game, "ITEM_TEACHY_TV", 1)
    expect_text(game, "Enregistrer un objet")
    expect_item(game, "ITEM_TM39", 1)   # CT du joueur rendues après la Boîte à CT du Pokédude
    expect_item(game, "ITEM_TM01", 0)
    for item, count in bag.items():   # le sac du Pokédude ne remplace pas celui du joueur
        expect_item(game, item, count)
