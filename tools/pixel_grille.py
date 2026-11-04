#!/usr/bin/env python3
"""Dessiner des sprites à la main, pixel par pixel, dans un fichier texte.

Une feuille de sprites (PNG en couleurs indexées, images côte à côte) devient un fichier texte : chaque image est une
grille, un caractère par pixel = l'indice de sa couleur dans la palette (« . » = 0, transparent ; 1-9 ; A-F = 10-15).
On édite la grille, puis on refait le PNG, et on regarde l'aperçu agrandi à côté des images de référence.

Usage (racine du dépôt) :
  python3 tools/pixel_grille.py exporter FEUILLE.png LARGEUR HAUTEUR SORTIE.txt [--images 0-8] [--palette P.png|P.pal]
      --palette : réécrit les indices dans cette palette (couleur la plus proche ; une couleur absente est signalée)
  python3 tools/pixel_grille.py importer GRILLES.txt FEUILLE.png --palette P.png|P.pal
      une image par grille, dans l'ordre de leurs numéros (« ## image N ») ; une image absente reste vide
  python3 tools/pixel_grille.py apercu SORTIE.png [--echelle 6] [--fond R,G,B] [--indices] FICHIER[:a-b]... (PNG ou
      .txt, avec --palette pour les .txt) : une ligne par fichier, images agrandies, quadrillage tous les 8 pixels ;
      --indices écrit l'indice de couleur dans chaque pixel (--echelle 14 ou plus)
"""
import argparse
import os
import re
import sys

from PIL import Image, ImageDraw

CARS = ".123456789ABCDEF"


def lire_palette(chemin):
    """16 couleurs (r, g, b) d'un PNG indexé ou d'un .pal JASC"""
    if chemin.endswith(".pal"):
        mots = open(chemin).read().split()
        n = int(mots[2])
        return [tuple(int(v) for v in mots[3 + 3 * i:6 + 3 * i]) for i in range(n)][:16]
    pal = Image.open(chemin).getpalette()[:48]
    return [tuple(pal[3 * i:3 * i + 3]) for i in range(16)]


def plage(texte, total):
    if not texte:
        return list(range(total))
    if "-" in texte:
        a, b = texte.split("-")
        return list(range(int(a), int(b) + 1))
    return [int(v) for v in texte.split(",")]


def exporter(args):
    feuille = Image.open(args.feuille)
    if feuille.mode != "P":
        sys.exit(f"{args.feuille} : pas en couleurs indexées")
    w, h = args.largeur, args.hauteur
    total = feuille.width // w
    source = lire_palette(args.feuille)
    vers = None
    if args.palette:
        cible = lire_palette(args.palette)
        vers = {}
        for i, c in enumerate(source):
            if i == 0:
                vers[0] = 0
                continue
            j = min(range(1, 16), key=lambda k: sum((a - b) ** 2 for a, b in zip(c, cible[k])))
            vers[i] = j
            if cible[j] != c:
                print(f"couleur {i} {c} -> {j} {cible[j]} (la plus proche)")
    with open(args.sortie, "w") as f:
        f.write(f"# {os.path.basename(args.feuille)} {w}x{h}\n")
        for n in plage(args.images, total):
            f.write(f"## image {n}\n")
            for y in range(h):
                ligne = ""
                for x in range(w):
                    i = feuille.getpixel((n * w + x, y))
                    ligne += CARS[vers[i] if vers else i]
                f.write(ligne + "\n")
    print(f"{args.sortie} : {len(plage(args.images, total))} images {w}x{h}")


def lire_grilles(chemin):
    """{numéro: [lignes]} et (largeur, hauteur)"""
    images, cle, taille = {}, None, None
    for brute in open(chemin):
        ligne = brute.rstrip("\n").rstrip()
        if ligne.startswith("## image"):
            cle = int(ligne.split()[2])
            images[cle] = []
        elif ligne.startswith("#") or cle is None or not ligne:
            continue
        else:
            images[cle].append(ligne)
    for n, lignes in images.items():
        t = (len(lignes[0]), len(lignes))
        if any(len(l) != t[0] for l in lignes):
            sys.exit(f"{chemin} image {n} : lignes de longueurs différentes "
                     f"{sorted(set(len(l) for l in lignes))}")
        if taille and t != taille:
            sys.exit(f"{chemin} image {n} : {t[0]}x{t[1]} au lieu de {taille[0]}x{taille[1]}")
        taille = t
        for y, l in enumerate(lignes):
            for x, c in enumerate(l):
                if c not in CARS:
                    sys.exit(f"{chemin} image {n} ligne {y} colonne {x} : caractère « {c} »")
    return images, taille


def vers_image(lignes, palette):
    im = Image.new("P", (len(lignes[0]), len(lignes)))
    im.putpalette([v for c in palette for v in c] + [0] * (768 - 3 * len(palette)))
    for y, l in enumerate(lignes):
        for x, c in enumerate(l):
            im.putpixel((x, y), CARS.index(c))
    return im


def importer(args):
    images, (w, h) = lire_grilles(args.grilles)
    palette = lire_palette(args.palette)
    total = max(images) + 1
    feuille = Image.new("P", (w * total, h))
    feuille.putpalette([v for c in palette for v in c] + [0] * (768 - 48))
    for n, lignes in images.items():
        feuille.paste(vers_image(lignes, palette), (n * w, 0))
    feuille.save(args.feuille)
    print(f"{args.feuille} : {total} images {w}x{h}")


