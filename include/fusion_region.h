#ifndef GUARD_FUSION_REGION_H
#define GUARD_FUSION_REGION_H

// PokemonNative3G : région où se trouve le joueur (src/fusion_events.c). C'est la seule question de région du jeu :
// ce qui en dépend est propre à chaque région (décors, portes, musiques, personnages, badges, carte de la région).
// Kanto = carte avec les tilesets importés de Rouge Feu ; sans carte chargée (nouvelle partie) : Hoenn.
bool8 Fusion_IsInKanto(void);
// Badges de la région (badge 0 à 7)
u16 Fusion_GetRegionBadgeFlag(u32 badge);
u16 CountRegionBadges(void); // aussi special

#endif // GUARD_FUSION_REGION_H
