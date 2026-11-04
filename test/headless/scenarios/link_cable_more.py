# CÂBLE LINK, cas restants (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto » :
# - acheté à la boutique de Rosyères (2 100 ¥) ;
# - sac d'Émeraude : PIKACHU (pas d'évolution par échange) et KADABRA avec une PIERRE STASE : « aucun effet », câble
#   gardé ; ONIX avec une PEAU MÉTAL : sans le POKéDEX NATIONAL, « aucun effet » (Kanto, 2026-11-04) ; avec, évolution
#   en STEELIX, la PEAU MÉTAL est consommée (comme un échange) ;
# - sac de RF (SAC = KANTO) : le second KADABRA évolue en ALAKAZAM.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, mark, saw_text, wait_until, wait_text
from kanto_tour import log
from menu_helpers import open_start_entry, pick, press_until_free, bag, texts


def party(game):
    return [(int(m.group(1)), int(m.group(2))) for m in
            re.finditer(r"espece (\d+) .* objet (\d+)", game.dev("joueur.equipe"))]


CURSOR = [0]   # le menu d'équipe se rouvre sur la dernière place choisie


def use_cable(game, slot, what, kanto=False):
    """CÂBLE LINK (1er des Objets) > UTILISER, puis le Pokémon de la place slot ; A jusqu'au retour au sac."""
    open_start_entry(game, "SAC"); game.wait(240)
    game.tap("LEFT", 5, gap=30); game.wait(60)
    game.tap("UP", 12, gap=10); game.wait(30)
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


def play(game):
    continue_game(game)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    game.give_mon("SPECIES_ONIX", 30, "ITEM_METAL_COAT")
    game.give_mon("SPECIES_PIKACHU", 20)
    game.give_mon("SPECIES_KADABRA", 25, "ITEM_EVERSTONE")
    game.give_mon("SPECIES_KADABRA", 25)
    game.money(5000)

    # Achat à Rosyères (boutique d'Émeraude, MENUS = HOENN) : CÂBLE LINK, 5e de la liste
    game.warp("OldaleTown_Mart", 3, 3); game.wait(40)
    game.press("LEFT", 4); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(150)
    for _ in range(6):
        if saw_text(game, "ACHETER", since):
            break
        game.tap("A"); game.wait(60)
    game.wait(30)
    pick(game, since, "ACHETER"); game.wait(300)
    game.tap("DOWN", 4, gap=20); game.wait(30)
    log(game, "boutique cable")
    for _ in range(10):
        if game.money() != 5000:
            break
        game.tap("A"); game.wait(60)
    press_until_free(game)
    bought = bag(game)
    game.item("ITEM_LINK_CABLE", 1)                    # un second câble : deux évolutions
    game.warp("PalletTown", 9, 12); game.wait(30)

    pikachu = use_cable(game, 1, "pikachu")
    everstone = use_cable(game, 2, "pierre stase")
    # Kanto sans le POKéDEX NATIONAL (2026-11-04, Kanto_IsEvolutionBlocked) : STEELIX, hors des POKéDEX de Kanto et de
    # Hoenn, attend le national ; le câble et la PEAU MÉTAL sont gardés
    onix_blocked = use_cable(game, 0, "onix sans national")
    onix_blocked_party = party(game)
    game.dev("jeu.pokedex", 0, 1)
    onix = use_cable(game, 0, "onix")
    after_hoenn = party(game)
    game.dev("jeu.options", 13, 1)                     # SAC = KANTO
    kadabra = use_cable(game, 3, "kadabra sac rf", kanto=True)
    final = party(game)
    cables = [q for n, _, q in bag(game)["poche 1"] if n == names.number("ITEM_LINK_CABLE")]

    # Vérifications
    expect(game, game.money() == 5000 - 2100 and [q for n, _, q in bought["poche 1"] if n == names.number("ITEM_LINK_CABLE")] == [1],
           f"CÂBLE LINK acheté 2 100 ¥ ({game.money()}, {bought['poche 1']})")
    for what, (evolved, shown) in (("PIKACHU", pikachu), ("KADABRA + PIERRE STASE", everstone)):
        expect(game, not evolved and any("aucun effet" in t for _, t in shown), f"{what} : aucun effet ({shown[-3:]})")
    expect(game, not onix_blocked[0] and any("aucun effet" in t for _, t in onix_blocked[1])
           and onix_blocked_party[0] == (names.number("SPECIES_ONIX"), names.number("ITEM_METAL_COAT")),
           f"Kanto sans le national : ONIX + PEAU MÉTAL sans effet, objet gardé ({onix_blocked_party[0]})")
    expect(game, onix[0] and after_hoenn[0] == (names.number("SPECIES_STEELIX"), 0),
           f"ONIX + PEAU MÉTAL : STEELIX, PEAU MÉTAL consommée ({after_hoenn[0]})")
    expect(game, kadabra[0] and final[3][0] == names.number("SPECIES_ALAKAZAM"), f"sac de RF : ALAKAZAM ({final[3]})")
    expect(game, final[1][0] == names.number("SPECIES_PIKACHU") and final[2] == (names.number("SPECIES_KADABRA"), names.number("ITEM_EVERSTONE")),
           f"PIKACHU et KADABRA + PIERRE STASE inchangés ({final[1:3]})")
    expect(game, cables == [], f"les deux câbles utilisés, pas ceux sans effet ({cables})")
