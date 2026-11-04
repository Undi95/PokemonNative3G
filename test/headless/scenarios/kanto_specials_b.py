# Specials de RF (scripts de Kanto), 2e série (2026-11-03, docs/A-TESTER.md), sauvegarde « kanto », FLORIZARRE en tête
# (amitié 255) et PIKACHU :
# - ascenseurs de Sylphe SARL (liste qui défile, entré au RC, sortie au dernier étage) et du repaire Rocket (CLÉ ASC.) ;
# - maison des badges d'Azuria (liste de RF) ; vendeur de Poudre Baie d'Azuria (échange) ;
# - massage de Daisy (amitié +3, puis 500 pas d'attente) ; Resort Gorgeous (POKéMON demandé, récompense) ;
# - poupées de Lorelei (selon les entrées au Panthéon) ; effaceur de capacités (Parmanie) ; vérificateur de surnoms
#   (Lavanville, écran des noms) ; tuteur du Cap Falaise (VÉGÉ-ATTAQUE à FLORIZARRE).
# Chaque partie est isolée : une erreur est notée et la suite continue.
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, re, sys, traceback
import driver
import names
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, finish_dialog, mark, saw_text, talk_to, talk_to_object, wait_until, wait_text, walk_to
from kanto_tour import log
from menu_helpers import bag, pick, texts

RESULTS = {}


def part(name):
    def wrap(fn):
        def run(game):
            try:
                RESULTS[name] = fn(game)
            except Exception as e:
                RESULTS[name] = f"ERREUR {e}"
                game.note(f"ERREUR dans {name} : {traceback.format_exc()[-400:]}")
                for _ in range(20):
                    if game.state.free:
                        break
                    game.tap("B"); game.wait(30)
        return run
    return wrap


def joined(game, since):
    return " ".join(t for _, t in texts(game, since))


def party(game):
    return [(int(a), int(b), int(c)) for a, b, c in
            re.findall(r"espece (\d+) N\.(\d+).*\n.*\n  amitie (\d+)", game.dev("joueur.equipe"))]


def moves(game, slot):
    lines = [l for l in game.dev("joueur.equipe").splitlines() if "capacites" in l]
    return [int(m.split("/")[0]) for m in lines[slot].split("capacites")[1].split()]


def converse(game, slot=0, forget=None, limit=80, back=False):
    """A jusqu'au retour au jeu ; menu d'équipe : le POKéMON de la place slot ; résumé (capacité à oublier ou à
    effacer) : la place forget ; écran des noms : START puis A (nom gardé) ; back : B au lieu de A."""
    chosen = summary = named = False
    for _ in range(limit):
        if game.state.free:
            break
        current = game.function(game.state.cb2)
        if not chosen and ("PartyMenu" in current or "ChooseMon" in current):
            game.wait(120)
            if slot:
                game.tap("DOWN", slot, gap=20); game.wait(20)
            game.tap("A"); game.wait(60)
            chosen = True
            continue
        if forget is not None and not summary and "Summary" in current or "PSS" in current and not summary and forget is not None:
            game.wait(200)
            if forget:
                game.tap("DOWN", forget, gap=30); game.wait(30)
            game.tap("A"); game.wait(60)
            summary = True
            continue
        if not named and "Naming" in current:
            game.wait(120)
            game.tap("START"); game.wait(30); game.tap("A"); game.wait(60)
            named = True
            continue
        game.tap("B" if back else "A"); game.wait(40)
    wait_until(game, lambda s: s.free, limit=900)


def talk(game, place, npc, face="UP"):
    dx, dy = {"UP": (0, 1), "DOWN": (0, -1), "LEFT": (1, 0), "RIGHT": (-1, 0)}[face]
    game.warp(place, npc[0] + dx, npc[1] + dy); game.wait(60)
    wait_until(game, lambda s: s.free)
    since = mark(game)
    for _ in range(3):
        talk_to(game, face, finish=False)              # se tourne (jusqu'à faire face), puis A
        if len(game.texts) > since or not game.state.free:
            break
        game.note(f"PAS DE RÉPONSE : {game.dev('carte.objets')} regarde {game.state.facing}")
        game.wait(60)
    return since


def ride_elevator(game, entry_map, door, through, end="UP"):
    """Entre dans l'ascenseur par la porte (door, direction through), panneau en (0,2), le bout de la liste (end :
    UP le haut, DOWN le bas), sortie par la porte du bas ; rend la carte d'arrivée et les textes."""
    game.warp(entry_map, door[0] - {"UP": 0, "DOWN": 0}[through], door[1] + (1 if through == "UP" else -1))
    game.wait(40)
    for _ in range(3):
        if "Elevator" in game.state.map_name:
            break
        game.press(through, 16); game.wait(60)
    elevator = game.state.map_name
    wait_until(game, lambda s: s.free)
    game.warp(elevator, 0, 3); game.wait(20)
    game.press("UP", 1); game.wait(20)
    since = mark(game)
    game.tap("A"); game.wait(240)
    log(game, f"{elevator} etages")
    if end in ("UP", "DOWN"):
        game.tap(end, 14, gap=14); game.wait(20)     # un bout de la liste (celle de Sylphe ne boucle pas)
        game.tap("A")
    else:
        pick(game, since, end)                         # un étage par son nom (menu court, qui boucle)
    for _ in range(60):
        if game.state.free:
            break
        game.wait(30)
    exits = {"SilphCo_Elevator": (2, 4), "RocketHideout_Elevator": (2, 4)}
    game.warp(elevator, *exits[elevator]); game.wait(20)
    for _ in range(4):
        if game.state.map_name != elevator:
            break
        game.press("DOWN", 16); game.wait(60)
    wait_until(game, lambda s: s.free and s.map_name != elevator, limit=900)
    return game.state.map_name, joined(game, since)


