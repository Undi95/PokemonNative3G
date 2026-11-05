#!/usr/bin/env python3
"""Aperçus d'entrée dessinés pour les lieux uniques de Hoenn (v1.1, 2026-11-05).

Rouge Feu montre une illustration à l'entrée de ses donjons (kanto_map_preview_screen.c). Les lieux de Hoenn qui
ressemblent à un lieu de Kanto en reprennent l'image ; les lieux uniques (Pilier Céleste, Tour Mirage...) ont ici une
illustration dessinée dans le style de RF : vue en perspective, couleurs douces, 15 couleurs.

Le style de RF, relevé sur ses aperçus : de grands aplats de couleurs claires, un tramage en damier seulement à la
limite de deux teintes (horizon, ombres), des reflets en traits horizontaux sur l'eau, de la roche en gros blocs
arrondis éclairés par le haut à gauche. Comme RF le fait entre ses propres aperçus, le décor générique reprend des
morceaux peints de RF recolorés dans la palette du lieu (nuages, mer, roche, fougères, sapins, collines, vapeur :
coller_rf, texturer, massif_rf) ; le sujet unique de chaque lieu (tour, épave, butte, générateur...) est dessiné en
code (fonctions scene_*), d'après Rubis Oméga / Saphir Alpha pour le Pilier Céleste et les ruines des Regi.

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


# --- Morceaux peints des aperçus de RF --------------------------------------------------------------------------
# RF compose ses aperçus en reprenant des morceaux des autres (la Grotte Taupiqueur reprend le Tunnel Roche, les
# grottes de Sevii reprennent les Îles Écume...). On fait pareil pour le décor générique (nuages, mer, roche, fougères,
# herbes, collines, sapins, vapeur) : un morceau d'un aperçu de RF, recoloré dans la palette du lieu (chaque teinte
# du morceau prend la teinte de la rampe au même rang de luminosité). Le sujet unique du lieu est dessiné à part.

_RF = {}


def rf(nom):
    """L'image (240 x 112) d'un aperçu de RF, graphics/kanto/map_preview/<nom>."""
    if nom not in _RF:
        _RF[nom] = rendu_ecran(os.path.join(RACINE, 'graphics', 'kanto', 'map_preview', nom)).crop(
            (0, IMAGE_Y * 8, W, IMAGE_Y * 8 + H))
    return _RF[nom]


def lum(c):
    return 0.3 * c[0] + 0.55 * c[1] + 0.15 * c[2]


def recoloration(pixels_rgb, rampe):
    """{teinte du morceau : nom de la rampe} : les teintes rangées par luminosité, réparties sur la rampe (du sombre au
    clair) selon la part de pixels qu'elles occupent."""
    compte = {}
    for c in pixels_rgb:
        compte[c] = compte.get(c, 0) + 1
    total = sum(compte.values()) or 1
    res, cumul = {}, 0
    for c in sorted(compte, key=lum):
        milieu = (cumul + compte[c] / 2) / total
        cumul += compte[c]
        res[c] = rampe[min(len(rampe) - 1, int(milieu * len(rampe)))]
    return res


def coller_rf(t, nom, box, x, y, rampe, garder=None, miroir=False, masque_clip=None):
    """Colle le morceau `box` de l'aperçu de RF `nom` en (x, y), recoloré sur `rampe`. `garder(rgb)` choisit les
    pixels du morceau à coller (le reste est transparent)."""
    morceau = rf(nom).crop(box)
    if miroir:
        morceau = morceau.transpose(Image.FLIP_LEFT_RIGHT)
    px = morceau.load()
    l, h = morceau.size
    garder = garder or (lambda c: True)
    gardes = [px[i, j] for j in range(h) for i in range(l) if garder(px[i, j])]
    table = recoloration(gardes, rampe)
    for j in range(h):
        for i in range(l):
            c = px[i, j]
            if garder(c) and (masque_clip is None or dedans(masque_clip, x + i, y + j)):
                t.point(x + i, y + j, table[c])


