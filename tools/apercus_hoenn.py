#!/usr/bin/env python3
"""Aperçus d'entrée dessinés pour les lieux uniques de Hoenn (v1.1, 2026-11-05).

Rouge Feu montre une illustration à l'entrée de ses donjons (kanto_map_preview_screen.c). Les lieux de Hoenn qui
ressemblent à un lieu de Kanto en reprennent l'image ; les lieux uniques (Pilier Céleste, Tour Mirage...) ont ici une
illustration dessinée dans le style de RF : vue en perspective, couleurs douces, 15 couleurs.

Le style de RF, relevé sur ses aperçus : de grands aplats de couleurs claires, un tramage en damier seulement à la
limite de deux teintes (horizon, ombres), des reflets en traits horizontaux sur l'eau, des rochers en facettes nettes
éclairées par le haut à gauche, des contours un ton plus sombre. Chaque scène est dessinée en code (fonctions scene_*)
avec les outils de dessin ci-dessous.

Format des aperçus de RF (graphics/kanto/map_preview/*) :
- image de 240 x 112 au milieu de l'écran (rangées de tuiles 3 à 16), en 15 couleurs (palette BG 13) ;
- bandeaux noirs et fond du nom du lieu (rangées 0-2 et 17-19, palette BG 14) repris tels quels de l'aperçu de la
  Tour Pokémon de RF (mêmes tuiles et même palette 14 pour tous les aperçus de RF : couleurs du texte du nom) ;
- tiles.png (pixels 0-31, palette de 32 couleurs) et tilemap.bin (32 x 20).

Usage :
    python tools/apercus_hoenn.py                    # écrit graphics/fusion/map_preview/<lieu>/ et la planche
    python tools/apercus_hoenn.py --planche P.png    # planche de relecture seulement (rien n'est écrit dans graphics/)
    python tools/apercus_hoenn.py --planche P.png sky_pillar mirage_tower
"""
import argparse
import math
import os
import random
import struct
import sys

from PIL import Image, ImageDraw, ImageFont

RACINE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CADRE = os.path.join(RACINE, 'graphics', 'kanto', 'map_preview', 'pokemon_tower')
SORTIE = os.path.join(RACINE, 'graphics', 'fusion', 'map_preview')
W, H = 240, 112                 # l'image (rangées de tuiles 3 à 16 de l'écran)
IMAGE_Y = 3


# --- Toile : une image en couleurs nommées (au plus 15) ----------------------------------------------------------

class Toile:
    def __init__(self, couleurs):
        if len(couleurs) > 15:
            raise SystemExit('%d couleurs : 15 au plus (palette 13 de RF)' % len(couleurs))
        self.noms = list(couleurs)
        self.rgb = [couleurs[n] for n in self.noms]
        self.idx = {n: i for i, n in enumerate(self.noms)}
        self.im = Image.new('P', (W, H), 0)
        self.im.putpalette([v for c in self.rgb for v in c])
        self.px = self.im.load()
        self.dessin = ImageDraw.Draw(self.im)

    def nom(self, x, y):
        return self.noms[self.px[x, y]]

    def point(self, x, y, nom):
        if 0 <= x < W and 0 <= y < H:
            self.px[x, y] = self.idx[nom]

    def rect(self, x0, y0, x1, y1, nom):
        self.dessin.rectangle((x0, y0, x1, y1), fill=self.idx[nom])

    def poly(self, pts, nom):
        self.dessin.polygon(pts, fill=self.idx[nom])

    def ligne(self, pts, nom, largeur=1):
        self.dessin.line(pts, fill=self.idx[nom], width=largeur)

    def ellipse(self, box, nom):
        self.dessin.ellipse(box, fill=self.idx[nom])


def aplat(t, x, y, rampe, l, trame=0.12):
    """La couleur de la rampe (du sombre au clair, ou du haut vers le bas) pour la valeur l (0-1), en aplats :
    un damier seulement près de la limite entre deux teintes, comme RF."""
    n = len(rampe) - 1
    if n <= 0:
        t.point(x, y, rampe[0])
        return
    v = min(max(l, 0.0), 0.9999) * n
    k = int(v)
    f = v - k
    if f >= 0.5 + trame or (f > 0.5 - trame and (x + y) & 1):
        k += 1
    t.point(x, y, rampe[min(k, n)])


def bandes_v(t, x0, y0, x1, y1, rampe, rangs=2, masque=None):
    """Bandes horizontales de la rampe (de haut en bas), séparées par `rangs` rangées en damier."""
    n = max(1, len(rampe) - 1)
    hb = max(1.0, (y1 - y0) / (n + 1))
    trame = rangs / (2 * hb) / 1.0
    for y in range(max(y0, 0), min(y1, H)):
        l = (y - y0) / max(1, y1 - y0 - 1)
        for x in range(max(x0, 0), min(x1, W)):
            if masque is not None and not masque.getpixel((x, y)):
                continue
            aplat(t, x, y, rampe, l, trame)


def masque():
    return Image.new('L', (W, H), 0)


def masque_poly(pts):
    m = masque()
    ImageDraw.Draw(m).polygon(pts, fill=255)
    return m


def pixels(m):
    d = m.load()
    return [(x, y) for y in range(H) for x in range(W) if d[x, y]]


def dedans(m, x, y):
    return 0 <= x < W and 0 <= y < H and m.getpixel((x, y))


def contour(t, m, sombre, clair=None):
    """Contour d'un masque : un ton sombre en bas et à droite, clair en haut et à gauche (lumière en haut à gauche)."""
    for x, y in pixels(m):
        if not dedans(m, x, y + 1) or not dedans(m, x + 1, y):
            t.point(x, y, sombre)
        elif clair and (not dedans(m, x, y - 1) or not dedans(m, x - 1, y)):
            t.point(x, y, clair)


# --- Éléments de décor ------------------------------------------------------------------------------------------

