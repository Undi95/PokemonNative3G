// Rouge Feu : pokedex_area_markers.c + wild_pokemon_area.c (zones du Pokédex de Kanto)
#include "global.h"
#include "decompress.h"
#include "event_data.h"
#include "kanto_pokedex.h"
#include "malloc.h"
#include "overworld.h"
#include "palette.h"
#include "pokedex.h"
#include "roamer.h"
#include "sprite.h"
#include "task.h"
#include "wild_encounter.h"
#include "constants/region_map_sections.h"
#include "constants/maps.h"
#include "constants/kanto_flags_vars.h"


/*
    Controls the red ellipse markers that appear on the pokedex maps to show where a species is found.
    All of the markers together are a single sprite, with each individual marker being represented by
    a subsprite of the necessary size and shape.

    The data about each area marker is in sAreaMarkers, each specified by a DEX_AREA constant.
    A MAPSEC is associated with a DEX_AREA constant by a series of arrays in wild_pokemon_area.c
*/

struct PAM_TaskData
{
    struct SubspriteTable subsprites;
    void *buffer;
    u8 unused;
    u8 spriteId;
    u16 tilesTag;
    u16 paletteTag; // Never read
};

enum {
    MARKER_CIRCULAR,
    MARKER_SMALL_H,
    MARKER_SMALL_V,
    MARKER_MED_H,
    MARKER_MED_V,
    MARKER_LARGE_H,
    MARKER_LARGE_V,
};

static const u16 sMarkerPal[] = INCGFX_U16("graphics/kanto/pokedex/area_markers/marker.pal", ".gbapal");
static const u32 sMarkerTiles[] = INCGFX_U32("graphics/kanto/pokedex/area_markers/marker.png", ".4bpp.lz");

static const struct Subsprite sSubsprite_Circular = {
    .size = SPRITE_SIZE(8x8),
    .shape = SPRITE_SHAPE(8x8),
    .priority = 1,
    .tileOffset = 0
};

static const struct Subsprite sSubsprite_SmallHorizontal = {
    .size = SPRITE_SIZE(16x8),
    .shape = SPRITE_SHAPE(16x8),
    .priority = 1,
    .tileOffset = 1
};

static const struct Subsprite sSubsprite_SmallVertical = {
    .size = SPRITE_SIZE(8x16),
    .shape = SPRITE_SHAPE(8x16),
    .priority = 1,
    .tileOffset = 3
};

static const struct Subsprite sSubsprite_MediumHorizontal = {
    .size = SPRITE_SIZE(32x16),
    .shape = SPRITE_SHAPE(32x16),
    .priority = 1,
    .tileOffset = 5
};

static const struct Subsprite sSubsprite_MediumVertical = {
    .size = SPRITE_SIZE(16x32),
    .shape = SPRITE_SHAPE(16x32),
    .priority = 1,
    .tileOffset = 13
};

static const struct Subsprite sSubsprite_LargeHorizontal = {
    .size = SPRITE_SIZE(32x16),
    .shape = SPRITE_SHAPE(32x16),
    .priority = 1,
    .tileOffset = 21
};

static const struct Subsprite sSubsprite_LargeVertical = {
    .size = SPRITE_SIZE(16x32),
    .shape = SPRITE_SHAPE(16x32),
    .priority = 1,
    .tileOffset = 29
};


static const struct Subsprite *const sSubsprites[] = {
    [MARKER_CIRCULAR] = &sSubsprite_Circular,
    [MARKER_SMALL_H]  = &sSubsprite_SmallHorizontal,
    [MARKER_SMALL_V]  = &sSubsprite_SmallVertical,
    [MARKER_MED_H]    = &sSubsprite_MediumHorizontal,
    [MARKER_MED_V]    = &sSubsprite_MediumVertical,
    [MARKER_LARGE_H]  = &sSubsprite_LargeHorizontal,
    [MARKER_LARGE_V]  = &sSubsprite_LargeVertical
};

