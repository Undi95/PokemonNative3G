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


def menu_index(game, since, label, first=None):
    """Place de label dans le dernier menu écrit depuis since (bloc de textes d'une même fenêtre, ou depuis la
    dernière entrée first quand un message a été écrit dans la même fenêtre juste avant le menu)."""
    shown = texts(game, since)
    last = max(i for i, (_, text) in enumerate(shown) if text == label)
    if first is not None:
        return last - max(i for i, (_, text) in enumerate(shown[:last + 1]) if text == first)
    window = shown[last][0]
    start = last
    while start > 0 and shown[start - 1][0] == window:
        start -= 1
    return last - start


def pick(game, since, label, gap=12, first=None):
    """Choisit label dans le menu qui vient de s'ouvrir (curseur sur la 1re entrée)."""
    index = menu_index(game, since, label, first)
    if index:
        game.tap("DOWN", index, gap=gap); game.wait(10)
    game.tap("A")


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
        if box and box[-1].rstrip().endswith("▼"):
            game.tap("A", gap=4)
        game.wait(26)
    raise GameError(f"pas de menu de combat : {game.describe()}")


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
