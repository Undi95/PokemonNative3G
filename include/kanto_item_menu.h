#ifndef GUARD_KANTO_ITEM_MENU_H
#define GUARD_KANTO_ITEM_MENU_H

// Option SAC = KANTO : le sac de Rouge Feu (src/kanto_item_menu.c). GoToBagMenu d'Émeraude
// passe d'abord par KantoBag_TryGoToBagMenu ; les fonctions du sac d'Émeraude qu'utilise
// item_use.c (messages, fermeture, écran suivant) passent la main au sac de RF quand c'est lui
// qui est ouvert (KantoBag_IsActive).
bool8 KantoBag_TryGoToBagMenu(u8 location, u8 pocket, MainCallback exitCallback);
bool8 KantoBag_IsActive(void);
void KantoBag_RemoveCases(void);
void KantoBag_DisplayItemMessage(u8 taskId, u8 fontId, const u8 *str, TaskFunc callback);
void KantoBag_CloseItemMessage(u8 taskId);
void KantoBag_FadeAndClose(u8 taskId);
void KantoBag_SetNewScreenCallback(MainCallback callback);
void KantoBag_RemoveUsedItem(u8 pocket);
// Rouge Feu : le sac de la démonstration du vieil homme de Jadielle (option SAC = KANTO ; sinon celui de Wally)
void InitOldManBag(void);

#endif // GUARD_KANTO_ITEM_MENU_H
