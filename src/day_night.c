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
// Les vitres des tilesets (src/data/day_night_lights.h) s'allument en jaune le soir et la nuit, dégradés compris.

struct DayNightKey
{
    u16 minute; // minute de la journée
    u16 r, g, b; // multiplicateurs sur 256
    u16 gray;    // désaturation (vision de nuit : les fleurs ne brillent pas), sur 256
    u16 light;   // fenêtres allumées, sur 256
};

static const struct DayNightKey sDayNightKeys[] =
{
    {  0 * 60, 120, 130, 190, 140, 256 }, // nuit
    {  5 * 60, 120, 130, 190, 140, 256 },
    {  7 * 60, 245, 215, 200,   0,   0 }, // matin
    {  9 * 60, 256, 256, 256,   0,   0 }, // jour
    { 17 * 60, 256, 256, 256,   0,   0 },
    { 19 * 60, 256, 180, 130,  40, 128 }, // coucher de soleil
    { 21 * 60, 120, 130, 190, 140, 256 }, // nuit
    { 24 * 60, 120, 130, 190, 140, 256 },
};

struct DayNightLights
{
    const struct Tileset *tileset;
    u16 colors[NUM_PALS_TOTAL]; // couleurs de vitre, par palette
    const u8 (*tileLights)[8];  // pixels de vitre, par tile du tileset
};

#include "data/day_night_lights.h"

static u16 sTintR = 256, sTintG = 256, sTintB = 256, sGray = 0, sLight = 0;
static u32 sLastUpdate = 0xFFFFFFFF;
static const struct MapLayout *sLightsLayout;
struct DayNightRender gDayNightRender;
static bool8 sMarkLights; // banc de test : vitres en magenta
// Animation des portes (field_door.c) : ses images sont copiées dans les 16 derniers tiles, à la place de ceux de
// la carte ; pendant ce temps chacun reprend les pixels allumés du métatile fermé à la même place (la vitre qui
// glisse reste allumée, l'ouverture sombre et le logo au-dessus non)
#define DOOR_ANIM_TILES (NUM_TILES_TOTAL - 16)
static bool8 sDoorAnimTiles;
static u8 sMapDoorTiles[16][8];
static u8 sDoorAnimMasks[16][8];

bool8 IsDayNightHourNight(u8 hours)
{
    return hours >= DAY_NIGHT_NIGHT_BEGIN || hours < DAY_NIGHT_NIGHT_END;
}

void DayNight_SetMarkLights(bool8 mark)
{
    sMarkLights = mark;
}

// Indice de couleur du pixel (x, y) d'un tile de la carte, en mémoire vidéo (BG, char base 0)
static u32 TilePixel(u32 tile, u32 x, u32 y)
{
    const u8 *p = (const u8 *)VRAM + tile * TILE_SIZE_4BPP + y * 4 + x / 2;

    return (x & 1) ? *p >> 4 : *p & 0xF;
}

// Pixel du métatile (couche du haut s'il n'est pas transparent, sinon celle du bas) à la place (px, py) du quart q :
// renvoie son indice de couleur, et s'il est allumé
static u32 MetatilePixel(const u16 *entries, u32 q, u32 px, u32 py, bool32 *lit)
{
    u32 layer, color = 0;

    *lit = FALSE;
    for (layer = 0; layer < 2; layer++)
    {
        u16 entry = entries[q + 4 * (1 - layer)];
        u32 tile = entry & 0x3FF, sx = (entry & 0x400) ? 7 - px : px, sy = (entry & 0x800) ? 7 - py : py;

        color = TilePixel(tile, sx, sy);
        if (color != 0)
        {
            *lit = tile < DOOR_ANIM_TILES && ((gDayNightRender.tiles[tile][sy] >> sx) & 1);
            break;
        }
    }
    return color;
}

