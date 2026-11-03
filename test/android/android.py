"""Banc de test Android : l'émulateur de tools/env (preparer-tests.bat), l'APK debug, adb et la console des outils
de debug (adb forward tcp:7777, comme test/headless/dev.py).

    emu = Emulator(); emu.start()               # téléphone virtuel « pn3g », démarré et prêt
    emu.install(APK); emu.launch()              # l'APK debug (fr.undi.pokemonnative3g.debug)
    emu.dev("carte.info")                       # un outil de debug, dans la partie en cours
    emu.tap_zone("A"); emu.hold_zone("RESET", 500)  # les touches tactiles du jeu (src/platform/touch.c)
    emu.screenshot("x.png"); emu.stop_app(); emu.kill()

Les zones tactiles sont recalculées comme LayOut() de src/platform/touch.c, en pixels de l'écran en paysage.
"""
import json
import os
import re
import socket
import subprocess
import sys
import time

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
ENV = os.path.join(REPO, "tools", "env")
SDK = os.path.join(ENV, "android-sdk")
ADB = os.path.join(SDK, "platform-tools", "adb.exe" if os.name == "nt" else "adb")
EMULATOR = os.path.join(SDK, "emulator", "emulator.exe" if os.name == "nt" else "emulator")
PACKAGE = "fr.undi.pokemonnative3g.debug"
ACTIVITY = "fr.undi.pokemonnative3g.GameActivity"
DEFAULT_APK = os.path.join(REPO, "out", "android", "PokemonNative3G-debug.apk")
CONSOLE_PORT = 7777
DISPLAY_WIDTH, DISPLAY_HEIGHT = 240, 160
# Codes evdev (linux/input-event-codes.h)
EV_SYN, EV_KEY, EV_ABS = 0, 1, 3
BTN_TOUCH = 0x14A
ABS_MT_SLOT, ABS_MT_POSITION_X, ABS_MT_POSITION_Y, ABS_MT_TRACKING_ID = 0x2F, 0x35, 0x36, 0x39


def tool_env():
    env = dict(os.environ)
    env.update(ANDROID_SDK_ROOT=SDK, ANDROID_HOME=SDK, ANDROID_AVD_HOME=os.path.join(ENV, "avd"),
               ANDROID_EMULATOR_HOME=os.path.join(ENV, "avd"), ANDROID_USER_HOME=os.path.join(ENV, "avd"))
    return env


class AndroidError(Exception):
    pass


