#!/usr/bin/env python3
"""Fenêtres éclairées du cycle jour/nuit (day_night.c) : écrit src/data/day_night_lights.h.

La nuit, les vitres des bâtiments extérieurs deviennent jaunes au lieu d'être assombries. Pour chaque tileset, le
fichier donne les pixels allumés de chaque tile et les couleurs allumées de chaque palette ; le rendu des BG allume
un pixel quand les deux le disent. Les vitres sont suivies sur les cartes (light_tiles) ; EXCLUDE, UNLIT_METATILES et
LIT_METATILES corrigent à la main ce que les règles ne peuvent pas trancher, vérifié sur les captures du scénario
day_night_towns (option marquage).
Usage : python tools/day_night_lights.py
"""
import glob, json, os, re, struct
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUTDOOR = {'MAP_TYPE_ROUTE', 'MAP_TYPE_TOWN', 'MAP_TYPE_CITY', 'MAP_TYPE_OCEAN_ROUTE'}
NUM_PALS_IN_PRIMARY, NUM_PALS_TOTAL = 6, 13
NUM_TILES_IN_PRIMARY = NUM_METATILES_IN_PRIMARY = 512
MIN_LIGHT = 6   # pixels d'une vitre au moins
WATER = ('WATER', 'POND', 'OCEAN', 'CURRENT', 'PUDDLE', 'SEAWEED', 'HOT_SPRINGS')

# (tileset, palette, couleur) : pas des vitres / vitres non repérées ; None = toute la palette / tout le tileset
EXCLUDE = {
    ('gTileset_General', 4, 7),          # toit de la Boutique de Hoenn
    ('gTileset_Pacifidlog', 10, None),   # eau autour des rondins
    ('gTileset_Cave', None, None),       # pas de bâtiments
    ('gTileset_Facility', None, None),   # Mont Mémoria : des tombes, pas de bâtiments
    ('gTileset_KantoViridianCity', 10, 3), ('gTileset_KantoViridianCity', 10, 4),   # fleurs des jardinières
    ('gTileset_KantoCeruleanCity', 12, None), ('gTileset_KantoCeruleanCity', 10, None),   # toits, plinthes
    *(('gTileset_Lilycove', 8, i) for i in (1, 2, 3, 4, 8, 11)),   # murs et toits bleus (vitres : 10)
    ('gTileset_KantoSeviiIslands67', 9, 8),   # façade de la Tour des Dresseurs
    ('gTileset_KantoVermilionCity', 8, 13), ('gTileset_KantoVermilionCity', 10, 14),   # plinthes
    ('gTileset_KantoVermilionCity', 9, 8), ('gTileset_KantoVermilionCity', 9, 9),       # portes bleues
}
INCLUDE = set()
# Métatiles dont les pixels ne s'allument jamais, même avec une couleur de vitre (le rendu teste chaque pixel de
# tile, voir gDayNightRender) : pour les couleurs partagées entre fenêtres et autre chose ; (métatile, palette,
# couleur) : seulement cette couleur dans ce métatile
UNLIT_METATILES = {
    'gTileset_KantoGeneral': [40, 41, 42, 43, 48, 49, 50, 51, 56, 57, 58, 59,    # verrière des Boutiques
                              44, 45, 46, 47, 52, 53, 54, 55],                   # toit bleu (portails des routes)
    # numéros dans un tileset secondaire : métatile de la carte - 512
    'gTileset_Lavaridge': [260, 341],    # machine à météorite du Mont Chimnée
    'gTileset_Fallarbor': [296, 297],    # machine de Cosmo
    'gTileset_Mossdeep': [411, 412],     # anneau de la fusée
    'gTileset_Lilycove': [224, 225, 226, 227, 228],   # bandes bleues de la façade du Hall des Concours
    'gTileset_KantoCeruleanCity': [233],   # vélos devant la boutique
    'gTileset_Mauville': [19, 21, 23],    # pétales bleus des fleurs
    'gTileset_Rustboro': [120, 121, 122, 123, 124],   # auvent rayé (Route 104)
    'gTileset_KantoSaffronCity': [280, 282, 284, 285, 286, 288, 290, 293, 294, 296, 297, 298, 301, 302,
                                  324, 325, 326, 327],   # rambardes
    'gTileset_Slateport': [7, 13, 15, 37, 45, 55, 248, 250,   # tentes du marché
                           # mur lavande du Fan Club, couleur des dégradés de vitre (hublots : 9, 10)
                           *((m, 1, i) for m in (104, 105, 173, 175, 181, 182, 183, 189, 190, 191, 197, 215)
                             for i in (2, 3, 4))],
    # Zone de Combat : logo des façades et des arches, drapeaux, sculptures Poké Ball, colonnes
    'gTileset_BattleFrontierOutsideEast': [366, 373, 374, 375, 414, 415, 491, 499, 502, 503, 245, 282],
    'gTileset_BattleFrontierOutsideWest': [355, 356, 362, 363, 364, 414, 454, 462, 502, 30, 38,
                                           11, 12, 13, 19, 21, 22, 23, 61],
    'gTileset_KantoCeladonCity': [208, 209, 210, 211, 212, 213, 215],   # fontaine
}
# Métatiles dont tous les pixels couleur de vitre (dégradé pâle compris) s'allument, même en petits bouts isolés ;
# (métatile, x0, y0, x1, y1) : seulement dans ce rectangle de pixels
LIT_METATILES = {
    'gTileset_General': [475,            # porte du Hall des Concours : vitre entre les traits de l'emblème
                         11, 19],        # fenêtre à carreaux des maisons : dégradé lavande sans vitre franche
    'gTileset_Mauville': [395, 396, (403, 0, 0, 15, 3), (404, 0, 0, 15, 3)],   # fenêtres de Vergazon : carreau bas
}


