# Aides pour piloter les menus par leurs textes (pas de play : la suite ne le lance pas).
from driver import mark, wait_until, wait_text


def open_start_entry(game, word):
    """Ouvre l'entrée du menu Start dont le nom contient word (le curseur est retenu d'une fois sur l'autre)."""
    wait_until(game, lambda s: s.free)
    game.tap("START"); game.wait(40)
    entries, cursor = game.start_menu()
    target = next(i for i, (_, name) in enumerate(entries) if word in name)
    down = (target - cursor) % len(entries)
    if down:
        game.tap("DOWN", down, gap=12); game.wait(10)
    game.tap("A")


def texts(game, since=0):
    """Les textes écrits depuis une marque : [(fenêtre, texte sur une ligne)], sans les curseurs."""
    return [(window, " ".join(text.split())) for _, window, text in game.texts[since:]
            if text.strip() not in ("▶", "")]


def menu_block(game, since, label, first=None):
    """(place de label, nombre d'entrées) dans le dernier menu écrit depuis since : bloc de textes d'une même
    fenêtre, ou depuis la dernière entrée first quand un message a été écrit dans la même fenêtre juste avant."""
    shown = texts(game, since)
    last = max(i for i, (_, text) in enumerate(shown) if text == label)
    window = shown[last][0]
    if first is not None:
        start = max(i for i, (_, text) in enumerate(shown[:last + 1]) if text == first)
    else:
        start = last
        while start > 0 and shown[start - 1][0] == window:
            start -= 1
    end = last
    while end + 1 < len(shown) and shown[end + 1][0] == window:
        end += 1
    return last - start, end - start + 1


def menu_index(game, since, label, first=None):
    return menu_block(game, since, label, first)[0]


def pick(game, since, label, gap=12, first=None, cursor=0):
    """Choisit label dans le menu qui vient de s'ouvrir ; cursor : place de départ du curseur (0, ou "last" pour la
    dernière entrée, comme le S.S. TIDAL)."""
    index, count = menu_block(game, since, label, first)
    start = count - 1 if cursor == "last" else cursor
    if index > start:
        game.tap("DOWN", index - start, gap=gap); game.wait(10)
    elif index < start:
        game.tap("UP", start - index, gap=gap); game.wait(10)
    game.tap("A")


def printer_waits(game):
    """Une imprimante de texte est arrêtée sur la flèche (RENDER_STATE_WAIT 1, RENDER_STATE_CLEAR 2 : fin de page ou
    de message, RENDER_STATE_SCROLL_START 3 : ligne à faire défiler) : elle attend A ; la chaîne n'a pas toujours de ▼
    à la fin."""
    return any(f" etat {state} " in line for line in game.dev("texte.imprimantes").splitlines() for state in (1, 2, 3))


def script_waits_button(game):
    """Le jeu attend A ou B : waitbuttonpress (WaitForAorBPress), ou une imprimante arrêtée sur la flèche."""
    if "WaitForAorBPress" in game.dev("scripts.contexte"):
        return True
    return printer_waits(game)


def press_until_free(game, button="B", limit=12, gap=40):
    for _ in range(limit):
        if game.state.free:
            break
        game.tap(button); game.wait(gap)
    wait_until(game, lambda s: s.free, limit=600)


def wild_battle(game, seed=4, place=("Route1", 12, 9)):
    """Va dans les hautes herbes (Route 1 de Kanto par défaut) et marche jusqu'à un combat sauvage ; la graine
    fixe la rencontre (4 : un RATTATA, comme kanto_bag_battle)."""
    from driver import GameError
    game.warp(*place); game.wait(30)
    game.dev("jeu.hasard", seed)
    y = place[2]
    for _ in range(80):
        if game.state.battle:
            break
        game.press("UP" if game.state.pos[1] == y else "DOWN", 16)
        game.wait(8)
    if not game.state.battle:
        raise GameError(f"pas de combat sauvage : {game.state}")


def wait_action_menu(game, since=None, limit=3000):
    """Jusqu'au menu ATTAQUE / SAC / POKéMON / FUITE (« Que doit faire … ? »), sans le valider : A seulement quand
    un message attend (il finit par ▼)."""
    from driver import GameError, saw_text
    since = mark(game) if since is None else since
    for _ in range(limit // 30):
        if saw_text(game, "Que doit faire", since):
            game.wait(40)
            return
        if not game.state.battle:
            raise GameError("combat fini avant le menu")
        box = [text for _, _, text in game.texts[since:] if text.strip() not in ("", "▶")]
        if (box and box[-1].rstrip().endswith("▼")) or printer_waits(game):
            game.tap("A", gap=4)
        game.wait(26)
    raise GameError(f"pas de menu de combat : {game.describe()} ; imprimantes : {game.dev('texte.imprimantes')}")


def bag(game):
    """joueur.sac : {poche: [(id, nom, quantité)]}, 'pc': [...], 'select': id."""
    result = {}
    for line in game.dev("joueur.sac").splitlines():
        if line.startswith("poche") or line.startswith("pc"):
            key, _, rest = line.partition(":")
            items = []
            for part in rest.split(","):
                part = part.strip()
                if part:
                    head, _, qty = part.rpartition(" x")
                    num, _, name = head.partition(" ")
                    items.append((int(num), name, int(qty)))
            result[key.strip()] = items
        elif line.startswith("enregistre"):
            result["select"] = int(line.split()[-1])
    return result