static const s8 sAreaMarkers[][4] = {
                                  // Marker,          x,    y
    [DEX_AREA_NONE]             = {},
    [DEX_AREA_PALLET_TOWN]      = { MARKER_CIRCULAR,  54,  44 },
    [DEX_AREA_VIRIDIAN_CITY]    = { MARKER_CIRCULAR,  54,  28 },
    [DEX_AREA_PEWTER_CITY]      = { MARKER_CIRCULAR,  54,  12 },
    [DEX_AREA_CERULEAN_CITY]    = { MARKER_CIRCULAR,  92,  12 },
    [DEX_AREA_LAVENDER_TOWN]    = { MARKER_CIRCULAR, 110,  24 },
    [DEX_AREA_VERMILION_CITY]   = { MARKER_CIRCULAR,  92,  36 },
    [DEX_AREA_CELADON_CITY]     = { MARKER_CIRCULAR,  76,  24 },
    [DEX_AREA_FUCHSIA_CITY]     = { MARKER_CIRCULAR,  78,  52 },
    [DEX_AREA_CINNABAR_ISLAND]  = { MARKER_CIRCULAR,  54,  62 },
    [DEX_AREA_INDIGO_PLATEAU]   = { MARKER_CIRCULAR,  42,   2 },
    [DEX_AREA_SAFFRON_CITY]     = { MARKER_CIRCULAR,  92,  24 },
    [DEX_AREA_ROUTE_1]          = { MARKER_SMALL_V,   54,  32 },
    [DEX_AREA_ROUTE_2]          = { MARKER_SMALL_V,   54,  16 },
    [DEX_AREA_ROUTE_3]          = { MARKER_SMALL_H,   61,  12 },
    [DEX_AREA_ROUTE_4]          = { MARKER_SMALL_H,   77,  12 },
    [DEX_AREA_ROUTE_5]          = { MARKER_CIRCULAR,  92,  18 },
    [DEX_AREA_ROUTE_6]          = { MARKER_CIRCULAR,  92,  30 },
    [DEX_AREA_ROUTE_7]          = { MARKER_CIRCULAR,  84,  24 },
    [DEX_AREA_ROUTE_8]          = { MARKER_SMALL_H,   98,  24 },
    [DEX_AREA_ROUTE_9]          = { MARKER_SMALL_H,   98,  12 },
    [DEX_AREA_ROUTE_10]         = { MARKER_SMALL_V,  110,  12 },
    [DEX_AREA_ROUTE_11]         = { MARKER_SMALL_H,   98,  36 },
    [DEX_AREA_ROUTE_12]         = { MARKER_MED_V,    106,  25 },
    [DEX_AREA_ROUTE_13]         = { MARKER_SMALL_H,  100,  46 },
    [DEX_AREA_ROUTE_14]         = { MARKER_SMALL_V,   94,  45 },
    [DEX_AREA_ROUTE_15]         = { MARKER_SMALL_H,   85,  52 },
    [DEX_AREA_ROUTE_16]         = { MARKER_CIRCULAR,  68,  24 },
    [DEX_AREA_ROUTE_17]         = { MARKER_MED_V,     62,  26 },
    [DEX_AREA_ROUTE_18]         = { MARKER_SMALL_H,   64,  52 },
    [DEX_AREA_ROUTE_19]         = { MARKER_CIRCULAR,  78,  60 },
    [DEX_AREA_ROUTE_20]         = { MARKER_MED_H,     55,  58 },
    [DEX_AREA_ROUTE_21]         = { MARKER_SMALL_V,   54,  50 },
    [DEX_AREA_ROUTE_22]         = { MARKER_SMALL_H,   40,  28 },
    [DEX_AREA_ROUTE_23]         = { MARKER_MED_V,     38,   4 },
    [DEX_AREA_ROUTE_24]         = { MARKER_CIRCULAR,  92,   4 },
    [DEX_AREA_ROUTE_25]         = { MARKER_MED_H,     90,  -2 },
    [DEX_AREA_VIRIDIAN_FOREST]  = { MARKER_CIRCULAR,  51,  20 },
    [DEX_AREA_DIGLETTS_CAVE]    = { MARKER_SMALL_H,   61,  18 },
    [DEX_AREA_MT_MOON]          = { MARKER_CIRCULAR,  72,   8 },
    [DEX_AREA_CERULEAN_CAVE]    = { MARKER_CIRCULAR,  87,   8 },
    [DEX_AREA_ROCK_TUNNEL]      = { MARKER_CIRCULAR, 112,  14 },
    [DEX_AREA_POWER_PLANT]      = { MARKER_CIRCULAR, 113,  20 },
    [DEX_AREA_POKEMON_TOWER]    = { MARKER_CIRCULAR, 113,  25 },
    [DEX_AREA_SAFARI_ZONE]      = { MARKER_SMALL_H,   78,  44 },
    [DEX_AREA_SEAFOAM_ISLANDS]  = { MARKER_CIRCULAR,  65,  60 },
    [DEX_AREA_POKEMON_MANSION]  = { MARKER_CIRCULAR,  52,  62 },
    [DEX_AREA_VICTORY_ROAD]     = { MARKER_CIRCULAR,  45,   7 },
    [DEX_AREA_ONE_ISLAND]       = { MARKER_CIRCULAR,  10,  10 },
    [DEX_AREA_TWO_ISLAND]       = { MARKER_CIRCULAR,  12,  35 },
    [DEX_AREA_THREE_ISLAND]     = { MARKER_CIRCULAR,  14,  52 },
    [DEX_AREA_FOUR_ISLAND]      = { MARKER_CIRCULAR,  12,  84 },
    [DEX_AREA_FIVE_ISLAND]      = { MARKER_CIRCULAR,  45,  81 },
    [DEX_AREA_SIX_ISLAND]       = { MARKER_CIRCULAR,  76,  84 },
    [DEX_AREA_SEVEN_ISLAND]     = { MARKER_CIRCULAR, 104,  82 },
    [DEX_AREA_KINDLE_ROAD]      = { MARKER_SMALL_V,   14,   2 },
    [DEX_AREA_TREASURE_BEACH]   = { MARKER_CIRCULAR,  10,  15 },
    [DEX_AREA_CAPE_BRINK]       = { MARKER_CIRCULAR,  12,  29 },
    [DEX_AREA_BOND_BRIDGE]      = { MARKER_SMALL_H,    2,  52 },
    [DEX_AREA_THREE_ISLE_PATH]  = { MARKER_SMALL_H,   12,  56 },
    [DEX_AREA_RESORT_GORGEOUS]  = { MARKER_SMALL_H,   44,  74 },
    [DEX_AREA_WATER_LABYRINTH]  = { MARKER_SMALL_H,   36,  78 },
    [DEX_AREA_FIVE_ISLE_MEADOW] = { MARKER_SMALL_V,   48,  80 },
    [DEX_AREA_MEMORIAL_PILLAR]  = { MARKER_SMALL_V,   52,  86 },
    [DEX_AREA_OUTCAST_ISLAND]   = { MARKER_CIRCULAR,  72,  74 },
    [DEX_AREA_GREEN_PATH]       = { MARKER_SMALL_H,   72,  78 },
    [DEX_AREA_WATER_PATH]       = { MARKER_SMALL_V,   81,  80 },
    [DEX_AREA_RUIN_VALLEY]      = { MARKER_CIRCULAR,  76,  92 },
    [DEX_AREA_TRAINER_TOWER]    = { MARKER_CIRCULAR, 104,  75 },
    [DEX_AREA_CANYON_ENTRANCE]  = { MARKER_CIRCULAR, 104,  86 },
    [DEX_AREA_SEVAULT_CANYON]   = { MARKER_SMALL_V,  108,  83 },
    [DEX_AREA_TANOBY_RUINS]     = { MARKER_MED_H,     96,  90 },
    [DEX_AREA_MT_EMBER]         = { MARKER_CIRCULAR,  14,   1 },
    [DEX_AREA_BERRY_FOREST]     = { MARKER_CIRCULAR,   5,  52 },
    [DEX_AREA_ICEFALL_CAVE]     = { MARKER_CIRCULAR,  13,  80 },
    [DEX_AREA_LOST_CAVE]        = { MARKER_CIRCULAR,  54,  74 },
    [DEX_AREA_ALTERING_CAVE]    = { MARKER_CIRCULAR,  69,  73 },
    [DEX_AREA_PATTERN_BUSH]     = { MARKER_CIRCULAR,  76,  77 },
    [DEX_AREA_DOTTED_HOLE]      = { MARKER_CIRCULAR,  73,  95 },
    [DEX_AREA_TANOBY_CHAMBER]   = { MARKER_MED_H,     96,  90 },
};

