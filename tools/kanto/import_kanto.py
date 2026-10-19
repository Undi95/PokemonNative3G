#!/usr/bin/env python3
"""Importe les cartes de Rouge Feu (décomp pokerougefeu) dans le moteur d'Émeraude.

Usage : import_kanto.py FR_DIR EM_DIR --all | MAP [MAP...]
  FR_DIR : décomp pokerougefeu (lecture seule)
  EM_DIR : ce dépôt
  MAP    : noms de dossier RF (ex. PalletTown Route1), ou --all

Tout ce que l'outil produit est régénéré à chaque exécution : il retire d'abord ce
qu'un import précédent a ajouté (groupes gMapGroup_Kanto*, layouts Kanto_*, tilesets
kanto_*, src/data/tilesets/kanto_*.h, data/kanto/scripts.inc). Ne pas modifier ces
fichiers à la main.

Principe des tilesets : RF découpe la VRAM en primaire 640 tuiles / 640 metatiles /
7 palettes, Émeraude en 512 / 512 / 6. Les totaux sont identiques (1024/1024/13).
On redécoupe donc chaque paire RF à la frontière d'Émeraude : le primaire Kanto garde
les 512 premiers éléments du primaire RF, le secondaire Kanto reçoit le reste du
primaire RF suivi du secondaire RF. La VRAM chargée est identique octet pour octet :
aucun index de tuile, de palette ou de metatile n'est renuméroté dans les cartes.

Étape actuelle : géométrie (layouts, tilesets, connexions, warps).
Les événements (PNJ, panneaux, scripts) viendront avec la conversion des scripts.
"""
import json, os, re, shutil, struct, sys
from PIL import Image

EM_TILES_PRI, EM_MT_PRI, EM_PALS_PRI = 512, 512, 6
FR_TILES_PRI, FR_MT_PRI, FR_PALS_PRI = 640, 640, 7

# Cartes RF dont le nom existe aussi dans Émeraude mais qui sont différentes : préfixe Kanto.
RENAME_PREFIXES = ('VictoryRoad', 'SafariZone')

# Décors de combat RF absents d'Émeraude (Conseil 4 : décor d'Émeraude du même type)
BATTLE_SCENE_ALIASES = {
    'MAP_BATTLE_SCENE_INDOOR_1': 'MAP_BATTLE_SCENE_NORMAL',
    'MAP_BATTLE_SCENE_INDOOR_2': 'MAP_BATTLE_SCENE_NORMAL',
    'MAP_BATTLE_SCENE_LINK': 'MAP_BATTLE_SCENE_NORMAL',
    'MAP_BATTLE_SCENE_LORELEI': 'MAP_BATTLE_SCENE_GLACIA',
    'MAP_BATTLE_SCENE_AGATHA': 'MAP_BATTLE_SCENE_PHOEBE',
    'MAP_BATTLE_SCENE_BRUNO': 'MAP_BATTLE_SCENE_SIDNEY',
    'MAP_BATTLE_SCENE_LANCE': 'MAP_BATTLE_SCENE_DRAKE',
}

# Comportements RF sans homonyme dans Émeraude -> équivalent le plus proche.
BEHAVIOR_ALIASES = {
    'MB_SIGNPOST': 'MB_NORMAL',              # Émeraude : panneaux = bg_events
    'MB_POKEMART_SIGN': 'MB_NORMAL',
    'MB_POKEMON_CENTER_SIGN': 'MB_NORMAL',
    'MB_ROCK_STAIRS': 'MB_NORMAL',
    'MB_WARP_DOOR': 'MB_ANIMATED_DOOR',      # animations : src/kanto_field_door.c
    'MB_CAVE_DOOR': 'MB_NON_ANIMATED_DOOR',
    'MB_FAST_WATER': 'MB_OCEAN_WATER',
    # Escaliers latéraux, trous, warps simples de RF -> warp classique d'Émeraude
    'MB_UP_LEFT_STAIR_WARP': 'MB_NON_ANIMATED_DOOR',
    'MB_UP_RIGHT_STAIR_WARP': 'MB_NON_ANIMATED_DOOR',
    'MB_DOWN_LEFT_STAIR_WARP': 'MB_NON_ANIMATED_DOOR',
    'MB_DOWN_RIGHT_STAIR_WARP': 'MB_NON_ANIMATED_DOOR',
    'MB_REGULAR_WARP': 'MB_NON_ANIMATED_DOOR',
    'MB_FALL_WARP': 'MB_NON_ANIMATED_DOOR',
}


