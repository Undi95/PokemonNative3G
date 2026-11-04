#ifndef GUARD_KANTO_SAVE_H
#define GUARD_KANTO_SAVE_H

#include "constants/kanto.h"
#include "constants/kanto/fame_checker.h"

#define NUM_KANTO_ROAMERS 3 // Raikou, Entei, Suicune

#define NUM_TOWER_CHALLENGE_TYPES 4 // RF : constants/global.h (simples, doubles, éliminatoires, mixte)

// Tour des Dresseurs de RF (global.h)
struct TrainerTower
{
    u32 timer;
    u32 bestTime;
    u8 floorsCleared;
    u8 unk9;
    bool8 receivedPrize:1;
    bool8 checkedFinalTime:1;
    bool8 spokeToOwner:1;
    bool8 hasLost:1;
    bool8 unkA_4:1;
    bool8 validated:1;
};

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
    u16 trainerRematchStepCounter; // Cherche VS (RF : SaveBlock1)
    u8 trainerRematches[MAX_REMATCH_ENTRIES]; // revanches des dresseurs de la carte, par numéro local
    struct TrainerTower trainerTower[NUM_TOWER_CHALLENGE_TYPES]; // Tour des Dresseurs (RF : SaveBlock1)
    u8 towerChallengeId;
    u8 reserved[1024 - (PLAYER_NAME_LENGTH + 1) - NUM_FAMECHECKER_PERSONS * 2 - sizeof(struct DaycareMon) - sizeof(struct Roamer) * NUM_KANTO_ROAMERS - 2 - MAX_REMATCH_ENTRIES - sizeof(struct TrainerTower) * NUM_TOWER_CHALLENGE_TYPES - 1]; // place pour Johto, les îles Sevii, etc.
    u32 checksum;
};

extern struct SaveBlockKanto gSaveBlockKanto;

// Poches du sac sans limite (constants/global.h). Depuis le 2026-11-04, écrites après le Panthéon de Kanto
// (KANTO_HOF_OFFSET) : 999 lignes par poche ne tiennent plus à SAVEBLOCK_OLD_BAG_OFFSET, où l'ancien bloc « BAG1 »
// (160 Objets, 80 Objets rares) est relu une fois (BagSave_Read)
#define SAVEBLOCK_OLD_BAG_OFFSET 4096
#define KANTO_HOF_OFFSET 8192
#define SAVEBLOCK_BAG_OFFSET 16384
struct SaveBlockBag
{
    u32 magic;
    struct ItemSlot items[BIG_BAG_ITEMS_COUNT];
    struct ItemSlot keyItems[BIG_BAG_KEYITEMS_COUNT];
    struct ItemSlot pokeBalls[BIG_BAG_POKEBALLS_COUNT];
    u32 checksum;
};

extern struct SaveBlockBag gSaveBlockBag;

void KantoSave_Clear(void);
void KantoSave_Write(void);
void KantoSave_Read(void);
void BagSave_Write(void);
void BagSave_Read(void);
void KantoHallOfFame_Write(const void *data, u32 size);
bool8 KantoHallOfFame_Read(void *data, u32 size);

#endif // GUARD_KANTO_SAVE_H
