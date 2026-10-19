// Décors de combat de Rouge Feu (src/battle_bg.c de RF), utilisés sur les cartes de Kanto.
// Les types de combat propres à RF (Pokédude, Tour d'Entraînement, Tour de Combat) ne sont pas
// encore importés ; leurs branches sont omises.
#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "decompress.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "kanto_battle_bg.h"
#include "metatile_behavior.h"
#include "constants/metatile_behaviors.h"
#include "overworld.h"
#include "palette.h"
#include "constants/trainers.h"

#include "data/graphics/kanto_battle_terrain.h"

static u8 GetBattleTerrainByMapScene(u8 mapBattleScene)
{
    int i;
    for (i = 0; i < NELEMS(sKantoMapBattleSceneMapping); i++)
    {
        if (mapBattleScene == sKantoMapBattleSceneMapping[i].mapScene)
            return sKantoMapBattleSceneMapping[i].battleTerrain;
    }
    return KANTO_BATTLE_TERRAIN_PLAIN;
}

static void LoadBattleTerrainGfx(u16 terrain)
{
    if (terrain >= NELEMS(sKantoBattleTerrainTable))
        terrain = KANTO_BATTLE_TERRAIN_PLAIN;
    // Copy to bg3
    LZDecompressVram(sKantoBattleTerrainTable[terrain].tileset, (void *)BG_CHAR_ADDR(2));
    LZDecompressVram(sKantoBattleTerrainTable[terrain].tilemap, (void *)BG_SCREEN_ADDR(26));
    LoadCompressedPalette(sKantoBattleTerrainTable[terrain].palette, BG_PLTT_ID(2), 3 * PLTT_SIZE_4BPP);
}

static void LoadBattleTerrainEntryGfx(u16 terrain)
{
    if (terrain >= NELEMS(sKantoBattleTerrainTable))
        terrain = KANTO_BATTLE_TERRAIN_PLAIN;
    // Copy to bg1
    LZDecompressVram(sKantoBattleTerrainTable[terrain].entryTileset, (void *)BG_CHAR_ADDR(1));
    LZDecompressVram(sKantoBattleTerrainTable[terrain].entryTilemap, (void *)BG_SCREEN_ADDR(28));
}

static u8 GetBattleTerrainOverride(void)
{
    u8 battleScene;
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_EREADER_TRAINER))
    {
        return KANTO_BATTLE_TERRAIN_LINK;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_LEADER)
            return KANTO_BATTLE_TERRAIN_LEADER;
        else if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_CHAMPION)
            return KANTO_BATTLE_TERRAIN_CHAMPION;
    }
    battleScene = GetCurrentMapBattleScene();
    if (battleScene == MAP_BATTLE_SCENE_NORMAL)
    {
        return gBattleEnvironment;
    }
    return GetBattleTerrainByMapScene(battleScene);
}

void Kanto_DrawMainBattleBackground(void)
{
    LoadBattleTerrainGfx(GetBattleTerrainOverride());
}

// DrawBattleEntryBackground de RF, hors combat en link (commun aux deux jeux)
void Kanto_DrawBattleEntryBackground(void)
{
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_EREADER_TRAINER))
    {
        LoadBattleTerrainEntryGfx(KANTO_BATTLE_TERRAIN_BUILDING);
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            u8 trainerClass = gTrainers[gTrainerBattleOpponent_A].trainerClass;
            if (trainerClass == TRAINER_CLASS_LEADER)
            {
                LoadBattleTerrainEntryGfx(KANTO_BATTLE_TERRAIN_BUILDING);
                return;
            }
            else if (trainerClass == TRAINER_CLASS_CHAMPION)
            {
                LoadBattleTerrainEntryGfx(KANTO_BATTLE_TERRAIN_BUILDING);
                return;
            }
        }
        if (GetCurrentMapBattleScene() == MAP_BATTLE_SCENE_NORMAL)
        {
            LoadBattleTerrainEntryGfx(gBattleEnvironment);
        }
        else
        {
            LoadBattleTerrainEntryGfx(KANTO_BATTLE_TERRAIN_BUILDING);
        }
    }
}

// Cas 3 à 5 de LoadChosenBattleElement de RF (décor)
bool8 Kanto_LoadChosenBattleElement(u8 caseId)
{
    u8 battleScene;

    switch (caseId)
    {
    case 3:
        battleScene = GetBattleTerrainOverride();
        LZDecompressVram(sKantoBattleTerrainTable[battleScene].tileset, (void *)BG_CHAR_ADDR(2));
        // fallthrough
    case 4:
        battleScene = GetBattleTerrainOverride();
        LZDecompressVram(sKantoBattleTerrainTable[battleScene].tilemap, (void *)BG_SCREEN_ADDR(26));
        break;
    case 5:
        battleScene = GetBattleTerrainOverride();
        LoadCompressedPalette(sKantoBattleTerrainTable[battleScene].palette, BG_PLTT_ID(2), 3 * PLTT_SIZE_4BPP);
        break;
    }
    return FALSE;
}

// BattleSetup_GetTerrainId de RF
u8 Kanto_BattleSetup_GetTerrainId(void)
{
    u16 tileBehavior;
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    tileBehavior = MapGridGetMetatileBehaviorAt(x, y);
    if (MetatileBehavior_IsTallGrass(tileBehavior))
        return KANTO_BATTLE_TERRAIN_GRASS;
    if (MetatileBehavior_IsLongGrass(tileBehavior))
        return KANTO_BATTLE_TERRAIN_LONG_GRASS;
    // MetatileBehavior_IsSandOrShallowFlowingWater de RF
    if (tileBehavior == MB_SAND || tileBehavior == MB_SHALLOW_WATER)
        return KANTO_BATTLE_TERRAIN_SAND;
    switch (gMapHeader.mapType)
    {
    case MAP_TYPE_TOWN:
    case MAP_TYPE_CITY:
    case MAP_TYPE_ROUTE:
        break;
    case MAP_TYPE_UNDERGROUND:
        if (MetatileBehavior_IsIndoorEncounter(tileBehavior))
            return KANTO_BATTLE_TERRAIN_BUILDING;
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return KANTO_BATTLE_TERRAIN_POND;
        return KANTO_BATTLE_TERRAIN_CAVE;
    case MAP_TYPE_INDOOR:
    case MAP_TYPE_SECRET_BASE:
        return KANTO_BATTLE_TERRAIN_BUILDING;
    case MAP_TYPE_UNDERWATER:
        return KANTO_BATTLE_TERRAIN_UNDERWATER;
    case MAP_TYPE_OCEAN_ROUTE:
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return KANTO_BATTLE_TERRAIN_WATER;
        return KANTO_BATTLE_TERRAIN_PLAIN;
    }
    if (MetatileBehavior_IsDeepOrOceanWater(tileBehavior))
        return KANTO_BATTLE_TERRAIN_WATER;
    if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
        return KANTO_BATTLE_TERRAIN_POND;
    if (MetatileBehavior_IsMountain(tileBehavior))
        return KANTO_BATTLE_TERRAIN_MOUNTAIN;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
    {
        if (MetatileBehavior_GetBridgeType(tileBehavior))
            return KANTO_BATTLE_TERRAIN_POND;
        if (MetatileBehavior_IsBridgeOverWater(tileBehavior) == TRUE)
            return KANTO_BATTLE_TERRAIN_WATER;
    }
    return KANTO_BATTLE_TERRAIN_PLAIN;
}
