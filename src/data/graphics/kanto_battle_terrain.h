// Généré par tools/kanto/gen_battle_bg.py depuis src/battle_bg.c de Rouge Feu.
// Ne pas modifier à la main.

#define KANTO_BATTLE_TERRAIN_GRASS 0
#define KANTO_BATTLE_TERRAIN_LONG_GRASS 1
#define KANTO_BATTLE_TERRAIN_SAND 2
#define KANTO_BATTLE_TERRAIN_UNDERWATER 3
#define KANTO_BATTLE_TERRAIN_WATER 4
#define KANTO_BATTLE_TERRAIN_POND 5
#define KANTO_BATTLE_TERRAIN_MOUNTAIN 6
#define KANTO_BATTLE_TERRAIN_CAVE 7
#define KANTO_BATTLE_TERRAIN_BUILDING 8
#define KANTO_BATTLE_TERRAIN_PLAIN 9
#define KANTO_BATTLE_TERRAIN_LINK 10
#define KANTO_BATTLE_TERRAIN_GYM 11
#define KANTO_BATTLE_TERRAIN_LEADER 12
#define KANTO_BATTLE_TERRAIN_INDOOR_2 13
#define KANTO_BATTLE_TERRAIN_INDOOR_1 14
#define KANTO_BATTLE_TERRAIN_LORELEI 15
#define KANTO_BATTLE_TERRAIN_BRUNO 16
#define KANTO_BATTLE_TERRAIN_AGATHA 17
#define KANTO_BATTLE_TERRAIN_LANCE 18
#define KANTO_BATTLE_TERRAIN_CHAMPION 19