@part("sylphe")
def silph(game):
    return ride_elevator(game, "SilphCo_1F", (22, 3), "UP")


@part("repaire")
def rocket(game):
    game.item("ITEM_LIFT_KEY", 1)
    game.flag("FLAG_KANTO_CAN_USE_ROCKET_HIDEOUT_LIFT", 1)             # la clé lâchée par le sbire
    return ride_elevator(game, "RocketHideout_B1F", (24, 25), "UP", end="4 SS")   # porte prise par le bas


@part("badges")
def badges(game):
    since = talk(game, "CeruleanCity_House1", (6, 5))
    for _ in range(10):                                # jusqu'à la liste
        if "Task_ListMenu" in game.dev("jeu.etat") or "ListMenu" in game.dev("jeu.etat"):
            break
        game.tap("A"); game.wait(50)
    game.wait(60)
    log(game, "badges liste")
    game.tap("A"); game.wait(120)                      # le 1er badge
    converse(game, back=True)                          # B : fin de la description, puis quitter la liste
    return joined(game, since)


@part("poudre")
def powder(game):
    game.flag("FLAG_KANTO_GOT_POWDER_JAR", 1)
    game.dev("joueur.poudre", 500)
    before = game.dev("joueur.poudre")
    since = talk(game, "CeruleanCity_House5", (7, 4))
    for _ in range(10):
        if "ListMenu" in game.dev("jeu.etat"):
            break
        game.tap("A"); game.wait(50)
    game.wait(60)
    log(game, "poudre liste")
    game.tap("A"); game.wait(60)                       # la 1re ligne
    for _ in range(12):                                # OUI à l'échange, messages, retour à la liste
        if "ListMenu" in game.dev("jeu.etat") and saw_text(game, "Obtenu", since):
            break
        game.tap("A"); game.wait(50)
    converse(game, back=True)
    return before, game.dev("joueur.poudre"), joined(game, since)


def talk_wanderer(game, place, local_id, near):
    """Un PNJ qui se promène : sa position réelle (carte.objets), puis talk_to_object."""
    game.warp(place, *near); game.wait(60)
    wait_until(game, lambda s: s.free)
    pos = next((int(m.group(1)), int(m.group(2))) for m in
               re.finditer(rf"id {local_id} gfx \S+ en (\d+),(\d+)", game.dev("carte.objets")))
    since = mark(game)
    talk_to_object(game, *pos, finish=False, live=True)
    return since


@part("daisy")
def daisy(game):
    game.flag("FLAG_KANTO_SYS_GAME_CLEAR", 1)
    game.var("VAR_KANTO_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE", 2)       # CARTE reçue : Daisy n'est plus à table
    game.var("VAR_KANTO_MASSAGE_COOLDOWN_STEP_COUNTER", 500)
    game.dev("joueur.amitie", 1, 100)                  # PIKACHU
    since = talk_wanderer(game, "PalletTown_RivalsHouse", 1, (8, 7))   # Daisy se promène autour de (10,6)
    converse(game, slot=1)
    massaged = (party(game)[1][2], game.var("VAR_KANTO_MASSAGE_COOLDOWN_STEP_COUNTER"), joined(game, since))
    wait_until(game, lambda s: s.free)
    since = mark(game)
    game.script("PalletTown_RivalsHouse_EventScript_Daisy")   # 2e visite (elle se promène : son script directement)
    converse(game)
    return massaged, joined(game, since)


@part("resort")
def resort(game):
    game.var("VAR_KANTO_RESORT_GORGEOUS_REQUESTED_MON", 0)
    game.flag("FLAG_KANTO_HIDE_RESORT_GORGEOUS_INSIDE_SELPHY", 0)    # rentrée chez elle (après l'histoire de l'Île 5)
    since = talk(game, "FiveIsland_ResortGorgeous_House", (4, 4), "RIGHT")
    converse(game)
    wanted = game.var("VAR_KANTO_RESORT_GORGEOUS_REQUESTED_MON")
    reward = game.var("VAR_KANTO_RESORT_GORGEOUS_REWARD")
    asked = joined(game, since)
    if 0 < wanted < 0xFFFF:
        game.give_mon(wanted, 20)
    before = bag(game)
    since = talk(game, "FiveIsland_ResortGorgeous_House", (4, 4), "RIGHT")
    converse(game)
    after = bag(game)
    got = sum(q for pocket in after.values() if isinstance(pocket, list) for n, _, q in pocket if n == reward)
    had = sum(q for pocket in before.values() if isinstance(pocket, list) for n, _, q in pocket if n == reward)
    return wanted, reward, got - had, asked[-100:], joined(game, since)[-150:]


