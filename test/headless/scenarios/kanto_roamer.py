# Les Pokémon errants de Kanto (RAIKOU, ENTEI, SUICUNE) : leur combat a la musique des légendaires de Rouge Feu
# (StartRoamerBattle de RF : MUS_VS_LEGEND de RF = MUS_RG_VS_LEGEND), pas celle des Pokémon sauvages.
# jeu.errants 1 les lâche (InitRoamer, comme le script du Centre de l'Île 1), 2 les met sur la Route 1.
from driver import *

FIXTURE = "kanto"
ROAMERS = ("SPECIES_RAIKOU", "SPECIES_ENTEI", "SPECIES_SUICUNE")


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_MEWTWO", 100)        # la sauvegarde de test n'a pas d'équipe
    for place in range(4):                      # PSYKO partout : chaque combat de la Route 1 se gagne en un coup
        game.dev("joueur.capacite", 0, place, names.number("MOVE_PSYCHIC"))
    game.dev("jeu.options", 0, 2)               # texte rapide
    game.warp("Route1", 11, 30)
    game.dev("jeu.errants", 1)
    game.note(game.dev("jeu.errants", 2))

    grid = live_map(game)
    px, py = game.state.pos
    grass = sorted(((x, y) for y, row in enumerate(grid.tiles) for x, c in enumerate(row) if c == "g"),
                   key=lambda t: abs(t[0] - px) + abs(t[1] - py))
    for x, y in grass[:20]:
        if grid.path((px, py), (x, y), set(game.state.objects)) is not None:
            walk_to(game, x, y, live=True, on_battle=lambda g: None)
            break

    roamer = None
    for _ in range(40):                         # 1 rencontre sur 4 avec un errant présent (TryStartRoamerEncounter)
        game.note(game.dev("jeu.errants", 2))   # un changement de carte (retour de combat) peut les déplacer
        frame = game.frames
        for i in range(400):
            if game.state.battle:
                break
            game.press(("LEFT", "RIGHT")[i % 2], 16)
        if not game.state.battle:
            break
        foes = game.battles[-1]["foes"] if game.battles else []
        if any(f in ROAMERS for f in foes):
            roamer = (foes, frame)
            game.wait(240)
            break
        fight_battle(game)                      # un Pokémon de la Route 1 : MEWTWO le bat
        wait_until(game, lambda s: s.free, limit=900)
        game.wait(20)
    expect(game, roamer is not None, "combat contre un errant de Kanto")
    if roamer:
        expect_song(game, "MUS_RG_VS_LEGEND", roamer[1])
        expect(game, "MUS_RG_VS_WILD" not in [n for f, n in game.songs if f >= roamer[1]],
               "pas la musique des Pokémon sauvages")
