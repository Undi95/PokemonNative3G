#include "global.h"
#include "day_night.h"
#include "fieldmap.h"
#include "main.h"
#include "overworld.h"
#include "rtc.h"
#include "constants/rgb.h"

// PokemonNative3G : cycle jour/nuit, purement visuel. Les couleurs envoyées au matériel (PLTT) sont teintées selon
// l'heure, après les fondus et la météo (gPlttBufferFaded n'est pas touché) : seulement sur le terrain, dehors, et
// seulement les palettes de la carte (BG 0-12) et des objets ; boîtes de texte et menus (BG 13-15) restent intacts.

struct DayNightKey
{
    u16 minute; // minute de la journée
    u16 r, g, b; // multiplicateurs sur 256
};

static const struct DayNightKey sDayNightKeys[] =
{
    {  0 * 60, 120, 130, 190 }, // nuit
    {  5 * 60, 120, 130, 190 },
    {  7 * 60, 245, 215, 200 }, // matin
    {  9 * 60, 256, 256, 256 }, // jour
    { 17 * 60, 256, 256, 256 },
    { 19 * 60, 256, 180, 130 }, // coucher de soleil
    { 21 * 60, 120, 130, 190 }, // nuit
    { 24 * 60, 120, 130, 190 },
};

static u16 sTintR = 256, sTintG = 256, sTintB = 256;
static u32 sLastUpdate = 0xFFFFFFFF;

bool8 IsDayNightHourNight(u8 hours)
{
    return hours >= DAY_NIGHT_NIGHT_BEGIN || hours < DAY_NIGHT_NIGHT_END;
}

static void UpdateTint(void)
{
    u32 i, minute, span, t;

    RtcCalcLocalTime();
    minute = gLocalTime.hours * 60 + gLocalTime.minutes;
    for (i = 1; i < ARRAY_COUNT(sDayNightKeys) - 1 && minute >= sDayNightKeys[i].minute; i++)
        ;
    span = sDayNightKeys[i].minute - sDayNightKeys[i - 1].minute;
    t = minute - sDayNightKeys[i - 1].minute;
    sTintR = sDayNightKeys[i - 1].r + ((s32)sDayNightKeys[i].r - sDayNightKeys[i - 1].r) * (s32)t / (s32)span;
    sTintG = sDayNightKeys[i - 1].g + ((s32)sDayNightKeys[i].g - sDayNightKeys[i - 1].g) * (s32)t / (s32)span;
    sTintB = sDayNightKeys[i - 1].b + ((s32)sDayNightKeys[i].b - sDayNightKeys[i - 1].b) * (s32)t / (s32)span;
}

static void TintColors(u16 *colors, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++)
    {
        u32 c = colors[i];
        u32 r = ((c & 0x1F) * sTintR) >> 8;
        u32 g = (((c >> 5) & 0x1F) * sTintG) >> 8;
        u32 b = (((c >> 10) & 0x1F) * sTintB) >> 8;
        colors[i] = RGB2(min(r, 31), min(g, 31), min(b, 31));
    }
}

void DayNight_TintPltt(void)
{
    if (!gSaveBlock2Ptr->optionsDayNight || gMain.callback2 != CB2_Overworld || !IsMapTypeOutdoors(gMapHeader.mapType))
        return;
    // L'heure n'est relue qu'une fois par seconde
    if (gMain.vblankCounter1 / 60 != sLastUpdate)
    {
        sLastUpdate = gMain.vblankCounter1 / 60;
        UpdateTint();
    }
    if (sTintR == 256 && sTintG == 256 && sTintB == 256)
        return;
    TintColors((u16 *)PLTT, NUM_PALS_TOTAL * 16);
    TintColors((u16 *)OBJ_PLTT, PLTT_SIZE / 2 / 2);
}
