#ifndef GUARD_KANTO_BAG_COMPAT_H
#define GUARD_KANTO_BAG_COMPAT_H

// Noms de Rouge Feu -> équivalents d'Émeraude, pour le sac de RF (option SAC = KANTO)

struct BagPocket;

#define ItemId_GetName           GetItemName
#define ItemId_GetImportance     GetItemImportance
#define ItemId_GetDescription    GetItemDescription
#define ItemId_GetFieldFunc      GetItemFieldFunc
#define ItemId_GetBattleFunc     GetItemBattleFunc
#define ItemId_GetBattleUsage    GetItemBattleUsage
#define ItemId_GetPrice          GetItemPrice
#define ItemId_GetType           GetItemType
#define ITEM_TYPE_PARTY_MENU     ITEM_USE_PARTY_MENU
#define SE_BAG_CURSOR            SE_RG_BAG_CURSOR
#define SE_BAG_POCKET            SE_RG_BAG_POCKET
#define GetTextSpeedSetting      GetPlayerTextSpeedDelay
#define Menu_ProcessInputNoWrapAround Menu_ProcessInputNoWrap
#define GetDialogBoxFontId()     FONT_KANTO
#define FONT_NORMAL_COPY_1       FONT_KANTO

// Le Vieil Homme de RF ouvre le sac de démonstration, mais ici il garde celui d'Émeraude : jamais utilisé.
// Les emplacements de la Télé Pokémon (ITEMMENULOCATION_TTVSCR_*) sont dans item_menu.h.
#define ITEMMENULOCATION_OLD_MAN          0xF0

// tm_case.h / berry_pouch.h de RF
enum {
    TMCASE_FIELD,
    TMCASE_GIVE_PARTY,
    TMCASE_SELL,
    TMCASE_GIVE_PC,
    TMCASE_POKEDUDE,
    TMCASE_REOPENING,
};
#define TMCASE_KEEP_PREV 0xFF
enum BerryPouchType
{
    BERRYPOUCH_FROMFIELD,
    BERRYPOUCH_FROMPARTYGIVE,
    BERRYPOUCH_FROMMARTSELL,
    BERRYPOUCH_FROMPOKEMONSTORAGEPC,
    BERRYPOUCH_FROMBATTLE,
    BERRYPOUCH_FROMBERRYCRUSH,
    BERRYPOUCH_NA
};
void KantoInitTMCase(u8 type, void (*exitCallback)(void), bool8 allowSelectClose);
void KantoInitBerryPouch(u8 type, void (*savedCallback)(void), u8 allowSelect);
#define InitTMCase     KantoInitTMCase
#define SortPocketAndPlaceHMsFirst KBag_SortPocketAndPlaceHMsFirst
void SortPocketAndPlaceHMsFirst(struct BagPocket *pocket);
#define InitBerryPouch KantoInitBerryPouch
void BerryPouch_StartFadeToExitCallback(u8 taskId);
void BerryPouch_SetExitCallback(void (*exitCallback)(void));
void DisplayItemMessageInBerryPouch(u8 taskId, u8 fontId, const u8 * str, TaskFunc followUpFunc);
void Task_BerryPouch_DestroyDialogueWindowAndRefreshListMenu(u8 taskId);

// Fonctions de RF : équivalents d'Émeraude, ou ajoutées dans src/kanto_bag.c
#define Menu_InitCursor                  InitMenuNormal
#define AddItemMenuActionTextPrinters    PrintMenuActionTexts
#define LoadMenuMessageWindowGfx         LoadMessageBoxGfx
#define LoadUserWindowGfx                LoadUserWindowBorderGfx
#define IsActiveOverworldLinkBusy        KBag_IsActiveOverworldLinkBusy
#define ResetAllBgsCoordinatesAndBgCntRegs KBag_ResetAllBgsCoordinatesAndBgCntRegs
#define SetBackdropFromPalette           KBag_SetBackdropFromPalette
#define LoadStdWindowGfx                 KBag_LoadStdWindowGfx
#define LoadStdWindowGfxOnBg             KBag_LoadStdWindowGfxOnBg
#define LoadUserWindowGfx2               LoadUserWindowBorderGfx
#define DestroyYesNoMenu                 EraseYesNoWindow
#define CB2_SelectBagItemToGive          KBag_CB2_SelectBagItemToGive
void CB2_ReturnToPokeStorage(void);
void CB2_GiveHoldItem(void);
void CB2_SelectBagItemToGive(void);
bool8 IsActiveOverworldLinkBusy(void);
void ResetAllBgsCoordinatesAndBgCntRegs(void);
void SetBackdropFromPalette(const u16 *palette);
void LoadStdWindowGfx(u8 windowId, u16 destOffset, u8 palOffset);
void LoadStdWindowGfxOnBg(u8 bgId, u16 destOffset, u8 palOffset);

#endif // GUARD_KANTO_BAG_COMPAT_H
