// Copié de Rouge Feu (src/field_specials.c) : ascenseurs (Sylphe SARL, repaire Rocket, Centre
// Commercial de Céladopole, Tour des Dresseurs) et special ListMenu (listes de choix des scripts).
// Textes : src/data/text/*_fr.h de RF (sText_ -> sText_). Variables RF préfixées KANTO_.
#include "global.h"
#include "bg.h"
#include "event_data.h"
#include "field_camera.h"
#include "fieldmap.h"
#include "list_menu.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/kanto/menu.h"
#include "constants/kanto/metatile_labels.h"

static const u8 sText_10F[] = _("9{SUPER_E}");
static const u8 sText_11F[] = _("10{SUPER_E}");
static const u8 sText_1F[] = _("RC");
static const u8 sText_2F[] = _("1{SUPER_ER}");
static const u8 sText_3F[] = _("2{SUPER_E}");
static const u8 sText_4F[] = _("3{SUPER_E}");
static const u8 sText_5F[] = _("4{SUPER_E}");
static const u8 sText_6F[] = _("5{SUPER_E}");
static const u8 sText_7F[] = _("6{SUPER_E}");
static const u8 sText_8F[] = _("7{SUPER_E}");
static const u8 sText_9F[] = _("8{SUPER_E}");
static const u8 sText_B1F[] = _("1 SS");
static const u8 sText_B2F[] = _("2 SS");
static const u8 sText_B3F[] = _("3 SS");
static const u8 sText_B4F[] = _("4 SS");
static const u8 sText_Rooftop[] = _("TOIT");
static const u8 sText_BoulderBadge[] = _("BADGE ROCHE");
static const u8 sText_Calcium_1000[] = _("CALCIUM{CLEAR_TO 0x6A}{FONT_SMALL}1000");
static const u8 sText_Carbos_1000[] = _("CARBONE{CLEAR_TO 0x6A}{FONT_SMALL}1000");
static const u8 sText_CascadeBadge[] = _("BADGECASCADE");
static const u8 sText_DirectCorner[] = _("SALLE LINK DIRECT");
static const u8 sText_EarthBadge[] = _("BADGE TERRE");
static const u8 sText_EnergyRoot_80[] = _("RACINENERGIE{CLEAR_TO 0x74}{FONT_SMALL}80");
static const u8 sText_Energypowder_50[] = _("POUDRENERGIE{CLEAR_TO 0x74}{FONT_SMALL}50");
static const u8 sText_HealPowder_50[] = _("POUDRE SOIN{CLEAR_TO 0x74}{FONT_SMALL}50");
static const u8 sText_HpUp_1000[] = _("PV PLUS{CLEAR_TO 0x6A}{FONT_SMALL}1000");
static const u8 sText_Iron_1000[] = _("FER{CLEAR_TO 0x6A}{FONT_SMALL}1000");
static const u8 sText_LinkedGamePlay[] = _("JEU EN LINK");
static const u8 sText_MarshBadge[] = _("BADGE MARAIS");
static const u8 sText_PpUp_3000[] = _("PP PLUS{CLEAR_TO 0x6A}{FONT_SMALL}3000");
static const u8 sText_Protein_1000[] = _("PROTEINE{CLEAR_TO 0x6A}{FONT_SMALL}1000");
static const u8 sText_RainbowBadge[] = _("BADGE PRISME");
static const u8 sText_RevivalHerb_300[] = _("HERBE RAPPEL{CLEAR_TO 0x6F}{FONT_SMALL}300");
static const u8 sText_SoulBadge[] = _("BADGE AME");
static const u8 sText_ThunderBadge[] = _("BADGE FOUDRE");
static const u8 sText_UnionRoom[] = _("SALLE UNION");
static const u8 sText_VolcanoBadge[] = _("BADGE VOLCAN");
static const u8 sText_Zinc_1000[] = _("ZINC{CLEAR_TO 0x6A}{FONT_SMALL}1000");
static const u8 sText_NowOn[] = _("Niveau:");

static EWRAM_DATA u8 sElevatorCurrentFloorWindowId = 0;
static EWRAM_DATA u16 sElevatorScroll = 0;
static EWRAM_DATA u16 sElevatorCursorPos = 0;
static EWRAM_DATA struct ListMenuItem * sListMenuItems = NULL;
static EWRAM_DATA u16 sListMenuLastScrollPosition = 0;

