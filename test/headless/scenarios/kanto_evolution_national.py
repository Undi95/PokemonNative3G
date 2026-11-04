# Kanto sans le POKéDEX NATIONAL (demande du 2026-11-04 ; règle de RF Task_EvolutionScene / MonCanEvolve, dans la
# fusion Kanto_IsEvolutionBlocked), sauvegarde « kanto » (sans le national) :
# - LEVEINARD (amitié 255) : la scène d'évolution s'arrête d'elle-même sur « ……? », pas de LEUPHORIE ;
# - NOSFERALTO (amitié 255) : NOSTENFER est du POKéDEX de HOENN, il évolue ;
# - TOURNEGRIN + PIERRE SOLEIL : « aucun effet » avec le sac d'Émeraude, la scène « Hein? » de RF avec son sac ; la
#   pierre est gardée ;
# - à Hoenn (Rosyères), sans le national, LEVEINARD devient LEUPHORIE, comme dans Émeraude ;
# - à Kanto avec le POKéDEX NATIONAL, LEVEINARD devient LEUPHORIE.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until
from kanto_tour import log
from menu_helpers import open_start_entry, pick, press_until_free, bag, texts
from kanto_item_use_scenes import bag_item_menu

OPTION_BAG_STYLE = 13
CHANSEY, GOLBAT, SUNKERN, CHANSEY_2 = 0, 1, 2, 3
CURSOR = [0]   # le menu d'équipe se rouvre sur la dernière place choisie


def species(game, slot):
    return game.state.party[slot][0]


def stones(game):
    return sum(q for n, _, q in bag(game)["poche 1"] if n == names.number("ITEM_SUN_STONE"))


def use_stone(game, slot, kanto_bag, what):
    """PIERRE SOLEIL > UTILISER, puis le Pokémon de la place slot ; A jusqu'au retour au sac ; les textes."""
    open_start_entry(game, "SAC"); game.wait(240)
    stone = next(name for n, name, _ in bag(game)["poche 1"] if n == names.number("ITEM_SUN_STONE"))
    if kanto_bag:
        since = bag_item_menu(game, stone)
    else:
        game.tap("LEFT", 5, gap=30); game.wait(60)
        listed = [name for _, name, _ in bag(game)["poche 1"]]
        game.tap("UP", 12, gap=10); game.wait(30)
        index = listed.index(stone)
        if index:
            game.tap("DOWN", index, gap=20); game.wait(30)
        since = mark(game)
        game.tap("A"); game.wait(60)
    pick(game, since, "UTILIS."); game.wait(240)
    move = slot - CURSOR[0]
    if move:
        game.tap("DOWN" if move > 0 else "UP", abs(move), gap=20); game.wait(30)
    CURSOR[0] = slot
    screens = len(game.cb2s)
    game.tap("A"); game.wait(240)
    log(game, what)
    for _ in range(40):
        current = game.function(game.state.cb2)
        if "BagMenu" in current or current == "CB2_Bag":
            break
        game.tap("A"); game.wait(60)
    evolved = any("Evolution" in name or "EvoScene" in name for _, name in game.cb2s[screens:])
    shown = texts(game, since)
    press_until_free(game)
    return evolved, shown


