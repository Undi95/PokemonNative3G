#!/usr/bin/env python3
"""Fenêtres éclairées du cycle jour/nuit (day_night.c) : écrit src/data/day_night_lights.h.

Pour chaque tileset des cartes extérieures, les couleurs de vitre (bleus clairs) de ses palettes sont des
« lumières » : la nuit, elles deviennent jaunes au lieu d'être assombries. Les couleurs sont repérées
automatiquement (glass) ; EXCLUDE retire celles qui ne sont pas des vitres (eau, ciel…), INCLUDE en ajoute,
vérifié sur les captures du scénario day_night_towns (option marquage).
Usage : python tools/day_night_lights.py
"""
import glob, json, os, re, struct
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUTDOOR = {'MAP_TYPE_ROUTE', 'MAP_TYPE_TOWN', 'MAP_TYPE_CITY', 'MAP_TYPE_OCEAN_ROUTE'}
NUM_PALS_IN_PRIMARY, NUM_PALS_TOTAL = 6, 13
NUM_TILES_IN_PRIMARY = 512
WATER = ('WATER', 'POND', 'OCEAN', 'CURRENT', 'PUDDLE', 'SEAWEED', 'HOT_SPRINGS')

# (tileset, palette, couleur) : pas des vitres / vitres non repérées ; None = toute la palette / tout le tileset
EXCLUDE = {
    ('gTileset_General', 4, 7),          # toit de la Boutique de Hoenn
    ('gTileset_Pacifidlog', 10, None),   # eau autour des rondins
    ('gTileset_Cave', None, None),       # pas de bâtiments
}
INCLUDE = set()
# Métatiles dont les tiles ne s'allument jamais, même avec une couleur de vitre (le rendu teste le tile de chaque
# pixel, voir gDayNightRender) : pour les couleurs partagées entre fenêtres et autre chose
UNLIT_METATILES = {
    'gTileset_KantoGeneral': [40, 41, 42, 43, 48, 49, 50, 51, 56, 57, 58, 59],   # verrière des Boutiques
    # Tentes de Combat (numéros dans le tileset secondaire : métatile de la carte - 512)
    'gTileset_Fallarbor': [r + c for r in (330, 338, 346, 354, 362) for c in range(5)],
    'gTileset_Mauville': [r + c for r in (434, 442, 450, 458, 466) for c in range(5)],
}


def excluded(key):
    tileset, slot, i = key
    return key in EXCLUDE or (tileset, slot, None) in EXCLUDE or (tileset, None, None) in EXCLUDE


def glass(c):
    r, g, b = c
    return b >= 200 and b - r >= 50 and g > r and r >= 80


def palette_files():
    files = {}
    for h in glob.glob(os.path.join(ROOT, 'src/data/tilesets/*graphics.h')) + [os.path.join(ROOT, 'src/graphics.c')]:
        text = open(h, encoding='utf-8').read()
        for name, body in re.findall(r'gTilesetPalettes_(\w+)\[\]\[16\] =\s*\{(.*?)\};', text, re.S):
            files['gTileset_' + name] = re.findall(r'"([^"]+\.pal)"', body)
    return files


def tileset_dir(pals, tileset):
    return os.path.dirname(os.path.dirname(pals[tileset][0]))


def water_behaviors():
    text = open(os.path.join(ROOT, 'include/constants/metatile_behaviors.h'), encoding='utf-8').read()
    names = re.findall(r'^\s*(MB_\w+)', text.split('enum {', 1)[1], re.M)
    return {i for i, n in enumerate(names) if any(w in n for w in WATER) and 'BRIDGE' not in n}


