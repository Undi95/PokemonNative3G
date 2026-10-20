// Rouge Feu : Pokédex (pokedex_screen.c, pokedex_area_markers.c, wild_pokemon_area.c) — option POKEDEX = KANTO
#ifndef GUARD_KANTO_POKEDEX_H
#define GUARD_KANTO_POKEDEX_H

#include "sprite.h"

#define DEX_CATEGORY_GRASSLAND      0
#define DEX_CATEGORY_FOREST         1
#define DEX_CATEGORY_WATERS_EDGE    2
#define DEX_CATEGORY_SEA            3
#define DEX_CATEGORY_CAVE           4
#define DEX_CATEGORY_MOUNTAIN       5
#define DEX_CATEGORY_ROUGH_TERRAIN  6
#define DEX_CATEGORY_URBAN          7
#define DEX_CATEGORY_RARE           8
#define DEX_CATEGORY_COUNT          9

#define DEX_ORDER_NUMERICAL_KANTO    0
#define DEX_ORDER_ATOZ               1
#define DEX_ORDER_TYPE               2
#define DEX_ORDER_LIGHTEST           3
#define DEX_ORDER_SMALLEST           4
#define DEX_ORDER_NUMERICAL_NATIONAL 5

#define DEX_MODE(name) (DEX_CATEGORY_COUNT + DEX_ORDER_##name)

// IDs for the pokedex area markers
enum {
    DEX_AREA_NONE,
    DEX_AREA_PALLET_TOWN,
    DEX_AREA_VIRIDIAN_CITY,
    DEX_AREA_PEWTER_CITY,
    DEX_AREA_CERULEAN_CITY,
    DEX_AREA_LAVENDER_TOWN,
    DEX_AREA_VERMILION_CITY,
    DEX_AREA_CELADON_CITY,
    DEX_AREA_FUCHSIA_CITY,
    DEX_AREA_CINNABAR_ISLAND,
    DEX_AREA_INDIGO_PLATEAU,
    DEX_AREA_SAFFRON_CITY,
    DEX_AREA_ROUTE_1,
    DEX_AREA_ROUTE_2,
    DEX_AREA_ROUTE_3,
    DEX_AREA_ROUTE_4,
    DEX_AREA_ROUTE_5,
    DEX_AREA_ROUTE_6,
    DEX_AREA_ROUTE_7,
    DEX_AREA_ROUTE_8,
    DEX_AREA_ROUTE_9,
    DEX_AREA_ROUTE_10,
    DEX_AREA_ROUTE_11,
    DEX_AREA_ROUTE_12,
    DEX_AREA_ROUTE_13,
    DEX_AREA_ROUTE_14,
    DEX_AREA_ROUTE_15,
    DEX_AREA_ROUTE_16,
    DEX_AREA_ROUTE_17,
    DEX_AREA_ROUTE_18,
    DEX_AREA_ROUTE_19,
    DEX_AREA_ROUTE_20,
    DEX_AREA_ROUTE_21,
    DEX_AREA_ROUTE_22,
    DEX_AREA_ROUTE_23,
    DEX_AREA_ROUTE_24,
    DEX_AREA_ROUTE_25,
    DEX_AREA_VIRIDIAN_FOREST,
    DEX_AREA_DIGLETTS_CAVE,
    DEX_AREA_MT_MOON,
    DEX_AREA_CERULEAN_CAVE,
    DEX_AREA_ROCK_TUNNEL,
    DEX_AREA_POWER_PLANT,
    DEX_AREA_POKEMON_TOWER,
    DEX_AREA_SAFARI_ZONE,
    DEX_AREA_SEAFOAM_ISLANDS,
    DEX_AREA_POKEMON_MANSION,
    DEX_AREA_VICTORY_ROAD,
    DEX_AREA_ONE_ISLAND,
    DEX_AREA_TWO_ISLAND,
    DEX_AREA_THREE_ISLAND,
    DEX_AREA_FOUR_ISLAND,
    DEX_AREA_FIVE_ISLAND,
    DEX_AREA_SIX_ISLAND, // Not associated with any MAPSEC
    DEX_AREA_SEVEN_ISLAND, // Not associated with any MAPSEC
    DEX_AREA_KINDLE_ROAD,
    DEX_AREA_TREASURE_BEACH,
    DEX_AREA_CAPE_BRINK,
    DEX_AREA_BOND_BRIDGE,
    DEX_AREA_THREE_ISLE_PATH,
    DEX_AREA_RESORT_GORGEOUS,
    DEX_AREA_WATER_LABYRINTH,
    DEX_AREA_FIVE_ISLE_MEADOW,
    DEX_AREA_MEMORIAL_PILLAR,
    DEX_AREA_OUTCAST_ISLAND,
    DEX_AREA_GREEN_PATH,
    DEX_AREA_WATER_PATH,
    DEX_AREA_RUIN_VALLEY,
    DEX_AREA_TRAINER_TOWER,
    DEX_AREA_CANYON_ENTRANCE,
    DEX_AREA_SEVAULT_CANYON,
    DEX_AREA_TANOBY_RUINS,
    DEX_AREA_MT_EMBER,
    DEX_AREA_BERRY_FOREST,
    DEX_AREA_ICEFALL_CAVE,
    DEX_AREA_LOST_CAVE,
    DEX_AREA_ALTERING_CAVE,
    DEX_AREA_PATTERN_BUSH,
    DEX_AREA_DOTTED_HOLE,
    DEX_AREA_TANOBY_CHAMBER,
};

// Rouge Feu (pokedex.h) : avec unusedDescription, contrairement à Émeraude
struct KantoPokedexEntry
{
    /*0x00*/ u8 categoryName[12];
    /*0x0C*/ u16 height; //in decimeters
    /*0x0E*/ u16 weight; //in hectograms
    /*0x10*/ const u8 *description;
    /*0x14*/ const u8 *unusedDescription;
    /*0x18*/ u16 unused;
    /*0x1A*/ u16 pokemonScale;
    /*0x1C*/ u16 pokemonOffset;
    /*0x1E*/ u16 trainerScale;
    /*0x20*/ u16 trainerOffset;
};  /*size = 0x24*/

void CB2_KantoOpenPokedexFromStartMenu(void);
u8 KantoDexScreen_RegisterMonToPokedex(u16 species);

void GetAreaMarkerSubsprite(s32 i, s32 dexArea, struct Subsprite * subsprites);
void DestroyPokedexAreaMarkers(u8 taskId);
u8 CreatePokedexAreaMarkers(u16 species, u16 tilesTag, u8 palIdx, u8 y);
u8 GetNumPokedexAreaMarkers(u8 taskId);
s32 GetSpeciesPokedexAreaMarkers(u16 species, struct Subsprite * subsprites);
u8 GetUnlockedSeviiAreas(void);

#endif // GUARD_KANTO_POKEDEX_H
