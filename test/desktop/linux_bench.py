"""Banc du vrai binaire Linux (build DEBUG), à lancer DANS la distribution WSL « PN3G-Linux » (preparer-tests.bat) :

    wsl -d PN3G-Linux -- python3 test/desktop/linux_bench.py [BINAIRE]     # depuis la racine du dépôt

Fenêtre (WSLg, X11), son (PulseAudio de WSLg, enregistré par parec), clavier (xdotool) et manette (uinput : une manette
Xbox 360 virtuelle, python3-evdev). Sauvegarde et réglages neufs dans un dossier temporaire. Sortie : OK / ÉCHEC.
"""
import array
import json
import os
import shutil
import socket
import subprocess
import sys
import tempfile
import time

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
DEFAULT_BINARY = os.path.join(REPO, "out", "linux", "pokeemeraude64")
PORT = 7779
failures = []


def check(condition, message):
    print(("  OK     " if condition else "  ÉCHEC  ") + message, flush=True)
    if not condition:
        failures.append(message)


class LinuxGame:
    def __init__(self, binary, workdir):
        self.binary, self.workdir = binary, workdir
        self.process = self.sock = self.reader = None

    def start(self, timeout=30):
        env = dict(os.environ, SDL_JOYSTICK_DISABLE_UDEV="1")   # pas de udevd dans WSL : /dev/input scruté directement
        self.process = subprocess.Popen(
            [self.binary, "--save", os.path.join(self.workdir, "pokeemerald.sav"), "--config",
             os.path.join(self.workdir, "pokeemerald.ini"), "--devtools", str(PORT)],
            cwd=self.workdir, env=env, stdout=open(os.path.join(self.workdir, "sortie.txt"), "w"),
            stderr=subprocess.STDOUT)
        deadline = time.time() + timeout
        while time.time() < deadline:
            try:
                self.sock = socket.create_connection(("127.0.0.1", PORT), timeout=10)
                self.reader = self.sock.makefile("r", encoding="utf-8")
                self.dev("jeu.etat")
                return self
            except OSError:
                self.sock = None
            if self.process.poll() is not None:
                raise RuntimeError(f"le jeu s'est arrêté (code {self.process.returncode}) : "
                                   + open(os.path.join(self.workdir, "sortie.txt")).read()[-800:])
            time.sleep(0.5)
        raise RuntimeError("pas de console")

    def stop(self):
        if self.sock:
            self.sock.close()
        if self.process and self.process.poll() is None:
            self.process.terminate()
            self.process.wait(timeout=10)

    def dev(self, *words):
        self.sock.sendall((" ".join(str(w) for w in words) + "\n").encode("utf-8"))
        reply = json.loads(self.reader.readline())
        if reply.get("error"):
            raise RuntimeError(f"{' '.join(map(str, words))} : {reply['error']}")
        return reply.get("reply")

    def frame(self):
        return int(self.dev("jeu.etat").split("image ")[1].split()[0])

    def wait_frames(self, n):
        target = self.frame() + n
        while self.frame() < target:
            time.sleep(0.02)

    def cb2(self):
        return next(l.split(" ", 1)[1] for l in self.dev("jeu.etat").splitlines() if l.startswith("cb2 "))

    def key_marker(self):
        """Repère dans les touches reçues (console « touches ») : images depuis le lancement."""
        return int(self.dev("touches", 0).split()[1])

    def keys_since(self, marker, count=60):
        """Combinaisons de boutons reçues par le jeu depuis le repère (« A+UP », « - » = rien)."""
        combos = []
        for line in self.dev("touches", count).splitlines()[1:]:
            start, frames, combo = line.split()
            if int(start) + int(frames) > marker:
                combos.append(combo)
        return combos

    def window(self):
        result = subprocess.run(["xdotool", "search", "--pid", str(self.process.pid)], capture_output=True, text=True)
        ids = result.stdout.split()
        return ids[-1] if ids else None

    def xkey(self, name, ms=120):
        """Une touche du clavier envoyée à la fenêtre du jeu (xdotool, XTEST)."""
        window = self.window()
        subprocess.run(["xdotool", "windowactivate", "--sync", window], capture_output=True)
        subprocess.run(["xdotool", "keydown", "--window", window, name], check=True)
        time.sleep(ms / 1000)
        subprocess.run(["xdotool", "keyup", "--window", window, name], check=True)


def focus(window, timeout=5):
    """Active la fenêtre et attend qu'elle soit la fenêtre active de X."""
    deadline = time.time() + timeout
    while time.time() < deadline:
        subprocess.run(["xdotool", "windowactivate", "--sync", window], capture_output=True, timeout=5)
        active = subprocess.run(["xdotool", "getactivewindow"], capture_output=True, text=True).stdout.strip()
        if active == window:
            time.sleep(0.3)
            return True
        time.sleep(0.3)
    return False


def wslg_ready(timeout=30):
    """Juste après le démarrage de la VM WSL, le son de WSLg n'est pas encore là (le jeu resterait muet)."""
    deadline = time.time() + timeout
    while time.time() < deadline:
        uptime = float(open("/proc/uptime").read().split()[0])
        if uptime > 20 and subprocess.run(["pactl", "info"], capture_output=True).returncode == 0:
            return True
        time.sleep(1)
    return False


def seen(game, marker, button):
    return any(button in combo.split("+") for combo in game.keys_since(marker))


