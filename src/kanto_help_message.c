// Rouge Feu : help_message.c (bande de description du menu Start, option MENUS = KANTO)
#include "global.h"
#include "palette.h"
#include "malloc.h"
#include "menu.h"
#include "text.h"
#include "window.h"
#include "kanto_help_message.h"

static EWRAM_DATA u8 sHelpMessageWindowId = WINDOW_NONE;

static const u8 gHelpMessageWindow_Gfx[] = INCGFX_U8("graphics/kanto/help_system/msg_window.png", ".4bpp");
const u16 gHelpMessageWindow_Pal[] = INCGFX_U16("graphics/kanto/text_window/stdpal_2.pal", ".gbapal"); // GetTextWindowPalette(2)

void ResetHelpMessageWindowId(void)
{
    sHelpMessageWindowId = WINDOW_NONE;
}

static const struct WindowTemplate sHelpMessageWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 0,
    .tilemapTop = 15,
    .width = 30,
    .height = 5,
    .paletteNum = 15,
    .baseBlock = 0x08F
};


u8 CreateHelpMessageWindow(void)
{
    if (sHelpMessageWindowId == WINDOW_NONE)
    {
        sHelpMessageWindowId = AddWindow(&sHelpMessageWindowTemplate);
        PutWindowTilemap(sHelpMessageWindowId);
        // RF (text_window.c : LoadHelpMessageWindowGfx) : palette de la bande
        LoadPalette(gHelpMessageWindow_Pal, BG_PLTT_ID(sHelpMessageWindowTemplate.paletteNum), PLTT_SIZE_4BPP);
    }
    return sHelpMessageWindowId;
}

void DestroyHelpMessageWindow(u8 a0)
{
    if (sHelpMessageWindowId != WINDOW_NONE)
    {
        FillWindowPixelBuffer(sHelpMessageWindowId, PIXEL_FILL(0));
        ClearWindowTilemap(sHelpMessageWindowId);

        if (a0)
            CopyWindowToVram(sHelpMessageWindowId, a0);

        RemoveWindow(sHelpMessageWindowId);
        sHelpMessageWindowId = WINDOW_NONE;
    }
}

// Creates the bottom bar window that displays help text for e.g. the options in the Start menu
void DrawHelpMessageWindowTilesById(u8 windowId)
{
    const u8 *ptr = gHelpMessageWindow_Gfx;
    u8 *buffer;
    u8 i, j;
    u8 width, height;
    u8 tileId;

    width = (u8)GetWindowAttribute(windowId, WINDOW_WIDTH);
    height = (u8)GetWindowAttribute(windowId, WINDOW_HEIGHT);
    
    buffer = (u8 *)Alloc(32 * width * height);

    if (buffer != NULL)
    {
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                if (i == 0) // Top row
                    tileId = 0;
                else if (i == height - 1) // Bottom row
                    tileId = 14;
                else // Middle row
                    tileId = 5; 
                CpuCopy32(
                    &ptr[tileId * 32],
                    &buffer[(i * width + j) * 32],
                    32
                );
            }
        }
        CopyToWindowPixelBuffer(windowId, buffer, width * height * 32, 0);
        Free(buffer);
    }
}

static void DrawHelpMessageWindowTiles(void)
{
    DrawHelpMessageWindowTilesById(sHelpMessageWindowId);
}

static const u8 sHelpMessageTextColors[3] = {TEXT_COLOR_TRANSPARENT, TEXT_DYNAMIC_COLOR_1, TEXT_COLOR_DARK_GRAY};

static void PrintHelpMessageText(const u8 *text)
{
    AddTextPrinterParameterized4(sHelpMessageWindowId, FONT_KANTO, 2, 5, 1, 1, sHelpMessageTextColors, -1, text);
}

void PrintTextOnHelpMessageWindow(const u8 *text, u8 mode)
{
    DrawHelpMessageWindowTiles();
    PrintHelpMessageText(text);
    if (mode)
        CopyWindowToVram(sHelpMessageWindowId, mode);
}
