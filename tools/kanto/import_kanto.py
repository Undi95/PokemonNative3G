#!/usr/bin/env python3
"""Importe des cartes de Rouge Feu (décomp pokerougefeu) dans le moteur d'Émeraude.

Usage : import_kanto.py FR_DIR EM_DIR MAP [MAP...]
  FR_DIR : décomp pokerougefeu (lecture seule)
  EM_DIR : ce dépôt
  MAP    : noms de dossier RF (ex. PalletTown Route1)

Principe des tilesets : RF découpe la VRAM en primaire 640 tuiles / 640 metatiles /
7 palettes, Émeraude en 512 / 512 / 6. Les totaux sont identiques (1024/1024/13).
On redécoupe donc chaque paire RF à la frontière d'Émeraude : le primaire Kanto garde
les 512 premiers éléments du primaire RF, le secondaire Kanto reçoit le reste du
primaire RF suivi du secondaire RF. La VRAM chargée est identique octet pour octet :
aucun index de tuile, de palette ou de metatile n'est renuméroté dans les cartes.

Étape actuelle : géométrie seulement (layouts, tilesets, connexions, warps internes).
Les événements (PNJ, panneaux, scripts) viendront avec la conversion des scripts.
"""
import json, os, re, shutil, struct, sys
from PIL import Image

EM_TILES_PRI, EM_MT_PRI, EM_PALS_PRI = 512, 512, 6
FR_TILES_PRI, FR_MT_PRI, FR_PALS_PRI = 640, 640, 7
NUM_PALS_TOTAL = 13

def camel_to_snake(s):
    return re.sub(r'(?<=[a-z0-9])(?=[A-Z])|(?<=[A-Z])(?=[A-Z][a-z])', '_', s).lower()

def parse_defines(path, prefix):
    out = {}
    for line in open(path, encoding='utf-8'):
        m = re.match(r'\s*#define\s+(' + prefix + r'\w+)\s+(0x[0-9A-Fa-f]+|\d+)', line)
        if m:
            out[m.group(1)] = int(m.group(2), 0)
    return out

def parse_enum(path, prefix):
    """Valeurs d'un enum C simple (membres séparés par des virgules, sans initialiseur)."""
    out, n = {}, 0
    for line in open(path, encoding='utf-8'):
        m = re.match(r'\s*(' + prefix + r'\w+)\s*(?:=\s*(0x[0-9A-Fa-f]+|\d+))?\s*,', line)
        if m:
            if m.group(2):
                n = int(m.group(2), 0)
            out[m.group(1)] = n
            n += 1
    return out

# Comportements RF sans homonyme dans Émeraude -> équivalent le plus proche.
BEHAVIOR_ALIASES = {
    'MB_SIGNPOST': 'MB_NORMAL',              # Émeraude : panneaux = bg_events
    'MB_POKEMART_SIGN': 'MB_NORMAL',
    'MB_POKEMON_CENTER_SIGN': 'MB_NORMAL',
    'MB_ROCK_STAIRS': 'MB_NORMAL',
    'MB_WARP_DOOR': 'MB_NON_ANIMATED_DOOR',  # TODO : animations de portes Kanto
    'MB_CAVE_DOOR': 'MB_NON_ANIMATED_DOOR',
    'MB_FAST_WATER': 'MB_OCEAN_WATER',
}