def record_sound(seconds=3):
    """Ce qui sort des haut-parleurs de WSLg (moniteur de RDPSink), en s16 stéréo 44,1 kHz : crête et moyenne."""
    data = subprocess.run(["timeout", str(seconds), "parec", "-d", "RDPSink.monitor", "--raw", "--format=s16le",
                           "--rate=44100", "--channels=2"], capture_output=True).stdout
    samples = array.array("h", data[: len(data) // 2 * 2])
    if not samples:
        return 0, 0
    return max(abs(s) for s in samples), sum(abs(s) for s in samples) / len(samples)


def make_pad():
    from evdev import AbsInfo, UInput, ecodes as e
    capabilities = {
        e.EV_KEY: [e.BTN_SOUTH, e.BTN_EAST, e.BTN_NORTH, e.BTN_WEST, e.BTN_TL, e.BTN_TR, e.BTN_SELECT, e.BTN_START,
                   e.BTN_MODE, e.BTN_THUMBL, e.BTN_THUMBR],
        e.EV_ABS: [(e.ABS_X, AbsInfo(0, -32768, 32767, 16, 128, 0)), (e.ABS_Y, AbsInfo(0, -32768, 32767, 16, 128, 0)),
                   (e.ABS_RX, AbsInfo(0, -32768, 32767, 16, 128, 0)), (e.ABS_RY, AbsInfo(0, -32768, 32767, 16, 128, 0)),
                   (e.ABS_Z, AbsInfo(0, 0, 255, 0, 0, 0)), (e.ABS_RZ, AbsInfo(0, 0, 255, 0, 0, 0)),
                   (e.ABS_HAT0X, AbsInfo(0, -1, 1, 0, 0, 0)), (e.ABS_HAT0Y, AbsInfo(0, -1, 1, 0, 0, 0))],
    }
    # Manette Xbox 360 (045e:028e) : SDL la connaît (correspondance des boutons intégrée)
    return UInput(capabilities, name="Microsoft X-Box 360 pad", vendor=0x045E, product=0x028E, version=0x110,
                  bustype=e.BUS_USB)


def pad_press(game, pad, code, value=1, kind="key", frames=8):
    from evdev import ecodes as e
    pad.write(e.EV_KEY if kind == "key" else e.EV_ABS, code, value)
    pad.syn()
    game.wait_frames(frames)
    pad.write(e.EV_KEY if kind == "key" else e.EV_ABS, code, 0)
    pad.syn()
    game.wait_frames(4)


def main():
    binary = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_BINARY
    if not wslg_ready():
        print("  (WSLg : pas de serveur de son après 30 s)")
    subprocess.run(["modprobe", "uinput"], capture_output=True)
    subprocess.run(["modprobe", "evdev"], capture_output=True)
    subprocess.run(["modprobe", "joydev"], capture_output=True)
    work = tempfile.mkdtemp(prefix="pn3g_linux_")
    start = time.time()
    pad = None
    try:
        pad = make_pad()       # avant le jeu : branchée au démarrage
        time.sleep(0.5)
        game = LinuxGame(binary, work).start()
        try:
            print("Fenêtre")
            check(game.window() is not None, f"fenêtre X11 du jeu (WSLg) : {game.window()}")
            game.wait_frames(240)
            game.dev("capture", os.path.join(work, "titre.ppm"))
            check(os.path.getsize(os.path.join(work, "titre.ppm")) > 100000, "capture de l'écran titre")

            print("Son")
            peak, mean = record_sound(3)
            print(f"    crête {peak}, moyenne {mean:.0f}")
            check(peak > 1000, "le jeu fait du bruit (musique de l'intro, PulseAudio de WSLg)")

            print("Clavier (xdotool)")
            # La fenêtre doit avoir le focus avant la première touche (sinon elle se perd)
            check(focus(game.window()), "fenêtre du jeu active")
            # XWayland (WSLg) perd parfois la toute première frappe synthétique : une touche sans effet d'abord
            game.xkey("shift")
            game.wait_frames(10)
            for key, button in (("Return", "START"), ("z", "A"), ("x", "B"), ("Down", "DOWN"), ("q", "L"), ("s", "R")):
                marker = game.key_marker()
                game.xkey(key)
                game.wait_frames(10)
                check(seen(game, marker, button), f"touche {key} -> {button}")

            print("Manette (uinput, Xbox 360 virtuelle)")
            from evdev import ecodes as e
            for code, name, button in ((e.BTN_SOUTH, "A (sud)", "A"), (e.BTN_EAST, "B (est)", "B"),
                                       (e.BTN_START, "START", "START"), (e.BTN_SELECT, "SELECT", "SELECT"),
                                       (e.BTN_TL, "LB", "L"), (e.BTN_TR, "RB", "R")):
                marker = game.key_marker()
                pad_press(game, pad, code)
                check(seen(game, marker, button), f"bouton {name} -> {button}")
            for code, name, value, button in ((e.ABS_HAT0X, "croix", 1, "RIGHT"), (e.ABS_HAT0X, "croix", -1, "LEFT"),
                                              (e.ABS_HAT0Y, "croix", -1, "UP"), (e.ABS_HAT0Y, "croix", 1, "DOWN"),
                                              (e.ABS_X, "stick", 30000, "RIGHT"), (e.ABS_Y, "stick", -30000, "UP")):
                marker = game.key_marker()
                pad_press(game, pad, code, value, kind="abs")
                check(seen(game, marker, button), f"{name} {value:+d} -> {button}")
        finally:
            game.stop()
    finally:
        if pad:
            pad.close()
        shutil.rmtree(work, ignore_errors=True)
    print(f"{'ÉCHECS : ' + str(len(failures)) if failures else 'tout est OK'} ({time.time() - start:.0f} s)")
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
