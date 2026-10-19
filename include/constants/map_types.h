#ifndef GUARD_CONSTANTS_MAP_TYPES_H
#define GUARD_CONSTANTS_MAP_TYPES_H

#define MAP_TYPE_NONE        0
#define MAP_TYPE_TOWN        1
#define MAP_TYPE_CITY        2
#define MAP_TYPE_ROUTE       3
#define MAP_TYPE_UNDERGROUND 4
#define MAP_TYPE_UNDERWATER  5
#define MAP_TYPE_OCEAN_ROUTE 6
#define MAP_TYPE_UNKNOWN     7 // Not used by any map.
#define MAP_TYPE_INDOOR      8
#define MAP_TYPE_SECRET_BASE 9

#define MAP_BATTLE_SCENE_NORMAL       0
#define MAP_BATTLE_SCENE_GYM          1
#define MAP_BATTLE_SCENE_MAGMA        2
#define MAP_BATTLE_SCENE_AQUA         3
#define MAP_BATTLE_SCENE_SIDNEY       4
#define MAP_BATTLE_SCENE_PHOEBE       5
#define MAP_BATTLE_SCENE_GLACIA       6
#define MAP_BATTLE_SCENE_DRAKE        7
#define MAP_BATTLE_SCENE_FRONTIER     8
// Décors de Rouge Feu (MAP_BATTLE_SCENE_X de RF ; GYM et NORMAL sont communs)
#define MAP_BATTLE_SCENE_KANTO_INDOOR_1 9 // Tour Pokémon, ruines Tanoby
#define MAP_BATTLE_SCENE_KANTO_INDOOR_2 10 // Manoir, Centrale, repaire Rocket
#define MAP_BATTLE_SCENE_KANTO_LORELEI  11
#define MAP_BATTLE_SCENE_KANTO_BRUNO    12
#define MAP_BATTLE_SCENE_KANTO_AGATHA   13
#define MAP_BATTLE_SCENE_KANTO_LANCE    14
#define MAP_BATTLE_SCENE_KANTO_LINK     15

#endif  // GUARD_CONSTANTS_MAP_TYPES_H
