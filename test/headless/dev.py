#!/usr/bin/env python3
"""Console des outils de debug (src/debug_tools.c) pour une partie qui tourne : la build DEBUG du PC écoute sur
127.0.0.1:7777 (option --devtools PORT, 0 = sans). Les mêmes commandes que le menu DEBUG > Outils et que le banc
headless (game.dev). Voir docs/DEVTOOLS.md.

usage: dev.py [--port N] COMMANDE [ARGS...]     une commande (aide = la liste)
       dev.py [--port N] capture FICHIER.png    la dernière image du jeu
       dev.py [--port N]                         commandes au clavier, une par ligne
"""

import argparse
import json
import os
import socket
import sys
import tempfile


def connect(port):
    sock = socket.create_connection(("127.0.0.1", port), timeout=10)
    return sock, sock.makefile("r", encoding="utf-8")


def run(sock, reader, line):
    """Envoie une ligne, rend (texte, erreur)."""
    sock.sendall((line + "\n").encode("utf-8"))
    reply = json.loads(reader.readline())
    return reply.get("reply"), reply.get("error")


def capture(sock, reader, path):
    """La dernière image du jeu en PNG (ou PPM sans Pillow)."""
    ppm = os.path.join(tempfile.gettempdir(), "pn3g_capture.ppm")
    _, error = run(sock, reader, "capture " + ppm)
    if error:
        return error
    try:
        from PIL import Image
        Image.open(ppm).save(path)
    except ImportError:
        os.replace(ppm, path)
    return None


def main():
    parser = argparse.ArgumentParser(description="Console des outils de debug d'une partie en cours")
    parser.add_argument("--port", type=int, default=7777)
    parser.add_argument("command", nargs="*")
    args = parser.parse_args()
    try:
        sock, reader = connect(args.port)
    except OSError as e:
        sys.exit(f"pas de partie DEBUG sur 127.0.0.1:{args.port} ({e})")

    lines = [" ".join(args.command)] if args.command else (line.strip() for line in sys.stdin)
    status = 0
    for line in lines:
        if not line:
            continue
        if line.split()[0] == "capture" and len(line.split()) == 2:
            error = capture(sock, reader, line.split()[1])
            text = None if error else f"capture : {line.split()[1]}"
        else:
            text, error = run(sock, reader, line)
        if text:
            print(text if isinstance(text, str) else json.dumps(text))
        if error:
            print("ERREUR :", error, file=sys.stderr)
            status = 1
    sys.exit(status)


if __name__ == "__main__":
    main()
