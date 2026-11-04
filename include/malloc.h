#ifndef GUARD_ALLOC_H
#define GUARD_ALLOC_H


#define FREE_AND_SET_NULL(ptr)          \
{                                       \
    Free(ptr);                          \
    ptr = NULL;                         \
}

#define TRY_FREE_AND_SET_NULL(ptr) if (ptr != NULL) FREE_AND_SET_NULL(ptr)

#ifdef PORTABLE
// PokemonNative3G : le sac sans limite (999 lignes par poche, constants/global.h) alloue ses listes au tas, ~40 Ko par
// sac, même en combat ; le PC et Android n'ont pas la limite de l'EWRAM : 4 fois le tas d'Émeraude
#define HEAP_SIZE (0x1C000 * 4)
#else
#define HEAP_SIZE 0x1C000
#endif
extern u8 gHeap[HEAP_SIZE];

void *Alloc(u32 size);
void *AllocZeroed(u32 size);
void Free(void *pointer);
void InitHeap(void *heapStart, u32 heapSize);

#endif // GUARD_ALLOC_H