def cadres_de(spec, args):
    """(images, largeur, hauteur) d'un FICHIER[:a-b] (PNG ou grilles .txt)"""
    # « :a-b » à la fin = les images a à b (pas le « C: » d'un chemin Windows)
    m = re.match(r"^(.*?)(?::([0-9][0-9,\-]*))?$", spec)
    chemin, sel = m.group(1), m.group(2)
    if chemin.endswith(".txt"):
        images, (w, h) = lire_grilles(chemin)
        pal = lire_palette(args.palette)
        nums = plage(sel, max(images) + 1) if sel else sorted(images)
        return [vers_image(images[n], pal) if n in images else None for n in nums], w, h
    feuille = Image.open(chemin)
    w = args.largeur or (16 if feuille.width % 32 else 32)
    h = feuille.height
    return [feuille.crop((n * w, 0, n * w + w, h)) for n in plage(sel, feuille.width // w)], w, h


def apercu(args):
    s = args.echelle
    fond = tuple(int(v) for v in args.fond.split(","))
    lignes = []
    for spec in args.fichiers:
        cadres, w, h = cadres_de(spec, args)
        if args.une_ligne and lignes:
            # tout sur la première ligne ; le nom de chaque fichier au-dessus de sa première image
            lignes[0][1].extend((spec if i == 0 else None, c, w) for i, c in enumerate(cadres))
            lignes[0][2] = max(lignes[0][2], h)
        else:
            lignes.append([spec, [(spec if args.une_ligne else None, c, w) for c in cadres], h])
    largeur = max(sum(w * s + 6 for _, _, w in cellules) for _, cellules, _ in lignes)
    hauteur = sum(h * s + 14 for _, _, h in lignes)
    out = Image.new("RGB", (largeur, hauteur), (30, 30, 30))
    d = ImageDraw.Draw(out)
    y = 0
    for spec, cellules, h in lignes:
        if not args.une_ligne:
            d.text((2, y), spec, fill=(255, 255, 0))
        x0 = 0
        for nom, c, w in cellules:
            if nom:
                d.text((x0 + 2, y), os.path.basename(nom)[:w * s // 6], fill=(255, 255, 0))
            if c is None:
                x0 += w * s + 6
                continue
            rgb = Image.new("RGB", c.size, fond)
            if c.mode != "P":
                # PNG en couleurs directes (sprites d'autres sources) : la couleur du coin = le fond
                src = c.convert("RGB")
                bg = src.getpixel((0, 0))
                for yy in range(c.height):
                    for xx in range(c.width):
                        if src.getpixel((xx, yy)) != bg:
                            rgb.putpixel((xx, yy), src.getpixel((xx, yy)))
                c = None
            else:
                pal = c.getpalette()
                for yy in range(c.height):
                    for xx in range(c.width):
                        k = c.getpixel((xx, yy))
                        if k:
                            rgb.putpixel((xx, yy), tuple(pal[3 * k:3 * k + 3]))
            ch = rgb.height
            out.paste(rgb.resize((w * s, ch * s), Image.NEAREST), (x0, y + 12))
            if args.indices and c is not None:
                # l'indice de chaque pixel écrit dedans, en noir ou blanc selon la couleur
                for yy in range(c.height):
                    for xx in range(c.width):
                        k = c.getpixel((xx, yy))
                        if k:
                            r, g, b = tuple(pal[3 * k:3 * k + 3])
                            encre = (0, 0, 0) if r + g + b > 380 else (255, 255, 255)
                            d.text((x0 + xx * s + s // 2 - 3, y + 12 + yy * s + s // 2 - 5), CARS[k], fill=encre)
            if not args.sans_grille:
                for gx in range(0, w + 1, 8):
                    d.line([(x0 + gx * s, y + 12), (x0 + gx * s, y + 12 + ch * s)],
                           fill=(0, 0, 0) if gx % 16 else (80, 0, 0))
                for gy in range(0, ch + 1, 8):
                    d.line([(x0, y + 12 + gy * s), (x0 + w * s, y + 12 + gy * s)],
                           fill=(0, 0, 0) if gy % 16 else (80, 0, 0))
            x0 += w * s + 6
        y += h * s + 14
    out.save(args.sortie)
    print(f"{args.sortie} {out.size}")


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sous = p.add_subparsers(dest="action", required=True)
    e = sous.add_parser("exporter")
    e.add_argument("feuille"); e.add_argument("largeur", type=int); e.add_argument("hauteur", type=int)
    e.add_argument("sortie"); e.add_argument("--images"); e.add_argument("--palette")
    i = sous.add_parser("importer")
    i.add_argument("grilles"); i.add_argument("feuille"); i.add_argument("--palette", required=True)
    a = sous.add_parser("apercu")
    a.add_argument("sortie"); a.add_argument("fichiers", nargs="+"); a.add_argument("--echelle", type=int, default=6)
    a.add_argument("--fond", default="90,90,110"); a.add_argument("--palette"); a.add_argument("--largeur", type=int)
    a.add_argument("--indices", action="store_true", help="écrit l'indice de couleur dans chaque pixel")
    a.add_argument("--une-ligne", action="store_true", help="toutes les images sur une seule ligne")
    a.add_argument("--sans-grille", action="store_true", help="sans quadrillage (pour juger à petite échelle)")
    args = p.parse_args()
    {"exporter": exporter, "importer": importer, "apercu": apercu}[args.action](args)


if __name__ == "__main__":
    main()
