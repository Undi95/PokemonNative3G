#ifndef GUARD_HEAL_LOCATION_H
#define GUARD_HEAL_LOCATION_H

struct HealLocation
{
    s8 mapGroup;
    s8 mapNum;
    u16 x;
    u16 y;
};

// Rouge Feu : où reprendre après un K.O. (respawn_* de heal_locations.json)
struct WhiteoutRespawn
{
    s8 mapGroup;
    s8 mapNum;
    u16 x;
    u16 y;
    u8 healerNpcId; // 0 : pas de reprise devant une infirmière
};

u32 GetHealLocationIndexByMap(u16 mapGroup, u16 mapNum);
const struct HealLocation *GetHealLocationByMap(u16 mapGroup, u16 mapNum);
const struct HealLocation *GetHealLocation(u32 index);
bool8 SetWhiteoutRespawnWarpAndHealerNpc(struct WarpData *warp); // Rouge Feu

#endif // GUARD_HEAL_LOCATION_H
