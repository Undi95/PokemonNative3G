#ifndef GUARD_KANTO_EASY_CHAT_INTERNAL_H
#define GUARD_KANTO_EASY_CHAT_INTERNAL_H

// Rouge Feu : l'écran d'Easy Chat (easy_chat_2.c, easy_chat_3.c) porté pour l'option MENUS = KANTO.
// À inclure après les en-têtes de la fusion, dans src/kanto_easy_chat_2.c et _3.c seulement :
// - les structures et les fonctions globales de RF prennent le préfixe KEC_ (Émeraude a les mêmes noms) ;
// - les mots viennent du dictionnaire de la fusion (décision du 2026-11-02 : tous les mots des deux jeux, dans les
//   deux écrans) : les fonctions de sélection de RF (easy_chat.c) sont celles d'Émeraude, exportées par easy_chat.c ;
// - les textes et les graphismes propres à RF ont leur nom Kanto.

#include "main.h"

// Structures de RF (Émeraude a les mêmes noms, d'autres champs)
#define EasyChatScreenTemplate          KEC_EasyChatScreenTemplate
#define EasyChatScreen                  KEC_EasyChatScreen
#define EasyChatPhraseFrameDimensions   KEC_EasyChatPhraseFrameDimensions

// easy_chat.h de RF : les fonctions de l'écran (easy_chat_2.c, easy_chat_3.c)
#define DoEasyChatScreen                KEC_DoEasyChatScreen
#define ShowEasyChatScreen              KEC_ShowEasyChatScreen
#define InitEasyChatGraphicsWork        KEC_InitEasyChatGraphicsWork
#define LoadEasyChatGraphics            KEC_LoadEasyChatGraphics
#define DestroyEasyChatGraphicsResources KEC_DestroyEasyChatGraphicsResources
#define EasyChatInterfaceCommand_Setup  KEC_EasyChatInterfaceCommand_Setup
#define EasyChatInterfaceCommand_Run    KEC_EasyChatInterfaceCommand_Run
#define GetEasyChatScreenFrameId        KEC_GetEasyChatScreenFrameId
#define GetTitleText                    KEC_GetTitleText
#define GetEasyChatWordBuffer           KEC_GetEasyChatWordBuffer
#define GetNumRows                      KEC_GetNumRows
#define GetNumColumns                   KEC_GetNumColumns
#define GetMainCursorColumn             KEC_GetMainCursorColumn
#define GetMainCursorRow                KEC_GetMainCursorRow
#define GetEasyChatInstructionsText     KEC_GetEasyChatInstructionsText
#define GetEasyChatConfirmText          KEC_GetEasyChatConfirmText
#define GetEasyChatConfirmCancelText    KEC_GetEasyChatConfirmCancelText
#define GetEasyChatConfirmDeletionText  KEC_GetEasyChatConfirmDeletionText
#define GetECSelectGroupCursorCoords    KEC_GetECSelectGroupCursorCoords
#define IsEasyChatAlphaMode             KEC_IsEasyChatAlphaMode
#define GetECSelectGroupRowsAbove       KEC_GetECSelectGroupRowsAbove
#define GetECSelectWordCursorCoords     KEC_GetECSelectWordCursorCoords
#define GetECSelectWordRowsAbove        KEC_GetECSelectWordRowsAbove
#define GetECSelectWordNumRows          KEC_GetECSelectWordNumRows
#define ShouldDrawECUpArrow             KEC_ShouldDrawECUpArrow
#define ShouldDrawECDownArrow           KEC_ShouldDrawECDownArrow

void DoEasyChatScreen(u8 type, u16 *words, MainCallback callback);
void ShowEasyChatScreen(void);
bool8 InitEasyChatGraphicsWork(void);
bool8 LoadEasyChatGraphics(void);
void DestroyEasyChatGraphicsResources(void);
void EasyChatInterfaceCommand_Setup(u16 id);
bool8 EasyChatInterfaceCommand_Run(void);
u8 GetEasyChatScreenFrameId(void);
const u8 *GetTitleText(void);
u16 *GetEasyChatWordBuffer(void);
u8 GetNumRows(void);
u8 GetNumColumns(void);
u8 GetMainCursorColumn(void);
u8 GetMainCursorRow(void);
void GetEasyChatInstructionsText(const u8 **str1, const u8 **str2);
void GetEasyChatConfirmText(const u8 **str1, const u8 **str2);
void GetEasyChatConfirmCancelText(const u8 **str1, const u8 **str2);
void GetEasyChatConfirmDeletionText(const u8 **str1, const u8 **str2);
void GetECSelectGroupCursorCoords(u8 *Xp, u8 *Yp);
bool8 IsEasyChatAlphaMode(void);
u8 GetECSelectGroupRowsAbove(void);
void GetECSelectWordCursorCoords(s8 *arg0, s8 *arg1);
u8 GetECSelectWordRowsAbove(void);
u8 GetECSelectWordNumRows(void);
bool32 ShouldDrawECUpArrow(void);
bool32 ShouldDrawECDownArrow(void);

// easy_chat.h de RF : la sélection des mots (easy_chat.c de RF) = celle d'Émeraude, exportée par easy_chat.c
#define InitEasyChatSelection           KEC_InitEasyChatSelection
#define DestroyEasyChatSelectionData    KEC_DestroyEasyChatSelectionData
#define GetNumDisplayableGroups         KEC_GetNumDisplayableGroups
#define GetSelectedGroupByIndex         KEC_GetSelectedGroupByIndex
#define GetEasyChatWordGroupName        KEC_GetEasyChatWordGroupName
#define CopyEasyChatWordPadded          KEC_CopyEasyChatWordPadded
#define GetUnlockedECWords              KEC_GetUnlockedECWords
#define GetDisplayedWordByIndex         KEC_GetDisplayedWordByIndex
#define GetNumDisplayedWords            KEC_GetNumDisplayedWords

