#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "random.h"
#include "roamer.h"
#include "fusion_region.h"
#include "kanto_save.h"
#include "overworld.h"
#include "constants/region_map_sections.h"
#include "fieldmap.h"

// PokemonNative3G : quatre vagabonds simultanés.
//   n°0 : Hoenn, Latios ou Latias (choix du joueur, roamer.c d'Émeraude, gSaveBlock1Ptr->roamer)
//   n°1-3 : Kanto, Raikou / Entei / Suicune tous les trois (roamer.c de RF : N.50, lieux de RF ;
//           RF n'en lâchait qu'un, selon le starter), gSaveBlockKanto.roamers[]
// Les fonctions publiques agissent sur les vagabonds de la région de la carte courante ; après une
// rencontre, sCurRoamer désigne celui qui est combattu.

// Despite having a variable to track it, the roamer is
// hard-coded to only ever be in map group 0
// (Kanto : groupe des routes de Kanto, 3 dans RF)
#define HOENN_ROAMER_MAP_GROUP 0
#define KANTO_ROAMER_MAP_GROUP MAP_GROUP(MAP_ROUTE1)
#define NUM_ROAMERS (1 + NUM_KANTO_ROAMERS)

enum
{
    MAP_GRP, // map group
    MAP_NUM, // map number
};

EWRAM_DATA static u8 sCurRoamer = 0;
EWRAM_DATA static u8 sRegionLocationHistory[2][3][2] = {0};
EWRAM_DATA static u8 sRoamerLocations_[NUM_ROAMERS][2] = {0};

#define IS_KANTO_ROAMER() (sCurRoamer != 0)
#define ROAMER (GetCurrentRoamer())
#define ROAMER_MAP_GROUP (IS_KANTO_ROAMER() ? KANTO_ROAMER_MAP_GROUP : HOENN_ROAMER_MAP_GROUP)
#define sLocationHistory sRegionLocationHistory[IS_KANTO_ROAMER()]
#define sRoamerLocation sRoamerLocations_[sCurRoamer]

#define ___ MAP_NUM(MAP_UNDEFINED) // For empty spots in the location table

// Note: There are two potential softlocks that can occur with this table if its maps are
//       changed in particular ways. They can be avoided by ensuring the following:
//       - There must be at least 2 location sets that start with a different map,
//         i.e. every location set cannot start with the same map. This is because of
//         the while loop in RoamerMoveToOtherLocationSet.
//       - Each location set must have at least 3 unique maps. This is because of
//         the while loop in RoamerMove. In this loop the first map in the set is
//         ignored, and an additional map is ignored if the roamer was there recently.
//       - Additionally, while not a softlock, it's worth noting that if for any
//         map in the location table there is not a location set that starts with
//         that map then the roamer will be significantly less likely to move away
//         from that map when it lands there.
static const u8 sRoamerLocations[][6] =
{
    { MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE134), ___ },
    { MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE118), ___, ___ },
    { MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE118), ___, ___ },
    { MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE123) },
    { MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE120), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE120), MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE121), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE120), MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE123), ___, ___ },
    { MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE123), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE123), MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE118), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE126), ___, ___ },
    { MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE127), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE126), MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE127), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE127), MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE126), MAP_NUM(MAP_ROUTE128), ___, ___ },
    { MAP_NUM(MAP_ROUTE128), MAP_NUM(MAP_ROUTE127), MAP_NUM(MAP_ROUTE129), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE129), MAP_NUM(MAP_ROUTE128), MAP_NUM(MAP_ROUTE130), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE130), MAP_NUM(MAP_ROUTE129), MAP_NUM(MAP_ROUTE131), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE131), MAP_NUM(MAP_ROUTE130), MAP_NUM(MAP_ROUTE132), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE132), MAP_NUM(MAP_ROUTE131), MAP_NUM(MAP_ROUTE133), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE133), MAP_NUM(MAP_ROUTE132), MAP_NUM(MAP_ROUTE134), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE134), MAP_NUM(MAP_ROUTE133), MAP_NUM(MAP_ROUTE110), ___, ___, ___ },
    { ___, ___, ___, ___, ___, ___ },
};