static void Task_ShowAreaMarkers(u8 taskId)
{
    struct PAM_TaskData * data = (void *)gTasks[taskId].data;
    gSprites[data->spriteId].invisible = FALSE;
}

u8 CreatePokedexAreaMarkers(u16 species, u16 tilesTag, u8 palIdx, u8 y)
{
    struct SpriteTemplate spriteTemplate;
    struct CompressedSpriteSheet spriteSheet;
    u8 taskId;
    struct PAM_TaskData * data;
    struct Subsprite * subsprites;

    // Load gfx
    spriteSheet.data = sMarkerTiles;
    spriteSheet.size = 0x4A0;
    spriteSheet.tag = tilesTag;
    LoadCompressedSpriteSheet(&spriteSheet);
    LoadPalette(sMarkerPal, OBJ_PLTT_ID(palIdx), sizeof(sMarkerPal));

    // Get marker subsprites
    taskId = CreateTask(Task_ShowAreaMarkers, 0);
    data = (void *)gTasks[taskId].data;
    data->unused = 0;
    data->tilesTag = tilesTag;
    data->paletteTag = TAG_NONE;
    subsprites = Alloc(120 * sizeof(struct Subsprite));
    data->buffer = subsprites;
    data->subsprites.subsprites = subsprites;
    data->subsprites.subspriteCount = GetSpeciesPokedexAreaMarkers(species, subsprites);

    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_BD);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(12, 8));
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_CLR);

    // Set marker subsprites on full sprite
    spriteTemplate = gDummySpriteTemplate;
    spriteTemplate.tileTag = tilesTag;
    data->spriteId = CreateSprite(&spriteTemplate, 104, y + 32, 0);
    SetSubspriteTables(&gSprites[data->spriteId], &data->subsprites);
    gSprites[data->spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
    gSprites[data->spriteId].oam.paletteNum = palIdx;
    gSprites[data->spriteId].subspriteTableNum = 0;
    gSprites[data->spriteId].invisible = TRUE;

    // Show markers
    HideBg(1);
    SetBgAttribute(1, BG_ATTR_CHARBASEINDEX, 0);
    FillBgTilemapBufferRect_Palette0(1, 0x00F, 0, 0, 30, 20);
    CopyBgTilemapBufferToVram(1);
    ShowBg(1);
    return taskId;
}

