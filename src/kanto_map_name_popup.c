// PokemonNative3G : panneau du nom de lieu de Rouge Feu (map_name_popup.c de RF), sur les cartes de Kanto (choix user
// 2026-11-02 : comme la carte de dresseur, il suit la région) ; Hoenn garde celui d'Émeraude (map_name_popup.c).
// Boîte au cadre standard de RF qui glisse en haut à gauche, avec l'étage (floor_number des cartes, réimporté :
// tools/kanto/add_floor_numbers.py). Adaptations de la fusion :
// - ShowMapNamePopup / DismissMapNamePopup / IsMapNamePopupTaskActive de RF = Kanto_* (noms pris par Émeraude) ;
// - FLAG_DONT_SHOW_MAP_NAME_POPUP de RF = FLAG_HIDE_MAP_NAME_POPUP (même drapeau spécial) ; le journal de RF
//   (QL_IS_PLAYBACK_STATE) est écarté ;
// - FONT_NORMAL de RF = FONT_KANTO ; GetTextWindowPalette(3) et LoadStdWindowTiles de RF : kanto_bag.c.
#include "global.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "kanto_map_name_popup.h"
#include "menu.h"
#include "palette.h"
#include "region_map.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/flags.h"
#include "kanto_bag_compat.h" // LoadStdWindowTiles, Kanto_GetStdTextWindowPalette ; en dernier : ses #define

#define FLOOR_ROOFTOP 127

static void Task_MapNamePopup(u8 taskId);
static u16 MapNamePopupCreateWindow(bool32 palIntoFadedBuffer);
static void MapNamePopupPrintMapNameOnWindow(u16 windowId);
static u8 *MapNamePopupAppendFloorNum(u8 *dest, s8 flags);

// Textes de RF (strings_1_fr.h du décomp)
static const u8 sKText_Text_1F[] = _("RC");
static const u8 sKText_Text_2F[] = _("1{SUPER_ER}");
static const u8 sKText_Text_3F[] = _("2{SUPER_E}");
static const u8 sKText_Text_4F[] = _("3{SUPER_E}");
static const u8 sKText_Text_5F[] = _("4{SUPER_E}");
static const u8 sKText_Text_6F[] = _("5{SUPER_E}");
static const u8 sKText_Text_7F[] = _("6{SUPER_E}");
static const u8 sKText_Text_8F[] = _("7{SUPER_E}");
static const u8 sKText_Text_9F[] = _("8{SUPER_E}");
static const u8 sKText_Text_10F[] = _("9{SUPER_E}");
static const u8 sKText_Text_11F[] = _("10{SUPER_E}");
static const u8 sKText_Text_B1F[] = _("1 SS");
static const u8 sKText_Text_B2F[] = _("2 SS");
static const u8 sKText_Text_B3F[] = _("3 SS");
static const u8 sKText_Text_B4F[] = _("4 SS");
static const u8 sKText_Text_Rooftop[] = _("TOIT");
static const u8 sKText_Text_Rooftop2[] = _("TOIT");

#define tState              data[0]
#define tTimer              data[1]
#define tPos                data[2]
#define tReshow             data[3]
#define tWindowId           data[4]
#define tWindowExists       data[5]
#define tWindowCleared      data[6]
#define tWindowDestroyed    data[7]
#define tPalIntoFadedBuffer data[8]

// ShowMapNamePopup de RF
void Kanto_ShowMapNamePopup(bool32 palIntoFadedBuffer)
{
    u8 taskId;
    if (FlagGet(FLAG_HIDE_MAP_NAME_POPUP) != TRUE)
    {
        taskId = FindTaskIdByFunc(Task_MapNamePopup);
        if (taskId == TASK_NONE)
        {
            taskId = CreateTask(Task_MapNamePopup, 90);
            ChangeBgX(0,  0x0000, BG_COORD_SET);
            ChangeBgY(0, -0x1081, BG_COORD_SET);
            gTasks[taskId].tState = 0;
            gTasks[taskId].tPos = 0;
            gTasks[taskId].tPalIntoFadedBuffer = palIntoFadedBuffer;
        }
        else
        {
            if (gTasks[taskId].tState != 4)
                gTasks[taskId].tState = 4;
            gTasks[taskId].tReshow = TRUE;
        }
    }
}

