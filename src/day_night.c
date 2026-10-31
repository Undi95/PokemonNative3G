#include "global.h"
#include "day_night.h"
#include "fieldmap.h"
#include "main.h"
#include "overworld.h"
#include "rtc.h"
#include "tilesets.h"
#include "constants/rgb.h"

// PokemonNative3G : cycle jour/nuit, purement visuel. Les couleurs envoyées au matériel (PLTT) sont teintées selon
// l'heure, après les fondus et la météo (gPlttBufferFaded n'est pas touché) : seulement sur le terrain, dehors, et
// seulement les palettes de la carte (BG 0-12) et des objets ; boîtes de texte et menus (BG 13-15) restent intacts.
// Les vitres des tilesets (src/data/day_night_lights.h) s'allument en jaune le soir et la nuit.

struct DayNightKey
{
    u16 minute; // minute de la journée
    u16 r, g, b; // multiplicateurs sur 256
    u16 light;   // fenêtres allumées, sur 256
};

static const struct DayNightKey sDayNightKeys[] =
{
    {  0 * 60, 120, 130, 190, 256 }, // nuit
    {  5 * 60, 120, 130, 190, 256 },
    {  7 * 60, 245, 215, 200,   0 }, // matin
    {  9 * 60, 256, 256, 256,   0 }, // jour
    { 17 * 60, 256, 256, 256,   0 },
    { 19 * 60, 256, 180, 130, 128 }, // coucher de soleil
    { 21 * 60, 120, 130, 190, 256 }, // nuit
    { 24 * 60, 120, 130, 190, 256 },
};

struct DayNightLights
{
    const struct Tileset *tileset;
    u16 colors[NUM_PALS_TOTAL]; // masque des couleurs de vitre, par palette
};

#include "data/day_night_lights.h"

static u16 sTintR = 256, sTintG = 256, sTintB = 256, sLight = 0;
static u32 sLastUpdate = 0xFFFFFFFF;
static const struct MapLayout *sLightsLayout;
static u16 sLightMasks[NUM_PALS_TOTAL];
static bool8 sMarkLights; // banc de test : vitres en magenta

bool8 IsDayNightHourNight(u8 hours)
{
    return hours >= DAY_NIGHT_NIGHT_BEGIN || hours < DAY_NIGHT_NIGHT_END;
}

void DayNight_SetMarkLights(bool8 mark)
{
    sMarkLights = mark;
}

static u16 Interpolate(u16 a, u16 b, u32 t, u32 span)
{
    return a + ((s32)b - a) * (s32)t / (s32)span;
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
    sTintR = Interpolate(sDayNightKeys[i - 1].r, sDayNightKeys[i].r, t, span);
    sTintG = Interpolate(sDayNightKeys[i - 1].g, sDayNightKeys[i].g, t, span);
    sTintB = Interpolate(sDayNightKeys[i - 1].b, sDayNightKeys[i].b, t, span);
    sLight = Interpolate(sDayNightKeys[i - 1].light, sDayNightKeys[i].light, t, span);
}

// Vitres de la carte : primaire (palettes 0-5) et secondaire (6-12)
static void UpdateLightMasks(void)
{
    const struct MapLayout *layout = gMapHeader.mapLayout;
    u32 i, j;

    if (layout == sLightsLayout)
        return;
    sLightsLayout = layout;
    memset(sLightMasks, 0, sizeof(sLightMasks));
    for (i = 0; i < ARRAY_COUNT(sDayNightLights); i++)
    {
        if (sDayNightLights[i].tileset != layout->primaryTileset && sDayNightLights[i].tileset != layout->secondaryTileset)
            continue;
        for (j = 0; j < NUM_PALS_TOTAL; j++)
            sLightMasks[j] |= sDayNightLights[i].colors[j];
    }
}

static u32 TintColor(u32 c)
{
    u32 r = ((c & 0x1F) * sTintR) >> 8;
    u32 g = (((c >> 5) & 0x1F) * sTintG) >> 8;
    u32 b = (((c >> 10) & 0x1F) * sTintB) >> 8;

    return RGB2(min(r, 31), min(g, 31), min(b, 31));
}

// Vitre allumée : jaune chaud, aussi clair que la couleur d'origine, mélangé à la couleur teintée selon sLight
static u32 LightColor(u32 c)
{
    u32 tinted = TintColor(c);
    u32 l = ((c & 0x1F) + ((c >> 5) & 0x1F) + ((c >> 10) & 0x1F)) / 3;
    u32 lit[3], dark[3], k, out = 0;

    if (sMarkLights)
        return RGB2(31, 0, 31);
    lit[0] = min(l + 6, 31);
    lit[1] = min(l * 7 / 8 + 4, 31);
    lit[2] = l / 2;
    dark[0] = tinted & 0x1F;
    dark[1] = (tinted >> 5) & 0x1F;
    dark[2] = (tinted >> 10) & 0x1F;
    for (k = 0; k < 3; k++)
        out |= ((dark[k] * (256 - sLight) + lit[k] * sLight) >> 8) << (k * 5);
    return out;
}

static void TintColors(u16 *colors, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++)
        colors[i] = TintColor(colors[i]);
}

void DayNight_TintPltt(void)
{
    u16 *pltt = (u16 *)PLTT;
    u32 pal, i;

    if (!gSaveBlock2Ptr->optionsDayNight || gMain.callback2 != CB2_Overworld || !IsMapTypeOutdoors(gMapHeader.mapType))
        return;
    // L'heure n'est relue qu'une fois par seconde
    if (gMain.vblankCounter1 / 60 != sLastUpdate)
    {
        sLastUpdate = gMain.vblankCounter1 / 60;
        UpdateTint();
    }
    if (sTintR == 256 && sTintG == 256 && sTintB == 256 && sLight == 0 && !sMarkLights)
        return;
    UpdateLightMasks();
    for (pal = 0; pal < NUM_PALS_TOTAL; pal++)
    {
        for (i = 0; i < 16; i++, pltt++)
        {
            if ((sLightMasks[pal] >> i) & 1)
                *pltt = LightColor(*pltt);
            else
                *pltt = TintColor(*pltt);
        }
    }
    TintColors((u16 *)OBJ_PLTT, PLTT_SIZE / 2 / 2);
}
