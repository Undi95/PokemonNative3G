"""Tests Android dans l'émulateur (tools/env, preparer-tests.bat) avec l'APK debug :

    python test/android/run.py [nom...]      # noms : zones, doigts, reset, manette, sauvegarde, arriereplan

- zones : chaque touche tactile (A, B, L, R, SELECT, START, croix en 8 directions) arrive au jeu ;
- doigts : plusieurs doigts à la fois (sendevent, multi-touch) ;
- reset : RESET effleuré ne fait rien, maintenu 0,3 s relance le jeu ;
- manette : manette HID virtuelle (comme une manette Bluetooth) : boutons, croix, stick ;
- sauvegarde : une sauvegarde du PC (banc headless, fixture hoenn) se continue sur Android ; sauvegarder en jeu,
  fermer l'appli, relancer : on reprend au même endroit ;
- arriereplan : retour à l'écran d'accueil puis à l'appli : la partie continue (pas de redémarrage).
"""
import os
import re
import shutil
import sys
import tempfile
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from android import PACKAGE, REPO, Emulator, HidGamepad  # noqa: E402

EXE = os.path.join(REPO, "out", "winwsl", "pokeemeraude64.exe")
failures = []
INTRO_CB2 = ("CB2_InitCopyrightScreenAfterBootup", "CB2_Intro", "MainCB2")


def check(condition, message):
    print(("  OK     " if condition else "  ÉCHEC  ") + message, flush=True)
    if not condition:
        failures.append(message)


def fresh_launch(emu, clear=False):
    emu.stop_app()
    if clear:
        emu.shell("pm", "clear", PACKAGE)
    emu.launch()


def to_main_menu(emu):
    """Intro puis écran titre puis menu principal (START, comme le banc headless)."""
    for _ in range(12):
        if emu.cb2() == "CB2_MainMenu":
            emu.wait_frames(60)
            return True
        emu.press("START", 4, 80)
    return emu.cb2() == "CB2_MainMenu"


def continue_game(emu):
    if not to_main_menu(emu):
        return False
    emu.press("A", 4, 200)                     # CONTINUER
    for _ in range(40):
        if emu.free():
            return True
        emu.wait_frames(30)
    return False


def position(emu):
    info = emu.dev("carte.info")
    match = re.search(r"joueur \(?(-?\d+)[, ]+(-?\d+)", info)
    first = info.splitlines()[0] if info else ""
    return first, match.groups() if match else None


# --- tests -----------------------------------------------------------------------------------------------------
def zones_test(emu):
    print("Touches tactiles (une à une)")
    fresh_launch(emu, clear=True)
    emu.wait_frames(120)
    for name in ("B", "L", "R", "SELECT", "UP", "DOWN", "LEFT", "RIGHT", "UP+LEFT", "UP+RIGHT", "DOWN+LEFT",
                 "DOWN+RIGHT", "A", "START"):
        marker = emu.key_marker()
        emu.hold_zone(name, 120)
        emu.wait_frames(6)
        combos = emu.keys_since(marker)
        wanted = set(name.split("+"))
        got = [c for c in combos if c != "-"]
        check(any(set(c.split("+")) == wanted for c in got), f"{name} -> reçu {got}")


def fingers_test(emu):
    print("Plusieurs doigts à la fois")
    for points in (["A", "RIGHT"], ["B", "UP", "R"], ["L", "DOWN+LEFT"]):
        marker = emu.key_marker()
        emu.fingers(points, 300)
        emu.wait_frames(6)
        wanted = set("+".join(points).split("+"))
        got = [c for c in emu.keys_since(marker) if c != "-"]
        check(any(set(c.split("+")) == wanted for c in got), f"{' + '.join(points)} ensemble -> reçu {got}")


def reset_test(emu):
    print("RESET (maintenu 0,3 s)")
    fresh_launch(emu)
    check(to_main_menu(emu), "menu principal atteint")
    emu.tap_zone("RESET")
    emu.wait_frames(60)
    check(emu.cb2() == "CB2_MainMenu", f"RESET effleuré : rien (cb2 {emu.cb2()})")
    emu.hold_zone("RESET", 150)
    emu.wait_frames(60)
    check(emu.cb2() == "CB2_MainMenu", f"RESET 0,15 s : rien (cb2 {emu.cb2()})")
    emu.hold_zone("RESET", 600)
    emu.wait_frames(30)
    check(emu.cb2() in INTRO_CB2, f"RESET 0,6 s : le jeu repart de l'intro (cb2 {emu.cb2()})")