def nuage(t, cx, cy, largeur, hauteur, graine, blanc='blanc', ombre='nuage_ombre'):
    """Cumulus : des bosses rondes sur une base presque plate, blanc, avec une ombre douce dans le bas."""
    rnd = random.Random(graine)
    m = masque()
    d = ImageDraw.Draw(m)
    n = max(3, largeur // 12)
    for k in range(n):
        u = (k + 0.5) / n
        r = hauteur * (0.35 + 0.65 * math.sin(math.pi * u)) * rnd.uniform(0.75, 1.0)
        x = cx - largeur / 2 + u * largeur
        d.ellipse((x - r * 1.3, cy - r, x + r * 1.3, cy + r * 0.5), fill=255)
    d.rectangle((cx - largeur / 2 + 3, cy - 3, cx + largeur / 2 - 3, cy + 1), fill=255)
    haut = {}
    for x, y in pixels(m):
        haut[x] = min(haut.get(x, y), y)
    for x, y in pixels(m):
        l = (y - haut[x]) / max(1, cy + 1 - haut[x])
        aplat(t, x, y, [blanc, ombre], 0.25 + l * 0.75, 0.08)


def mer(t, y0, y1, loin, eau, clair, blanc, graine, fonce=None):
    """La mer de RF : une bande claire à l'horizon, puis un aplat, avec des reflets en traits horizontaux, plus longs
    et plus nombreux au premier plan."""
    rnd = random.Random(graine)
    for y in range(y0, y1):
        for x in range(W):
            if y < y0 + 3:
                t.point(x, y, loin)
            elif y < y0 + 5:
                t.point(x, y, loin if (x + y) & 1 else eau)
            elif fonce and y > y1 - (y1 - y0) // 3 and (x + y) & 1 and y > y1 - (y1 - y0) // 3 + 2:
                t.point(x, y, fonce)
            else:
                t.point(x, y, eau)
    for y in range(y0 + 5, y1, 2):
        p = (y - y0) / max(1, y1 - y0)
        for _ in range(int(2 + 5 * p)):
            longueur = int(3 + p * 14 * rnd.random())
            x = rnd.randrange(-8, W)
            t.ligne([(x, y), (x + longueur, y)], clair)
            if rnd.random() < 0.25:
                t.ligne([(x + 1, y), (x + max(1, longueur // 3), y)], blanc)


def rocher(t, cx, cy, rx, ry, rampe, graine, sombre=None, plat_bas=True):
    """Rocher à la manière de RF : un gros bloc arrondi et deux ou trois plus petits accolés, chacun éclairé en haut à
    gauche, posés à plat (base coupée) quand ils sont au sol. Renvoie leur masque."""
    from PIL import ImageChops
    rnd = random.Random(graine)
    pierres = [(cx, cy, rx, ry)]
    for _ in range(rnd.randint(1, 3)):
        a = rnd.uniform(0, 2 * math.pi)
        pierres.append((cx + math.cos(a) * rx * 0.6, cy + math.sin(a) * ry * 0.35 + ry * 0.15,
                        rx * rnd.uniform(0.4, 0.65), ry * rnd.uniform(0.5, 0.8)))
    pierres.sort(key=lambda p: p[1] + p[3])   # du fond vers l'avant
    clip = None
    if plat_bas:
        clip = masque()
        ImageDraw.Draw(clip).rectangle((0, 0, W, cy + ry * 0.45), fill=255)
    tout = masque()
    for x, y, a, b in pierres:
        tout = ImageChops.lighter(tout, pierre_ronde(t, x, y, a, b, rampe, clip, sombre or rampe[0]))
    return tout


def herbe(t, x0, x1, y_base, hauteur, rampe, graine, densite=0.8):
    """Touffes d'herbe : des brins fins et courbes, foncés à la base et clairs au bout."""
    rnd = random.Random(graine)
    for _ in range(int((x1 - x0) * densite)):
        x = rnd.uniform(x0, x1)
        h = hauteur * rnd.uniform(0.4, 1.0)
        pente = rnd.uniform(-0.6, 0.6)
        yb = y_base + rnd.uniform(-2, 2)
        for k in range(int(h)):
            u = k / max(1, h)
            t.point(int(x + pente * k * k / max(1, h)), int(yb - k), rampe[min(len(rampe) - 1, int(u * len(rampe)))])


def buisson(t, cx, cy, r, rampe, graine):
    """Buisson ou feuillage arrondi : des boules qui se chevauchent, sombres dessous, claires en haut à gauche."""
    rnd = random.Random(graine)
    boules = [(cx + rnd.uniform(-r, r), cy + rnd.uniform(-r * 0.4, r * 0.3), r * rnd.uniform(0.45, 0.7))
              for _ in range(6)]
    for bx, by, br in boules:
        t.ellipse((bx - br, by - br, bx + br, by + br), rampe[0])
    for bx, by, br in boules:
        t.ellipse((bx - br * 0.85, by - br, bx + br * 0.7, by + br * 0.55), rampe[1])
    for bx, by, br in boules:
        t.ellipse((bx - br * 0.6, by - br * 0.9, bx + br * 0.2, by - br * 0.2), rampe[2])


def sapin(t, cx, base, hauteur, rampe):
    """Sapin : des étages triangulaires, côté gauche éclairé."""
    etages = 4
    for k in range(etages):
        y1 = base - k * hauteur * 0.22
        y0 = y1 - hauteur * 0.38
        demi = hauteur * 0.32 * (1 - k * 0.2)
        t.poly([(cx, y0), (cx - demi, y1), (cx + demi, y1)], rampe[0])
        t.poly([(cx, y0), (cx - demi, y1), (cx - demi * 0.1, y1)], rampe[1])
        t.poly([(cx, y0 + 2), (cx - demi * 0.5, y0 + (y1 - y0) * 0.6), (cx - 1, y0 + (y1 - y0) * 0.6)], rampe[2])


def organique(pts, amplitude, graine, pas=6):
    """Rend un contour moins droit, à la main comme les décors de RF : chaque côté est redécoupé tous les `pas`
    pixels et ses points sont un peu déplacés, en douceur (bruit lissé)."""
    rnd = random.Random(graine)
    res = []
    for (ax, ay), (bx, by) in zip(pts, pts[1:] + pts[:1]):
        n = max(1, int(math.hypot(bx - ax, by - ay) / pas))
        nx, ny = by - ay, ax - bx
        ln = math.hypot(nx, ny) or 1
        phase = rnd.uniform(0, 6.3)
        for k in range(n):
            u = k / n
            d = amplitude * (0.6 * math.sin(phase + u * 5.0) + 0.4 * rnd.uniform(-1, 1))
            if k == 0:
                d = 0  # les coins restent en place
            res.append((ax + (bx - ax) * u + nx / ln * d, ay + (by - ay) * u + ny / ln * d))
    return res


def pierre_ronde(t, cx, cy, rx, ry, rampe, masque_clip=None, sombre=None):
    """Une pierre arrondie : aplats de la rampe éclairés en haut à gauche, bord sombre en bas et à droite."""
    m = masque()
    ImageDraw.Draw(m).ellipse((cx - rx, cy - ry, cx + rx, cy + ry), fill=255)
    if masque_clip is not None:
        from PIL import ImageChops
        m = ImageChops.multiply(m, masque_clip)
    for x, y in pixels(m):
        u, v = (x - cx) / max(1, rx), (y - cy) / max(1, ry)
        l = 0.62 - 0.42 * (u * 0.55 + v * 0.85)
        aplat(t, x, y, rampe, l, 0.08)
    for x, y in pixels(m):
        if not dedans(m, x, y + 1) or not dedans(m, x + 1, y):
            t.point(x, y, sombre or rampe[0])
    return m


def roche_cannelee(t, pts, rampe, dessus, graine, rx=(3, 5), ry=(7, 11), clair_dessus=None):
    """Un massif de roche (falaise, butte) au contour irrégulier, fait de cannelures verticales arrondies qui se
    chevauchent, avec son dessus plat éclairé. Renvoie son masque."""
    rnd = random.Random(graine)
    contour_ = organique(pts, 1.6, graine)
    m = masque_poly(contour_)
    ys = [p[1] for p in contour_]
    xs = [p[0] for p in contour_]
    y = int(min(ys)) + 2
    while y < max(ys) + ry[1]:
        x = int(min(xs)) - rx[1] + rnd.randint(0, 3)
        while x < max(xs) + rx[1]:
            a, b = rnd.randint(*rx), rnd.randint(*ry)
            pierre_ronde(t, x, y + rnd.randint(-2, 2), a, b, rampe, m, rampe[0])
            x += int(a * 1.6) + rnd.randint(0, 2)
        y += ry[0] + 2
    # Le dessus : une bande claire qui suit le haut du contour
    haut = {}
    for x, y in pixels(m):
        haut[x] = min(haut.get(x, y), y)
    for x, y0 in haut.items():
        for k in range(3):
            t.point(x, y0 + k, (clair_dessus or dessus) if k == 0 else dessus)
    return m


def bouche(t, cx, sol, largeur, hauteur, porte, bord):
    """L'entrée sombre d'une grotte, en arc, posée sur le sol (son bas sur la ligne `sol`)."""
    t.rect(cx - largeur // 2, sol - hauteur + largeur // 2, cx + largeur // 2, sol - 1, porte)
    t.ellipse((cx - largeur // 2, sol - hauteur, cx + largeur // 2, sol - hauteur + largeur), porte)
    m = masque()
    d = ImageDraw.Draw(m)
    d.rectangle((cx - largeur // 2, sol - hauteur + largeur // 2, cx + largeur // 2, sol - 1), fill=255)
    d.ellipse((cx - largeur // 2, sol - hauteur, cx + largeur // 2, sol - hauteur + largeur), fill=255)
    for x, y in pixels(m):  # bord éclairé à gauche et en haut
        if (not dedans(m, x - 1, y) or not dedans(m, x, y - 1)) and x < cx + largeur // 3:
            t.point(x - 1, y, bord)


def butte_regi(t, cx, base, rampe, dessus, porte, graine):
    """L'entrée d'une salle des Regi, comme dans Rubis Oméga / Saphir Alpha : une butte de roche rouge en deux gradins
    cannelés, et la bouche sombre de la grotte, en arc, posée au sol. Les trois salles ont la même ; seul le décor
    change."""
    roche_cannelee(t, [(cx - 52, base - 22), (cx - 40, base - 47), (cx + 40, base - 47), (cx + 52, base - 22)], rampe,
                   dessus, graine)
    roche_cannelee(t, [(cx - 78, base), (cx - 62, base - 27), (cx + 62, base - 27), (cx + 78, base)], rampe, dessus,
                   graine + 1)
    bouche(t, cx, base, 20, 24, porte, rampe[-1])


# --- Scènes -----------------------------------------------------------------------------------------------------

def falaise(t, x0, x1, y_haut, y_bas, rampe, graine, dessus=None, pente=0.0):
    """Falaise rocheuse en strates (comme les rochers rouges de Hoenn dans Rubis Oméga / Saphir Alpha) : un dessus
    plat éclairé, une face striée de cannelures verticales, plus sombre en bas. `rampe` : du sombre au clair.
    `pente` : les côtés rentrent de tant de pixels par rangée en montant (une butte)."""
    rnd = random.Random(graine)
    stries = {}
    x = x0
    while x <= x1:
        largeur = rnd.randint(3, 8)
        valeur = rnd.choice([0.5, 0.6, 0.6, 0.7, 0.8])
        for k in range(largeur):
            # une crevasse sombre de temps en temps, sinon des cannelures à peine marquées
            stries[x + k] = 0.2 if k == largeur - 1 and rnd.random() < 0.45 else valeur
        x += largeur
    for y in range(max(0, y_haut), min(H, y_bas)):
        retrait = pente * (y_bas - 1 - y)
        g, d = int(x0 + retrait), int(x1 - retrait)
        for xx in range(max(0, g), min(W, d + 1)):
            if y < y_haut + 3:
                nom = dessus or rampe[-1]
            elif xx in (g, d):
                nom = rampe[0]
            else:
                l = stries.get(xx, 0.5) - 0.25 * (y - y_haut) / max(1, y_bas - y_haut)
                if (y - y_haut) % 7 == 6:
                    l -= 0.2  # strates horizontales
                if pente and xx < g + 3:
                    l += 0.25  # arête de gauche, au soleil
                aplat(t, xx, y, rampe, l, 0.1)
                continue
            t.point(xx, y, nom)
    for xx in range(max(0, x0), min(W, x1 + 1)):
        if y_bas - 1 < H and t.nom(xx, y_bas - 1) in rampe:
            t.point(xx, y_bas - 1, rampe[0])


def scene_sky_pillar():
    """Pilier Céleste : la tour de pierre au milieu de son île de sable et de falaises rouges, comme dans Rubis Oméga /
    Saphir Alpha, la mer à l'horizon."""
    t = Toile({
        'ciel_haut': (152, 196, 240), 'ciel': (200, 224, 248), 'blanc': (248, 248, 248),
        'mer': (96, 152, 216), 'mer_clair': (160, 200, 240),
        'pierre_claire': (236, 216, 172), 'pierre': (204, 176, 132), 'pierre_ombre': (156, 128, 96),
        'pierre_noire': (100, 80, 66), 'porte': (40, 34, 38),
        'sable_clair': (246, 228, 176), 'sable': (226, 198, 140),
        'falaise_claire': (224, 150, 116), 'falaise': (188, 108, 84), 'falaise_ombre': (130, 74, 64),
    })
    bandes_v(t, 0, 0, W, 62, ['ciel_haut', 'ciel', 'blanc'], rangs=2)
    nuage(t, 30, 26, 56, 10, 3, ombre='ciel')
    nuage(t, 214, 18, 56, 10, 5, ombre='ciel')
    mer(t, 58, H, 'blanc', 'mer', 'mer_clair', 'blanc', 2)
    # L'île : un plateau de sable aux bords irréguliers, la mer tout autour, l'écume sur ses bords
    ile = organique([(10, 112), (230, 112), (210, 70), (30, 70)], 3, 6, pas=8)
    t.poly([(x + (-3 if x < 120 else 3), y - 2) for x, y in ile], 'blanc')
    m = masque_poly(ile)
    bandes_v(t, 0, 66, W, H, ['sable_clair', 'sable'], rangs=2, masque=m)
    # Falaises rouges sur l'île, de part et d'autre de la tour
    rampe_f = ['pierre_noire', 'falaise_ombre', 'falaise', 'falaise_claire']
    roche_cannelee(t, [(30, 82), (38, 62), (70, 60), (78, 82)], rampe_f, 'pierre', 1, clair_dessus='pierre_claire')
    roche_cannelee(t, [(162, 82), (170, 58), (204, 60), (214, 82)], rampe_f, 'pierre', 3, clair_dessus='pierre_claire')
    bouche(t, 194, 82, 12, 15, 'porte', 'pierre')  # la grotte vers l'entrée du Pilier
    roche_cannelee(t, [(16, 102), (24, 86), (50, 86), (58, 102)], rampe_f, 'pierre', 2, clair_dessus='pierre_claire')
    roche_cannelee(t, [(186, 104), (194, 88), (218, 88), (226, 104)], rampe_f, 'pierre', 4, clair_dessus='pierre_claire')
    # La tour : d'énormes blocs de pierre, la face avant éclairée, le flanc droit dans l'ombre ; elle sort de l'image
    x0, x1, flanc, base = 70, 160, 172, 84
    rnd = random.Random(8)
    for y_assise in range(-6, base, 12):
        x = x0 - rnd.randint(0, 12)
        while x < x1:
            largeur = rnd.randint(14, 28)
            g, d = max(x, x0), min(x + largeur, x1)
            sombre = rnd.random() < 0.25
            for yy in range(max(0, y_assise), min(base, y_assise + 12)):
                for xx in range(g, d):
                    if yy == y_assise or xx == g:
                        nom = 'pierre_ombre'
                    elif yy == y_assise + 1:
                        nom = 'pierre_claire'
                    elif sombre and (xx + yy) & 1:
                        nom = 'pierre_ombre'
                    else:
                        nom = 'pierre'
                    t.point(xx, yy, nom)
            x += largeur
    for y in range(0, base):  # flanc droit, dans l'ombre
        for xx in range(x1, flanc + 1):
            nom = 'pierre_noire' if (y % 12 == 0 or xx == flanc) else 'pierre_ombre'
            t.point(xx, y, nom)
    t.ligne([(x0, 0), (x0, base)], 'pierre_noire')
    # Des assises qui dépassent un peu des murs : un contour de vieille pierre, pas une règle
    for y_assise in range(0, base - 6, 12):
        for cote, signe in ((x0, -1), (flanc, 1)):
            saillie = rnd.choice([0, 1, 2, 2, 3])
            if saillie:
                for yy in range(y_assise + 1, min(base, y_assise + 12)):
                    for k in range(1, saillie + 1):
                        nom = 'pierre_claire' if yy == y_assise + 1 else ('pierre' if signe < 0 else 'pierre_ombre')
                        t.point(cote + signe * k, yy, nom)
                    t.point(cote + signe * (saillie + 1), yy, 'pierre_noire')
                t.ligne([(cote + signe, y_assise + 11), (cote + signe * (saillie + 1), y_assise + 11)], 'pierre_noire')
    for gx, gy, gl, gh in [(84, 8, 12, 8), (140, 20, 10, 9), (96, 44, 8, 6)]:  # blocs manquants
        t.rect(gx, gy, gx + gl, gy + gh, 'pierre_noire')
        t.rect(gx + 1, gy + 2, gx + gl, gy + gh, 'porte')
    # La porte : un passage rectangulaire dans un cadre de grosses dalles
    t.rect(100, 52, 130, base, 'pierre_claire')
    t.rect(101, 53, 129, 57, 'pierre')
    t.rect(105, 58, 125, base, 'porte')
    t.rect(100, 58, 104, base, 'pierre')
    t.rect(126, 58, 130, base, 'pierre_ombre')
    t.ligne([(100, 57), (130, 57)], 'pierre_noire')
    # Le pied de la tour, irrégulier : des blocs tombés et du sable qui remonte contre les murs
    for k, (x, y, rx, ry) in enumerate([(74, 84, 6, 4), (92, 85, 5, 3), (140, 85, 6, 3), (164, 84, 7, 4)]):
        pierre_ronde(t, x, y, rx, ry, ['pierre_noire', 'pierre_ombre', 'pierre', 'pierre_claire'])
    for xx in range(x0 - 4, flanc + 6):
        if not 104 < xx < 126:  # pas devant la porte, qui reste posée sur le sol
            for yy in range(base - 2 - int(1.5 + 1.5 * math.sin(xx / 5)), base):
                t.point(xx, yy, 'sable_clair' if yy < base - 1 else 'sable')
    for xx in range(x0, flanc + 4):  # ombre de la tour sur le sable
        for yy in range(base, base + 4):
            if (xx + yy) & 1 and t.nom(xx, yy).startswith('sable'):
                t.point(xx, yy, 'pierre_ombre')
    # Rochers rouges éparpillés sur le sable
    for k, (x, y, rx, ry) in enumerate([(40, 104, 10, 7), (84, 100, 7, 5), (150, 104, 9, 6), (182, 100, 7, 5),
                                        (210, 108, 12, 7), (12, 108, 8, 5), (120, 110, 8, 4)]):
        rocher(t, x, y, rx, ry, ['falaise_ombre', 'falaise', 'pierre'], 40 + k, 'pierre_noire')
    return t


def scene_mirage_tower():
    """Tour Mirage : la tour de sable du désert de la Route 111, à demi voilée par la tempête de sable."""
    t = Toile({
        'ciel_haut': (208, 204, 216), 'ciel': (232, 224, 208), 'voile': (244, 236, 212), 'loin': (216, 196, 160),
        'sable_clair': (248, 232, 176), 'sable': (232, 208, 144), 'sable_ombre': (208, 176, 112),
        'sable_fonce': (168, 136, 88),
        'tour_claire': (248, 224, 168), 'tour': (224, 192, 128), 'tour_ombre': (184, 144, 96),
        'tour_noire': (128, 96, 72), 'porte': (80, 60, 52), 'cactus': (136, 168, 96), 'cactus_ombre': (96, 128, 80),
    })
    bandes_v(t, 0, 0, W, 66, ['ciel_haut', 'ciel', 'voile'], rangs=3)
    # Mesas lointaines noyées dans le sable qui vole
    for pts in ([(0, 64), (6, 54), (40, 52), (52, 58), (60, 64)], [(150, 64), (162, 50), (204, 49), (214, 56), (240, 58),
                                                                  (240, 64)]):
        t.poly(pts, 'loin')
    # Le sol et les dunes, plus foncées en approchant
    bandes_v(t, 0, 62, W, H, ['sable_clair', 'sable', 'sable_ombre'], rangs=2)
    for pts, rampe in [([(0, 100), (40, 84), (90, 90), (130, 112), (0, 112)], ['sable_clair', 'sable_ombre']),
                       ([(150, 112), (192, 86), (240, 80), (240, 112)], ['sable_clair', 'sable', 'sable_fonce'])]:
        m = masque_poly(pts)
        ys = [p[1] for p in pts]
        bandes_v(t, 0, min(ys), W, H, rampe, masque=m)
    # La tour : un fût de grosses pierres de sable, crénelé, plus étroit en haut
    cx, base, sommet = 110, 92, 6
    for y in range(sommet, base):
        u = (base - y) / (base - sommet)
        demi = 21 - 6 * u
        assise = (y - sommet) % 10
        for x in range(int(cx - demi), int(cx + demi) + 1):
            v = (x - (cx - demi)) / (2 * demi)
            l = 0.95 - 0.95 * max(0.0, v) ** 1.3  # cylindre éclairé à gauche
            if assise == 0:
                l -= 0.3
            aplat(t, x, y, ['tour_noire', 'tour_ombre', 'tour', 'tour_claire'], l, 0.06)
            if assise > 0 and (int(x - cx + demi) + (y - sommet) // 10 * 4) % 8 == 0 and v > 0.05:
                t.point(x, y, 'tour_ombre' if v < 0.7 else 'tour_noire')
        t.point(int(cx - demi) - 1, y, 'tour_noire')
        t.point(int(cx + demi) + 1, y, 'tour_noire')
    for k in range(5):  # créneaux
        x = cx - 14 + k * 6
        t.rect(x, sommet - 5, x + 3, sommet, 'tour' if k < 3 else 'tour_ombre')
        t.point(x, sommet - 5, 'tour_claire')
    for wy in (28, 52):  # fenêtres
        t.rect(cx - 3, wy, cx + 2, wy + 7, 'porte')
        t.point(cx - 3, wy, 'tour_noire')
    t.rect(cx - 7, base - 15, cx + 6, base, 'tour_noire')
    t.rect(cx - 5, base - 13, cx + 4, base, 'porte')
    # Ombre de la tour sur le sable, cactus
    for x in range(cx + 14, cx + 80):
        for yy in range(base - 1, base + 3):
            if (x + yy) & 1 and t.nom(x, yy).startswith('sable'):
                t.point(x, yy, 'sable_ombre')
    for x, y0, h in [(36, 100, 16), (200, 94, 12)]:
        t.rect(x, y0 - h, x + 3, y0, 'cactus')
        t.rect(x + 3, y0 - h, x + 3, y0, 'cactus_ombre')
        t.rect(x - 5, y0 - h + 6, x - 1, y0 - h + 8, 'cactus')
        t.rect(x - 5, y0 - h + 2, x - 4, y0 - h + 8, 'cactus')
        t.rect(x + 4, y0 - h + 8, x + 7, y0 - h + 10, 'cactus')
        t.rect(x + 6, y0 - h + 4, x + 7, y0 - h + 10, 'cactus_ombre')
    # Traînées de sable qui volent
    rnd = random.Random(7)
    for _ in range(40):
        x, y = rnd.randrange(-20, W), rnd.randrange(0, 90)
        longueur = rnd.randint(6, 26)
        for k in range(longueur):
            if (k + y) % 3:
                t.point(x + k, y + k // 6, 'voile')
    return t


def scene_abandoned_ship():
    """Épave : le grand paquebot échoué de la Route 108, penché, la coque rouillée, dans des eaux peu profondes."""
    t = Toile({
        'ciel_haut': (168, 200, 240), 'ciel': (200, 224, 248), 'blanc': (248, 248, 248), 'nuage_ombre': (216, 220, 240),
        'mer': (112, 168, 224), 'mer_clair': (168, 208, 240),
        'coque_claire': (240, 240, 232), 'coque': (200, 204, 200), 'coque_ombre': (144, 148, 152),
        'rouille': (192, 120, 88), 'rouille_fonce': (136, 80, 64), 'noir': (64, 68, 88),
        'roc': (176, 160, 136), 'roc_ombre': (120, 112, 100), 'roc_clair': (216, 204, 176),
    })
    bandes_v(t, 0, 0, W, 58, ['ciel_haut', 'ciel', 'blanc'], rangs=2)
    nuage(t, 60, 24, 70, 12, 21)
    nuage(t, 196, 14, 50, 9, 22)
    mer(t, 58, H, 'blanc', 'mer', 'mer_clair', 'blanc', 23)

    # Le paquebot, penché : proue à gauche relevée. Coordonnées dans le repère du bateau, puis tournées.
    angle = math.radians(-7)
    ox, oy = 120, 74

    def r(x, y):
        return (ox + x * math.cos(angle) - y * math.sin(angle), oy + x * math.sin(angle) + y * math.cos(angle))

    def p(pts):
        return [r(x, y) for x, y in pts]
    t.poly(p([(-96, -14), (88, -14), (92, -6), (84, 16), (-80, 16), (-100, -8)]), 'coque_ombre')
    t.poly(p([(-96, -14), (88, -14), (90, -9), (-98, -9)]), 'coque_claire')
    t.poly(p([(-98, -9), (90, -9), (88, 0), (-94, 0)]), 'coque')
    t.poly(p([(-94, 0), (88, 0), (84, 16), (-80, 16)]), 'rouille')
    t.poly(p([(-60, 6), (84, 6), (84, 16), (-80, 16)]), 'rouille_fonce')
    for k in range(14):  # hublots
        x = -84 + k * 12
        cx_, cy_ = r(x, -5)
        t.ellipse((cx_ - 1.5, cy_ - 1.5, cx_ + 1.5, cy_ + 1.5), 'noir')
    for k in range(9):  # coulures de rouille
        x = -70 + k * 17
        t.ligne([r(x, 0), r(x + 1, 6), r(x, 11)], 'rouille_fonce')
    # Superstructure : deux ponts de cabines, la cheminée, le mât cassé
    t.poly(p([(-60, -14), (50, -14), (46, -26), (-56, -26)]), 'coque')
    t.poly(p([(-56, -26), (46, -26), (45, -28), (-55, -28)]), 'coque_claire')
    for k in range(10):
        x = -50 + k * 10
        t.poly(p([(x, -23), (x + 6, -23), (x + 6, -18), (x, -18)]), 'noir')
    t.poly(p([(-40, -28), (24, -28), (20, -38), (-36, -38)]), 'coque_claire')
    t.poly(p([(4, -28), (24, -28), (20, -38), (4, -38)]), 'coque')
    for k in range(5):
        x = -30 + k * 10
        t.poly(p([(x, -35), (x + 5, -35), (x + 5, -31), (x, -31)]), 'noir')
    t.poly(p([(30, -28), (44, -28), (46, -50), (34, -50)]), 'rouille')
    t.poly(p([(40, -28), (44, -28), (46, -50), (42, -50)]), 'rouille_fonce')
    t.poly(p([(34, -50), (46, -50), (45, -53), (35, -53)]), 'noir')
    t.ligne([r(-74, -14), r(-78, -44), r(-70, -52)], 'coque_ombre', 2)  # mât, plié
    t.ligne([r(-74, -14), r(-78, -44)], 'noir')
    # Ligne de flottaison : la mer recouvre le bas de la coque, avec de l'écume
    for x in range(W):
        for y in range(84, H):
            if t.nom(x, y) in ('rouille', 'rouille_fonce', 'coque_ombre') and y > 86 + (x - 20) * 0.12:
                t.point(x, y, 'mer' if (x + y) % 5 else 'mer_clair')
    rnd = random.Random(5)
    for _ in range(60):
        x = rnd.randrange(16, 214)
        y = int(86 + (x - 20) * 0.12) + rnd.randint(-1, 2)
        t.ligne([(x, y), (x + rnd.randint(2, 7), y)], 'blanc')
    # Rochers au premier plan
    rampe = ['roc_ombre', 'roc', 'roc_clair']
    for k, (x, y, rx, ry) in enumerate([(14, 104, 26, 12), (226, 102, 28, 14), (190, 110, 18, 6)]):
        m = rocher(t, x, y, rx, ry, rampe, 60 + k, 'noir')
        for xx, yy in pixels(m):
            if not dedans(m, xx, yy + 1) and yy + 1 < H and (xx + yy) % 3:
                t.point(xx, yy + 1, 'blanc')
    return t


def scene_mt_pyre():
    """Mont Mémoria : la montagne sacrée dans la brume, et les tombes alignées au premier plan."""
    t = Toile({
        'brume_haut': (200, 200, 220), 'brume': (224, 224, 236), 'blanc': (244, 244, 248), 'mer': (168, 192, 224),
        'mont_clair': (184, 192, 184), 'mont': (144, 156, 148), 'mont_ombre': (104, 116, 112),
        'mont_noir': (72, 80, 84),
        'herbe_claire': (184, 208, 152), 'herbe': (144, 176, 120), 'herbe_ombre': (104, 136, 96),
        'tombe_claire': (232, 232, 236), 'tombe': (192, 192, 204), 'tombe_ombre': (140, 140, 160),
        'fleur': (232, 152, 176),
    })
    bandes_v(t, 0, 0, W, 66, ['brume_haut', 'brume', 'blanc'], rangs=3)
    for y in range(62, 68):
        for x in range(W):
            t.point(x, y, 'mer' if y > 63 or (x + y) & 1 else 'blanc')
    # La montagne : une crête irrégulière ; chaque versant prend l'aplat de sa pente (montant : éclairé, descendant :
    # dans l'ombre), avec des ravines sous les sommets
    crete = [(20, 66), (44, 52), (58, 50), (76, 40), (90, 38), (104, 26), (116, 24), (130, 10), (142, 6), (150, 3),
             (160, 9), (170, 12), (182, 22), (196, 26), (210, 38), (226, 42), (240, 50), (240, 66)]
    t.poly(crete, 'mont')
    # Versant éclairé (à gauche de l'arête qui descend du sommet) et versant à l'ombre (à droite d'une autre arête)
    t.poly(crete[:10] + [(132, 30), (118, 46), (100, 66)], 'mont_clair')
    t.poly(crete[9:] + [(150, 66), (158, 40), (154, 22)], 'mont_ombre')
    t.ligne([(150, 3), (154, 22), (158, 40), (150, 66)], 'mont_noir')
    for pts in ([(116, 24), (112, 40), (106, 60)], [(90, 38), (88, 52)], [(182, 22), (188, 40), (190, 62)],
                [(210, 38), (216, 56)], [(142, 6), (136, 22), (132, 30)]):
        t.ligne(pts, 'mont_noir' if pts[0][0] > 150 else 'mont_ombre')
    t.ligne(crete[1:-1], 'mont_noir')
    for (ax, ay), (bx, by) in zip(crete[:10], crete[1:10]):
        if by < ay:
            t.ligne([(ax, ay + 1), (bx, by + 1)], 'blanc')
    # Brume accrochée aux flancs : des nappes de nuages bas
    for k, (x, y, l, h) in enumerate([(60, 50, 90, 8), (170, 40, 80, 7), (120, 60, 160, 8), (220, 58, 70, 6),
                                      (20, 60, 60, 6)]):
        nuage(t, x, y, l, h, 70 + k, 'blanc', 'brume')
    # Le flanc herbeux du premier plan
    bandes_v(t, 0, 68, W, H, ['herbe_claire', 'herbe', 'herbe_ombre'], rangs=2)

    def tombe(x, y, l, h):
        t.rect(x, y - h + l // 2, x + l, y, 'tombe')
        t.ellipse((x, y - h, x + l, y - h + l), 'tombe')
        t.rect(x, y - h + l // 2, x + max(1, l // 4), y, 'tombe_claire')
        t.rect(x + l - max(1, l // 4), y - h + l // 2, x + l, y, 'tombe_ombre')
        t.rect(x - 1, y, x + l + 1, y + max(1, l // 5), 'tombe_ombre')
        t.ligne([(x + l // 3, y - h + l // 2 + 2), (x + 2 * l // 3, y - h + l // 2 + 2)], 'tombe_ombre')
    for rang, (y, l, h, pas) in enumerate([(76, 5, 7, 14), (88, 8, 11, 22), (106, 12, 17, 34)]):
        decal = (rang * 9) % pas
        for x in range(-4 + decal, W, pas):
            if rang < 2 and 104 < x < 136:
                continue  # l'allée
            tombe(x, y, l, h)
            if rang == 2 and (x // pas) % 2:
                for k in range(3):
                    t.point(x + l + 3 + k * 2, y - 1 - k % 2, 'fleur')
    # Brume basse entre les tombes
    for y in range(78, 84):
        for x in range(W):
            if (x + y) % 2 == 0 and (x // 9 + y) % 3 and t.nom(x, y).startswith('herbe'):
                t.point(x, y, 'blanc')
    herbe(t, 0, W, H, 7, ['herbe_ombre', 'herbe', 'herbe_claire'], 31, 0.5)
    return t


def scene_new_mauville():
    """New Lavandia : la salle souterraine du générateur, ses câbles et ses machines, sous les néons."""
    t = Toile({
        'mur_clair': (208, 216, 208), 'mur': (176, 188, 180), 'mur_ombre': (136, 148, 144), 'noir': (72, 80, 88),
        'sol_clair': (216, 220, 200), 'sol': (184, 192, 172), 'sol_ombre': (144, 152, 136),
        'gen_clair': (248, 200, 120), 'gen': (224, 152, 80), 'gen_ombre': (176, 104, 64), 'gen_noir': (112, 72, 56),
        'vert': (120, 232, 144), 'cable': (88, 96, 112), 'lumiere': (248, 244, 216), 'ecran': (120, 200, 192),
    })
    fx, fy = 120, 34  # point de fuite
    bandes_v(t, 0, 0, W, 14, ['noir', 'mur_ombre'], rangs=1)  # plafond
    t.rect(52, 14, 188, 60, 'mur')  # mur du fond
    for x in range(56, 188, 22):
        t.rect(x, 18, x + 16, 52, 'mur_clair')
        t.rect(x + 15, 18, x + 16, 52, 'mur_ombre')
    t.poly([(0, 0), (52, 14), (52, 60), (0, 112)], 'mur_ombre')  # murs de côté
    t.poly([(240, 0), (188, 14), (188, 60), (240, 112)], 'mur_ombre')
    t.poly([(0, 6), (52, 18), (52, 56), (0, 96)], 'mur')
    t.poly([(240, 6), (188, 18), (188, 56), (240, 96)], 'mur')
    t.poly([(52, 60), (188, 60), (240, 112), (0, 112)], 'sol')  # sol
    for k in range(-6, 7):  # dalles : lignes vers le point de fuite
        t.ligne([(fx + k * 12, 60), (fx + k * 52, 112)], 'sol_ombre')
    for y in (66, 74, 85, 100):
        t.ligne([(int(52 - (y - 60) * 52 / 52), y), (int(188 + (y - 60) * 52 / 52), y)], 'sol_ombre')
    for x0 in (60, 150):  # néons au plafond
        t.rect(x0, 4, x0 + 30, 6, 'lumiere')
        t.rect(x0 + 4, 7, x0 + 26, 8, 'mur_clair')
    # Machines contre les murs
    for xa, sens in ((14, 1), (226, -1)):
        x0, x1 = sorted((xa, xa + sens * 26))
        t.rect(x0, 40, x1, 90, 'mur_clair')
        t.rect(x0, 40, x1, 43, 'lumiere')
        t.rect(x0 + 4, 48, x1 - 4, 62, 'noir')
        t.rect(x0 + 5, 49, x1 - 5, 61, 'ecran')
        for k in range(3):
            t.rect(x0 + 5 + k * 6, 68, x0 + 8 + k * 6, 71, 'vert' if k != 1 else 'gen')
        t.rect(x1 - 2 if sens > 0 else x0, 40, x1 if sens > 0 else x0 + 2, 90, 'mur_ombre')
    # Le générateur : des anneaux empilés, éclairé à gauche, avec des voyants verts
    cx = 120

    def anneau(y0, y1, demi):
        for y in range(y0, y1):
            for x in range(cx - demi, cx + demi + 1):
                v = (x - cx + demi) / (2 * demi)
                l = 0.9 - 0.9 * max(0.0, v) ** 1.4
                if y - y0 < 2:
                    l += 0.25
                aplat(t, x, y, ['gen_noir', 'gen_ombre', 'gen', 'gen_clair'], l, 0.06)
        t.ellipse((cx - demi, y0 - 3, cx + demi, y0 + 3), 'gen_clair')
        t.ellipse((cx - demi + 3, y0 - 2, cx + demi - 3, y0 + 2), 'gen')
    t.ellipse((cx - 44, 80, cx + 44, 98), 'sol_ombre')  # socle
    t.ellipse((cx - 42, 78, cx + 42, 94), 'mur_ombre')
    anneau(58, 88, 36)
    anneau(38, 58, 28)
    anneau(22, 38, 20)
    t.ellipse((cx - 12, 14, cx + 12, 26), 'gen_ombre')
    t.ellipse((cx - 10, 15, cx + 8, 23), 'gen_clair')
    for k in range(7):
        x = cx - 27 + k * 9
        t.rect(x, 70, x + 3, 73, 'vert')
        t.point(x, 70, 'lumiere')
    for k in range(5):
        x = cx - 18 + k * 9
        t.rect(x, 46, x + 2, 48, 'vert')
    # Câbles sur le sol
    for pts in ([(cx - 30, 92), (90, 100), (50, 104), (0, 108)], [(cx + 30, 92), (160, 98), (200, 106), (240, 104)],
                [(cx - 6, 96), (110, 106), (100, 112)]):
        t.ligne(pts, 'cable', 3)
        t.ligne([(x, y - 1) for x, y in pts], 'mur_ombre')
    return t


def scene_aqua_hideout():
    """Planque Aqua : la grotte marine aménagée, son quai de métal et le sous-marin de la Team Aqua amarré."""
    t = Toile({
        'roc_noir': (48, 56, 80), 'roc_ombre': (80, 92, 124), 'roc': (112, 124, 156), 'roc_clair': (152, 164, 192),
        'eau_fonce': (48, 96, 160), 'eau': (72, 136, 200), 'eau_claire': (128, 184, 232), 'blanc': (232, 240, 248),
        'metal_clair': (200, 208, 216), 'metal': (152, 160, 176), 'metal_ombre': (104, 112, 128),
        'sm': (56, 80, 128), 'sm_clair': (96, 128, 176), 'lampe': (248, 232, 160), 'rouge': (208, 72, 72),
    })
    t.rect(0, 0, W, H, 'roc_noir')
    # La voûte de la grotte et l'ouverture du fond, plus claire
    t.ellipse((40, 8, 200, 96), 'roc_ombre')
    t.ellipse((58, 18, 182, 90), 'eau_fonce')
    for k, (x, y, rx, ry) in enumerate([(30, 20, 40, 26), (210, 18, 40, 26), (120, 2, 80, 12), (6, 70, 26, 40),
                                        (234, 70, 26, 40)]):
        rocher(t, x, y, rx, ry, ['roc_noir', 'roc_ombre', 'roc', 'roc_clair'], 70 + k, 'roc_noir', plat_bas=False)
    for x in range(52, 190, 9):  # stalactites
        h = 4 + (x * 7) % 9
        t.poly([(x - 3, 12), (x + 3, 12), (x, 12 + h)], 'roc_ombre')
        t.point(x - 1, 13, 'roc_clair')
    # L'eau du chenal
    for y in range(56, H):
        for x in range(W):
            if t.nom(x, y) in ('roc_noir', 'eau_fonce') or y > 60:
                aplat(t, x, y, ['eau_fonce', 'eau'], (y - 56) / 56 * 1.3, 0.1)
    rnd = random.Random(9)
    for _ in range(70):
        x, y = rnd.randrange(W), rnd.randrange(60, H)
        t.ligne([(x, y), (x + rnd.randint(2, 10), y)], 'eau_claire')
    # Les quais de métal, à gauche et à droite, en perspective
    for sens in (1, -1):
        def q(x, y):
            return (x if sens > 0 else W - x, y)
        t.poly([q(0, 76), q(70, 62), q(84, 62), q(26, 112), q(0, 112)], 'metal')
        t.poly([q(0, 76), q(70, 62), q(72, 64), q(0, 80)], 'metal_clair')
        t.poly([q(84, 62), q(26, 112), q(32, 112), q(88, 64)], 'metal_ombre')
        for k in range(6):  # garde-corps
            x = 6 + k * 12
            y = 75 - k * 2.4
            t.ligne([q(x, y), q(x, y - 12)], 'metal_ombre')
        t.ligne([q(4, 64), q(72, 50)], 'metal_clair', 2)
        lx, ly = q(60, 44)
        t.ellipse((lx - 3, ly - 3, lx + 3, ly + 3), 'lampe')
    # Le sous-marin, au milieu du chenal
    cx, cy = 120, 66
    t.ellipse((cx - 50, cy - 9, cx + 50, cy + 9), 'sm')
    t.ellipse((cx - 46, cy - 9, cx + 40, cy - 1), 'sm_clair')
    t.rect(cx - 10, cy - 24, cx + 12, cy - 6, 'sm')
    t.rect(cx - 10, cy - 24, cx - 4, cy - 6, 'sm_clair')
    t.rect(cx - 12, cy - 26, cx + 14, cy - 23, 'metal')
    # Emblème de la Team Aqua sur le kiosque : un « A » blanc en forme d'os
    t.ligne([(cx - 4, cy - 9), (cx + 1, cy - 20), (cx + 6, cy - 9)], 'blanc', 2)
    t.ligne([(cx - 2, cy - 13), (cx + 4, cy - 13)], 'blanc')
    t.ellipse((cx - 6, cy - 11, cx - 2, cy - 7), 'blanc')
    t.ellipse((cx + 4, cy - 11, cx + 8, cy - 7), 'blanc')
    for k in range(5):
        x = cx - 36 + k * 16
        t.ellipse((x - 2, cy - 2, x + 2, cy + 2), 'lampe' if k != 2 else 'rouge')
    for y in range(cy + 4, cy + 10):  # reflets de la coque dans l'eau
        for x in range(cx - 50, cx + 50):
            if (x + y) % 4 == 0 and t.nom(x, y) in ('sm', 'sm_clair'):
                t.point(x, y, 'eau')
    for k in range(40):
        x = cx - 52 + k * 3
        t.point(x, cy + 9 + (k % 3 == 0), 'blanc')
    return t


def scene_magma_hideout():
    """Planque Magma : la galerie creusée dans le volcan, la passerelle au-dessus de la lave, la porte blindée."""
    t = Toile({
        'roc_noir': (64, 40, 44), 'roc_ombre': (104, 64, 60), 'roc': (148, 92, 76), 'roc_clair': (192, 136, 112),
        'cendre': (176, 164, 160), 'lave_fonce': (200, 64, 40), 'lave': (240, 120, 48), 'lave_claire': (248, 208, 104),
        'metal_clair': (208, 208, 216), 'metal': (160, 160, 172), 'metal_ombre': (104, 104, 120), 'noir': (40, 32, 40),
        'rouge': (200, 48, 48), 'vapeur': (236, 228, 228),
    })
    t.rect(0, 0, W, H, 'roc_ombre')
    bandes_v(t, 0, 0, W, 40, ['roc_noir', 'roc_ombre'], rangs=2)
    # Parois de la galerie
    for k, (x, y, rx, ry) in enumerate([(20, 30, 40, 40), (220, 30, 40, 42), (60, 8, 50, 16), (180, 6, 50, 16),
                                        (120, -4, 60, 14), (10, 90, 30, 26), (232, 88, 28, 26)]):
        rocher(t, x, y, rx, ry, ['roc_noir', 'roc_ombre', 'roc', 'roc_clair'], 90 + k, 'noir', plat_bas=False)
    # La porte blindée au fond, dans un cadre de métal
    t.rect(92, 20, 148, 66, 'metal_ombre')
    t.rect(94, 22, 146, 64, 'metal')
    t.rect(94, 22, 146, 24, 'metal_clair')
    t.rect(119, 24, 121, 64, 'metal_ombre')
    for x in (98, 140):
        for y in (28, 58):
            t.point(x, y, 'metal_clair')
    # Emblème de la Team Magma : un « M » en forme de montagne rouge, sur le centre de la porte
    t.poly([(108, 50), (114, 34), (120, 44), (126, 34), (132, 50), (126, 50), (126, 42), (120, 52), (114, 42), (114, 50)],
           'rouge')
    t.ligne([(114, 34), (108, 50)], 'lave_claire')
    # Sol de la galerie : roche et cendre, coulées de lave qui brillent
    t.poly([(0, 66), (240, 66), (240, 112), (0, 112)], 'roc')
    bandes_v(t, 0, 66, W, H, ['cendre', 'roc', 'roc_ombre'], rangs=2)
    for pts in ([(0, 84), (40, 80), (70, 92), (60, 112), (0, 112)], [(170, 112), (180, 90), (214, 84), (240, 88),
                                                                    (240, 112)]):
        m = masque_poly(pts)
        for x, y in pixels(m):
            aplat(t, x, y, ['lave_claire', 'lave', 'lave_fonce'], (y - 80) / 32, 0.12)
        contour(t, m, 'noir', 'lave_claire')
    # La passerelle de métal jusqu'à la porte
    t.poly([(104, 66), (136, 66), (168, 112), (72, 112)], 'metal')
    t.poly([(104, 66), (108, 66), (80, 112), (72, 112)], 'metal_clair')
    t.poly([(132, 66), (136, 66), (168, 112), (160, 112)], 'metal_ombre')
    for y in (72, 80, 90, 102):
        g = 104 - (y - 66) * 32 / 46
        d = 136 + (y - 66) * 32 / 46
        t.ligne([(g, y), (d, y)], 'metal_ombre')
    for k in range(5):  # garde-corps
        y = 70 + k * 9
        for g in (104 - (y - 66) * 32 / 46 - 2, 136 + (y - 66) * 32 / 46 + 2):
            t.ligne([(g, y), (g, y - 8 - k * 2)], 'noir')
    # Vapeur qui monte des coulées
    rnd = random.Random(4)
    for bx in (30, 200):
        for k in range(26):
            x = bx + rnd.randint(-10, 10) + k // 3
            y = 78 - k * 2
            r = 2 + k // 6
            t.ellipse((x - r, y - r, x + r, y + r), 'vapeur' if k % 3 else 'cendre')
    return t


REGI_ROCHE = {'roc_clair': (232, 168, 128), 'roc': (192, 112, 84), 'roc_ombre': (140, 76, 64),
              'roc_noir': (96, 52, 52), 'porte': (36, 28, 32)}
REGI_RAMPE = ['roc_noir', 'roc_ombre', 'roc', 'roc_clair']


def rochers_regi(t, positions, graine):
    """Les rochers rouges éparpillés autour des buttes des Regi."""
    for k, (x, y, rx, ry) in enumerate(positions):
        rocher(t, x, y, rx, ry, REGI_RAMPE[1:], graine + k, 'roc_noir')


def scene_desert_ruins():
    """Ruines Désert : la butte rouge de la salle de Regirock au milieu du désert de la Route 111."""
    t = Toile(dict({
        'ciel_haut': (184, 204, 232), 'ciel': (216, 224, 236), 'voile': (244, 236, 212), 'loin': (220, 196, 156),
        'sable_clair': (248, 232, 168), 'sable': (236, 208, 136), 'sable_ombre': (208, 172, 104),
        'dessus': (220, 160, 120), 'cactus': (128, 164, 96), 'cactus_ombre': (88, 124, 76),
    }, **REGI_ROCHE))
    bandes_v(t, 0, 0, W, 50, ['ciel_haut', 'ciel', 'voile'], rangs=2)
    t.poly([(0, 50), (10, 42), (46, 40), (58, 48), (176, 48), (186, 38), (224, 37), (240, 44), (240, 50)], 'loin')
    bandes_v(t, 0, 48, W, H, ['sable_clair', 'sable', 'sable_ombre'], rangs=2)
    for y in range(54, H, 6):  # rides du sable
        for x in range(0, W, 2):
            if math.sin(x / 9 + y) > 0.55:
                t.point(x, y + int(2 * math.sin(x / 13)), 'sable_ombre' if y > 70 else 'sable')
    butte_regi(t, 120, 96, REGI_RAMPE, 'dessus', 'porte', 110)
    rochers_regi(t, [(26, 70, 9, 7), (214, 66, 8, 6), (36, 104, 12, 8), (204, 104, 13, 8), (64, 100, 6, 4),
                     (178, 98, 6, 4), (90, 56, 5, 3), (160, 56, 5, 3)], 114)
    for x, y0, h in [(12, 92, 14), (230, 90, 12)]:  # cactus
        t.rect(x, y0 - h, x + 3, y0, 'cactus')
        t.rect(x + 3, y0 - h, x + 3, y0, 'cactus_ombre')
        t.rect(x - 5, y0 - h + 6, x - 1, y0 - h + 8, 'cactus')
        t.rect(x - 5, y0 - h + 2, x - 4, y0 - h + 8, 'cactus')
    rnd = random.Random(7)  # sable qui vole
    for _ in range(26):
        x, y = rnd.randrange(-20, W), rnd.randrange(0, 70)
        for k in range(rnd.randint(6, 22)):
            if (k + y) % 3:
                t.point(x + k, y + k // 6, 'voile')
    return t


def scene_island_cave():
    """Grotte de l'Île : la butte rouge de la salle de Regice sur son îlot de sable, en pleine mer (Route 105)."""
    t = Toile(dict({
        'ciel_haut': (152, 196, 240), 'ciel': (196, 222, 248), 'blanc': (248, 248, 248), 'nuage_ombre': (208, 216, 240),
        'mer': (88, 148, 216), 'mer_clair': (152, 196, 240),
        'sable_clair': (248, 236, 192), 'sable': (232, 212, 156), 'dessus': (220, 160, 120),
    }, **REGI_ROCHE))
    bandes_v(t, 0, 0, W, 44, ['ciel_haut', 'ciel', 'blanc'], rangs=2)
    nuage(t, 190, 18, 70, 11, 41)
    nuage(t, 40, 26, 46, 8, 42)
    mer(t, 44, H, 'blanc', 'mer', 'mer_clair', 'blanc', 43)
    for x, y in [(70, 14), (84, 20), (150, 10)]:  # Goélise au loin
        t.ligne([(x - 4, y - 2), (x, y), (x + 4, y - 2)], 'roc_ombre')
    # L'îlot de sable, son écume
    t.ellipse((6, 56, 234, 124), 'blanc')
    t.ellipse((10, 58, 230, 122), 'sable')
    t.ellipse((24, 62, 216, 118), 'sable_clair')
    t.ellipse((40, 66, 200, 116), 'sable')
    butte_regi(t, 120, 98, REGI_RAMPE, 'dessus', 'porte', 120)
    rochers_regi(t, [(30, 84, 9, 6), (210, 82, 10, 7), (60, 104, 9, 6), (184, 106, 10, 6), (44, 70, 6, 4),
                     (196, 68, 6, 4)], 124)
    return t


def scene_ancient_tomb():
    """Tombeau Ancien : la butte rouge de la salle de Registeel dans les prairies de la Route 120, entre les mares,
    la forêt au fond, sous la pluie."""
    t = Toile(dict({
        'ciel': (196, 202, 220), 'blanc': (236, 238, 244),
        'arbre_fonce': (64, 104, 84), 'arbre': (96, 144, 100),
        'herbe_ombre': (100, 148, 88), 'herbe': (140, 188, 112), 'herbe_claire': (184, 216, 144),
        'eau': (136, 184, 232), 'dessus': (196, 176, 120),
    }, **REGI_ROCHE))
    bandes_v(t, 0, 0, W, 40, ['ciel', 'blanc'], rangs=2)
    for k in range(14):  # la forêt au fond
        sapin(t, -6 + k * 19, 50, 34 + (k * 13) % 12, ['arbre_fonce', 'arbre', 'herbe'])
    bandes_v(t, 0, 48, W, H, ['herbe_claire', 'herbe', 'herbe_ombre'], rangs=2)
    for box in [(14, 92, 70, 108), (168, 96, 236, 114), (100, 104, 150, 118)]:  # mares
        t.ellipse(box, 'herbe_ombre')
        t.ellipse((box[0] + 2, box[1] + 1, box[2] - 2, box[3] - 1), 'eau')
        t.ligne([(box[0] + 8, box[1] + 4), (box[0] + 18, box[1] + 4)], 'blanc')
    butte_regi(t, 120, 94, REGI_RAMPE, 'dessus', 'porte', 130)
    for xx in range(46, 194, 5):  # herbe sur le dessus de la butte
        t.point(xx, 69 if 70 < xx < 170 else 70, 'herbe')
    rochers_regi(t, [(24, 66, 8, 6), (216, 64, 9, 6), (86, 98, 6, 4), (160, 98, 7, 4)], 134)
    herbe(t, 0, W, H + 2, 9, ['herbe_ombre', 'herbe', 'herbe_claire'], 51, 0.9)
    rnd = random.Random(52)  # pluie fine
    for _ in range(80):
        x, y = rnd.randrange(W), rnd.randrange(H)
        t.ligne([(x, y), (x - 2, y + 4)], 'blanc')
    return t


SCENES = {
    'mt_pyre': ('Mont Mémoria', scene_mt_pyre),
    'sky_pillar': ('Pilier Céleste', scene_sky_pillar),
    'aqua_hideout': ('Planque Aqua', scene_aqua_hideout),
    'magma_hideout': ('Planque Magma', scene_magma_hideout),
    'abandoned_ship': ('Épave', scene_abandoned_ship),
    'new_mauville': ('New Lavandia', scene_new_mauville),
    'mirage_tower': ('Tour Mirage', scene_mirage_tower),
    'desert_ruins': ('Ruines Désert', scene_desert_ruins),
    'island_cave': ('Grotte Island', scene_island_cave),
    'ancient_tomb': ('Tombeau Antique', scene_ancient_tomb),
}


# --- Format des aperçus de RF -----------------------------------------------------------------------------------

def ecrire_apercu(toile, dossier):
    """Écrit tiles.png et tilemap.bin au format des aperçus de RF."""
    cadre = Image.open(os.path.join(CADRE, 'tiles.png'))
    cadre_pal = cadre.getpalette()[:96]
    cadre_px = cadre.load()
    cadre_tm = open(os.path.join(CADRE, 'tilemap.bin'), 'rb').read()
    larg_cadre = cadre.size[0] // 8
    tpx = toile.px

    tuiles = [tuple([0] * 64)]  # tuile 0 vide (hors écran, colonnes 30-31)
    index = {tuiles[0]: 0}
    tilemap = [0] * (32 * 20)

    def ajouter(pix):
        if pix not in index:
            index[pix] = len(tuiles)
            tuiles.append(pix)
        return index[pix]

    for ty in range(20):
        for tx in range(30):
            if IMAGE_Y <= ty < IMAGE_Y + H // 8:
                pix = tuple(tpx[tx * 8 + x, (ty - IMAGE_Y) * 8 + y] + 1 for y in range(8) for x in range(8))
                tilemap[ty * 32 + tx] = ajouter(pix) | (13 << 12)
            else:
                e = struct.unpack_from('<H', cadre_tm, (ty * 32 + tx) * 2)[0]
                t = e & 0x3FF
                x0, y0 = (t % larg_cadre) * 8, (t // larg_cadre) * 8
                pix = tuple(cadre_px[x0 + x, y0 + y] for y in range(8) for x in range(8))
                tilemap[ty * 32 + tx] = ajouter(pix) | (e & 0xFC00)
    if len(tuiles) > 0x1C2:  # la fenêtre du nom commence à la tuile 0x1C2 (sMapNameWindow.baseBlock)
        sys.exit('%s : %d tuiles, plus que les 0x1C2 de RF' % (dossier, len(tuiles)))

    larg = 15
    haut = (len(tuiles) + larg - 1) // larg
    sortie = Image.new('P', (larg * 8, haut * 8), 0)
    couleurs = toile.rgb + [(0, 0, 0)] * (15 - len(toile.rgb))
    pal = [(255, 255, 90)] + [((r >> 3) << 3, (g >> 3) << 3, (b >> 3) << 3) for r, g, b in couleurs]
    sortie.putpalette([v for c in pal for v in c] + cadre_pal[48:96])
    spx = sortie.load()
    for n, pix in enumerate(tuiles):
        x0, y0 = (n % larg) * 8, (n // larg) * 8
        for i, v in enumerate(pix):
            spx[x0 + i % 8, y0 + i // 8] = v
    os.makedirs(dossier, exist_ok=True)
    sortie.save(os.path.join(dossier, 'tiles.png'))
    with open(os.path.join(dossier, 'tilemap.bin'), 'wb') as f:
        f.write(struct.pack('<640H', *tilemap))


def rendu_ecran(dossier):
    """L'aperçu tel que l'écran le montre (sans le nom), depuis tiles.png et tilemap.bin."""
    tiles = Image.open(os.path.join(dossier, 'tiles.png'))
    pal = tiles.getpalette()[:96]
    tm = open(os.path.join(dossier, 'tilemap.bin'), 'rb').read()
    larg = tiles.size[0] // 8
    px = tiles.load()
    out = Image.new('RGB', (240, 160))
    opx = out.load()
    for ty in range(20):
        for tx in range(30):
            e = struct.unpack_from('<H', tm, (ty * 32 + tx) * 2)[0]
            t, hf, vf, p = e & 0x3FF, (e >> 10) & 1, (e >> 11) & 1, e >> 12
            for y in range(8):
                for x in range(8):
                    c = px[(t % larg) * 8 + (7 - x if hf else x), (t // larg) * 8 + (7 - y if vf else y)] & 15
                    i = (p - 13) * 16 + c
                    opx[tx * 8 + x, ty * 8 + y] = tuple(pal[i * 3:i * 3 + 3]) if c else (0, 0, 0)
    return out


def planche(images, chemin, colonnes=2):
    """Planche de relecture : chaque aperçu à l'écran (240 x 160), agrandi 2 fois, avec son nom."""
    lignes = (len(images) + colonnes - 1) // colonnes
    marge = 20
    out = Image.new('RGB', (colonnes * 488, lignes * (328 + marge)), (40, 40, 40))
    try:
        police = ImageFont.truetype('arial.ttf', 16)
    except OSError:
        police = ImageFont.load_default()
    d = ImageDraw.Draw(out)
    for i, (titre, im) in enumerate(images):
        x, y = (i % colonnes) * 488 + 4, (i // colonnes) * (328 + marge) + 4
        d.text((x, y), '%d. %s' % (i + 1, titre), fill=(255, 255, 255), font=police)
        out.paste(im.resize((480, 320), Image.NEAREST), (x, y + marge))
    out.save(chemin)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--planche', help='planche de relecture seulement, dans ce fichier')
    ap.add_argument('lieux', nargs='*', help='lieux (défaut : tous)')
    args = ap.parse_args()
    noms = args.lieux or list(SCENES)
    images = []
    for nom in noms:
        titre, fonction = SCENES[nom]
        dossier = os.path.join(SORTIE, nom) if not args.planche else os.path.join(
            os.path.dirname(os.path.abspath(args.planche)), 'apercus', nom)
        ecrire_apercu(fonction(), dossier)
        images.append((titre, rendu_ecran(dossier)))
        print(nom, 'OK')
    planche(images, args.planche or os.path.join(RACINE, 'build', 'apercus_hoenn_dessins.png'))


if __name__ == '__main__':
    main()
