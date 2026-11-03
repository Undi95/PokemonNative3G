# Machine à sous de Rouge Feu (Casino de Céladopole, kanto_slot_machine.c), les gains (2026-11-03, docs/A-TESTER.md),
# sauvegarde « kanto », graine fixe : 40 parties de 3 jetons (R) ; fanfare MUS_SLOTS_WIN (ou MUS_SLOTS_JACKPOT),
# jetons gagnés un par un (SE_PIN une fois la fanfare finie, comme RF), Mélofée qui danse pendant le paiement ; les
# jetons du joueur suivent (mises retirées, gains ajoutés ; jackpot des 7 : 300) ; plus de jetons : message, retour
# au Casino.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import press_until_free, texts

SEED = int(os.environ.get("KANTO_SLOTS_SEED", "7"))


def coins(game):
    return int(re.search(r"jetons (\d+)", game.dev("joueur.jetons")).group(1))


def play(game):
    continue_game(game)
    game.item("ITEM_COIN_CASE", 1)
    game.dev("joueur.jetons", 300)
    game.warp("CeladonCity_GameCorner", 4, 6); game.wait(30)
    game.press("RIGHT", 4); game.wait(20)
    since = mark(game)
    game.tap("A")
    wait_text(game, "On joue", since)
    wait_text(game, "NON", since)
    game.wait(30)
    game.tap("A"); game.wait(400)                      # OUI : la machine
    wait_until(game, lambda s: "MainTask_SlotsGameLoop" in game.dev("jeu.etat"), step=10, limit=600)
    game.wait(30)
    log(game, "machine")
    game.dev("jeu.hasard", SEED)

    spins = []                                         # (jetons avant, après, fanfares, SE_PIN)
    danced = False
    for spin in range(40):
        start = coins(game)
        sounds = len(game.sounds)
        game.tap("R"); game.wait(80)                   # mise de 3 : les rouleaux tournent
        for _ in range(3):
            game.tap("A"); game.wait(50)
        for _ in range(30):
            if not danced and any(s.startswith("MUS_SLOTS") for _, s in game.sounds[sounds:]):
                game.wait(30)
                log(game, "gain")                      # Mélofée danse, la ligne gagnante clignote
                danced = True
                break
            game.wait(4)
        for _ in range(400):                           # paiement (un jeton toutes les 8 images), retour à la mise
            if "MainTask_SlotsGameLoop" in game.dev("jeu.etat"):
                break
            game.wait(10)
        game.wait(30)
        fanfare = [s for _, s in game.sounds[sounds:] if s.startswith("MUS_SLOTS")]
        pins = sum(1 for _, s in game.sounds[sounds:] if s == "SE_PIN")
        spins.append((start, coins(game), fanfare, pins))
    game.note("parties : " + " ; ".join(f"{a}->{b} {''.join(f)} {p}" for a, b, f, p in spins))

    # Plus de jetons : message de fin, puis retour au Casino (MainTask_NoCoinsGameOver)
    game.dev("joueur.jetons", 0)
    since = mark(game)
    game.wait(120)
    log(game, "plus de jetons")
    no_coins = texts(game, since)
    game.tap("A"); game.wait(300)
    press_until_free(game)

    # Vérifications
    wins = [s for s in spins if s[2]]
    expect(game, len(wins) > 0 and any("MUS_SLOTS_WIN" in s[2] for s in wins), f"des gains en 40 parties (graine {SEED})")
    expect(game, all(after == before - 3 for before, after, fanfare, _ in spins if not fanfare),
           "partie perdue : 3 jetons misés")
    expect(game, all(after > before - 3 for before, after, fanfare, _ in wins), "partie gagnée : des jetons en plus")
    jackpots = [after - before + 3 for before, after, fanfare, _ in wins if "MUS_SLOTS_JACKPOT" in fanfare]
    # CalcPayout additionne les lignes gagnantes : un jackpot rapporte au moins 100 (ROCKET) ou 300 (7)
    expect(game, all(won >= 100 for won in jackpots), f"jackpot : au moins 100 jetons ({jackpots})")
    # RF : SE_PIN seulement une fois la fanfare finie (IsFanfareTaskInactive) ; un jeton toutes les 8 images
    expect(game, all(pins <= after - before + 3 for before, after, _, pins in wins), "pas plus de SE_PIN que de jetons")
    expect(game, any("jeton" in t.lower() for _, t in no_coins) and game.state.free,
           f"plus de jetons : message, retour au Casino ({no_coins})")