// Une image de porte est dessinée à (x, y) avec les tiles tileNum à tileNum + 3 (couche du bas du métatile) : un
// pixel s'allume s'il l'est dans le métatile fermé à la même place et qu'il en a gardé la couleur (la vitre qui
// glisse, pas l'intérieur qui apparaît)
void DayNight_DoorAnimMetatile(u32 tileNum, s32 x, s32 y)
{
    const struct MapLayout *layout = gMapHeader.mapLayout;
    u32 id = MapGridGetMetatileIdAt(x, y), q, px, py;
    const u16 *entries;
    bool32 lit;

    if (id < NUM_METATILES_IN_PRIMARY)
        entries = layout->primaryTileset->metatiles + id * NUM_TILES_PER_METATILE;
    else
        entries = layout->secondaryTileset->metatiles + (id - NUM_METATILES_IN_PRIMARY) * NUM_TILES_PER_METATILE;
    for (q = 0; q < 4; q++)
    {
        u8 *mask = sDoorAnimMasks[tileNum + q - DOOR_ANIM_TILES];

        for (py = 0; py < 8; py++)
        {
            mask[py] = 0;
            for (px = 0; px < 8; px++)
            {
                if (MetatilePixel(entries, q, px, py, &lit) == TilePixel(tileNum + q, px, py) && lit)
                    mask[py] |= 1 << px;
            }
        }
    }
    sDoorAnimTiles = TRUE;
}

void DayNight_DoorClosed(void)
{
    sDoorAnimTiles = FALSE;
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
    sGray = Interpolate(sDayNightKeys[i - 1].gray, sDayNightKeys[i].gray, t, span);
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
    memset(gDayNightRender.masks, 0, sizeof(gDayNightRender.masks));
    memset(gDayNightRender.tiles, 0, sizeof(gDayNightRender.tiles));
    for (i = 0; i < ARRAY_COUNT(sDayNightLights); i++)
    {
        const struct DayNightLights *lights = &sDayNightLights[i];
        u32 base;

        if (lights->tileset == layout->primaryTileset)
            base = 0;
        else if (lights->tileset == layout->secondaryTileset)
            base = NUM_TILES_IN_PRIMARY;
        else
            continue;
        for (j = 0; j < NUM_PALS_TOTAL; j++)
            gDayNightRender.masks[j] |= lights->colors[j];
        memcpy(gDayNightRender.tiles[base], lights->tileLights, NUM_TILES_IN_PRIMARY * sizeof(gDayNightRender.tiles[0]));
    }
    memcpy(sMapDoorTiles, gDayNightRender.tiles[DOOR_ANIM_TILES], sizeof(sMapDoorTiles));
    sDoorAnimTiles = FALSE;
}

static u32 Desaturate(u32 x, u32 l)
{
    return (x * (256 - sGray) + l * sGray) >> 8;
}

static u32 TintColor(u32 c)
{
    u32 r = c & 0x1F, g = (c >> 5) & 0x1F, b = (c >> 10) & 0x1F;
    u32 l = (r * 77 + g * 150 + b * 29) >> 8;

    r = (Desaturate(r, l) * sTintR) >> 8;
    g = (Desaturate(g, l) * sTintG) >> 8;
    b = (Desaturate(b, l) * sTintB) >> 8;

    return RGB2(min(r, 31), min(g, 31), min(b, 31));
}

// Vitre allumée : jaune chaud, aussi clair que la couleur d'origine (fenêtres bleu nuit éclaircies, jusqu'au
// double : un écran noir pendant un fondu reste noir), mélangé à la couleur teintée selon sLight
static u32 LightColor(u32 c)
{
    u32 tinted = TintColor(c);
    u32 l = ((c & 0x1F) + ((c >> 5) & 0x1F) + ((c >> 10) & 0x1F)) / 3;
    u32 lit[3], dark[3], k, out = 0;

    if (sMarkLights)
        return RGB2(31, 0, 31);
    l = max(l, min(14, l * 2));
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

    gDayNightRender.active = FALSE;
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
    if (sDoorAnimTiles)
        memcpy(gDayNightRender.tiles[DOOR_ANIM_TILES], sDoorAnimMasks, sizeof(sDoorAnimMasks));
    else
        memcpy(gDayNightRender.tiles[DOOR_ANIM_TILES], sMapDoorTiles, sizeof(sMapDoorTiles));
    gDayNightRender.active = sLight != 0 || sMarkLights;
    for (pal = 0; pal < NUM_PALS_TOTAL; pal++)
    {
        for (i = 0; i < 16; i++, pltt++)
        {
            if (gDayNightRender.active && ((gDayNightRender.masks[pal] >> i) & 1))
                gDayNightRender.colors[pal * 16 + i] = LightColor(*pltt);
            *pltt = TintColor(*pltt);
        }
    }
    TintColors((u16 *)OBJ_PLTT, PLTT_SIZE / 2 / 2);
}