void DestroyPokedexAreaMarkers(u8 taskId)
{
    struct PAM_TaskData * data = (void *)gTasks[taskId].data;
    FreeSpriteTilesByTag(data->tilesTag);
    DestroySprite(&gSprites[data->spriteId]);
    Free(data->buffer);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ);
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    HideBg(1);
    SetBgAttribute(1, BG_ATTR_CHARBASEINDEX, 2);
    FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
    CopyBgTilemapBufferToVram(1);
    ShowBg(1);
    DestroyTask(taskId);
}

void GetAreaMarkerSubsprite(s32 i, s32 dexArea, struct Subsprite * subsprites)
{
    subsprites[i] = *sSubsprites[sAreaMarkers[dexArea][0]];
    subsprites[i].x = sAreaMarkers[dexArea][1];
    subsprites[i].y = sAreaMarkers[dexArea][2];
}

u8 GetNumPokedexAreaMarkers(u8 taskId)
{
    struct PAM_TaskData * data = (void *)gTasks[taskId].data;
    return data->subsprites.subspriteCount;
}


struct RoamerPair
{
    u16 roamer;
    u16 starter;
};

static s32 GetRoamerIndex(u16 species);
static s32 GetRoamerPokedexAreaMarkers(u16 species, struct Subsprite * subsprites);
static bool32 IsSpeciesOnMap(const struct WildPokemonHeader * data, s32 species);
static bool32 IsSpeciesInEncounterTable(const struct WildPokemonInfo * pokemon, s32 species, s32 count);
static u16 GetMapSecIdFromWildMonHeader(const struct WildPokemonHeader * header);
static bool32 FindDexAreaByMapSec(u16 mapSecId, const u16 (*lut)[2], s32 count, s32 * lutIdx_p, u16 * tableIdx_p);

