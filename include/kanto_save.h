#ifndef GUARD_KANTO_SAVE_H
#define GUARD_KANTO_SAVE_H

#include "constants/kanto.h"

// Données de sauvegarde des régions importées. Sur PC, écrites dans le fichier .sav
// juste après les 128 Ko de la flash GBA (qui restent au format d'origine).
struct SaveBlockKanto
{
    u32 magic;
    u32 saveCounter;
    u8 flags[KANTO_FLAG_BYTES];
    u16 vars[KANTO_VARS_COUNT];
    u8 reserved[1024]; // place pour Johto, les îles Sevii, etc.
    u32 checksum;
};

extern struct SaveBlockKanto gSaveBlockKanto;

void KantoSave_Clear(void);
void KantoSave_Write(void);
void KantoSave_Read(void);

#endif // GUARD_KANTO_SAVE_H
