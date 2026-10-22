#ifndef GUARD_KANTO_BAG_COMPAT_H
#define GUARD_KANTO_BAG_COMPAT_H

// Noms de Rouge Feu -> équivalents d'Émeraude, pour le sac de RF (option SAC = KANTO)

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

// Endroits d'où RF ouvre le sac et qu'Émeraude n'a pas (tutoriels) : jamais utilisés ici
#define ITEMMENULOCATION_OLD_MAN          0xF0
#define ITEMMENULOCATION_TTVSCR_STATUS    0xF1
#define ITEMMENULOCATION_TTVSCR_CATCHING  0xF2
#define ITEMMENULOCATION_TTVSCR_REGISTER  0xF3
#define ITEMMENULOCATION_TTVSCR_TMS       0xF4

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

// Fonctions de RF : équivalents d'Émeraude, ou ajoutées dans src/kanto_bag.c
#define Menu_InitCursor                  InitMenuNormal
#define AddItemMenuActionTextPrinters    PrintMenuActionTexts
#define LoadMenuMessageWindowGfx         LoadMessageBoxGfx
#define LoadUserWindowGfx                LoadUserWindowBorderGfx
#define IsActiveOverworldLinkBusy        KBag_IsActiveOverworldLinkBusy
#define ResetAllBgsCoordinatesAndBgCntRegs KBag_ResetAllBgsCoordinatesAndBgCntRegs
#define SetBackdropFromPalette           KBag_SetBackdropFromPalette
#define LoadStdWindowGfx                 KBag_LoadStdWindowGfx
#define CB2_SelectBagItemToGive          KBag_CB2_SelectBagItemToGive
void CB2_ReturnToPokeStorage(void);
void CB2_GiveHoldItem(void);
void CB2_SelectBagItemToGive(void);
bool8 IsActiveOverworldLinkBusy(void);
void ResetAllBgsCoordinatesAndBgCntRegs(void);
void SetBackdropFromPalette(const u16 *palette);
void LoadStdWindowGfx(u8 windowId, u16 destOffset, u8 palOffset);

#endif // GUARD_KANTO_BAG_COMPAT_H