class Emulator:
    def __init__(self, avd="pn3g", serial=None):
        self.avd = avd
        self.serial = serial
        self.process = None
        self.sock = None
        self.reader = None

    # --- adb ----------------------------------------------------------------------------------------------------
    def adb(self, *args, check=True, binary=False, timeout=120):
        command = [ADB] + (["-s", self.serial] if self.serial else []) + [str(a) for a in args]
        result = subprocess.run(command, capture_output=True, timeout=timeout, env=tool_env())
        if check and result.returncode != 0:
            raise AndroidError(f"adb {' '.join(map(str, args))} : {result.stderr.decode(errors='replace').strip()}")
        return result.stdout if binary else result.stdout.decode(errors="replace")

    def shell(self, *args, **kwargs):
        return self.adb("shell", *args, **kwargs)

    # --- émulateur ----------------------------------------------------------------------------------------------
    def running_emulators(self):
        return re.findall(r"^(emulator-\d+)\s+device", self.adb("devices", check=False), re.M)

    def start(self, window=False, timeout=900, wipe=False):
        """Démarre le téléphone virtuel (sans fenêtre par défaut) et attend la fin du démarrage d'Android.
        Un émulateur déjà lancé est réutilisé. Le premier démarrage (données neuves) prend plusieurs minutes."""
        if not wipe and self.running_emulators():
            self.serial = self.running_emulators()[0]
        else:
            args = [EMULATOR, "-avd", self.avd, "-no-boot-anim", "-no-snapshot", "-gpu", "host", "-netdelay", "none",
                    "-netspeed", "full"]
            if not window:
                args.append("-no-window")
            if wipe:
                args.append("-wipe-data")
            log = open(os.path.join(ENV, "emulateur.log"), "w")
            self.process = subprocess.Popen(args, env=tool_env(), stdout=log, stderr=subprocess.STDOUT)
        deadline = time.time() + timeout
        while time.time() < deadline:
            found = self.running_emulators()
            if found:
                self.serial = self.serial or found[0]
                if self.shell("getprop", "sys.boot_completed", check=False).strip() == "1":
                    self.shell("input", "keyevent", "KEYCODE_WAKEUP", check=False)
                    self.shell("wm", "dismiss-keyguard", check=False)
                    # sinon la bulle « Viewing full screen » d'Android couvre le jeu au premier lancement
                    self.shell("settings", "put", "secure", "immersive_mode_confirmations", "confirmed", check=False)
                    return self
            if self.process and self.process.poll() is not None:
                raise AndroidError(f"l'émulateur s'est arrêté (code {self.process.returncode}, tools/env/emulateur.log)")
            time.sleep(2)
        raise AndroidError("l'émulateur n'a pas fini de démarrer (tools/env/emulateur.log)")

    def kill(self):
        self.close_console()
        if self.serial:
            self.adb("emu", "kill", check=False)
        if self.process:
            try:
                self.process.wait(timeout=60)
            except subprocess.TimeoutExpired:
                self.process.kill()

    # --- application --------------------------------------------------------------------------------------------
    def install(self, apk=DEFAULT_APK):
        if not os.path.exists(apk):
            raise AndroidError(f"pas d'APK debug : {apk} (bash build-all.sh, ou docker/build-android.sh FLAVOR=debugtools)")
        self.adb("install", "-r", "-g", apk, timeout=600)

    def launch(self, wait_console=True, timeout=60):
        self.shell("am", "start", "-n", f"{PACKAGE}/{ACTIVITY}")
        if wait_console:
            self.open_console(timeout)

    def stop_app(self):
        self.close_console()
        self.shell("am", "force-stop", PACKAGE)

    def home(self):
        self.shell("input", "keyevent", "KEYCODE_HOME")

    def running(self):
        return self.shell("pidof", PACKAGE, check=False).strip() != ""

    # Sauvegarde et réglages : stockage interne de l'appli (SDL_GetPrefPath) ; rapports de bug : stockage partagé
    DATA_DIR = f"/data/data/{PACKAGE}/files"
    REPORT_DIR = f"/sdcard/Android/data/{PACKAGE}/files/rapports"

    def as_root(self):
        """adb root (image Google APIs) : accès aux fichiers de l'appli et à /dev/input. Coupe la console un instant."""
        if "uid=0" in self.shell("id"):
            return
        console = self.sock is not None
        self.close_console()
        self.adb("root", check=False)
        time.sleep(2)
        self.adb("wait-for-device")
        if console:
            self.open_console()

    def files(self, path=""):
        """Fichiers de l'appli : sauvegarde (pokeemerald.sav), réglages (pokeemerald.ini)."""
        self.as_root()
        return self.shell("ls", "-la", f"{self.DATA_DIR}/{path}", check=False)

    def push_save(self, local):
        """Pose une sauvegarde (appli arrêtée), propriétaire = l'appli."""
        self.as_root()
        self.shell("am", "force-stop", PACKAGE)
        owner = self.shell("stat", "-c", "%u:%g", f"/data/data/{PACKAGE}").strip()
        self.shell("mkdir", "-p", self.DATA_DIR)
        self.adb("push", local, f"{self.DATA_DIR}/pokeemerald.sav")
        self.shell("chown", "-R", owner, self.DATA_DIR)
        self.shell("chmod", "600", f"{self.DATA_DIR}/pokeemerald.sav")

    def pull_save(self, local):
        self.as_root()
        self.adb("pull", f"{self.DATA_DIR}/pokeemerald.sav", local)
        return local

    def save_info(self):
        """Empreinte (md5) de la sauvegarde sur le téléphone ("" si absente)."""
        self.as_root()
        return self.shell("md5sum", f"{self.DATA_DIR}/pokeemerald.sav", check=False).split(" ")[0].strip()

    # --- console des outils de debug ----------------------------------------------------------------------------
    def open_console(self, timeout=60):
        self.adb("forward", f"tcp:{CONSOLE_PORT}", f"tcp:{CONSOLE_PORT}")
        deadline = time.time() + timeout
        while time.time() < deadline:
            try:
                self.sock = socket.create_connection(("127.0.0.1", CONSOLE_PORT), timeout=10)
                self.reader = self.sock.makefile("r", encoding="utf-8")
                self.dev("jeu.etat")
                return
            except (OSError, ValueError, AndroidError):
                self.close_console()
                time.sleep(1)
        raise AndroidError("la console des outils de debug ne répond pas (APK debug lancé ?)")

    def close_console(self):
        for item in (self.reader, self.sock):
            try:
                if item:
                    item.close()
            except OSError:
                pass
        self.sock = self.reader = None

    def dev(self, *words):
        """Un outil de debug (dev.py), dans la partie en cours."""
        self.sock.sendall((" ".join(str(w) for w in words) + "\n").encode("utf-8"))
        line = self.reader.readline()
        if not line:
            raise AndroidError("la console s'est fermée")
        reply = json.loads(line)
        if reply.get("error"):
            raise AndroidError(f"{' '.join(map(str, words))} : {reply['error']}")
        return reply.get("reply")

    # --- état du jeu -------------------------------------------------------------------------------------------
    def frame(self):
        return int(self.dev("jeu.etat").split("image ")[1].split()[0])

    def wait_frames(self, n, timeout=60):
        """Attend n images du jeu (60 par seconde)."""
        target = self.frame() + n
        deadline = time.time() + timeout
        while self.frame() < target:
            if time.time() > deadline:
                raise AndroidError("le jeu n'avance plus")
            time.sleep(0.03)

    def cb2(self):
        return next(l.split(" ", 1)[1] for l in self.dev("jeu.etat").splitlines() if l.startswith("cb2 "))

    def free(self):
        """Sur la carte, commandes libres (comme state.free du banc headless)."""
        state = self.dev("jeu.etat")
        return "cb2 CB2_Overworld" in state and "fondu 0" in state and "controles bloques 0" in state

    def press(self, buttons, frames=4, gap=10):
        """Boutons injectés par la console (« touche A+UP 4 »), puis gap images d'attente."""
        self.dev("touche", buttons, frames)
        self.wait_frames(frames + gap)

    # --- écran et gestes ----------------------------------------------------------------------------------------
    def screen_size(self):
        """Taille de l'écran en paysage (le jeu est en sensorLandscape)."""
        match = re.search(r"(\d+)x(\d+)", self.shell("wm", "size"))
        w, h = int(match.group(1)), int(match.group(2))
        return max(w, h), min(w, h)

    def screenshot(self, path):
        data = self.adb("exec-out", "screencap", "-p", binary=True)
        with open(path, "wb") as f:
            f.write(data)
        return path

    def game_frame(self):
        """Cadre de la fenêtre du jeu sur l'écran (x0, y0, x1, y1) : elle évite l'encoche de la caméra."""
        windows = self.shell("dumpsys", "window", "windows")
        block = windows.split(f"{PACKAGE}/{ACTIVITY}}}:", 1)
        if len(block) < 2:
            raise AndroidError("fenêtre du jeu introuvable (appli lancée ?)")
        match = re.search(r" frame=\[(\d+),(\d+)\]\[(\d+),(\d+)\]", block[1])
        return tuple(int(v) for v in match.groups())

    def zones(self):
        """Centres des zones tactiles du jeu en pixels de l'écran (LayOut de src/platform/touch.c, dans la fenêtre)."""
        x0, y0, x1, y1 = self.game_frame()
        w, h = x1 - x0, y1 - y0
        u = h / 100.0
        scale = min(w // DISPLAY_WIDTH, h // DISPLAY_HEIGHT)
        side = (w - DISPLAY_WIDTH * max(scale, 1)) / 2.0
        left_x = max(side / 2, 20 * u)
        right_x = w - left_x
        r = 9 * u
        dpad_r = min(max(side * 0.42, 15 * u), 24 * u)
        lr_w = max(side * 0.8, 26 * u)
        zones = {
            "DPAD": (left_x, 58 * u, dpad_r),
            "A": (right_x + r * 1.15, 52 * u), "B": (right_x - r * 1.15, 66 * u),
            "L": (lr_w / 2, 5.5 * u), "R": (w - lr_w / 2, 5.5 * u),
            "SELECT": (w / 2 - 26 * u, h - 4.5 * u), "RESET": (w / 2, h - 4.5 * u), "START": (w / 2 + 26 * u, h - 4.5 * u),
            "FAST": (w / 2, 4.5 * u),
        }
        return {name: (z[0] + x0, z[1] + y0) + z[2:] for name, z in zones.items()}

    def zone_point(self, name):
        zones = self.zones()
        if name in ("UP", "DOWN", "LEFT", "RIGHT", "UP+LEFT", "UP+RIGHT", "DOWN+LEFT", "DOWN+RIGHT"):
            x, y, r = zones["DPAD"]
            dx = (-1 if "LEFT" in name else 1 if "RIGHT" in name else 0) * r * 0.7
            dy = (-1 if "UP" in name else 1 if "DOWN" in name else 0) * r * 0.7
            return int(x + dx), int(y + dy)
        x, y = zones[name][:2]
        return int(x), int(y)

    def tap_zone(self, name):
        x, y = self.zone_point(name)
        self.shell("input", "tap", x, y)

    def hold_zone(self, name, ms):
        x, y = self.zone_point(name)
        self.shell("input", "swipe", x, y, x, y, ms)

    def keyevent(self, key, source=None):
        """Touche Android (KEYCODE_…) ; source="gamepad" : comme une manette (input gamepad keyevent)."""
        self.shell("input", *([source] if source else []), "keyevent", key)

    # --- plusieurs doigts (sendevent sur l'écran tactile virtuel, protocole multi-touch B) ---------------------
    def touch_device(self):
        """Écran tactile de l'affichage principal : /dev/input/eventN, maximum des axes, taille naturelle."""
        if getattr(self, "_touch", None) is None:
            self.as_root()          # sendevent écrit dans /dev/input
            listing = self.shell("getevent", "-pl")
            device = re.search(r"add device \d+: (/dev/input/event\d+)\s+name:\s+\"virtio_input_multi_touch_1\"", listing)
            maximum = int(re.search(r"ABS_MT_POSITION_X\s*: value \d+, min 0, max (\d+)", listing).group(1))
            natural = re.search(r"real (\d+) x (\d+)", self.shell("dumpsys", "display"))
            self._touch = (device.group(1), maximum, int(natural.group(1)), int(natural.group(2)))
        return self._touch

    def rotation(self):
        return int(re.search(r"mCurrentRotation=ROTATION_(\d+)", self.shell("dumpsys", "window", "displays")).group(1)) // 90

    def to_device(self, x, y):
        """Point de l'écran (paysage) vers les axes de l'écran tactile (orientation naturelle, portrait)."""
        _, maximum, nw, nh = self.touch_device()
        rotation = self.rotation()
        if rotation == 1:
            nx, ny = nw - y, x
        elif rotation == 3:
            nx, ny = y, nh - x
        else:
            nx, ny = x, y
        return int(nx * maximum / nw), int(ny * maximum / nh)

    def fingers(self, points, ms):
        """Pose un doigt sur chaque point (x, y de l'écran ou nom de zone), les garde ms millisecondes, les lève.
        Par un écran tactile virtuel multi-touch (outil « uinput » d'Android) : écrire dans le nœud de l'écran virtio
        de l'émulateur (sendevent) n'arrive pas jusqu'à Android."""
        if getattr(self, "_touchscreen", None) is None:
            self._touchscreen = VirtualTouchscreen(self)
            time.sleep(1.5)                      # le temps qu'Android l'ajoute
        screen = self._touchscreen
        down = []
        for slot, point in enumerate(points):
            x, y = self.to_device(*(self.zone_point(point) if isinstance(point, str) else point))
            down += [EV_ABS, ABS_MT_SLOT, slot, EV_ABS, ABS_MT_TRACKING_ID, 100 + slot,
                     EV_ABS, ABS_MT_POSITION_X, x, EV_ABS, ABS_MT_POSITION_Y, y]
        down += [EV_KEY, BTN_TOUCH, 1, EV_SYN, 0, 0]
        up = []
        for slot in range(len(points)):
            up += [EV_ABS, ABS_MT_SLOT, slot, EV_ABS, ABS_MT_TRACKING_ID, -1]
        up += [EV_KEY, BTN_TOUCH, 0, EV_SYN, 0, 0]
        screen.send({"id": 1, "command": "inject", "events": down})
        screen.send({"id": 1, "command": "delay", "duration": ms})
        screen.send({"id": 1, "command": "inject", "events": up})
        time.sleep(ms / 1000 + 0.2)

    def key_marker(self):
        """Repère dans les touches reçues par le jeu (console « touches ») : images depuis le lancement."""
        return int(self.dev("touches", 0).split()[1])

    def keys_since(self, marker, count=60):
        """Combinaisons de boutons reçues par le jeu depuis le repère (« A+UP » ; « - » = rien)."""
        combos = []
        for line in self.dev("touches", count).splitlines()[1:]:
            start, frames, combo = line.split()
            if int(start) + int(frames) > marker:
                combos.append(combo)
        return combos

    def pressed_since(self, marker):
        """Tous les boutons reçus depuis le repère."""
        return {button for combo in self.keys_since(marker) for button in combo.split("+") if button != "-"}


class VirtualTouchscreen:
    """Écran tactile multi-touch virtuel (outil « uinput » d'Android, /dev/uinput), posé sur l'écran principal :
    axes 0..32767 dans l'orientation naturelle (portrait), comme l'écran virtio de l'émulateur (Emulator.to_device)."""

    def __init__(self, emulator, name="Ecran tactile de test"):
        emulator.as_root()
        self.process = subprocess.Popen([ADB, "-s", emulator.serial, "shell", "uinput", "-"], stdin=subprocess.PIPE,
                                        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, env=tool_env())
        # Codes numériques (l'outil d'Android 14 ne connaît pas encore les noms) : UI_SET_EVBIT 100, UI_SET_KEYBIT 101,
        # UI_SET_ABSBIT 103, UI_SET_PROPBIT 110 ; EV_SYN 0, EV_KEY 1, EV_ABS 3 ; INPUT_PROP_DIRECT 1
        axis = {"value": 0, "minimum": 0, "maximum": 32767, "fuzz": 0, "flat": 0, "resolution": 0}
        self.send({"id": 1, "command": "register", "name": name, "vid": 0x1209, "pid": 0x0002, "bus": "usb",
                   "configuration": [
                       {"type": 100, "data": [EV_KEY, EV_ABS, EV_SYN]},
                       {"type": 101, "data": [BTN_TOUCH]},
                       {"type": 103, "data": [ABS_MT_SLOT, ABS_MT_TRACKING_ID, ABS_MT_POSITION_X, ABS_MT_POSITION_Y]},
                       {"type": 110, "data": [1]}],
                   "abs_info": [
                       {"code": ABS_MT_SLOT, "info": dict(axis, maximum=9)},
                       {"code": ABS_MT_TRACKING_ID, "info": dict(axis, maximum=65535)},
                       {"code": ABS_MT_POSITION_X, "info": axis},
                       {"code": ABS_MT_POSITION_Y, "info": axis}]})

    def send(self, event):
        self.process.stdin.write((json.dumps(event) + "\n").encode())
        self.process.stdin.flush()

    def close(self):
        try:
            self.process.stdin.close()
            self.process.wait(timeout=10)
        except (OSError, subprocess.TimeoutExpired):
            self.process.kill()


class HidGamepad:
    """Manette HID virtuelle (outil « hid » d'Android, /dev/uhid) : le même chemin qu'une manette Bluetooth, qui est
    un périphérique HID (bus "bluetooth"). Boutons HID 1 à 16 = BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TL, BTN_TR,
    BTN_TL2, BTN_TR2, BTN_SELECT, BTN_START... (hid-input), croix = chapeau, stick = axes X et Y."""
    BUTTONS = {"A": 0, "B": 1, "X": 3, "Y": 4, "L1": 6, "R1": 7, "L2": 8, "R2": 9, "SELECT": 10, "START": 11}
    HAT = {"UP": 0, "UP+RIGHT": 1, "RIGHT": 2, "DOWN+RIGHT": 3, "DOWN": 4, "DOWN+LEFT": 5, "LEFT": 6, "UP+LEFT": 7}
    DESCRIPTOR = [
        0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0x85, 0x01,             # Generic Desktop, Game Pad, collection, rapport 1
        0x05, 0x09, 0x19, 0x01, 0x29, 0x10, 0x15, 0x00, 0x25, 0x01,  # 16 boutons
        0x75, 0x01, 0x95, 0x10, 0x81, 0x02,
        0x05, 0x01, 0x09, 0x39, 0x15, 0x00, 0x25, 0x07, 0x35, 0x00,  # chapeau 0..7 (8+ = relâché)
        0x46, 0x3B, 0x01, 0x65, 0x14, 0x75, 0x04, 0x95, 0x01, 0x81, 0x42,
        0x65, 0x00, 0x75, 0x04, 0x95, 0x01, 0x81, 0x03,              # bourrage
        0x09, 0x30, 0x09, 0x31, 0x15, 0x81, 0x25, 0x7F,              # X, Y : -127..127
        0x75, 0x08, 0x95, 0x02, 0x81, 0x02,
        0xC0,
    ]

    def __init__(self, emulator, name="Manette HID de test"):
        emulator.as_root()             # /dev/uhid
        self.process = subprocess.Popen([ADB, "-s", emulator.serial, "shell", "hid", "-"], stdin=subprocess.PIPE,
                                        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, env=tool_env())
        self.send({"id": 1, "command": "register", "name": name, "vid": 0x1209, "pid": 0x0001, "bus": "bluetooth",
                   "descriptor": self.DESCRIPTOR})
        self.state(None)

    def send(self, event):
        self.process.stdin.write((json.dumps(event) + "\n").encode())
        self.process.stdin.flush()

    def state(self, buttons=(), hat=None, x=0, y=0):
        """Boutons tenus (noms de BUTTONS), croix (nom de HAT ou None), stick -127..127."""
        mask = sum(1 << self.BUTTONS[b] for b in (buttons or ()))
        self.send({"id": 1, "command": "report",
                   "report": [1, mask & 0xFF, mask >> 8, self.HAT[hat] if hat else 0x0F, x & 0xFF, y & 0xFF]})

    def close(self):
        try:
            self.process.stdin.close()
            self.process.wait(timeout=10)
        except (OSError, subprocess.TimeoutExpired):
            self.process.kill()


if __name__ == "__main__":
    # Démarrage rapide : python test/android/android.py [--fenetre]
    emu = Emulator().start(window="--fenetre" in sys.argv)
    print("émulateur prêt :", emu.serial, emu.screen_size())
