#include "global.h"
#include "kanto_save.h"
#include "platform.h"
#include "save.h"
#include "string_util.h"

#define KANTO_SAVE_MAGIC 0x4B414E54 // "KANT"

// Nom du rival de Kanto en attendant la scène de RF où on le choisit (oak_speech.c)
static const u8 sText_KantoRivalDefaultName[] = _("BLUE");

EWRAM_DATA struct SaveBlockKanto gSaveBlockKanto = {0};

static u32 KantoSave_Checksum(void)
{
    const u8 *p = (const u8 *)&gSaveBlockKanto;
    u32 sum = 0x811C9DC5, i;
    for (i = 0; i < offsetof(struct SaveBlockKanto, checksum); i++)
        sum = (sum ^ p[i]) * 0x01000193;
    return sum;
}

void KantoSave_Clear(void)
{
    memset(&gSaveBlockKanto, 0, sizeof(gSaveBlockKanto));
    StringCopy(gSaveBlockKanto.rivalName, sText_KantoRivalDefaultName);
}

void KantoSave_Write(void)
{
#ifdef PORTABLE
    gSaveBlockKanto.magic = KANTO_SAVE_MAGIC;
    gSaveBlockKanto.saveCounter = gSaveCounter;
    gSaveBlockKanto.checksum = KantoSave_Checksum();
    Platform_WriteExtraSave(&gSaveBlockKanto, sizeof(gSaveBlockKanto));
#endif
}

void KantoSave_Read(void)
{
#ifdef PORTABLE
    // Une sauvegarde sans bloc Kanto (ancienne, ou partie jamais allée à Kanto) le laisse vide.
    if (!Platform_ReadExtraSave(&gSaveBlockKanto, sizeof(gSaveBlockKanto))
     || gSaveBlockKanto.magic != KANTO_SAVE_MAGIC
     || gSaveBlockKanto.checksum != KantoSave_Checksum())
        KantoSave_Clear();
#endif
}

// --- Poches agrandies du sac ---------------------------------------------------
#define BAG_SAVE_MAGIC 0x42414731 // "BAG1"

EWRAM_DATA struct SaveBlockBag gSaveBlockBag = {0};

static u32 BagSave_Checksum(void)
{
    const u8 *p = (const u8 *)&gSaveBlockBag;
    u32 sum = 0x811C9DC5, i;
    for (i = 0; i < offsetof(struct SaveBlockBag, checksum); i++)
        sum = (sum ^ p[i]) * 0x01000193;
    return sum;
}

void BagSave_Write(void)
{
#ifdef PORTABLE
    gSaveBlockBag.magic = BAG_SAVE_MAGIC;
    gSaveBlockBag.checksum = BagSave_Checksum();
    Platform_WriteExtraSaveAt(SAVEBLOCK_BAG_OFFSET, &gSaveBlockBag, sizeof(gSaveBlockBag));
#endif
}

// Sauvegarde sans ce bloc (antérieure) : on reprend les poches d'origine de SaveBlock1
// (quantités chiffrées avec la même clé, copiées telles quelles).
void BagSave_Read(void)
{
#ifdef PORTABLE
    if (Platform_ReadExtraSaveAt(SAVEBLOCK_BAG_OFFSET, &gSaveBlockBag, sizeof(gSaveBlockBag))
     && gSaveBlockBag.magic == BAG_SAVE_MAGIC
     && gSaveBlockBag.checksum == BagSave_Checksum())
        return;
#endif
    memset(&gSaveBlockBag, 0, sizeof(gSaveBlockBag));
    memcpy(gSaveBlockBag.items, gSaveBlock1Ptr->bagPocket_Items, sizeof(gSaveBlock1Ptr->bagPocket_Items));
    memcpy(gSaveBlockBag.keyItems, gSaveBlock1Ptr->bagPocket_KeyItems, sizeof(gSaveBlock1Ptr->bagPocket_KeyItems));
}