// Rouge Feu (roamer.c)
static const u8 sKantoRoamerLocations[][7] = {
    {MAP_NUM(MAP_ROUTE1), MAP_NUM(MAP_ROUTE2), MAP_NUM(MAP_ROUTE21_NORTH), MAP_NUM(MAP_ROUTE22), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE2), MAP_NUM(MAP_ROUTE1), MAP_NUM(MAP_ROUTE3), MAP_NUM(MAP_ROUTE22), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE3), MAP_NUM(MAP_ROUTE2), MAP_NUM(MAP_ROUTE4), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE4), MAP_NUM(MAP_ROUTE3), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE9), MAP_NUM(MAP_ROUTE24), ___, ___},
    {MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE4), MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE9), MAP_NUM(MAP_ROUTE24)},
    {MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE11), ___, ___},
    {MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE16), ___, ___},
    {MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE12), ___},
    {MAP_NUM(MAP_ROUTE9), MAP_NUM(MAP_ROUTE4), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE24), ___, ___},
    {MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE9), MAP_NUM(MAP_ROUTE12), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE11), MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE12), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE12), MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE11), MAP_NUM(MAP_ROUTE13), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE13), MAP_NUM(MAP_ROUTE12), MAP_NUM(MAP_ROUTE14), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE14), MAP_NUM(MAP_ROUTE13), MAP_NUM(MAP_ROUTE15), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE15), MAP_NUM(MAP_ROUTE14), MAP_NUM(MAP_ROUTE18), MAP_NUM(MAP_ROUTE19), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE16), MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE17), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE17), MAP_NUM(MAP_ROUTE16), MAP_NUM(MAP_ROUTE18), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE18), MAP_NUM(MAP_ROUTE15), MAP_NUM(MAP_ROUTE17), MAP_NUM(MAP_ROUTE19), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE19), MAP_NUM(MAP_ROUTE15), MAP_NUM(MAP_ROUTE18), MAP_NUM(MAP_ROUTE20), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE20), MAP_NUM(MAP_ROUTE19), MAP_NUM(MAP_ROUTE21_NORTH), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE21_NORTH), MAP_NUM(MAP_ROUTE1), MAP_NUM(MAP_ROUTE20), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE22), MAP_NUM(MAP_ROUTE1), MAP_NUM(MAP_ROUTE2), MAP_NUM(MAP_ROUTE23), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE23), MAP_NUM(MAP_ROUTE22), MAP_NUM(MAP_ROUTE2), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE24), MAP_NUM(MAP_ROUTE4), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE9), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE25), MAP_NUM(MAP_ROUTE24), MAP_NUM(MAP_ROUTE9), ___, ___, ___, ___},
    {___, ___, ___, ___, ___, ___, ___}
};

#undef ___
#define NUM_HOENN_LOCATION_SETS (ARRAY_COUNT(sRoamerLocations) - 1)
#define NUM_KANTO_LOCATION_SETS (ARRAY_COUNT(sKantoRoamerLocations) - 1)
#define NUM_LOCATION_SETS (IS_KANTO_ROAMER() ? NUM_KANTO_LOCATION_SETS : NUM_HOENN_LOCATION_SETS)
#define NUM_LOCATIONS_PER_SET (IS_KANTO_ROAMER() ? ARRAY_COUNT(sKantoRoamerLocations[0]) : ARRAY_COUNT(sRoamerLocations[0]))
#define ROAMER_LOCATION(set, i) (IS_KANTO_ROAMER() ? sKantoRoamerLocations[set][i] : sRoamerLocations[set][i])

static const u16 sKantoRoamerSpecies[NUM_KANTO_ROAMERS] = {SPECIES_RAIKOU, SPECIES_ENTEI, SPECIES_SUICUNE};

struct Roamer *GetCurrentRoamer(void)
{
    if (sCurRoamer == 0)
        return &gSaveBlock1Ptr->roamer;
    return &gSaveBlockKanto.roamers[sCurRoamer - 1];
}

// Premier / dernier vagabond de la région de la carte courante
static u8 FirstRoamerOfRegion(void)
{
    return Fusion_IsInKanto() ? 1 : 0;
}

static u8 LastRoamerOfRegion(void)
{
    return Fusion_IsInKanto() ? NUM_KANTO_ROAMERS : 0;
}

#define FOR_EACH_REGION_ROAMER for (sCurRoamer = FirstRoamerOfRegion(); sCurRoamer <= LastRoamerOfRegion(); sCurRoamer++)

static void ClearRoamerData_(void)
{
    memset(ROAMER, 0, sizeof(*ROAMER));
    if (!IS_KANTO_ROAMER())
        ROAMER->species = SPECIES_LATIAS;
}

void ClearRoamerData(void)
{
    FOR_EACH_REGION_ROAMER
        ClearRoamerData_();
    sCurRoamer = FirstRoamerOfRegion();
}

