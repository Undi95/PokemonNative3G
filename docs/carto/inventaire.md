# Inventaire des fonctions de Rouge Feu absentes de la fusion

> Généré par `tools/cartographie.py` — ne pas éditer à la main.

Les 1873 fonctions propres à Rouge Feu absentes de la fusion par leur nom (`fonctions-rf-absentes.md`), chacune dans une seule catégorie. « Équivalente » est une preuve (même suite de jetons ; seuls diffèrent des noms de fonctions déjà prouvées équivalentes, jusqu'au point fixe, ou une variante Kanto du même nom) ; « à vérifier » et « manquante » se lisent à la main, puis se classent dans `tools/carto_classement.txt` avec leur preuve.

| Catégorie | Sens | Fonctions |
|---|---|---|
| manquante | rien de proche dans la fusion : à porter | 540 |
| à vérifier | ressemble à une fonction de la fusion (donnée) sans en être prouvée la même : à lire | 556 |
| équivalente | prouvée : même code sous un autre nom (seuls diffèrent des noms eux-mêmes équivalents) | 87 |
| triviale | corps vide ou d'une instruction (« return TRUE; ») : se porte avec son appelant | 120 |
| morte | jamais appelée ni référencée dans RF | 70 |
| link | link / E-Reader : à porter, désactivé | 139 |
| écartée | écartée par décision | 361 |

## Manquante (540) : rien de proche dans la fusion : à porter

### easy_chat_3.c (80)
AnimateBg2VerticalScroll, AnimateFrameResize, AnimateSeletGroupModeAndHelpSpriteEnter, ClearECRowsWin2,
CreateFooterWindow, CreateRedRectangularCursorSpritePair, CreateSelectDestFieldCursorSprite,
CreateSelectGroupHelpSprite, CreateSelectWordCursorSprite, CreateStartSelectButtonsSprites,
CreateVerticalScrollArrowSprites, DestroyEasyChatGraphicsResources, DestroyRedRectangularCursor,
DestroySelectWordCursorSprite, ECInterfaceCmd_01, ECInterfaceCmd_02, ECInterfaceCmd_03, ECInterfaceCmd_04,
ECInterfaceCmd_05, ECInterfaceCmd_06, ECInterfaceCmd_07, ECInterfaceCmd_08, ECInterfaceCmd_09,
ECInterfaceCmd_10, ECInterfaceCmd_11, ECInterfaceCmd_12, ECInterfaceCmd_13, ECInterfaceCmd_14,
ECInterfaceCmd_15, ECInterfaceCmd_16, ECInterfaceCmd_17, ECInterfaceCmd_18, ECInterfaceCmd_19,
ECInterfaceCmd_20, ECInterfaceCmd_21, ECInterfaceCmd_22, EC_AddTextPrinterParameterized,
EC_CreateYesNoMenuWithInitialCursorPos, EC_MoveCursor, EasyChatInterfaceCommand_Run,
EasyChatInterfaceCommand_Setup, FreezeSelectDestFieldCursorSprite, HideStartSelectButtonSprites,
HideVerticalScrollArrowSprites, InitBg2Scroll, InitEasyChatGraphicsWork, InitEasyChatGraphicsWork_Internal,
LoadEasyChatGraphics, LoadSpriteGfx, ModeIconsSpriteAnimIsEnded, MoveCursor_Alpha, MoveCursor_Group,
PrintECFields, PrintECGroupOrAlphaMenu, PrintECInstructionsText, PrintECInterfaceTextById, PrintECMenuById,
PrintECRowsWin2, PrintECWordsMenu, PrintEasyChatKeyboardText, PrintTitleText, PutWin2TilemapAndCopyToVram,
RedrawFrameByIndex, RunModeIconHidingAnimation, ScheduleBg2VerticalScroll,
SetSelectDestFieldCursorSpritePosAndResetAnim, SetSelectWordCursorSpritePos,
SetSelectWordCursorSpritePosExplicit, ShowModeIconsSprite, ShrinkModeIconsSprite, StartModeIconHidingAnimation,
StartWin2FrameAnim, UnfreezeSelectDestFieldCursorSprite, UpdateStartSelectButtonSpriteVisibility,
UpdateVerticalScrollArrowSpriteXPos, UpdateVerticalScrollArrowVisibility, UpdateWin2PrintWordsScrollDown,
UpdateWin2PrintWordsScrollPageDown, UpdateWin2PrintWordsScrollPageUp, UpdateWin2PrintWordsScrollUp

### easy_chat_2.c (45)
BackOutFromGroupToFieldSelect, Cancel_CreateYesNoMenu, Cancel_HandleYesNoMenu, CommitECWords,
CompareProfileResponseWithPassphrase, CompareQuestionnaireResponseWithPassphrase, Confirm_CreateYesNoMenu,
Confirm_HandleYesNoMenu, DelAll_CreateYesNoMenu, DelAll_HandleYesNoMenu, DeleteAllECFields,
EasyChatScreen_HandleJoypad, EasyChat_AllocateResources, EasyChat_FreeResources, GetECSelectGroupCursorCoords,
GetECSelectWordCursorCoords, GetEasyChatScreenTemplateId, GetMaxGroupCursorXinAlphaMode,
GetSelectWordCursorPos, GetSelectedLetter, GroupCursorMoveToBlueBox, GroupCursorWrapAroundLeft,
GroupSelectCursorXPosTooFarRight, HandleJoypad_SelectFooter, HandleJoypad_SelectGroup, HandleJoypad_SelectWord,
HasECMessageChanged, IsEcWordBufferUninitialized, MoveGroupCursorXToMaxCol, MoveWordCursorXToMaxCol,
OpenSelectedGroup, PlaceSelectedWord, SelectWordCursorAction, SetEasyChatTaskFunc, SetEasyChatWordToField,
ShouldDrawECDownArrow, ShouldDrawECUpArrow, Task_InitEasyChat, Task_InitEasyChatInternal, Task_RunEasyChat,
ToggleGroupAlphaMode, UpdateSelectGroupCursorPos_InsideBlueBox,
UpdateSelectGroupCursorPos_OutsideBlueBox_AlphaMode, UpdateSelectGroupCursorPos_OutsideBlueBox_GroupMode,
WordSelectCursorXPosTooFarRight

### start_menu.c (25)
DestroySafariZoneStatsWindow, DoDrawStartMenu, DrawSafariZoneStatsWindow, PrintSaveStats, PrintStartMenuItems,
SaveDialogCB_AskOverwriteOrReplacePreviousFileHandleInput, SaveDialogCB_AskReplacePreviousFilePrintYesNoMenu,
SaveDialogCB_AskSaveHandleInput, SaveDialogCB_DoSave, SaveDialogCB_PrintAskOverwriteText,
SaveDialogCB_PrintAskSaveText, SaveDialogCB_PrintSaveResult, SaveDialogCB_PrintSavingDontTurnOffPower,
SaveDialogCB_ReturnError, SetUpStartMenu, SetUpStartMenu_Link, SetUpStartMenu_NormalField,
SetUpStartMenu_SafariZone, SetUpStartMenu_UnionRoom, StartCB_HandleInput, StartCB_Save1, StartCB_Save2,
StartMenuPokedexSanityCheck, StartMenu_FadeScreenIfLeavingOverworld, task50_save_game

### battle_anim_special.c (23)
AnimTask_FreeBaitGfx, AnimTask_IsBallBlockedByTrainerOrDodged, AnimTask_LoadBaitGfx,
AnimTask_SafariGetReaction, AnimTask_ShinySparkles, AnimTask_ThrowBallSpecial,
AnimTask_ThrowBallSpecial_PlaySfx, CreateStarsWhenBallClicks, SpriteCB_SafariBaitOrRock_Init,
SpriteCB_ShinySparkles_1, SpriteCB_ShinySparkles_2, SpriteCB_ThrowBall_Bounce,
SpriteCB_ThrowBall_DelayThenBreakOut, SpriteCB_ThrowBall_DoClick, SpriteCB_ThrowBall_DoShake,
SpriteCB_ThrowBall_Init, SpriteCB_ThrowBall_InitClick, SpriteCB_ThrowBall_InitShake,
SpriteCB_ThrowBall_InitialFall, SpriteCB_ThrowBall_ShrinkMon, SpriteCB_ThrowBall_TenFrameDelay,
TrainerBallBlock, TrainerBallBlock2

### battle_tower.c (23)
AppendBattleTowerBannedSpeciesName, BattleTowerMapScript2, BattleTowerUtil, BufferBattleTowerTrainerMessage,
CB2_FinishEReaderBattle, CheckMonBattleTowerBanlist, CheckPartyBattleTowerBanlist,
ChooseNextBattleTowerTrainer, DetermineBattleTowerPrize, Dummy_TryEnableBravoTrainerBattleTower,
FillBattleTowerTrainerParty, GetBattleTowerTrainerClassNameId, GetBattleTowerTrainerFrontSpriteId,
GetBattleTowerTrainerName, GiveBattleTowerPrize, PopulateBravoTrainerBattleTowerLostData,
PrintBattleTowerTrainerGreeting, ResetBattleTowerStreak, SaveBattleTowerProgress, SetBattleTowerProperty,
SetBattleTowerTrainerGfxId, ShouldBattleEReaderTrainer, StartSpecialBattle

### item_use.c (20)
BattleUseFunc_PokeBallEtc, BattleUseFunc_PokeDoll, BattleUseFunc_StatBooster,
DisplayItemMessageInCurrentContext, FieldCB2_UseItemFromField, FieldUseFunc_BerryPouch,
FieldUseFunc_BlackWhiteFlute, FieldUseFunc_FameChecker, FieldUseFunc_OakStopsYou, FieldUseFunc_Repel,
FieldUseFunc_TeachyTv, FieldUseFunc_TmCase, FieldUseFunc_TownMap, ItemUseOnFieldCB_Bicycle,
ItemUse_SetQuestLogEvent, ItemUse_SwitchToPartyMenuInBattle, PrintNotTheTimeToUseThat,
Task_BattleUse_StatBooster_DelayAndPrint, Task_BattleUse_StatBooster_WaitButton_ReturnToBattle,
Task_ItemUseWaitForFade

### battle_controller_oak_old_man.c (19)
BtlCtrl_OakOldMan_SetState2Flag, BtlCtrl_OakOldMan_TestState2Flag, OakHandleChooseMove_WaitDma3,
OakOldManHandleChooseMove, OakOldManHandleEndBounceEffect, OakOldManHandleInputChooseMove,
OakOldManHandlePrintSelectionString, OakOldManHandlePrintString, OakOldManHandleSetMonData,
PrintOakTextWithMainBgDarkened, PrintOakText_ForPetesSake, PrintOakText_HowDisappointing,
PrintOakText_InflictingDamageIsKey, PrintOakText_KeepAnEyeOnHP, PrintOakText_LoweringStats,
PrintOakText_OakNoRunningFromATrainer, PrintOakText_WinEarnsPrizeMoney, SetControllerToOakOrOldMan,
SimulateInputChooseAction

### party_menu.c (19)
CB2_ReturnToBerryPouchMenu, CB2_ReturnToTMCaseMenu, CursorCB_NoEntry, EnterPartyFromItemMenuInBattle,
FirstBattleEnterParty_CreateWindowAndMsg1Printer, FirstBattleEnterParty_DestroyVoiceoverWindow,
ItemUseCB_RareCandyStep, OpenPartyMenuInTutorialBattle, PartyMenu_Oak_PrintText,
SetSwappedHeldItemQuestLogEvent, SetSwitchedPartyOrderQuestLogEvent, SetUsedFieldMoveQuestLogEvent,
SetUsedFlyQuestLogEvent, Task_FirstBattleEnterParty_RunPrinterMsg2, Task_FirstBattleEnterParty_WaitDarken,
Task_FirstBattleEnterParty_WaitFadeIn, Task_FirstBattleEnterParty_WaitFadeNormal,
Task_FirstBattleEnterParty_WaitLightenFirstMonIcon, Task_ValidateChosenMonsForBattle

### main_menu.c (17)
MoveWindowByMenuTypeAndCursorPos, PrintBadgeCount, PrintDexCount, PrintMessageOnWindow4, PrintPlayTime,
PrintPlayerName, PrintSaveErrorStatus, SetStdFrame0OnBg, Task_ExecuteMainMenuSelection, Task_HandleMenuInput,
Task_PrintMainMenuText, Task_ReturnToTileScreen, Task_SaveErrorStatus_RunPrinterThenWaitButton,
Task_SetWin0BldRegsAndCheckSaveFile, Task_SetWin0BldRegsNoSaveFileCheck, Task_WaitDma3AndFadeIn,
Task_WaitFadeAndPrintMainMenuText

### option_menu.c (15)
BufferOptionMenuString, CB2_OptionMenu, CB2_OptionsMenuFromStartMenu, CloseAndSaveOptionMenu, DrawOptionMenuBg,
InitOptionMenuBg, LoadOptionMenuItemNames, LoadOptionMenuPalette, Localize_BufferOptionMenuString,
OptionMenu_PickSwitchCancel, OptionMenu_ProcessInput, PrintOptionMenuHeader, SetOptionMenuTask,
Task_OptionMenu, UpdateSettingSelectionDisplay

### player_pc.c (15)
CB2_ReturnToMailbox, CB2_ReturnToMailboxPc_UpdateScrollVariables, Task_CreateItemStorageSubmenu,
Task_DrawMailSubmenu, Task_DrawMailboxPcMenu, Task_DrawPlayerPcTopMenu, Task_PlayerPcExitMailSubmenu,
Task_PlayerPcMailbox, Task_PlayerPcTurnOff, Task_PlayerPcWithdrawItem, Task_PrintWhatToDoWithSelectedMail,
Task_ReturnToTopMenu, Task_SetPageItemVars, Task_TopMenu_ItemStorageSubmenu_HandleInput,
Task_TryPutMailInBag_DestroyMsgIfSuccessful

### field_effect.c (13)
ApplyGlobalFieldPaletteTint, DoBirdSpriteWithPlayerAffineAnim, FallWarpEffect_7,
FieldEffectScript_LoadFadedPal, FieldEffectScript_LoadPal, ShowMonEffect_Indoors_3, ShowMonEffect_Indoors_7,
ShowMonEffect_Outdoors_5, ShowMonEffect_Outdoors_7, SpinObjectEvent, TryChangeBirdSprite,
WarpInObjectEventDownwards, WarpOutObjectEventUpwards

### event_object_movement.c (12)
MovementAction_FaceDownFast_Step0, MovementAction_FaceLeftFast_Step0, MovementAction_FaceRightFast_Step0,
MovementAction_FaceUpFast_Step0, MovementAction_GlideDown_Step0, MovementAction_GlideLeft_Step0,
MovementAction_GlideRight_Step0, MovementAction_GlideUp_Step0, MovementAction_ShakeHeadOrWalkInPlace_Step0,
SetHideObstacleFlag, ShouldInitObjectEventStateFromTemplate, TemplateIsObstacleAndVisibleFromConnectingMap

### wild_encounter.c (12)
AddToWildEncounterRateBuff, DoWildEncounterRateTest, GenerateWildMon, GetAbilityEncounterRateModType,
GetFluteEncounterRateModType, GetMapBaseEncounterCooldown, HandleWildEncounterCooldown,
IsLeadMonHoldingCleanseTag, ResetEncounterRateModifiers, SeedWildEncounterRng, TryStandardWildEncounter,
WildEncounterRandom

### field_fadetransition.c (10)
DoTeleport2Warp, DoUnionRoomWarp, ExitWarpFadeInScreen, FadeTransition_FadeInOnReturnToStartMenu,
FieldCB_SafariZoneRanOutOfBalls, Task_CableClubWarp, Task_DoorWarp, Task_ReturnFromLinkRoomWarp,
Task_SafariZoneRanOutOfBalls, WarpFadeInScreenWithDelay

### text.c (10)
DecompressGlyph_Female, DecompressGlyph_Male, DecompressGlyph_NormalCopy1, DecompressGlyph_NormalCopy2,
FontFunc_Female, FontFunc_Male, FontFunc_NormalCopy1, FontFunc_NormalCopy2, GetGlyphWidth_Female,
GetGlyphWidth_Male

### save_failed_screen.c (9)
BlankPalettes, ClearMapBuffer, FillBgMapBufferRect, PrintTextOnSaveFailedScreen, RequestDmaCopyFromCharBuffer,
RequestDmaCopyFromScreenBuffer, RunSaveFailedScreen, TryWipeDamagedSectors, UpdateMapBufferWithText

### overworld.c (8)
CB2_EnterFieldFromQuestLog, CB2_SetUpOverworldForQLPlayback, CountBadgesForOverworldWhiteOutLossCalculation,
DoCB1_Overworld_QuestLogPlayback, MetatileBehavior_IsSurfableInSeafoamIslands,
Overworld_MusicCanOverrideMapMusic, Overworld_ResetStateAfterWhitingOut, QL_LoadMapNormal

### script_menu.c (8)
CreateMCMenuInputHandlerTask, CreatePCMenuWindow, DrawVerticalMultichoiceMenu, GetMCWindowHeight,
GetMenuWidthFromList, GetStringTilesWide, MultiChoicePrintHelpDescription, QL_DestroyAbortedDisplay

### bike.c (7)
BikeInputHandler_Normal, BikeInputHandler_Slope, BikeInputHandler_Turning, BikeTransition_Downhill,
BikeTransition_MoveDirection, BikeTransition_Uphill, MetatileBehaviorForbidsBiking

### pokemon_storage_system_data.c (7)
AddBoxMenu, HandleInput_BoxTitle, HandleInput_InBox_MovingMultiple, HandleInput_InBox_Normal,
SetMenuTextsForItem, SetMenuTextsForMon, ToggleCursorMultiMoveMode

### daycare.c (6)
SpriteCB_Egg_0, SpriteCB_Egg_1, SpriteCB_Egg_2, SpriteCB_Egg_3, SpriteCB_Egg_4, SpriteCB_Egg_5

### mailbox_pc.c (6)
ItemPrintFunc, MailboxPC_AddScrollIndicatorArrows, MailboxPC_GetAddWindow, MailboxPC_InitBuffers,
MailboxPC_InitListMenu, MailboxPC_RemoveWindow

### new_menu_helpers.c (6)
CreateStartMenuWindow, DecompressAndCopyTileDataToVram2, DecompressAndLoadBgGfxUsingHeap2,
DisplayYesNoMenuDefaultNo, LoadStdWindowFrameGfx, TaskFreeBufAfterCopyingTileDataToVram

### clear_save_data_screen.c (5)
CB2_SaveClearScreen_Init, CB2_Sub_SaveClearScreen_Init, Task_CleanUpAndSoftReset, Task_DrawClearSaveDataScreen,
Task_HandleYesNoMenu

### field_player_avatar.c (5)
GetPlayerAvatarVsSeekerGfxId, MetatileAtCoordsIsWaterTile, PlayerAvatarTransition_Bike,
QL_TryRecordNPCStepWithDuration32, QL_TryRecordPlayerStepWithDuration0

### map_name_popup.c (5)
DismissMapNamePopup, MapNamePopupAppendFloorNum, MapNamePopupCreateWindow, MapNamePopupPrintMapNameOnWindow,
Task_MapNamePopup

### pokemon.c (5)
InitMonSpritesGfx_Mode1, Localize_BattleStrings, SetMonExpWithMaxLevelCheck, es_sub_8044D1C, es_sub_8044D64

### pokemon_storage_system_graphics.c (5)
DoReleaseMonAnim, DoReleaseMonComeBackAnim, SetBoxSpeciesAndPersonalities, SetShiftMonSpritePtr, ShiftMons

### battle_main.c (4)
BattleIntroOpponentSendsOutMonAnimation, BattleIntroPlayerSendsOutMonAnimation, HandleAction_ThrowBait,
HandleAction_ThrowRock

### battle_transition.c (4)
Spiral_End, Spiral_Init, Spiral_UpdateFrame, VBlankCB_Spiral

### event_data.c (4)
EnableNationalPokedex_RSE, GetFlagAddr, IsFlagOrVarStoredInQuestLog, ResetSpecialVars

### field_screen_effect.c (4)
BarnDoorWipeLoadGpuRegs, BarnDoorWipeSaveGpuRegs, Task_BarnDoorWipe, Task_BarnDoorWipeChild

### field_specials.c (4)
QuestLog_CheckDepartingIndoorsMap, QuestLog_TryRecordDepartedLocation, SetDeoxysTrianglePalette,
Task_DoDeoxysTriangleInteraction

### title_screen.c (4)
CreateStreakSprites, SpriteCallback_Streak, SpriteCallback_TitleScreenLeaf, Task_LeafSpawner

### trainer_card.c (4)
DmaClearOam, DmaClearPltt, SetTrainerCardBgsAndPals, SetTrainerCardCB2

### battle_gfx_sfx_util.c (3)
BattleInterfaceSetWindowPals, DecompressTrainerBackPalette, FreeTrainerFrontPicPaletteAndTile

### field_weather.c (3)
ApplyGammaShift, BuildGammaShiftTables, SlightlyDarkenPalsInWeather

### fieldmap.c (3)
ExtractMetatileAttribute, GetAttributeByMetatileIdAndMapLayout, MapGridGetMetatileAttributeAt

### mail.c (3)
AddMailMessagePrinters, BufferMailMessage, ShowMailCB_Teardown

### pokemon_storage_system_menu.c (3)
ChooseBoxMenu_PrintBoxNameAndCount, ChooseBoxMenu_PrintTextToSprite, CreatePCMainMenu

### pokemon_storage_system_misc.c (3)
IsActiveItemMoving, Item_SwitchMonsWithMoving, MultiMove_InitBg

### pokemon_storage_system_tasks.c (3)
IsDisplayMonMosaicActive, PrintStorageMessage, SetPokeStorageQuestLogEvent

### trainer_see.c (3)
MovementAction_RevealTrainer_RunTrainerSeeFuncList, StartTrainerApproachWithFollowupTask,
TrainerApproachPlayer

### battle_anim_flying.c (2)
AnimUnusedFeather, AnimUnusedFeather_Step

### battle_anim_normal.c (2)
AnimShakeMonOrBattleTerrain, AnimTask_ShakeBattleTerrain

### battle_controller_player.c (2)
PreviewDeterminativeMoveTargets, Task_CreateLevelUpVerticalStripes

### battle_message.c (2)
BattleStringShouldBeColored, Localize_TrainerClass_Names

### battle_records.c (2)
AddOpponentLinkBattleRecord, UpdateBattleOutcomeOnTrainerCards

### easy_chat.c (2)
DestroyEasyChatSelectionData, PopulateECGroups

### fldeff_cut.c (2)
MetatileAtCoordsIsGrassTile, SetCutGrassMetatileAt

### item.c (2)
SetPcItemQuantity, TrySetObtainedItemQuestLogEvent

### menu.c (2)
DestroyYesNoMenu, MultichoiceGrid_PrintItems

### new_game.c (2)
ClearBattleTower, WarpToPlayersRoom

### scrcmd.c (2)
ScriptContext_GetQuestLogInput, ScriptContext_NextCommandEndsScript

### shop.c (2)
RecordItemTransaction, RecordTransactionForQuestLog

### sound.c (2)
BGMVolumeMax_EnableHelpSystemReduction, SetBGMVolume_SuppressHelpSystemReduction

### text_window.c (2)
LoadQuestLogWindowTiles, LoadStdWindowTiles

### battle_ai_script_commands.c (1)
Cmd_if_level_compare

### battle_anim_mons.c (1)
GetBattleAnimBgDataByPriorityRank

### battle_setup.c (1)
StartTrainerBattle

### berry.c (1)
InitEnigmaBerry

### bg.c (1)
AdjustBgMosaic

### blend_palette.c (1)
BlendPalettesAt

### coins.c (1)
PrintCoinsString_Parameterized

### dma3_manager.c (1)
WaitDma3Request

### field_control_avatar.c (1)
QuestLogOverrideJoyVars

### field_weather_effects.c (1)
SetThunderCounter

### heal_location.c (1)
SetWhiteoutRespawnHealerNpcAsLastTalked

### menu_helpers.c (1)
GetDialogBoxFontId

### naming_screen.c (1)
NamingScreen_CreateRivalIcon

### palette.c (1)
CopyPaletteInvertedTint

### pokemon_icon.c (1)
LoadMonIconPalettesAt

### reshow_battle_screen.c (1)
ReshowBattleScreen_TurnOnDisplay

### save_menu_util.c (1)
SaveStatToString

### script_pokemon_util.c (1)
ChooseBattleTowerPlayerParty

### text_window_graphics.c (1)
GetUserWindowGraphics

### tilemap_util.c (1)
TilemapUtil_SetTilemap


## À vérifier (556) : ressemble à une fonction de la fusion (donnée) sans en être prouvée la même : à lire

### field_effect.c (59)
CreateTeleportFieldEffectTask ~ FldEff_TeleportWarpOut (field_effect.c, 88 %)
EscalatorWarpEffect_1 ~ EscalatorWarpOut_Init (field_effect.c, 90 %)
EscalatorWarpEffect_4 ~ EscalatorWarpOut_Up_End (field_effect.c, 85 %)
EscalatorWarpEffect_6 ~ EscalatorWarpOut_Up_End (field_effect.c, 85 %)
EscalatorWarpInEffect_1 ~ EscalatorWarpIn_Init (field_effect.c, 97 %)
EscalatorWarpInEffect_7 ~ EscalatorWarpIn_End (field_effect.c, 89 %)
Escalator_TransitionToWarpInEffect ~ WarpAtEndOfEscalator (field_effect.c, 95 %)
FallWarpEffect_1 ~ FallWarpEffect_Init (field_effect.c, 98 %)
FallWarpEffect_2 ~ FallWarpEffect_WaitWeather (field_effect.c, 95 %)
FallWarpEffect_4 ~ FallWarpEffect_Fall (field_effect.c, 97 %)
FallWarpEffect_6 ~ FallWarpEffect_CameraShake (field_effect.c, 97 %)
FieldCB_EscalatorWarpIn ~ FieldCB_FallWarpExit (field_effect.c, 90 %)
FieldCallback_EscapeRopeExit ~ FieldCallback_EscapeRopeWarpIn (field_effect.c, 95 %)
FieldCallback_TeleportIn ~ FieldCallback_TeleportWarpIn (field_effect.c, 91 %)
LavaridgeGym1FWarpEffect_1 ~ LavaridgeGym1FWarpEffect_Init (field_effect.c, 94 %)
LavaridgeGym1FWarpEffect_2 ~ LavaridgeGym1FWarpEffect_AshPuff (field_effect.c, 99 %)
LavaridgeGym1FWarpEffect_4 ~ LavaridgeGym1FWarpEffect_FadeOut (field_effect.c, 96 %)
LavaridgeGymB1FWarpEffect_1 ~ LavaridgeGymB1FWarpEffect_Init (field_effect.c, 96 %)
LavaridgeGymB1FWarpEffect_3 ~ LavaridgeGymB1FWarpEffect_Launch (field_effect.c, 98 %)
LavaridgeGymB1FWarpExitEffect_1 ~ LavaridgeGymB1FWarpExitEffect_Init (field_effect.c, 97 %)
LavaridgeGymB1FWarpExitEffect_2 ~ LavaridgeGymB1FWarpExitEffect_StartPopOut (field_effect.c, 98 %)
LavaridgeGymB1FWarpExitEffect_3 ~ LavaridgeGymB1FWarpExitEffect_PopOut (field_effect.c, 98 %)
LoadFieldMoveStreaksTilemapToVram ~ LoadFieldMoveOutdoorStreaksTilemap (field_effect.c, 88 %)
PokeballGlowEffect_FlashFirstThree ~ PokeballGlowEffect_Flash1 (field_effect.c, 97 %)
ShowMonEffect_Indoors_1 ~ FieldMoveShowMonIndoorsEffect_Init (field_effect.c, 78 %)
ShowMonEffect_Indoors_2 ~ FieldMoveShowMonIndoorsEffect_LoadGfx (field_effect.c, 88 %)
ShowMonEffect_Indoors_4 ~ FieldMoveShowMonIndoorsEffect_WaitForMon (field_effect.c, 97 %)
ShowMonEffect_Indoors_5 ~ FieldMoveShowMonIndoorsEffect_RestoreBg (field_effect.c, 84 %)
ShowMonEffect_Indoors_6 ~ FieldMoveShowMonIndoorsEffect_SlideBannerOff (field_effect.c, 96 %)
ShowMonEffect_Outdoors_1 ~ FieldMoveShowMonOutdoorsEffect_Init (field_effect.c, 86 %)
ShowMonEffect_Outdoors_2 ~ FieldMoveShowMonOutdoorsEffect_LoadGfx (field_effect.c, 88 %)
ShowMonEffect_Outdoors_3 ~ FieldMoveShowMonOutdoorsEffect_CreateBanner (field_effect.c, 80 %)
ShowMonEffect_Outdoors_4 ~ FieldMoveShowMonOutdoorsEffect_WaitForMon (field_effect.c, 97 %)
ShowMonEffect_Outdoors_6 ~ FieldMoveShowMonOutdoorsEffect_RestoreBg (field_effect.c, 88 %)
SpriteCB_FlyBirdWithPlayer ~ SpriteCB_FlyBirdSwoopDown (field_effect.c, 83 %)
SpriteCB_PopOutOfAsh ~ SpriteCB_AshLaunch (field_effect.c, 88 %)
Task_DoTeleportFieldEffect ~ Task_EscapeRopeWarpOut (field_effect.c, 95 %)
Task_DoTeleportInFieldEffect ~ Task_EscapeRopeWarpOut (field_effect.c, 95 %)
Task_EscalatorWarpFieldEffect ~ Task_FallWarpFieldEffect (field_effect.c, 93 %)
Task_EscalatorWarpInFieldEffect ~ Task_EscalatorWarpIn (field_effect.c, 96 %)
Task_FldEffUseSurf ~ Task_EscapeRopeWarpOut (field_effect.c, 95 %)
Task_MoveDeoxysRock_Step ~ Task_MoveDeoxysRock (field_effect.c, 93 %)
Task_ShowMon_Indoors ~ Task_EscapeRopeWarpOut (field_effect.c, 95 %)
Task_ShowMon_Outdoors ~ Task_EscapeRopeWarpOut (field_effect.c, 95 %)
TeleportFieldEffectTask1 ~ TeleportWarpOutFieldEffect_Init (field_effect.c, 97 %)
TeleportFieldEffectTask2 ~ TeleportWarpOutFieldEffect_SpinGround (field_effect.c, 93 %)
TeleportFieldEffectTask3 ~ TeleportWarpOutFieldEffect_SpinExit (field_effect.c, 99 %)
TeleportFieldEffectTask4 ~ WarpAtEndOfEscalator (field_effect.c, 79 %)
TeleportInFieldEffectTask3 ~ TeleportWarpInFieldEffect_SpinGround (field_effect.c, 94 %)
UseSurfEffect_2 ~ SurfFieldEffect_FieldMovePose (field_effect.c, 98 %)
UseSurfEffect_3 ~ SurfFieldEffect_ShowMon (field_effect.c, 96 %)
UseSurfEffect_4 ~ SurfFieldEffect_JumpOnSurfBlob (field_effect.c, 99 %)
UseSurfEffect_5 ~ SurfFieldEffect_End (field_effect.c, 95 %)
VBlankCB_ShowMonEffect_Indoors ~ VBlankCB_FieldMoveShowMonIndoors (field_effect.c, 77 %)
VBlankCB_ShowMonEffect_Outdoors ~ VBlankCB_FieldMoveShowMonOutdoors (field_effect.c, 88 %)
waterfall_1_do_anim_probably ~ WaterfallFieldEffect_ShowMon (field_effect.c, 96 %)
waterfall_2_wait_anim_finish_probably ~ WaterfallFieldEffect_WaitForShowMon (field_effect.c, 96 %)
waterfall_3_move_player_probably ~ WaterfallFieldEffect_RideUp (field_effect.c, 92 %)
waterfall_4_wait_player_move_probably ~ WaterfallFieldEffect_ContinueRideOrEnd (field_effect.c, 96 %)

### event_object_movement.c (52)
CalcWhetherObjectIsOffscreen ~ UpdateObjectEventOffscreen (event_object_movement.c, 81 %)
CameraObjectReset1 ~ CameraObjectReset (event_object_movement.c, 79 %)
CameraObjectReset2 ~ CameraObjectFreeze (event_object_movement.c, 85 %)
CameraObjectSetFollowedObjectId ~ CameraObjectSetFollowedSpriteId (event_object_movement.c, 80 %)
CopyablePlayerMovement_GoSpeed0 ~ CopyablePlayerMovement_WalkFast (event_object_movement.c, 98 %)
CopyablePlayerMovement_GoSpeed1 ~ CopyablePlayerMovement_WalkFast (event_object_movement.c, 99 %)
CopyablePlayerMovement_GoSpeed2 ~ CopyablePlayerMovement_WalkFaster (event_object_movement.c, 99 %)
CopyablePlayerMovement_GoSpeed4 ~ CopyablePlayerMovement_Jump (event_object_movement.c, 99 %)
FaceDirectionFast ~ AcroWheelieFaceDirection (event_object_movement.c, 81 %)
FindCameraObject ~ FindCameraSprite (event_object_movement.c, 96 %)
MakeObjectTemplateFromObjectEventTemplate ~ MakeSpriteTemplateFromObjectEventTemplate (event_object_movement.c, 90 %)
MovementAction_EmoteSmile_Step0 ~ MovementAction_EmoteExclamationMark_Step0 (event_object_movement.c, 97 %)
MovementAction_GlideDown_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 88 %)
MovementAction_GlideLeft_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 88 %)
MovementAction_GlideRight_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 88 %)
MovementAction_GlideUp_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 88 %)
MovementAction_JumpSpecialWithEffectDown_Step0 ~ MovementAction_JumpSpecialDown_Step0 (event_object_movement.c, 94 %)
MovementAction_JumpSpecialWithEffectDown_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_JumpSpecialWithEffectLeft_Step0 ~ MovementAction_JumpSpecialLeft_Step0 (event_object_movement.c, 94 %)
MovementAction_JumpSpecialWithEffectLeft_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_JumpSpecialWithEffectRight_Step0 ~ MovementAction_JumpSpecialRight_Step0 (event_object_movement.c, 94 %)
MovementAction_JumpSpecialWithEffectRight_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_JumpSpecialWithEffectUp_Step0 ~ MovementAction_JumpSpecialUp_Step0 (event_object_movement.c, 94 %)
MovementAction_JumpSpecialWithEffectUp_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_WalkSlowerDown_Step0 ~ MovementAction_WalkSlowDown_Step0 (event_object_movement.c, 89 %)
MovementAction_WalkSlowerDown_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_WalkSlowerLeft_Step0 ~ MovementAction_WalkSlowLeft_Step0 (event_object_movement.c, 89 %)
MovementAction_WalkSlowerLeft_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_WalkSlowerRight_Step0 ~ MovementAction_WalkSlowRight_Step0 (event_object_movement.c, 89 %)
MovementAction_WalkSlowerRight_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_WalkSlowerUp_Step0 ~ MovementAction_WalkSlowUp_Step0 (event_object_movement.c, 89 %)
MovementAction_WalkSlowerUp_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_WalkSlowestDown_Step0 ~ MovementAction_WalkSlowDown_Step0 (event_object_movement.c, 89 %)
MovementAction_WalkSlowestDown_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_WalkSlowestLeft_Step0 ~ MovementAction_WalkSlowLeft_Step0 (event_object_movement.c, 89 %)
MovementAction_WalkSlowestLeft_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_WalkSlowestRight_Step0 ~ MovementAction_WalkSlowRight_Step0 (event_object_movement.c, 89 %)
MovementAction_WalkSlowestRight_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementAction_WalkSlowestUp_Step0 ~ MovementAction_WalkSlowUp_Step0 (event_object_movement.c, 89 %)
MovementAction_WalkSlowestUp_Step1 ~ MovementAction_WalkSlowDiagonalUpLeft_Step1 (event_object_movement.c, 96 %)
MovementType_WanderAround_Step5Slower ~ MovementType_WanderAround_Step5 (event_object_movement.c, 97 %)
ObjectCB_CameraObject ~ SpriteCB_CameraObject (event_object_movement.c, 90 %)
ObjectEventCheckForReflectiveSurface ~ ObjectEventGetNearbyReflectionType (event_object_movement.c, 83 %)
QL_UpdateObjectEventCurrentMovement ~ UpdateObjectEventCurrentMovement (event_object_movement.c, 76 %)
QuestLogObjectEventExecHeldMovementAction ~ ObjectEventExecHeldMovementAction (event_object_movement.c, 77 %)
TryLoadObjectPalette ~ LoadSpritePaletteIfTagExists (event_object_movement.c, 96 %)
UpdateMovementGlide ~ UpdateMovementNormal (event_object_movement.c, 89 %)
UpdateObjEventSpriteVisibility ~ UpdateObjectEventSpriteVisibility (event_object_movement.c, 96 %)
UpdateWalkSlower ~ UpdateMovementNormal (event_object_movement.c, 97 %)
UpdateWalkSlowerAnim ~ UpdateWalkSlowAnim (event_object_movement.c, 97 %)
UpdateWalkSlowest ~ UpdateMovementNormal (event_object_movement.c, 97 %)
UpdateWalkSlowestAnim ~ UpdateKantoWalkSlowAnim (event_object_movement.c, 82 %)

