#include "global.h"
#include "heal_location.h"
#include "event_data.h"
#include "kanto_save.h"
#include "constants/heal_locations.h"
#include "constants/map_event_ids.h"
#include "constants/maps.h"

#include "data/heal_locations.h"

u32 GetHealLocationIndexByMap(u16 mapGroup, u16 mapNum)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sHealLocations); i++)
    {
        if (sHealLocations[i].mapGroup == mapGroup && sHealLocations[i].mapNum == mapNum)
            return i + 1;
    }
    return HEAL_LOCATION_NONE;
}

const struct HealLocation *GetHealLocationByMap(u16 mapGroup, u16 mapNum)
{
    u32 index = GetHealLocationIndexByMap(mapGroup, mapNum);

    if (index == HEAL_LOCATION_NONE)
        return NULL;
    else
        return &sHealLocations[index - 1];
}

const struct HealLocation *GetHealLocation(u32 index)
{
    if (index == HEAL_LOCATION_NONE)
        return NULL;
    else if (index > ARRAY_COUNT(sHealLocations))
        return NULL;
    else
        return &sHealLocations[index - 1];
}

// PokemonNative3G : Rouge Feu (heal_location.c). Après un K.O., RF fait reprendre le joueur dans le Centre POKéMON, devant
// l'infirmière qui soignera l'équipe (respawn_map / respawn_npc de heal_locations.json), ou dans le hall de la Tour des
// Dresseurs pendant un défi. FALSE pour les lieux de soin sans infirmière : Hoenn, et Bourg Palette, dont la maison n'a
// plus de maman (reprise d'Émeraude devant la maison).
bool8 SetWhiteoutRespawnWarpAndHealerNpc(struct WarpData *warp)
{
    u32 healLocationIdx;

    if (VarGet(VAR_KANTO_MAP_SCENE_TRAINER_TOWER) == 1)
    {
        if (!gSaveBlockKanto.trainerTower[gSaveBlockKanto.towerChallengeId].spokeToOwner)
            VarSet(VAR_KANTO_MAP_SCENE_TRAINER_TOWER, 0);
        gSpecialVar_LastTalked = LOCALID_KANTO_TOWER_NURSE;
        warp->x = 4;
        warp->y = 11;
        warp->mapGroup = MAP_GROUP(MAP_TRAINER_TOWER_LOBBY);
        warp->mapNum = MAP_NUM(MAP_TRAINER_TOWER_LOBBY);
        warp->warpId = WARP_ID_NONE;
        return TRUE;
    }

    healLocationIdx = GetHealLocationIndexByMap(gSaveBlock1Ptr->lastHealLocation.mapGroup, gSaveBlock1Ptr->lastHealLocation.mapNum);
    if (healLocationIdx == HEAL_LOCATION_NONE || healLocationIdx > ARRAY_COUNT(sWhiteoutRespawnHealerNpcIds)
     || sWhiteoutRespawnHealerNpcIds[healLocationIdx - 1] == 0)
        return FALSE;

    warp->mapGroup = sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][0];
    warp->mapNum = sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][1];
    warp->warpId = WARP_ID_NONE;
    if (warp->mapGroup == MAP_GROUP(MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F) && warp->mapNum == MAP_NUM(MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F))
    {
        warp->x = 13;
        warp->y = 12;
    }
    else if (warp->mapGroup == MAP_GROUP(MAP_ONE_ISLAND_POKEMON_CENTER_1F) && warp->mapNum == MAP_NUM(MAP_ONE_ISLAND_POKEMON_CENTER_1F))
    {
        warp->x = 5;
        warp->y = 4;
    }
    else
    {
        warp->x = 7;
        warp->y = 4;
    }
    gSpecialVar_LastTalked = sWhiteoutRespawnHealerNpcIds[healLocationIdx - 1];
    return TRUE;
}
