#!/usr/bin/env python3
"""Génère src/kanto_field_door.c à partir du field_door.c de Rouge Feu.

Usage : gen_door.py FR_DIR EM_DIR

Les portes de RF (1x1 / 1x2, trames et tuiles propres) diffèrent de celles d'Émeraude ;
on reprend donc leur code tel quel, avec :
  - les fonctions exportées préfixées Kanto_ (field_door.c d'Émeraude les appelle
    quand la carte utilise un tileset de Kanto) ;
  - les METATILE_* de RF remplacés par leur valeur (les numéros de metatiles de
    Kanto sont conservés par l'import) ;
  - les graphismes copiés dans graphics/door_anims/kanto/.
"""
import os, re, shutil, sys

fr, em = sys.argv[1], sys.argv[2]
src = open(f'{fr}/src/field_door.c', encoding='utf-8').read()

labels = {}
for line in open(f'{fr}/include/constants/metatile_labels.h', encoding='utf-8'):
    m = re.match(r'\s*#define\s+(METATILE_\w+)\s+(0x[0-9A-Fa-f]+|\d+)', line)
    if m:
        labels[m.group(1)] = m.group(2)

src = src.replace('#include "constants/metatile_labels.h"\n', '#include "kanto_field_door.h"\n#include "day_night.h"\n')
src = re.sub(r'\bMETATILE_\w+\b', lambda m: labels[m.group(0)], src)
src = src.replace('MetatileBehavior_IsWarpDoor_2', 'MetatileBehavior_IsWarpDoor')  # MB_WARP_DOOR -> MB_ANIMATED_DOOR

os.makedirs(f'{em}/graphics/door_anims/kanto', exist_ok=True)
def gfx(m):
    name = m.group(1)
    shutil.copy(f'{fr}/graphics/door_anims/{name}.png', f'{em}/graphics/door_anims/kanto/{name}.png')
    return f'INCGFX_U8("graphics/door_anims/kanto/{name}.png", ".4bpp")'
src = re.sub(r'INCBIN_U8\("graphics/door_anims/(\w+)\.4bpp"\)', gfx, src)

for fn in ('FieldSetDoorOpened', 'FieldSetDoorClosed', 'FieldAnimateDoorClose', 'FieldAnimateDoorOpen',
           'FieldIsDoorAnimationRunning', 'GetDoorSoundEffect'):
    src = re.sub(rf'^(\w[\w ]*?)\b{fn}\(', rf'\1Kanto_{fn}(', src, flags=re.M)

# Pointeurs rangés dans deux cases s16 : faux en 64 bits -> ptr.genericPtr, comme le port le fait dans Émeraude
for a, b in (
    ('const struct DoorAnimFrame *frames = (struct DoorAnimFrame *)((u16)tFramesHi << 16 | (u16)tFramesLo);',
     'const struct DoorAnimFrame *frames = gTasks[taskId].ptr.genericPtr[0];'),
    ('const struct DoorGraphics *gfx = (struct DoorGraphics *)((u16)tGfxHi << 16 | (u16)tGfxLo);',
     'const struct DoorGraphics *gfx = gTasks[taskId].ptr.genericPtr[1];'),
    ('    tFramesLo = (uintptr_t)frames;\n    tFramesHi = (uintptr_t)frames >> 16;\n'
     '    tGfxLo = (uintptr_t)gfx;\n    tGfxHi = (uintptr_t)gfx >> 16;\n',
     '    gTasks[taskId].ptr.genericPtr[0] = (void *)frames;\n    gTasks[taskId].ptr.genericPtr[1] = (void *)gfx;\n'),
    # UBFIX : une porte 1x1 n'a que 4 tuiles par trame, en copier 8 lit après la dernière trame
    ('static void CopyDoorTilesToVram(const u8 *tiles);', 'static void CopyDoorTilesToVram(const u8 *tiles, u8 size);'),
    ('CopyDoorTilesToVram(&gfx->tiles[frames->tileOffset]);',
     'CopyDoorTilesToVram(&gfx->tiles[frames->tileOffset], gfx->size);'),
    ('static void CopyDoorTilesToVram(const u8 *tiles)\n{\n',
     'static void CopyDoorTilesToVram(const u8 *tiles, u8 size)\n{\n'
     '#ifdef UBFIX\n'
     '    // A 1x1 door only has 4 tiles per frame: copying 8 reads past the last frame\n'
     '    if (size == DOOR_SIZE_1x1)\n'
     '    {\n'
     '        CpuFastCopy(tiles, (void *)(VRAM + TILE_OFFSET_4BPP(DOOR_TILE_START)), 4 * TILE_SIZE_4BPP);\n'
     '        return;\n'
     '    }\n'
     '#endif\n'),
    # Cycle jour/nuit : la nuit, la vitre de la porte reste allumée pendant l'animation (day_night.c)
    ('static void DrawCurrentDoorAnimFrame(const struct DoorGraphics *gfx, int x, int y, const u8 *paletteNums)\n{\n',
     '// PokemonNative3G : DayNight_DoorAnimMetatile, la nuit la vitre de la porte reste allumée pendant l\'animation\n'
     'static void DrawCurrentDoorAnimFrame(const struct DoorGraphics *gfx, int x, int y, const u8 *paletteNums)\n{\n'),
    ('        BuildDoorTiles(tiles, DOOR_TILE_START, paletteNums);\n        DrawDoorMetatileAt(x, y - 1, tiles);\n',
     '        BuildDoorTiles(tiles, DOOR_TILE_START, paletteNums);\n'
     '        DayNight_DoorAnimMetatile(DOOR_TILE_START, x, y - 1);\n        DrawDoorMetatileAt(x, y - 1, tiles);\n'),
    ('    }\n\n    DrawDoorMetatileAt(x, y, tiles);\n',
     '    }\n\n    DayNight_DoorAnimMetatile(tiles[0] & 0x3FF, x, y);\n    DrawDoorMetatileAt(x, y, tiles);\n'),
    ('static void DrawClosedDoorTiles(const struct DoorGraphics *gfx, int x, int y)\n{\n',
     'static void DrawClosedDoorTiles(const struct DoorGraphics *gfx, int x, int y)\n{\n'
     '    DayNight_DoorClosed();\n'),
):
    assert a in src, a
    src = src.replace(a, b)

header = ('// Généré par tools/kanto/gen_door.py depuis src/field_door.c de Rouge Feu.\n'
          '// Ne pas modifier à la main : relancer le générateur.\n')
with open(f'{em}/src/kanto_field_door.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(header + src)
print('src/kanto_field_door.c généré')
