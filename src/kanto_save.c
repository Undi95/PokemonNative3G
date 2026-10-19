#include "global.h"
#include "kanto_save.h"
#include "platform.h"
#include "save.h"

#define KANTO_SAVE_MAGIC 0x4B414E54 // "KANT"

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