def parse_defines(path, prefix):
    out = {}
    for line in open(path, encoding='utf-8'):
        m = re.match(r'\s*#define\s+(' + prefix + r'\w+)\s+(0x[0-9A-Fa-f]+|\d+)', line)
        if m:
            out[m.group(1)] = int(m.group(2), 0)
    return out


def parse_enum(path, prefix):
    """Valeurs d'un enum C simple (un membre par ligne)."""
    out, n = {}, 0
    for line in open(path, encoding='utf-8'):
        m = re.match(r'\s*(' + prefix + r'\w+)\s*(?:=\s*(0x[0-9A-Fa-f]+|\d+))?\s*,', line)
        if m:
            if m.group(2):
                n = int(m.group(2), 0)
            out[m.group(1)] = n
            n += 1
    return out


def write_text(path, text):
    with open(path, 'w', encoding='utf-8', newline='\n') as f:
        f.write(text)


def write_json(path, data):
    with open(path, 'w', encoding='utf-8', newline='\n') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write('\n')


class Importer:
    def __init__(self, fr, em):
        self.fr, self.em = fr, em
        fr_mb = parse_defines(f'{fr}/include/constants/metatile_behaviors.h', 'MB_')
        self.fr_mb_name = {v: k for k, v in fr_mb.items()}
        self.em_mb = parse_enum(f'{em}/include/constants/metatile_behaviors.h', 'MB_')
        self.unmapped_behaviors = {}
        self.fr_layouts = {l['id']: l for l in json.load(open(f'{fr}/data/layouts/layouts.json'))['layouts'] if 'id' in l}
        self.fr_tilesets = self._tileset_sources(fr)
        self.em_songs = parse_defines(f'{em}/include/constants/songs.h', 'MUS_')

    # --- tilesets -------------------------------------------------------------
    def _tileset_sources(self, root):
        """gTileset_X -> fichiers sources (tuiles, palettes, metatiles, attributs), en lisant
        headers.h : plusieurs tilesets RF partagent les tuiles/palettes d'un autre."""
        files = {}
        for path in (f'{root}/src/data/tilesets/graphics.h', f'{root}/src/data/tilesets/metatiles.h', f'{root}/src/graphics.c'):
            text = open(path, encoding='utf-8').read()
            for sym, inc in re.findall(r'const u\d+ (gTilesetTiles_\w+|gMetatiles_\w+|gMetatileAttributes_\w+)\[\] = INCBIN_U\d+\("([^"]+)"\)', text):
                files[sym] = inc
            for sym, body in re.findall(r'const u16 (gTilesetPalettes_\w+)\[\]\[16\] =\s*\{(.*?)\};', text, re.S):
                first = re.search(r'"([^"]+)/00\.gbapal"', body)
                files[sym] = first.group(1)
        out = {}
        text = open(f'{root}/src/data/tilesets/headers.h', encoding='utf-8').read()
        for label, body in re.findall(r'const struct Tileset (gTileset_\w+) =\s*\{(.*?)\};', text, re.S):
            f = dict(re.findall(r'\.(tiles|palettes|metatiles|metatileAttributes) = (\w+)', body))
            out[label] = {
                'tiles': files[f['tiles']].replace('.4bpp.lz', '.png').replace('.4bpp', '.png'),
                'palettes': files[f['palettes']],
                'metatiles': files[f['metatiles']],
                'attrs': files[f['metatileAttributes']],
                'dir': os.path.dirname(files[f['metatiles']]),
            }
        return out

    def behavior(self, fr_value):
        name = self.fr_mb_name.get(fr_value)
        name = BEHAVIOR_ALIASES.get(name, name)
        if name in self.em_mb:
            return self.em_mb[name]
        key = name or hex(fr_value)
        self.unmapped_behaviors[key] = self.unmapped_behaviors.get(key, 0) + 1
        return 0  # MB_NORMAL

    def convert_attrs(self, data):
        out = bytearray()
        for (a,) in struct.iter_unpack('<I', data):
            out += struct.pack('<H', self.behavior(a & 0x1FF) | (((a >> 29) & 0x3) << 12))
        return bytes(out)

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

    @staticmethod
    def tileset_name(fr_label):
        return 'gTileset_Kanto' + fr_label[len('gTileset_'):]

    def import_tileset_pair(self, pri_label, sec_label, variant=''):
        """Crée gTileset_Kanto<Pri> (primaire) et gTileset_Kanto<Sec> (secondaire)."""
        P, S = self.fr_tilesets[pri_label], self.fr_tilesets[sec_label]
        pdir, sdir = P['dir'], S['dir']
        pimg, simg = Image.open(f"{self.fr}/{P['tiles']}"), Image.open(f"{self.fr}/{S['tiles']}")
        ptiles, stiles = self.tiles_of(pimg), self.tiles_of(simg)
        pmt = open(f"{self.fr}/{P['metatiles']}", 'rb').read()
        pat = open(f"{self.fr}/{P['attrs']}", 'rb').read()
        smt = open(f"{self.fr}/{S['metatiles']}", 'rb').read()
        sat = open(f"{self.fr}/{S['attrs']}", 'rb').read()
        made = []
        pname = self.tileset_name(pri_label)
        pout = f'{self.em}/data/tilesets/primary/kanto_{os.path.basename(pdir)}'
        if not os.path.exists(pout):
            os.makedirs(f'{pout}/palettes')
            self.tiles_to_png(ptiles[:EM_TILES_PRI], pimg.getpalette(), f'{pout}/tiles.png')
            open(f'{pout}/metatiles.bin', 'wb').write(pmt[:EM_MT_PRI * 16])
            open(f'{pout}/metatile_attributes.bin', 'wb').write(self.convert_attrs(pat[:EM_MT_PRI * 4]))
            for i in range(16):  # Émeraude n'en charge que 0-5 pour un primaire
                shutil.copy(f"{self.fr}/{P['palettes']}/{i:02}.pal", f'{pout}/palettes/{i:02}.pal')
            made.append((pname, pout, False))
        sname = self.tileset_name(sec_label) + variant
        sout = f'{self.em}/data/tilesets/secondary/kanto_{os.path.basename(sdir)}' + ('_' + variant.lower() if variant else '')
        if not os.path.exists(sout):
            os.makedirs(f'{sout}/palettes')
            tiles = ptiles[EM_TILES_PRI:FR_TILES_PRI] + stiles
            assert len(tiles) <= 512, (sec_label, len(tiles))
            self.tiles_to_png(tiles, simg.getpalette(), f'{sout}/tiles.png')
            open(f'{sout}/metatiles.bin', 'wb').write(pmt[EM_MT_PRI * 16:FR_MT_PRI * 16] + smt)
            open(f'{sout}/metatile_attributes.bin', 'wb').write(self.convert_attrs(pat[EM_MT_PRI * 4:FR_MT_PRI * 4] + sat))
            # Émeraude charge palettes[6..12] du secondaire : 6 = palette 6 du primaire RF,
            # 7..12 = palettes du secondaire RF (aux mêmes indices).
            for i in range(16):
                src = f"{self.fr}/{P['palettes']}/{i:02}.pal" if i < FR_PALS_PRI else f"{self.fr}/{S['palettes']}/{i:02}.pal"
                shutil.copy(src, f'{sout}/palettes/{i:02}.pal')
            made.append((sname, sout, True))
        return pname, sname, made

    def write_tileset_sources(self, made):
        """src/data/tilesets/kanto_{graphics,metatiles,headers}.h, inclus en fin des fichiers d'Émeraude."""
        head = '// Généré par tools/kanto/import_kanto.py — ne pas modifier à la main.\n'
        gfx = mt = hdr = head
        for name, path, secondary in sorted(made):
            short = name[len('gTileset_'):]
            rel = os.path.relpath(path, self.em).replace('\\', '/')
            gfx += f'\nconst u32 gTilesetTiles_{short}[] = INCGFX_U32("{rel}/tiles.png", ".4bpp.lz");\n\n'
            gfx += f'const u16 gTilesetPalettes_{short}[][16] =\n{{\n'
            gfx += ''.join(f'\tINCGFX_U16("{rel}/palettes/{i:02}.pal", ".gbapal"),\n' for i in range(16))
            gfx += '};\n'
            mt += (f'\nconst u16 gMetatiles_{short}[] = INCBIN_U16("{rel}/metatiles.bin");\n'
                   f'const u16 gMetatileAttributes_{short}[] = INCBIN_U16("{rel}/metatile_attributes.bin");\n')
            hdr += (f'\nconst struct Tileset {name} =\n{{\n'
                    f'    .isCompressed = TRUE,\n'
                    f'    .isSecondary = {"TRUE" if secondary else "FALSE"},\n'
                    f'    .tiles = gTilesetTiles_{short},\n'
                    f'    .palettes = gTilesetPalettes_{short},\n'
                    f'    .metatiles = gMetatiles_{short},\n'
                    f'    .metatileAttributes = gMetatileAttributes_{short},\n'
                    f'    .callback = NULL,\n}};\n')
        base = f'{self.em}/src/data/tilesets'
        write_text(f'{base}/kanto_graphics.h', gfx)
        write_text(f'{base}/kanto_metatiles.h', mt)
        write_text(f'{base}/kanto_headers.h', hdr)

    # --- nettoyage de l'import précédent -----------------------------------------
    def remove_previous_import(self, em_layouts, groups):
        old_groups = [g for g in groups['group_order'] if g.startswith('gMapGroup_Kanto')]
        old_maps = [m for g in old_groups for m in groups[g]]
        for g in old_groups:
            groups['group_order'].remove(g)
            del groups[g]
        groups['connections_include_order'] = [m for m in groups['connections_include_order'] if m not in old_maps]
        for m in old_maps:
            shutil.rmtree(f'{self.em}/data/maps/{m}', ignore_errors=True)
        old_layouts = [l for l in em_layouts['layouts'] if l.get('primary_tileset', '').startswith('gTileset_Kanto')]
        for l in old_layouts:
            shutil.rmtree(f'{self.em}/{os.path.dirname(l["blockdata_filepath"])}', ignore_errors=True)
        em_layouts['layouts'] = [l for l in em_layouts['layouts'] if l not in old_layouts]
        for d in ('primary', 'secondary'):
            for t in os.listdir(f'{self.em}/data/tilesets/{d}'):
                if t.startswith('kanto_'):
                    shutil.rmtree(f'{self.em}/data/tilesets/{d}/{t}')

    # --- noms ------------------------------------------------------------------
    def plan_names(self, em_map_names, em_map_ids, em_layout_ids):
        """Cartes RF ignorées (versions d'Émeraude conservées) et renommages."""
        self.skip, self.map_rename, self.id_rename, self.layout_rename = set(), {}, {}, {}
        for m, j in self.fr_maps.items():
            if self.fr_group_of[m] == 'gMapGroup_Link' or m.startswith(('NavelRock', 'BirthIsland')):
                self.skip.add(m)
            elif m.startswith(RENAME_PREFIXES) or m in em_map_names or j['id'] in em_map_ids:
                self.map_rename[m] = 'Kanto' + m
                self.id_rename[j['id']] = 'MAP_KANTO_' + j['id'][len('MAP_'):]
        for m, j in self.fr_maps.items():
            lid = j['layout']
            if m not in self.skip and lid in em_layout_ids:
                self.layout_rename[lid] = 'LAYOUT_KANTO_' + lid[len('LAYOUT_'):]

    def em_map_id(self, fr_id):
        return self.id_rename.get(fr_id, fr_id)

    def music(self, fr_name):
        if fr_name == 'MUS_NONE':
            return fr_name
        cand = 'MUS_RG_' + fr_name[len('MUS_'):]
        if cand in self.em_songs:
            return cand
        if fr_name in self.em_songs:
            return fr_name
        self.warn('musique sans équivalent -> MUS_NONE', fr_name)
        return 'MUS_NONE'

    def warn(self, kind, what):
        self.warnings.setdefault(kind, set()).add(what)

    # --- cartes ----------------------------------------------------------------
    def run(self, maps):
        self.warnings = {}
        layouts_path = f'{self.em}/data/layouts/layouts.json'
        groups_path = f'{self.em}/data/maps/map_groups.json'
        em_layouts = json.load(open(layouts_path, encoding='utf-8'))
        groups = json.load(open(groups_path, encoding='utf-8'))
        self.remove_previous_import(em_layouts, groups)

        em_layout_ids = {l['id'] for l in em_layouts['layouts'] if 'id' in l}
        em_map_names = {m for g in groups['group_order'] for m in groups[g]}
        em_map_ids = set()
        for m in em_map_names:
            mj = f'{self.em}/data/maps/{m}/map.json'
            if os.path.exists(mj):
                em_map_ids.add(json.load(open(mj, encoding='utf-8'))['id'])
        em_mapsecs = set(re.findall(r'"(MAPSEC_\w+)"', open(f'{self.em}/src/data/region_map/region_map_sections.json', encoding='utf-8').read()))

        fr_groups = json.load(open(f'{self.fr}/data/maps/map_groups.json', encoding='utf-8'))
        self.fr_group_of = {m: g for g in fr_groups['group_order'] for m in fr_groups[g]}
        if maps == ['--all']:
            maps = [m for g in fr_groups['group_order'] for m in fr_groups[g]]
        self.fr_maps = {m: json.load(open(f'{self.fr}/data/maps/{m}/map.json', encoding='utf-8')) for m in maps}
        self.plan_names(em_map_names, em_map_ids, em_layout_ids)
        imported_ids = {self.em_map_id(j['id']) for m, j in self.fr_maps.items() if m not in self.skip}
        valid_dest = imported_ids | em_map_ids | {'MAP_DYNAMIC'}

        made, pairs, sec_primary, layouts_done, kanto_maps = [], {}, {}, set(), []
        for m, j in self.fr_maps.items():
            if m in self.skip:
                continue
            em_name = self.map_rename.get(m, m)
            lay = self.fr_layouts[j['layout']]
            em_lid = self.layout_rename.get(lay['id'], lay['id'])
            if em_lid not in layouts_done:
                pair = (lay['primary_tileset'], lay['secondary_tileset'])
                if pair not in pairs:
                    # un secondaire RF utilisé avec deux primaires donne deux secondaires Kanto
                    variant = '' if sec_primary.setdefault(pair[1], pair[0]) == pair[0] else pair[0][len('gTileset_'):]
                    pairs[pair] = self.import_tileset_pair(*pair, variant)
                    made += pairs[pair][2]
                pname, sname, _ = pairs[pair]
                ldir = f'data/layouts/Kanto_{os.path.basename(os.path.dirname(lay["blockdata_filepath"]))}'
                os.makedirs(f'{self.em}/{ldir}', exist_ok=True)
                shutil.copy(f'{self.fr}/{lay["border_filepath"]}', f'{self.em}/{ldir}/border.bin')
                shutil.copy(f'{self.fr}/{lay["blockdata_filepath"]}', f'{self.em}/{ldir}/map.bin')
                em_layouts['layouts'].append({
                    'id': em_lid, 'name': 'Kanto_' + lay['name'], 'width': lay['width'], 'height': lay['height'],
                    'border_width': lay.get('border_width', 2), 'border_height': lay.get('border_height', 2),
                    'primary_tileset': pname, 'secondary_tileset': sname,
                    'border_filepath': f'{ldir}/border.bin', 'blockdata_filepath': f'{ldir}/map.bin'})
                layouts_done.add(em_lid)

            out = {'id': self.em_map_id(j['id']), 'name': em_name, 'layout': em_lid, 'music': self.music(j['music']),
                   'region_map_section': j['region_map_section']}
            for k in ('requires_flash', 'weather', 'map_type', 'allow_cycling', 'allow_escaping',
                      'allow_running', 'show_map_name', 'battle_scene'):
                out[k] = j[k]
            out['battle_scene'] = BATTLE_SCENE_ALIASES.get(out['battle_scene'], out['battle_scene'])
            if out['region_map_section'] not in em_mapsecs:
                self.warn('MAPSEC inconnu -> MAPSEC_NONE', out['region_map_section'])
                out['region_map_section'] = 'MAPSEC_NONE'
            conns = [dict(c, map=self.em_map_id(c['map'])) for c in (j.get('connections') or [])]
            out['connections'] = [c for c in conns if c['map'] in imported_ids] or None
            out['object_events'] = []
            warps = []
            for w in j.get('warp_events', []):
                w = dict(w, dest_map=self.em_map_id(w['dest_map']))
                if w['dest_map'] in valid_dest:
                    warps.append(w)
                else:
                    self.warn('warp vers une carte absente (retiré)', w['dest_map'])
            out['warp_events'] = warps
            out['coord_events'] = []
            out['bg_events'] = []
            os.makedirs(f'{self.em}/data/maps/{em_name}', exist_ok=True)
            write_json(f'{self.em}/data/maps/{em_name}/map.json', out)
            write_text(f'{self.em}/data/maps/{em_name}/scripts.inc', f'{em_name}_MapScripts::\n\t.byte 0\n')
            kanto_maps.append(em_name)

            g = 'gMapGroup_Kanto' + self.fr_group_of[m][len('gMapGroup_'):]
            if g not in groups:
                groups[g] = []
                groups['group_order'].append(g)
            groups[g].append(em_name)
            if out['connections']:
                groups['connections_include_order'].append(em_name)

        os.makedirs(f'{self.em}/data/kanto', exist_ok=True)
        write_text(f'{self.em}/data/kanto/scripts.inc',
                   '/* Scripts des cartes de Kanto (généré par tools/kanto/import_kanto.py) */\n'
                   + ''.join(f'\t.include "data/maps/{m}/scripts.inc"\n' for m in kanto_maps))
        write_json(layouts_path, em_layouts)
        write_json(groups_path, groups)
        self.write_tileset_sources(made)

        print(f'{len(kanto_maps)} cartes, {len(layouts_done)} layouts, {len(made)} tilesets')
        print('ignorées (versions Émeraude) :', sorted(self.skip))
        print('renommées :', self.map_rename)
        for k, v in self.warnings.items():
            print(f'{k} : {sorted(v)}')
        if self.unmapped_behaviors:
            print('comportements RF sans équivalent (-> MB_NORMAL) :', self.unmapped_behaviors)


if __name__ == '__main__':
    Importer(sys.argv[1], sys.argv[2]).run(sys.argv[3:])