bool8 InitEasyChatSelection(void);
void DestroyEasyChatSelectionData(void);
u8 GetNumDisplayableGroups(void);
u8 GetSelectedGroupByIndex(u8 index);
const u8 *GetEasyChatWordGroupName(u8 groupId);
u8 *CopyEasyChatWordPadded(u8 *dest, u16 easyChatWord, u16 totalChars);
void GetUnlockedECWords(bool32 isAlphabetical, u16 groupId);
u16 GetDisplayedWordByIndex(u16 index);
u16 GetNumDisplayedWords(void);

// overworld.c de RF
#define IsUpdateLinkStateCBActive       IsOverworldLinkActive

// text.h de RF : FONT_NORMAL_COPY_1 est sa police normale, FONT_KANTO dans la fusion (mesures de RF)
#define FONT_NORMAL_COPY_1              FONT_KANTO

// menu.c de RF : OUI / NON dans la police et à la place voulues
#define CreateYesNoMenu                 Kanto_CreateYesNoMenu
// text_window.c de RF : le cadre choisi dans les options
#define LoadUserWindowGfx               LoadUserWindowBorderGfx

// easy_chat.h de RF : le clavier alphabétique
#define NUM_ALPHABET_ROWS    4
#define NUM_ALPHABET_COLUMNS 7

// global.h et malloc.h de RF
#define JOY_REPT                        JOY_REPEAT
#define malloc                          Alloc

// flags.h de RF : les drapeaux de Kanto ont le préfixe KANTO_ dans la fusion
#define FLAG_SYS_SET_TRAINER_CARD_PROFILE FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE

// constants/easy_chat.h de RF : un type de RF qu'Émeraude n'a pas (aucun script ne le demande)
#define EASY_CHAT_TYPE_MAIL_NO_CONFIRM  21

// Textes de RF (src/kanto_easy_chat_2.c) : ceux d'Émeraude ont d'autres mots, à la mesure de ses fenêtres
#define gText_AndFillOutTheQuestionnaire  gKantoECText_AndFillOutTheQuestionnaire
#define gText_AndImproveTheBardsSong      gKantoECText_AndImproveTheBardsSong
#define gText_AndMakeAMessage             gKantoECText_AndMakeAMessage
#define gText_AndMakeYourProfile          gKantoECText_AndMakeYourProfile
#define gText_AtTheBattlesStart           gKantoECText_AtTheBattlesStart
#define gText_ChangeJustOneWordOrPhrase   gKantoECText_ChangeJustOneWordOrPhrase
#define gText_CombineFourWordsOrPhrases   gKantoECText_CombineFourWordsOrPhrases
#define gText_DelAllCancelOk              gKantoECText_DelAllCancelOk
#define gText_MakeMessageSixPhrases       gKantoECText_MakeMessageSixPhrases
#define gText_MaxTwoTwelveLetterPhrases   gKantoECText_MaxTwoTwelveLetterPhrases
#define gText_TheMailMessage              gKantoECText_TheMailMessage
#define gText_TheNewSong                  gKantoECText_TheNewSong
#define gText_TheTrendySaying             gKantoECText_TheTrendySaying
#define gText_WhatsHipAndHappening        gKantoECText_WhatsHipAndHappening

extern const u8 gText_AndFillOutTheQuestionnaire[];
extern const u8 gText_AndImproveTheBardsSong[];
extern const u8 gText_AndMakeAMessage[];
extern const u8 gText_AndMakeYourProfile[];
extern const u8 gText_AtTheBattlesStart[];
extern const u8 gText_ChangeJustOneWordOrPhrase[];
extern const u8 gText_CombineFourWordsOrPhrases[];
extern const u8 gText_DelAllCancelOk[];
extern const u8 gText_MakeMessageSixPhrases[];
extern const u8 gText_MaxTwoTwelveLetterPhrases[];
extern const u8 gText_TheMailMessage[];
extern const u8 gText_TheNewSong[];
extern const u8 gText_TheTrendySaying[];
extern const u8 gText_WhatsHipAndHappening[];

// Graphismes de RF (src/kanto_easy_chat_3.c)
#define gEasyChatWindow_Pal             gKantoEasyChatWindow_Pal
#define gEasyChatWindow_Gfx             gKantoEasyChatWindow_Gfx
#define gEasyChatWindow_Tilemap         gKantoEasyChatWindow_Tilemap
#define gEasyChatButtonWindow_Pal       gKantoEasyChatButtonWindow_Pal
#define gEasyChatButtonWindow_Gfx       gKantoEasyChatButtonWindow_Gfx
#define gEasyChatMode_Gfx               gKantoEasyChatMode_Gfx
#define gEasyChatRectangleCursor_Gfx    gKantoEasyChatRectangleCursor_Gfx

extern const u16 gEasyChatWindow_Pal[];
extern const u32 gEasyChatWindow_Gfx[];
extern const u32 gEasyChatWindow_Tilemap[];
extern const u16 gEasyChatButtonWindow_Pal[];
extern const u32 gEasyChatButtonWindow_Gfx[];
extern const u32 gEasyChatMode_Gfx[];
extern const u32 gEasyChatRectangleCursor_Gfx[];

// keyboard_text.h de RF : les rangées de l'alphabet (gText_EasyChatKeyboard_*) sont dans strings.h de la fusion,
// mêmes textes

#endif // GUARD_KANTO_EASY_CHAT_INTERNAL_H
