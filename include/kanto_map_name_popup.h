#ifndef GUARD_KANTO_MAP_NAME_POPUP_H
#define GUARD_KANTO_MAP_NAME_POPUP_H

// PokemonNative3G : panneau du nom de lieu de Rouge Feu, sur les cartes de Kanto (src/kanto_map_name_popup.c)
void Kanto_ShowMapNamePopup(bool32 palIntoFadedBuffer);
void Kanto_DismissMapNamePopup(void);
bool32 Kanto_IsMapNamePopupTaskActive(void);

#endif // GUARD_KANTO_MAP_NAME_POPUP_H
