// Rouge Feu : éclairage de la Ligue Pokémon (field_specials.c) et téléporteurs de la maison de Léo
// (special_field_anim.c). La palette 7 du décor de Kanto est celle de RF (tilesets importés sans renumérotation).
#include "global.h"
#include "event_data.h"
#include "field_camera.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "palette.h"
#include "task.h"
#include "constants/maps.h"
#include "constants/rgb.h"

static void Task_RunPokemonLeagueLightingEffect(u8 taskId);
static void Task_CancelPokemonLeagueLightingEffect(u8 taskId);
static void Task_DrawTeleporterHousing(u8 taskId);
static void Task_DrawTeleporterCable(u8 taskId);

// Rouge Feu (constants/metatile_labels.h) : maison de Léo (Route 25)
#define METATILE_SeaCottage_Teleporter_CableBall_Bottom  0x2BA
#define METATILE_SeaCottage_Teleporter_CableBall_Top     0x2B9
#define METATILE_SeaCottage_Teleporter_Cable_Bottom      0x2B4
#define METATILE_SeaCottage_Teleporter_Cable_Top         0x285
#define METATILE_SeaCottage_Teleporter_Door              0x296
#define METATILE_SeaCottage_Teleporter_Door_FullGlowing  0x2B8
#define METATILE_SeaCottage_Teleporter_Door_HalfGlowing  0x2B7
#define METATILE_SeaCottage_Teleporter_Light_Green       0x28A
#define METATILE_SeaCottage_Teleporter_Light_Red         0x2B6
#define METATILE_SeaCottage_Teleporter_Light_Yellow      0x2B5

static const u16 sEliteFourLightingPalettes[][16] = {
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_0.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_1.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_2.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_3.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_4.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_5.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_6.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_7.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_8.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_9.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_10.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/elite_four_lighting_11.pal", ".gbapal")
};

static const u16 sChampionRoomLightingPalettes[][16] = {
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_0.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_1.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_2.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_3.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_4.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_5.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_6.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_7.pal", ".gbapal"),
    INCGFX_U16("graphics/kanto/field_specials/champion_room_lighting_8.pal", ".gbapal")
};

static const u8 sEliteFourLightingTimers[] = {
    40,
    12,
    12,
    12,
    12,
    12,
    12,
    12,
    12,
    12,
    12
};

static const u8 sChampionRoomLightingTimers[] = {
    20,
     8,
     8,
     8,
     8,
     8,
     8,
     8
};

void DoPokemonLeagueLightingEffect(void)
{
    u8 taskId = CreateTask(Task_RunPokemonLeagueLightingEffect, 8);
    s16 *data = gTasks[taskId].data;
    if (FlagGet(FLAG_TEMP_3) == TRUE)
    {
        gTasks[taskId].func = Task_CancelPokemonLeagueLightingEffect;
    }
    else
    {
        if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM))
        {
            data[0] = sChampionRoomLightingTimers[0];
            data[2] = 8;
            LoadPalette(sChampionRoomLightingPalettes[0], BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        }
        else
        {
            data[0] = sEliteFourLightingTimers[0];
            data[2] = 11;
            LoadPalette(sEliteFourLightingPalettes[0], BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        }
        data[1] = 0;
    }
}

static void Task_RunPokemonLeagueLightingEffect(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active
     && FlagGet(FLAG_TEMP_2) != FALSE
     && FlagGet(FLAG_TEMP_5) != TRUE
     && --data[0] == 0
    )
    {
        if (++data[1] == data[2])
            data[1] = 0;

        if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM))
        {
            data[0] = sChampionRoomLightingTimers[data[1]];
            LoadPalette(sChampionRoomLightingPalettes[data[1]], BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        }
        else
        {
            data[0] = sEliteFourLightingTimers[data[1]];
            LoadPalette(sEliteFourLightingPalettes[data[1]], BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        }
    }
}

static void Task_CancelPokemonLeagueLightingEffect(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (FlagGet(FLAG_TEMP_4) != FALSE)
    {
        if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM))
            LoadPalette(sChampionRoomLightingPalettes[8], BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        else
            LoadPalette(sEliteFourLightingPalettes[11], BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        if (gPaletteFade.active)
        {
            BlendPalettes(0x00000080, 16, RGB_BLACK);
        }
        DestroyTask(taskId);
    }
}

void StopPokemonLeagueLightingEffectTask(void)
{
    if (FuncIsActiveTask(Task_RunPokemonLeagueLightingEffect) == TRUE)
    {
        DestroyTask(FindTaskIdByFunc(Task_RunPokemonLeagueLightingEffect));
    }
}

