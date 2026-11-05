// Rouge Feu : map_preview_screen.h (aperçus des donjons et forêts de Kanto)
#ifndef GUARD_KANTO_MAP_PREVIEW_SCREEN_H
#define GUARD_KANTO_MAP_PREVIEW_SCREEN_H

enum MapPreviewScreenId
{
    MPS_VIRIDIAN_FOREST = 0u,
    MPS_MT_MOON,
    MPS_DIGLETTS_CAVE,
    MPS_ROCK_TUNNEL,
    MPS_POKEMON_TOWER,
    MPS_SAFARI_ZONE,
    MPS_SEAFOAM_ISLANDS,
    MPS_POKEMON_MANSION,
    MPS_ROCKET_HIDEOUT,
    MPS_SILPH_CO,
    MPS_VICTORY_ROAD,
    MPS_CERULEAN_CAVE,
    MPS_POWER_PLANT,
    MPS_MT_EMBER,
    MPS_ROCKET_WAREHOUSE,
    MPS_MONEAN_CHAMBER,
    MPS_DOTTED_HOLE,
    MPS_BERRY_FOREST,
    MPS_ICEFALL_CAVE,
    MPS_LOST_CAVE,
    MPS_ALTERING_CAVE,
    MPS_PATTERN_BUSH,
    MPS_LIPTOO_CHAMBER,
    MPS_WEEPTH_CHAMBER,
    MPS_TDILFORD_CHAMBER,
    MPS_SCUFIB_CHAMBER,
    MPS_RIXY_CHAMBER,
    MPS_VIAPOIS_CHAMBER,
    // PokemonNative3G : lieux de Hoenn, avec une image de RF qui ne montre pas un lieu unique (v1.1, demande user)
    MPS_HOENN_PETALBURG_WOODS,
    MPS_HOENN_SAFARI_ZONE,
    MPS_HOENN_RUSTURF_TUNNEL,
    MPS_HOENN_GRANITE_CAVE,
    MPS_HOENN_METEOR_FALLS,
    MPS_HOENN_FIERY_PATH,
    MPS_HOENN_SHOAL_CAVE,
    MPS_HOENN_CAVE_OF_ORIGIN,
    MPS_HOENN_VICTORY_ROAD,
    MPS_HOENN_SCORCHED_SLAB,
    MPS_HOENN_ALTERING_CAVE,
    MPS_HOENN_ARTISAN_CAVE,
    MPS_HOENN_TERRA_CAVE,
    // PokemonNative3G : lieux uniques de Hoenn, avec une illustration dessinée dans le style de RF
    // (graphics/fusion/map_preview, tools/apercus_hoenn.py)
    MPS_HOENN_MT_PYRE,
    MPS_HOENN_SKY_PILLAR,
    MPS_HOENN_AQUA_HIDEOUT,
    MPS_HOENN_MAGMA_HIDEOUT,
    MPS_HOENN_ABANDONED_SHIP,
    MPS_HOENN_NEW_MAUVILLE,
    MPS_HOENN_MIRAGE_TOWER,
    MPS_HOENN_DESERT_RUINS,
    MPS_HOENN_ISLAND_CAVE,
    MPS_HOENN_ANCIENT_TOMB,
    MPS_COUNT
};

#define MPS_TYPE_CAVE   0
#define MPS_TYPE_FOREST 1
#define MPS_TYPE_ANY    2

struct MapPreviewScreen
{
    u8 mapsec;
    u8 type;
    u16 flagId;
    const void *tilesptr;
    const void *tilemapptr;
    const void *palptr;
};

u16 MapPreview_CreateMapNameWindow(u8 id);
void MapPreview_SetFlag(u16 a0);
u16 MapPreview_GetDuration(u8 id);
bool8 MapHasPreviewScreen(u8 mapsec, u8 type);
bool32 ForestMapPreviewScreenIsRunning(void);
const struct MapPreviewScreen * GetDungeonMapPreviewScreenInfo(u8 mapsec);
bool32 MapHasPreviewScreen_HandleQLState2(u8 mapsec, u8 type);
void MapPreview_InitBgs(void);
void MapPreview_LoadGfx(u8 mapsec);
bool32 MapPreview_IsGfxLoadFinished(void);
void MapPreview_Unload(s32 windowId);
void MapPreview_StartForestTransition(u8 mapsec);

#endif //GUARD_KANTO_MAP_PREVIEW_SCREEN_H