### field_player_avatar.c (26)
CreateStopSurfingTask_NoMusicChange ~ CreateStopSurfingTask (field_player_avatar.c, 95 %)
DoBoulderDust ~ PushBoulder_Move (field_player_avatar.c, 83 %)
DoBoulderFinish ~ PushBoulder_End (field_player_avatar.c, 88 %)
Fishing10 ~ Fishing_MonOnHook (field_player_avatar.c, 94 %)
Fishing11 ~ Fishing_StartEncounter (field_player_avatar.c, 95 %)
Fishing12 ~ Fishing_NotEvenNibble (field_player_avatar.c, 90 %)
Fishing13 ~ Fishing_GotAway (field_player_avatar.c, 82 %)
Fishing14 ~ Fishing_NoMon (field_player_avatar.c, 84 %)
Fishing15 ~ Fishing_PutRodAway (field_player_avatar.c, 96 %)
Fishing16 ~ Fishing_EndNoMon (field_player_avatar.c, 95 %)
Fishing2 ~ Fishing_GetRodOut (field_player_avatar.c, 88 %)
Fishing3 ~ Fishing_WaitBeforeDots (field_player_avatar.c, 92 %)
Fishing5 ~ Fishing_ShowDots (field_player_avatar.c, 84 %)
Fishing6 ~ Fishing_CheckForBite (field_player_avatar.c, 66 %)
Fishing7 ~ Fishing_NoMon (field_player_avatar.c, 80 %)
Fishing8 ~ Fishing_WaitForA (field_player_avatar.c, 86 %)
Fishing9 ~ Fishing_CheckMoreDots (field_player_avatar.c, 92 %)
GetTeleportSavedFacingDirection ~ GetSpinStartFacingDir (field_player_avatar.c, 83 %)
StartPlayerAvatarSummonMonForFieldMoveAnim ~ SetPlayerAvatarFieldMove (field_player_avatar.c, 96 %)
StartTeleportInPlayerAnim ~ DoPlayerMatSpin (field_player_avatar.c, 82 %)
StartTeleportWarpOutPlayerAnim ~ DoPlayerMatSpin (field_player_avatar.c, 82 %)
Task_BumpBoulder ~ Task_PushBoulder (field_player_avatar.c, 97 %)
Task_TeleportWarpInPlayerAnim ~ Task_DoPlayerSpinEntrance (field_player_avatar.c, 96 %)
Task_TeleportWarpOutPlayerAnim ~ Task_DoPlayerSpinExit (field_player_avatar.c, 96 %)
TeleportAnim_RotatePlayer ~ TrySpinPlayerForWarp (field_player_avatar.c, 90 %)
player_step ~ PlayerStep (field_player_avatar.c, 87 %)

