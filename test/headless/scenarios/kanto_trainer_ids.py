# Les deux dresseurs de Kanto dont le numéro est celui d'un adversaire spécial d'Émeraude (IS_SECRET_BASE_OPPONENT,
# IS_FRONTIER_BRAIN_OPPONENT dans include/battle_setup.h) se battent comme les autres. Trouvé par l'explorateur le
# 2026-11-02 : PIQUE-NIQUE TINA (1024 = TRAINER_SECRET_BASE) se battait comme une Base Secrète (équipe du combat
# d'avant, 0 ¥, texte de défaite d'une Base Secrète, pas de drapeau : le combat recommençait sans fin).
from driver import *
import crawl
import maps

FIXTURE = "kanto"


def battle(game, map_name, x, y, trainer, foes):
    """Combat contre le dresseur en (x, y), vu d'en dessous : son équipe, de l'argent, puis il ne combat plus."""
    money = game.money()
    group, num = maps.find_map(map_name)
    game.command("warp", group, num, x, y + 1)
    game.wait(60)
    wait_until(game, lambda s: s.free or s.script or s.battle)
    if game.state.free:
        talk_to(game, "UP")
    else:                           # il voit le joueur en arrivant : il vient lui parler
        finish_dialog(game)
    expect_battle(game, trainer=trainer, outcome="WON")
    expect(game, game.battles[-1]["foes"] == foes, f"équipe de {trainer} : {foes} ({game.battles[-1]['foes']})")
    expect(game, game.money() > money, f"argent gagné contre {trainer} ({money} -> {game.money()})")
    count = len(game.battles)
    talk_to(game, "UP")             # vaincu : il parle, sans combat
    expect(game, len(game.battles) == count, f"{trainer} ne combat plus")


def play(game):
    continue_game(game)
    crawl.give_mewtwo(game)
    game.dev("jeu.options", 3, 1)   # STYLE COMBAT : DEFINI
    battle(game, "CeladonCity_Gym", 10, 7, "TRAINER_KANTO_PICNICKER_TINA", ["SPECIES_BULBASAUR", "SPECIES_IVYSAUR"])
    expect_no_text(game, "Tu es trop balèze")       # le texte de défaite d'une Base Secrète
    expect_text(game, "ouvert les yeux")            # son texte de défaite (« Tu m’as ouvert les yeux! »)
    battle(game, "RockTunnel_B1F", 11, 15, "TRAINER_KANTO_PICNICKER_SOFIA", ["SPECIES_JIGGLYPUFF", "SPECIES_PIDGEY",
                                                                       "SPECIES_MEOWTH"])
    expect_text(game, "PIQUE-NIQUE SOFIA")