def gamepad_test(emu):
    print("Manette HID virtuelle (comme une manette Bluetooth)")
    pad = HidGamepad(emu)
    try:
        time.sleep(1.5)
        if not emu.sock:
            emu.open_console()
        connected = "Controller connected" in emu.shell("logcat", "-d", "-s", "SDL/APP:*", "stdout:*", "*:I", check=False)
        print(f"    manette annoncée par SDL dans logcat : {connected}")
        for button, wanted in (("A", "A"), ("B", "B"), ("X", "B"), ("START", "START"), ("SELECT", "SELECT"),
                               ("L1", "L"), ("R1", "R")):
            marker = emu.key_marker()
            pad.state([button])
            emu.wait_frames(8)
            pad.state()
            emu.wait_frames(4)
            got = [c for c in emu.keys_since(marker) if c != "-"]
            check(any(wanted in c.split("+") for c in got), f"bouton {button} -> {wanted} (reçu {got})")
        for hat in ("UP", "DOWN", "LEFT", "RIGHT", "UP+RIGHT"):
            marker = emu.key_marker()
            pad.state(hat=hat)
            emu.wait_frames(8)
            pad.state()
            emu.wait_frames(4)
            got = [c for c in emu.keys_since(marker) if c != "-"]
            check(any(set(c.split("+")) == set(hat.split("+")) for c in got), f"croix {hat} (reçu {got})")
        for x, y, wanted in ((127, 0, "RIGHT"), (-127, 0, "LEFT"), (0, -127, "UP"), (0, 127, "DOWN")):
            marker = emu.key_marker()
            pad.state(x=x, y=y)
            emu.wait_frames(8)
            pad.state()
            emu.wait_frames(4)
            got = [c for c in emu.keys_since(marker) if c != "-"]
            check(any(wanted in c.split("+") for c in got), f"stick {x:+d},{y:+d} -> {wanted} (reçu {got})")
    finally:
        pad.close()


def make_pc_save(work):
    """Sauvegarde faite par l'exe Windows dans le banc headless : la fixture « hoenn » (scenarios/fixture_hoenn.py)."""
    sys.path.insert(0, os.path.join(REPO, "test", "headless"))
    import headless
    save = os.path.join(work, "pc.sav")
    shutil.copyfile(headless.fixture(EXE, "hoenn"), save)
    return save


def save_menu(emu):
    """START, l'entrée SAUVER du menu Start, OUI ; jusqu'au retour sur la carte."""
    emu.press("START", 4, 40)
    menu = emu.dev("jeu.menustart")
    index = next(int(l.split()[0]) for l in menu.splitlines()[1:] if "SAUV" in l.upper())
    cursor = int(re.search(r"curseur (\d+)", menu).group(1))
    for _ in range((index - cursor) % int(menu.split()[0])):
        emu.press("DOWN", 4, 6)
    emu.press("A", 4, 90)                      # SAUVER
    emu.press("A", 4, 120)                     # OUI
    for _ in range(30):
        if emu.free():
            return True
        emu.press("A", 4, 60)                  # écraser l'ancienne sauvegarde : OUI ; message de fin
    return emu.free()


def save_test(emu):
    print("Sauvegarde (du PC à Android, puis sauvegarder, fermer, relancer)")
    work = tempfile.mkdtemp(prefix="pn3g_android_")
    try:
        pc_save = make_pc_save(work)
        emu.push_save(pc_save)
        emu.launch()
        check(continue_game(emu), "sauvegarde du PC continuée sur Android")
        start = position(emu)
        print("    ", start)
        emu.press("RIGHT", 16, 30)
        emu.press("DOWN", 16, 30)
        moved = position(emu)
        before = emu.save_info()
        check(save_menu(emu), "sauvegarde en jeu (menu Start)")
        after = emu.save_info()
        check(after != before, f"fichier de sauvegarde réécrit ({before} -> {after})")
        emu.stop_app()
        check(not emu.running(), "appli fermée (force-stop)")
        emu.launch()
        check(continue_game(emu), "relance et CONTINUER")
        again = position(emu)
        print("    ", moved, "->", again)
        check(again == moved, "même carte et même position qu'à la sauvegarde")
    finally:
        shutil.rmtree(work, ignore_errors=True)


def background_test(emu):
    print("Arrière-plan puis retour")
    if not emu.free():
        fresh_launch(emu)
        check(continue_game(emu), "partie continuée")
    f0 = emu.frame()
    sound0 = emu.dev("son.etat").splitlines()[0]
    emu.close_console()
    emu.home()
    time.sleep(4)
    check(emu.running(), "l'appli tourne encore en arrière-plan")
    emu.shell("am", "start", "-n", f"fr.undi.pokemonnative3g.debug/fr.undi.pokemonnative3g.GameActivity")
    time.sleep(2)
    emu.open_console()
    f1 = emu.frame()
    emu.wait_frames(60)
    check(f1 >= f0, f"pas de redémarrage (image {f0} -> {f1})")
    check(f1 - f0 < 4 * 60, f"le jeu s'est mis en pause en arrière-plan ({f1 - f0} images en ~6 s)")
    check(emu.cb2() == "CB2_Overworld", f"toujours sur la carte (cb2 {emu.cb2()})")
    sound1 = emu.dev("son.etat").splitlines()[0]
    print("    son :", sound0, "->", sound1)
    check(sound1 == sound0, "même musique au retour")
    emu.screenshot(os.path.join(tempfile.gettempdir(), "pn3g_android_retour.png"))


TESTS = {"zones": zones_test, "doigts": fingers_test, "reset": reset_test, "manette": gamepad_test,
         "sauvegarde": save_test, "arriereplan": background_test}

if __name__ == "__main__":
    names = sys.argv[1:] or list(TESTS)
    start = time.time()
    emu = Emulator().start()
    emu.install()
    emu.as_root()
    for name in names:
        try:
            if name in ("zones", "doigts", "manette") and not emu.sock:
                fresh_launch(emu)
            TESTS[name](emu)
        except Exception as error:  # un test qui casse n'arrête pas les autres
            check(False, f"{name} : {type(error).__name__} {error}")
    print(f"{'ÉCHECS : ' + str(len(failures)) if failures else 'tout est OK'} ({time.time() - start:.0f} s)")
    sys.exit(1 if failures else 0)