### battle_controller_oak_old_man.c (24)
CopyOakOldManMonData ~ CopyLinkPartnerMonData (battle_controller_link_partner.c, 95 %)
OakOldManBufferExecCompleted ~ PokedudeBufferExecCompleted (kanto_battle_controller_pokedude.c, 84 %)
OakOldManBufferRunCommand ~ PokedudeBufferRunCommand (kanto_battle_controller_pokedude.c, 63 %)
OakOldManDoMoveAnimation ~ PokedudeDoMoveAnimation (kanto_battle_controller_pokedude.c, 97 %)
OakOldManHandleBattleAnimation ~ LinkOpponentHandleBattleAnimation (battle_controller_link_opponent.c, 94 %)
OakOldManHandleChooseAction ~ OldManHandleChooseAction (battle_controller_old_man.c, 75 %)
OakOldManHandleChoosePokemon ~ PokedudeHandleChoosePokemon (kanto_battle_controller_pokedude.c, 84 %)
OakOldManHandleCmd55 ~ OldManHandleEndLinkBattle (battle_controller_old_man.c, 88 %)
OakOldManHandleDrawPartyStatusSummary ~ LinkOpponentHandleDrawPartyStatusSummary (battle_controller_link_opponent.c, 84 %)
OakOldManHandleDrawTrainerPic ~ SafariHandleDrawTrainerPic (battle_controller_safari.c, 69 %)
OakOldManHandleExpUpdate ~ PlayerHandleExpUpdate (battle_controller_player.c, 81 %)
OakOldManHandleFaintAnimation ~ PokedudeHandleFaintAnimation (kanto_battle_controller_pokedude.c, 89 %)
OakOldManHandleFaintingCry ~ LinkPartnerHandleFaintingCry (battle_controller_link_partner.c, 75 %)
OakOldManHandleGetMonData ~ PokedudeHandleGetMonData (kanto_battle_controller_pokedude.c, 76 %)
OakOldManHandleHitAnimation ~ LinkOpponentHandleHitAnimation (battle_controller_link_opponent.c, 75 %)
OakOldManHandleIntroSlide ~ LinkOpponentHandleIntroSlide (battle_controller_link_opponent.c, 60 %)
OakOldManHandleIntroTrainerBallThrow ~ PlayerHandleIntroTrainerBallThrow (battle_controller_player.c, 89 %)
OakOldManHandleLinkStandbyMsg ~ PokedudeHandleLinkStandbyMsg (kanto_battle_controller_pokedude.c, 100 %)
OakOldManHandleMoveAnimation ~ LinkOpponentHandleMoveAnimation (battle_controller_link_opponent.c, 95 %)
OakOldManHandlePlayFanfare ~ LinkPartnerHandlePlayFanfareOrBGM (battle_controller_link_partner.c, 100 %)
OakOldManHandlePlaySE ~ LinkPartnerHandlePlayFanfareOrBGM (battle_controller_link_partner.c, 100 %)
OakOldManHandleReturnMonToBall ~ OldManHandleReturnMonToBall (battle_controller_old_man.c, 91 %)
OakOldManHandleTrainerSlide ~ SafariHandleDrawTrainerPic (battle_controller_safari.c, 65 %)
SetOakOldManMonData ~ SetLinkPartnerMonData (battle_controller_link_partner.c, 96 %)

### player_pc.c (23)
CB2_ReturnFromDepositMenu ~ ItemStorage_ReshowAfterBagMenu (player_pc.c, 76 %)
CB2_SetCbToReturnToMailbox ~ CB2_PlayerPCExitBagMenu (player_pc.c, 90 %)
CountPCMail ~ GetMailboxMailCount (player_pc.c, 77 %)
PCMailCompaction ~ Mailbox_CompactMailList (player_pc.c, 76 %)
PrintStringOnWindow0WithDialogueFrame ~ ItemStorageMenuPrint (player_pc.c, 92 %)
Task_DepositItem_WaitFadeAndGoToBag ~ Task_WithdrawItem_WaitFadeAndGoToItemStorage (player_pc.c, 83 %)
Task_DestroyMailboxPcViewAndCancel ~ Mailbox_ReturnToPlayerPC (player_pc.c, 85 %)
Task_DrawYesNoMenuToConfirmMoveToBag ~ Mailbox_AskConfirmMoveToBag (player_pc.c, 93 %)
Task_Error_NoPokemon ~ Mailbox_MoveToBag (player_pc.c, 75 %)
Task_MailSubmenuHandleInput ~ Mailbox_MailOptionsProcessInput (player_pc.c, 77 %)
Task_MailboxPcHandleInput ~ Mailbox_ProcessInput (player_pc.c, 77 %)
Task_MoveToBagYesNoMenuHandleInput ~ Mailbox_HandleConfirmMoveToBag (player_pc.c, 77 %)
Task_PlayerPcCancel ~ ItemStorage_EraseMainMenu (player_pc.c, 77 %)
Task_PlayerPcDepositItem ~ ItemStorage_Deposit (player_pc.c, 94 %)
Task_PlayerPcGiveMailToMon ~ Mailbox_Give (player_pc.c, 94 %)
Task_PlayerPcItemStorage ~ PlayerPC_ItemStorage (player_pc.c, 83 %)
Task_PlayerPcMoveMailToBag ~ Mailbox_MoveToBag (player_pc.c, 83 %)
Task_PlayerPcReadMail ~ Mailbox_DoMailRead (player_pc.c, 94 %)
Task_RedrawPlayerPcMailboxAndSetUpInputHandler ~ Mailbox_Cancel (player_pc.c, 85 %)
Task_ReturnToItemStorageSubmenu ~ ItemStorage_HandleReturnToProcessInput (player_pc.c, 95 %)
Task_WaitFadeAndGoToPartyMenu ~ Mailbox_DoGiveMailPokeMenu (player_pc.c, 96 %)
Task_WaitFadeAndReadSelectedMail ~ Mailbox_DoGiveMailPokeMenu (player_pc.c, 83 %)
Task_WaitFadeAndReturnToMailboxPcInputHandler ~ ItemStorage_HandleReturnToProcessInput (player_pc.c, 95 %)

### start_menu.c (22)
AppendToStartMenuItems ~ AddStartMenuAction (start_menu.c, 75 %)
CloseSaveStatsWindow ~ RemoveSaveInfoWindow (start_menu.c, 85 %)
CloseStartMenu ~ HideStartMenuWindow (start_menu.c, 86 %)
DoSetUpSaveAfterLinkBattle ~ InitSaveWindowAfterLinkBattle (start_menu.c, 88 %)
DrawStartMenuInOneGo ~ InitStartMenu (start_menu.c, 87 %)
FieldCB2_DrawStartMenu ~ FieldCB_ReturnToFieldStartMenu (start_menu.c, 76 %)
OpenStartMenuWithFollowupFunc ~ CreateStartMenuTask (start_menu.c, 83 %)
PrintSaveTextWithFollowupFunc ~ ShowSaveMessage (start_menu.c, 82 %)
RunSaveDialogCB ~ RunSaveCallback (start_menu.c, 79 %)
SaveDialogCB_AskOverwritePrintYesNoMenu ~ SaveYesNoCallback (start_menu.c, 76 %)
SaveDialogCB_AskSavePrintYesNoMenu ~ SaveYesNoCallback (start_menu.c, 76 %)
SaveDialogCB_ReturnSuccess ~ SaveReturnSuccessCallback (start_menu.c, 80 %)
SaveDialogCB_WaitPrintErrorAndPlaySE ~ SaveErrorCallback (start_menu.c, 80 %)
SaveDialogCB_WaitPrintSuccessAndPlaySE ~ SaveSuccessCallback (start_menu.c, 80 %)
SaveDialog_Wait60FramesOrAButtonHeld ~ SaveSuccesTimer (start_menu.c, 90 %)
SaveDialog_Wait60FramesThenCheckAButtonHeld ~ SaveSuccesTimer (start_menu.c, 60 %)
SetUpReturnToStartMenu ~ ShowReturnToFieldStartMenu (start_menu.c, 85 %)
StartMenuPlayerCallback ~ StartMenuPokemonCallback (start_menu.c, 91 %)
StartMenu_PrepareForSave ~ InitSave (start_menu.c, 78 %)
Task_StartMenuHandleInput ~ Task_ShowStartMenu (start_menu.c, 86 %)
task50_after_link_battle_save ~ Task_SaveAfterLinkBattle (start_menu.c, 81 %)
task50_startmenu ~ StartMenuTask (start_menu.c, 93 %)

### easy_chat.c (20)
EC_DoesEasyChatStringFitOnLine ~ CanPhraseFitInXRowsYCols (easy_chat.c, 95 %)
EC_IsDeoxys ~ IsRestrictedWordSpecies (easy_chat.c, 92 %)
EnableRareWord ~ UnlockTrendySaying (easy_chat.c, 86 %)
GetDisplayedWordByIndex ~ GetUnlockedEasyChatGroupId (easy_chat.c, 80 %)
GetNumUnlockedTrendySayings ~ GetNumTrendySayingsUnlocked (easy_chat.c, 88 %)
GetRandomECPokemon ~ GetRandomUnlockedEasyChatPokemon (easy_chat.c, 93 %)
GetRandomWordFromAnyGroup ~ GetRandomEasyChatWordFromUnlockedGroup (easy_chat.c, 87 %)
GetRandomWordFromGroup ~ GetRandomEasyChatWordFromGroup (easy_chat.c, 93 %)
GetSelectedGroupByIndex ~ GetUnlockedEasyChatGroupId (easy_chat.c, 84 %)
GetUnlockedECWords ~ SetSelectedWordGroup (easy_chat.c, 75 %)
GetUnlockedWordsInAlphabeticalGroup ~ SetSelectedWordGroup_AlphabetMode (easy_chat.c, 85 %)
GetUnlockedWordsInECGroup ~ SetSelectedWordGroup_GroupMode (easy_chat.c, 93 %)
InitEasyChatSelection ~ InitEasyChatScreenWordData (easy_chat.c, 78 %)
IsECGroupUnlocked ~ IsEasyChatGroupUnlocked (easy_chat.c, 89 %)
IsECWordInvalid ~ IsEasyChatWordInvalid (easy_chat.c, 95 %)
IsGroupSelectable ~ IsEasyChatGroupUnlocked2 (easy_chat.c, 88 %)
IsWordUnlocked ~ IsEasyChatWordUnlocked (easy_chat.c, 94 %)
Localize_ConvertEasyChatMessageToString ~ OtherConvertEasyChatWordsToString (easy_chat.c, 99 %)
PopulateAlphabeticalGroups ~ SetUnlockedWordsByAlphabet (easy_chat.c, 83 %)
UnlockedECMonOrMove ~ IsEasyChatIndexAndGroupUnlocked (easy_chat.c, 89 %)