static const u16 sDexAreas_Kanto[][2] = {
    { MAPSEC_PALLET_TOWN,         DEX_AREA_PALLET_TOWN },
    { MAPSEC_VIRIDIAN_CITY,       DEX_AREA_VIRIDIAN_CITY },
    { MAPSEC_PEWTER_CITY,         DEX_AREA_PEWTER_CITY },
    { MAPSEC_CERULEAN_CITY,       DEX_AREA_CERULEAN_CITY },
    { MAPSEC_LAVENDER_TOWN,       DEX_AREA_LAVENDER_TOWN },
    { MAPSEC_VERMILION_CITY,      DEX_AREA_VERMILION_CITY },
    { MAPSEC_CELADON_CITY,        DEX_AREA_CELADON_CITY },
    { MAPSEC_FUCHSIA_CITY,        DEX_AREA_FUCHSIA_CITY },
    { MAPSEC_CINNABAR_ISLAND,     DEX_AREA_CINNABAR_ISLAND },
    { MAPSEC_INDIGO_PLATEAU,      DEX_AREA_INDIGO_PLATEAU },
    { MAPSEC_SAFFRON_CITY,        DEX_AREA_SAFFRON_CITY },
    { MAPSEC_ROUTE_4_POKECENTER,  DEX_AREA_ROUTE_4 },
    { MAPSEC_ROUTE_10_POKECENTER, DEX_AREA_ROUTE_10 },
    { MAPSEC_ROUTE_1,             DEX_AREA_ROUTE_1 },
    { MAPSEC_ROUTE_2,             DEX_AREA_ROUTE_2 },
    { MAPSEC_ROUTE_3,             DEX_AREA_ROUTE_3 },
    { MAPSEC_ROUTE_4,             DEX_AREA_ROUTE_4 },
    { MAPSEC_ROUTE_5,             DEX_AREA_ROUTE_5 },
    { MAPSEC_ROUTE_6,             DEX_AREA_ROUTE_6 },
    { MAPSEC_ROUTE_7,             DEX_AREA_ROUTE_7 },
    { MAPSEC_ROUTE_8,             DEX_AREA_ROUTE_8 },
    { MAPSEC_ROUTE_9,             DEX_AREA_ROUTE_9 },
    { MAPSEC_ROUTE_10,            DEX_AREA_ROUTE_10 },
    { MAPSEC_ROUTE_11,            DEX_AREA_ROUTE_11 },
    { MAPSEC_ROUTE_12,            DEX_AREA_ROUTE_12 },
    { MAPSEC_ROUTE_13,            DEX_AREA_ROUTE_13 },
    { MAPSEC_ROUTE_14,            DEX_AREA_ROUTE_14 },
    { MAPSEC_ROUTE_15,            DEX_AREA_ROUTE_15 },
    { MAPSEC_ROUTE_16,            DEX_AREA_ROUTE_16 },
    { MAPSEC_ROUTE_17,            DEX_AREA_ROUTE_17 },
    { MAPSEC_ROUTE_18,            DEX_AREA_ROUTE_18 },
    { MAPSEC_ROUTE_19,            DEX_AREA_ROUTE_19 },
    { MAPSEC_ROUTE_20,            DEX_AREA_ROUTE_20 },
    { MAPSEC_ROUTE_21,            DEX_AREA_ROUTE_21 },
    { MAPSEC_ROUTE_22,            DEX_AREA_ROUTE_22 },
    { MAPSEC_ROUTE_23,            DEX_AREA_ROUTE_23 },
    { MAPSEC_ROUTE_24,            DEX_AREA_ROUTE_24 },
    { MAPSEC_ROUTE_25,            DEX_AREA_ROUTE_25 },
    { MAPSEC_VIRIDIAN_FOREST,     DEX_AREA_VIRIDIAN_FOREST },
    { MAPSEC_MT_MOON,             DEX_AREA_MT_MOON },
    { MAPSEC_S_S_ANNE,            DEX_AREA_VERMILION_CITY },
    { MAPSEC_UNDERGROUND_PATH,    DEX_AREA_SAFFRON_CITY },
    { MAPSEC_UNDERGROUND_PATH_2,  DEX_AREA_SAFFRON_CITY },
    { MAPSEC_DIGLETTS_CAVE,       DEX_AREA_DIGLETTS_CAVE },
    { MAPSEC_KANTO_VICTORY_ROAD,  DEX_AREA_VICTORY_ROAD },
    { MAPSEC_ROCKET_HIDEOUT,      DEX_AREA_CELADON_CITY },
    { MAPSEC_SILPH_CO,            DEX_AREA_SAFFRON_CITY },
    { MAPSEC_POKEMON_MANSION,     DEX_AREA_POKEMON_MANSION },
    { MAPSEC_KANTO_SAFARI_ZONE,   DEX_AREA_SAFARI_ZONE },
    { MAPSEC_POKEMON_LEAGUE,      DEX_AREA_VICTORY_ROAD },
    { MAPSEC_ROCK_TUNNEL,         DEX_AREA_ROCK_TUNNEL },
    { MAPSEC_SEAFOAM_ISLANDS,     DEX_AREA_SEAFOAM_ISLANDS },
    { MAPSEC_POKEMON_TOWER,       DEX_AREA_POKEMON_TOWER },
    { MAPSEC_CERULEAN_CAVE,       DEX_AREA_CERULEAN_CAVE },
    { MAPSEC_POWER_PLANT,         DEX_AREA_POWER_PLANT }
};