def excluded(key):
    tileset, slot, i = key
    return key in EXCLUDE or (tileset, slot, None) in EXCLUDE or (tileset, None, None) in EXCLUDE


def glass(c):
    r, g, b = c
    return b >= 190 and b >= g and b - r >= 50 and g > r and r >= 80


def palette_files():
    files = {}
    for h in glob.glob(os.path.join(ROOT, 'src/data/tilesets/*graphics.h')) + [os.path.join(ROOT, 'src/graphics.c')]:
        text = open(h, encoding='utf-8').read()
        for name, body in re.findall(r'gTilesetPalettes_(\w+)\[\]\[16\] =\s*\{(.*?)\};', text, re.S):
            files['gTileset_' + name] = re.findall(r'"([^"]+\.pal)"', body)
    return files


def tileset_dir(pals, tileset):
    return os.path.dirname(os.path.dirname(pals[tileset][0]))


def behaviors(words):
    """Comportements de métatile dont le nom contient un des mots (sauf les ponts)."""
    text = open(os.path.join(ROOT, 'include/constants/metatile_behaviors.h'), encoding='utf-8').read()
    names = re.findall(r'^\s*(MB_\w+)', text.split('enum {', 1)[1], re.M)
    return {i for i, n in enumerate(names) if any(w in n for w in words) and 'BRIDGE' not in n}