def tile_indices(path):
    """Indices de couleur de chaque tile 8x8 de tiles.png."""
    im = Image.open(os.path.join(ROOT, path))
    w, h = im.size
    px = im.load()
    return [{px[tx * 8 + x, ty * 8 + y] & 15 for y in range(8) for x in range(8)}
            for ty in range(h // 8) for tx in range(w // 8)]


def water_colors(pals, pairs):
    """(tileset propriétaire de la palette, palette, couleur) dessinées par un métatile d'eau."""
    water = water_behaviors()
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


def outdoor_tilesets():
    layouts = {l['id']: l for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts'] if 'id' in l}
    pairs = set()
    for f in glob.glob(os.path.join(ROOT, 'data/maps/*/map.json')):
        m = json.load(open(f, encoding='utf-8'))
        if m.get('map_type') in OUTDOOR and m.get('layout') in layouts:
            l = layouts[m['layout']]
            pairs.add((l['primary_tileset'], l['secondary_tileset']))
    return pairs


def unlit_tiles(pals, tileset):
    """Tiles du tileset (0-511) posés par UNLIT_METATILES."""
    meta = open(os.path.join(ROOT, tileset_dir(pals, tileset), 'metatiles.bin'), 'rb').read()
    base = NUM_TILES_IN_PRIMARY if is_secondary(tileset) else 0
    tiles = set()
    for m in UNLIT_METATILES.get(tileset, []):
        for k in range(8):
            t = struct.unpack_from('<H', meta, (m * 8 + k) * 2)[0] & 0x3FF
            if base <= t < base + NUM_TILES_IN_PRIMARY:
                tiles.add(t - base)
    return tiles


def is_secondary(tileset):
    for h in glob.glob(os.path.join(ROOT, 'src/data/tilesets/*headers.h')):
        m = re.search(r'struct Tileset ' + tileset + r' =\s*\{.*?isSecondary = (\w+)', open(h, encoding='utf-8').read(), re.S)
        if m:
            return m.group(1) == 'TRUE'
    raise KeyError(tileset)


def main():
    pals = palette_files()
    pairs = outdoor_tilesets()
    water = water_colors(pals, pairs)
    entries = []
    for tileset, primary in sorted({(p, True) for p, _ in pairs} | {(s, False) for _, s in pairs}):
        slots = range(NUM_PALS_IN_PRIMARY) if primary else range(NUM_PALS_IN_PRIMARY, NUM_PALS_TOTAL)
        masks = []
        for slot in slots:
            cols = read_pal(pals[tileset][slot])
            mask = 0
            for i, c in enumerate(cols):
                key = (tileset, slot, i)
                if i and ((glass(c) and key not in water and not excluded(key)) or key in INCLUDE):
                    mask |= 1 << i
            masks.append((slot, mask))
        if any(m for _, m in masks):
            entries.append((tileset, masks, unlit_tiles(pals, tileset)))
    out = ['// Généré par tools/day_night_lights.py : couleurs de vitre (masque par palette) éclairées la nuit']
    out += [f'extern const struct Tileset {t};' for t, _, _ in entries]
    for tileset, _, unlit in entries:
        if unlit:
            bits = [0] * (NUM_TILES_IN_PRIMARY // 8)
            for t in unlit:
                bits[t // 8] |= 1 << (t % 8)
            out += ['', f'static const u8 sUnlitTiles_{tileset[9:]}[NUM_TILES_IN_PRIMARY / 8] =', '{']
            out += ['    ' + ', '.join(f'0x{b:02X}' for b in bits[i:i + 16]) + ',' for i in range(0, len(bits), 16)]
            out += ['};']
    out += ['', 'static const struct DayNightLights sDayNightLights[] =', '{']
    for tileset, masks, unlit in entries:
        body = ', '.join(f'[{s}] = 0x{m:04X}' for s, m in masks if m)
        tiles = f', sUnlitTiles_{tileset[9:]}' if unlit else ''
        out.append(f'    {{ &{tileset}, {{ {body} }}{tiles} }},')
    out += ['};', '']
    open(os.path.join(ROOT, 'src/data/day_night_lights.h'), 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
    print(f'src/data/day_night_lights.h : {len(entries)} tilesets')


if __name__ == '__main__':
    main()
