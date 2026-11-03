#ifdef PORTABLE
#include "global.h"
#include "platform/dma.h"

struct DMATransfer {
    union {
        const void *src;
        const u16 *src16;
        const u32 *src32;
    };
    union {
        volatile void *dst;
        vu16 *dst16;
        vu32 *dst32;
    };
    u32 size;
    u16 control;
} DMAList[DMA_COUNT];

struct DMATransfer DMASet[DMA_COUNT];

void RunDMAs(u32 type)
{
    for (int dmaNum = 0; dmaNum < DMA_COUNT; dmaNum++)
    {
        struct DMATransfer *dma = &DMAList[dmaNum];
        u32 dmaCntReg = (&REG_DMA0CNT)[dmaNum * 3];
        if (!((dmaCntReg >> 16) & DMA_ENABLE))
        {
            dma->control &= ~DMA_ENABLE;
        }
        
        if ( (dma->control & DMA_ENABLE) &&
           (((dma->control & DMA_START_MASK) >> 12) == type))
        {
            //printf("DMA%d src=%p, dest=%p, control=%d\n", dmaNum, dma->src, dma->dst, dma->control);
            for (int i = 0; i < (dma->size); i++)
            {
                if ((dma->control) & DMA_32BIT)
                     *dma->dst32 = *dma->src32;
                else *dma->dst16 = *dma->src16;

                // process destination pointer changes
                if (((dma->control) & DMA_DEST_MASK) == DMA_DEST_INC)
                {
                    if ((dma->control) & DMA_32BIT)
                            dma->dst32++;
                    else    dma->dst16++;
                }
                else if (((dma->control) & DMA_DEST_MASK) == DMA_DEST_DEC)
                {
                    if ((dma->control) & DMA_32BIT)
                            dma->dst32--;
                    else    dma->dst16--;
                }
                else if (((dma->control) & DMA_DEST_MASK) == DMA_DEST_RELOAD) // TODO
                {
                    if ((dma->control) & DMA_32BIT)
                            dma->dst32++;
                    else    dma->dst16++;
                }

                // process source pointer changes
                if (((dma->control) & DMA_SRC_MASK) == DMA_SRC_INC)
                {
                    if ((dma->control) & DMA_32BIT)
                            dma->src32++;
                    else    dma->src16++;
                }
                else if (((dma->control) & DMA_SRC_MASK) == DMA_SRC_DEC)
                {
                    if ((dma->control) & DMA_32BIT)
                            dma->src32--;
                    else    dma->src16--;
                }
            }

            if (dma->control & DMA_REPEAT)
            {
                dma->size = ((&REG_DMA0CNT)[dmaNum * 3] & 0x1FFFF);
                if (((dma->control) & DMA_DEST_MASK) == DMA_DEST_RELOAD)
                {
                    dma->dst = DMASet[dmaNum].dst;
                }
            }
            else
            {
                dma->control &= ~DMA_ENABLE;
            }
        }
    }
}

// Sonde de debug (outil gfx.dma) : pour chaque canal en cours, le moment (0 tout de suite, 1 VBlank, 2 HBlank,
// 3 spécial), la répétition, la source et la destination actuelles (décalage dans les registres, la VRAM...), la taille
void Dma_Describe(char *out, size_t size)
{
    static const struct { const char *name; uintptr_t start, end; } areas[] = {
        {"registres", (uintptr_t)REG_BASE, (uintptr_t)REG_BASE + 0x400},
        {"VRAM", (uintptr_t)VRAM, (uintptr_t)VRAM + 0x18000},
        {"palettes", (uintptr_t)PLTT, (uintptr_t)PLTT + 0x400},
        {"OAM", (uintptr_t)OAM, (uintptr_t)OAM + 0x400},
    };
    size_t len = 0;
    int dmaNum, i;

    for (dmaNum = 0; dmaNum < DMA_COUNT && len < size; dmaNum++)
    {
        struct DMATransfer *dma = &DMAList[dmaNum];
        uintptr_t dst = (uintptr_t)dma->dst;
        const char *where = "memoire";
        uintptr_t offset = dst;

        if (!(dma->control & DMA_ENABLE))
        {
            len += snprintf(out + len, size - len, "DMA%d arrete\n", dmaNum);
            continue;
        }
        for (i = 0; i < (int)ARRAY_COUNT(areas); i++)
        {
            if (dst >= areas[i].start && dst < areas[i].end)
            {
                where = areas[i].name;
                offset = dst - areas[i].start;
                break;
            }
        }
        len += snprintf(out + len, size - len, "DMA%d moment %d%s, source %p (depart %p), destination %s %#lx, taille %u, controle %04x\n",
                        dmaNum, (dma->control & DMA_START_MASK) >> 12, (dma->control & DMA_REPEAT) ? " repete" : "",
                        dma->src, DMASet[dmaNum].src, where, (unsigned long)offset, (unsigned)dma->size, dma->control);
    }
}

void DmaSet(int dmaNum, const void *src, volatile void *dest, u32 control)
{
    if (dmaNum >= DMA_COUNT)
    {
        fprintf(stderr, "DmaSet with invalid DMA number: dmaNum=%d, src=%p, dest=%p, control=%d\n", dmaNum, src, dest, control);
        return;
    }

    struct DMATransfer *dma = &DMASet[dmaNum];
    dma->src = src;
    dma->dst = dest;
    dma->size = control & 0x1ffff;
    dma->control = control >> 16;
    
    // RunDMAs reads the enable bit back from the control register. The address
    // registers are 32-bit and nothing reads them, so the pointers stay in DMASet.
    (&REG_DMA0CNT)[dmaNum * 3] = control;

    dma = &DMAList[dmaNum];
    dma->src = src;
    dma->dst = dest;
    dma->size = control & 0x1ffff;
    dma->control = control >> 16;

    RunDMAs(DMA_NOW);
}
#endif //PORTABLE