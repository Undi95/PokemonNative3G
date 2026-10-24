#ifndef GUARD_FUSION_EVENTS_H
#define GUARD_FUSION_EVENTS_H

// PokemonNative3G : événements propres à la fusion (src/fusion_events.c)

// POKé MONTURE : emplacement d'équipe fictif du POKéMON des environs appelé pour une capacité de terrain
// (rendu par checkpartymove quand aucun POKéMON de l'équipe ne la connaît)
#define FIELD_MOVE_HELPER_SLOT (PARTY_SIZE + 1)

bool32 PokeMonture_CanUse(u16 move);
void PokeMonture_SetMove(u16 move);
u16 PokeMonture_HelperSpecies(void);
void PokeMonture_StartFlash(void); // fldeff_flash.c

#endif // GUARD_FUSION_EVENTS_H
