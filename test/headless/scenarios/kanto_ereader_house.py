# La maison de l'Île 7 et son dresseur e-Reader (SevenIsland_House_Room1/Room2 ; fonctions de RF portées le
# 2026-11-04 : StartSpecialBattle, BufferEReaderTrainerGreeting, ReducePlayerPartyToThree, kanto_battle_tower.c). Sans
# e-Reader, le dresseur est enregistré par l'outil combat.ereader (FillEReaderTrainerWithPlayerData : l'équipe du
# joueur, ici 3 MAGICARPE). La porte est ouverte, la vieille dame propose le combat : OUI, 3 POKéMON choisis,
# sauvegarde, la salle de combat (combat e-Reader, BATTLE_TYPE_EREADER_TRAINER), victoire, retour et commentaire.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from menu_helpers import texts

BATTLE_TYPE_EREADER_TRAINER = 1 << 11


def party_count(game):
    return len(re.findall(r"(?m)^\d+ ", game.dev("joueur.equipe")))


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for _ in range(3):
        game.give_mon("SPECIES_MAGIKARP", 5)
    trainer = game.dev("combat.ereader", 1)
    game.note(f"DRESSEUR e-Reader : {trainer.strip()}")
    expect(game, "valide" in trainer and trainer.count(" 129") == 3, f"dresseur e-Reader enregistré ({trainer.strip()})")
    for species, level in (("SPECIES_MEWTWO", 100), ("SPECIES_PIKACHU", 50), ("SPECIES_SNORLAX", 50)):
        game.give_mon(species, level)
    for _ in range(3):
        game.dev("joueur.pc", 0)                        # les MAGICARPE au PC
    expect(game, party_count(game) == 3, f"équipe de 3 ({game.dev('joueur.equipe')[:120]})")

    # La vieille dame, devant la porte ouverte (4, 2)
    game.warp("SevenIsland_House_Room1", 4, 3); game.wait(40)
    finish_dialog(game, settle=20)
    game.shot("porte-ouverte")
    since = mark(game)
    game.press("UP", 1); game.wait(10); game.tap("A")
    for _ in range(100):                                # OUI, jusqu'au choix des POKéMON
        if game.function(game.state.cb2) == "CB2_UpdatePartyMenu":
            break
        game.tap("A"); game.wait(20)
    game.wait(60)
    for i in range(3):                                  # chacun : A, INSCRIRE, puis le suivant
        game.tap("A"); game.wait(40); game.tap("A"); game.wait(40)
        if i < 2:
            game.tap("DOWN"); game.wait(20)
    game.shot("choix")                                  # (après le 3e, le curseur est sur CONFIR.)
    game.tap("A"); game.wait(120)
    for _ in range(400):                                # la sauvegarde (OUI), la salle de combat
        if game.state.battle or game.state.map_name == "SevenIsland_House_Room2":
            break
        game.tap("A"); game.wait(20)
    greeting = mark(game)
    for _ in range(200):                                # l'accueil du dresseur (BufferEReaderTrainerGreeting)
        if game.state.battle:
            break
        game.tap("A"); game.wait(20)
    said = " ".join(t for _, t in texts(game, since))
    game.note(f"VIEILLE DAME : {said[:400]}")
    game.note(f"ACCUEIL : {[t for _, t in texts(game, greeting)][:4]}")
    state = game.dev("combat.etat")
    game.note(f"COMBAT : {state.splitlines()[0]}")
    flags = int(re.search(r"type (0x[0-9a-f]+|\d+)", state).group(1), 0)
    expect(game, flags & BATTLE_TYPE_EREADER_TRAINER, f"combat e-Reader ({state.splitlines()[0]})")
    for _ in range(12):                                 # l'entrée du dresseur (son image et son nom)
        game.wait(20)
        if game.dev("texte.imprimantes").count("etat") and "Un combat est lancé" in " ".join(t for _, t in texts(game, greeting)):
            break
    game.shot("combat")
    fight_battle(game)
    since = mark(game)
    for _ in range(200):                                # l'adieu, le retour et le commentaire de la vieille dame
        if game.state.free and game.state.map_name == "SevenIsland_House_Room1":
            break
        game.tap("A"); game.wait(20)
    after = " ".join(t for _, t in texts(game, since))
    game.note(f"APRÈS : {after[:300]} ; combats {game.battles[-1:]}")
    expect(game, game.battles and game.battles[-1].get("outcome") == "WON", f"combat gagné ({game.battles[-1:]})")
    expect(game, game.state.map_name == "SevenIsland_House_Room1" and party_count(game) == 3,
           f"retour dans la maison, l'équipe rendue ({game.state.map_name}, {party_count(game)})")