static const u32 sKantoBattleTerrainPalette_Grass[] = INCGFX_U32("graphics/kanto/battle_terrain/grass/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Grass[] = INCGFX_U32("graphics/kanto/battle_terrain/grass/terrain.png", ".4bpp.lz", "-num_tiles 98 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_Grass[] = INCGFX_U32("graphics/kanto/battle_terrain/grass/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_Grass[] = INCGFX_U32("graphics/kanto/battle_terrain/grass/anim.png", ".4bpp.lz");
static const u32 sKantoBattleTerrainAnimTilemap_Grass[] = INCGFX_U32("graphics/kanto/battle_terrain/grass/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_LongGrass[] = INCGFX_U32("graphics/kanto/battle_terrain/longgrass/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_LongGrass[] = INCGFX_U32("graphics/kanto/battle_terrain/longgrass/terrain.png", ".4bpp.lz", "-num_tiles 98 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_LongGrass[] = INCGFX_U32("graphics/kanto/battle_terrain/longgrass/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_LongGrass[] = INCGFX_U32("graphics/kanto/battle_terrain/longgrass/anim.png", ".4bpp.lz", "-num_tiles 133 -Wnum_tiles");
static const u32 sKantoBattleTerrainAnimTilemap_LongGrass[] = INCGFX_U32("graphics/kanto/battle_terrain/longgrass/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_Sand[] = INCGFX_U32("graphics/kanto/battle_terrain/sand/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Sand[] = INCGFX_U32("graphics/kanto/battle_terrain/sand/terrain.png", ".4bpp.lz", "-num_tiles 83 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_Sand[] = INCGFX_U32("graphics/kanto/battle_terrain/sand/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_Sand[] = INCGFX_U32("graphics/kanto/battle_terrain/sand/anim.png", ".4bpp.lz");
static const u32 sKantoBattleTerrainAnimTilemap_Sand[] = INCGFX_U32("graphics/kanto/battle_terrain/sand/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_Underwater[] = INCGFX_U32("graphics/kanto/battle_terrain/underwater/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Underwater[] = INCGFX_U32("graphics/kanto/battle_terrain/underwater/terrain.png", ".4bpp.lz", "-num_tiles 85 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_Underwater[] = INCGFX_U32("graphics/kanto/battle_terrain/underwater/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_Underwater[] = INCGFX_U32("graphics/kanto/battle_terrain/underwater/anim.png", ".4bpp.lz", "-num_tiles 26 -Wnum_tiles");
static const u32 sKantoBattleTerrainAnimTilemap_Underwater[] = INCGFX_U32("graphics/kanto/battle_terrain/underwater/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_Water[] = INCGFX_U32("graphics/kanto/battle_terrain/water/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Water[] = INCGFX_U32("graphics/kanto/battle_terrain/water/terrain.png", ".4bpp.lz", "-num_tiles 81 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_Water[] = INCGFX_U32("graphics/kanto/battle_terrain/water/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_Water[] = INCGFX_U32("graphics/kanto/battle_terrain/water/anim.png", ".4bpp.lz");
static const u32 sKantoBattleTerrainAnimTilemap_Water[] = INCGFX_U32("graphics/kanto/battle_terrain/water/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_Pond[] = INCGFX_U32("graphics/kanto/battle_terrain/pond/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Pond[] = INCGFX_U32("graphics/kanto/battle_terrain/pond/terrain.png", ".4bpp.lz", "-num_tiles 75 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_Pond[] = INCGFX_U32("graphics/kanto/battle_terrain/pond/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_Pond[] = INCGFX_U32("graphics/kanto/battle_terrain/pond/anim.png", ".4bpp.lz", "-num_tiles 36 -Wnum_tiles");
static const u32 sKantoBattleTerrainAnimTilemap_Pond[] = INCGFX_U32("graphics/kanto/battle_terrain/pond/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_Mountain[] = INCGFX_U32("graphics/kanto/battle_terrain/mountain/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Mountain[] = INCGFX_U32("graphics/kanto/battle_terrain/mountain/terrain.png", ".4bpp.lz");
static const u32 sKantoBattleTerrainTilemap_Mountain[] = INCGFX_U32("graphics/kanto/battle_terrain/mountain/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_Mountain[] = INCGFX_U32("graphics/kanto/battle_terrain/mountain/anim.png", ".4bpp.lz", "-num_tiles 47 -Wnum_tiles");
static const u32 sKantoBattleTerrainAnimTilemap_Mountain[] = INCGFX_U32("graphics/kanto/battle_terrain/mountain/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_Cave[] = INCGFX_U32("graphics/kanto/battle_terrain/cave/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Cave[] = INCGFX_U32("graphics/kanto/battle_terrain/cave/terrain.png", ".4bpp.lz", "-num_tiles 84 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_Cave[] = INCGFX_U32("graphics/kanto/battle_terrain/cave/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_Cave[] = INCGFX_U32("graphics/kanto/battle_terrain/cave/anim.png", ".4bpp.lz", "-num_tiles 106 -Wnum_tiles");
static const u32 sKantoBattleTerrainAnimTilemap_Cave[] = INCGFX_U32("graphics/kanto/battle_terrain/cave/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_Building[] = INCGFX_U32("graphics/kanto/battle_terrain/building/terrain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Building[] = INCGFX_U32("graphics/kanto/battle_terrain/building/terrain.png", ".4bpp.lz", "-num_tiles 77 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_Building[] = INCGFX_U32("graphics/kanto/battle_terrain/building/terrain.bin", ".lz");
static const u32 sKantoBattleTerrainAnimTiles_Building[] = INCGFX_U32("graphics/kanto/battle_terrain/building/anim.png", ".4bpp.lz");
static const u32 sKantoBattleTerrainAnimTilemap_Building[] = INCGFX_U32("graphics/kanto/battle_terrain/building/anim.bin", ".lz");
static const u32 sKantoBattleTerrainPalette_Link[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/link.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Gym[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/gym.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Leader[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/leader.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Indoor2[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/2.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Indoor1[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/1.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Lorelei[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/lorelei.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Bruno[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/bruno.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Agatha[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/agatha.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Lance[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/lance.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Champion[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/champion.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainPalette_Plain[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/plain.pal", ".gbapal.lz");
static const u32 sKantoBattleTerrainTiles_Indoor[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/terrain.png", ".4bpp.lz", "-num_tiles 77 -Wnum_tiles");
static const u32 sKantoBattleTerrainTilemap_Indoor[] = INCGFX_U32("graphics/kanto/battle_terrain/indoor/terrain.bin", ".lz");

static const struct BattleBackground sKantoBattleTerrainTable[] = {
    [KANTO_BATTLE_TERRAIN_GRASS] =
    {
        .tileset = sKantoBattleTerrainTiles_Grass,
        .tilemap = sKantoBattleTerrainTilemap_Grass,
        .entryTileset = sKantoBattleTerrainAnimTiles_Grass,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Grass,
        .palette = sKantoBattleTerrainPalette_Grass
    },
    [KANTO_BATTLE_TERRAIN_LONG_GRASS] =
    {
        .tileset = sKantoBattleTerrainTiles_LongGrass,
        .tilemap = sKantoBattleTerrainTilemap_LongGrass,
        .entryTileset = sKantoBattleTerrainAnimTiles_LongGrass,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_LongGrass,
        .palette = sKantoBattleTerrainPalette_LongGrass
    },
    [KANTO_BATTLE_TERRAIN_SAND] =
    {
        .tileset = sKantoBattleTerrainTiles_Sand,
        .tilemap = sKantoBattleTerrainTilemap_Sand,
        .entryTileset = sKantoBattleTerrainAnimTiles_Sand,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Sand,
        .palette = sKantoBattleTerrainPalette_Sand
    },
    [KANTO_BATTLE_TERRAIN_UNDERWATER] =
    {
        .tileset = sKantoBattleTerrainTiles_Underwater,
        .tilemap = sKantoBattleTerrainTilemap_Underwater,
        .entryTileset = sKantoBattleTerrainAnimTiles_Underwater,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Underwater,
        .palette = sKantoBattleTerrainPalette_Underwater
    },
    [KANTO_BATTLE_TERRAIN_WATER] =
    {
        .tileset = sKantoBattleTerrainTiles_Water,
        .tilemap = sKantoBattleTerrainTilemap_Water,
        .entryTileset = sKantoBattleTerrainAnimTiles_Water,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Water,
        .palette = sKantoBattleTerrainPalette_Water
    },
    [KANTO_BATTLE_TERRAIN_POND] =
    {
        .tileset = sKantoBattleTerrainTiles_Pond,
        .tilemap = sKantoBattleTerrainTilemap_Pond,
        .entryTileset = sKantoBattleTerrainAnimTiles_Pond,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Pond,
        .palette = sKantoBattleTerrainPalette_Pond
    },
    [KANTO_BATTLE_TERRAIN_MOUNTAIN] =
    {
        .tileset = sKantoBattleTerrainTiles_Mountain,
        .tilemap = sKantoBattleTerrainTilemap_Mountain,
        .entryTileset = sKantoBattleTerrainAnimTiles_Mountain,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Mountain,
        .palette = sKantoBattleTerrainPalette_Mountain
    },
    [KANTO_BATTLE_TERRAIN_CAVE] =
    {
        .tileset = sKantoBattleTerrainTiles_Cave,
        .tilemap = sKantoBattleTerrainTilemap_Cave,
        .entryTileset = sKantoBattleTerrainAnimTiles_Cave,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Cave,
        .palette = sKantoBattleTerrainPalette_Cave
    },
    [KANTO_BATTLE_TERRAIN_BUILDING] =
    {
        .tileset = sKantoBattleTerrainTiles_Building,
        .tilemap = sKantoBattleTerrainTilemap_Building,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Building
    },
    [KANTO_BATTLE_TERRAIN_PLAIN] =
    {
        .tileset = sKantoBattleTerrainTiles_Building,
        .tilemap = sKantoBattleTerrainTilemap_Building,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Plain
    },
    [KANTO_BATTLE_TERRAIN_LINK] =
    {
        .tileset = sKantoBattleTerrainTiles_Building,
        .tilemap = sKantoBattleTerrainTilemap_Building,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Link
    },
    [KANTO_BATTLE_TERRAIN_GYM] =
    {
        .tileset = sKantoBattleTerrainTiles_Building,
        .tilemap = sKantoBattleTerrainTilemap_Building,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Gym
    },
    [KANTO_BATTLE_TERRAIN_LEADER] =
    {
        .tileset = sKantoBattleTerrainTiles_Building,
        .tilemap = sKantoBattleTerrainTilemap_Building,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Leader
    },
    [KANTO_BATTLE_TERRAIN_INDOOR_2] =
    {
        .tileset = sKantoBattleTerrainTiles_Indoor,
        .tilemap = sKantoBattleTerrainTilemap_Indoor,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Indoor2
    },
    [KANTO_BATTLE_TERRAIN_INDOOR_1] =
    {
        .tileset = sKantoBattleTerrainTiles_Indoor,
        .tilemap = sKantoBattleTerrainTilemap_Indoor,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Indoor1
    },
    [KANTO_BATTLE_TERRAIN_LORELEI] =
    {
        .tileset = sKantoBattleTerrainTiles_Indoor,
        .tilemap = sKantoBattleTerrainTilemap_Indoor,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Lorelei
    },
    [KANTO_BATTLE_TERRAIN_BRUNO] =
    {
        .tileset = sKantoBattleTerrainTiles_Indoor,
        .tilemap = sKantoBattleTerrainTilemap_Indoor,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Bruno
    },
    [KANTO_BATTLE_TERRAIN_AGATHA] =
    {
        .tileset = sKantoBattleTerrainTiles_Indoor,
        .tilemap = sKantoBattleTerrainTilemap_Indoor,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Agatha
    },
    [KANTO_BATTLE_TERRAIN_LANCE] =
    {
        .tileset = sKantoBattleTerrainTiles_Indoor,
        .tilemap = sKantoBattleTerrainTilemap_Indoor,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Lance
    },
    [KANTO_BATTLE_TERRAIN_CHAMPION] =
    {
        .tileset = sKantoBattleTerrainTiles_Indoor,
        .tilemap = sKantoBattleTerrainTilemap_Indoor,
        .entryTileset = sKantoBattleTerrainAnimTiles_Building,
        .entryTilemap = sKantoBattleTerrainAnimTilemap_Building,
        .palette = sKantoBattleTerrainPalette_Champion
    }
};

static const struct {
    u8 mapScene;
    u8 battleTerrain;
} sKantoMapBattleSceneMapping[] = {
    {MAP_BATTLE_SCENE_GYM,      KANTO_BATTLE_TERRAIN_GYM},
    {MAP_BATTLE_SCENE_KANTO_INDOOR_1, KANTO_BATTLE_TERRAIN_INDOOR_1},
    {MAP_BATTLE_SCENE_KANTO_INDOOR_2, KANTO_BATTLE_TERRAIN_INDOOR_2},
    {MAP_BATTLE_SCENE_KANTO_LORELEI,  KANTO_BATTLE_TERRAIN_LORELEI},
    {MAP_BATTLE_SCENE_KANTO_BRUNO,    KANTO_BATTLE_TERRAIN_BRUNO},
    {MAP_BATTLE_SCENE_KANTO_AGATHA,   KANTO_BATTLE_TERRAIN_AGATHA},
    {MAP_BATTLE_SCENE_KANTO_LANCE,    KANTO_BATTLE_TERRAIN_LANCE},
    {MAP_BATTLE_SCENE_KANTO_LINK,     KANTO_BATTLE_TERRAIN_LINK}
};