def texturer(t, m, nom, box, rampe, ox=0, oy=0, miroir_alterne=True):
    """Remplit le masque `m` avec la texture du morceau `box` de RF (répété, une rangée sur deux en miroir pour cacher
    les raccords), recolorée sur `rampe`."""
    morceau = rf(nom).crop(box)
    inverse = morceau.transpose(Image.FLIP_LEFT_RIGHT)
    l, h = morceau.size
    px, pxi = morceau.load(), inverse.load()
    table = recoloration([px[i, j] for j in range(h) for i in range(l)], rampe)
    for x, y in pixels(m):
        rang_x, rang_y = (x + ox) // l, (y + oy) // h
        src = pxi if miroir_alterne and (rang_x + rang_y) % 2 else px
        t.point(x, y, table[src[(x + ox) % l, (y + oy) % h]])


def est_ciel(c):
    return c[2] > c[0] + 24 and lum(c) > 150


def est_nuage(c):
    return lum(c) > 214 and -4 <= c[2] - c[0] < 30


ROCHE_RF = ('altering_cave', (120, 0, 240, 74))   # la roche en gros blocs ronds de la Grotte Métamo de RF


def massif_rf(t, pts, rampe, dessus, graine, ox=0, oy=0, ombre=0.3, texture=ROCHE_RF, clair_dessus=None):
    """Un massif de roche (butte, falaise, paroi) au contour irrégulier, peint avec la roche de RF recolorée sur
    `rampe` (du sombre au clair) : le dessus plat éclairé, le pied sombre, et le côté droit (la part `ombre`) un ton
    plus bas. Renvoie son masque."""
    contour_ = organique(pts, 1.6, graine)
    m = masque_poly(contour_)
    texturer(t, m, texture[0], texture[1], rampe, ox, oy)
    xs = [x for x, _ in pixels(m)]
    if xs and ombre:
        limite = max(xs) - (max(xs) - min(xs)) * ombre
        for x, y in pixels(m):
            if x > limite and ((x + y) & 1 or x > limite + 4):
                k = rampe.index(t.nom(x, y)) if t.nom(x, y) in rampe else 1
                t.point(x, y, rampe[max(0, k - 1)])
    haut, bas = {}, {}
    for x, y in pixels(m):
        haut[x] = min(haut.get(x, y), y)
        bas[x] = max(bas.get(x, y), y)
    if dessus:
        for x, y0 in haut.items():
            for k in range(3):
                t.point(x, y0 + k, (clair_dessus or dessus) if k == 0 else dessus)
    for x, y1 in bas.items():
        t.point(x, y1, rampe[0])
    return m


def ellipse_pts(cx, cy, rx, ry, n=24):
    """Les sommets d'une ellipse, pour un contour irrégulier (organique)."""
    return [(cx + math.cos(2 * math.pi * k / n) * rx, cy + math.sin(2 * math.pi * k / n) * ry) for k in range(n)]


def butte_rf(t, cx, base, rampe, dessus, porte, graine):
    """L'entrée d'une salle des Regi (Rubis Oméga / Saphir Alpha) : une butte de roche rouge en deux gradins, peinte
    avec la roche de RF, et la bouche sombre de la grotte, en arc, posée au sol."""
    massif_rf(t, [(cx - 52, base - 22), (cx - 40, base - 48), (cx + 40, base - 48), (cx + 52, base - 22)], rampe,
              dessus, graine, ox=graine * 7)
    massif_rf(t, [(cx - 80, base), (cx - 64, base - 28), (cx + 64, base - 28), (cx + 80, base)], rampe, dessus,
              graine + 1, ox=graine * 3 + 40, oy=20)
    bouche(t, cx, base, 20, 24, porte, rampe[-1])