class Importer:
    def __init__(self, fr, em):
        self.fr, self.em = fr, em
        fr_mb = parse_defines(f'{fr}/include/constants/metatile_behaviors.h', 'MB_')
        em_mb = parse_enum(f'{em}/include/constants/metatile_behaviors.h', 'MB_')
        self.fr_mb_name = {v: k for k, v in fr_mb.items()}
        self.em_mb = em_mb
        self.unmapped_behaviors = {}
        self.fr_layouts = {l['id']: l for l in json.load(open(f'{fr}/data/layouts/layouts.json'))['layouts'] if 'id' in l}
        self.fr_tileset_dirs = self._tileset_dirs(fr)

    # --- tilesets -------------------------------------------------------------
    def _tileset_dirs(self, root):
        """gTileset_X -> dossier, d'après src/data/tilesets/metatiles.h."""
        out = {}
        for line in open(f'{root}/src/data/tilesets/metatiles.h', encoding='utf-8'):
            m = re.match(r'const u16 gMetatiles_(\w+)\[\] = INCBIN_U16\("(data/tilesets/\w+/\w+)/metatiles.bin"\)', line)
            if m:
                out['gTileset_' + m.group(1)] = m.group(2)
        return out

    def behavior(self, fr_value):
        name = self.fr_mb_name.get(fr_value)
        name = BEHAVIOR_ALIASES.get(name, name)
        if name in self.em_mb:
            return self.em_mb[name]
        self.unmapped_behaviors[name or hex(fr_value)] = self.unmapped_behaviors.get(name or hex(fr_value), 0) + 1
        return 0  # MB_NORMAL

    def convert_attrs(self, data):
        out = bytearray()
        for (a,) in struct.iter_unpack('<I', data):
            beh = self.behavior(a & 0x1FF)
            layer = (a >> 29) & 0x3
            out += struct.pack('<H', beh | (layer << 12))
        return bytes(out)

    def fr_tiles_png(self, d):
        for name in ('tiles_fr.png', 'tiles.png'):
            if os.path.exists(f'{self.fr}/{d}/{name}'):
                return f'{self.fr}/{d}/{name}'
        raise FileNotFoundError(d)

    @staticmethod
    def tiles_of(img):
        w, h = img.size
        return [img.crop((x, y, x + 8, y + 8)) for y in range(0, h, 8) for x in range(0, w, 8)]

    @staticmethod
    def tiles_to_png(tiles, palette, path, width_tiles=16):
        rows = (len(tiles) + width_tiles - 1) // width_tiles
        img = Image.new('P', (width_tiles * 8, rows * 8), 0)
        img.putpalette(palette)
        for i, t in enumerate(tiles):
            img.paste(t, ((i % width_tiles) * 8, (i // width_tiles) * 8))
        img.save(path)

    def tileset_name(self, fr_label):
        return 'gTileset_Kanto' + fr_label[len('gTileset_'):]

    def import_tileset_pair(self, pri_label, sec_label):
        """Crée gTileset_Kanto<Pri> (primaire) et gTileset_Kanto<Sec> (secondaire)."""
        pdir, sdir = self.fr_tileset_dirs[pri_label], self.fr_tileset_dirs[sec_label]
        pimg = Image.open(self.fr_tiles_png(pdir)); simg = Image.open(self.fr_tiles_png(sdir))
        ptiles, stiles = self.tiles_of(pimg), self.tiles_of(simg)
        pmt = open(f'{self.fr}/{pdir}/metatiles.bin', 'rb').read()
        pat = open(f'{self.fr}/{pdir}/metatile_attributes.bin', 'rb').read()
        smt = open(f'{self.fr}/{sdir}/metatiles.bin', 'rb').read()
        sat = open(f'{self.fr}/{sdir}/metatile_attributes.bin', 'rb').read()
        assert len(ptiles) >= FR_TILES_PRI or True
        made = []
        # primaire
        pname = self.tileset_name(pri_label)
        pout = f'{self.em}/data/tilesets/primary/kanto_{os.path.basename(pdir)}'
        if not os.path.exists(pout):
            os.makedirs(f'{pout}/palettes')
            self.tiles_to_png(ptiles[:EM_TILES_PRI], pimg.getpalette(), f'{pout}/tiles.png')
            open(f'{pout}/metatiles.bin', 'wb').write(pmt[:EM_MT_PRI * 16])
            open(f'{pout}/metatile_attributes.bin', 'wb').write(self.convert_attrs(pat[:EM_MT_PRI * 4]))
            for i in range(16):  # palettes 0-5 utiles, le reste suit RF
                shutil.copy(f'{self.fr}/{pdir}/palettes/{i:02}.pal', f'{pout}/palettes/{i:02}.pal')
            made.append((pname, pout, False, len(ptiles[:EM_TILES_PRI])))
        # secondaire = débord du primaire RF + secondaire RF
        sname = self.tileset_name(sec_label)
        sout = f'{self.em}/data/tilesets/secondary/kanto_{os.path.basename(sdir)}'
        if not os.path.exists(sout):
            os.makedirs(f'{sout}/palettes')
            tiles = ptiles[EM_TILES_PRI:FR_TILES_PRI] + stiles
            tiles += [Image.new('P', (8, 8), 0)] * 0
            self.tiles_to_png(tiles, simg.getpalette(), f'{sout}/tiles.png')
            mt = pmt[EM_MT_PRI * 16:FR_MT_PRI * 16] + smt
            at = self.convert_attrs(pat[EM_MT_PRI * 4:FR_MT_PRI * 4] + sat)
            open(f'{sout}/metatiles.bin', 'wb').write(mt)
            open(f'{sout}/metatile_attributes.bin', 'wb').write(at)
            # Émeraude charge palettes[6..12] du secondaire : 6 = palette 6 du primaire RF,
            # 7..12 = palettes du secondaire RF (aux mêmes indices).
            for i in range(16):
                src = f'{self.fr}/{pdir}/palettes/{i:02}.pal' if i < FR_PALS_PRI else f'{self.fr}/{sdir}/palettes/{i:02}.pal'
                shutil.copy(src, f'{sout}/palettes/{i:02}.pal')
            made.append((sname, sout, True, len(tiles)))
        return pname, sname, made

    # --- fichiers C des tilesets ----------------------------------------------
    def register_tilesets(self, made, pri_callbacks):
        base = f'{self.em}/src/data/tilesets'
        for name, path, secondary, ntiles in made:
            short = name[len('gTileset_'):]
            rel = os.path.relpath(path, self.em).replace('\\', '/')
            gfx = f'\nconst u32 gTilesetTiles_{short}[] = INCGFX_U32("{rel}/tiles.png", ".4bpp.lz");\n\n'
            gfx += f'const u16 gTilesetPalettes_{short}[][16] =\n{{\n'
            gfx += ''.join(f'\tINCGFX_U16("{rel}/palettes/{i:02}.pal", ".gbapal"),\n' for i in range(16))
            gfx += '};\n'
            open(f'{base}/graphics.h', 'a', encoding='utf-8').write(gfx)
            mt = (f'\nconst u16 gMetatiles_{short}[] = INCBIN_U16("{rel}/metatiles.bin");\n'
                  f'const u16 gMetatileAttributes_{short}[] = INCBIN_U16("{rel}/metatile_attributes.bin");\n')
            open(f'{base}/metatiles.h', 'a', encoding='utf-8').write(mt)
            hdr = (f'\nconst struct Tileset {name} =\n{{\n'
                   f'    .isCompressed = TRUE,\n'
                   f'    .isSecondary = {"TRUE" if secondary else "FALSE"},\n'
                   f'    .tiles = gTilesetTiles_{short},\n'
                   f'    .palettes = gTilesetPalettes_{short},\n'
                   f'    .metatiles = gMetatiles_{short},\n'
                   f'    .metatileAttributes = gMetatileAttributes_{short},\n'
                   f'    .callback = NULL,\n}};\n')
            open(f'{base}/headers.h', 'a', encoding='utf-8').write(hdr)

    # --- cartes ----------------------------------------------------------------
    def run(self, maps):
        em_layouts_path = f'{self.em}/data/layouts/layouts.json'
        em_layouts = json.load(open(em_layouts_path, encoding='utf-8'))
        em_layout_ids = {l['id'] for l in em_layouts['layouts'] if 'id' in l}
        groups_path = f'{self.em}/data/maps/map_groups.json'
        groups = json.load(open(groups_path, encoding='utf-8'))
        em_map_ids = set()
        for g in groups['group_order']:
            for m in groups[g]:
                mj = f'{self.em}/data/maps/{m}/map.json'
                if os.path.exists(mj):
                    em_map_ids.add(json.load(open(mj, encoding='utf-8'))['id'])
        fr_groups = json.load(open(f'{self.fr}/data/maps/map_groups.json', encoding='utf-8'))
        fr_group_of = {m: g for g in fr_groups['group_order'] for m in fr_groups[g]}

        fr_maps = {m: json.load(open(f'{self.fr}/data/maps/{m}/map.json', encoding='utf-8')) for m in maps}
        imported_ids = {j['id'] for j in fr_maps.values()}
        for j in fr_maps.values():
            assert j['id'] not in em_map_ids, f"collision d'id de carte : {j['id']}"

        all_made = []
        done_pairs = {}
        for m, j in fr_maps.items():
            lay = self.fr_layouts[j['layout']]
            assert lay['id'] not in em_layout_ids or lay['id'] in [l.get('id') for l in em_layouts['layouts'][-50:]], f"collision layout {lay['id']}"
            pair = (lay['primary_tileset'], lay['secondary_tileset'])
            if pair not in done_pairs:
                done_pairs[pair] = self.import_tileset_pair(*pair)
                all_made += done_pairs[pair][2]
            pname, sname, _ = done_pairs[pair]
            if lay['id'] not in em_layout_ids:
                ldir = f'data/layouts/{os.path.basename(os.path.dirname(lay["blockdata_filepath"]))}'
                os.makedirs(f'{self.em}/{ldir}', exist_ok=True)
                shutil.copy(f'{self.fr}/{lay["border_filepath"]}', f'{self.em}/{ldir}/border.bin')
                shutil.copy(f'{self.fr}/{lay["blockdata_filepath"]}', f'{self.em}/{ldir}/map.bin')
                em_layouts['layouts'].append({
                    'id': lay['id'], 'name': lay['name'], 'width': lay['width'], 'height': lay['height'],
                    'border_width': lay.get('border_width', 2), 'border_height': lay.get('border_height', 2),
                    'primary_tileset': pname, 'secondary_tileset': sname,
                    'border_filepath': f'{ldir}/border.bin', 'blockdata_filepath': f'{ldir}/map.bin'})
                em_layout_ids.add(lay['id'])

            # map.json
            out = {k: j[k] for k in ('id', 'name', 'layout', 'music', 'region_map_section', 'requires_flash',
                                     'weather', 'map_type', 'allow_cycling', 'allow_escaping', 'allow_running',
                                     'show_map_name', 'battle_scene')}
            out['music'] = self.music(j['music'])
            out['connections'] = [c for c in (j.get('connections') or []) if c['map'] in imported_ids] or None
            out['object_events'] = []
            out['warp_events'] = [w for w in j.get('warp_events', []) if w['dest_map'] in imported_ids]
            out['coord_events'] = []
            out['bg_events'] = []
            os.makedirs(f'{self.em}/data/maps/{m}', exist_ok=True)
            json.dump(out, open(f'{self.em}/data/maps/{m}/map.json', 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
            open(f'{self.em}/data/maps/{m}/scripts.inc', 'w', encoding='utf-8').write(f'{m}_MapScripts::\n\t.byte 0\n')

            g = 'gMapGroup_Kanto' + fr_group_of[m][len('gMapGroup_'):]
            if g not in groups:
                groups[g] = []
                groups['group_order'].append(g)
            if m not in groups[g]:
                groups[g].append(m)
            if out['connections'] and m not in groups['connections_include_order']:
                groups['connections_include_order'].append(m)

        json.dump(em_layouts, open(em_layouts_path, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
        json.dump(groups, open(groups_path, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
        self.register_tilesets(all_made, None)
        print('tilesets créés :', [m[0] for m in all_made])
        if self.unmapped_behaviors:
            print('comportements RF sans équivalent (-> MB_NORMAL) :', self.unmapped_behaviors)

    def music(self, fr_name):
        em_songs = parse_defines(f'{self.em}/include/constants/songs.h', 'MUS_')
        cand = 'MUS_RG_' + fr_name[len('MUS_'):]
        if cand in em_songs:
            return cand
        print(f'musique sans équivalent : {fr_name} -> MUS_NONE')
        return 'MUS_NONE'

if __name__ == '__main__':
    Importer(sys.argv[1], sys.argv[2]).run(sys.argv[3:])