static const u16 sDexAreas_Sevii1[][2] = {
	{ MAPSEC_KINDLE_ROAD,    DEX_AREA_KINDLE_ROAD },
	{ MAPSEC_TREASURE_BEACH, DEX_AREA_TREASURE_BEACH },
	{ MAPSEC_ONE_ISLAND,     DEX_AREA_ONE_ISLAND },
	{ MAPSEC_MT_EMBER,       DEX_AREA_MT_EMBER }    
};

static const u16 sDexAreas_Sevii2[][2] = {
	{ MAPSEC_CAPE_BRINK, DEX_AREA_CAPE_BRINK },
	{ MAPSEC_TWO_ISLAND, DEX_AREA_TWO_ISLAND }    
};

static const u16 sDexAreas_Sevii3[][2] = {
	{ MAPSEC_BOND_BRIDGE,     DEX_AREA_BOND_BRIDGE },
	{ MAPSEC_THREE_ISLE_PORT, DEX_AREA_THREE_ISLE_PATH },
	{ MAPSEC_THREE_ISLAND,    DEX_AREA_THREE_ISLAND },
	{ MAPSEC_BERRY_FOREST,    DEX_AREA_BERRY_FOREST },
	{ MAPSEC_THREE_ISLE_PATH, DEX_AREA_THREE_ISLE_PATH }    
};

static const u16 sDexAreas_Sevii4[][2] = {
	{ MAPSEC_FOUR_ISLAND,  DEX_AREA_FOUR_ISLAND },
	{ MAPSEC_ICEFALL_CAVE, DEX_AREA_ICEFALL_CAVE }    
};

static const u16 sDexAreas_Sevii5[][2] = {
	{ MAPSEC_RESORT_GORGEOUS,  DEX_AREA_RESORT_GORGEOUS },
	{ MAPSEC_WATER_LABYRINTH,  DEX_AREA_WATER_LABYRINTH },
	{ MAPSEC_FIVE_ISLE_MEADOW, DEX_AREA_FIVE_ISLE_MEADOW },
	{ MAPSEC_MEMORIAL_PILLAR,  DEX_AREA_MEMORIAL_PILLAR },
	{ MAPSEC_FIVE_ISLAND,      DEX_AREA_FIVE_ISLAND },
	{ MAPSEC_ROCKET_WAREHOUSE, DEX_AREA_FIVE_ISLE_MEADOW },
	{ MAPSEC_LOST_CAVE,        DEX_AREA_LOST_CAVE }    
};

static const u16 sDexAreas_Sevii6[][2] = {
	{ MAPSEC_OUTCAST_ISLAND, DEX_AREA_OUTCAST_ISLAND },
	{ MAPSEC_GREEN_PATH,     DEX_AREA_GREEN_PATH },
	{ MAPSEC_WATER_PATH,     DEX_AREA_WATER_PATH },
	{ MAPSEC_RUIN_VALLEY,    DEX_AREA_RUIN_VALLEY },
	{ MAPSEC_DOTTED_HOLE,    DEX_AREA_DOTTED_HOLE },
	{ MAPSEC_PATTERN_BUSH,   DEX_AREA_PATTERN_BUSH },
	{ MAPSEC_ALTERING_CAVE,  DEX_AREA_ALTERING_CAVE }    
};

static const u16 sDexAreas_Sevii7[][2] = {
	{ MAPSEC_TRAINER_TOWER,   DEX_AREA_TRAINER_TOWER },
	{ MAPSEC_CANYON_ENTRANCE, DEX_AREA_CANYON_ENTRANCE },
	{ MAPSEC_SEVAULT_CANYON,  DEX_AREA_SEVAULT_CANYON },
	{ MAPSEC_TANOBY_RUINS,    DEX_AREA_TANOBY_RUINS },
	{ MAPSEC_MONEAN_CHAMBER,  DEX_AREA_TANOBY_CHAMBER },
	{ MAPSEC_LIPTOO_CHAMBER,  DEX_AREA_TANOBY_CHAMBER },
	{ MAPSEC_WEEPTH_CHAMBER,  DEX_AREA_TANOBY_CHAMBER },
	{ MAPSEC_DILFORD_CHAMBER, DEX_AREA_TANOBY_CHAMBER },
	{ MAPSEC_SCUFIB_CHAMBER,  DEX_AREA_TANOBY_CHAMBER },
	{ MAPSEC_RIXY_CHAMBER,    DEX_AREA_TANOBY_CHAMBER },
	{ MAPSEC_VIAPOIS_CHAMBER, DEX_AREA_TANOBY_CHAMBER }    
};

