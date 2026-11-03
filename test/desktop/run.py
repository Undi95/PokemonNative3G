"""Vérifications du vrai exe Windows (build DEBUG), hors du mode test : touche de reset, hasard et ID dresseur
d'un lancement à l'autre. Chaque lancement a son dossier (sauvegarde et réglages neufs).

    python test/desktop/run.py [EXE] [nom...]      # noms : reset, hasard, id
"""
import os
import re
import shutil
import sys
import tempfile
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from windows import DEFAULT_EXE, DesktopGame  # noqa: E402

failures = []


def check(condition, message):
    print(("  OK     " if condition else "  ÉCHEC  ") + message, flush=True)
    if not condition:
        failures.append(message)


def launch(exe, workdir, args=()):
    os.makedirs(workdir, exist_ok=True)
    return DesktopGame(workdir, exe=exe).start(args)


def wait_cb2(game, names, timeout_frames=1200):
    for _ in range(timeout_frames // 10):
        if game.cb2() in names:
            return True
        game.wait_frames(10)
    return False


def to_main_menu(game):
    """Écran titre puis menu principal (START deux fois, comme le scénario headless new_game)."""
    game.wait_frames(300)
    for _ in range(6):
        if game.cb2() == "CB2_MainMenu":
            return True
        game.key("RETURN")
        game.wait_frames(90)
    return game.cb2() == "CB2_MainMenu"


def reset_test(exe, root):
    print("Touche de reset (F5, key_reset dans pokeemerald.ini)")
    work = os.path.join(root, "reset")
    game = launch(exe, work)
    try:
        check(to_main_menu(game), "menu principal atteint")
        game.key("F5", frames=10)
        check(wait_cb2(game, ("CB2_InitCopyrightScreenAfterBootup", "CB2_Intro", "MainCB2"), 120),
              f"F5 relance le jeu (cb2 {game.cb2()})")
    finally:
        game.stop()
    ini = open(game.config, encoding="utf-8").read()
    check(re.search(r"^key_reset = F5$", ini, re.M) is not None, "key_reset = F5 écrit dans le .ini neuf")

    # Ancien .ini sans key_reset : la ligne est ajoutée au lancement
    old = "\n".join(line for line in ini.splitlines() if "key_reset" not in line and "Soft reset" not in line) + "\n"
    open(game.config, "w", encoding="utf-8").write(old)
    game = launch(exe, work)
    game.stop()
    ini = open(game.config, encoding="utf-8").read()
    check(ini.count("key_reset") == 1 and "key_reset = F5" in ini, "ligne key_reset ajoutée à un ancien .ini")

    # Touche changée : F6 relance, F5 ne fait plus rien
    open(game.config, "w", encoding="utf-8").write(ini.replace("key_reset = F5", "key_reset = F6"))
    game = launch(exe, work)
    try:
        check(to_main_menu(game), "menu principal atteint (key_reset = F6)")
        game.key("F5", frames=10)
        game.wait_frames(30)
        check(game.cb2() == "CB2_MainMenu", f"F5 ne relance plus le jeu (cb2 {game.cb2()})")
        game.key("F6", frames=10)
        check(wait_cb2(game, ("CB2_InitCopyrightScreenAfterBootup", "CB2_Intro", "MainCB2"), 120),
              f"F6 relance le jeu (cb2 {game.cb2()})")
    finally:
        game.stop()


def system_state(game):
    state = game.dev("sys.etat")
    rng = re.search(r"RNG ([0-9a-f]+) ([0-9a-f]+)", state).groups()
    trainer = re.search(r"ID dresseur (\d+) \(public (\d+), secret (\d+)\)", state).groups()
    return rng, tuple(int(v) for v in trainer)


def random_test(exe, root):
    print("Hasard d'un lancement à l'autre (graine prise au démarrage)")
    seen = []
    for i in range(3):
        game = launch(exe, os.path.join(root, f"hasard{i}"))
        try:
            game.wait_frames(60 - game.frame() if game.frame() < 60 else 0)
            seen.append(system_state(game)[0])
        finally:
            game.stop()
    print("   ", seen)
    check(len(set(seen)) == len(seen), "RNG différent à chaque lancement")


def new_game(game):
    """Menu principal > NOUVELLE PARTIE, discours de Birch (A en boucle, nom proposé), jusqu'au camion."""
    if not to_main_menu(game):
        return False
    return new_game_from_birch(game)


def new_game_from_birch(game):
    """A jusqu'à la première carte, le camion (le nom proposé par Birch est gardé)."""
    for _ in range(400):
        if game.cb2() == "CB2_Overworld":
            return True
        game.key("Z", frames=4)
        game.wait_frames(20)
    return False


def trainer_id_test(exe, root):
    print("ID dresseur d'une nouvelle partie (avant : partie basse toujours 0 sur PC)")
    ids = []
    for i in range(2):
        game = launch(exe, os.path.join(root, f"id{i}"))
        try:
            check(new_game(game), f"partie {i + 1} : nouvelle partie jusqu'au camion")
            ids.append(system_state(game)[1])
        finally:
            game.stop()
    print("   ", ids)
    check(all(public != 0 and secret != 0 for _, public, secret in ids), "parties publique et secrète non nulles")
    check(len(ids) == 2 and ids[0][0] != ids[1][0], "ID différent d'une partie à l'autre")


def tools_sweep(game, stage):
    """Toutes les commandes de la console sans argument : le jeu ne doit planter à aucune (sys.rapport exclu : il
    écrit dans le vrai dossier de données)."""
    tools = [line.split(" ")[0] for line in game.dev("aide").splitlines() if "(0 arg.)" in line]
    broken = []
    for tool in tools:
        if tool in ("sys.rapport", "aide"):
            continue
        try:
            game.dev(tool)
        except Exception as error:
            broken.append(f"{tool} ({type(error).__name__})")
            time.sleep(0.5)
            if game.process.poll() is not None:
                break
    check(not broken and game.process.poll() is None, f"{stage} : {len(tools) - 2} outils sans plantage {broken}")
    return game.process.poll() is None


def tools_test(exe, root):
    print("Outils de debug à chaque étape (intro, titre, menu, Birch, carte)")
    game = launch(exe, os.path.join(root, "outils"))
    try:
        if not tools_sweep(game, "copyright"):
            return
        game.wait_frames(400)
        if not tools_sweep(game, "intro"):
            return
        check(to_main_menu(game), "menu principal atteint")
        if not tools_sweep(game, "menu principal"):
            return
        game.key("Z")
        game.wait_frames(240)
        for _ in range(8):
            game.key("Z", frames=4)
            game.wait_frames(20)
        if not tools_sweep(game, f"discours de Birch ({game.cb2()})"):
            return
        check(new_game_from_birch(game), "jusqu'au camion")
        tools_sweep(game, "camion (carte)")
    finally:
        game.stop()


def keyboard_test(exe, root):
    print("Clavier : une touche du .ini = la touche où ce nom est écrit, quelle que soit la disposition")
    work = os.path.join(root, "clavier")
    game = launch(exe, work)
    try:
        game.wait_frames(30)
        for key, button in (("Z", "A"), ("X", "B"), ("RETURN", "START"), ("BACK", "SELECT"), ("A", "L"), ("S", "R"),
                            ("UP", "UP"), ("DOWN", "DOWN"), ("LEFT", "LEFT"), ("RIGHT", "RIGHT")):
            marker = game.key_marker()
            game.key(key)
            got = game.pressed_since(marker)
            check(button in got, f"touche {key} -> {button} (reçu {sorted(got)})")
    finally:
        game.stop()
    # Une touche qui n'existe que sur certains claviers : ù (AZERTY). Pas é : SDL garde la rangée des chiffres en 1 à 0
    # sur tous les claviers (sur AZERTY, la touche é s'appelle « 2 »)
    ini = open(game.config, encoding="utf-8").read()
    open(game.config, "w", encoding="utf-8").write(ini.replace("key_a = Z", "key_a = ù"))
    game = launch(exe, work)
    try:
        game.wait_frames(30)
        marker = game.key_marker()
        if game.key_char("ù"):
            got = game.pressed_since(marker)
            check("A" in got, f"key_a = ù : la touche ù -> A (reçu {sorted(got)})")
        else:
            print("    (pas de touche ù sur ce clavier : essai sauté)")
        marker = game.key_marker()
        game.key("Z")
        check("A" not in game.pressed_since(marker), "Z ne fait plus A")
    finally:
        game.stop()


TESTS = {"reset": reset_test, "hasard": random_test, "id": trainer_id_test, "outils": tools_test,
         "clavier": keyboard_test}

if __name__ == "__main__":
    args = sys.argv[1:]
    exe = args.pop(0) if args and args[0].endswith(".exe") else DEFAULT_EXE
    names = args or list(TESTS)
    root = tempfile.mkdtemp(prefix="pn3g_desktop_")
    start = time.time()
    try:
        for name in names:
            TESTS[name](exe, root)
    finally:
        shutil.rmtree(root, ignore_errors=True)
    print(f"{'ÉCHECS : ' + str(len(failures)) if failures else 'tout est OK'} ({time.time() - start:.0f} s)")
    sys.exit(1 if failures else 0)