#define tState            data[0]
#define tTimer data[0]
#define tState data[1]
#define tX     data[2]
#define tY     data[3]

void AnimateTeleporterHousing(void)
{
    u8 taskId;
    s16 *data;
    
    taskId = CreateTask(Task_DrawTeleporterHousing, 0);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].tState = 0;
    data = gTasks[taskId].data;
    PlayerGetDestCoords(&tX, &tY);

    // Set the coords of whichever teleporter is being animated
    // 0 for the right teleporter, 1 for the left teleporter
    if (gSpecialVar_0x8004 == 0)
    {
        gTasks[taskId].tX += 6;
        gTasks[taskId].tY -= 5;
    }
    else
    {
        gTasks[taskId].tX -= 1;
        gTasks[taskId].tY -= 5;
    }    
}

static void Task_DrawTeleporterHousing(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    
    if (tTimer == 0)
    {
        // Alternate the teleporter light / brightness of the teleporter door
        if ((tState & 1) == 0)
        {
            MapGridSetMetatileIdAt(tX, tY, METATILE_SeaCottage_Teleporter_Light_Yellow | MAPGRID_COLLISION_MASK);
            MapGridSetMetatileIdAt(tX, tY + 2, METATILE_SeaCottage_Teleporter_Door_HalfGlowing | MAPGRID_COLLISION_MASK);
        }
        else
        {
            MapGridSetMetatileIdAt(tX, tY, METATILE_SeaCottage_Teleporter_Light_Red | MAPGRID_COLLISION_MASK);
            MapGridSetMetatileIdAt(tX, tY + 2, METATILE_SeaCottage_Teleporter_Door_FullGlowing | MAPGRID_COLLISION_MASK);
        }
        CurrentMapDrawMetatileAt(tX, tY);
        CurrentMapDrawMetatileAt(tX, tY + 2);
    }
    
    tTimer++;
    if (tTimer != 16)
        return;
    
    tTimer = 0;
    tState++;
    if (tState != 13)
        return;
    
    MapGridSetMetatileIdAt(tX, tY, METATILE_SeaCottage_Teleporter_Light_Green | MAPGRID_COLLISION_MASK);
    MapGridSetMetatileIdAt(tX, tY + 2, METATILE_SeaCottage_Teleporter_Door | MAPGRID_COLLISION_MASK);
    CurrentMapDrawMetatileAt(tX, tY);
    CurrentMapDrawMetatileAt(tX, tY + 2);
    DestroyTask(taskId);
}

void AnimateTeleporterCable(void)
{
    u8 taskId;
    s16 *data;
    
    taskId = CreateTask(Task_DrawTeleporterCable, 0);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].tState = 0;
    data = gTasks[taskId].data;
    PlayerGetDestCoords(&tX, &tY);
    gTasks[taskId].tX += 4;
    gTasks[taskId].tY -= 5;
}

static void Task_DrawTeleporterCable(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    
    if (tTimer == 0)
    {
        if (tState != 0)
        {
            // Set default cable tiles to clear the ball
            MapGridSetMetatileIdAt(tX, tY, METATILE_SeaCottage_Teleporter_Cable_Top | MAPGRID_COLLISION_MASK);
            MapGridSetMetatileIdAt(tX, tY + 1, METATILE_SeaCottage_Teleporter_Cable_Bottom | MAPGRID_COLLISION_MASK);
            CurrentMapDrawMetatileAt(tX, tY);
            CurrentMapDrawMetatileAt(tX, tY + 1);

            // End after drawing 4 times (length of the cable)
            if (tState == 4)
            {
                DestroyTask(taskId);
                return;
            }
            
            tX--;
        }

        // Draw the cable ball
        MapGridSetMetatileIdAt(tX, tY, METATILE_SeaCottage_Teleporter_CableBall_Top | MAPGRID_COLLISION_MASK);
        MapGridSetMetatileIdAt(tX, tY + 1, METATILE_SeaCottage_Teleporter_CableBall_Bottom | MAPGRID_COLLISION_MASK);
        CurrentMapDrawMetatileAt(tX, tY);
        CurrentMapDrawMetatileAt(tX, tY + 1);
    }
    
    tTimer++;
    if (tTimer == 4)
    {
        tTimer = 0;
        tState++;
    }
}

#undef tTimer
#undef tState
#undef tX
#undef tY