### evolution_graphics.c (20)
CreatePostEvoSparkleSet1 ~ CreateSparkle_CircleInward (evolution_graphics.c, 94 %)
CreatePostEvoSparkleSet2 ~ CreateSparkle_Spray (evolution_graphics.c, 95 %)
CreatePreEvoSparkleSet1 ~ CreateSparkle_SpiralUpward (evolution_graphics.c, 94 %)
CreatePreEvoSparkleSet2 ~ CreateSparkle_ArcDown (evolution_graphics.c, 95 %)
EvoTask_ChooseNextEvoSpriteAnim ~ Task_CycleEvolutionMonSprite_TryEnd (evolution_graphics.c, 95 %)
EvoTask_CreatePostEvoSparklesSet1 ~ Task_Sparkles_CircleInward (evolution_graphics.c, 92 %)
EvoTask_CreatePostEvoSparklesSet2 ~ Task_Sparkles_SprayAndFlash (evolution_graphics.c, 92 %)
EvoTask_CreatePostEvoSparklesSet2Trade ~ Task_Sparkles_SprayAndFlash (evolution_graphics.c, 92 %)
EvoTask_CreatePreEvoSparkleSet1 ~ Task_Sparkles_SpiralUpward (evolution_graphics.c, 89 %)
EvoTask_CreatePreEvoSparklesSet2 ~ Task_Sparkles_ArcDown (evolution_graphics.c, 91 %)
EvoTask_PostEvoSparklesSet1Init ~ Task_Sparkles_CircleInward_Init (evolution_graphics.c, 96 %)
EvoTask_PostEvoSparklesSet2Init ~ Task_Sparkles_SprayAndFlash_Init (evolution_graphics.c, 93 %)
EvoTask_PostEvoSparklesSet2TradeInit ~ Task_Sparkles_SprayAndFlash_Init (evolution_graphics.c, 93 %)
EvoTask_PreEvoSparkleSet1Init ~ Task_Sparkles_SpiralUpward_Init (evolution_graphics.c, 94 %)
EvoTask_PreEvoSparkleSet2Init ~ Task_Sparkles_ArcDown_Init (evolution_graphics.c, 96 %)
EvoTask_PrePostEvoMonSpritesInit ~ Task_CycleEvolutionMonSprite_Init (evolution_graphics.c, 97 %)
EvoTask_ShrinkOrExpandEvoSprites ~ Task_CycleEvolutionMonSprite_UpdateSize (evolution_graphics.c, 87 %)
SpriteCB_PostEvoSparkleSet2 ~ SpriteCB_Sparkle_Spray (evolution_graphics.c, 93 %)
SpriteCB_PreEvoSparkleSet1 ~ SpriteCB_Sparkle_SpiralUpward (evolution_graphics.c, 96 %)
SpriteCB_PreEvoSparkleSet2 ~ SpriteCB_Sparkle_ArcDown (evolution_graphics.c, 97 %)

### party_menu.c (20)
CursorCB_Cancel2 ~ CursorCb_DeoxysForm (party_menu.c, 86 %)
CursorCB_Enter ~ CursorCb_Enter (party_menu.c, 81 %)
CursorCB_FieldMove ~ CursorCb_FieldMove (party_menu.c, 96 %)
CursorCB_Item ~ CursorCb_Item (party_menu.c, 96 %)
CursorCB_Mail ~ CursorCb_Mail (party_menu.c, 96 %)
CursorCB_Store ~ CursorCb_Store (party_menu.c, 80 %)
DisplayPartyPokemonDataForChooseMultiple ~ DisplayPartyPokemonDataForChooseHalf (party_menu.c, 86 %)
InitChooseMonsForBattle ~ InitChooseHalfPartyForBattle (party_menu.c, 85 %)
ItemUseCB_MedicineStep ~ ItemUseCB_Medicine (party_menu.c, 96 %)
ItemUseCB_TryRestorePP ~ ItemUseCB_PPRecovery (party_menu.c, 90 %)
PartyMenuPrintText ~ PrintMessage (party_menu.c, 92 %)
Task_ContinueChoosingMonsForBattle ~ Task_ContinueChoosingHalfParty (party_menu.c, 94 %)
Task_FirstBattleEnterParty_CreatePrinter ~ Task_PartyMenu_Pokedude (party_menu.c, 77 %)
Task_FirstBattleEnterParty_DarkenScreen ~ Task_ClosePartyMenu (party_menu.c, 79 %)
Task_FirstBattleEnterParty_FadeNormal ~ Task_ClosePartyMenu (party_menu.c, 75 %)
Task_FirstBattleEnterParty_LightenFirstMonIcon ~ Task_ClosePartyMenu (party_menu.c, 75 %)
Task_FirstBattleEnterParty_RunPrinterMsg1 ~ Task_PartyMenu_Pokedude (party_menu.c, 77 %)
Task_FirstBattleEnterParty_StartPrintMsg2 ~ Task_PartyMenu_Pokedude (party_menu.c, 85 %)
Task_HandleRestoreWhichMoveInput ~ Task_HandleWhichMoveInput (party_menu.c, 86 %)
TryUsePPItemInBattle ~ TryUsePPItem (party_menu.c, 90 %)

### tileset_anims.c (17)
InitTilesetAnim_CeladonCity ~ InitTilesetAnim_KantoCeladonCity (tileset_anims.c, 92 %)
InitTilesetAnim_CeladonGym ~ InitTilesetAnim_KantoMtEmber (tileset_anims.c, 92 %)
InitTilesetAnim_MtEmber ~ InitTilesetAnim_KantoMtEmber (tileset_anims.c, 92 %)
InitTilesetAnim_SilphCo ~ InitTilesetAnim_KantoSilphCo (tileset_anims.c, 92 %)
InitTilesetAnim_VermilionGym ~ InitTilesetAnim_SootopolisGym (tileset_anims.c, 92 %)
QueueAnimTiles_CeladonCity_Fountain ~ QueueAnimTiles_KantoCeladonCity_Fountain (tileset_anims.c, 93 %)
QueueAnimTiles_CeladonGym_Flowers ~ QueueAnimTiles_KantoCeladonGym_Flowers (tileset_anims.c, 94 %)
QueueAnimTiles_General_SandWatersEdge ~ QueueAnimTiles_KantoGeneral_SandWatersEdge (tileset_anims.c, 93 %)
QueueAnimTiles_General_Water_Current_LandWatersEdge ~ QueueAnimTiles_KantoGeneral_Water_Current_LandWatersEdge (tileset_anims.c, 93 %)
QueueAnimTiles_MtEmber_Steam ~ QueueAnimTiles_KantoMtEmber_Steam (tileset_anims.c, 93 %)
QueueAnimTiles_SilphCo_Fountain ~ QueueAnimTiles_KantoSilphCo_Fountain (tileset_anims.c, 93 %)
QueueAnimTiles_VermilionGym_MotorizedDoor ~ QueueAnimTiles_KantoVermilionGym_MotorizedDoor (tileset_anims.c, 94 %)
TilesetAnim_CeladonCity ~ TilesetAnim_KantoCeladonCity (tileset_anims.c, 94 %)
TilesetAnim_CeladonGym ~ TilesetAnim_Slateport (tileset_anims.c, 94 %)
TilesetAnim_MtEmber ~ TilesetAnim_Slateport (tileset_anims.c, 94 %)
TilesetAnim_SilphCo ~ TilesetAnim_KantoSilphCo (tileset_anims.c, 94 %)
TilesetAnim_VermilionGym ~ TilesetAnim_MauvilleGym (tileset_anims.c, 94 %)

### item_use.c (16)
BattleUseFunc_Ether ~ ItemUseOutOfBattle_ReduceEV (item_use.c, 81 %)
BattleUseFunc_Medicine ~ ItemUseOutOfBattle_ReduceEV (item_use.c, 81 %)
BattleUseFunc_PokeFlute ~ ItemUseOutOfBattle_Mail (item_use.c, 78 %)
FieldUseFunc_Bike ~ ItemUseOutOfBattle_Bike (item_use.c, 77 %)
FieldUseFunc_CoinCase ~ ItemUseOutOfBattle_CoinCase (item_use.c, 79 %)
FieldUseFunc_Ether ~ ItemUseOutOfBattle_ReduceEV (item_use.c, 81 %)
FieldUseFunc_EvoItem ~ ItemUseOutOfBattle_ReduceEV (item_use.c, 81 %)
FieldUseFunc_Mail ~ ItemUseOutOfBattle_Mail (item_use.c, 83 %)
FieldUseFunc_Medicine ~ ItemUseInBattle_Medicine (item_use.c, 90 %)
FieldUseFunc_PokeFlute ~ ItemUseOutOfBattle_PokeFlute (item_use.c, 85 %)
FieldUseFunc_PowderJar ~ ItemUseOutOfBattle_PowderJar (item_use.c, 79 %)
FieldUseFunc_PpUp ~ ItemUseOutOfBattle_PPUp (item_use.c, 90 %)
FieldUseFunc_RareCandy ~ ItemUseOutOfBattle_ReduceEV (item_use.c, 81 %)
FieldUseFunc_Rod ~ ItemUseOutOfBattle_Rod (item_use.c, 94 %)
FieldUseFunc_VsSeeker ~ ItemUseOutOfBattle_VsSeeker (item_use.c, 99 %)
Task_ItemUse_CloseMessageBoxAndReturnToField ~ Task_CloseCantUseKeyItemMessage (item_use.c, 90 %)

### fldeff_flash.c (13)
FlashTransition_Enter ~ DoExitCaveTransition (fldeff_flash.c, 88 %)
FlashTransition_Exit ~ DoExitCaveTransition (fldeff_flash.c, 88 %)
MapTransitionIsEnter ~ GetMapPairFadeToType (fldeff_flash.c, 91 %)
MapTransitionIsExit ~ GetMapPairFadeFromType (fldeff_flash.c, 91 %)
Task_FlashTransition_Enter_0 ~ Task_ExitCaveTransition1 (fldeff_flash.c, 90 %)
Task_FlashTransition_Enter_1 ~ Task_EnterCaveTransition2 (fldeff_flash.c, 92 %)
Task_FlashTransition_Enter_2 ~ Task_EnterCaveTransition3 (fldeff_flash.c, 94 %)
Task_FlashTransition_Enter_3 ~ Task_EnterCaveTransition4 (fldeff_flash.c, 81 %)
Task_FlashTransition_Exit_0 ~ Task_ExitCaveTransition1 (fldeff_flash.c, 90 %)
Task_FlashTransition_Exit_1 ~ Task_ExitCaveTransition2 (fldeff_flash.c, 90 %)
Task_FlashTransition_Exit_2 ~ Task_ExitCaveTransition3 (fldeff_flash.c, 85 %)
Task_FlashTransition_Exit_3 ~ Task_ExitCaveTransition4 (fldeff_flash.c, 86 %)
Task_FlashTransition_Exit_4 ~ Task_ExitCaveTransition5 (fldeff_flash.c, 95 %)

### menu.c (13)
AddItemMenuActionTextPrinters ~ PrintMenuActionTexts (menu.c, 98 %)
Menu_InitCursor ~ InitMenuNormal (menu.c, 90 %)
Menu_InitCursorInternal ~ InitMenu (menu.c, 98 %)
Menu_ProcessInputGridLayout ~ Menu_ProcessGridInput (menu.c, 97 %)
Menu_ProcessInputNoWrapAround ~ Menu_ProcessInputNoWrap (menu.c, 98 %)
Menu_ProcessInput_other ~ ProcessMenuInput_other (menu.c, 94 %)
Menu_RedrawCursor ~ RedrawMenuCursor (menu.c, 97 %)
MultichoiceGrid_InitCursor ~ InitMenuGridDefaultCursorHeight (menu.c, 79 %)
MultichoiceGrid_InitCursorInternal ~ InitMenuGrid (menu.c, 95 %)
MultichoiceGrid_MoveCursor ~ ChangeMenuGridCursorPosition (menu.c, 98 %)
MultichoiceGrid_MoveCursorIfValid ~ ChangeGridMenuCursorPosition (menu.c, 96 %)
MultichoiceGrid_RedrawCursor ~ MoveMenuGridCursor (menu.c, 99 %)
MultichoiceList_PrintItems ~ PrintMenuActionTextsWithSpacing (menu.c, 96 %)

### overworld.c (12)
CB2_LoadMapForQLPlayback ~ CB2_LoadMap2 (overworld.c, 95 %)
CB2_SetUpOverworldForQLPlaybackWithWarpExit ~ CB2_LoadMap (overworld.c, 90 %)
CreateConfirmLeaveTradeRoomPrompt ~ RunConfirmLeaveCableClubScript (overworld.c, 93 %)
DoLoadMap_QLPlayback ~ DoMapLoadLoop (overworld.c, 83 %)
FieldCB_ShowMapNameOnContinue ~ FieldCB_FadeTryShowMapPopup (overworld.c, 80 %)
InitOverworldBgs_NoResetHeap ~ InitOverworldBgs (overworld.c, 82 %)
LoadMap_QLPlayback ~ LoadMapInStepsLink (overworld.c, 80 %)
Overworld_ResetStateOnContinue ~ UpdateMiscOverworldStates (overworld.c, 89 %)
Overworld_TryMapConnectionMusicTransition ~ TransitionMapMusic (overworld.c, 85 %)
ReloadObjectsAndRunReturnToFieldMapScript ~ InitObjectEventsReturnToField (overworld.c, 86 %)
SetInitialPlayerAvatarStateWithDirection ~ ResetInitialPlayerAvatarState (overworld.c, 76 %)
SetUpScrollSceneForCredits ~ Overworld_DoScrollSceneForCredits (overworld.c, 98 %)

### metatile_behavior.c (11)
MetatileBehavior_IsDeepWaterTerrain ~ MetatileBehavior_IsPokeGrass (metatile_behavior.c, 76 %)
MetatileBehavior_IsFastWater ~ MetatileBehavior_IsJumpEast (metatile_behavior.c, 93 %)
MetatileBehavior_IsImpressiveMachine ~ MetatileBehavior_IsJumpEast (metatile_behavior.c, 93 %)
MetatileBehavior_IsPlayerFacingBattleRecords ~ MetatileBehavior_IsPlayerFacingPokemonCenterSign (metatile_behavior.c, 96 %)
MetatileBehavior_IsPlayerFacingCableClubWirelessMonitor ~ MetatileBehavior_IsPlayerFacingPokemonCenterSign (metatile_behavior.c, 96 %)
MetatileBehavior_IsSandOrShallowFlowingWater ~ MetatileBehavior_IsSandOrDeepSand (metatile_behavior.c, 95 %)
MetatileBehavior_IsSnacks ~ MetatileBehavior_IsJumpEast (metatile_behavior.c, 93 %)
MetatileBehavior_IsSurfable ~ MetatileBehavior_IsEncounterTile (metatile_behavior.c, 84 %)
MetatileBehavior_IsVideoGame ~ MetatileBehavior_IsJumpEast (metatile_behavior.c, 93 %)
MetatileBehavior_IsWarpDoor_2 ~ MetatileBehavior_IsJumpEast (metatile_behavior.c, 93 %)
TestMetatileAttributeBit ~ MetatileBehavior_IsEncounterTile (metatile_behavior.c, 84 %)

