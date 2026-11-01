#ifndef GUARD_DAY_NIGHT_H
#define GUARD_DAY_NIGHT_H

// PokemonNative3G : cycle jour/nuit, purement visuel (option JOUR/NUIT). La nuit d'évolution (Mentali/Noctali)
// suit les mêmes heures, voir IsDayNightHourNight.
#define DAY_NIGHT_NIGHT_BEGIN 20
#define DAY_NIGHT_NIGHT_END   6

// Fenêtres allumées, lues par le rendu des BG (gba_easy_draw.c) : un pixel 4bpp de la carte (char base 0, palettes
// 0-12) dont la couleur est dans masks (par palette) et la place dans tiles (par tile, une rangée de 8 bits par ligne)
// prend la couleur de colors au lieu de celle de PLTT
struct DayNightRender
{
    bool8 active;
    u16 masks[13];
    u16 colors[13 * 16];
    u8 tiles[1024][8];
};

extern struct DayNightRender gDayNightRender;

bool8 IsDayNightHourNight(u8 hours);
void DayNight_TintPltt(void);
void DayNight_SetMarkLights(bool8 mark);
void DayNight_DoorAnimMetatile(u32 tileNum, s32 x, s32 y);
void DayNight_DoorClosed(void);

#endif // GUARD_DAY_NIGHT_H