static const struct
{
    const u16 (*table)[2];
    s32 count;
} sSeviiDexAreas[] = {
    { sDexAreas_Sevii1, ARRAY_COUNT(sDexAreas_Sevii1) },
    { sDexAreas_Sevii2, ARRAY_COUNT(sDexAreas_Sevii2) },
    { sDexAreas_Sevii3, ARRAY_COUNT(sDexAreas_Sevii3) },
    { sDexAreas_Sevii4, ARRAY_COUNT(sDexAreas_Sevii4) },
    { sDexAreas_Sevii5, ARRAY_COUNT(sDexAreas_Sevii5) },
    { sDexAreas_Sevii6, ARRAY_COUNT(sDexAreas_Sevii6) },
    { sDexAreas_Sevii7, ARRAY_COUNT(sDexAreas_Sevii7) }
};

static const struct RoamerPair sRoamerPairs[] = {
    { SPECIES_ENTEI,   SPECIES_BULBASAUR  },
    { SPECIES_SUICUNE, SPECIES_CHARMANDER },
    { SPECIES_RAIKOU,  SPECIES_SQUIRTLE   }
};

// Scans for the given species and populates 'subsprites' with the area markers.
// Returns the number of areas where the species was found.
s32 GetSpeciesPokedexAreaMarkers(u16 species, struct Subsprite * subsprites)
{
    s32 areaCount;
    s32 j;
    s32 mapSecId;
    u16 dexArea;
    s32 tableIndex;
    s32 seviiAreas;
    s32 alteringCaveCount;
    s32 alteringCaveNum;
    s32 i;

    if (GetRoamerIndex(species) >= 0)
        return GetRoamerPokedexAreaMarkers(species, subsprites);

    seviiAreas = GetUnlockedSeviiAreas();
    alteringCaveCount = 0;
    alteringCaveNum = VarGet(VAR_ALTERING_CAVE_WILD_SET);
    if (alteringCaveNum >= NUM_ALTERING_CAVE_TABLES)
        alteringCaveNum = 0;
    for (i = 0, areaCount = 0; gWildMonHeaders[i].mapGroup != MAP_GROUP(MAP_UNDEFINED); i++)
    {
        mapSecId = GetMapSecIdFromWildMonHeader(&gWildMonHeaders[i]);
        if (mapSecId == MAPSEC_ALTERING_CAVE)
        {
            alteringCaveCount++;
            if (alteringCaveNum != alteringCaveCount - 1)
                continue;
        }
        if (IsSpeciesOnMap(&gWildMonHeaders[i], species))
        {
            // Search for all dex areas associated with this MAPSEC.
            // In the vanilla game each MAPSEC only has at most one DEX_AREA.
            tableIndex = 0;
            while (FindDexAreaByMapSec(mapSecId, sDexAreas_Kanto, ARRAY_COUNT(sDexAreas_Kanto), &tableIndex, &dexArea))
            {
                if (dexArea != DEX_AREA_NONE)
                    GetAreaMarkerSubsprite(areaCount++, dexArea, subsprites);
            }

            for (j = 0; j < ARRAY_COUNT(sSeviiDexAreas); j++)
            {
                if ((seviiAreas >> j) & 1)
                {
                    // Search for all dex areas associated with this MAPSEC in this unlocked Sevii Island
                    tableIndex = 0;
                    while (FindDexAreaByMapSec(mapSecId, sSeviiDexAreas[j].table, sSeviiDexAreas[j].count, &tableIndex, &dexArea))
                    {
                        if (dexArea != DEX_AREA_NONE)
                            GetAreaMarkerSubsprite(areaCount++, dexArea, subsprites);
                    }
                }
            }
        }
    }

    return areaCount;
}

