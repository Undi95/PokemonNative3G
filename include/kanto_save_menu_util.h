#ifndef GUARD_KANTO_SAVE_MENU_UTIL_H
#define GUARD_KANTO_SAVE_MENU_UTIL_H

// Rouge Feu (save_menu_util.h) : la fenêtre d'infos de la sauvegarde de RF (option MENUS = KANTO)

enum SaveStat
{
    SAVE_STAT_NAME = 0,
    SAVE_STAT_POKEDEX,
    SAVE_STAT_TIME,
    SAVE_STAT_LOCATION,
    SAVE_STAT_BADGES,
    SAVE_STAT_TIME_HR_RT_ALIGN
};

void SaveStatToString(u8 gameStatId, u8 *dest0, u8 color);
u8 Kanto_PrintSaveStats(void);

#endif // GUARD_KANTO_SAVE_MENU_UTIL_H