void ClearRoamerLocationData(void)
{
    u8 i;

    sCurRoamer = FirstRoamerOfRegion();
    for (i = 0; i < ARRAY_COUNT(sLocationHistory); i++)
    {
        sLocationHistory[i][MAP_GRP] = 0;
        sLocationHistory[i][MAP_NUM] = 0;
    }

    FOR_EACH_REGION_ROAMER
    {
        sRoamerLocation[MAP_GRP] = 0;
        sRoamerLocation[MAP_NUM] = 0;
    }
    sCurRoamer = FirstRoamerOfRegion();
}

static void CreateInitialRoamerMon(u16 species, u8 level)
{
    CreateMon(&gEnemyParty[0], species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    ROAMER->species = species;
    ROAMER->level = level;
    ROAMER->status = 0;
    ROAMER->active = TRUE;
    ROAMER->ivs = GetMonData(&gEnemyParty[0], MON_DATA_IVS);
    ROAMER->personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY);
    ROAMER->hp = GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP);
    ROAMER->cool = GetMonData(&gEnemyParty[0], MON_DATA_COOL);
    ROAMER->beauty = GetMonData(&gEnemyParty[0], MON_DATA_BEAUTY);
    ROAMER->cute = GetMonData(&gEnemyParty[0], MON_DATA_CUTE);
    ROAMER->smart = GetMonData(&gEnemyParty[0], MON_DATA_SMART);
    ROAMER->tough = GetMonData(&gEnemyParty[0], MON_DATA_TOUGH);
    sRoamerLocation[MAP_GRP] = ROAMER_MAP_GROUP;
    sRoamerLocation[MAP_NUM] = ROAMER_LOCATION(Random() % NUM_LOCATION_SETS, 0);
}

// Hoenn : gSpecialVar_0x8004 here corresponds to the options in the multichoice MULTI_TV_LATI (0 for 'Red', 1 for 'Blue')
// Kanto : les trois chiens (Île 1, après le Réseau Sevii)
void InitRoamer(void)
{
    ClearRoamerData();
    ClearRoamerLocationData();
    FOR_EACH_REGION_ROAMER
    {
        if (IS_KANTO_ROAMER())
            CreateInitialRoamerMon(sKantoRoamerSpecies[sCurRoamer - 1], 50);
        else
            CreateInitialRoamerMon(gSpecialVar_0x8004 ? SPECIES_LATIOS : SPECIES_LATIAS, 40);
    }
    sCurRoamer = FirstRoamerOfRegion();
}

void UpdateLocationHistoryForRoamer(void)
{
    sCurRoamer = FirstRoamerOfRegion();
    sLocationHistory[2][MAP_GRP] = sLocationHistory[1][MAP_GRP];
    sLocationHistory[2][MAP_NUM] = sLocationHistory[1][MAP_NUM];

    sLocationHistory[1][MAP_GRP] = sLocationHistory[0][MAP_GRP];
    sLocationHistory[1][MAP_NUM] = sLocationHistory[0][MAP_NUM];

    sLocationHistory[0][MAP_GRP] = gSaveBlock1Ptr->location.mapGroup;
    sLocationHistory[0][MAP_NUM] = gSaveBlock1Ptr->location.mapNum;
}

static void RoamerMoveToOtherLocationSet_(void)
{
    u8 mapNum = 0;

    if (!ROAMER->active)
        return;

    sRoamerLocation[MAP_GRP] = ROAMER_MAP_GROUP;

    // Choose a location set that starts with a map
    // different from the roamer's current map
    while (1)
    {
        mapNum = ROAMER_LOCATION(Random() % NUM_LOCATION_SETS, 0);
        if (sRoamerLocation[MAP_NUM] != mapNum)
        {
            sRoamerLocation[MAP_NUM] = mapNum;
            return;
        }
    }
}

void RoamerMoveToOtherLocationSet(void)
{
    FOR_EACH_REGION_ROAMER
        RoamerMoveToOtherLocationSet_();
    sCurRoamer = FirstRoamerOfRegion();
}

static void RoamerMove_(void)
{
    u8 locSet = 0;

    if ((Random() % 16) == 0)
    {
        RoamerMoveToOtherLocationSet_();
    }
    else
    {
        if (!ROAMER->active)
            return;

        while (locSet < NUM_LOCATION_SETS)
        {
            // Find the location set that starts with the roamer's current map
            if (sRoamerLocation[MAP_NUM] == ROAMER_LOCATION(locSet, 0))
            {
                u8 mapNum;
                while (1)
                {
                    // Choose a new map (excluding the first) within this set
                    // Also exclude a map if the roamer was there 2 moves ago
                    mapNum = ROAMER_LOCATION(locSet, (Random() % (NUM_LOCATIONS_PER_SET - 1)) + 1);
                    if (!(sLocationHistory[2][MAP_GRP] == ROAMER_MAP_GROUP
                       && sLocationHistory[2][MAP_NUM] == mapNum)
                       && mapNum != MAP_NUM(MAP_UNDEFINED))
                        break;
                }
                sRoamerLocation[MAP_NUM] = mapNum;
                return;
            }
            locSet++;
        }
    }
}