def evolve(game, slot, what):
    """joueur.evolution : la scène, A jusqu'au retour sur la carte ; capture au message de fin ; les textes."""
    since = mark(game)
    screens = len(game.cb2s)
    reply = game.dev("joueur.evolution", slot)
    game.note(f"ÉVOLUTION {slot} : {reply.strip()}")
    wait_until(game, lambda s: any("Evolution" in n or "EvoScene" in n for _, n in game.cb2s[screens:]), limit=600)
    logged = False
    for _ in range(120):
        if not logged and (saw_text(game, "……?", since) or saw_text(game, "Félicitations", since)):
            game.wait(60)
            log(game, what)
            logged = True
        if game.state.free and logged:
            break
        game.tap("A"); game.wait(40)
    wait_until(game, lambda s: s.free, limit=600)
    return texts(game, since)


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.flag("FLAG_SYS_POKEDEX_GET", 1)               # le POKéDEX de HOENN, qu'une partie a forcément à Kanto
    national = game.dev("jeu.pokedex").splitlines()[0]
    game.give_mon("SPECIES_CHANSEY", 30)
    game.give_mon("SPECIES_GOLBAT", 30)
    game.give_mon("SPECIES_SUNKERN", 20)
    game.give_mon("SPECIES_CHANSEY", 30)
    for slot in (CHANSEY, GOLBAT, CHANSEY_2):
        game.dev("joueur.amitie", slot, 255)
    game.item("ITEM_SUN_STONE", 1)
    game.warp("PalletTown", 9, 12); game.wait(30)

    # PIERRE SOLEIL sur TOURNEGRIN : sac d'Émeraude, puis sac de RF
    stone_hoenn_bag = use_stone(game, SUNKERN, False, "pierre sac hoenn")
    stones_after_hoenn_bag = stones(game)
    game.dev("jeu.options", OPTION_BAG_STYLE, 1)        # SAC = KANTO
    stone_kanto_bag = use_stone(game, SUNKERN, True, "pierre sac kanto")
    stones_after_kanto_bag = stones(game)
    game.dev("jeu.options", OPTION_BAG_STYLE, 0)

    # Évolutions par l'amitié, à Kanto sans le national
    chansey = evolve(game, CHANSEY, "leveinard kanto")
    chansey_species = species(game, CHANSEY)
    golbat = evolve(game, GOLBAT, "nosferalto kanto")
    golbat_species = species(game, GOLBAT)

    # À Hoenn, sans le national
    game.warp("OldaleTown_Mart", 3, 3); game.wait(30)
    hoenn = evolve(game, CHANSEY, "leveinard hoenn")
    hoenn_species = species(game, CHANSEY)

    # À Kanto, avec le national
    game.warp("PalletTown", 9, 12); game.wait(30)
    game.dev("jeu.pokedex", 0, 1)
    with_national = evolve(game, CHANSEY_2, "leveinard national")
    national_species = species(game, CHANSEY_2)

    # Vérifications
    expect(game, "national 0" in national, f"sauvegarde sans le national ({national})")
    expect(game, not stone_hoenn_bag[0] and any("aucun effet" in t for _, t in stone_hoenn_bag[1])
           and stones_after_hoenn_bag == 1,
           f"sac d'Émeraude : PIERRE SOLEIL sans effet, gardée ({stone_hoenn_bag[1][-3:]}, {stones_after_hoenn_bag})")
    expect(game, not stone_kanto_bag[0] and any("Hein" in t for _, t in stone_kanto_bag[1])
           and stones_after_kanto_bag == 1,
           f"sac de RF : scène « Hein? », PIERRE SOLEIL gardée ({stone_kanto_bag[1][-3:]}, {stones_after_kanto_bag})")
    expect(game, species(game, SUNKERN) == names.number("SPECIES_SUNKERN"), "TOURNEGRIN reste TOURNEGRIN")
    expect(game, chansey_species == names.number("SPECIES_CHANSEY") and any("……?" in t for _, t in chansey),
           f"Kanto sans le national : LEVEINARD s'arrête sur « ……? » ({chansey_species}, {chansey[-3:]})")
    expect(game, golbat_species == names.number("SPECIES_CROBAT"),
           f"NOSFERALTO devient NOSTENFER (POKéDEX de HOENN) ({golbat_species}, {golbat[-3:]})")
    expect(game, hoenn_species == names.number("SPECIES_BLISSEY"),
           f"Hoenn sans le national : LEUPHORIE ({hoenn_species}, {hoenn[-3:]})")
    expect(game, national_species == names.number("SPECIES_BLISSEY"),
           f"Kanto avec le national : LEUPHORIE ({national_species}, {with_national[-3:]})")
