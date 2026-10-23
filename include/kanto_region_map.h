#ifndef GUARD_KANTO_REGION_MAP_H
#define GUARD_KANTO_REGION_MAP_H

// Rouge Feu (region_map.h) : carte de Kanto et des Îles Sevii
enum {
    REGIONMAP_TYPE_NORMAL,
    REGIONMAP_TYPE_WALL,
    REGIONMAP_TYPE_FLY,
    REGIONMAP_TYPE_COUNT
};

u8 *KantoGetMapName(u8 *dest, u16 mapsec, u16 fill);
u8 *KantoGetMapNameGeneric(u8 *dest, u16 mapsec);
u8 *KantoGetMapNameGeneric_(u8 *dest, u16 mapsec);
void KantoInitRegionMapWithExitCB(u8 type, void (*callback)(void));
void KantoCB2_OpenFlyMap(void);

// PokemonNative3G : Vol entre Hoenn et Kanto (SELECT sur la carte de vol)
extern bool8 gFlyMapSwitchRegion;
bool8 CanFlyBetweenRegions(void);

#endif // GUARD_KANTO_REGION_MAP_H