# Des nuages entiers de RF, qui ne touchent pas le bord de leur morceau (repérés par composantes connexes : ailleurs,
# les nuages débordent du morceau ou se confondent avec le ciel pâle de l'horizon) : le cumulus de la Route Victoire et
# la traînée du Mont Sélénite.
NUAGES_RF = [('victory_road', (4, 1, 81, 32)), ('mt_moon', (16, 14, 65, 26)), ('victory_road', (4, 1, 81, 32))]
COLLINES_RF = ('safari_zone', (120, 26, 240, 52))    # les collines lointaines du Parc Safari
SAPINS_RF = ('victory_road', (0, 26, 88, 104))        # la forêt de sapins de la Route Victoire
VOLCAN_RF = ('mt_ember', (92, 18, 200, 54))           # le volcan lointain du Mont Braise
VAPEUR_RF = ('mt_ember', (186, 40, 236, 104))         # les jets de vapeur du Mont Braise


def loin(c):
    """Un pixel de décor lointain (ni ciel ni nuage)."""
    return not est_ciel(c) and not est_nuage(c)


def ciel_rf(t, y1, rampe, nuages, blanc='blanc', ombre='nuage_ombre'):
    """Ciel en bandes, et des nuages peints de RF : `nuages` = [(n° du morceau de NUAGES_RF, x, y, miroir)]."""
    bandes_v(t, 0, 0, W, y1, rampe, rangs=2)
    for k, x, y, miroir in nuages:
        nom, box = NUAGES_RF[k]
        coller_rf(t, nom, box, x, y, [ombre, blanc], est_nuage, miroir,
                  masque_clip=masque_poly([(0, 0), (W, 0), (W, y1), (0, y1)]))


def bloc_rf(t, cx, cy, rx, ry, rampe, graine, sol=True):
    """Un rocher arrondi peint avec la roche de RF (contour irrégulier, base plate s'il est posé au sol)."""
    pts = []
    for k in range(12):
        a = math.pi + 2 * math.pi * k / 12
        y = cy + math.sin(a) * ry
        if sol and y > cy:
            y = cy + (y - cy) * 0.3
        pts.append((cx + math.cos(a) * rx, y))
    return massif_rf(t, pts, rampe, None, graine, ox=graine * 13, oy=graine * 5, ombre=0.35)


def mer_rf(t, y0, y1, rampe, horizon):
    """La mer de RF (celle de la Grotte Métamo), répétée sur toute la largeur, avec la ligne claire de l'horizon."""
    m = masque_poly([(0, y0), (W, y0), (W, y1), (0, y1)])
    texturer(t, m, 'altering_cave', (0, 20, 84, 44), rampe, 0, 0)
    for x in range(W):
        t.point(x, y0, horizon)
        if x & 1:
            t.point(x, y0 + 1, horizon)


def fougere_rf(t, x, y, rampe, miroir=False):
    """Les fougères du premier plan de RF (Grotte Métamo), pour encadrer la scène."""
    coller_rf(t, 'altering_cave', (190, 74, 240, 112), x, y, rampe,
              lambda c: c[1] > c[0] + 12 and c[1] > c[2], miroir)


