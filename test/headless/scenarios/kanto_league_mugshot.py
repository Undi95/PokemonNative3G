# Ligue de Kanto : le combat contre Olga commence par la transition à portrait de Rouge Feu (B_TRANSITION_LORELEI :
# bandeau, portraits d'Olga et du joueur, palettes de RF), comme dans RF. Avant, la classe TRAINER_CLASS_KANTO_ELITE_FOUR
# n'était pas reconnue par GetTrainerBattleTransition : une transition générique.
from driver import *

FIXTURE = "kanto"


def play(game):
    continue_game(game)
    game.dev("jeu.options", 6, 1)               # PERSO = Red/Leaf : leur portrait et la palette rouge de RF
    game.warp("PokemonLeague_LoreleisRoom", 6, 12)     # la porte d'en bas : le joueur monte de 5 cases en entrant
    game.wait(30)
    wait_until(game, lambda s: s.free, limit=600)      # l'entrée dans la salle (EnterRoom : 5 pas, la porte se ferme)
    talk_to_object(game, 6, 5, finish=False)    # OLGA
    seen = False
    for _ in range(300):
        if "Task_Lorelei" in [game.function(t) for t in game.state.tasks]:
            seen = True
            break
        game.tap("A", hold=2, gap=10)
    expect(game, seen, "transition à portrait d'Olga (Task_Lorelei)")
    game.wait(60)                               # le bandeau, les deux portraits qui glissent
    check_screen(game, "kanto_league_mugshot-olga")