### trainer_see.c (9)
FldEff_ExclamationMarkIcon1 ~ FldEff_DoubleExclMarkIcon (trainer_see.c, 84 %)
Task_RevealTrainer_RunTrainerSeeFuncList ~ Task_SetBuriedTrainerMovement (trainer_see.c, 81 %)
TrainerSeeFunc_BeginJumpOutOfAsh ~ PopOutOfAshBuriedTrainer (trainer_see.c, 98 %)
TrainerSeeFunc_EndJumpOutOfAsh ~ WaitRevealBuriedTrainer (trainer_see.c, 91 %)
TrainerSeeFunc_OffscreenAboveTrainerCameraObjMoveDown ~ OffscreenAboveTrainerCameraObjMoveDown (trainer_see.c, 96 %)
TrainerSeeFunc_OffscreenAboveTrainerCameraObjMoveUp ~ OffscreenAboveTrainerCameraObjMoveUp (trainer_see.c, 96 %)
TrainerSeeFunc_OffscreenAboveTrainerCreateCameraObj ~ OffscreenAboveTrainerCreateCameraObj (trainer_see.c, 93 %)
TrainerSeeFunc_PrepareToEngage ~ PlayerFaceApproachingTrainer (trainer_see.c, 89 %)
TrainerSeeFunc_StartExclMark ~ TrainerExclamationMark (trainer_see.c, 87 %)

### battle_main.c (8)
LinkBattleComputeBattleTypeFlags ~ FindLinkBattleMaster (battle_main.c, 98 %)
PrepareOwnMultiPartnerBuffer ~ SetMultiPartnerMenuParty (battle_main.c, 77 %)
SpriteCB_PlayerThrowInit ~ SpriteCB_TrainerThrowObject (battle_main.c, 93 %)
SpriteCB_PlayerThrowUpdate ~ SpriteCB_TrainerThrowObject_Main (battle_main.c, 95 %)
SpriteCB_UnusedDebugSprite ~ SpriteCB_UnusedBattleInit (battle_main.c, 94 %)
SpriteCB_UnusedDebugSprite_Step ~ SpriteCB_UnusedBattleInit_Main (battle_main.c, 80 %)
UpdatePartyOwnerOnSwitch_NonMulti ~ SwitchPartyOrder (battle_main.c, 90 %)
UpdatePlayerPosInThrowAnim ~ AnimSetCenterToCornerVecX (battle_main.c, 96 %)

### field_weather.c (8)
ApplyDroughtGammaShiftWithBlend ~ ApplyDroughtColorMapWithBlend (field_weather.c, 81 %)
ApplyGammaShiftWithBlend ~ ApplyColorMapWithBlend (field_weather.c, 91 %)
ApplyWeatherGammaShiftToPal ~ ApplyWeatherColorMapToPal (field_weather.c, 85 %)
FadeSelectedPals ~ FadeScreen (field_weather.c, 97 %)
SetDroughtGamma ~ SetDroughtColorMap (field_weather.c, 80 %)
UpdateWeatherGammaShift ~ UpdateWeatherColorMap (field_weather.c, 82 %)
WeatherBeginGammaFade ~ ApplyWeatherColorMapIfIdle_Gradual (field_weather.c, 83 %)
WeatherShiftGammaIfPalStateIdle ~ ApplyWeatherColorMapIfIdle (field_weather.c, 86 %)

### item.c (8)
BagGetQuantityByItemId ~ CountTotalItemQuantityInBag (item.c, 86 %)
BagPocketCompaction ~ CompactItemsInBagPocket (item.c, 86 %)
BagPocketGetFirstEmptySlot ~ IsBagPocketNonEmpty (item.c, 81 %)
ClearPCItemSlots ~ ClearItemSlots (item.c, 84 %)
CountItemsInPC ~ CountUsedPCItemSlots (item.c, 93 %)
ItemPcCompaction ~ CompactPCItems (item.c, 92 %)
SetBagPocketsPointers ~ SetBagItemsPointers (item.c, 75 %)
SortAndCompactBagPocket ~ SortBerriesOrTMHMs (item.c, 84 %)

### pokemon_storage_system_misc.c (8)
Item_FromMonToMoving ~ TakeItemFromMon (pokemon_storage_system.c, 65 %)
Item_GiveMovingToMon ~ GiveItemToMon (pokemon_storage_system.c, 73 %)
Item_TakeMons ~ MoveItemFromMonToBag (pokemon_storage_system.c, 81 %)
MultiMove_Function_ChangeSelection ~ MultiMove_ChangeSelection (pokemon_storage_system.c, 82 %)
MultiMove_Function_GrabSelection ~ MultiMove_GrabSelection (pokemon_storage_system.c, 66 %)
MultiMove_Function_MoveMons ~ MultiMove_MoveMons (pokemon_storage_system.c, 60 %)
MultiMove_Function_PlaceMons ~ MultiMove_PlaceMons (pokemon_storage_system.c, 83 %)
MultiMove_Function_Start ~ MultiMove_Start (pokemon_storage_system.c, 78 %)

### battle_tower.c (7)
BufferEReaderTrainerGreeting ~ CopyEReaderTrainerGreeting (battle_tower.c, 85 %)
CopyEReaderTrainerName5 ~ GetEreaderTrainerName (battle_tower.c, 93 %)
PrintEReaderTrainerFarewellMessage ~ CopyEReaderTrainerFarewellMessage (battle_tower.c, 91 %)
SetBattleTowerParty ~ GetEreaderTrainerName (battle_tower.c, 76 %)
SetBattleTowerRecordChecksum ~ CalcEmeraldBattleTowerChecksum (battle_tower.c, 88 %)
SetPlayerBattleTowerRecord ~ SaveBattleTowerRecord (battle_tower.c, 79 %)
Task_WaitBT ~ Task_StartBattleAfterTransition (battle_tower.c, 90 %)

### main_menu.c (7)
LoadUserFrameToBg ~ LoadMainMenuWindowFrameTiles (main_menu.c, 82 %)
MainMenuGpuInit ~ InitMainMenu (main_menu.c, 75 %)
MainMenu_DrawWindow ~ DrawMainMenuWindowBorder (main_menu.c, 77 %)
MainMenu_EraseWindow ~ ClearMainMenuWindowTilemap (main_menu.c, 85 %)
PrintContinueStats ~ CB2_MainMenu (main_menu.c, 77 %)
Task_MysteryGiftError ~ Task_DisplayMainMenuInvalidActionError (main_menu.c, 84 %)
Task_UpdateVisualSelection ~ Task_HighlightSelectedMainMenuItem (main_menu.c, 82 %)

### battle_transition.c (6)
Task_Agatha ~ Task_Sidney (battle_transition.c, 94 %)
Task_Blue ~ Task_Sidney (battle_transition.c, 94 %)
Task_Bruno ~ Task_Sidney (battle_transition.c, 94 %)
Task_Lance ~ Task_Sidney (battle_transition.c, 94 %)
Task_Lorelei ~ Task_Sidney (battle_transition.c, 94 %)
Task_Spiral ~ Task_BattleTransition (battle_transition.c, 96 %)

### easy_chat_3.c (6)
CreatePhraseFrameWindow ~ AddPhraseWindow (easy_chat.c, 90 %)
DrawECFrameInTilemapBuffer ~ BufferFrameTilemap (easy_chat.c, 80 %)
EC_AddTextPrinterParameterized2 ~ PrintEasyChatTextWithColors (easy_chat.c, 60 %)
LoadEasyChatPals ~ LoadEasyChatPalettes (easy_chat.c, 90 %)
PrintECGroupsMenu ~ PrintKeyboardGroupNames (easy_chat.c, 64 %)
RedrawFrameByRect ~ BufferLowerWindowFrame (easy_chat.c, 65 %)

### fldeff_rocksmash.c (6)
CreateFieldEffectShowMon ~ CreateFieldMoveTask (fldeff_rocksmash.c, 95 %)
FieldCallback_UseRockSmash ~ FieldCallback_RockSmash (fldeff_rocksmash.c, 93 %)
Task_FieldEffectShowMon_Cleanup ~ Task_DoFieldMove_RunFunc (fldeff_rocksmash.c, 78 %)
Task_FieldEffectShowMon_Init ~ Task_DoFieldMove_Init (fldeff_rocksmash.c, 91 %)
Task_FieldEffectShowMon_WaitFldeff ~ Task_DoFieldMove_WaitForMon (fldeff_rocksmash.c, 99 %)
Task_FieldEffectShowMon_WaitPlayerAnim ~ Task_DoFieldMove_ShowMonAfterPose (fldeff_rocksmash.c, 97 %)

### script_menu.c (6)
DestroyScriptMenuWindow ~ ClearToTransparentAndRemoveWindow (script_menu.c, 84 %)
Hask_MultichoiceGridMenu_HandleInput ~ Task_HandleMultichoiceGridInput (script_menu.c, 92 %)
PicboxWait ~ IsPicboxClosed (script_menu.c, 94 %)
Task_MultichoiceMenu_HandleInput ~ Task_HandleMultichoiceInput (script_menu.c, 75 %)
Task_ScriptShowMonPic ~ Task_PokemonPicWindow (script_menu.c, 99 %)
Task_YesNoMenu_HandleInput ~ Task_HandleYesNoInput (script_menu.c, 88 %)

### trainer_card.c (6)
BufferTextForCardBack ~ BufferTextsVarsForCardPage2 (trainer_card.c, 81 %)
GetCardType ~ GetSetCardType (trainer_card.c, 63 %)
GetTrainerStarCount ~ GetRubyTrainerStars (trainer_card.c, 86 %)
HandleGpuRegs ~ InitGpuRegs (trainer_card.c, 81 %)
ResetBgRegs ~ ClearVramOamPlttRegs (battle_records.c, 93 %)
VBlankCB_TrainerCard ~ VblankCb_TrainerCard (trainer_card.c, 97 %)

### battle_anim_mons.c (5)
InitBattleAnimBg ~ ClearBattleAnimBg (battle_anim_mons.c, 87 %)
PlayerThrowBall_AnimTranslateLinear_WithFollowup ~ AnimTranslateLinear_WithFollowup_SetCornerVecX (battle_anim_mons.c, 94 %)
PlayerThrowBall_StartAnimLinearTranslation ~ StartAnimLinearTranslation (battle_anim_mons.c, 97 %)
SetGreyscaleOrOriginalPalette ~ SetGrayscaleOrOriginalPalette (battle_anim_mons.c, 94 %)
ToggleBg3Mode ~ UpdateAnimBg3ScreenSize (battle_anim_mons.c, 95 %)

### battle_interface.c (5)
DrawHealthbarOntoScreen ~ Debug_TestHealthBar_Helper (battle_interface.c, 76 %)
GetReceivedValueInPixels ~ GetScaledExpFraction (battle_interface.c, 95 %)
SpriteCB_PartySummaryBall_Exit ~ SpriteCB_StatusSummaryBalls_Exit (battle_interface.c, 87 %)
SpriteCB_PartySummaryBall_OnBattleStart ~ SpriteCB_StatusSummaryBalls_Enter (battle_interface.c, 86 %)
SpriteCB_PartySummaryBall_OnSwitchout ~ SpriteCB_StatusSummaryBalls_OnSwitchout (battle_interface.c, 91 %)

### daycare.c (5)
CB2_EggHatch_0 ~ CB2_LoadEggHatch (egg_hatch.c, 76 %)
CB2_EggHatch_1 ~ CB2_EggHatch (egg_hatch.c, 60 %)
CreatedHatchedMon ~ CreateHatchedMon (egg_hatch.c, 94 %)
DayCare_GetBoxMonNickname ~ GetBoxMonNickname (daycare.c, 92 %)
DayCare_GetMonNickname ~ GetMonNickname2 (daycare.c, 92 %)

### field_message_box.c (5)
CreateTask_DrawFieldMessageBox ~ CreateTask_DrawFieldMessage (field_message_box.c, 77 %)
DestroyTask_DrawFieldMessageBox ~ DestroyTask_DrawFieldMessage (field_message_box.c, 90 %)
ExpandStringAndStartDrawFieldMessageBox ~ ExpandStringAndStartDrawFieldMessage (field_message_box.c, 88 %)
StartDrawFieldMessageBox ~ StartDrawFieldMessage (field_message_box.c, 90 %)
Task_DrawFieldMessageBox ~ Task_DrawFieldMessage (field_message_box.c, 82 %)

### mail.c (5)
CB2_InitMailView ~ CB2_InitMailRead (mail.c, 93 %)
CB2_RunShowMailCB ~ CB2_MailRead (mail.c, 82 %)
DoInitMailView ~ MailReadBuildGraphics (mail.c, 88 %)
ShowMailCB_WaitButton ~ CB2_ExitOnKeyPress (mail.c, 90 %)
ShowMailCB_WaitFadeIn ~ CB2_WaitForPaletteExitOnKeyPress (mail.c, 76 %)

### pokemon_storage_system_data.c (5)
HandleInput_InBox_GrabbingMultiple ~ InBoxInput_SelectingMultiple (pokemon_storage_system.c, 62 %)
MonPlaceChange_MoveCursorDown ~ MonPlaceChange_CursorDown (pokemon_storage_system.c, 66 %)
MonPlaceChange_MoveCursorUp ~ MonPlaceChange_CursorUp (pokemon_storage_system.c, 66 %)
SetMovedMonData ~ SetMovingMonData (pokemon_storage_system.c, 64 %)
TrySetDisplayMonData ~ TryRefreshDisplayMon (pokemon_storage_system.c, 100 %)

### text_window.c (5)
LoadHelpMessageWindowGfx ~ LoadSignpostWindowGfx (text_window.c, 84 %)
LoadMenuMessageWindowGfx ~ LoadSignpostWindowGfx (text_window.c, 84 %)
LoadUserWindowGfx ~ LoadUserWindowBorderGfx (text_window.c, 93 %)
LoadUserWindowGfx2 ~ LoadUserWindowBorderGfx (text_window.c, 93 %)
LoadUserWindowGfxByFrame ~ LoadWindowGfx (text_window.c, 86 %)

### battle_anim_special.c (4)
SpriteCB_ThrowBall_ArcFlight ~ SpriteCB_Ball_Arc (battle_anim_throw.c, 75 %)
SpriteCB_ThrowBall_BeginBreakOut ~ SpriteCB_Ball_Release_Step (battle_anim_throw.c, 70 %)
SpriteCB_ThrowBall_FinishClick ~ SpriteCB_Ball_FadeOut (battle_anim_throw.c, 68 %)
SpriteCB_ThrowBall_RunBreakOut ~ SpriteCB_Ball_Release_Wait (battle_anim_throw.c, 60 %)

### easy_chat_2.c (4)
DismantleEasyChat ~ ExitEasyChatScreen (easy_chat.c, 75 %)
GetEasyChatConfirmCancelText ~ GetEasyChatConfirmExitText (easy_chat.c, 100 %)
HandleJoypad_SelectField ~ HandleEasyChatInput_Phrase (easy_chat.c, 64 %)
SelectGroupCursorAction ~ MoveKeyboardCursor (easy_chat.c, 60 %)

### field_effect_helpers.c (4)
CreateBobbingEffect ~ UpdateBobbingEffect (field_effect_helpers.c, 83 %)
FldEff_UnusedWaterSurfacing ~ FldEff_WaterSurfacing (field_effect_helpers.c, 95 %)
SynchroniseSurfAnim ~ SynchronizeSurfAnim (field_effect_helpers.c, 78 %)
SynchroniseSurfPosition ~ SynchronizeSurfPosition (field_effect_helpers.c, 87 %)

### new_menu_helpers.c (4)
CopyDecompressedTileDataToVram ~ copy_decompressed_tile_data_to_vram (menu.c, 66 %)
DrawHelpMessageWindowWithText ~ LoadSignpostWindowFrameGfx (menu.c, 75 %)
GetTextSpeedSetting ~ GetPlayerTextSpeedDelay (menu.c, 66 %)
MallocAndDecompress ~ malloc_and_decompress (menu.c, 83 %)

### battle_ai_script_commands.c (3)
Cmd_count_alive_pokemon ~ Cmd_count_usable_party_mons (battle_ai_script_commands.c, 90 %)
Cmd_if_would_go_first ~ Cmd_if_user_goes (battle_ai_script_commands.c, 77 %)
Cmd_if_would_not_go_first ~ Cmd_if_user_goes (battle_ai_script_commands.c, 75 %)

### battle_records.c (3)
IncTrainerCardLossCount ~ IncTrainerCardLosses (battle_records.c, 94 %)
IncTrainerCardWinCount ~ IncTrainerCardWins (battle_records.c, 94 %)
IndexOfOpponentLinkBattleRecord ~ FindLinkBattleRecord (battle_records.c, 91 %)

### battle_script_commands.c (3)
Cmd_callterrainattack ~ Cmd_callenvironmentattack (battle_script_commands.c, 97 %)
Cmd_cureifburnedparalysedorpoisoned ~ Cmd_cureifburnedparalyzedorpoisoned (battle_script_commands.c, 95 %)
Cmd_settypetoterrain ~ Cmd_settypetoenvironment (battle_script_commands.c, 83 %)

### battle_setup.c (3)
EndPokedudeBattle ~ CB2_EndFirstBattle (battle_setup.c, 76 %)
StartRoamerBattle ~ BattleSetup_StartRoamerBattle (battle_setup.c, 89 %)
StartScriptedWildBattle ~ StartSouthernIslandBattle (battle_setup.c, 97 %)

