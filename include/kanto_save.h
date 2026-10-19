#ifndef GUARD_KANTO_SAVE_H
#define GUARD_KANTO_SAVE_H

#include "constants/kanto.h"
#include "constants/kanto/fame_checker.h"

#define NUM_KANTO_ROAMERS 3 // Raikou, Entei, Suicune

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
    struct Roamer roamers[NUM_KANTO_ROAMERS]; // chiens légendaires (RF : un seul, SaveBlock1)
    u8 reserved[1024 - (PLAYER_NAME_LENGTH + 1) - NUM_FAMECHECKER_PERSONS * 2 - sizeof(struct DaycareMon) - sizeof(struct Roamer) * NUM_KANTO_ROAMERS]; // place pour Johto, les îles Sevii, etc.
    u32 checksum;
};

extern struct SaveBlockKanto gSaveBlockKanto;

// Poches agrandies du sac (constants/global.h), écrites après le bloc Kanto
#define SAVEBLOCK_BAG_OFFSET 4096
struct SaveBlockBag
{
    u32 magic;
    struct ItemSlot items[BIG_BAG_ITEMS_COUNT];
    struct ItemSlot keyItems[BIG_BAG_KEYITEMS_COUNT];
    u32 checksum;
};

extern struct SaveBlockBag gSaveBlockBag;

void KantoSave_Clear(void);
void KantoSave_Write(void);
void KantoSave_Read(void);
void BagSave_Write(void);
void BagSave_Read(void);

#endif // GUARD_KANTO_SAVE_H
