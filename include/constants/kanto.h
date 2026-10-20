#ifndef GUARD_CONSTANTS_KANTO_H
#define GUARD_CONSTANTS_KANTO_H

// Plages des flags et variables des régions importées (Kanto depuis Rouge Feu).
// Un flag RF de valeur N devient KANTO_FLAGS_START + N, une variable RF 0x40NN devient
// KANTO_VARS_START + 0xNN : les numéros restent lisibles et stables d'un import à l'autre.
// Stockés dans gSaveBlockKanto (src/kanto_save.c), pas dans SaveBlock1 (plein).
#define KANTO_FLAGS_START   0x1000
#define KANTO_FLAGS_COUNT   0x900
#define KANTO_FLAGS_END     (KANTO_FLAGS_START + KANTO_FLAGS_COUNT - 1)
#define KANTO_FLAG_BYTES    (KANTO_FLAGS_COUNT / 8)

#define KANTO_VARS_START    0x5000
#define KANTO_VARS_COUNT    0x100
#define KANTO_VARS_END      (KANTO_VARS_START + KANTO_VARS_COUNT - 1)

// PokemonNative3G : Pokédex de Kanto reçu du Prof. Chen (numéro de FLAG_SYS_POKEDEX_GET dans Rouge Feu,
// libre dans le bloc Kanto). FLAG_SYS_POKEDEX_GET est partagé avec Hoenn : celui-ci débloque la vue KANTO.
#define FLAG_KANTO_SYS_POKEDEX_GET (KANTO_FLAGS_START + 0x829)

#endif // GUARD_CONSTANTS_KANTO_H