### bike.c (3)
BikeTransition_TurnDirection ~ AcroBikeTransition_TurnDirection (bike.c, 92 %)
CanBikeFaceDirectionOnRail ~ CanBikeFaceDirOnMetatile (bike.c, 92 %)
GetBikeTransitionId ~ CheckMovementInputAcroBike (bike.c, 88 %)

### field_camera.c (3)
FieldCameraGetPixelOffsetAtGround ~ GetCameraOffsetWithPan (field_camera.c, 90 %)
coords8_add ~ AddCameraPixelOffset (field_camera.c, 88 %)
tilemap_move_something ~ AddCameraTileOffset (field_camera.c, 94 %)

### field_fadetransition.c (3)
Task_ContinueScript ~ Task_EnableScriptAfterMusicFade (field_screen_effect.c, 85 %)
Task_Teleport2Warp ~ Task_TeleportWarp (field_screen_effect.c, 76 %)
Task_WaitFadeAndCreateStartMenuTask ~ Task_WaitForFadeShowStartMenu (field_screen_effect.c, 100 %)

### field_specials.c (3)
DoDeoxysTriangleInteraction ~ DoDeoxysRockInteraction (field_specials.c, 88 %)
MoveDeoxysObject ~ ChangeDeoxysRockLevel (field_specials.c, 88 %)
Task_WaitDeoxysFieldEffect ~ WaitForDeoxysRockMovement (field_specials.c, 90 %)

### fldeff_cut.c (3)
SpriteCallback_CutGrass_Cleanup ~ CutGrassSpriteCallbackEnd (fldeff_cut.c, 83 %)
SpriteCallback_CutGrass_Init ~ CutGrassSpriteCallback1 (fldeff_cut.c, 97 %)
SpriteCallback_CutGrass_Run ~ CutGrassSpriteCallback2 (fldeff_cut.c, 91 %)

### pokemon_storage_system_graphics.c (3)
DestroyAllIconsInColumn ~ DestroyBoxMonIconsInColumn (pokemon_storage_system.c, 62 %)
SpriteCB_BoxScrollArrow ~ SpriteCB_Arrow (pokemon_storage_system.c, 88 %)
SpriteCB_MovePartySpriteToNextSlot ~ SpriteCB_MovePartyMonToNextSlot (pokemon_storage_system.c, 83 %)

### wild_encounter.c (3)
DoGlobalWildEncounterDiceRoll ~ AllowWildCheckOnNewMetatile (wild_encounter.c, 92 %)
DoWildEncounterRateDiceRoll ~ EncounterOddsCheck (wild_encounter.c, 91 %)
GenerateFishingEncounter ~ GenerateFishingWildMon (wild_encounter.c, 82 %)

### battle_anim_mon_movement.c (2)
AnimTask_ShakeMon2Step ~ AnimTask_ShakeMon2_Step (battle_anim_mon_movement.c, 99 %)
AnimTask_SwayMon_Step ~ AnimTask_SwayMonStep (battle_anim_mon_movement.c, 92 %)

### battle_anim_normal.c (2)
AnimShakeMonOrBattleTerrain_Step ~ AnimShakeMonOrBattlePlatforms_Step (battle_anim_normal.c, 79 %)
AnimShakeMonOrBattleTerrain_UpdateCoordOffsetEnabled ~ AnimShakeMonOrBattlePlatforms_UpdateCoordOffsetEnabled (battle_anim_normal.c, 86 %)

### battle_controller_player.c (2)
PlayerHandleCmd55 ~ PlayerHandleEndLinkBattle (battle_controller_player.c, 100 %)
PlayerHandlePlayFanfare ~ PlayerHandlePlayBGM (battle_controller_player.c, 96 %)

### battle_controllers.c (2)
BtlController_EmitPlayFanfare ~ BtlController_EmitPlaySE (battle_controllers.c, 97 %)
SetUpBattleVars ~ SetUpBattleVarsAndBirchZigzagoon (battle_controllers.c, 72 %)

### item_menu.c (2)
InitOldManBag ~ DoWallyTutorialBagMenu (item_menu.c, 86 %)
Task_Bag_OldManTutorial ~ Task_Bag_TeachyTvTMs (kanto_item_menu.c, 85 %)

### mail_data.c (2)
GiveMailToMon2 ~ GiveMailToMon (mail_data.c, 96 %)
TakeMailFromMon2 ~ TakeMailFromMonAndSave (mail_data.c, 96 %)

### pokemon.c (2)
Battle_PrintStatBoosterEffectMessage ~ UseStatIncreaseItem (pokemon.c, 97 %)
InitMonSpritesGfx_Mode0 ~ InitMonSpritesGfx_FullParty (pokemon.c, 89 %)

### pokemon_icon.c (2)
CreateMonIcon_HandleDeoxys ~ CreateMonIconNoPersonality (pokemon_icon.c, 98 %)
MailSpeciesToIconSpecies ~ GetIconSpeciesNoPersonality (pokemon_icon.c, 94 %)

### script.c (2)
IsQuestLogInputDpad ~ CanWalkAwayToCancelMsgBox (script.c, 93 %)
ValidateRamScript ~ ValidateSavedRamScript (script.c, 97 %)

### script_pokemon_util.c (2)
CB2_ReturnFromChooseBattleTowerParty ~ CB2_ReturnFromChooseHalfParty (script_pokemon_util.c, 89 %)
ReducePlayerPartyToThree ~ ReducePlayerPartyToSelectedMons (script_pokemon_util.c, 82 %)

### text.c (2)
GetGlyphWidth_NormalCopy1 ~ GetGlyphWidth_Small (text.c, 94 %)
GetGlyphWidth_NormalCopy2 ~ GetGlyphWidth_Small (text.c, 89 %)

### battle_anim_effects_2.c (1)
AirCutterProjectile_Step1 ~ AirCutterProjectileStep1 (battle_anim_effects_2.c, 98 %)

### battle_anim_utility_funcs.c (1)
AnimTask_GetBattleTerrain ~ AnimTask_GetBattleEnvironment (battle_anim_utility_funcs.c, 92 %)

### battle_controller_opponent.c (1)
OpponentHandlePlayFanfare ~ LinkOpponentHandlePlayFanfareOrBGM (battle_controller_link_opponent.c, 83 %)

### battle_intro.c (1)
CopyBattlerSpriteToBg ~ DrawBattlerOnBg (battle_intro.c, 87 %)

### battle_util.c (1)
AtkCanceller_UnableToUseMove ~ AtkCanceler_UnableToUseMove (battle_util.c, 97 %)

### clear_save_data_screen.c (1)
SaveClearScreen_GpuInit ~ DiplomaInitScreen (kanto_diploma.c, 65 %)

### event_object_lock.c (1)
Task_WaitPlayerAndTargetNPCStopMoving ~ Task_FreezeSelectedObjectAndPlayer (event_object_lock.c, 93 %)

### field_control_avatar.c (1)
UpdateHappinessStepCounter ~ UpdateFriendshipStepCounter (field_control_avatar.c, 98 %)

### field_screen_effect.c (1)
DoOutwardBarnDoorWipe ~ FadeOutOrbEffect (field_screen_effect.c, 78 %)

### fldeff_strength.c (1)
FieldCB_UseStrength ~ FieldCallback_Strength (fldeff_strength.c, 93 %)

### heal_location.c (1)
GetHealLocationIndexFromMapGroupAndNum ~ GetHealLocationIndexByMap (heal_location.c, 98 %)

### pokemon_storage_system.c (1)
SeekToNextMonInBox ~ StorageSystemGetNextMonIndex (pokemon_storage_system.c, 81 %)

### pokemon_storage_system_menu.c (1)
PrintStringToBufferCopyNow ~ UnusedDrawTextWindow (pokemon_storage_system.c, 64 %)

### pokemon_storage_system_tasks.c (1)
StartDisplayMonMosaic ~ StartDisplayMonMosaicEffect (pokemon_storage_system.c, 62 %)

### save_failed_screen.c (1)
WipeDamagedSectors ~ WipeSectors (save_failed_screen.c, 84 %)

### sprite.c (1)
FreeSpriteTilesIfNotUsingSheet ~ DestroySprite (sprite.c, 79 %)

### title_screen.c (1)
CreateLeafSprite ~ CreateFlameSprite (kanto_title_screen.c, 62 %)


## Équivalente (87) : prouvée : même code sous un autre nom (seuls diffèrent des noms eux-mêmes équivalents)

### event_object_movement.c (19)
CameraObject_0 → CameraObject_Init (event_object_movement.c)
CameraObject_1 → CameraObject_UpdateMove (event_object_movement.c)
CameraObject_2 → CameraObject_UpdateFrozen (event_object_movement.c)
InitNpcForWalkSlower → InitNpcForKantoWalkSlow (event_object_movement.c)
InitNpcForWalkSlowest → InitNpcForKantoWalkSlow (event_object_movement.c)
InitWalkSlower → InitKantoWalkSlow (event_object_movement.c)
InitWalkSlowest → InitKantoWalkSlow (event_object_movement.c)
MovementAction_RunDownSlow_Step0 → MovementAction_PlayerRunDownSlow_Step0 (event_object_movement.c)
MovementAction_RunDownSlow_Step1 → MovementAction_PlayerRunDownSlow_Step1 (event_object_movement.c)
MovementAction_RunLeftSlow_Step0 → MovementAction_PlayerRunLeftSlow_Step0 (event_object_movement.c)
MovementAction_RunLeftSlow_Step1 → MovementAction_PlayerRunDownSlow_Step1 (event_object_movement.c)
MovementAction_RunRightSlow_Step0 → MovementAction_PlayerRunDownSlow_Step0 (event_object_movement.c)
MovementAction_RunRightSlow_Step1 → MovementAction_PlayerRunDownSlow_Step1 (event_object_movement.c)
MovementAction_RunUpSlow_Step0 → MovementAction_PlayerRunUpSlow_Step0 (event_object_movement.c)
MovementAction_RunUpSlow_Step1 → MovementAction_PlayerRunDownSlow_Step1 (event_object_movement.c)
MovementType_WalkInPlaceFast_Step0 → MovementType_JogInPlace_Step0 (event_object_movement.c)
SetWalkSlowerSpriteData → SetKantoWalkSlowSpriteData (event_object_movement.c)
SetWalkSlowestSpriteData → SetKantoWalkSlowSpriteData (event_object_movement.c)
cph_IM_DIFFERENT → CopyablePlayerMovement_JumpInPlace (event_object_movement.c)

### field_effect.c (16)
EscalatorWarpEffect_2 → EscalatorWarpOut_WaitForPlayer (field_effect.c)
EscalatorWarpEffect_3 → EscalatorWarpOut_Up_Ride (field_effect.c)
EscalatorWarpEffect_5 → EscalatorWarpOut_Down_Ride (field_effect.c)
EscalatorWarpInEffect_2 → EscalatorWarpIn_Down_Init (field_effect.c)
EscalatorWarpInEffect_3 → EscalatorWarpIn_Down_Ride (field_effect.c)
EscalatorWarpInEffect_4 → EscalatorWarpIn_Up_Init (field_effect.c)
EscalatorWarpInEffect_5 → EscalatorWarpIn_Up_Ride (field_effect.c)
EscalatorWarpInEffect_6 → EscalatorWarpIn_WaitForMovement (field_effect.c)
FallWarpEffect_3 → FallWarpEffect_StartFall (field_effect.c)
FallWarpEffect_5 → FallWarpEffect_Land (field_effect.c)
FldEff_FlyOut → FldEff_UseFly (field_effect.c)
LavaridgeGymB1FWarpEffect_4 → LavaridgeGymB1FWarpEffect_Rise (field_effect.c)
PokeballGlowEffect_FlashLast → PokeballGlowEffect_Flash2 (field_effect.c)
TeleportInFieldEffectTask2 → TeleportWarpInFieldEffect_SpinEnter (field_effect.c)
UseSurfEffect_1 → SurfFieldEffect_Init (field_effect.c)
waterfall_0_setup → WaterfallFieldEffect_Init (field_effect.c)

### battle_anim_special.c (5)
AnimTask_ShinySparkles_WaitSparkles → Task_ShinyStars_Wait (battle_anim_throw.c)
AnimTask_ThrowBall_WaitAnimObjComplete → AnimTask_ThrowBall_Step (battle_anim_throw.c)
BattleAnimObj_SignalEnd → DestroySpriteAfterOneFrame (battle_anim_throw.c)
SpriteCB_SafariBaitOrRock_ArcFlight → SpriteCB_PokeBlock_Arc (battle_anim_throw.c)
SpriteCB_SafariBaitOrRock_WaitPlayerThrow → SpriteCB_PokeBlock_LiftArm (battle_anim_throw.c)

### easy_chat_3.c (4)
ClearWin2AndCopyToVram → ClearWordSelectWindow (easy_chat.c)
SetGpuRegsForEasyChatInit → InitEasyChatBgs (easy_chat.c)
SpriteCB_BounceCursor → SpriteCB_Cursor (easy_chat.c)
SpriteCB_SelectWordCursorSprite → SpriteCB_WordSelectCursor (easy_chat.c)

### overworld.c (4)
IsUpdateLinkStateCBActive → IsOverworldLinkActive (overworld.c)
LinkPlayerDetectCollision → LinkPlayerGetCollision (overworld.c)
Overworld_LinkRecvQueueLengthMoreThan2 → Overworld_IsRecvQueueAtMax (overworld.c)
ResetAllLinkStates → ResetAllPlayerLinkStates (overworld.c)

### item_use.c (3)
BattleUseFunc_BerryPouch → ItemUseInBattle_BerryPouch (kanto_berry_pouch.c)
FieldCB_FadeInFromBlack → FieldCB_UseItemOnField (item_use.c)
Task_WaitFadeIn_CallItemUseOnFieldCB → Task_CallItemUseOnFieldCallback (item_use.c)

### trainer_see.c (3)
TrainerSeeFunc_WaitExclMark → WaitTrainerExclamationMark (trainer_see.c)
TrainerSeeFunc_WaitJumpOutOfAsh → JumpInPlaceBuriedTrainer (trainer_see.c)
TrainerSeeFunc_WaitRemoveDisguise → WaitRevealDisguisedTrainer (trainer_see.c)

### battle_interface.c (2)
SpriteCB_PartySummaryBar → SpriteCB_StatusSummaryBar_Enter (battle_interface.c)
SpriteCB_PartySummaryBar_Exit → SpriteCB_StatusSummaryBar_Exit (battle_interface.c)

### event_object_lock.c (2)
Task_WaitPlayerStopMoving → Task_FreezePlayer (event_object_lock.c)
walkrun_is_standing_still → IsPlayerStandingStill (event_object_lock.c)

### evolution_graphics.c (2)
EvoTask_WaitForPre1SparklesToGoUp → Task_Sparkles_SpiralUpward_End (evolution_graphics.c)
SpriteCB_PostEvoSparkleSet1 → SpriteCB_Sparkle_CircleInward (evolution_graphics.c)

### field_effect_helpers.c (2)
UpdateAshFieldEffect_Step0 → UpdateAshFieldEffect_Wait (field_effect_helpers.c)
UpdateAshFieldEffect_Step1 → UpdateAshFieldEffect_Show (field_effect_helpers.c)

### load_save.c (2)
LoadSerializedGame → CopyPartyAndObjectsFromSave (load_save.c)
SaveSerializedGame → CopyPartyAndObjectsToSave (load_save.c)

### mail_data.c (2)
ClearMailData → ClearAllMail (mail_data.c)
ClearMailStruct → ClearMail (mail_data.c)

### math_util.c (2)
Q_8_8_inv → MathUtil_Inv16 (math_util.c)
Q_N_S_div → MathUtil_Div16Shift (math_util.c)

### start_menu.c (2)
CB2_WhileSavingAfterLinkBattle → MainCB (clear_save_data_screen.c)
CloseSaveMessageWindow → HideSaveMessageWindow (start_menu.c)

### battle_anim_fight.c (1)
AnimStompFootStep → AnimStompFoot_Step (battle_anim_fight.c)

### battle_bg.c (1)
CB2_unused → CB2_UnusedBattleInit (battle_bg.c)

### battle_controller_oak_old_man.c (1)
OakOldManHandleChooseItem → PokedudeHandleChooseItem (kanto_battle_controller_pokedude.c)

### battle_controller_opponent.c (1)
OpponentHandleCmd55 → OpponentHandleEndLinkBattle (battle_controller_opponent.c)

### battle_controller_safari.c (1)
SafariHandleCmd55 → SafariHandleEndLinkBattle (battle_controller_safari.c)

### battle_main.c (1)
SpriteCB_AllyMon → SpriteCB_BattleSpriteStartSlideLeft (battle_main.c)

