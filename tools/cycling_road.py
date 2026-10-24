#!/usr/bin/env python3
"""Piste Cyclable (PokemonNative3G, 2026-10-24) : les tuiles en pente de RF (MB_CYCLING_ROAD_PULL_DOWN(_GRASS),
tileset secondaire de Céladopole) étaient devenues MB_NORMAL à l'import. Elles reprennent deux comportements
inutilisés d'Émeraude (0x1D, 0x1E) ; à vélo (Course ou Cross), on y descend tout seul comme dans RF
(bike.c : BikeInputHandler_Normal/Slope, BikeTransition_Downhill/Uphill). Relancer ne fait rien de plus.
Usage : python tools/cycling_road.py   (depuis la racine du projet)
"""
import struct

FR = '../decomps/pokerougefeu'


def rd(p):
    return open(p, encoding='utf-8', newline='').read()


def wr(p, t):
    open(p, 'w', encoding='utf-8', newline='').write(t)


def once(p, a, b):
    t = rd(p)
    if '\r\n' in t:
        a, b = a.replace('\n', '\r\n'), b.replace('\n', '\r\n')
    if b in t:
        return
    assert t.count(a) == 1, (p, a)
    wr(p, t.replace(a, b))


once('include/constants/metatile_behaviors.h', '    MB_UNUSED_1D,\n    MB_UNUSED_1E,\n',
     '    MB_CYCLING_ROAD_PULL_DOWN,       // PokemonNative3G : RF (Piste Cyclable)\n'
     '    MB_CYCLING_ROAD_PULL_DOWN_GRASS, // PokemonNative3G : RF\n')
once('src/metatile_behavior.c', '    [MB_TALL_GRASS]                      = TILE_FLAG_UNUSED | TILE_FLAG_HAS_ENCOUNTERS,\n',
     '    [MB_TALL_GRASS]                      = TILE_FLAG_UNUSED | TILE_FLAG_HAS_ENCOUNTERS,\n'
     '    [MB_CYCLING_ROAD_PULL_DOWN_GRASS]    = TILE_FLAG_UNUSED | TILE_FLAG_HAS_ENCOUNTERS, // PokemonNative3G : RF\n')
once('src/metatile_behavior.c', '''bool8 MetatileBehavior_IsTallGrass(u8 metatileBehavior)
{
    if (metatileBehavior == MB_TALL_GRASS)
''', '''// PokemonNative3G : RF
bool32 MetatileBehavior_IsCyclingRoadPullDownTile(u8 metatileBehavior)
{
    if (metatileBehavior >= MB_CYCLING_ROAD_PULL_DOWN && metatileBehavior <= MB_CYCLING_ROAD_PULL_DOWN_GRASS)
        return TRUE;
    else
        return FALSE;
}

bool8 MetatileBehavior_IsTallGrass(u8 metatileBehavior)
{
    if (metatileBehavior == MB_TALL_GRASS || metatileBehavior == MB_CYCLING_ROAD_PULL_DOWN_GRASS) // PokemonNative3G : RF
''')
once('include/metatile_behavior.h', 'bool8 MetatileBehavior_IsTallGrass(u8 metatileBehavior);\n',
     'bool8 MetatileBehavior_IsTallGrass(u8 metatileBehavior);\n'
     'bool32 MetatileBehavior_IsCyclingRoadPullDownTile(u8 metatileBehavior);\n')
once('src/bike.c', '''void MovePlayerOnBike(u8 direction, u16 newKeys, u16 heldKeys)
{
    if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_MACH_BIKE)
''', '''// PokemonNative3G : pentes de la Piste Cyclable, comme RF (bike.c : BikeInputHandler_Normal/Slope,
// BikeTransition_Downhill/Uphill) : sans B, on descend tout seul ; avec une direction, on avance normalement.
static bool8 MovePlayerOnCyclingRoadSlope(u8 direction, u16 heldKeys)
{
    if (!MetatileBehavior_IsCyclingRoadPullDownTile(gObjectEvents[gPlayerAvatar.objectEventId].currentMetatileBehavior))
        return FALSE;
    if (!(heldKeys & B_BUTTON) && direction < DIR_NORTH)
    {
        u8 collision = GetBikeCollision(DIR_SOUTH);

        if (collision == COLLISION_NONE)
            PlayerWalkFaster(DIR_SOUTH);
        else if (collision == COLLISION_LEDGE_JUMP)
            PlayerJumpLedge(DIR_SOUTH);
        else
            return FALSE;
    }
    else if (direction != DIR_NONE)
    {
        if (GetBikeCollision(direction) == COLLISION_NONE)
            PlayerWalkNormal(direction);
        else
            return FALSE;
    }
    else
    {
        return FALSE;
    }
    gPlayerAvatar.bikeSpeed = PLAYER_SPEED_STANDING;
    gPlayerAvatar.runningState = MOVING;
    return TRUE;
}

void MovePlayerOnBike(u8 direction, u16 newKeys, u16 heldKeys)
{
    if (MovePlayerOnCyclingRoadSlope(direction, heldKeys))
        return;
    if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_MACH_BIKE)
''')

# Tuiles : tileset secondaire de Céladopole (attributs RF 32 bits -> Émeraude 16 bits, décalage 640-512 = 128
# métatuiles du primaire RF recopiées en tête du secondaire, cf. tools/kanto/import_kanto.py)
names = [l.split(',')[0].strip() for l in rd('include/constants/metatile_behaviors.h').split('enum')[1].split('\n')
         if l.strip().startswith('MB_')]
em = {n: i for i, n in enumerate(names)}
fr_attrs = open(f'{FR}/data/tilesets/secondary/celadon_city/metatile_attributes.bin', 'rb').read()
p = 'data/tilesets/secondary/kanto_celadon_city/metatile_attributes.bin'
out = bytearray(open(p, 'rb').read())
n = 0
for i, (a,) in enumerate(struct.iter_unpack('<I', fr_attrs)):
    b = a & 0x1FF
    if b in (0xD0, 0xD1):
        mb = em['MB_CYCLING_ROAD_PULL_DOWN' if b == 0xD0 else 'MB_CYCLING_ROAD_PULL_DOWN_GRASS']
        off = (128 + i) * 2
        old = struct.unpack_from('<H', out, off)[0]
        struct.pack_into('<H', out, off, (old & ~0xFF) | mb)
        n += 1
open(p, 'wb').write(out)
print('ok', n, 'tuiles', hex(em['MB_CYCLING_ROAD_PULL_DOWN']))