static void Task_ElevatorShake(u8 taskId);
static void AnimateElevatorWindowView(u16 nfloors, bool8 direction);
static void Task_AnimateElevatorWindowView(u8 taskId);
static void Task_CreateScriptListMenu(u8 taskId);
static void CreateScriptListMenu(void);
static void ScriptListMenuMoveCursorFunction(s32 nothing, bool8 is, struct ListMenu * used);
static void Task_ListMenuHandleInput(u8 taskId);
static void Task_DestroyListMenu(u8 taskId);
static void Task_SuspendListMenu(u8 taskId);
static void Task_RedrawScrollArrowsAndWaitInput(u8 taskId);
static void Task_CreateMenuRemoveScrollIndicatorArrowPair(u8 taskId);
static void Task_ListMenuRemoveScrollIndicatorArrowPair(u8 taskId);
static u16 GetStarterSpeciesById(u16 starterIdx);

static const struct WindowTemplate sElevatorCurrentFloorWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 22,
    .tilemapTop = 1,
    .width = 7,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 0x008
};

static const u8 *const sFloorNamePointers[] = {
    sText_B4F,
    sText_B3F,
    sText_B2F,
    sText_B1F,
    sText_1F,
    sText_2F,
    sText_3F,
    sText_4F,
    sText_5F,
    sText_6F,
    sText_7F,
    sText_8F,
    sText_9F,
    sText_10F,
    sText_11F,
    sText_Rooftop
};

// Unused
static const u8 sFloorNameWidthPadding[] = {
    26,
    26,
    26,
    26,
    30,
    30,
    30,
    30,
    30,
    30,
    30,
    30,
    30,
    26,
    26,
    18
};

static const u16 sElevatorWindowMetatilesGoingUp[][3] = {
    {
        METATILE_SilphCo_ElevatorWindow_Top0, 
        METATILE_SilphCo_ElevatorWindow_Top1, 
        METATILE_SilphCo_ElevatorWindow_Top2
    },
    {
        METATILE_SilphCo_ElevatorWindow_Mid0, 
        METATILE_SilphCo_ElevatorWindow_Mid1, 
        METATILE_SilphCo_ElevatorWindow_Mid2
    },
    {
        METATILE_SilphCo_ElevatorWindow_Bottom0, 
        METATILE_SilphCo_ElevatorWindow_Bottom1, 
        METATILE_SilphCo_ElevatorWindow_Bottom2
    }
};

static const u16 sElevatorWindowMetatilesGoingDown[][3] = {
    {
        METATILE_SilphCo_ElevatorWindow_Top0, 
        METATILE_SilphCo_ElevatorWindow_Top2, 
        METATILE_SilphCo_ElevatorWindow_Top1
    },
    {
        METATILE_SilphCo_ElevatorWindow_Mid0, 
        METATILE_SilphCo_ElevatorWindow_Mid2, 
        METATILE_SilphCo_ElevatorWindow_Mid1
    },
    {
        METATILE_SilphCo_ElevatorWindow_Bottom0, 
        METATILE_SilphCo_ElevatorWindow_Bottom2, 
        METATILE_SilphCo_ElevatorWindow_Bottom1
    }
};

static const u8 sElevatorAnimationDuration[] = {
    8,
    16,
    24,
    32,
    38,
    46,
    53,
    56,
    57
};

static const u8 sElevatorWindowAnimDuration[] = {
    3,
    6,
    9,
    12,
    15,
    18,
    21,
    24,
    27
};

