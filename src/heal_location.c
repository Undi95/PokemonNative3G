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

// Rouge Feu (heal_location.c) : après un K.O., reprise dans le Centre POKéMON, devant l'infirmière qui soignera l'équipe
// (respawn_* de heal_locations.json, Kanto et Hoenn), ou dans le hall de la Tour des Dresseurs pendant un défi. FALSE
// pour les lieux de soin sans infirmière (maisons de Bourg-en-Vol et de Bourg Palette, Île du Sud) : reprise d'Émeraude.
bool8 SetWhiteoutRespawnWarpAndHealerNpc(struct WarpData *warp)
{
    const struct WhiteoutRespawn *respawn;
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
    if (healLocationIdx == HEAL_LOCATION_NONE)
        return FALSE;
    respawn = &sWhiteoutRespawns[healLocationIdx - 1];
    if (respawn->healerNpcId == 0)
        return FALSE;

    warp->mapGroup = respawn->mapGroup;
    warp->mapNum = respawn->mapNum;
    warp->warpId = WARP_ID_NONE;
    warp->x = respawn->x;
    warp->y = respawn->y;
    gSpecialVar_LastTalked = respawn->healerNpcId;
    return TRUE;
}