### battle_setup.c (1)
StartWildBattle → BattleSetup_StartWildBattle (battle_setup.c)

### field_control_avatar.c (1)
Task_QuestLogPlayback_OpenStartMenu → Task_OpenStartMenuAfterSignpost (field_control_avatar.c)

### field_fadetransition.c (1)
Task_ContinueScriptUnionRoom → Task_WaitForUnionRoomFade (field_screen_effect.c)

### field_player_avatar.c (1)
DoBoulderInit → WaterfallFieldEffect_Init (field_effect.c)

### fldeff_cut.c (1)
FieldMoveCallback_CutGrass → StartCutGrassFieldEffect (fldeff_cut.c)

### intro.c (1)
CB2_WaitFadeBeforeSetUpIntro → KantoIntro_Start (kanto_intro.c)

### mailbox_pc.c (1)
MoveCursorFunc → MailboxMenu_MoveCursorFunc (menu_specialized.c)

### naming_screen.c (1)
DecompressToBgTilemapBuffer → DrawBgTilemap (naming_screen.c)

### option_menu.c (1)
OptionMenu_ResetSpriteData → DiplomaReset (kanto_diploma.c)

### pokemon.c (1)
GetSecretBaseTrainerNameIndex → GetSecretBaseTrainerClass (pokemon.c)

### pokemon_storage_system_graphics.c (1)
GetMonIconPriorityByCursorArea → GetMonIconPriorityByCursorPos (pokemon_storage_system.c)


## Triviale (120) : corps vide ou d'une instruction (« return TRUE; ») : se porte avec son appelant

### battle_controller_oak_old_man.c (30)
OakOldManDummy, OakOldManHandleGetRawMonData, OakOldManHandleSetRawMonData, OakOldManHandleLoadMonSprite,
OakOldManHandleSwitchInAnim, OakOldManHandleTrainerSlideBack, OakOldManHandlePaletteFade, OakOldManHandlePause,
OakOldManHandleUnknownYesNoBox, OakOldManHandleCmd23, OakOldManHandleStatusIconUpdate,
OakOldManHandleStatusAnimation, OakOldManHandleStatusXor, OakOldManHandleDataTransfer,
OakOldManHandleDMA3Transfer, OakOldManHandlePlayBGM, OakOldManHandleCmd32, OakOldManHandleTwoReturnValues,
OakOldManHandleChosenMonReturnValue, OakOldManHandleOneReturnValue, OakOldManHandleOneReturnValue_Duplicate,
OakOldManHandleCmd37, OakOldManHandleCmd38, OakOldManHandleCmd39, OakOldManHandleCmd40, OakOldManHandleCmd42,
OakOldManHandleHidePartyStatusSummary, OakOldManHandleSpriteInvisibility,
OakOldManHandleResetActionMoveSelection, OakOldManCmdEnd

### battle_ai_script_commands.c (10)
Cmd_nullsub_2A, Cmd_nullsub_2B, Cmd_nullsub_32, Cmd_nullsub_33, Cmd_nullsub_52, Cmd_nullsub_53, Cmd_nullsub_54,
Cmd_nullsub_55, Cmd_nullsub_56, Cmd_nullsub_57

### battle_controller_safari.c (6)
SafariHandleUnknownYesNoBox, SafariHandleCmd37, SafariHandleCmd38, SafariHandleCmd39, SafariHandleCmd40,
SafariHandleCmd42

### easy_chat_2.c (6)
GetStateBackup, GetEasyChatWordBuffer, IsEasyChatAlphaMode, GetECSelectGroupRowsAbove,
GetECSelectWordRowsAbove, GetECSelectWordNumRows

### overworld.c (6)
Overworld_SetWhiteoutRespawnPoint, Overworld_GetFlashLevel, Overworld_SetWarpDestinationFromWarp,
ClearFieldCallback, MoveSaveBlocks_ResetHeap_, KeyInterCB_SendNothing_2

### field_player_avatar.c (5)
GetPlayerAvatarObjectId, StartPlayerAvatarFishAnim, WaitTeleportWarpOutPlayerAnim,
SavePlayerFacingDirectionForTeleport, WaitTeleportInPlayerAnim

### script.c (5)
SetQuestLogInputIsDpadFlag, ClearQuestLogInputIsDpadFlag, RegisterQuestLogInput, ClearQuestLogInput,
GetRegisteredQuestLogInput

### evolution_graphics.c (4)
SpriteCallbackDummy_EvoSparkles, EvoTask_PreEvoSparkleSet2Teardown, EvoTask_PostEvoSparklesSet1Teardown,
SpriteCallbackDummy_MonSprites

### pokemon_storage_system_data.c (4)
MonPlaceChange_DoMoveCursorDown, MonPlaceChange_DoMoveCursorUp, DoTrySetDisplayMonData, GetBoxCursorPosition

### battle_controller_opponent.c (3)
OpponentHandleBallThrowAnim, OpponentHandleUnknownYesNoBox, OpponentHandleCmd42

### battle_message.c (3)
Localize_TrainerClass_SchoolKid, Localize_TrainerClass_PkmnTrainer, Localize_TrainerClass_Leader

### easy_chat.c (3)
EC_IsNationalPokedexEnabled, GetNumDisplayableGroups, GetNumDisplayedWords

### start_menu.c (3)
CloseSaveStatsWindow_, SetSaveDialogDelayTo60Frames, VBlankCB_WhileSavingAfterLinkBattle

### battle_controller_player.c (2)
PlayerHandleUnknownYesNoBox, PlayerHandleCmd42

### event_object_movement.c (2)
MovementAction_ShakeHeadOrWalkInPlace_Step1, MovementAction_FlyUp_Step2

### item_use.c (2)
SetFieldCallback2ForItemUse, DoSetUpItemUseCallback

### main.c (2)
SetVBlankCounter1Ptr, DisableVBlankCounter1

### new_menu_helpers.c (2)
GetStdWindowBaseTileNum, DestroyHelpMessageWindow_

### shop.c (2)
DebugFunc_PrintPurchaseDetails, DebugFunc_PrintShopMenuHistoryBeforeClearMaybe

### battle_interface.c (1)
GetBattleInterfaceGfxPtr

### battle_tower.c (1)
BattleTower_SoftReset

### bike.c (1)
BikeTransition_FaceDirection

### easy_chat_3.c (1)
GetBg2ScrollRow

### field_camera.c (1)
move_tilemap_camera_to_upper_left_corner

### field_fadetransition.c (1)
WaitWarpFadeOutScreen

### field_message_box.c (1)
GetFieldMessageBoxType

### field_weather_util.c (1)
GetSav1Weather

### mailbox_pc.c (1)
MailboxPC_DestroyListMenuBuffer

### option_menu.c (1)
OptionMenu_SetVBlankCallback

### party_menu.c (1)
CursorCB_Trade2

### player_pc.c (1)
Task_DeclinedMoveMailToBag

### pokemon_icon.c (1)
DestroyMonIcon

### pokemon_storage_system_misc.c (1)
GetMovingItem

### pokemon_storage_system_tasks.c (1)
LoadsMiscSpritePalette

### save_failed_screen.c (1)
SetNotInSaveFailedScreen

### trainer_card.c (1)
TrainerCardNull

### trainer_see.c (1)
TrainerSeeFunc_Dummy

### window.c (1)
nullsub_8

### window_8bpp.c (1)
nullsub_9


## Morte (70) : jamais appelée ni référencée dans RF

### field_player_avatar.c (7)
PlayerWalkSlower, PlayerGlide, PlayerFaceDirectionFast, PlayerShakeHeadOrWalkInPlace, PlayerAcroWheelieCollide,
PlayerAcroPopWheelie, PlayerAcroWheelieMove

### metatile_behavior.c (6)
MetatileBehavior_IsArrowWarp, MetatileBehavior_IsUnused01, MetatileBehavior_IsUnusedWater,
MetatileBehavior_IsWater, MetatileBehavior_IsCyclingRoadPullDownTileGrass, MetatileBehavior_IsStrengthButton

### text_window.c (5)
LoadHelpMessageWindowGfxOnBg, LoadMenuMessageWindowGfxOnBg, LoadSignpostWindowGfxOnBg,
LoadQuestLogWindowTilesOnBg, LoadUserWindowGfxByFrameOnBg

### event_object_movement.c (4)
GetReflectionEffectPaletteSlot, CameraObjectGetFollowedObjectId, GetAcroBunnyHopFrontWheelDirectionAnimNum,
GetWalkSlowestMovementAction

### field_special_scene.c (4)
FieldSpecialScene_Dummy0, FieldSpecialScene_Dummy1, FieldSpecialScene_Dummy2, FieldSpecialScene_Dummy3

### battle_interface.c (3)
UpdateAndDrawHealthbarOntoScreen, CalcNewHealthbarValue, DoDrawHealthbarOntoScreen

### math_util.c (3)
Q_8_8_div, Q_N_S_inv, Q_24_8_inv

### menu.c (3)
Unused_ClearTopBarWindow, CreateYesNoMenu2, MultichoiceGrid_PrintItemsCustomOrder

### trainer_card.c (3)
Unref_InitTrainerCard, Unref_InitTrainerCardLink, Unref_InitTrainerCardLink2

### battle_bg.c (2)
CreateUnknownDebugSprite, GetBattleTerrainGfxPtrs

### battle_setup.c (2)
StartPokedudeBattle, SetBattledTrainerFlag2

### battle_tower.c (2)
UpdateOrInsertReceivedBattleTowerRecord, Debug_FillEReaderTrainerWithPlayerData

### cable_car_util.c (2)
CableCarUtil_FillWrapped, CableCarUtil_CopyWrapped

### event_data.c (2)
DisableNationalPokedex_RSE, IsNationalPokedexEnabled_RSE

### new_menu_helpers.c (2)
GetStdMenuPalette, GetDlgWindowBaseTileNum

### battle_anim_special.c (1)
AnimTask_LevelUpHealthBox

### battle_controller_safari.c (1)
SafariDummy

### battle_controllers.c (1)
BtlController_EmitUnknownYesNoBox

### battle_gfx_sfx_util.c (1)
DoBattleSpriteAffineAnim

### coins.c (1)
ShowCoinsWindow_Parameterized

### field_control_avatar.c (1)
Unref_ClearHappinessStepCounter

### field_fadetransition.c (1)
WarpFadeOutScreenWithDelay

### field_screen_effect.c (1)
DoInwardBarnDoorFade

### field_weather.c (1)
IsWeatherFadingIn

### fldeff_sweetscent.c (1)
Unused_StartSweetscentFldeff

### heal_location.c (1)
GetHealLocationPointerFromMapGroupAndNum

### item.c (1)
IsPocketNotEmpty

### item_use.c (1)
BattleUseFunc_SacredAsh

### mailbox_pc.c (1)
MailboxPC_GetWindowId

### main_menu.c (1)
CB2_InitMainMenu_2

### map_name_popup.c (1)
IsMapNamePopupTaskActive

### naming_screen.c (1)
Debug_NamingScreenRival

### pokemon_storage_system.c (1)
RestorePokemonStorage

### start_menu.c (1)
SetHasPokedexAndPokemon

### text_printer.c (1)
CopyGlyphToWindow_Parameterized


## Link (139) : link / E-Reader : à porter, désactivé

### union_room_chat_display.c (49)
UnionRoomChat_TryAllocGraphicsWork, UnionRoomChat_RunDisplaySubtask0, UnionRoomChat_FreeGraphicsWork, InitWork,
UnionRoomChat_ResetDisplaySubtasks, UnionRoomChat_RunDisplaySubtasks, UnionRoomChat_StartDisplaySubtask,
RunDisplaySubtask, DisplaySubtask_LoadGfx, DisplaySubtask_PrintWin3, DisplaySubtask_HideWin3,
DisplaySubtask_SwitchPages, DisplaySubtask_MoveSelectorCursorObj, DisplaySubtask_ShowQuitChattingDialog,
DisplaySubtask_UpdateMessageBuffer, DisplaySubtask_PrintRegisterWhere, DisplaySubtask_CancelRegister,
DisplaySubtask_ReturnToKeyboard, DisplaySubtask_ScrollChat, DisplaySubtask_AnimateSelectorCursorBlink,
DisplaySubtask_PrintInputText, DisplaySubtask_PrintExitingChat, DisplaySubtask_PrintLeaderLeft,
DisplaySubtask_AskSave, DisplaySubtask_AskOverwriteSave, DisplaySubtask_PrintSavingDontTurnOffPower,
DisplaySubtask_PrintSavedTheGame, DisplaySubtask_ShowConfirmLeaderLeaveDialog, DisplaySubtaskDummy,
PlaceYesNoMenuAt, UnionRoomChat_ProcessInput, PlaceStdMessageWindow, FillWin1Rect, PrintOnWin1Parameterized,
AnimateMoveBg1Right, AnimateMoveBg1Left, PrintKeyboardSwapTextsOnWin3, ClearWin3, PrintTextOnWin0Colorized,
SetBgTilemapWorkBuffers, LoadUnionRoomChatPanelGfx, LoadLinkMiscMenuGfx, LoadBg1Pal8, LoadWin0, LoadWin2,
LoadWin1, LoadWin3, FillScanlineEffectWithValue1col, FillScanlineEffectWithValue2col

### union_room_chat.c (34)
InitChatWork, FreeChatWork, ChatEntryRoutine_Join, ChatEntryRoutine_HandleInput, ChatEntryRoutine_Switch,
ChatEntryRoutine_AskQuitChatting, ChatEntryRoutine_ExitChat, ChatEntryRoutine_Drop, ChatEntryRoutine_Disbanded,
ChatEntryRoutine_SendMessage, ChatEntryRoutine_Register, ChatEntryRoutine_SaveAndExit, GoToRoutine,
TypeChatMessage_HandleDPad, AppendCharacterToChatMessageBuffer, DeleteLastCharacterOfChatMessageBuffer,
ToggleCaseOfLastCharacterInChatMessageBuffer, ChatMsgHasAtLeastOneCharcter, SaveRegisteredTextsToSB1,
UnionRoomChat_GetWorkRegisteredText, GetEndOfUnk1A, GetPtrToLastCharOfUnk1A, GetNumCharsInMessageEntryBuffer,
UnionRoomChat_GetCursorColAndRow, UnionRoomChat_GetMessageEntryBuffer, UnionRoomChat_LenMessageEntryBuffer,
UnionRoomChat_GetBufferSelectionRegion, UnionRoomChat_GetEndOfMessageEntryBuffer,
UnionRoomChat_GetNumCharsInMessageEntryBuffer, UnionRoomChat_GetLastReceivedMessage,
UnionRoomChat_GetReceivedPlayerIndex, UnionRoomChat_GetMessageEntryCursorPosition,
UnionRoomChat_GetWhetherShouldShowCaseToggleIcon, UnionRoomChat_GetNameOfPlayerWhoDisbandedChat

### union_room_chat_objects.c (11)
UnionRoomChat_TryAllocSpriteWork, UnionRoomChat_FreeSpriteWork, UnionRoomChat_CreateSelectorCursorObj,
UnionRoomChat_ToggleSelectorCursorObjVisibility, UnionRoomChat_MoveSelectorCursorObj,
UnionRoomChat_UpdateObjPalCycle, UnionRoomChat_SetSelectorCursorClosedImage,
UnionRoomChat_AnimateSelectorCursorReopen, UnionRoomChat_SpawnTextEntryPointerSprites,
CreatePageSwitchUISprites, UpdateVisibleUnionRoomChatIcon

### cereader_tool.c (6)
ValidateTrainerTowerTrainer, ValidateTrainerTowerData, CEReaderTool_SaveTrainerTower_r,
CEReaderTool_SaveTrainerTower, CEReaderTool_LoadTrainerTower_r, CEReaderTool_LoadTrainerTower

### cable_club.c (5)
AnyConnectedPartnersPlayingRS, CableClub_AskSaveTheGame, EnterTradeSeat, StartWiredCableClubTrade,
GetSeeingLinkPlayerCardMsg

### berry_crush.c (4)
BerryCrush_SetVBlankCallback, BerryCrush_BuildLocalState, printCrushingResults, Task_ShowBerryCrushRankings

### mystery_gift_menu.c (4)
PrintMysteryGiftOrEReaderTopMenu, AddTextPrinterToWindow1, ClearTextWindow, HandleMysteryGiftListMenu

### battle_controller_link_partner.c (3)
LinkPartnerDummy, LinkPartnerHandleUnknownYesNoBox, LinkPartnerHandlePlayFanfare

### link_rfu_2.c (3)
LinkRfu_ForceChangeSpParent, RfuGetErrorInfo, DestroyTask_RfuReconnectWithParent

### trade_scene.c (3)
CheckLinkTimeout, LoadTradeGbaSpriteGfx, TradeBufferOTnameAndNicknames