static void Task_MapNamePopup(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    switch (task->tState)
    {
    case 0:
        task->tWindowId = MapNamePopupCreateWindow(task->tPalIntoFadedBuffer);
        task->tWindowExists = TRUE;
        task->tState = 1;
        break;
    case 1:
        if (IsDma3ManagerBusyWithBgCopy())
            break;
        // fallthrough
    case 2:
        task->tPos -= 2;
        if (task->tPos <= -24)
        {
            task->tState = 3;
            task->tTimer = 0;
        }
        break;
    case 3:
        task->tTimer++;
        if (task->tTimer > 120)
        {
            task->tTimer = 0;
            task->tState = 4;
        }
        break;
    case 4:
        task->tPos += 2;
        if (task->tPos >= 0)
        {
            if (task->tReshow)
            {
                MapNamePopupPrintMapNameOnWindow(task->tWindowId);
                CopyWindowToVram(task->tWindowId, COPYWIN_GFX);
                task->tState = 1;
                task->tReshow = FALSE;
            }
            else
            {
                task->tState = 6;
                return;
            }
        }
        // fallthrough
    case 5:
        break;
    case 6:
        if (task->tWindowExists && !task->tWindowCleared)
        {
            rbox_fill_rectangle(task->tWindowId);
            CopyWindowToVram(task->tWindowId, COPYWIN_MAP);
            task->tWindowCleared = TRUE;
        }
        task->tState = 7;
        return;
    case 7:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            if (task->tWindowExists)
            {
                RemoveWindow(task->tWindowId);
                task->tWindowExists = FALSE;
                task->tWindowDestroyed = TRUE;
            }
            task->tState = 8;
            ChangeBgY(0, 0x00000000, BG_COORD_SET);
        }
        return;
    case 8:
        DestroyTask(taskId);
        return;
    }
    SetGpuReg(REG_OFFSET_BG0VOFS, task->tPos);
}

// DismissMapNamePopup de RF
void Kanto_DismissMapNamePopup(void)
{
    u8 taskId;
    s16 *data;
    taskId = FindTaskIdByFunc(Task_MapNamePopup);
    if (taskId != TASK_NONE)
    {
        data = gTasks[taskId].data;
        if (tState < 6)
            tState = 6;
    }
}

// IsMapNamePopupTaskActive de RF
bool32 Kanto_IsMapNamePopupTaskActive(void)
{
    return FindTaskIdByFunc(Task_MapNamePopup) != TASK_NONE ? TRUE : FALSE;
}

#define WIN_PAL_NUM  13

static u16 MapNamePopupCreateWindow(bool32 palintoFadedBuffer)
{
    struct WindowTemplate windowTemplate = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 29,
        .width = 14,
        .height = 2,
        .paletteNum = WIN_PAL_NUM,
        .baseBlock = 0x001
    };
    u16 windowId;
    u16 tileNum = 0x01D;
    if (gMapHeader.floorNum != 0)
    {
        if (gMapHeader.floorNum != FLOOR_ROOFTOP)
        {
            windowTemplate.width += 5;
            tileNum = 0x027;
        }
        else
        {
            // ROOFTOP
            windowTemplate.width += 8;
            tileNum = 0x02D;
        }
    }
    windowId = AddWindow(&windowTemplate);
    if (palintoFadedBuffer)
        LoadPalette(Kanto_GetStdTextWindowPalette(), BG_PLTT_ID(WIN_PAL_NUM), PLTT_SIZE_4BPP);
    else
        CpuCopy16(Kanto_GetStdTextWindowPalette(), &gPlttBufferUnfaded[BG_PLTT_ID(WIN_PAL_NUM)], PLTT_SIZE_4BPP);
    LoadStdWindowTiles(windowId, tileNum);
    DrawTextBorderOuter(windowId, tileNum, WIN_PAL_NUM);
    PutWindowTilemap(windowId);
    MapNamePopupPrintMapNameOnWindow(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
    return windowId;
}

static void MapNamePopupPrintMapNameOnWindow(u16 windowId)
{
    u8 mapName[25];
    u32 maxWidth = 112;
    u32 xpos;
    u8 *ptr = GetMapName(mapName, gMapHeader.regionMapSectionId, 0);
    if (gMapHeader.floorNum != 0)
    {
        ptr = MapNamePopupAppendFloorNum(ptr, gMapHeader.floorNum);
        maxWidth = gMapHeader.floorNum != FLOOR_ROOFTOP ? 152 : 176;
    }
    xpos = (maxWidth - GetStringWidth(FONT_KANTO, mapName, -1)) / 2;
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    AddTextPrinterParameterized(windowId, FONT_KANTO, mapName, xpos, 2, TEXT_SKIP_DRAW, NULL);
}

static const u8 *const sFloorNamePointers_up[] = {
    sKText_Text_1F,
    sKText_Text_2F,
    sKText_Text_3F,
    sKText_Text_4F,
    sKText_Text_5F,
    sKText_Text_6F,
    sKText_Text_7F,
    sKText_Text_8F,
    sKText_Text_9F,
    sKText_Text_10F,
    sKText_Text_11F,
    sKText_Text_Rooftop
};

static const u8 *const sFloorNamePointers_down[] = {
    sKText_Text_B1F,
    sKText_Text_B2F,
    sKText_Text_B3F,
    sKText_Text_B4F
};

static u8 *MapNamePopupAppendFloorNum(u8 *dest, s8 floorNum)
{
    if (floorNum == 0)
        return dest;

    *dest++ = CHAR_SPACE;

    if (floorNum == 0x7F)
        return StringCopy(dest, sKText_Text_Rooftop2);

    if (floorNum < 0)
        return StringCopy(dest, sFloorNamePointers_down[~floorNum]);

    return StringCopy(dest, sFloorNamePointers_up[floorNum - 1]);
}

#undef tPalIntoFadedBuffer
#undef tWindowDestroyed
#undef tWindowCleared
#undef tWindowExists
#undef tWindowId
#undef tReshow
#undef tPos
#undef tTimer
#undef tState
