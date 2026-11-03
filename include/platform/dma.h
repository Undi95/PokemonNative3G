#ifndef GUARD_DMA_H
#define GUARD_DMA_H

#include "global.h"

#define DMA_COUNT 4

enum {
    DMA_NOW,
    DMA_VBLANK,
    DMA_HBLANK,
    DMA_SPECIAL
};

void RunDMAs(u32 type);
// Sonde de debug (outil gfx.dma) : l'état des 4 canaux
void Dma_Describe(char *out, size_t size);
#endif