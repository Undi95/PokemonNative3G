// Rouge Feu (save_menu_util.c et PrintSaveStats de start_menu.c) : la fenêtre d'infos de la sauvegarde de RF,
// avec l'option MENUS = KANTO (avec HOENN : ShowSaveInfoWindow et BufferSaveMenuText d'Émeraude)
#include "global.h"
#include "kanto_save_menu_util.h"
#include "event_data.h"
#include "fusion_region.h"
#include "menu.h"
#include "palette.h"
#include "pokedex.h"
#include "region_map.h"
#include "string_util.h"
#include "text.h"
#include "window.h"
#include "constants/flags.h"
#include "kanto_bag_compat.h" // LoadStdWindowGfx (cadre standard de RF, src/kanto_bag.c) ; en dernier : ses #define

EWRAM_DATA static u8 sSaveStatsWindowId = 0;

static const struct WindowTemplate sSaveStatsWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 14,
    .height = 9,
    .paletteNum = 13,
    .baseBlock = 0x008
};

static ALIGNED(2) const u8 sTextColor_StatName[] = { 1, 2, 3 };
static ALIGNED(2) const u8 sTextColor_StatValue[] = { 1, 4, 5 };
static ALIGNED(2) const u8 sTextColor_LocationHeader[] = { 1, 6, 7 };

// strings_1_fr.h de RF
static const u8 sKText_SaveStatName_Player[] = _("JOUEUR");
static const u8 sKText_SaveStatName_Badges[] = _("BADGES");
static const u8 sKText_SaveStatName_Pokedex[] = _("POKéDEX");
static const u8 sKText_SaveStatName_Time[] = _("DUREE JEU");

void SaveStatToString(u8 gameStatId, u8 *dest0, u8 color)
{
    int nBadges;
    int flagId;
    int firstBadge;

    u8 *dest = dest0;
    *dest++ = EXT_CTRL_CODE_BEGIN;
    *dest++ = EXT_CTRL_CODE_COLOR;
    *dest++ = color;
    *dest++ = EXT_CTRL_CODE_BEGIN;
    *dest++ = EXT_CTRL_CODE_SHADOW;
    *dest++ = color + 1;
    switch (gameStatId)
    {
    case SAVE_STAT_NAME:
        dest = StringCopy(dest, gSaveBlock2Ptr->playerName);
        break;
    case SAVE_STAT_POKEDEX:
        if (IsNationalPokedexEnabled())
            dest = ConvertIntToDecimalStringN(dest, GetNationalPokedexCount(FLAG_GET_CAUGHT), STR_CONV_MODE_LEFT_ALIGN, 3);
        else if (Fusion_IsInKanto()) // PokemonNative3G : le Pokédex de la région (RF : celui de Kanto)
            dest = ConvertIntToDecimalStringN(dest, GetKantoPokedexCount(FLAG_GET_CAUGHT), STR_CONV_MODE_LEFT_ALIGN, 3);
        else
            dest = ConvertIntToDecimalStringN(dest, GetHoennPokedexCount(FLAG_GET_CAUGHT), STR_CONV_MODE_LEFT_ALIGN, 3);
        break;
    case SAVE_STAT_TIME:
        dest = ConvertIntToDecimalStringN(dest, gSaveBlock2Ptr->playTimeHours, STR_CONV_MODE_LEFT_ALIGN, 3);
        *dest++ = CHAR_COLON;
        dest = ConvertIntToDecimalStringN(dest, gSaveBlock2Ptr->playTimeMinutes, STR_CONV_MODE_LEADING_ZEROS, 2);
        break;
    case SAVE_STAT_TIME_HR_RT_ALIGN:
        dest = ConvertIntToDecimalStringN(dest, gSaveBlock2Ptr->playTimeHours, STR_CONV_MODE_RIGHT_ALIGN, 3);
        *dest++ = CHAR_COLON;
        dest = ConvertIntToDecimalStringN(dest, gSaveBlock2Ptr->playTimeMinutes, STR_CONV_MODE_LEADING_ZEROS, 2);
        break;
    case SAVE_STAT_LOCATION:
        GetMapNameGeneric(dest, gMapHeader.regionMapSectionId);
        break;
    case SAVE_STAT_BADGES:
        // PokemonNative3G : les badges de la région (RF : ceux de Kanto), comme le menu principal de RF
        firstBadge = Fusion_IsInKanto() ? FLAG_KANTO_BADGE01_GET : FLAG_BADGE01_GET;
        for (flagId = firstBadge, nBadges = 0; flagId < firstBadge + 8; flagId++)
        {
            if (FlagGet(flagId))
                nBadges++;
        }
        *dest++ = nBadges + CHAR_0;
        *dest++ = 10; // 'こ'
        *dest++ = EOS;
        break;
    }
}

u8 Kanto_PrintSaveStats(void)
{
    u8 y;
    u8 x;
    sSaveStatsWindowId = AddWindow(&sSaveStatsWindowTemplate);
    LoadStdWindowGfx(sSaveStatsWindowId, 0x21D, BG_PLTT_ID(13));
    DrawStdFrameWithCustomTileAndPalette(sSaveStatsWindowId, FALSE, 0x21D, 13);
    SaveStatToString(SAVE_STAT_LOCATION, gStringVar4, 8);
    x = (u32)(112 - GetStringWidth(FONT_KANTO, gStringVar4, -1)) / 2;
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_KANTO, x, 0, sTextColor_LocationHeader, -1, gStringVar4);
    x = (u32)(112 - GetStringWidth(FONT_KANTO, gStringVar4, -1)) / 2;
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 2, 14, sTextColor_StatName, -1, sKText_SaveStatName_Player);
    SaveStatToString(SAVE_STAT_NAME, gStringVar4, 2);
    Menu_PrintFormatIntlPlayerName(sSaveStatsWindowId, gStringVar4, 60, 14);
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 2, 28, sTextColor_StatName, -1, sKText_SaveStatName_Badges);
    SaveStatToString(SAVE_STAT_BADGES, gStringVar4, 2);
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 60, 28, sTextColor_StatValue, -1, gStringVar4);
    y = 42;
    // PokemonNative3G : le Pokédex de la région (RF : celui de Kanto)
    if (FlagGet(Fusion_IsInKanto() ? FLAG_KANTO_SYS_POKEDEX_GET : FLAG_SYS_POKEDEX_GET) == TRUE)
    {
        AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 2, 42, sTextColor_StatName, -1, sKText_SaveStatName_Pokedex);
        SaveStatToString(SAVE_STAT_POKEDEX, gStringVar4, 2);
        AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 60, 42, sTextColor_StatValue, -1, gStringVar4);
        y = 56;
    }
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 2, y, sTextColor_StatName, -1, sKText_SaveStatName_Time);
    SaveStatToString(SAVE_STAT_TIME, gStringVar4, 2);
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 60, y, sTextColor_StatValue, -1, gStringVar4);
    CopyWindowToVram(sSaveStatsWindowId, COPYWIN_GFX);
    return sSaveStatsWindowId;
}
