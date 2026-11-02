#!/usr/bin/env python3
"""Vérifie le rapport de bug rejouable (src/platform/devtools.c, replay.py) de bout en bout, avec la build DEBUG du
PC : la lance (sans image ni son à l'écran) sur la sauvegarde « kanto » du banc, la fait jouer par sa console
(touche : écran titre, CONTINUER, quelques pas), demande un rapport (sys.rapport), puis le rejoue dans le banc
headless : la dernière image du rejeu doit être celle du rapport.

usage: report_check.py BINAIRE        (build DEBUG Windows ou Linux)
"""

import json
import os
import shutil
import socket
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from headless import BUILD_DIR, fixture  # noqa: E402


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    binary = os.path.abspath(sys.argv[1])
    live = os.path.join(BUILD_DIR, "report_check")
    shutil.rmtree(live, ignore_errors=True)
    os.makedirs(live)
    shutil.copy(fixture(binary, "kanto"), os.path.join(live, "game.sav"))
    # Le dossier des données (et des rapports) est celui du jeu quand pokeemerald.sav y est (FindDataFiles)
    open(os.path.join(live, "pokeemerald.sav"), "wb").close()

    env = dict(os.environ, SDL_VIDEODRIVER="dummy", SDL_AUDIODRIVER="dummy")
    with open(os.path.join(live, "sortie.txt"), "w") as output:
        game = subprocess.Popen([binary, "--save", "game.sav", "--config", "game.ini", "--devtools", "7790"], cwd=live,
                                env=env, stdout=output, stderr=subprocess.STDOUT)
    try:
        for _ in range(50):
            try:
                sock = socket.create_connection(("127.0.0.1", 7790), timeout=10)
                break
            except OSError:
                time.sleep(0.2)
        else:
            sys.exit("la console du jeu ne répond pas")
        reader = sock.makefile("r", encoding="utf-8")

        def command(line):
            sock.sendall((line + "\n").encode())
            return json.loads(reader.readline())

        def press(buttons, frames, seconds):
            command(f"touche {buttons} {frames}")
            time.sleep(seconds)

        time.sleep(4)
        press("START", 4, 2); press("START", 4, 3); press("A", 4, 3); press("A", 4, 4)   # titre, CONTINUER
        for direction in ("UP", "UP", "LEFT", "LEFT", "DOWN"):
            press(direction, 16, 0.8)
        reply = command("sys.rapport")["reply"]
    finally:
        game.kill()
    reports = sorted(os.listdir(os.path.join(live, "rapports")))
    if not reports:
        sys.exit(f"pas de rapport :\n{reply}")
    print(reply.splitlines()[1])
    replay = subprocess.run([sys.executable, os.path.join(os.path.dirname(os.path.abspath(__file__)), "replay.py"),
                             binary, os.path.join(live, "rapports", reports[-1])])
    print("RAPPORT OK : le rejeu retrouve la même image" if replay.returncode == 0 else "RAPPORT EN ÉCHEC")
    sys.exit(replay.returncode)


if __name__ == "__main__":
    main()
