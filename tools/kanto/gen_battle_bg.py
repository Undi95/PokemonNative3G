#!/usr/bin/env python3
"""Importe les décors de combat de Rouge Feu.

Usage : gen_battle_bg.py FR_DIR EM_DIR

Reprend de src/battle_bg.c de RF les images des terrains et les tables sBattleTerrainTable et
sMapBattleSceneMapping (symboles préfixés Kanto, constantes KANTO_BATTLE_TERRAIN_* et
MAP_BATTLE_SCENE_KANTO_*), avec les options gbagfx de RF (-num_tiles).
Produit :
  src/data/graphics/kanto_battle_terrain.h   images et tables (inclus par src/kanto_battle_bg.c)
  graphics/kanto/battle_terrain/...          images et palettes copiées de RF
"""
import os, re, shutil, sys

fr, em = sys.argv[1], sys.argv[2]


def read(p):
    return open(p, encoding='utf-8').read()


src = read(f'{fr}/src/battle_bg.c')
rules = {}
mk = read(f'{fr}/graphics_file_rules.mk')
dirs = dict(re.findall(r'^(\w+)\s*:=\s*(\S+)', mk, re.M))
for target, flags in re.findall(r'^(\S+):\s*%\.\w+:\s*%\.png[ \t]*\n\t\$\(GFX\) \$< \$@ ([^\n]*)', mk, re.M):
    rules[re.sub(r'\$\((\w+)\)', lambda d: dirs.get(d.group(1), d.group(0)), target)] = flags.strip()


def incgfx(m):
    path = m.group(1)                       # graphics/battle_terrain/x/y.4bpp.lz
    base, ext = path.split('.', 1)
    ext = '.' + ext
    if ext == '.bin.lz':
        src_file, out_ext = base + '.bin', '.lz'
    elif ext == '.gbapal.lz':
        src_file, out_ext = base + '.pal', ext
    else:
        src_file, out_ext = base + '.png', ext
    dest = 'graphics/kanto/' + src_file[len('graphics/'):]
    os.makedirs(os.path.dirname(f'{em}/{dest}'), exist_ok=True)
    shutil.copy(f'{fr}/{src_file}', f'{em}/{dest}')
    flags = rules.get(base + '.4bpp') if ext == '.4bpp.lz' else None
    return f'INCGFX_U32("{dest}", "{out_ext}"' + (f', "{flags}")' if flags else ')')


shutil.rmtree(f'{em}/graphics/kanto/battle_terrain', ignore_errors=True)
gfx = re.findall(r'^static const u32 sBattleTerrain\w+\[\] = INCBIN_U32\("graphics/battle_terrain/[^"]+"\);$', src, re.M)
table = re.search(r'^static const struct BattleBackground sBattleTerrainTable\[\] = \{.*?^\};$', src, re.M | re.S).group(0)
mapping = re.search(r'^static const struct \{\n    u8 mapScene;.*?^\};$', src, re.M | re.S).group(0)

# constantes de terrain RF (include/constants/battle.h... de RF : enum ou #define)
consts = re.findall(r'#define (BATTLE_TERRAIN_\w+)\s+(\d+)', read(f'{fr}/include/constants/battle.h'))
if not consts:
    sys.exit('BATTLE_TERRAIN_* introuvables')

out = ['// Généré par tools/kanto/gen_battle_bg.py depuis src/battle_bg.c de Rouge Feu.',
       '// Ne pas modifier à la main.', '']
out += [f'#define KANTO_{n} {v}' for n, v in consts] + ['']
body = '\n'.join(gfx) + '\n\n' + table + '\n\n' + mapping + '\n'
body = re.sub(r'INCBIN_U32\("(graphics/battle_terrain/[^"]+)"\)', incgfx, body)
body = re.sub(r'\bsBattleTerrain', 'sKantoBattleTerrain', body)
body = re.sub(r'\bsMapBattleSceneMapping\b', 'sKantoMapBattleSceneMapping', body)
body = re.sub(r'\bBATTLE_TERRAIN_', 'KANTO_BATTLE_TERRAIN_', body)
body = re.sub(r'\bMAP_BATTLE_SCENE_(?!GYM\b|NORMAL\b)(\w+)', r'MAP_BATTLE_SCENE_KANTO_\1', body)
out.append(body)
with open(f'{em}/src/data/graphics/kanto_battle_terrain.h', 'w', encoding='utf-8', newline='\n') as f:
    f.write('\n'.join(out))
print(f'{len(gfx)} images, {len(consts)} terrains')
