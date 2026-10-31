#ifndef GUARD_KANTO_BAG_INTERNAL_H
#define GUARD_KANTO_BAG_INTERNAL_H

// Rouge Feu : sac (item_menu.c, bag.c, item_menu_icons.c) porté pour l'option SAC = KANTO.
// Les noms globaux de RF prennent le préfixe KBag_ (Émeraude a les mêmes).

struct YesNoFuncTable;

#define AddItemIconObject KBag_AddItemIconObject
#define AddItemIconObjectWithCustomObjectTemplate KBag_AddItemIconObjectWithCustomObjectTemplate
#define BagCreateYesNoMenuBottomRight KBag_BagCreateYesNoMenuBottomRight
#define BagCreateYesNoMenuTopRight KBag_BagCreateYesNoMenuTopRight
#define BagDrawDepositItemTextBox KBag_BagDrawDepositItemTextBox
#define BagDrawTextBoxOnWindow KBag_BagDrawTextBoxOnWindow
#define BagPrintMoneyAmount KBag_BagPrintMoneyAmount
#define BagPrintTextOnWin1CenteredColor0 KBag_BagPrintTextOnWin1CenteredColor0
#define BagPrintTextOnWindow KBag_BagPrintTextOnWindow
#define Bag_BeginCloseWin0Animation KBag_Bag_BeginCloseWin0Animation
#define CB2_SetUpReshowBattleScreenAfterMenu KBag_CB2_SetUpReshowBattleScreenAfterMenu
#define CloseBagWindow KBag_CloseBagWindow
#define CopyItemIconPicTo4x4Buffer KBag_CopyItemIconPicTo4x4Buffer
#define CreateBagSprite KBag_CreateBagSprite
#define CreateBerryPouchItemIcon KBag_CreateBerryPouchItemIcon
#define CreateItemMenuIcon KBag_CreateItemMenuIcon
#define CreateSwapLine KBag_CreateSwapLine
#define DestroyItemMenuIcon KBag_DestroyItemMenuIcon
#define DisplayItemMessageInBag KBag_DisplayItemMessageInBag
#define GetBagWindow KBag_GetBagWindow
#define GetItemIconGfxPtr KBag_GetItemIconGfxPtr
#define GoToBagMenu KBag_GoToBagMenu
#define HideBagWindow KBag_HideBagWindow
#define InitBagWindows KBag_InitBagWindows
#define ItemMenu_SetExitCallback KBag_ItemMenu_SetExitCallback
#define ItemMenu_StartFadeToExitCallback KBag_ItemMenu_StartFadeToExitCallback
#define MoveItemSlotInList KBag_MoveItemSlotInList
#define OpenBagWindow KBag_OpenBagWindow
#define PocketCalculateInitialCursorPosAndItemsAbove KBag_PocketCalculateInitialCursorPosAndItemsAbove
#define Pocket_CalculateNItemsAndMaxShowed KBag_Pocket_CalculateNItemsAndMaxShowed
#define ResetBagCursorPositions KBag_ResetBagCursorPositions
#define ResetItemMenuIconState KBag_ResetItemMenuIconState
#define SetBagVisualPocketId KBag_SetBagVisualPocketId
#define SetSwapLineInvisibility KBag_SetSwapLineInvisibility
#define ShakeBagSprite KBag_ShakeBagSprite
#define ShowBagWindow KBag_ShowBagWindow
#define Task_ReturnToBagFromContextMenu KBag_Task_ReturnToBagFromContextMenu
#define UpdateSwapLinePos KBag_UpdateSwapLinePos
#define gBagMenuState KBag_gBagMenuState
#define gBagSwapSpritePalette KBag_gBagSwapSpritePalette
#define gBagSwapSpriteSheet KBag_gBagSwapSpriteSheet
#define gSpritePalette_Bag KBag_gSpritePalette_Bag
#define gSpriteSheet_BagFemale KBag_gSpriteSheet_BagFemale
#define gSpriteSheet_BagMale KBag_gSpriteSheet_BagMale

// Poches de RF (0 Objets, 1 Objets rares, 2 Balls) -> poches d'Émeraude
#define OPEN_BAG_ITEMS     0
#define OPEN_BAG_KEYITEMS  1
#define OPEN_BAG_POKEBALLS 2
#define OPEN_BAG_LAST      3
#define NUM_BAG_POCKETS_NO_CASES 3
extern const u8 gKantoBagPocketToEmerald[NUM_BAG_POCKETS_NO_CASES];
#define KPOCKET(p) (gKantoBagPocketToEmerald[(p)])
#define KANTO_BAG_MAX_ITEMS 255