def tile_indices(path):
    """Indices de couleur de chaque tile 8x8 de tiles.png."""
    im = Image.open(os.path.join(ROOT, path))
    w, h = im.size
    px = im.load()
    return [{px[tx * 8 + x, ty * 8 + y] & 15 for y in range(8) for x in range(8)}
            for ty in range(h // 8) for tx in range(w // 8)]


def water_colors(pals, pairs):
    """(tileset propriétaire de la palette, palette, couleur) dessinées par un métatile d'eau."""
    water = behaviors(WATER)
    tiles, found = {}, set()
    for primary, secondary in pairs:
        for ts in (primary, secondary):
            if ts not in tiles:
                tiles[ts] = tile_indices(tileset_dir(pals, ts) + '/tiles.png')
        for ts in (primary, secondary):
            d = os.path.join(ROOT, tileset_dir(pals, ts))
            meta = open(os.path.join(d, 'metatiles.bin'), 'rb').read()
            attrs = open(os.path.join(d, 'metatile_attributes.bin'), 'rb').read()
            for m in range(len(attrs) // 2):
                if struct.unpack_from('<H', attrs, m * 2)[0] & 0xFF not in water:
                    continue
                for k in range(8):
                    e = struct.unpack_from('<H', meta, (m * 8 + k) * 2)[0]
                    tile, pal = e & 0x3FF, e >> 12
                    owner_tiles = tiles[primary] if tile < NUM_TILES_IN_PRIMARY else tiles[secondary]
                    tile %= NUM_TILES_IN_PRIMARY
                    if pal >= NUM_PALS_TOTAL or tile >= len(owner_tiles):
                        continue
                    owner = primary if pal < NUM_PALS_IN_PRIMARY else secondary
                    for i in owner_tiles[tile]:
                        found.add((owner, pal, i))
    return found


def read_pal(path):
    lines = open(os.path.join(ROOT, path)).read().split('\n')[3:19]
    return [tuple(map(int, l.split())) for l in lines if l.strip()]


def outdoor_layouts():
    layouts = {l['id']: l for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts'] if 'id' in l}
    used = set()
    for f in glob.glob(os.path.join(ROOT, 'data/maps/*/map.json')):
        m = json.load(open(f, encoding='utf-8'))
        if m.get('map_type') in OUTDOOR and m.get('layout') in layouts:
            used.add(m['layout'])
    return [layouts[l] for l in sorted(used)]


def is_secondary(tileset):
    for h in glob.glob(os.path.join(ROOT, 'src/data/tilesets/*headers.h')):
        m = re.search(r'struct Tileset ' + tileset + r' =\s*\{.*?isSecondary = (\w+)', open(h, encoding='utf-8').read(), re.S)
        if m:
            return m.group(1) == 'TRUE'
    raise KeyError(tileset)


def family(c):
    """Couleur du dégradé d'une vitre : bleutée."""
    r, g, b = c
    return b >= g and b - r >= 45 and b >= 150


def pale(c):
    """Couleur pâle, jusqu'au blanc : bas de dégradé ou reflet d'une vitre, mais aussi murs clairs."""
    r, g, b = c
    return b >= g and b >= r and r >= 150 and not family(c)


def dark(c):
    """Cadre d'une vitre."""
    return max(c) < 140


def metatile_layers(meta, m):
    """Les deux couches (bas, haut) d'un métatile : grilles 16x16 de (tile VRAM, palette, indice) ou None."""
    for layer in (0, 1):
        yield [(k, struct.unpack_from('<H', meta, (m * 8 + layer * 4 + k) * 2)[0]) for k in range(4)]


class MetatilePixels(dict):
    """Pixels des métatiles d'une paire de tilesets, décodés à la demande, par couche :
    {(tileset, métatile): [{(x, y): pixel}] * 2}, où pixel = (tileset, tile local, tileset de la palette, palette,
    indice, x et y dans le tile)."""
    def __init__(self, pals, primary, secondary, tiles):
        super().__init__()
        self.primary, self.secondary, self.tiles = primary, secondary, tiles
        self.meta = {ts: open(os.path.join(ROOT, tileset_dir(pals, ts), 'metatiles.bin'), 'rb').read() for ts in (primary, secondary)}

    def keys_all(self):
        return [(ts, m) for ts in (self.primary, self.secondary) for m in range(len(self.meta[ts]) // 16)]

    def __missing__(self, key):
        owner, m = key
        layers = []
        for layer in metatile_layers(self.meta[owner], m):
            grid = {}
            for k, e in layer:
                tile, hflip, vflip, pal = e & 0x3FF, e >> 10 & 1, e >> 11 & 1, e >> 12
                ts = self.primary if tile < NUM_TILES_IN_PRIMARY else self.secondary
                px, w, count = self.tiles[ts]
                local = tile % NUM_TILES_IN_PRIMARY
                if pal >= NUM_PALS_TOTAL or local >= count:
                    continue
                pal_owner = self.primary if pal < NUM_PALS_IN_PRIMARY else self.secondary
                for y in range(8):
                    for x in range(8):
                        i = px[local % w * 8 + x, local // w * 8 + y] & 15
                        if i:
                            pos = (k % 2 * 8 + (7 - x if hflip else x), k // 2 * 8 + (7 - y if vflip else y))
                            grid[pos] = (ts, local, pal_owner, pal, i, x, y)
            layers.append(grid)
        self[key] = layers
        return layers

    def may_light(self, key, seeds, colors):
        """Le métatile a-t-il une couleur de vitre ? (sans le décoder)"""
        owner, m = key
        for k in range(8):
            e = struct.unpack_from('<H', self.meta[owner], (m * 8 + k) * 2)[0]
            tile, pal = e & 0x3FF, e >> 12
            if pal < NUM_PALS_TOTAL:
                pal_owner = self.primary if pal < NUM_PALS_IN_PRIMARY else self.secondary
                ts = self.primary if tile < NUM_TILES_IN_PRIMARY else self.secondary
                if seeds.get((pal_owner, pal), 0) & colors[ts].get(tile % NUM_TILES_IN_PRIMARY, 0):
                    return True
        return False


def light_tiles(pals, layouts, seeds, report=None):
    """Pixels allumés, suivis sur chaque carte extérieure (une vitre continue d'un métatile à l'autre) : les couleurs
    de vitre (seeds), puis de proche en proche les couleurs de leur dégradé (family) qui les touchent, puis les zones
    pâles (pale : reflet, bas du dégradé) enfermées entre la vitre et son cadre sombre (pas un mur clair). Une tache de
    moins de MIN_LIGHT pixels n'est pas une vitre (fleur bleue). Un métatile qu'aucune carte ne pose est regardé
    seul. Le rendu teste le pixel de chaque tile : un pixel allumé quelque part l'est partout où son tile est posé.
    Rend {(tileset, tile local): 8 lignes de bits} et {(tileset, palette): masque des couleurs}."""
    tiles, colors, cache = {}, {}, {}
    lit = set()     # (tileset, métatile, couche, x, y)
    placed = set()

    def is_seed(p):
        return p and seeds.get((p[2], p[3]), 0) >> p[4] & 1

    def enclosed(group, at, seen):
        """Zones pâles qui touchent la vitre, bordées au moins pour moitié par la vitre ou son cadre sombre (pas un mur
        clair, que la vitre ne fait que toucher), et pas plus de trois fois la vitre (meneaux entre les carreaux)."""
        inside, found, tried = set(group), [], set()
        def color(q):
            p, cell = at(*q)
            return p and not excluded((p[2], p[3], p[4])) and cell[2][p[3]][p[4]]
        for n, X, Y in group:
            for q in ((n, X + 1, Y), (n, X - 1, Y), (n, X, Y + 1), (n, X, Y - 1)):
                if q in seen or q in tried or not (color(q) and pale(color(q))):
                    continue
                zone, good, bad = [q], 0, 0
                tried.add(q)
                for n_, X_, Y_ in zone:
                    if len(zone) > 3 * len(group):
                        break
                    for r in ((n_, X_ + 1, Y_), (n_, X_ - 1, Y_), (n_, X_, Y_ + 1), (n_, X_, Y_ - 1)):
                        if r in inside:
                            good += 1
                        elif r in tried:
                            continue
                        elif (c := color(r)) and pale(c) and r not in seen:
                            tried.add(r)
                            zone.append(r)
                        elif (c and dark(c)) or is_seed(at(*r)[0]):
                            good += 1
                        else:
                            bad += 1
                if good >= bad and len(zone) <= 3 * len(group):
                    seen.update(zone)
                    found += zone
        return found

    def framed(group, at):
        """Si la vitre et ce qui l'entoure sont fermés par son cadre sombre (pas un mur ouvert), les pixels couleur de
        vitre ou bleutés de cette zone, même exclus ailleurs (bleu du mur en bas d'un carreau)."""
        zone, inside = list(group), set(group)
        for n, X, Y in zone:
            for q in ((n, X + 1, Y), (n, X - 1, Y), (n, X, Y + 1), (n, X, Y - 1)):
                if q in inside:
                    continue
                p, cell = at(*q)
                if not p:
                    return []
                if dark(cell[2][p[3]][p[4]]):
                    continue
                if len(zone) > 3 * len(group) + 32:
                    return []
                inside.add(q)
                zone.append(q)
        found = []
        for q in zone[len(group):]:
            p, cell = at(*q)
            c = cell[2][p[3]][p[4]]
            if is_seed(p) or family(c):
                found.append(q)
        return found

    def spread(cells, keep_edges):
        """cells : {(mx, my): (clé du métatile, pixels, couleurs, pixels de vitre)} ; allume les taches de vitre."""
        def at(n, X, Y):
            cell = cells.get((X // 16, Y // 16))
            return cell and cell[1][cell[0]][n].get((X % 16, Y % 16)), cell
        done_pixels = set()     # pixels déjà allumés : départs inutiles
        for (mx, my), (key, layers, cols, starts) in cells.items():
            for n, x, y in starts:
                start = (n, mx * 16 + x, my * 16 + y)
                if start in done_pixels:
                    continue
                # seen est propre à cette tache : une tache refusée (trop petite) ne cache rien aux suivantes
                group, seen, done = [start], {start}, 0
                while done < len(group):
                    for n_, X, Y in group[done:]:
                        done += 1
                        for q in ((n_, X + 1, Y), (n_, X - 1, Y), (n_, X, Y + 1), (n_, X, Y - 1)):
                            if q in seen:
                                continue
                            p, cell = at(*q)
                            if is_seed(p) or (p and family(cell[2][p[3]][p[4]]) and not excluded((p[2], p[3], p[4]))):
                                seen.add(q)
                                group.append(q)
                    group += enclosed(group, at, seen)
                if len(group) < MIN_LIGHT and not (keep_edges and any(not (0 < X % 16 < 15 and 0 < Y % 16 < 15) for _, X, Y in group)):
                    if report is not None:
                        report.append((key, len(group)))
                    continue
                group += framed(group, at)
                done_pixels.update(group)
                for n_, X, Y in group:
                    k = cells[(X // 16, Y // 16)][0]
                    lit.add((k[0], k[1], n_, X % 16, Y % 16))

    def pair_data(primary, secondary):
        if (primary, secondary) not in cache:
            for ts in (primary, secondary):
                if ts not in tiles:
                    im = Image.open(os.path.join(ROOT, tileset_dir(pals, ts) + '/tiles.png'))
                    tiles[ts] = (im.load(), im.size[0] // 8, im.size[0] // 8 * (im.size[1] // 8))
                    colors[ts] = {t: sum(1 << i for i in c) for t, c in enumerate(tile_indices(tileset_dir(pals, ts) + '/tiles.png'))}
            cols = {s: read_pal(pals[primary if s < NUM_PALS_IN_PRIMARY else secondary][s]) for s in range(NUM_PALS_TOTAL)}
            pixels = MetatilePixels(pals, primary, secondary, tiles)
            starts = {}
            for key in pixels.keys_all():
                if pixels.may_light(key, seeds, colors):
                    starts[key] = [(n, x, y) for n, layer in enumerate(pixels[key]) for (x, y), p in layer.items()
                                   if seeds.get((p[2], p[3]), 0) >> p[4] & 1]
            cache[(primary, secondary)] = (pixels, cols, starts)
        return cache[(primary, secondary)]

    unlit = lambda key: key[1] in UNLIT_METATILES.get(key[0], ())
    unlit_colors = {}   # (métatile, palette, couleur) : cette couleur seulement
    for ts, entries in UNLIT_METATILES.items():
        for entry in entries:
            if isinstance(entry, tuple):
                unlit_colors.setdefault((ts, entry[0]), set()).add(entry[1:])
    water, doors = behaviors(WATER), behaviors(('DOOR',))
    attrs = {}
    def behavior(key):
        if key[0] not in attrs:
            attrs[key[0]] = open(os.path.join(ROOT, tileset_dir(pals, key[0]), 'metatile_attributes.bin'), 'rb').read()
        return struct.unpack_from('<H', attrs[key[0]], key[1] * 2)[0] & 0xFF
    for l in layouts:
        primary, secondary = l['primary_tileset'], l['secondary_tileset']
        pixels, cols, starts = pair_data(primary, secondary)
        blocks = open(os.path.join(ROOT, l['blockdata_filepath']), 'rb').read()
        cells = {}
        width, count = l['width'], len(blocks) // 2
        block = lambda c: struct.unpack_from('<H', blocks, c * 2)[0]
        for c in range(count):
            m = block(c) & 0x3FF
            key = (primary, m) if m < NUM_METATILES_IN_PRIMARY else (secondary, m - NUM_METATILES_IN_PRIMARY)
            placed.add(key)
            # Seulement les bâtiments : cases bloquantes, portes, ou praticables juste au-dessus d'un mur (haut d'un
            # toit) ; pas l'eau (ses bleus touchent les vitres des bords de mer), ni les chemins, l'herbe…
            wall = block(c) & 0xC00 or behavior(key) in doors or (c + width < count and block(c + width) & 0xC00)
            if not unlit(key) and wall and behavior(key) not in water:
                cells[(c % width, c // width)] = (key, pixels, cols, starts.get(key, ()))
        spread(cells, False)
    for pair in sorted({(l['primary_tileset'], l['secondary_tileset']) for l in layouts}):
        pixels, cols, starts = pair_data(*pair)
        for key, start in list(starts.items()):
            if key not in placed and not unlit(key) and start:
                spread({(0, 0): (key, pixels, cols, start)}, True)
        for ts in pair:
            for entry in LIT_METATILES.get(ts, []):
                m, x0, y0, x1, y1 = entry if isinstance(entry, tuple) else (entry, 0, 0, 15, 15)
                for n, layer in enumerate(pixels[(ts, m)]):
                    for (x, y), p in layer.items():
                        if not (x0 <= x <= x1 and y0 <= y <= y1):
                            continue
                        c = cols[p[3]][p[4]]
                        if is_seed(p) or ((family(c) or pale(c)) and not excluded((p[2], p[3], p[4]))):
                            lit.add((ts, m, n, x, y))
    # Pixels des métatiles éteints (UNLIT_METATILES) et de l'eau : éteints même si une vitre partage leur tile
    unlit_pixels = set()
    for pixels, _, _ in cache.values():
        for key in pixels.keys_all():
            if unlit(key) or behavior(key) in water:
                unlit_pixels.update((p[0], p[1], p[5], p[6]) for layer in pixels[key] for p in layer.values())
            elif key in unlit_colors:
                unlit_pixels.update((p[0], p[1], p[5], p[6]) for layer in pixels[key] for p in layer.values()
                                    if (p[3], p[4]) in unlit_colors[key])
    tile_masks, pal_masks = {}, {}
    for pixels, _, _ in cache.values():
        for key, layers in list(pixels.items()):
            for n, layer in enumerate(layers):
                for (x, y), p in layer.items():
                    if (key[0], key[1], n, x, y) in lit and (p[0], p[1], p[5], p[6]) not in unlit_pixels:
                        tile_masks.setdefault((p[0], p[1]), [0] * 8)[p[6]] |= 1 << p[5]
                        pal_masks[(p[2], p[3])] = pal_masks.get((p[2], p[3]), 0) | 1 << p[4]
    return tile_masks, pal_masks


def glass_seeds(pals, pairs, water):
    seeds = {}
    for tileset in {p for p, _ in pairs} | {s for _, s in pairs}:
        slots = range(NUM_PALS_IN_PRIMARY, NUM_PALS_TOTAL) if is_secondary(tileset) else range(NUM_PALS_IN_PRIMARY)
        for slot in slots:
            for i, c in enumerate(read_pal(pals[tileset][slot])):
                key = (tileset, slot, i)
                if i and ((glass(c) and key not in water and not excluded(key)) or key in INCLUDE):
                    seeds[(tileset, slot)] = seeds.get((tileset, slot), 0) | 1 << i
    return seeds


def compute(report=None):
    pals = palette_files()
    layouts = outdoor_layouts()
    pairs = {(l['primary_tileset'], l['secondary_tileset']) for l in layouts}
    water = water_colors(pals, pairs)
    return pals, pairs, light_tiles(pals, layouts, glass_seeds(pals, pairs, water), report)


def main():
    _, _, (tile_masks, pal_masks) = compute()
    # Un tileset peut n'avoir que des pixels (vitres dessinées avec les palettes de l'autre) ou que des couleurs
    entries = sorted({ts for ts, _ in pal_masks} | {ts for (ts, _), rows in tile_masks.items() if any(rows)})
    out = ['// Généré par tools/day_night_lights.py : couleurs de vitre éclairées la nuit (par palette) et leurs pixels',
           '// (par tile, une ligne de 8 bits par rangée)']
    out += [f'extern const struct Tileset {t};' for t in entries]
    for tileset in entries:
        lit = sorted(t for (ts, t), rows in tile_masks.items() if ts == tileset and any(rows))
        out += ['', f'static const u8 sTileLights_{tileset[9:]}[NUM_TILES_IN_PRIMARY][8] =', '{']
        out += [f'    [{t}] = {{ ' + ', '.join(f'0x{b:02X}' for b in tile_masks[(tileset, t)]) + ' },' for t in lit]
        out += [] if lit else ['    { 0 },']
        out += ['};']
    out += ['', 'static const struct DayNightLights sDayNightLights[] =', '{']
    for tileset in entries:
        body = ', '.join(f'[{s}] = 0x{m:04X}' for (t, s), m in sorted(pal_masks.items()) if t == tileset)
        out.append(f'    {{ &{tileset}, {{ {body} }}, sTileLights_{tileset[9:]} }},')
    out += ['};', '']
    open(os.path.join(ROOT, 'src/data/day_night_lights.h'), 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
    print(f'src/data/day_night_lights.h : {len(entries)} tilesets')


if __name__ == '__main__':
    main()