void RoamerMove(void)
{
    FOR_EACH_REGION_ROAMER
        RoamerMove_();
    sCurRoamer = FirstRoamerOfRegion();
}

static bool8 IsRoamerAt_(u8 mapGroup, u8 mapNum)
{
    if (ROAMER->active && mapGroup == sRoamerLocation[MAP_GRP] && mapNum == sRoamerLocation[MAP_NUM])
        return TRUE;
    else
        return FALSE;
}

bool8 IsRoamerAt(u8 mapGroup, u8 mapNum)
{
    FOR_EACH_REGION_ROAMER
    {
        if (IsRoamerAt_(mapGroup, mapNum))
            return TRUE;
    }
    sCurRoamer = FirstRoamerOfRegion();
    return FALSE;
}

void CreateRoamerMonInstance(void)
{
    u32 status;
    struct Pokemon *mon = &gEnemyParty[0];
    ZeroEnemyPartyMons();
    CreateMonWithIVsPersonality(mon, ROAMER->species, ROAMER->level, ROAMER->ivs, ROAMER->personality);
// The roamer's status field is u8, but SetMonData expects status to be u32, so will set the roamer's status
// using the status field and the following 3 bytes (cool, beauty, and cute).
// PokemonNative3G : bug corrigé
    status = ROAMER->status;
    SetMonData(mon, MON_DATA_STATUS, &status);
    SetMonData(mon, MON_DATA_HP, &ROAMER->hp);
    SetMonData(mon, MON_DATA_COOL, &ROAMER->cool);
    SetMonData(mon, MON_DATA_BEAUTY, &ROAMER->beauty);
    SetMonData(mon, MON_DATA_CUTE, &ROAMER->cute);
    SetMonData(mon, MON_DATA_SMART, &ROAMER->smart);
    SetMonData(mon, MON_DATA_TOUGH, &ROAMER->tough);
}

// Plusieurs chiens peuvent être sur la même route : l'un d'eux est tiré au hasard
bool8 TryStartRoamerEncounter(void)
{
    u8 found[NUM_ROAMERS];
    u8 n = 0;

    FOR_EACH_REGION_ROAMER
    {
        if (IsRoamerAt_(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
            found[n++] = sCurRoamer;
    }
    if (n != 0 && (Random() % 4) == 0)
    {
        sCurRoamer = found[Random() % n];
        CreateRoamerMonInstance();
        return TRUE;
    }
    else
    {
        sCurRoamer = FirstRoamerOfRegion();
        return FALSE;
    }
}

// Après le combat : sCurRoamer = vagabond rencontré (TryStartRoamerEncounter)
void UpdateRoamerHPStatus(struct Pokemon *mon)
{
    ROAMER->hp = GetMonData(mon, MON_DATA_HP);
    ROAMER->status = GetMonData(mon, MON_DATA_STATUS);

    RoamerMoveToOtherLocationSet_();
}

void SetRoamerInactive(void)
{
    ROAMER->active = FALSE;
}

void GetRoamerLocation(u8 *mapGroup, u8 *mapNum)
{
    *mapGroup = sRoamerLocation[MAP_GRP];
    *mapNum = sRoamerLocation[MAP_NUM];
}

// PokemonNative3G : zone d'un chien de Kanto pour le Pokédex de RF (les 3 chiens errent, quel que soit le starter)
u16 GetKantoRoamerLocationMapSectionId(u16 species)
{
    u16 mapSec = MAPSEC_NONE;
    u8 saved = sCurRoamer;

    for (sCurRoamer = 1; sCurRoamer <= NUM_KANTO_ROAMERS; sCurRoamer++)
    {
        if (ROAMER->active && ROAMER->species == species)
            mapSec = Overworld_GetMapHeaderByGroupAndId(sRoamerLocation[MAP_GRP], sRoamerLocation[MAP_NUM])->regionMapSectionId;
    }
    sCurRoamer = saved;
    return mapSec;
}

// Rouge Feu (Pokédex : zone du vagabond)
u16 GetRoamerLocationMapSectionId(void)
{
    if (!ROAMER->active)
        return MAPSEC_NONE;
    return Overworld_GetMapHeaderByGroupAndId(sRoamerLocation[MAP_GRP], sRoamerLocation[MAP_NUM])->regionMapSectionId;
}
