"""Banc du vrai exe Windows (pas le mode test headless) : vraies touches du clavier envoyées à la fenêtre du jeu par
messages Windows (WM_KEYDOWN / WM_KEYUP, sans prendre le focus au joueur), état lu par la console des outils de
debug. Sauvegarde et réglages à part (--save, --config) : la vraie partie du joueur n'est jamais touchée.

    game = DesktopGame(workdir).start()       # build DEBUG : out/winwsl/pokeemeraude64.exe
    game.dev("jeu.etat"); game.key("F5")      # outil de debug ; touche (nom de touche virtuelle Windows)
    game.capture("x.png"); game.stop()
"""
import ctypes
import ctypes.wintypes as wt
import json
import os
import socket
import subprocess
import tempfile
import time

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
DEFAULT_EXE = os.path.join(REPO, "out", "winwsl", "pokeemeraude64.exe")

user32 = ctypes.WinDLL("user32", use_last_error=True)
WM_KEYDOWN, WM_KEYUP = 0x0100, 0x0101
VK = {"F1": 0x70, "F2": 0x71, "F3": 0x72, "F4": 0x73, "F5": 0x74, "F6": 0x75, "F7": 0x76, "F8": 0x77,
      "RETURN": 0x0D, "ESCAPE": 0x1B, "SPACE": 0x20, "BACK": 0x08, "TAB": 0x09,
      "LEFT": 0x25, "UP": 0x26, "RIGHT": 0x27, "DOWN": 0x28}
VK.update({chr(c): c for c in range(ord("A"), ord("Z") + 1)})
EXTENDED = {"LEFT", "UP", "RIGHT", "DOWN"}

EnumWindowsProc = ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)


def windows_of(pid):
    found = []

    def callback(hwnd, _):
        owner = wt.DWORD()
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(owner))
        if owner.value == pid and user32.IsWindowVisible(hwnd):
            found.append(hwnd)
        return True
    user32.EnumWindows(EnumWindowsProc(callback), 0)
    return found


class DesktopError(Exception):
    pass


class DesktopGame:
    def __init__(self, workdir=None, exe=DEFAULT_EXE, port=7778):
        self.workdir = workdir or tempfile.mkdtemp(prefix="pn3g_desktop_")
        self.exe = exe
        self.port = port
        self.process = None
        self.hwnd = None
        self.sock = self.reader = None
        self.save = os.path.join(self.workdir, "pokeemerald.sav")
        self.config = os.path.join(self.workdir, "pokeemerald.ini")

    def start(self, args=(), timeout=30):
        if not os.path.exists(self.exe):
            raise DesktopError(f"pas d'exe : {self.exe}")
        command = [self.exe, "--save", self.save, "--config", self.config, "--devtools", str(self.port)] + list(args)
        self.process = subprocess.Popen(command, cwd=os.path.dirname(self.exe), stdout=subprocess.PIPE,
                                        stderr=subprocess.STDOUT)
        deadline = time.time() + timeout
        while time.time() < deadline:
            found = windows_of(self.process.pid)
            if found and self.hwnd is None:
                self.hwnd = found[0]
            if self.hwnd:
                try:
                    self.sock = socket.create_connection(("127.0.0.1", self.port), timeout=10)
                    self.reader = self.sock.makefile("r", encoding="utf-8")
                    self.dev("jeu.etat")
                    return self
                except (OSError, ValueError):
                    self.sock = self.reader = None
            if self.process.poll() is not None:
                raise DesktopError(f"le jeu s'est arrêté (code {self.process.returncode})")
            time.sleep(0.5)
        raise DesktopError("pas de fenêtre ou pas de console")

    def stop(self):
        for item in (self.reader, self.sock):
            try:
                if item:
                    item.close()
            except OSError:
                pass
        if self.process and self.process.poll() is None:
            self.process.terminate()
            try:
                self.process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                self.process.kill()

    def dev(self, *words):
        self.sock.sendall((" ".join(str(w) for w in words) + "\n").encode("utf-8"))
        line = self.reader.readline()
        if not line:
            raise DesktopError("la console s'est fermée")
        reply = json.loads(line)
        if reply.get("error"):
            raise DesktopError(f"{' '.join(map(str, words))} : {reply['error']}")
        return reply.get("reply")

    def frame(self):
        return int(self.dev("jeu.etat").split("image ")[1].split()[0])

    def wait_frames(self, n, timeout=60):
        """Attend n images du jeu (il tourne à 60 images par seconde)."""
        target = self.frame() + n
        deadline = time.time() + timeout
        while self.frame() < target:
            if time.time() > deadline:
                raise DesktopError("le jeu n'avance plus")
            time.sleep(0.02)

    def key(self, name, frames=6):
        """Appuie sur une touche du clavier (message à la fenêtre), la garde frames images. name = ce qui est écrit
        sur la touche ; sa position vient de la disposition du clavier en service, comme une vraie frappe."""
        vk = VK[name]
        scan = user32.MapVirtualKeyW(vk, 0)
        extended = (1 << 24) if name in EXTENDED else 0
        down = 1 | (scan << 16) | extended
        up = down | (1 << 30) | (1 << 31)
        user32.PostMessageW(self.hwnd, WM_KEYDOWN, vk, down)
        self.wait_frames(frames)
        user32.PostMessageW(self.hwnd, WM_KEYUP, vk, up)
        self.wait_frames(2)

    def key_char(self, char, frames=6):
        """La touche qui tape ce caractère sans majuscule ni AltGr sur le clavier en service (é sur un AZERTY) ;
        False si ce clavier ne l'a pas."""
        result = user32.VkKeyScanW(ord(char))
        if result == -1 or (result >> 8) & 0xFF:
            return False
        vk = result & 0xFF
        name = f"VK{vk:02X}"
        VK[name] = vk
        self.key(name, frames)
        return True

    def key_marker(self):
        """Repère dans les touches reçues par le jeu (console « touches ») : images depuis le lancement."""
        return int(self.dev("touches", 0).split()[1])

    def pressed_since(self, marker, count=60):
        """Boutons reçus par le jeu depuis le repère."""
        buttons = set()
        for line in self.dev("touches", count).splitlines()[1:]:
            start, frames, combo = line.split()
            if int(start) + int(frames) > marker and combo != "-":
                buttons |= set(combo.split("+"))
        return buttons

    def capture(self, path):
        ppm = os.path.join(self.workdir, "capture.ppm")
        self.dev("capture", ppm)
        from PIL import Image
        Image.open(ppm).save(path)
        return path

    def cb2(self):
        return next(line.split(" ", 1)[1] for line in self.dev("jeu.etat").splitlines() if line.startswith("cb2 "))