@part("poupees")
def dolls(game):
    game.dev("jeu.stat", names.number("GAME_STAT_KANTO_ENTERED_HOF"), 0)     # (compteur de Kanto)
    game.warp("FourIsland_LoreleisHouse", 7, 6); game.wait(60)
    none = game.dev("carte.objets").count("\n")
    game.dev("jeu.stat", names.number("GAME_STAT_KANTO_ENTERED_HOF"), 200)
    game.warp("FourIsland_LoreleisHouse", 7, 6); game.wait(60)
    log(game, "poupees")
    return none, game.dev("carte.objets").count("\n")


@part("effaceur")
def deleter(game):
    before = moves(game, 1)
    since = talk(game, "FuchsiaCity_House3", (4, 4))
    converse(game, slot=1, forget=0)
    return before, moves(game, 1), joined(game, since)[-160:]


@part("surnoms")
def name_rater(game):
    screens = len(game.cb2s)
    since = talk(game, "LavenderTown_House2", (4, 4))
    converse(game, slot=1)
    return [n for _, n in game.cb2s[screens:] if "Naming" in n][:1], joined(game, since)[-160:]


@part("cap falaise")
def cape_brink(game):
    since = talk(game, "TwoIsland_CapeBrink_House", (4, 4))
    converse(game, slot=0, forget=0)
    # ChooseMonForMoveTutor de RF (2026-11-04) : le POKéMON de tête, sans « Enseigner à quel POKéMON? »
    return (moves(game, 0), str(game.flag("FLAG_KANTO_TUTOR_FRENZY_PLANT")).strip(), joined(game, since)[-160:],
            "Enseigner à quel" in joined(game, since))


def play(game):
    continue_game(game)
    game.give_mon("SPECIES_VENUSAUR", 50)
    game.give_mon("SPECIES_PIKACHU", 20)
    game.dev("joueur.amitie", 0, 255)
    game.flag("FLAG_SYS_POKEMON_GET", 1)
    for run in (silph, rocket, badges, powder, daisy, resort, dolls, deleter, name_rater, cape_brink):
        run(game)
    game.note("résultats : " + " | ".join(f"{k} = {str(v)[:300]}" for k, v in RESULTS.items()))
    if isinstance(RESULTS["daisy"], tuple):
        game.note(f"daisy, 2e visite : {RESULTS['daisy'][1]}")

    # Vérifications
    ok = lambda name: not (isinstance(RESULTS[name], str) and RESULTS[name].startswith("ERREUR"))
    expect(game, ok("sylphe") and RESULTS["sylphe"][0] == "SilphCo_11F", f"Sylphe SARL : sortie au 11F ({RESULTS['sylphe']})")
    expect(game, ok("repaire") and RESULTS["repaire"][0] == "RocketHideout_B4F", f"repaire Rocket : B1F -> B4F ({RESULTS['repaire']})")
    expect(game, ok("badges") and "BADGE" in RESULTS["badges"], f"maison des badges ({str(RESULTS['badges'])[-120:]})")
    r = RESULTS["poudre"]
    expect(game, ok("poudre") and r[0] != r[1] and "Obtenu" in r[2], f"Poudre Baie échangée ({str(r)[:200]})")
    r = RESULTS["daisy"]
    # +3 (FRIENDSHIP_EVENT_MASSAGE), +1 si le POKéMON a été rencontré ici (AdjustFriendship) : ce PIKACHU, à Bourg Palette
    expect(game, ok("daisy") and r[0][0] == 104 and r[0][1] == 0 and "NINA" in r[1] and "bichonne un" not in r[1],
           f"Daisy : amitié 100 -> 104, attente remise à 0, puis plus de massage ({str(r)[-200:]})")
    r = RESULTS["resort"]
    expect(game, ok("resort") and r[0] > 0 and r[2] == 1, f"Resort Gorgeous : POKéMON demandé, récompense ({r})")
    r = RESULTS["poupees"]
    expect(game, ok("poupees") and r[1] >= r[0] + 8, f"poupées de Lorelei : 8 de plus avec 200 entrées au Panthéon ({r})")
    r = RESULTS["effaceur"]
    expect(game, ok("effaceur") and r[1] == r[0][1:] + [0], f"effaceur : 1re capacité oubliée, les autres remontent ({r})")
    r = RESULTS["surnoms"]
    expect(game, ok("surnoms") and r[0], f"vérificateur de surnoms : écran des noms ({r})")
    r = RESULTS["cap falaise"]
    expect(game, ok("cap falaise") and names.number("MOVE_FRENZY_PLANT") in r[0] and r[1] in ("1", "True"),
           f"Cap Falaise : VÉGÉ-ATTAQUE apprise ({r})")
    expect(game, ok("cap falaise") and not r[3], f"Cap Falaise : au POKéMON de tête, sans choisir dans l'équipe ({r})")
