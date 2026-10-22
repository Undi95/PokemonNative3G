// Rouge Feu : bag.c (option SAC = KANTO)
#include "global.h"
#include "battle.h"
#include "battle_controllers.h"
#include "bg.h"
#include "decompress.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_player_avatar.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "item_icon.h"
#include "item_menu.h"
#include "item_use.h"
#include "link.h"
#include "list_menu.h"
#include "mail.h"
#include "main.h"
#include "malloc.h"
#include "map_name_popup.h"
#include "menu.h"
#include "menu_helpers.h"
#include "money.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "player_pc.h"
#include "pokemon_storage_system.h"
#include "scanline_effect.h"
#include "script.h"
#include "shop.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/items.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "kanto_bag_internal.h"

// Rouge Feu (graphics.c)


// Rouge Feu (strings_1_fr.h)
static const u8 sKText_Text_DepositItem[] = _("DEPOSER OBJET");


static const u16 sBagWindowPalF[] = INCGFX_U16("graphics/kanto/item_menu/bag_window_pal.pal", ".gbapal");

static const u8 sTextColors[][3] = {
    {0, 1, 2},
    {0, 2, 3},
    {0, 3, 2},
    {0, 8, 9}
};

static const struct WindowTemplate sDefaultBagWindowsStd[] = {
    {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 1,
        .width = 18,
        .height = 12,
        .paletteNum = 15,
        .baseBlock = 0x008a
    }, {
        .bg = 0,
        .tilemapLeft = 5,
        .tilemapTop = 14,
        .width = 25,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0162
    }, {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 9,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x01f8
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sDefaultBagWindowsDeposit[] = {
    {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 1,
        .width = 18,
        .height = 12,
        .paletteNum = 15,
        .baseBlock = 0x008a
    }, {
        .bg = 0,
        .tilemapLeft = 5,
        .tilemapTop = 14,
        .width = 25,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0162
    }, {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 8,
        .height = 2,
        .paletteNum = 12,
        .baseBlock = 0x01f8
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sWindowTemplates[] = {
    {
        .bg = 0,
        .tilemapLeft = 24,
        .tilemapTop = 15,
        .width = 5,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x242
    }, {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 9,
        .width = 12,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x242
    }, {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 8,
        .height = 3,
        .paletteNum = 12,
        .baseBlock = 0x272
    }, {
        .bg = 0,
        .tilemapLeft = 23,
        .tilemapTop = 15,
        .width = 6,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x28a
    }, {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 9,
        .width = 6,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x28a
    }, {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x2a2
    }, {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 14,
        .height = 4,
        .paletteNum = 12,
        .baseBlock = 0x2a2
    }, {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 15,
        .height = 4,
        .paletteNum = 12,
        .baseBlock = 0x2da
    }, {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 16,
        .height = 4,
        .paletteNum = 12,
        .baseBlock = 0x316
    }, {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 23,
        .height = 4,
        .paletteNum = 12,
        .baseBlock = 0x356
    }, {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 17,
        .width = 7,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x20a
    }, {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 15,
        .width = 7,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x20a
    }, {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 13,
        .width = 7,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x20a
    }, {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 11,
        .width = 7,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 0x20a
    }
};

static const u8 sUnused[] = {16, 8, 4};

static EWRAM_DATA u8 sOpenWindows[11] = {};

void InitBagWindows(void)
{
    u8 i;

    if (gBagMenuState.location != 3)
        InitWindows(sDefaultBagWindowsStd);
    else
        InitWindows(sDefaultBagWindowsDeposit);
    DeactivateAllTextPrinters();
    LoadUserWindowGfx(0, 0x64, BG_PLTT_ID(14));
    LoadMenuMessageWindowGfx(0, 0x6D, BG_PLTT_ID(13));
    LoadStdWindowGfx(0, 0x81, BG_PLTT_ID(12));
    LoadPalette(sBagWindowPalF, BG_PLTT_ID(15), sizeof(sBagWindowPalF));
    for (i = 0; i < 3; i++)
    {
        FillWindowPixelBuffer(i, 0x00);
        PutWindowTilemap(i);
    }
    ScheduleBgCopyTilemapToVram(0);
    for (i = 0; i < 11; i++)
    {
        sOpenWindows[i] = 0xFF;
    }
}

void BagPrintTextOnWindow(u8 windowId, u8 fontId, const u8 * str, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIdx)
{
    AddTextPrinterParameterized4(windowId, fontId, x, y, letterSpacing, lineSpacing, sTextColors[colorIdx], speed, str);
}

void BagPrintTextOnWin1CenteredColor0(const u8 * str, u8 unused)
{
    u32 x = 0x48 - GetStringWidth(FONT_NORMAL_COPY_1, str, 0);
    AddTextPrinterParameterized3(2, FONT_NORMAL_COPY_1, x / 2, 1, sTextColors[0], 0, str);
}

void BagDrawDepositItemTextBox(void)
{
    u32 x;
    DrawStdFrameWithCustomTileAndPalette(2, FALSE, 0x081, 12);
    x = 0x40 - GetStringWidth(FONT_SMALL, sKText_Text_DepositItem, 0);
    AddTextPrinterParameterized(2, FONT_SMALL, sKText_Text_DepositItem, x / 2, 1, 0, NULL);
}

u8 ShowBagWindow(u8 whichWindow, u8 nItems)
{
    if (sOpenWindows[whichWindow] == 0xFF)
    {
        sOpenWindows[whichWindow] = AddWindow(&sWindowTemplates[whichWindow + nItems]);
        if (whichWindow != 6)
        {
            DrawStdFrameWithCustomTileAndPalette(sOpenWindows[whichWindow], FALSE, 0x064, 14);
        }
        else
        {
            DrawStdFrameWithCustomTileAndPalette(sOpenWindows[whichWindow], FALSE, 0x081, 12);
        }
        ScheduleBgCopyTilemapToVram(0);
    }
    return sOpenWindows[whichWindow];
}

void HideBagWindow(u8 whichWindow)
{
    ClearStdWindowAndFrameToTransparent(sOpenWindows[whichWindow], FALSE);
    ClearWindowTilemap(sOpenWindows[whichWindow]);
    RemoveWindow(sOpenWindows[whichWindow]);
    ScheduleBgCopyTilemapToVram(0);
    sOpenWindows[whichWindow] = 0xFF;
}

u8 OpenBagWindow(u8 whichWindow)
{
    if (sOpenWindows[whichWindow] == 0xFF)
    {
        sOpenWindows[whichWindow] = AddWindow(&sWindowTemplates[whichWindow]);
    }
    return sOpenWindows[whichWindow];
}

void CloseBagWindow(u8 whichWindow)
{
    if (sOpenWindows[whichWindow] != 0xFF)
    {
        ClearDialogWindowAndFrameToTransparent(sOpenWindows[whichWindow], FALSE);
        ClearWindowTilemap(sOpenWindows[whichWindow]);
        RemoveWindow(sOpenWindows[whichWindow]);
        PutWindowTilemap(1);
        ScheduleBgCopyTilemapToVram(0);
        sOpenWindows[whichWindow] = 0xFF;
    }
}

u8 GetBagWindow(u8 whichWindow)
{
    return sOpenWindows[whichWindow];
}

void BagCreateYesNoMenuBottomRight(u8 taskId, const struct YesNoFuncTable * ptrs)
{
    CreateYesNoMenuWithCallbacks(taskId, &sWindowTemplates[3], FONT_NORMAL, 0, 2, 0x064, 14, ptrs);
}

void BagCreateYesNoMenuTopRight(u8 taskId, const struct YesNoFuncTable * ptrs)
{
    CreateYesNoMenuWithCallbacks(taskId, &sWindowTemplates[4], FONT_NORMAL, 0, 2, 0x064, 14, ptrs);
}

void BagPrintMoneyAmount(void)
{
    PrintMoneyAmountInMoneyBoxWithBorder(ShowBagWindow(2, 0), 0x081, 0x0C, GetMoney(&gSaveBlock1Ptr->money));
}

void BagDrawTextBoxOnWindow(u8 windowId)
{
    DrawTextBorderOuter(windowId, 0x064, 14);
}

// ---- Rouge Feu : fonctions des autres fichiers dont le sac a besoin ----

// menu_helpers.c
bool8 IsActiveOverworldLinkBusy(void)
{
    if (!MenuHelpers_IsLinkActive())
        return FALSE;
    else
        return (u8)Overworld_LinkRecvQueueLengthMoreThan2();
}

void ResetAllBgsCoordinatesAndBgCntRegs(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
}

// gflib (palette.c)
void SetBackdropFromPalette(const u16 *palette)
{
    LoadPalette(palette, BG_PLTT_ID(0), PLTT_SIZEOF(1));
}

// text_window.c : cadre standard de RF
static const u16 sStdTextWindow_Gfx[] = INCGFX_U16("graphics/kanto/text_window/std.png", ".4bpp");
static const u16 sStdTextWindow_Pal[] = INCGFX_U16("graphics/kanto/text_window/stdpal_3.pal", ".gbapal");

void LoadStdWindowGfx(u8 windowId, u16 destOffset, u8 palOffset)
{
    LoadBgTiles(GetWindowAttribute(windowId, WINDOW_BG), sStdTextWindow_Gfx, 0x120, destOffset);
    LoadPalette(sStdTextWindow_Pal, palOffset, PLTT_SIZE_4BPP);
}

// party_menu.c : retour au sac pour choisir l'objet à donner
void CB2_SelectBagItemToGive(void)
{
    GoToBagMenu(ITEMMENULOCATION_PARTY, OPEN_BAG_LAST, CB2_GiveHoldItem);
}