void GetElevatorFloor(void)
{
    u16 floor = 4;
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(MAP_ROCKET_HIDEOUT_B1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(MAP_SILPH_CO_1F):
            floor = 4;
            break;
        case MAP_NUM(MAP_SILPH_CO_2F):
            floor = 5;
            break;
        case MAP_NUM(MAP_SILPH_CO_3F):
            floor = 6;
            break;
        case MAP_NUM(MAP_SILPH_CO_4F):
            floor = 7;
            break;
        case MAP_NUM(MAP_SILPH_CO_5F):
            floor = 8;
            break;
        case MAP_NUM(MAP_SILPH_CO_6F):
            floor = 9;
            break;
        case MAP_NUM(MAP_SILPH_CO_7F):
            floor = 10;
            break;
        case MAP_NUM(MAP_SILPH_CO_8F):
            floor = 11;
            break;
        case MAP_NUM(MAP_SILPH_CO_9F):
            floor = 12;
            break;
        case MAP_NUM(MAP_SILPH_CO_10F):
            floor = 13;
            break;
        case MAP_NUM(MAP_SILPH_CO_11F):
            floor = 14;
            break;
        case MAP_NUM(MAP_ROCKET_HIDEOUT_B1F):
            floor = 3;
            break;
        case MAP_NUM(MAP_ROCKET_HIDEOUT_B2F):
            floor = 2;
            break;
        case MAP_NUM(MAP_ROCKET_HIDEOUT_B4F):
            floor = 0;
            break;
        }
    }
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(MAP_CELADON_CITY_DEPARTMENT_STORE_1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_1F):
            floor = 4;
            break;
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_2F):
            floor = 5;
            break;
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_3F):
            floor = 6;
            break;
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_4F):
            floor = 7;
            break;
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_5F):
            floor = 8;
            break;
        }
    }
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(MAP_TRAINER_TOWER_1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(MAP_TRAINER_TOWER_1F):
        case MAP_NUM(MAP_TRAINER_TOWER_2F):
        case MAP_NUM(MAP_TRAINER_TOWER_3F):
        case MAP_NUM(MAP_TRAINER_TOWER_4F):
        case MAP_NUM(MAP_TRAINER_TOWER_5F):
        case MAP_NUM(MAP_TRAINER_TOWER_6F):
        case MAP_NUM(MAP_TRAINER_TOWER_7F):
        case MAP_NUM(MAP_TRAINER_TOWER_8F):
        case MAP_NUM(MAP_TRAINER_TOWER_ROOF):
            floor = 15;
            break;
        case MAP_NUM(MAP_TRAINER_TOWER_LOBBY):
            floor = 3;
            break;
        }
    }
    VarSet(VAR_KANTO_ELEVATOR_FLOOR, floor);
}

