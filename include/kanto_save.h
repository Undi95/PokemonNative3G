#ifndef GUARD_KANTO_SAVE_H
#define GUARD_KANTO_SAVE_H

#include "constants/kanto.h"
#include "constants/kanto/fame_checker.h"

// fame_checker de RF (global.h)
struct FameCheckerSaveData
{
    u16 pickState:2;
    u16 flavorTextFlags:12;
    u16 unk_0_E:2;
};

// Données de sauvegarde des régions importées. Sur PC, écrites dans le fichier .sav
// juste après les 128 Ko de la flash GBA (qui restent au format d'origine).
struct SaveBlockKanto
{
    u32 magic;
    u32 saveCounter;
    u8 flags[KANTO_FLAG_BYTES];
    u16 vars[KANTO_VARS_COUNT];
    u8 rivalName[PLAYER_NAME_LENGTH + 1];
    struct FameCheckerSaveData fameChecker[NUM_FAMECHECKER_PERSONS];
    struct DaycareMon route5DayCareMon; // SaveBlock1 de RF (pension de la Route 5)
    u8 reserved[1024 - (PLAYER_NAME_LENGTH + 1) - NUM_FAMECHECKER_PERSONS * 2 - sizeof(struct DaycareMon)]; // place pour Johto, les îles Sevii, etc.
    u32 checksum;
};

extern struct SaveBlockKanto gSaveBlockKanto;

void KantoSave_Clear(void);
void KantoSave_Write(void);
void KantoSave_Read(void);

#endif // GUARD_KANTO_SAVE_H