#define ITEMMENUACTION_USE           0
#define ITEMMENUACTION_TOSS          1
#define ITEMMENUACTION_REGISTER      2
#define ITEMMENUACTION_GIVE          3
#define ITEMMENUACTION_CANCEL        4
#define ITEMMENUACTION_BATTLE_USE    5
#define ITEMMENUACTION_CHECK         6
#define ITEMMENUACTION_OPEN          7
#define ITEMMENUACTION_OPEN_BERRIES  8
#define ITEMMENUACTION_WALK          9
#define ITEMMENUACTION_DESELECT     10
#define ITEMMENUACTION_DUMMY        11

#define FONT_NORMAL FONT_KANTO
#include "kanto_bag_compat.h"
#define SetHelpContext(x)
#define FREE_IF_SET(ptr) ({ if (ptr) Free(ptr); })

struct BagStruct
{
    MainCallback bagCallback;
    u8 location;
    bool8 bagOpen;
    u16 pocket;
    u16 itemsAbove[NUM_BAG_POCKETS_NO_CASES];
    u16 cursorPos[NUM_BAG_POCKETS_NO_CASES];
};
extern struct BagStruct gBagMenuState;

enum { ITEMICON_TILES, ITEMICON_PAL };

extern const struct CompressedSpriteSheet gSpriteSheet_BagMale;
extern const struct CompressedSpriteSheet gSpriteSheet_BagFemale;
extern const struct CompressedSpritePalette gSpritePalette_Bag;
extern const struct CompressedSpriteSheet gBagSwapSpriteSheet;
extern const struct CompressedSpritePalette gBagSwapSpritePalette;

void GoToBagMenu(u8 location, u8 pocket, MainCallback bagCallback);
void ResetBagCursorPositions(void);
void PocketCalculateInitialCursorPosAndItemsAbove(u8 pocketId);
void ItemMenu_StartFadeToExitCallback(u8 taskId);
void Bag_BeginCloseWin0Animation(void);
void CB2_SetUpReshowBattleScreenAfterMenu(void);
void MoveItemSlotInList(struct ItemSlot * itemSlots_, u32 from, u32 to_);
void Pocket_CalculateNItemsAndMaxShowed(u8 pocketId);
void DisplayItemMessageInBag(u8 taskId, u8 fontId, const u8 * string, TaskFunc followUpFunc);
void ItemMenu_SetExitCallback(MainCallback cb);
void Task_ReturnToBagFromContextMenu(u8 taskId);
void InitBagWindows(void);
void BagPrintTextOnWindow(u8 windowId, u8 fontId, const u8 * str, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIdx);
void BagPrintTextOnWin1CenteredColor0(const u8 * str, u8 unused);
void BagDrawDepositItemTextBox(void);
u8 ShowBagWindow(u8 whichWindow, u8 nItems);
void HideBagWindow(u8 whichWindow);
u8 OpenBagWindow(u8 whichWindow);
void CloseBagWindow(u8 whichWindow);
u8 GetBagWindow(u8 whichWindow);
void BagCreateYesNoMenuBottomRight(u8 taskId, const struct YesNoFuncTable * ptrs);
void BagCreateYesNoMenuTopRight(u8 taskId, const struct YesNoFuncTable * ptrs);
void BagPrintMoneyAmount(void);
void BagDrawTextBoxOnWindow(u8 windowId);
void ResetItemMenuIconState(void);
void CreateBagSprite(u8 animNum);
void SetBagVisualPocketId(u8 animNum);
void ShakeBagSprite(void);
void CreateSwapLine(void);
void SetSwapLineInvisibility(bool8 invisible);
void UpdateSwapLinePos(s16 x, u16 y);
void CopyItemIconPicTo4x4Buffer(const void *src, void *dest);
u8 AddItemIconObject(u16 tilesTag, u16 paletteTag, u16 itemId);
u8 AddItemIconObjectWithCustomObjectTemplate(const struct SpriteTemplate * origTemplate, u16 tilesTag, u16 paletteTag, u16 itemId);
void CreateItemMenuIcon(u16 itemId, u8 idx);
void DestroyItemMenuIcon(u8 idx);
const u32 *GetItemIconGfxPtr(u16 itemId, u8 attrId);
void CreateBerryPouchItemIcon(u16 itemId, u8 idx);

#endif // GUARD_KANTO_BAG_INTERNAL_H