static s32 GetRoamerIndex(u16 species)
{
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sRoamerPairs); i++)
    {
        if (sRoamerPairs[i].roamer == species)
            return i;
    }

    return -1;
}

static s32 GetRoamerPokedexAreaMarkers(u16 species, struct Subsprite * subsprites)
{
    u16 mapSecId;
    s32 roamerIdx;
    u16 dexArea;
    s32 tableIndex;

    // Make sure that this is a roamer species, and that it corresponds to the player's starter.
    roamerIdx = GetRoamerIndex(species);
    if (roamerIdx < 0)
        return 0;
    if (sRoamerPairs[roamerIdx].starter != GetStarterSpecies())
        return 0;

    mapSecId = GetRoamerLocationMapSectionId();
    tableIndex = 0;
    if (FindDexAreaByMapSec(mapSecId, sDexAreas_Kanto, ARRAY_COUNT(sDexAreas_Kanto), &tableIndex, &dexArea))
    {
        if (dexArea != DEX_AREA_NONE)
        {
            GetAreaMarkerSubsprite(0, dexArea, subsprites);
            return 1;
        }
    }
    return 0;
}

static bool32 IsSpeciesOnMap(const struct WildPokemonHeader * data, s32 species)
{
    if (IsSpeciesInEncounterTable(data->landMonsInfo, species, LAND_WILD_COUNT))
        return TRUE;
    if (IsSpeciesInEncounterTable(data->waterMonsInfo, species, WATER_WILD_COUNT))
        return TRUE;
// When searching the fishing encounters, this incorrectly uses the size of the land encounters.
// As a result it's reading out of bounds of the fishing encounters tables.
#ifdef BUGFIX
    if (IsSpeciesInEncounterTable(data->fishingMonsInfo, species, FISH_WILD_COUNT))
#else
    if (IsSpeciesInEncounterTable(data->fishingMonsInfo, species, LAND_WILD_COUNT))
#endif
        return TRUE;
    if (IsSpeciesInEncounterTable(data->rockSmashMonsInfo, species, ROCK_WILD_COUNT))
        return TRUE;

    return FALSE;
}

static bool32 IsSpeciesInEncounterTable(const struct WildPokemonInfo * info, s32 species, s32 count)
{
    s32 i;
    if (info != NULL)
    {
        for (i = 0; i < count; i++)
        {
            if (info->wildPokemon[i].species == species)
                return TRUE;
        }
    }
    return FALSE;
}

static u16 GetMapSecIdFromWildMonHeader(const struct WildPokemonHeader * header)
{
    return Overworld_GetMapHeaderByGroupAndId(header->mapGroup, header->mapNum)->regionMapSectionId;
}

// Search a MAPSEC -> DEX_AREA table for the given mapsec.
// Assigns the DEX_AREA (if found) to 'dexArea', and the first unread table index to 'index'.
// Returns TRUE if DEX_AREA was found, FALSE otherwise.
static bool32 FindDexAreaByMapSec(u16 mapSecId, const u16 (*table)[2], s32 count, s32 * index, u16 * dexArea)
{
    s32 i;
    for (i = *index; i < count; i++)
    {
        if (table[i][0] == mapSecId)
        {
            *dexArea = table[i][1];
            *index = i + 1;
            return TRUE;
        }
    }
    return FALSE;
}

// Rouge Feu (field_specials.c)
u8 GetUnlockedSeviiAreas(void)
{
    u8 result = 0;
    if (FlagGet(FLAG_KANTO_WORLD_MAP_ONE_ISLAND) == TRUE)
        result |= 1 << 0;
    if (FlagGet(FLAG_KANTO_WORLD_MAP_TWO_ISLAND) == TRUE)
        result |= 1 << 1;
    if (FlagGet(FLAG_KANTO_WORLD_MAP_THREE_ISLAND) == TRUE)
        result |= 1 << 2;
    if (FlagGet(FLAG_KANTO_WORLD_MAP_FOUR_ISLAND) == TRUE)
        result |= 1 << 3;
    if (FlagGet(FLAG_KANTO_WORLD_MAP_FIVE_ISLAND) == TRUE)
        result |= 1 << 4;
    if (FlagGet(FLAG_KANTO_WORLD_MAP_SIX_ISLAND) == TRUE)
        result |= 1 << 5;
    if (FlagGet(FLAG_KANTO_WORLD_MAP_SEVEN_ISLAND) == TRUE)
        result |= 1 << 6;
    return result;
}