### union_room_battle.c (3)
SetUpPartiesAndStartBattle, UnionRoomBattle_CreateTextPrinter, UnionRoomBattle_PrintTextOnWindow0

### battle_controller_link_opponent.c (2)
LinkOpponentHandleUnknownYesNoBox, LinkOpponentHandlePlayFanfare

### link_rfu_3.c (2)
ZeroName, NameIsEmpty

### trade.c (2)
CB2_ReturnToTradeMenuFromSummary, CommunicateWhetherMonCanBeTraded

### union_room.c (2)
Leader_DisconnectOnState, ItemPrintFunc_Unused

### berry_fix_program.c (1)
SetScene

### dodrio_berry_picking.c (1)
DBP_LoadStdWindowGfx

### link.c (1)
SetLinkErrorFromRfu

### mystery_event_script.c (1)
MEventScript_Run

### union_room_player_avatar.c (1)
MakeGroupAssemblyAreasPassable

### wireless_communication_status_screen.c (1)
ExitWirelessCommunicationStatusScreen


## Écartée (361) : écartée par décision

### quest_log_events.c (117)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), SetQuestLogEvent,
InQuestLogDisabledLocation, QuestLog_ShouldEndSceneOnMapChange, ShouldRegisterEvent_HandlePartyActions,
ShouldRegisterEvent_HandleBeatStoryTrainer, QL_EnableRecordingSteps, ShouldRegisterEvent, TryDeferLinkEvent,
ResetDeferredLinkEvent, TryDeferTrainerBattleEvent, QuestLogEvents_HandleEndTrainerBattle, QL_RecordWait,
IsEventWithSpecialEncounterSpecies, QL_SkipCommand, QL_UpdateLastDepartedLocation, QL_LoadEvent,
QL_TryRepeatEvent, QL_ResetRepeatEventTracker, UpdateRepeatEventCounter, QL_ResetEventStates,
QL_RecordAction_SceneEnd, QL_LoadAction_SceneEnd, QL_RecordAction_Wait, QL_LoadAction_Wait,
QL_RecordAction_Input, QL_LoadAction_Input, QL_RecordAction_MovementOrGfxChange,
QL_LoadAction_MovementOrGfxChange, RecordEventHeader, LoadEvent, QuestLog_GetSpeciesName,
RecordEvent_SwitchedPartyOrder, LoadEvent_SwitchedPartyOrder, RecordEvent_UsedItem, LoadEvent_UsedItem,
RecordEvent_GiveTakeHeldItem, RecordEvent_GaveHeldItemFromPartyMenu, LoadEvent_GaveHeldItemFromPartyMenu,
RecordEvent_GaveHeldItemFromBagMenu, LoadEvent_GaveHeldItemFromBagMenu, RecordEvent_GaveHeldItemFromPC,
LoadEvent_GaveHeldItemFromPC, RecordEvent_TookHeldItem, LoadEvent_TookHeldItem, RecordEvent_SwappedHeldItem,
RecordEvent_SwappedHeldItemFromBag, LoadEvent_SwappedHeldItem, RecordEvent_SwappedHeldItemFromPC,
LoadEvent_SwappedHeldItemFromPC, RecordEvent_UsedPkmnCenter, LoadEvent_UsedPkmnCenter, RecordEvent_LinkTraded,
LoadEvent_LinkTraded, RecordEvent_LinkBattledSingle, LoadEvent_LinkBattledSingle,
RecordEvent_LinkBattledDouble, LoadEvent_LinkBattledDouble, RecordEvent_LinkBattledMulti,
LoadEvent_LinkBattledMulti, RecordEvent_UsedUnionRoom, LoadEvent_UsedUnionRoom, RecordEvent_UsedUnionRoomChat,
LoadEvent_UsedUnionRoomChat, RecordEvent_LinkTradedUnionRoom, LoadEvent_LinkTradedUnionRoom,
RecordEvent_LinkBattledUnionRoom, LoadEvent_LinkBattledUnionRoom, RecordEvent_SwitchedMonsBetweenBoxes,
LoadEvent_SwitchedMonsBetweenBoxes, RecordEvent_SwitchedMonsWithinBox, LoadEvent_SwitchedMonsWithinBox,
RecordEvent_SwitchedPartyMonForPCMon, LoadEvent_SwitchedPartyMonForPCMon, RecordEvent_MovedMonBetweenBoxes,
LoadEvent_MovedMonBetweenBoxes, RecordEvent_MovedMonWithinBox, LoadEvent_MovedMonWithinBox,
RecordEvent_WithdrewMonFromPC, LoadEvent_WithdrewMonFromPC, RecordEvent_DepositedMonInPC,
LoadEvent_DepositedMonInPC, RecordEvent_SwitchedMultipleMons, LoadEvent_SwitchedMultipleMons,
RecordEvent_DepositedItemInPC, LoadEvent_DepositedItemInPC, RecordEvent_WithdrewItemFromPC,
LoadEvent_WithdrewItemFromPC, RecordEvent_DefeatedTrainer, RecordEvent_DefeatedGymLeader,
LoadEvent_DefeatedGymLeader, RecordEvent_DefeatedWildMon, LoadEvent_DefeatedWildMon,
IsSpeciesFromSpecialEncounter, RecordEvent_DefeatedEliteFourMember, LoadEvent_DefeatedEliteFourMember,
RecordEvent_DefeatedChampion, LoadEvent_DefeatedChampion, RecordEvent_DefeatedNormalTrainer,
LoadEvent_DefeatedTrainer, RecordEvent_DepartedLocation, LoadEvent_DepartedLocation, SetQLPlayedTheSlots,
ShouldRegisterEvent_HandleDeparted, ShouldRegisterEvent_DepartedGameCorner, RecordEvent_UsedFieldMove,
LoadEvent_UsedFieldMove, RecordEvent_BoughtItem, LoadEvent_BoughtItem, RecordEvent_SoldItem,
LoadEvent_SoldItem, RecordEvent_ObtainedStoryItem, LoadEvent_ObtainedStoryItem, QuestLog_RecordEnteredMap,
SetQuestLogEvent_Arrived, RecordEvent_ArrivedInLocation, LoadEvent_ArrivedInLocation,
TranslateLinkPartnersName

### quest_log.c (86)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), QL_AddASLROffset, ResetQuestLog,
ClearSavedScene, QL_ResetDefeatedWildMonRecord, RunQuestLogCB, QL_IsRoomToSaveEvent, QL_IsRoomToSaveAction,
SetQuestLogState, QLogCB_Recording, QLogCB_Playback, GetQuestLogStartType, QL_StartRecordingAction,
SetPlayerInitialCoordsAtScene, SetNPCInitialCoordsAtScene, SetGameStateAtScene, BackUpTrainerRematches,
BackUpMapLayout, RecordSceneEnd, TryRecordActionSequence, TryStartQuestLogPlayback, Task_BeginQuestLogPlayback,
QL_InitSceneObjectsAndActions, FieldCB2_QuestLogStartPlaybackWithWarpExit,
FieldCB2_QuestLogStartPlaybackStandingInPlace, DrawPreviouslyOnQuestHeader, CommitQuestLogWindow1,
QL_LoadObjectsAndTemplates, QLPlayback_SetInitialPlayerPosition, QLPlayback_InitOverworldState,
QL_CopySaveState, QL_ResetPartyAndPC, SetPokemonCounts, QuestLog_GetPartyCount, QuestLog_GetBoxMonCount,
RestoreTrainerRematches, QL_RestoreMapLayoutId, ReadQuestLogScriptFromSav1, DoSceneEndTransition,
QuestLog_AdvancePlayhead, QuestLog_StartFinalScene, QuestLog_AdvancePlayhead_, QL_AvoidDisplay,
Task_AvoidDisplay, QuestLog_PlayCurrentEvent, HandleShowQuestLogMessage, GetQuestLogTextDisplayDuration,
QL_IsTrainerSightDisabled, QL_HandleInput, QuestLogScenePlaybackIsEnding,
QuestLog_DrawPreviouslyOnQuestHeaderIfInPlaybackMode, DrawSceneDescription, CopyDescriptionWindowTiles,
QuestLog_CloseTextWindow, DoSkipToEndTransition, QuestLog_WaitFadeAndCancelPlayback,
QuestLog_InitPalettesBackup, QuestLog_BackUpPalette, FieldCB2_FinalScene, Task_FinalScene_WaitFade,
Task_QuestLogScene_SavedGame, Task_WaitAtEndOfQuestLog, Task_EndQuestLog, RestoreScreenAfterPlayback,
QL_SlightlyDarkenSomePals, QL_FinishRecordingScene, SortQuestLogInSav1, SaveQuestLogData, QL_UpdateObject,
QuestLogRecordNPCStep, QuestLogRecordNPCStepWithDuration, QuestLogRecordPlayerStep,
QuestLogRecordPlayerStepWithDuration, QuestLogRecordPlayerAvatarGfxTransition,
QuestLogRecordPlayerAvatarGfxTransitionWithDuration, QL_RecordFieldInput, TogglePlaybackStateForOverworldLock,
QuestLog_OnEscalatorWarp, ResetActions, QL_TryRunActions, QL_AfterRecordFishActionSuccessful,
QL_GetPlaybackState, RecordHeadAtEndOfEntryOrScriptContext2Enabled, RecordHeadAtEndOfEntry,
QuestLogGetFlagOrVarPtr, QuestLogSetFlagOrVar, QuestLogResetFlagsOrVars

### oak_speech.c (62)
— discours de Chen (la partie commence à Hoenn, décision 2026-11-02), StartNewGameScene, Task_NewGameScene,
ControlsGuide_LoadPage1, Task_ControlsGuide_LoadPage, Task_ControlsGuide_HandleInput,
Task_ControlsGuide_ChangePage, Task_ControlsGuide_Clear, Task_PikachuIntro_LoadPage1,
Task_PikachuIntro_HandleInput, Task_PikachuIntro_Clear, Task_OakSpeech_Init, Task_OakSpeech_WelcomeToTheWorld,
Task_OakSpeech_ThisWorld, Task_OakSpeech_ReleaseNidoranFFromPokeBall, Task_OakSpeech_IsInhabitedFarAndWide,
Task_OakSpeech_IStudyPokemon, Task_OakSpeech_ReturnNidoranFToPokeBall,
Task_OakSpeech_TellMeALittleAboutYourself, Task_OakSpeech_FadeOutOak, Task_OakSpeech_AskPlayerGender,
Task_OakSpeech_ShowGenderOptions, Task_OakSpeech_HandleGenderInput, Task_OakSpeech_ClearGenderWindows,
Task_OakSpeech_LoadPlayerPic, Task_OakSpeech_YourNameWhatIsIt, Task_OakSpeech_FadeOutForPlayerNamingScreen,
Task_OakSpeech_MoveRivalDisplayNameOptions, Task_OakSpeech_RepeatNameQuestion,
Task_OakSpeech_HandleRivalNameInput, Task_OakSpeech_DoNamingScreen, Task_OakSpeech_ConfirmName,
Task_OakSpeech_HandleConfirmNameInput, Task_OakSpeech_FadeOutPlayerPic, Task_OakSpeech_FadeOutRivalPic,
Task_OakSpeech_FadeInRivalPic, Task_OakSpeech_AskRivalsName, Task_OakSpeech_ReshowPlayersPic,
Task_OakSpeech_LetsGo, Task_OakSpeech_FadeOutBGM, Task_OakSpeech_SetUpExitAnimation,
Task_OakSpeech_SetUpShrinkPlayerPic, Task_OakSpeech_ShrinkPlayerPic,
Task_OakSpeech_SetUpDestroyPlatformSprites, Task_OakSpeech_DestroyPlatformSprites,
Task_OakSpeech_SetUpFadePlayerPicWhite, Task_OakSpeech_FadePlayerPicWhite, Task_OakSpeech_FadePlayerPicToBlack,
Task_OakSpeech_WaitForFade, Task_OakSpeech_FreeResources, CB2_ReturnFromNamingScreen, CreateNidoranFSprite,
SpriteCB_Pikachu, CreatePikachuOrPlatformSprites, DestroyPikachuOrPlatformSprites, LoadTrainerPic,
ClearTrainerPic, Task_SlowFadeIn, CreateFadeInTask, Task_SlowFadeOut, CreateFadeOutTask,
PrintNameChoiceOptions, GetDefaultName

### help_system_util.c (39)
— aide L/R de RF (Kanto = post-game, décision 2026-11-02), RunHelpSystemCallback, SaveCallbacks,
SaveMapGPURegs, SaveMapTiles, SaveMapTextColors, RestoreCallbacks, RestoreGPURegs, RestoreMapTiles,
RestoreMapTextColors, CommitTilemap, HS_DrawBgTilemapRect, HS_BufferFillMapWithTile1FF,
HS_ShowOrHideWordHELPinTopLeft, HS_ShowOrHideControlsGuideInTopRight, HS_ShowOrHideMainWindowText,
HS_SetMainWindowBgBrightness, HS_ShowOrHideToplevelTooltipWindow, HS_ShowOrHideHeaderAndFooterLines_Lighter,
HS_ShowOrHideHeaderAndFooterLines_Darker, HS_ShowOrHideVerticalBlackBarsAlongSides,
HS_ShowOrHideHeaderLine_Darker_FooterStyle, HS_ShowOrHideScrollArrows, HelpSystemRenderText,
DecompressAndRenderGlyph, HelpSystem_PrintTextInTopLeftCorner, HelpSystem_PrintTextRightAlign_Row52,
HelpSystem_PrintTextAt, HelpSystem_PrintQuestionAndAnswerPair, HelpSystem_PrintTopicMouseoverDescription,
HelpSystem_FillPanel3, HelpSystem_FillPanel2, HelpSystem_FillPanel1, HelpSystem_InitListMenuController,
HelpSystem_SetInputDelay, HelpSystem_GetMenuInput, HS_UpdateMenuScrollArrows, PrintListMenuItems,
HS_RemoveSelectionCursorAt, TryMoveCursor1

### help_system.c (35)
— aide L/R de RF (Kanto = post-game, décision 2026-11-02), SetHelpContextDontCheckBattle, SetHelpContext,
IsInMartMap, IsInGymMap, IsCurrentMapInArray, IsInDungeonMap, HelpSystem_UpdateHasntSeenIntro,
HelpSystem_IsSinglePlayer, HelpSystem_DisableToggleWithRButton, HelpSystem_EnableToggleWithRButton,
ResetHelpSystemListMenu, BuildAndPrintMainTopicsListMenu, BuildMainTopicsListAndMoveToH00,
BuildAndPrintSubmenuList, SetHelpSystemSubmenuItems, HelpSystem_ShouldShowBasicTerms,
IsHelpSystemSubmenuEnabled, HasGottenAtLeastOneHM, RunHelpMenuSubroutine,
HelpSystemSubroutine_PrintWelcomeMessage, HelpSystemSubroutine_WelcomeWaitButton,
HelpSystemSubroutine_WelcomeEndGotoMenu, HelpSystemSubroutine_MenuInputHandlerMain,
HelpMenuSubroutine_InitSubmenu, HelpMenuSubroutine_ReturnFromSubmenu, HelpMenuSubroutine_SubmenuInputHandler,
HelpSystem_PrintTopicLabel, HelpMenuSubroutine_HelpItemPrint, HelpMenuSubroutine_ReturnFromHelpItem,
HelpMenuSubroutine_HelpItemWaitButton, PrintWelcomeMessageOnPanel1, PrintTextOnPanel2Row52RightAlign,
GetHelpSystemMenuLevel, ResetHelpSystemCursor, PrintHelpSystemTopicMouseoverDescription

### quest_log_player.c (15)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), QuestLogUpdatePlayerSprite,
QuestLogTryRecordPlayerAvatarGfxTransition, QuestLogCallUpdatePlayerSprite, QL_GfxTransition_Normal,
QL_GfxTransition_Bike, QL_GfxTransition_Fish, Task_QLFishMovement, QL_GfxTransition_StartSurf,
QL_GfxTransition_VSSeeker, Task_QLVSSeekerMovement, QL_SetObjectGraphicsId, QL_GfxTransition_StopSurfSouth,
QL_GfxTransition_StopSurfNorth, QL_GfxTransition_StopSurfWest, QL_GfxTransition_StopSurfEast

### quest_log_battle.c (3)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), TrySetQuestLogBattleEvent,
TrySetQuestLogLinkBattleEvent, GetLinkMultiBattlePlayerIndexes

### quest_log_objects.c (3)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), QL_RecordObjects, QL_LoadObjects,
QL_TryStopSurfing

### help_message.c (1)
— aide L/R de RF (Kanto = post-game, décision 2026-11-02), MapNamePopupWindowIdSetDummy