def rocaille_rf(t, x, y, rampe, miroir=False, box=(0, 74, 70, 112)):
    """Des blocs de roche de RF au premier plan (le bas gauche de la Grotte Métamo)."""
    coller_rf(t, 'altering_cave', box, x, y, rampe, lambda c: not est_ciel(c) and not (c[1] > c[0] + 12), miroir)


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
    ciel_rf(t, 62, ['ciel_haut', 'ciel', 'blanc'], [(0, 2, 2, False), (0, 176, -4, True), (2, 196, 24, False)],
            ombre='ciel')
    mer_rf(t, 58, H, ['mer', 'mer', 'mer_clair', 'blanc'], 'blanc')
    # L'île : un plateau de sable aux bords irréguliers, la mer tout autour, l'écume sur ses bords
    ile = organique([(10, 112), (230, 112), (210, 70), (30, 70)], 3, 6, pas=8)
    t.poly([(x + (-3 if x < 120 else 3), y - 2) for x, y in ile], 'blanc')
    m = masque_poly(ile)
    bandes_v(t, 0, 66, W, H, ['sable_clair', 'sable'], rangs=2, masque=m)
    # Falaises rouges sur l'île, de part et d'autre de la tour, peintes avec la roche de RF
    rampe_f = ['pierre_noire', 'falaise_ombre', 'falaise', 'falaise_claire']
    massif_rf(t, [(30, 82), (38, 62), (70, 60), (78, 82)], rampe_f, 'pierre', 1, 5, 0, clair_dessus='pierre_claire')
    massif_rf(t, [(162, 82), (170, 58), (204, 60), (214, 82)], rampe_f, 'pierre', 3, 60, 10,
              clair_dessus='pierre_claire')
    bouche(t, 194, 82, 12, 15, 'porte', 'pierre')  # la grotte vers l'entrée du Pilier
    # La tour : d'énormes blocs de pierre au grain peint (la roche de RF, recolorée en ocre), la face avant éclairée,
    # le flanc droit dans l'ombre ; elle sort de l'image par le haut
    x0, x1, flanc, base = 70, 160, 172, 84
    texturer(t, masque_poly([(x0, 0), (x1, 0), (x1, base), (x0, base)]), ROCHE_RF[0], ROCHE_RF[1],
             ['pierre_ombre', 'pierre', 'pierre', 'pierre_claire'], 11, 3)
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
                        t.point(xx, yy, 'pierre_ombre')
                    elif yy == y_assise + 1 or xx == g + 1:
                        t.point(xx, yy, 'pierre_claire')
                    elif sombre and (xx + yy) & 1 and t.nom(xx, yy) == 'pierre':
                        t.point(xx, yy, 'pierre_ombre')
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
    # Rochers rouges sur le sable, et deux gros au premier plan qui encadrent la scène
    for k, (x, y, rx, ry) in enumerate([(84, 100, 7, 5), (150, 102, 8, 5), (182, 96, 6, 4), (120, 110, 7, 4),
                                        (22, 108, 22, 16), (220, 110, 24, 18), (58, 96, 6, 4)]):
        bloc_rf(t, x, y, rx, ry, rampe_f, 40 + k)
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
    ciel_rf(t, 66, ['ciel_haut', 'ciel', 'voile'], [(1, 30, 10, False), (1, 170, 4, True)], 'voile', 'ciel')
    # Mesas lointaines : les collines de RF, noyées dans le sable qui vole
    coller_rf(t, COLLINES_RF[0], COLLINES_RF[1], 0, 40, ['loin', 'voile'], loin)
    coller_rf(t, COLLINES_RF[0], COLLINES_RF[1], 130, 38, ['loin', 'voile'], loin, miroir=True)
    # Le sol et les dunes, plus foncées en approchant
    bandes_v(t, 0, 62, W, H, ['sable_clair', 'sable', 'sable_ombre'], rangs=2)
    for pts, rampe in [([(0, 100), (40, 84), (90, 90), (130, 112), (0, 112)], ['sable_clair', 'sable_ombre']),
                       ([(150, 112), (192, 86), (240, 80), (240, 112)], ['sable_clair', 'sable', 'sable_fonce'])]:
        m = masque_poly(organique(pts, 2, len(pts)))
        ys = [p[1] for p in pts]
        bandes_v(t, 0, min(ys), W, H, rampe, masque=m)
    # La tour : un fût de grosses pierres de sable au grain peint (roche de RF), éclairé à gauche, plus étroit en haut
    cx, base, sommet = 110, 92, 6
    profil = []
    for y in range(sommet, base):
        u = (base - y) / (base - sommet)
        demi = 21 - 6 * u
        profil += [(cx - demi, y)]
    fut = masque_poly(profil + [(2 * cx - x, y) for x, y in reversed(profil)])
    texturer(t, fut, ROCHE_RF[0], ROCHE_RF[1], ['tour_ombre', 'tour', 'tour', 'tour_claire'], 7, 2)
    rampe_t = ['tour_noire', 'tour_ombre', 'tour', 'tour_claire']
    for x, y in pixels(fut):
        u = (base - y) / (base - sommet)
        demi = 21 - 6 * u
        v = (x - (cx - demi)) / (2 * demi)
        k = rampe_t.index(t.nom(x, y))
        if v > 0.62 and ((x + y) & 1 or v > 0.78):  # le côté droit du cylindre, dans l'ombre
            t.point(x, y, rampe_t[max(0, k - 1)])
        if (y - sommet) % 10 == 0:
            t.point(x, y, 'tour_ombre' if v < 0.7 else 'tour_noire')
        elif (y - sommet) % 10 == 1 and v < 0.62:
            t.point(x, y, 'tour_claire')
    for x, y in pixels(fut):
        if not dedans(fut, x - 1, y) or not dedans(fut, x + 1, y):
            t.point(x, y, 'tour_noire')
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
    # Rochers de grès au premier plan (roche de RF)
    for k, (x, y, rx, ry) in enumerate([(14, 108, 20, 13), (226, 106, 22, 15), (168, 100, 7, 4), (72, 98, 6, 4)]):
        bloc_rf(t, x, y, rx, ry, ['tour_noire', 'sable_fonce', 'sable_ombre', 'sable_clair'], 70 + k)
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
    ciel_rf(t, 58, ['ciel_haut', 'ciel', 'blanc'], [(0, 20, 6, False), (1, 150, 10, False), (0, 176, -4, True)])
    mer_rf(t, 58, H, ['mer', 'mer', 'mer_clair', 'blanc'], 'blanc')

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
    # La coque rongée : la rouille prend le grain de la roche de RF, et des coulures descendent des hublots
    rouille = masque()
    for x in range(W):
        for y in range(H):
            if t.nom(x, y) in ('rouille', 'rouille_fonce'):
                rouille.putpixel((x, y), 255)
    texturer(t, rouille, ROCHE_RF[0], ROCHE_RF[1], ['noir', 'rouille_fonce', 'rouille', 'rouille'], 9, 4)
    rnd_c = random.Random(12)
    for k in range(22):
        x = rnd_c.randint(-90, 84)
        y0 = rnd_c.choice([-12, -4])
        for d in range(rnd_c.randint(2, 6)):
            px_, py_ = r(x, y0 + d)
            if t.nom(int(px_), int(py_)) in ('coque', 'coque_claire'):
                t.point(int(px_), int(py_), 'rouille' if d < 2 else 'coque_ombre')
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
    # Rochers au premier plan (roche de RF), l'écume à leur pied
    rampe = ['noir', 'roc_ombre', 'roc', 'roc_clair']
    for k, (x, y, rx, ry) in enumerate([(16, 106, 26, 16), (226, 104, 28, 18), (190, 110, 14, 7)]):
        m = bloc_rf(t, x, y, rx, ry, rampe, 60 + k)
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
    # La montagne : une grande crête peinte avec la roche de RF, recolorée en gris-vert, le versant droit à l'ombre ;
    # des montagnes plus lointaines, plus pâles, de chaque côté
    rampe_m = ['mont_noir', 'mont_ombre', 'mont', 'mont_clair']
    massif_rf(t, [(0, 66), (0, 42), (30, 36), (60, 50), (60, 66)], ['mont', 'mont', 'mont_clair', 'brume'], None, 3,
              ombre=0)
    massif_rf(t, [(180, 66), (196, 40), (220, 34), (240, 38), (240, 66)], ['mont', 'mont', 'mont_clair', 'brume'],
              None, 4, 30, 8, ombre=0)
    crete = [(30, 66), (58, 50), (76, 40), (90, 38), (104, 26), (116, 24), (130, 10), (142, 6), (150, 3), (160, 9),
             (170, 12), (182, 22), (196, 26), (210, 38), (226, 46), (226, 66)]
    massif_rf(t, crete, rampe_m, None, 5, 17, 0, ombre=0.45)
    for (ax, ay), (bx, by) in zip(crete[1:9], crete[2:10]):  # le fil de la crête, au soleil
        t.ligne([(ax, ay), (bx, by)], 'blanc' if by < ay else 'mont_clair')
    for x in range(W):  # le pied des montagnes dans la brume
        for y in range(54, 68):
            if t.nom(x, y).startswith('mont') and (y > 58 or (x + y) & 1):
                t.point(x, y, 'brume' if y < 62 else 'blanc')
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
    fougere_rf(t, -10, 78, ['herbe_ombre', 'herbe', 'herbe_claire'])
    fougere_rf(t, 200, 78, ['herbe_ombre', 'herbe', 'herbe_claire'], miroir=True)
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
    # Les faisceaux des néons, comme les rayons de lumière de la Centrale de RF : un ton plus clair, en damier
    eclaircir = {'mur_ombre': 'mur', 'mur': 'mur_clair', 'sol_ombre': 'sol', 'sol': 'sol_clair', 'noir': 'mur_ombre'}
    for x0 in (60, 150):
        faisceau = masque_poly([(x0, 8), (x0 + 30, 8), (x0 + 58, 112), (x0 - 24, 112)])
        for x, y in pixels(faisceau):
            if (x + y) % 2 == 0 and t.nom(x, y) in eclaircir:
                t.point(x, y, eclaircir[t.nom(x, y)])
    # Le générateur : des bobines empilées, cerclées de métal, éclairées à gauche, voyants verts et sphère au sommet
    cx = 120
    rampe_g = ['gen_noir', 'gen_ombre', 'gen', 'gen_clair']

    def anneau(y0, y1, demi):
        for y in range(y0, y1):
            for x in range(cx - demi, cx + demi + 1):
                v = (x - cx + demi) / (2 * demi)
                l = 0.9 - 0.9 * max(0.0, v) ** 1.4
                if y - y0 < 2:
                    l += 0.25
                if (x - cx) % 5 == 0 and y - y0 >= 3:
                    l -= 0.28  # les spires de la bobine
                aplat(t, x, y, rampe_g, l, 0.06)
        t.ellipse((cx - demi - 2, y1 - 3, cx + demi + 2, y1 + 3), 'mur_ombre')  # cerclage de métal en bas
        t.ellipse((cx - demi - 2, y1 - 4, cx + demi + 2, y1 + 1), 'mur_clair')
        t.ellipse((cx - demi, y0 - 3, cx + demi, y0 + 3), 'gen_clair')
        t.ellipse((cx - demi + 3, y0 - 2, cx + demi - 3, y0 + 2), 'gen')
    t.ellipse((cx - 44, 80, cx + 44, 98), 'sol_ombre')  # socle
    t.ellipse((cx - 42, 78, cx + 42, 94), 'mur_ombre')
    anneau(58, 86, 36)
    anneau(38, 56, 28)
    anneau(22, 36, 20)
    t.rect(cx - 2, 8, cx + 2, 22, 'mur_ombre')  # la tige et la sphère du sommet
    t.rect(cx - 2, 8, cx - 1, 22, 'mur_clair')
    t.ellipse((cx - 7, 2, cx + 7, 14), 'gen_ombre')
    t.ellipse((cx - 6, 3, cx + 5, 12), 'gen_clair')
    t.ellipse((cx - 4, 4, cx, 8), 'lumiere')
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
        'sm': (64, 96, 152), 'sm_clair': (128, 164, 212), 'lampe': (248, 232, 160), 'rouge': (208, 72, 72),
    })
    t.rect(0, 0, W, H, 'roc_noir')
    # L'ouverture du fond, sombre, et la voûte de la grotte peinte avec la roche de RF (recolorée en gris-bleu)
    bandes_v(t, 50, 14, 190, 96, ['roc_noir', 'eau_fonce'], rangs=3)
    voute = masque()
    d = ImageDraw.Draw(voute)
    d.rectangle((0, 0, W, H), fill=255)
    d.polygon(organique(ellipse_pts(120, 55, 70, 41), 3, 77), fill=0)
    d.rectangle((30, 62, 210, H), fill=0)
    texturer(t, voute, ROCHE_RF[0], ROCHE_RF[1], ['roc_noir', 'roc_ombre', 'roc', 'roc_clair'], 4, 9)
    for x, y in pixels(voute):  # le bord de l'ouverture, un ton plus sombre : la profondeur
        proche = any(not dedans(voute, x + dx, y + dy) for dx, dy in ((4, 0), (-4, 0), (0, 4), (0, -4)))
        if proche and t.nom(x, y) != 'roc_noir':
            t.point(x, y, {'roc_clair': 'roc', 'roc': 'roc_ombre', 'roc_ombre': 'roc_noir'}[t.nom(x, y)])
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
    # Le fond de la galerie et ses parois, peints avec la roche de RF recolorée en rouge sombre (plus sombre au fond)
    texturer(t, masque_poly([(0, 0), (W, 0), (W, 70), (0, 70)]), ROCHE_RF[0], ROCHE_RF[1],
             ['noir', 'roc_noir', 'roc_ombre', 'roc'], 21, 6)
    for k, pts in enumerate([[(0, 0), (70, 0), (52, 30), (40, 70), (24, 100), (0, 112)],
                             [(240, 0), (172, 0), (190, 32), (200, 70), (216, 100), (240, 112)]]):
        massif_rf(t, pts, ['roc_noir', 'roc_ombre', 'roc', 'roc_clair'], None, 90 + k, 40 * k, 7, ombre=0.4 if k else 0)
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
    # Vapeur qui monte des coulées : les jets de vapeur peints du Mont Braise de RF
    coller_rf(t, VAPEUR_RF[0], VAPEUR_RF[1], 6, 14, ['cendre', 'vapeur'], est_nuage)
    coller_rf(t, VAPEUR_RF[0], VAPEUR_RF[1], 184, 10, ['cendre', 'vapeur'], est_nuage, miroir=True)
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
        'ciel_haut': (176, 204, 236), 'ciel': (214, 226, 240), 'voile': (244, 236, 212), 'loin': (220, 198, 160),
        'sable_clair': (248, 232, 168), 'sable': (236, 208, 136), 'sable_ombre': (208, 172, 104),
        'dessus': (226, 168, 124), 'cactus': (128, 164, 96), 'cactus_ombre': (88, 124, 76),
    }, **REGI_ROCHE))
    ciel_rf(t, 50, ['ciel_haut', 'ciel', 'voile'], [(0, 140, 0, False), (2, 20, 6, True)], 'voile', 'ciel')
    # Les collines lointaines de RF, devenues des mesas de sable noyées dans la brume du désert
    coller_rf(t, COLLINES_RF[0], COLLINES_RF[1], 0, 24, ['loin', 'voile'], loin)
    coller_rf(t, COLLINES_RF[0], COLLINES_RF[1], 120, 22, ['loin', 'voile'], loin, miroir=True)
    bandes_v(t, 0, 48, W, H, ['sable_clair', 'sable', 'sable_ombre'], rangs=2)
    for y in range(54, H, 6):  # rides du sable
        for x in range(0, W, 2):
            if math.sin(x / 9 + y) > 0.55:
                t.point(x, y + int(2 * math.sin(x / 13)), 'sable_ombre' if y > 70 else 'sable')
    butte_rf(t, 120, 96, REGI_RAMPE, 'dessus', 'porte', 110)
    for k, (x, y, rx, ry) in enumerate([(26, 70, 9, 6), (214, 66, 8, 6), (90, 56, 5, 3), (160, 56, 5, 3),
                                        (64, 100, 6, 4), (178, 98, 6, 4), (20, 108, 20, 14), (222, 110, 22, 15)]):
        bloc_rf(t, x, y, rx, ry, REGI_RAMPE, 114 + k)
    for x, y0, h in [(44, 94, 14), (196, 90, 12)]:  # cactus
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
        'ciel_haut': (152, 196, 240), 'ciel': (200, 224, 248), 'blanc': (248, 248, 248), 'nuage_ombre': (214, 224, 244),
        'mer_fonce': (80, 136, 208), 'mer': (120, 172, 232), 'mer_clair': (176, 212, 244),
        'sable_clair': (248, 236, 196), 'sable': (230, 210, 158), 'dessus': (224, 170, 128),
    }, **REGI_ROCHE))
    ciel_rf(t, 46, ['ciel_haut', 'ciel', 'blanc'], [(0, 150, -2, False), (0, 6, 4, True), (2, 76, -6, False)])
    mer_rf(t, 44, H, ['mer_fonce', 'mer', 'mer_clair', 'blanc'], 'blanc')
    for x, y in [(70, 14), (84, 20), (128, 8)]:  # Goélise au loin
        t.ligne([(x - 3, y - 2), (x, y), (x + 3, y - 2)], 'roc_ombre')
    # L'îlot de sable aux bords irréguliers, son écume
    ile = organique([(4, 112), (236, 112), (214, 64), (26, 64)], 4, 9, pas=8)
    t.poly([(x + (-3 if x < 120 else 3), y - 2) for x, y in ile], 'blanc')
    m = masque_poly(ile)
    bandes_v(t, 0, 62, W, H, ['sable_clair', 'sable'], rangs=2, masque=m)
    for x, y in pixels(m):  # le sable mouillé du bord, un ton plus foncé
        if not dedans(m, x - 4, y) or not dedans(m, x + 4, y):
            t.point(x, y, 'sable' if (x + y) & 1 else 'sable_clair')
    butte_rf(t, 120, 98, REGI_RAMPE, 'dessus', 'porte', 120)
    for k, (x, y, rx, ry) in enumerate([(52, 74, 7, 5), (188, 72, 8, 5), (22, 106, 16, 11), (222, 108, 18, 12),
                                        (72, 106, 7, 5), (166, 106, 8, 5)]):
        bloc_rf(t, x, y, rx, ry, REGI_RAMPE, 30 + k)
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
    ciel_rf(t, 40, ['ciel', 'blanc'], [(0, 10, -6, False), (0, 150, -10, True)], 'blanc', 'ciel')
    # La forêt de sapins de RF (Route Victoire), recolorée en vert sombre de jour de pluie
    rampe_sapins = ['arbre_fonce', 'arbre', 'herbe', 'herbe_claire']
    for k, x in enumerate((-10, 74, 158)):
        coller_rf(t, SAPINS_RF[0], SAPINS_RF[1], x, -16, rampe_sapins, lambda c: c[1] > c[0] + 8 and c[1] >= c[2],
                  miroir=bool(k % 2))
    bandes_v(t, 0, 52, W, H, ['herbe_claire', 'herbe', 'herbe_ombre'], rangs=2)
    for box in [(14, 92, 70, 108), (168, 96, 236, 114), (100, 104, 150, 118)]:  # mares
        t.ellipse(box, 'herbe_ombre')
        t.ellipse((box[0] + 2, box[1] + 1, box[2] - 2, box[3] - 1), 'eau')
        t.ligne([(box[0] + 8, box[1] + 4), (box[0] + 18, box[1] + 4)], 'blanc')
    butte_rf(t, 120, 94, REGI_RAMPE, 'dessus', 'porte', 130)
    for xx in range(46, 194, 5):  # herbe sur le dessus de la butte
        t.point(xx, 69 if 70 < xx < 170 else 70, 'herbe')
    for k, (x, y, rx, ry) in enumerate([(24, 66, 8, 6), (216, 64, 9, 6), (86, 98, 6, 4), (160, 98, 7, 4)]):
        bloc_rf(t, x, y, rx, ry, REGI_RAMPE, 134 + k)
    herbe(t, 0, W, H + 2, 9, ['herbe_ombre', 'herbe', 'herbe_claire'], 51, 0.9)
    fougere_rf(t, -6, 80, ['herbe_ombre', 'herbe', 'herbe_claire'])
    fougere_rf(t, 196, 80, ['herbe_ombre', 'herbe', 'herbe_claire'], miroir=True)
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
