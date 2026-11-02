#include "global.h"
#include "coins.h"
#include "text.h"
#include "window.h"
#include "strings.h"
#include "string_util.h"
#include "menu.h"
#include "international_string_util.h"
#include "palette.h"
#include "constants/coins.h"
#include "kanto_bag_compat.h" // LoadStdWindowGfx (cadre standard de RF) ; en dernier : ses #define

static EWRAM_DATA u8 sCoinsWindowId = 0;

/**
 * French Difference
 * 
 * It uses a different font size and
 * total width from the EN Version
 */
void PrintCoinsString(u32 coinAmount)
{
    u32 xAlign;

    ConvertIntToDecimalStringN(gStringVar1, coinAmount, STR_CONV_MODE_RIGHT_ALIGN, MAX_COIN_DIGITS);
    StringExpandPlaceholders(gStringVar4, gText_Coins);

    xAlign = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 56);
    AddTextPrinterParameterized(sCoinsWindowId, FONT_NARROW, gStringVar4, xAlign, 1, 0, NULL);
}

void ShowCoinsWindow(u32 coinAmount, u8 x, u8 y)
{
    struct WindowTemplate template;
    SetWindowTemplateFields(&template, 0, x, y, 7, 2, 0xF, 0x141); //!< French Difference
    sCoinsWindowId = AddWindow(&template);
    FillWindowPixelBuffer(sCoinsWindowId, PIXEL_FILL(0));
    PutWindowTilemap(sCoinsWindowId);
    DrawStdFrameWithCustomTileAndPalette(sCoinsWindowId, FALSE, 0x214, 0xE);
    PrintCoinsString(coinAmount);
}

void HideCoinsWindow(void)
{
    ClearStdWindowAndFrame(sCoinsWindowId, TRUE);
    RemoveWindow(sCoinsWindowId);
}

// ---- Rouge Feu (coins.c) : boîte des jetons des scripts avec MENUS = KANTO (ScrCmd_showcoinsbox) : « JETONS » écrit
// dans la fenêtre (8 × 3) et le nombre dessous en petite police, dans le cadre standard de RF ; celle d'Émeraude n'a
// que le nombre (7 × 2). RF place la fenêtre une case après les coordonnées du script (le cadre est à x, y).

static const u8 sKText_Coins_2[] = _("JETONS"); // RF : gText_Coins_2 (strings_1_fr.h)

void Kanto_PrintCoinsString(u32 coinAmount)
{
    u8 windowId;
    int width;

    ConvertIntToDecimalStringN(gStringVar1, coinAmount, STR_CONV_MODE_RIGHT_ALIGN, 4);
    StringExpandPlaceholders(gStringVar4, gText_Coins);
    width = GetStringWidth(FONT_SMALL, gStringVar4, 0);
    windowId = sCoinsWindowId;
    AddTextPrinterParameterized(windowId, FONT_SMALL, gStringVar4, 64 - width, 0xC, 0, NULL);
}

void Kanto_ShowCoinsWindow(u32 coinAmount, u8 x, u8 y)
{
    struct WindowTemplate template;

    SetWindowTemplateFields(&template, 0, x + 1, y + 1, 8, 3, 0xF, 0x20);
    sCoinsWindowId = AddWindow(&template);
    FillWindowPixelBuffer(sCoinsWindowId, PIXEL_FILL(0));
    PutWindowTilemap(sCoinsWindowId);
    LoadStdWindowGfx(sCoinsWindowId, 0x21D, BG_PLTT_ID(13));
    DrawStdFrameWithCustomTileAndPalette(sCoinsWindowId, FALSE, 0x21D, 13);
    AddTextPrinterParameterized(sCoinsWindowId, FONT_KANTO, sKText_Coins_2, 0, 0, TEXT_SKIP_DRAW, NULL); // RF : FONT_NORMAL de RF
    Kanto_PrintCoinsString(coinAmount);
}

void Kanto_HideCoinsWindow(void)
{
    ClearWindowTilemap(sCoinsWindowId);
    ClearStdWindowAndFrameToTransparent(sCoinsWindowId, TRUE);
    RemoveWindow(sCoinsWindowId);
}

u16 GetCoins(void)
{
    return gSaveBlock1Ptr->coins ^ gSaveBlock2Ptr->encryptionKey;
}

void SetCoins(u16 coinAmount)
{
    gSaveBlock1Ptr->coins = coinAmount ^ gSaveBlock2Ptr->encryptionKey;
}

bool8 AddCoins(u16 toAdd)
{
    u16 newAmount;
    u16 ownedCoins = GetCoins();
    if (ownedCoins >= MAX_COINS)
        return FALSE;
    // check overflow, can't have less coins than previously
    if (ownedCoins > ownedCoins + toAdd)
    {
        newAmount = MAX_COINS;
    }
    else
    {
        ownedCoins += toAdd;
        if (ownedCoins > MAX_COINS)
            ownedCoins = MAX_COINS;
        newAmount = ownedCoins;
    }
    SetCoins(newAmount);
    return TRUE;
}

bool8 RemoveCoins(u16 toSub)
{
    u16 ownedCoins = GetCoins();
    if (ownedCoins >= toSub)
    {
        SetCoins(ownedCoins - toSub);
        return TRUE;
    }
    return FALSE;
}