u16 InitElevatorFloorSelectMenuPos(void)
{
    sElevatorScroll = 0;
    sElevatorCursorPos = 0;

    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(MAP_ROCKET_HIDEOUT_B1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(MAP_SILPH_CO_11F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 0;
            break;
        case MAP_NUM(MAP_SILPH_CO_10F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 1;
            break;
        case MAP_NUM(MAP_SILPH_CO_9F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 2;
            break;
        case MAP_NUM(MAP_SILPH_CO_8F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 3;
            break;
        case MAP_NUM(MAP_SILPH_CO_7F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(MAP_SILPH_CO_6F):
            sElevatorScroll = 1;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(MAP_SILPH_CO_5F):
            sElevatorScroll = 2;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(MAP_SILPH_CO_4F):
            sElevatorScroll = 3;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(MAP_SILPH_CO_3F):
            sElevatorScroll = 4;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(MAP_SILPH_CO_2F):
            sElevatorScroll = 5;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(MAP_SILPH_CO_1F):
            sElevatorScroll = 5;
            sElevatorCursorPos = 5;
            break;
        case MAP_NUM(MAP_ROCKET_HIDEOUT_B1F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 0;
            break;
        case MAP_NUM(MAP_ROCKET_HIDEOUT_B2F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 1;
            break;
        case MAP_NUM(MAP_ROCKET_HIDEOUT_B4F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 2;
            break;
        }
    }
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(MAP_CELADON_CITY_DEPARTMENT_STORE_1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_5F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 0;
            break;
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_4F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 1;
            break;
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_3F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 2;
            break;
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_2F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 3;
            break;
        case MAP_NUM(MAP_CELADON_CITY_DEPARTMENT_STORE_1F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 4;
            break;
        }
    }
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(MAP_TRAINER_TOWER_1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(MAP_TRAINER_TOWER_1F):
        case MAP_NUM(MAP_TRAINER_TOWER_2F):
        case MAP_NUM(MAP_TRAINER_TOWER_3F):
        case MAP_NUM(MAP_TRAINER_TOWER_4F):
        case MAP_NUM(MAP_TRAINER_TOWER_5F):
        case MAP_NUM(MAP_TRAINER_TOWER_6F):
        case MAP_NUM(MAP_TRAINER_TOWER_7F):
        case MAP_NUM(MAP_TRAINER_TOWER_8F):
        case MAP_NUM(MAP_TRAINER_TOWER_ROOF):
            sElevatorScroll = 0;
            sElevatorCursorPos = 0;
            break;
        case MAP_NUM(MAP_TRAINER_TOWER_LOBBY):
            sElevatorScroll = 0;
            sElevatorCursorPos = 1;
            break;
        }
    }
    return sElevatorCursorPos;
}

void AnimateElevator(void)
{
    u16 nfloors;
    s16 *data = gTasks[CreateTask(Task_ElevatorShake, 9)].data;
    data[1] = 0;
    data[2] = 0;
    data[4] = 1;
    if (gSpecialVar_0x8005 > gSpecialVar_0x8006)
    {
        nfloors = gSpecialVar_0x8005 - gSpecialVar_0x8006;
        data[6] = 1;
    }
    else
    {
        nfloors = gSpecialVar_0x8006 - gSpecialVar_0x8005;
        data[6] = 0;
    }
    if (nfloors > 8)
        nfloors = 8;
    data[5] = sElevatorAnimationDuration[nfloors];
    SetCameraPanningCallback(NULL);
    AnimateElevatorWindowView(nfloors, data[6]);
    PlaySE(SE_ELEVATOR);
}

static void Task_ElevatorShake(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    data[1]++;
    if ((data[1] % 3) == 0)
    {
        data[1] = 0;
        data[2]++;
        data[4] = -data[4];
        SetCameraPanning(0, data[4]);
        if (data[2] == data[5])
        {
            PlaySE(SE_DING_DONG);
            DestroyTask(taskId);
            ScriptContext_Enable();
            InstallCameraPanAheadCallback();
        }
    }
}

void DrawElevatorCurrentFloorWindow(void)
{
    const u8 *floorname;
    u32 strwidth;

    sElevatorCurrentFloorWindowId = AddWindow(&sElevatorCurrentFloorWindowTemplate);
    LoadStdWindowGfx(sElevatorCurrentFloorWindowId, 0x21D, BG_PLTT_ID(13));
    DrawStdFrameWithCustomTileAndPalette(sElevatorCurrentFloorWindowId, FALSE, 0x21D, 13);
    AddTextPrinterParameterized(sElevatorCurrentFloorWindowId, FONT_NORMAL, sText_NowOn, 0, 2, 0xFF, NULL);
    floorname = sFloorNamePointers[gSpecialVar_0x8005];
    strwidth = GetStringWidth(FONT_NORMAL, floorname, 0);
    AddTextPrinterParameterized(sElevatorCurrentFloorWindowId, FONT_NORMAL, floorname, 56 - strwidth, 16, 0xFF, NULL);
    PutWindowTilemap(sElevatorCurrentFloorWindowId);
    CopyWindowToVram(sElevatorCurrentFloorWindowId, COPYWIN_FULL);
}

void CloseElevatorCurrentFloorWindow(void)
{
    ClearStdWindowAndFrameToTransparent(sElevatorCurrentFloorWindowId, TRUE);
    RemoveWindow(sElevatorCurrentFloorWindowId);
}

static void AnimateElevatorWindowView(u16 nfloors, u8 direction)
{
    u8 taskId;
    if (FuncIsActiveTask(Task_AnimateElevatorWindowView) != TRUE)
    {
        taskId = CreateTask(Task_AnimateElevatorWindowView, 8);
        gTasks[taskId].data[0] = 0;
        gTasks[taskId].data[1] = 0;
        gTasks[taskId].data[2] = direction;
        gTasks[taskId].data[3] = sElevatorWindowAnimDuration[nfloors];
    }
}

static void Task_AnimateElevatorWindowView(u8 taskId)
{
    u8 i;
    u8 j;
    s16 *data = gTasks[taskId].data;
    if (data[1] == 6)
    {
        data[0]++;
        if (data[2] == 0)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                    MapGridSetMetatileIdAt(j + 1 + MAP_OFFSET, i + MAP_OFFSET, sElevatorWindowMetatilesGoingUp[i][data[0] % 3] | MAPGRID_COLLISION_MASK);
            }
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                    MapGridSetMetatileIdAt(j + 1 + MAP_OFFSET, i + MAP_OFFSET, sElevatorWindowMetatilesGoingDown[i][data[0] % 3] | MAPGRID_COLLISION_MASK);
            }
        }
        DrawWholeMapView();
        data[1] = 0;
        if (data[0] == data[3])
            DestroyTask(taskId);
    }
    data[1]++;
}

void ListMenu(void)
{
    u8 taskId;
    struct Task *task;

    taskId = CreateTask(Task_CreateScriptListMenu, 8);
    task = &gTasks[taskId];
    switch (gSpecialVar_0x8004)
    {
    case LISTMENU_BADGES:
        task->data[0] = 4;
        task->data[1] = 9;
        task->data[2] = 1;
        task->data[3] = 1;
        task->data[4] = 12;
        task->data[5] = 7;
        task->data[6] = 1;
        task->data[15] = taskId;
        break;
    case LISTMENU_SILPHCO_FLOORS:
        task->data[0] = 7;
        task->data[1] = 12;
        task->data[2] = 1;
        task->data[3] = 1;
        task->data[4] = 8;
        task->data[5] = 12;
        task->data[6] = 0;
        task->data[15] = taskId;
        task->data[7] = sElevatorScroll;
        task->data[8] = sElevatorCursorPos;
        break;
    case LISTMENU_ROCKET_HIDEOUT_FLOORS: // Multichoice used instead
        task->data[0] = 4;
        task->data[1] = 4;
        task->data[2] = 1;
        task->data[3] = 1;
        task->data[4] = 8;
        task->data[5] = 8;
        task->data[6] = 0;
        task->data[15] = taskId;
        break;
    case LISTMENU_DEPT_STORE_FLOORS: // Multichoice used instead
        task->data[0] = 4;
        task->data[1] = 6;
        task->data[2] = 1;
        task->data[3] = 1;
        task->data[4] = 8;
        task->data[5] = 8;
        task->data[6] = 0;
        task->data[15] = taskId;
        break;
    case LISTMENU_WIRELESS_LECTURE_HEADERS: // Multichoice used instead
        task->data[0] = 4;
        task->data[1] = 4;
        task->data[2] = 1;
        task->data[3] = 1;
        task->data[4] = 17;
        task->data[5] = 8;
        task->data[6] = 1;
        task->data[15] = taskId;
        break;
    case LISTMENU_BERRY_POWDER:
        task->data[0] = 7;
        task->data[1] = 12;
        task->data[2] = 16;
        task->data[3] = 1;
        task->data[4] = 17;
        task->data[5] = 12;
        task->data[6] = 0;
        task->data[15] = taskId;
        break;
    case LISTMENU_TRAINER_TOWER_FLOORS: // Mulitchoice used instead
        task->data[0] = 3;
        task->data[1] = 3;
        task->data[2] = 1;
        task->data[3] = 1;
        task->data[4] = 8;
        task->data[5] = 6;
        task->data[6] = 0;
        task->data[15] = taskId;
        break;
    case 99:
        break;
    default:
        gSpecialVar_Result = 0x7F;
        DestroyTask(taskId);
        break;
    }
}

static const u8 *const sListMenuLabels[][12] = {
    [LISTMENU_BADGES] = 
    {
        sText_BoulderBadge,
        sText_CascadeBadge,
        sText_ThunderBadge,
        sText_RainbowBadge,
        sText_SoulBadge,
        sText_MarshBadge,
        sText_VolcanoBadge,
        sText_EarthBadge,
        gOtherText_Exit,
    }, 
    [LISTMENU_SILPHCO_FLOORS] = 
    {
        sText_11F,
        sText_10F,
        sText_9F,
        sText_8F,
        sText_7F,
        sText_6F,
        sText_5F,
        sText_4F,
        sText_3F,
        sText_2F,
        sText_1F,
        gOtherText_Exit,
    }, 
    [LISTMENU_ROCKET_HIDEOUT_FLOORS] = // Unncessary, MULTICHOICE_ROCKET_HIDEOUT_ELEVATOR is used instead
    {
        sText_B1F,
        sText_B2F,
        sText_B4F,
        gOtherText_Exit,
    }, 
    [LISTMENU_DEPT_STORE_FLOORS] = // Unncessary, MULTICHOICE_DEPT_STORE_ELEVATOR is used instead
    {
        sText_5F,
        sText_4F,
        sText_3F,
        sText_2F,
        sText_1F,
        gOtherText_Exit,
    }, 
    [LISTMENU_WIRELESS_LECTURE_HEADERS] = // Unnecessary, MULTICHOICE_LINKED_DIRECT_UNION is used instead
    {
        sText_LinkedGamePlay,
        sText_DirectCorner,
        sText_UnionRoom,
        gOtherText_Quit,
    }, 
    [LISTMENU_BERRY_POWDER] = 
    {
        sText_Energypowder_50,
        sText_EnergyRoot_80,
        sText_HealPowder_50,
        sText_RevivalHerb_300,
        sText_Protein_1000,
        sText_Iron_1000,
        sText_Carbos_1000,
        sText_Calcium_1000,
        sText_Zinc_1000,
        sText_HpUp_1000,
        sText_PpUp_3000,
        gOtherText_Exit,
    }, 
    [LISTMENU_TRAINER_TOWER_FLOORS] = // Unnecessary, MULTICHOICE_ROOFTOP_B1F is used instead
    {
        sText_Rooftop,
        sText_B1F,
        gOtherText_Exit,
    }
};

static void Task_CreateScriptListMenu(u8 taskId)
{
    struct WindowTemplate template;
    u8 i;
    s32 width;
    s32 mwidth;
    struct Task *task = &gTasks[taskId];
    u8 windowId;
    LockPlayerFieldControls();
    if (gSpecialVar_0x8004 == LISTMENU_SILPHCO_FLOORS)
        sListMenuLastScrollPosition = sElevatorScroll;
    else
        sListMenuLastScrollPosition = 0;
    sListMenuItems = AllocZeroed(task->data[1] * sizeof(struct ListMenuItem));
    CreateScriptListMenu();
    mwidth = 0;
    for (i = 0; i < task->data[1]; i++)
    {
        sListMenuItems[i].label = sListMenuLabels[gSpecialVar_0x8004][i];
        sListMenuItems[i].index = i;
        width = GetStringWidth(FONT_NORMAL, sListMenuItems[i].label, 0);
        if (width > mwidth)
            mwidth = width;
    }
    task->data[4] = (mwidth + 9) / 8 + 1;
    if (task->data[2] + task->data[4] > 29)
        task->data[2] = 29 - task->data[4];
    template = SetWindowTemplateFields(0, task->data[2], task->data[3], task->data[4], task->data[5], 15, 0x038);
    task->data[13] = windowId = AddWindow(&template);
    SetStdWindowBorderStyle(task->data[13], 0);
    sFieldSpecialsListMenuTemplate.totalItems = task->data[1];
    sFieldSpecialsListMenuTemplate.maxShowed = task->data[0];
    sFieldSpecialsListMenuTemplate.windowId = task->data[13];
    Task_CreateMenuRemoveScrollIndicatorArrowPair(taskId);
    task->data[14] = ListMenuInit(&sFieldSpecialsListMenuTemplate, task->data[7], task->data[8]);
    PutWindowTilemap(task->data[13]);
    CopyWindowToVram(task->data[13], COPYWIN_FULL);
    gTasks[taskId].func = Task_ListMenuHandleInput;
}

static void CreateScriptListMenu(void)
{
    sFieldSpecialsListMenuTemplate.items = sListMenuItems;
    sFieldSpecialsListMenuTemplate.moveCursorFunc = ScriptListMenuMoveCursorFunction;
    sFieldSpecialsListMenuTemplate.itemPrintFunc = NULL;
    sFieldSpecialsListMenuTemplate.totalItems = 1;
    sFieldSpecialsListMenuTemplate.maxShowed = 1;
    sFieldSpecialsListMenuTemplate.windowId = 0;
    sFieldSpecialsListMenuTemplate.header_X = 0;
    sFieldSpecialsListMenuTemplate.item_X = 8;
    sFieldSpecialsListMenuTemplate.cursor_X = 0;
    sFieldSpecialsListMenuTemplate.upText_Y = 0;
    sFieldSpecialsListMenuTemplate.cursorPal = 2;
    sFieldSpecialsListMenuTemplate.fillValue = 1;
    sFieldSpecialsListMenuTemplate.cursorShadowPal = 3;
    sFieldSpecialsListMenuTemplate.lettersSpacing = 1;
    sFieldSpecialsListMenuTemplate.itemVerticalPadding = 0;
    sFieldSpecialsListMenuTemplate.scrollMultiple = 0;
    sFieldSpecialsListMenuTemplate.fontId = FONT_NORMAL;
    sFieldSpecialsListMenuTemplate.cursorKind = 0;
}

static void ScriptListMenuMoveCursorFunction(s32 nothing, bool8 is, struct ListMenu * used)
{
    u8 taskId;
    struct Task *task;
    PlaySE(SE_SELECT);
    taskId = FindTaskIdByFunc(Task_ListMenuHandleInput);
    if (taskId != 0xFF)
    {
        task = &gTasks[taskId];
        ListMenuGetScrollAndRow(task->data[14], &sFieldSpecialsListMenuScrollBuffer, NULL);
        sListMenuLastScrollPosition = sFieldSpecialsListMenuScrollBuffer;
    }
}

static void Task_ListMenuHandleInput(u8 taskId)
{
    s32 input;
    struct Task *task;

    task = &gTasks[taskId];
    task++;task--;
    input = ListMenu_ProcessInput(task->data[14]);
    switch (input)
    {
    case -1:
        break;
    case -2:
        gSpecialVar_Result = 0x7F;
        PlaySE(SE_SELECT);
        Task_DestroyListMenu(taskId);
        break;
    default:
        gSpecialVar_Result = input;
        PlaySE(SE_SELECT);
        if (task->data[6] == 0 || input == task->data[1] - 1)
        {
            Task_DestroyListMenu(taskId);
        }
        else
        {
            Task_ListMenuRemoveScrollIndicatorArrowPair(taskId);
            task->func = Task_SuspendListMenu;
            ScriptContext_Enable();
        }
        break;
    }
}

static void Task_DestroyListMenu(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    Task_ListMenuRemoveScrollIndicatorArrowPair(taskId);
    DestroyListMenuTask(task->data[14], NULL, NULL);
    Free(sListMenuItems);
    ClearStdWindowAndFrameToTransparent(task->data[13], TRUE);
    FillWindowPixelBuffer(task->data[13], PIXEL_FILL(0));
    ClearWindowTilemap(task->data[13]);
    CopyWindowToVram(task->data[13], COPYWIN_GFX);
    RemoveWindow(task->data[13]);
    DestroyTask(taskId);
    ScriptContext_Enable();
}

static void Task_SuspendListMenu(u8 taskId)
{
    switch (gTasks[taskId].data[6])
    {
    case 1:
        break;
    case 2:
        gTasks[taskId].data[6] = 1;
        gTasks[taskId].func = Task_RedrawScrollArrowsAndWaitInput;
        break;
    }
}

void ReturnToListMenu(void)
{
    u8 taskId = FindTaskIdByFunc(Task_SuspendListMenu);
    if (taskId == 0xFF)
        ScriptContext_Enable();
    else
        gTasks[taskId].data[6]++;
}

static void Task_RedrawScrollArrowsAndWaitInput(u8 taskId)
{
    LockPlayerFieldControls();
    Task_CreateMenuRemoveScrollIndicatorArrowPair(taskId);
    gTasks[taskId].func = Task_ListMenuHandleInput;
}

static void Task_CreateMenuRemoveScrollIndicatorArrowPair(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    struct ScrollArrowsTemplate template = {
        .firstArrowType = 2,
        .secondArrowType = 3,
        .tileTag = 2000,
        .palTag = 100
    };
    if (task->data[0] != task->data[1])
    {
        template.firstX = 4 * task->data[4] + 8 * task->data[2];
        template.firstY = 8;
        template.secondX = 4 * task->data[4] + 8 * task->data[2];
        template.secondY = 8 * task->data[5] + 10;
        template.fullyUpThreshold = 0;
        template.fullyDownThreshold = task->data[1] - task->data[0];
        task->data[12] = AddScrollIndicatorArrowPair(&template, &sListMenuLastScrollPosition);
    }
}

static void Task_ListMenuRemoveScrollIndicatorArrowPair(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    if (task->data[0] != task->data[1])
        RemoveScrollIndicatorArrowPair(task->data[12]);
}

