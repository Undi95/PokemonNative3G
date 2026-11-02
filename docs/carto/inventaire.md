# Inventaire des fonctions de Rouge Feu absentes de la fusion

> Généré par `tools/cartographie.py` — ne pas éditer à la main.

Les 1704 fonctions propres à Rouge Feu absentes de la fusion par leur nom (`fonctions-rf-absentes.md`), chacune dans une seule catégorie. « Équivalente » est une preuve (même suite de jetons ; seuls diffèrent des noms de fonctions déjà prouvées équivalentes, jusqu'au point fixe, ou une variante Kanto du même nom) ; « à vérifier » et « manquante » se lisent à la main, puis se classent dans `tools/carto_classement.txt` avec leur preuve.

| Catégorie | Sens | Fonctions |
|---|---|---|
| manquante | rien de proche dans la fusion : à porter | 264 |
| à vérifier | ressemble à une fonction de la fusion (donnée) sans en être prouvée la même : à lire | 61 |
| équivalente | prouvée : même code sous un autre nom (seuls diffèrent des noms eux-mêmes équivalents) | 564 |
| triviale | corps vide ou d'une instruction (« return TRUE; ») : se porte avec son appelant | 113 |
| morte | jamais appelée ni référencée dans RF | 105 |
| link | link / E-Reader : à porter, désactivé | 170 |
| écartée | écartée par décision | 427 |

## Manquante (264) : rien de proche dans la fusion : à porter

### battle_tower.c (23)
AppendBattleTowerBannedSpeciesName, BattleTowerMapScript2, BattleTowerUtil, BufferBattleTowerTrainerMessage,
CB2_FinishEReaderBattle, CheckMonBattleTowerBanlist, CheckPartyBattleTowerBanlist,
ChooseNextBattleTowerTrainer, DetermineBattleTowerPrize, Dummy_TryEnableBravoTrainerBattleTower,
FillBattleTowerTrainerParty, GetBattleTowerTrainerClassNameId, GetBattleTowerTrainerFrontSpriteId,
GetBattleTowerTrainerName, GiveBattleTowerPrize, PopulateBravoTrainerBattleTowerLostData,
PrintBattleTowerTrainerGreeting, ResetBattleTowerStreak, SaveBattleTowerProgress, SetBattleTowerProperty,
SetBattleTowerTrainerGfxId, ShouldBattleEReaderTrainer, StartSpecialBattle

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

### field_effect.c (13)
ApplyGlobalFieldPaletteTint, DoBirdSpriteWithPlayerAffineAnim, FallWarpEffect_7,
FieldEffectScript_LoadFadedPal, FieldEffectScript_LoadPal, ShowMonEffect_Indoors_3, ShowMonEffect_Indoors_7,
ShowMonEffect_Outdoors_5, ShowMonEffect_Outdoors_7, SpinObjectEvent, TryChangeBirdSprite,
WarpInObjectEventDownwards, WarpOutObjectEventUpwards

### battle_anim_special.c (11)
AnimTask_IsBallBlockedByTrainerOrDodged, AnimTask_ShinySparkles, SpriteCB_ShinySparkles_1,
SpriteCB_ThrowBall_Bounce, SpriteCB_ThrowBall_DoShake, SpriteCB_ThrowBall_Init, SpriteCB_ThrowBall_InitClick,
SpriteCB_ThrowBall_InitShake, SpriteCB_ThrowBall_InitialFall, SpriteCB_ThrowBall_TenFrameDelay,
TrainerBallBlock2

### event_object_movement.c (11)
MovementAction_FaceDownFast_Step0, MovementAction_FaceLeftFast_Step0, MovementAction_FaceRightFast_Step0,
MovementAction_FaceUpFast_Step0, MovementAction_GlideDown_Step0, MovementAction_GlideLeft_Step0,
MovementAction_GlideRight_Step0, MovementAction_GlideUp_Step0, SetHideObstacleFlag,
ShouldInitObjectEventStateFromTemplate, TemplateIsObstacleAndVisibleFromConnectingMap

### text.c (10)
DecompressGlyph_Female, DecompressGlyph_Male, DecompressGlyph_NormalCopy1, DecompressGlyph_NormalCopy2,
FontFunc_Female, FontFunc_Male, FontFunc_NormalCopy1, FontFunc_NormalCopy2, GetGlyphWidth_Female,
GetGlyphWidth_Male

### save_failed_screen.c (9)
BlankPalettes, ClearMapBuffer, FillBgMapBufferRect, PrintTextOnSaveFailedScreen, RequestDmaCopyFromCharBuffer,
RequestDmaCopyFromScreenBuffer, RunSaveFailedScreen, TryWipeDamagedSectors, UpdateMapBufferWithText

### bike.c (7)
BikeInputHandler_Normal, BikeInputHandler_Slope, BikeInputHandler_Turning, BikeTransition_Downhill,
BikeTransition_MoveDirection, BikeTransition_Uphill, MetatileBehaviorForbidsBiking

### field_fadetransition.c (7)
ExitWarpFadeInScreen, FadeTransition_FadeInOnReturnToStartMenu, Task_CableClubWarp, Task_ContinueScript,
Task_DoorWarp, Task_SafariZoneRanOutOfBalls, WarpFadeInScreenWithDelay

### new_menu_helpers.c (7)
CopyDecompressedTileDataToVram, CreateStartMenuWindow, DecompressAndCopyTileDataToVram2,
DecompressAndLoadBgGfxUsingHeap2, DrawHelpMessageWindowWithText, GetTextSpeedSetting, LoadStdWindowFrameGfx

### overworld.c (7)
CB2_EnterFieldFromQuestLog, CB2_SetUpOverworldForQLPlayback, CountBadgesForOverworldWhiteOutLossCalculation,
DoCB1_Overworld_QuestLogPlayback, MetatileBehavior_IsSurfableInSeafoamIslands,
Overworld_ResetStateAfterWhitingOut, QL_LoadMapNormal

### daycare.c (6)
SpriteCB_Egg_0, SpriteCB_Egg_1, SpriteCB_Egg_2, SpriteCB_Egg_3, SpriteCB_Egg_4, SpriteCB_Egg_5

### mailbox_pc.c (6)
ItemPrintFunc, MailboxPC_AddScrollIndicatorArrows, MailboxPC_GetAddWindow, MailboxPC_InitBuffers,
MailboxPC_InitListMenu, MailboxPC_RemoveWindow

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

### pokemon_storage_system_data.c (5)
AddBoxMenu, HandleInput_InBox_Normal, SetMenuTextsForItem, SetMenuTextsForMon, ToggleCursorMultiMoveMode

### pokemon_storage_system_graphics.c (5)
DestroyAllIconsInColumn, DoReleaseMonAnim, DoReleaseMonComeBackAnim, SetShiftMonSpritePtr, ShiftMons

### title_screen.c (5)
CreateLeafSprite, CreateStreakSprites, SpriteCallback_Streak, SpriteCallback_TitleScreenLeaf, Task_LeafSpawner

### battle_transition.c (4)
Spiral_End, Spiral_Init, Spiral_UpdateFrame, VBlankCB_Spiral

### event_data.c (4)
EnableNationalPokedex_RSE, GetFlagAddr, IsFlagOrVarStoredInQuestLog, ResetSpecialVars

### field_screen_effect.c (4)
BarnDoorWipeLoadGpuRegs, BarnDoorWipeSaveGpuRegs, Task_BarnDoorWipe, Task_BarnDoorWipeChild

### field_specials.c (4)
QuestLog_CheckDepartingIndoorsMap, QuestLog_TryRecordDepartedLocation, SetDeoxysTrianglePalette,
Task_DoDeoxysTriangleInteraction

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

### battle_gfx_sfx_util.c (2)
BattleInterfaceSetWindowPals, DecompressTrainerBackPalette

### battle_message.c (2)
BattleStringShouldBeColored, Localize_TrainerClass_Names

### battle_records.c (2)
AddOpponentLinkBattleRecord, UpdateBattleOutcomeOnTrainerCards

### fldeff_cut.c (2)
MetatileAtCoordsIsGrassTile, SetCutGrassMetatileAt

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

### battle_main.c (1)
BattleIntroOpponentSendsOutMonAnimation

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

### easy_chat.c (1)
PopulateECGroups

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

### save_menu_util.c (1)
SaveStatToString

### script_pokemon_util.c (1)
ChooseBattleTowerPlayerParty

### text_window_graphics.c (1)
GetUserWindowGraphics

### tilemap_util.c (1)
TilemapUtil_SetTilemap


## À vérifier (61) : ressemble à une fonction de la fusion (donnée) sans en être prouvée la même : à lire

### pokemon_storage_system_misc.c (8)
Item_FromMonToMoving ~ TakeItemFromMon (pokemon_storage_system.c, 68 %)
Item_GiveMovingToMon ~ GiveItemToMon (pokemon_storage_system.c, 64 %)
Item_TakeMons ~ MoveItemFromMonToBag (pokemon_storage_system.c, 87 %)
MultiMove_Function_ChangeSelection ~ MultiMove_ChangeSelection (pokemon_storage_system.c, 90 %)
MultiMove_Function_GrabSelection ~ MultiMove_GrabSelection (pokemon_storage_system.c, 80 %)
MultiMove_Function_MoveMons ~ MultiMove_MoveMons (pokemon_storage_system.c, 77 %)
MultiMove_Function_PlaceMons ~ MultiMove_PlaceMons (pokemon_storage_system.c, 80 %)
MultiMove_Function_Start ~ MultiMove_Start (pokemon_storage_system.c, 90 %)

### main_menu.c (7)
LoadUserFrameToBg ~ LoadMainMenuWindowFrameTiles (main_menu.c, 82 %)
MainMenuGpuInit ~ InitMainMenu (main_menu.c, 75 %)
MainMenu_DrawWindow ~ DrawMainMenuWindowBorder (main_menu.c, 77 %)
MainMenu_EraseWindow ~ ClearMainMenuWindowTilemap (main_menu.c, 85 %)
PrintContinueStats ~ CB2_MainMenu (main_menu.c, 77 %)
Task_MysteryGiftError ~ Task_DisplayMainMenuInvalidActionError (main_menu.c, 84 %)
Task_UpdateVisualSelection ~ Task_HighlightSelectedMainMenuItem (main_menu.c, 82 %)

### pokemon_storage_system_data.c (7)
HandleInput_BoxTitle ~ HandleInput_OnBox (pokemon_storage_system.c, 62 %)
HandleInput_InBox_GrabbingMultiple ~ InBoxInput_SelectingMultiple (pokemon_storage_system.c, 65 %)
HandleInput_InBox_MovingMultiple ~ InBoxInput_MovingMultiple (pokemon_storage_system.c, 75 %)
MonPlaceChange_MoveCursorDown ~ MonPlaceChange_CursorDown (pokemon_storage_system.c, 60 %)
MonPlaceChange_MoveCursorUp ~ MonPlaceChange_CursorUp (pokemon_storage_system.c, 75 %)
SetMovedMonData ~ SetMovingMonData (pokemon_storage_system.c, 81 %)
TrySetDisplayMonData ~ TryRefreshDisplayMon (pokemon_storage_system.c, 93 %)

### daycare.c (5)
CB2_EggHatch_0 ~ CB2_LoadEggHatch (egg_hatch.c, 69 %)
CB2_EggHatch_1 ~ CB2_EggHatch (egg_hatch.c, 61 %)
CreatedHatchedMon ~ CreateHatchedMon (egg_hatch.c, 98 %)
DayCare_GetBoxMonNickname ~ GetBoxMonNickname (daycare.c, 92 %)
DayCare_GetMonNickname ~ GetMonNickname2 (daycare.c, 92 %)

### mail.c (5)
CB2_InitMailView ~ CB2_InitMailRead (mail.c, 93 %)
CB2_RunShowMailCB ~ CB2_MailRead (mail.c, 82 %)
DoInitMailView ~ MailReadBuildGraphics (mail.c, 88 %)
ShowMailCB_WaitButton ~ CB2_ExitOnKeyPress (mail.c, 90 %)
ShowMailCB_WaitFadeIn ~ CB2_WaitForPaletteExitOnKeyPress (mail.c, 76 %)

### text_window.c (5)
LoadHelpMessageWindowGfx ~ LoadSignpostWindowGfx (text_window.c, 84 %)
LoadMenuMessageWindowGfx ~ LoadSignpostWindowGfx (text_window.c, 84 %)
LoadUserWindowGfx ~ LoadUserWindowBorderGfx (text_window.c, 93 %)
LoadUserWindowGfx2 ~ LoadUserWindowBorderGfx (text_window.c, 93 %)
LoadUserWindowGfxByFrame ~ LoadWindowGfx (text_window.c, 86 %)

### new_menu_helpers.c (3)
DisplayYesNoMenuDefaultNo ~ DisplayYesNoMenuDefaultYes (menu.c, 60 %)
MallocAndDecompress ~ malloc_and_decompress (menu.c, 100 %)
TaskFreeBufAfterCopyingTileDataToVram ~ task_free_buf_after_copying_tile_data_to_vram (menu.c, 66 %)

### pokemon_storage_system_graphics.c (3)
SetBoxSpeciesAndPersonalities ~ GetIncomingBoxMonData (pokemon_storage_system.c, 71 %)
SpriteCB_BoxScrollArrow ~ SpriteCB_Arrow (pokemon_storage_system.c, 82 %)
SpriteCB_MovePartySpriteToNextSlot ~ SpriteCB_MovePartyMonToNextSlot (pokemon_storage_system.c, 91 %)

### battle_anim_special.c (2)
SpriteCB_ShinySparkles_2 ~ SpriteCB_ShinyStars_Diagonal (battle_anim_throw.c, 68 %)
SpriteCB_ThrowBall_DelayThenBreakOut ~ SpriteCB_Ball_Release (battle_anim_throw.c, 60 %)

### mail_data.c (2)
GiveMailToMon2 ~ GiveMailToMon (mail_data.c, 96 %)
TakeMailFromMon2 ~ TakeMailFromMonAndSave (mail_data.c, 96 %)

### pokemon.c (2)
Battle_PrintStatBoosterEffectMessage ~ UseStatIncreaseItem (pokemon.c, 97 %)
InitMonSpritesGfx_Mode0 ~ InitMonSpritesGfx_FullParty (pokemon.c, 89 %)

### pokemon_icon.c (2)
CreateMonIcon_HandleDeoxys ~ CreateMonIconNoPersonality (pokemon_icon.c, 98 %)
MailSpeciesToIconSpecies ~ GetIconSpeciesNoPersonality (pokemon_icon.c, 94 %)

### text.c (2)
GetGlyphWidth_NormalCopy1 ~ GetGlyphWidth_Small (text.c, 94 %)
GetGlyphWidth_NormalCopy2 ~ GetGlyphWidth_Small (text.c, 89 %)

### battle_gfx_sfx_util.c (1)
FreeTrainerFrontPicPaletteAndTile ~ FreeTrainerFrontPicPalette (battle_gfx_sfx_util.c, 60 %)

### clear_save_data_screen.c (1)
SaveClearScreen_GpuInit ~ PokeSum_Setup_InitGpu (kanto_summary_screen.c, 65 %)

### field_fadetransition.c (1)
Task_ReturnFromLinkRoomWarp ~ Task_ReturnToWorldFromLinkRoom (field_screen_effect.c, 67 %)

### pokemon_storage_system.c (1)
SeekToNextMonInBox ~ StorageSystemGetNextMonIndex (pokemon_storage_system.c, 81 %)

### pokemon_storage_system_menu.c (1)
PrintStringToBufferCopyNow ~ UnusedDrawTextWindow (pokemon_storage_system.c, 69 %)

### pokemon_storage_system_tasks.c (1)
StartDisplayMonMosaic ~ StartDisplayMonMosaicEffect (pokemon_storage_system.c, 65 %)

### save_failed_screen.c (1)
WipeDamagedSectors ~ WipeSectors (save_failed_screen.c, 84 %)

### sprite.c (1)
FreeSpriteTilesIfNotUsingSheet ~ DestroySprite (sprite.c, 79 %)


## Équivalente (564) : prouvée : même code sous un autre nom (seuls diffèrent des noms eux-mêmes équivalents)

### field_effect.c (74)
PokeballGlowEffect_FlashFirstThree (PokeballGlowEffect_Flash1 (field_effect.c), 0x1007 = FLDEFF_PAL_TAG_POKEBALL_GLOW, >= 3 = > 2)
FallWarpEffect_1 (FallWarpEffect_Init (field_effect.c), même code)
FallWarpEffect_2 (FallWarpEffect_WaitWeather (field_effect.c), même code)
FallWarpEffect_4 (FallWarpEffect_Fall (field_effect.c), même code)
FallWarpEffect_6 (FallWarpEffect_CameraShake (field_effect.c), même code)
Task_EscalatorWarpFieldEffect (Task_EscalatorWarpOut (field_effect.c), table appariée)
EscalatorWarpEffect_1 (EscalatorWarpOut_Init (field_effect.c), + journal de RF)
EscalatorWarpEffect_4 (EscalatorWarpOut_Down_End (field_effect.c), Escalator_AnimatePlayerGoingDown = RideDownEscalatorOut)
EscalatorWarpEffect_6 (EscalatorWarpOut_Up_End (field_effect.c), Escalator_AnimatePlayerGoingUp = RideUpEscalatorOut)
Escalator_TransitionToWarpInEffect (WarpAtEndOfEscalator (field_effect.c), même code)
FieldCB_EscalatorWarpIn (FieldCallback_EscalatorWarpIn (field_effect.c), RF + FreezeObjectEvents et journal (pas d'escalator à Kanto))
Task_EscalatorWarpInFieldEffect (Task_EscalatorWarpIn (field_effect.c), même code)
EscalatorWarpInEffect_1 (EscalatorWarpIn_Init (field_effect.c), même code)
EscalatorWarpInEffect_7 (EscalatorWarpIn_End (field_effect.c), RF + UnfreezeObjectEvents et journal (pas d'escalator à Kanto))
waterfall_1_do_anim_probably (WaterfallFieldEffect_ShowMon (field_effect.c), même code)
waterfall_2_wait_anim_finish_probably (WaterfallFieldEffect_WaitForShowMon (field_effect.c), même code)
waterfall_3_move_player_probably (WaterfallFieldEffect_RideUp (field_effect.c), WalkSlower de RF = WalkSlow d'Émeraude (1 pixel / 2 images))
waterfall_4_wait_player_move_probably (WaterfallFieldEffect_ContinueRideOrEnd (field_effect.c), même code)
LavaridgeGymB1FWarpEffect_1 (LavaridgeGymB1FWarpEffect_Init (field_effect.c), même code)
LavaridgeGymB1FWarpEffect_3 (LavaridgeGymB1FWarpEffect_Launch (field_effect.c), FLDEFF_LAVARIDGE_GYM_WARP = FLDEFF_ASH_LAUNCH)
LavaridgeGymB1FWarpExitEffect_1 (LavaridgeGymB1FWarpExitEffect_Init (field_effect.c), même code)
LavaridgeGymB1FWarpExitEffect_2 (LavaridgeGymB1FWarpExitEffect_StartPopOut (field_effect.c), FLDEFF_POP_OUT_OF_ASH = FLDEFF_ASH_PUFF)
LavaridgeGymB1FWarpExitEffect_3 (LavaridgeGymB1FWarpExitEffect_PopOut (field_effect.c), même code)
LavaridgeGym1FWarpEffect_1 (LavaridgeGym1FWarpEffect_Init (field_effect.c), même code (Arène de Vermilava : Hoenn))
LavaridgeGym1FWarpEffect_2 (LavaridgeGym1FWarpEffect_AshPuff (field_effect.c), FLDEFF_POP_OUT_OF_ASH = FLDEFF_ASH_PUFF)
LavaridgeGym1FWarpEffect_4 (LavaridgeGym1FWarpEffect_FadeOut (field_effect.c), FLDEFF_POP_OUT_OF_ASH = FLDEFF_ASH_PUFF)
SpriteCB_PopOutOfAsh (SpriteCB_AshLaunch (field_effect.c), FLDEFF_POP_OUT_OF_ASH = FLDEFF_ASH_LAUNCH)
FieldCallback_EscapeRopeExit (FieldCallback_EscapeRopeWarpIn (field_effect.c), + journal de RF)
CreateTeleportFieldEffectTask (FldEff_TeleportWarpOut (field_effect.c), même code)
Task_DoTeleportFieldEffect (Task_TeleportWarpOut (field_effect.c), table appariée)
TeleportFieldEffectTask1 (TeleportWarpOutFieldEffect_Init (field_effect.c), même code)
TeleportFieldEffectTask2 (TeleportWarpOutFieldEffect_SpinGround (field_effect.c), même table de rotation (initialiseurs nommés))
TeleportFieldEffectTask3 (TeleportWarpOutFieldEffect_SpinExit (field_effect.c), 168 = DISPLAY_HEIGHT + 8)
TeleportFieldEffectTask4 (TeleportWarpOutFieldEffect_End (field_effect.c), Émeraude + Tour Mirage (Hoenn))
FieldCallback_TeleportIn (FieldCallback_TeleportWarpIn (field_effect.c), même code)
Task_DoTeleportInFieldEffect (Task_TeleportWarpIn (field_effect.c), table appariée)
TeleportInFieldEffectTask3 (TeleportWarpInFieldEffect_SpinGround (field_effect.c), directions en valeur)
Task_ShowMon_Outdoors (Task_FieldMoveShowMonOutdoors (field_effect.c), table appariée)
ShowMonEffect_Outdoors_1 (FieldMoveShowMonOutdoorsEffect_Init (field_effect.c), DISPLAY_WIDTH / HEIGHT en valeur, pointeur de VBlank)
ShowMonEffect_Outdoors_2 (FieldMoveShowMonOutdoorsEffect_LoadGfx (field_effect.c), même code)
ShowMonEffect_Outdoors_3 (FieldMoveShowMonOutdoorsEffect_CreateBanner (field_effect.c), WIN_RANGE écrit à la main, mêmes bornes)
ShowMonEffect_Outdoors_4 (FieldMoveShowMonOutdoorsEffect_WaitForMon (field_effect.c), case de tâche)
ShowMonEffect_Outdoors_6 (FieldMoveShowMonOutdoorsEffect_RestoreBg (field_effect.c), WIN_RANGE(0, 241) = DISPLAY_WIDTH + 1)
VBlankCB_ShowMonEffect_Outdoors (VBlankCB_FieldMoveShowMonOutdoors (field_effect.c), pointeur, cases de tâche)
LoadFieldMoveStreaksTilemapToVram (LoadFieldMoveOutdoorStreaksTilemap (field_effect.c), 10 * 32 = ARRAY_COUNT(sFieldMoveStreaksOutdoors_Tilemap))
Task_ShowMon_Indoors (Task_FieldMoveShowMonIndoors (field_effect.c), table appariée)
ShowMonEffect_Indoors_1 (FieldMoveShowMonIndoorsEffect_Init (field_effect.c), pointeur de VBlank (port 64 bits))
ShowMonEffect_Indoors_2 (FieldMoveShowMonIndoorsEffect_LoadGfx (field_effect.c), même code)
ShowMonEffect_Indoors_4 (FieldMoveShowMonIndoorsEffect_WaitForMon (field_effect.c), même code)
ShowMonEffect_Indoors_5 (FieldMoveShowMonIndoorsEffect_RestoreBg (field_effect.c), RF remet aussi WININ (invisible : fenêtres coupées))
ShowMonEffect_Indoors_6 (FieldMoveShowMonIndoorsEffect_SlideBannerOff (field_effect.c), même code)
VBlankCB_ShowMonEffect_Indoors (VBlankCB_FieldMoveShowMonIndoors (field_effect.c), pointeur (port 64 bits))
Task_FldEffUseSurf (Task_SurfFieldEffect (field_effect.c), table appariée)
UseSurfEffect_2 (SurfFieldEffect_FieldMovePose (field_effect.c), même code)
UseSurfEffect_3 (SurfFieldEffect_ShowMon (field_effect.c), case de tâche, 0x80000000 = 1 << 31)
UseSurfEffect_4 (SurfFieldEffect_JumpOnSurfBlob (field_effect.c), PLAYER_AVATAR_GFX_RIDE de RF = PLAYER_AVATAR_STATE_SURFING)
UseSurfEffect_5 (SurfFieldEffect_End (field_effect.c), + aide de RF)
Task_MoveDeoxysRock_Step (Task_MoveDeoxysRock (field_effect.c), << 4 = * 16)
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

### start_menu.c (44)
SetUpStartMenu (BuildStartMenuActions (start_menu.c), même aiguillage)
AppendToStartMenuItems (AddStartMenuAction (start_menu.c), même code)
SetUpStartMenu_NormalField (BuildNormalStartMenu (start_menu.c), mêmes entrées)
SetUpStartMenu_SafariZone (BuildSafariZoneStartMenu (start_menu.c), mêmes entrées)
DestroySafariZoneStatsWindow (RemoveExtraStartMenuWindows (start_menu.c), fenêtre du Safari de Kanto comprise)
PrintStartMenuItems (PrintStartMenuActions (start_menu.c), même code)
DoDrawStartMenu (InitStartMenuStep (start_menu.c), même enchaînement)
DrawStartMenuInOneGo (InitStartMenu (start_menu.c), même code)
task50_startmenu (StartMenuTask (start_menu.c), même code)
OpenStartMenuWithFollowupFunc (CreateStartMenuTask (start_menu.c), même code)
FieldCB2_DrawStartMenu (FieldCB_ReturnToFieldStartMenu (start_menu.c), même code)
SetUpReturnToStartMenu (ShowReturnToFieldStartMenu (start_menu.c), même code)
Task_StartMenuHandleInput (Task_ShowStartMenu (start_menu.c), même code)
StartCB_HandleInput (HandleStartMenuInput (start_menu.c), même code)
StartMenu_FadeScreenIfLeavingOverworld (HandleStartMenuInput (start_menu.c), fondu avant un écran (sauf SAUVER, RETOUR, PARTIR))
StartMenuPokedexSanityCheck (StartMenuPokedexCallback (start_menu.c), même vérification)
StartMenuPlayerCallback (StartMenuPlayerNameCallback (start_menu.c), carte de dresseur)
StartCB_Save1 (StartMenuSaveCallback (start_menu.c), même code)
StartCB_Save2 (SaveStartCallback (start_menu.c), même code)
StartMenu_PrepareForSave (InitSave (start_menu.c), même code)
RunSaveDialogCB (RunSaveCallback (start_menu.c), SAVECB_RETURN_* = SAVE_*)
PrintSaveTextWithFollowupFunc (ShowSaveMessage (start_menu.c), même code)
task50_save_game (SaveCallback (start_menu.c), boucle de sauvegarde)
SaveDialog_Wait60FramesOrAButtonHeld (SaveSuccesTimer (start_menu.c), même code)
SaveDialog_Wait60FramesThenCheckAButtonHeld (SaveErrorTimer (start_menu.c), même attente)
SaveDialogCB_PrintAskSaveText (SaveConfirmSaveCallback (start_menu.c), même code)
SaveDialogCB_AskSavePrintYesNoMenu (SaveYesNoCallback (start_menu.c), même code)
SaveDialogCB_AskSaveHandleInput (SaveConfirmInputCallback (start_menu.c), même code)
SaveDialogCB_PrintAskOverwriteText (SaveConfirmOverwriteCallback (start_menu.c), même code)
SaveDialogCB_AskOverwritePrintYesNoMenu (SaveYesNoCallback (start_menu.c), même code)
SaveDialogCB_AskReplacePreviousFilePrintYesNoMenu (SaveFileExistsCallback (start_menu.c), même enchaînement)
SaveDialogCB_AskOverwriteOrReplacePreviousFileHandleInput (SaveOverwriteInputCallback (start_menu.c), même code)
SaveDialogCB_PrintSavingDontTurnOffPower (SaveSavingMessageCallback (start_menu.c), même code)
SaveDialogCB_DoSave (SaveDoSaveCallback (start_menu.c), même code)
SaveDialogCB_PrintSaveResult (SaveSuccessCallback (start_menu.c), résultat de la sauvegarde)
SaveDialogCB_WaitPrintSuccessAndPlaySE (SaveSuccessCallback (start_menu.c), même code)
SaveDialogCB_ReturnSuccess (SaveReturnSuccessCallback (start_menu.c), même code)
SaveDialogCB_WaitPrintErrorAndPlaySE (SaveErrorCallback (start_menu.c), même code)
SaveDialogCB_ReturnError (SaveReturnErrorCallback (start_menu.c), même code)
PrintSaveStats (ShowSaveInfoWindow (start_menu.c), même fenêtre)
CloseSaveStatsWindow (RemoveSaveInfoWindow (start_menu.c), même code)
CloseStartMenu (HideStartMenu (start_menu.c), SE_SELECT puis HideStartMenuWindow)
CB2_WhileSavingAfterLinkBattle → MainCB (clear_save_data_screen.c)
CloseSaveMessageWindow → HideSaveMessageWindow (start_menu.c)

### event_object_movement.c (42)
MakeObjectTemplateFromObjectEventTemplate (MakeSpriteTemplateFromObjectEventTemplate (event_object_movement.c), union du gabarit de RF)
TryLoadObjectPalette (LoadSpritePaletteIfTagExists (event_object_movement.c), même code)
ObjectCB_CameraObject (SpriteCB_CameraObject (event_object_movement.c), même code)
FindCameraObject (FindCameraSprite (event_object_movement.c), même code)
CameraObjectReset1 (CameraObjectReset (event_object_movement.c), CAMERA_STATE_INIT = 0)
CameraObjectSetFollowedObjectId (CameraObjectSetFollowedSpriteId (event_object_movement.c), même code)
CameraObjectReset2 (CameraObjectFreeze (event_object_movement.c), CAMERA_STATE_FROZEN = 2)
CopyablePlayerMovement_GoSpeed0 (CopyablePlayerMovement_WalkNormal (event_object_movement.c), + MEW de l'Île Lointaine (Hoenn))
CopyablePlayerMovement_GoSpeed1 (CopyablePlayerMovement_WalkFast (event_object_movement.c), même code)
CopyablePlayerMovement_GoSpeed2 (CopyablePlayerMovement_WalkFaster (event_object_movement.c), même code)
CopyablePlayerMovement_GoSpeed4 (CopyablePlayerMovement_Jump (event_object_movement.c), même code)
UpdateWalkSlower (UpdateWalkSlow (event_object_movement.c), même vitesse)
MovementAction_WalkSlowerDown_Step0 (MovementAction_WalkSlowDown_Step0 (event_object_movement.c), WALK_SLOWER de RF = WALK_SLOW d'Émeraude (macro walk_slower_*))
MovementAction_WalkSlowerDown_Step1 (MovementAction_WalkSlowDown_Step1 (event_object_movement.c), même vitesse)
MovementAction_WalkSlowerUp_Step0 (MovementAction_WalkSlowUp_Step0 (event_object_movement.c), même vitesse)
MovementAction_WalkSlowerUp_Step1 (MovementAction_WalkSlowUp_Step1 (event_object_movement.c), même vitesse)
MovementAction_WalkSlowerLeft_Step0 (MovementAction_WalkSlowLeft_Step0 (event_object_movement.c), même vitesse)
MovementAction_WalkSlowerLeft_Step1 (MovementAction_WalkSlowLeft_Step1 (event_object_movement.c), même vitesse)
MovementAction_WalkSlowerRight_Step0 (MovementAction_WalkSlowRight_Step0 (event_object_movement.c), même vitesse)
MovementAction_WalkSlowerRight_Step1 (MovementAction_WalkSlowRight_Step1 (event_object_movement.c), même vitesse)
CalcWhetherObjectIsOffscreen (UpdateObjectEventOffscreen (event_object_movement.c), avec la marge de l'OCEANE de RF (portée 2026-11-02))
UpdateObjEventSpriteVisibility (UpdateObjectEventSpriteVisibility (event_object_movement.c), même code)
UpdateWalkSlowerAnim (UpdateWalkSlowAnim (event_object_movement.c), même code)
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

### item_use.c (38)
DisplayItemMessageInCurrentContext (DisplayCannotUseItemMessage (item_use.c), sac ou terrain)
PrintNotTheTimeToUseThat (DisplayDadsAdviceCannotUseItemMessage (item_use.c), gText_OakForbidsUseOfItemHere à Kanto (porté 2026-11-02))
Task_ItemUse_CloseMessageBoxAndReturnToField (Task_CloseCantUseKeyItemMessage (item_use.c), même code)
FieldCB2_UseItemFromField (FieldCB_UseItemOnField (item_use.c), retour au terrain avant l'objet)
Task_ItemUseWaitForFade (FieldCB_ReturnToFieldNoScript (field_screen_effect.c), attente du fondu puis déblocage)
FieldUseFunc_Mail (ItemUseOutOfBattle_Mail (item_use.c), même code)
FieldUseFunc_Bike (ItemUseOutOfBattle_Bike (item_use.c), Piste Cyclable de Kanto comprise)
ItemUseOnFieldCB_Bicycle (ItemUseOnFieldCB_Bike (item_use.c), même code)
FieldUseFunc_Rod (ItemUseOutOfBattle_Rod (item_use.c), message de CHEN à Kanto)
FieldUseFunc_CoinCase (ItemUseOutOfBattle_CoinCase (item_use.c), + journal de RF)
FieldUseFunc_PowderJar (ItemUseOutOfBattle_PowderJar (item_use.c), + journal de RF)
FieldUseFunc_PokeFlute (ItemUseOutOfBattle_PokeFlute (item_use.c), textes de RF (sKText))
FieldUseFunc_Medicine (ItemUseOutOfBattle_Medicine (item_use.c), scène de RF avec SAC = KANTO)
FieldUseFunc_Ether (ItemUseOutOfBattle_PPRecovery (item_use.c), même code)
FieldUseFunc_PpUp (ItemUseOutOfBattle_PPUp (item_use.c), même code)
FieldUseFunc_RareCandy (ItemUseOutOfBattle_RareCandy (item_use.c), scène de RF avec SAC = KANTO)
FieldUseFunc_EvoItem (ItemUseOutOfBattle_EvolutionStone (item_use.c), scène de RF avec SAC = KANTO)
FieldUseFunc_TmCase (ItemUseOutOfBattle_TMCase (item_use.c), BOITE CT de RF)
FieldUseFunc_BerryPouch (ItemUseOutOfBattle_BerryPouch (item_use.c), SAC A BAIES de RF)
FieldUseFunc_TeachyTv (ItemUseOutOfBattle_TeachyTv (item_use.c), TV ABC de RF)
FieldUseFunc_Repel (ItemUseOutOfBattle_Repel (item_use.c), même code)
FieldUseFunc_BlackWhiteFlute (ItemUseOutOfBattle_BlackWhiteFlute (item_use.c), même code)
FieldUseFunc_TownMap (ItemUseOutOfBattle_TownMap (item_use.c), CARTE de RF)
FieldUseFunc_FameChecker (ItemUseOutOfBattle_FameChecker (item_use.c), MEMORYDEX de RF)
FieldUseFunc_VsSeeker (ItemUseOutOfBattle_VsSeeker (item_use.c), CHERCHE VS de RF)
BattleUseFunc_PokeBallEtc (ItemUseInBattle_PokeBall (item_use.c), même code)
BattleUseFunc_PokeFlute (ItemUseInBattle_PokeFlute (item_use.c), POKé FLUTE de RF)
BattleUseFunc_StatBooster (ItemUseInBattle_StatIncrease (item_use.c), même code)
Task_BattleUse_StatBooster_DelayAndPrint (Task_UseStatIncreaseItem (item_use.c), même enchaînement)
Task_BattleUse_StatBooster_WaitButton_ReturnToBattle (Task_UseStatIncreaseItem (item_use.c), même enchaînement)
ItemUse_SwitchToPartyMenuInBattle (ItemUseInBattle_ShowPartyMenu (item_use.c), même code)
BattleUseFunc_Medicine (ItemUseInBattle_Medicine (item_use.c), même aiguillage)
BattleUseFunc_Ether (ItemUseInBattle_PPRecovery (item_use.c), même aiguillage)
BattleUseFunc_PokeDoll (ItemUseInBattle_Escape (item_use.c), même code)
FieldUseFunc_OakStopsYou (DisplayDadsAdviceCannotUseItemMessage (item_use.c), message de CHEN à Kanto (porté 2026-11-02))
BattleUseFunc_BerryPouch → ItemUseInBattle_BerryPouch (kanto_berry_pouch.c)
FieldCB_FadeInFromBlack → FieldCB_UseItemOnField (item_use.c)
Task_WaitFadeIn_CallItemUseOnFieldCB → Task_CallItemUseOnFieldCallback (item_use.c)

### player_pc.c (38)
Task_DrawPlayerPcTopMenu (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_ReturnToTopMenu (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcItemStorage (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcMailbox (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcTurnOff (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_CreateItemStorageSubmenu (player_pc.c d'Émeraude (PC du joueur), même rôle)
PrintStringOnWindow0WithDialogueFrame (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_TopMenu_ItemStorageSubmenu_HandleInput (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_DepositItem_WaitFadeAndGoToBag (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcDepositItem (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_ReturnToItemStorageSubmenu (player_pc.c d'Émeraude (PC du joueur), même rôle)
CB2_ReturnFromDepositMenu (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcWithdrawItem (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcCancel (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_SetPageItemVars (player_pc.c d'Émeraude (PC du joueur), même rôle)
CountPCMail (player_pc.c d'Émeraude (PC du joueur), même rôle)
PCMailCompaction (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_DrawMailboxPcMenu (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_MailboxPcHandleInput (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PrintWhatToDoWithSelectedMail (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_DestroyMailboxPcViewAndCancel (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_DrawMailSubmenu (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_MailSubmenuHandleInput (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcReadMail (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_WaitFadeAndReadSelectedMail (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_WaitFadeAndReturnToMailboxPcInputHandler (player_pc.c d'Émeraude (PC du joueur), même rôle)
CB2_ReturnToMailbox (player_pc.c d'Émeraude (PC du joueur), même rôle)
CB2_SetCbToReturnToMailbox (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcMoveMailToBag (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_DrawYesNoMenuToConfirmMoveToBag (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_MoveToBagYesNoMenuHandleInput (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_TryPutMailInBag_DestroyMsgIfSuccessful (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcGiveMailToMon (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_WaitFadeAndGoToPartyMenu (player_pc.c d'Émeraude (PC du joueur), même rôle)
CB2_ReturnToMailboxPc_UpdateScrollVariables (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_Error_NoPokemon (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_RedrawPlayerPcMailboxAndSetUpInputHandler (player_pc.c d'Émeraude (PC du joueur), même rôle)
Task_PlayerPcExitMailSubmenu (player_pc.c d'Émeraude (PC du joueur), même rôle)

### battle_controller_oak_old_man.c (32)
SetControllerToOakOrOldMan (SetControllerToOldMan (battle_controller_old_man.c), sans CHEN)
OakOldManBufferRunCommand (OldManBufferRunCommand (battle_controller_old_man.c), table appariée)
SimulateInputChooseAction (OldManHandleActions (battle_controller_old_man.c), mêmes touches simulées (compteurs de Wally))
OakOldManBufferExecCompleted (OldManBufferExecCompleted (battle_controller_old_man.c), même code)
OakOldManHandleGetMonData (OldManHandleGetMonData (battle_controller_old_man.c), même code)
CopyOakOldManMonData (CopyOldManMonData (battle_controller_old_man.c), même code)
OakOldManHandleSetMonData (OldManHandleSetMonData (battle_controller_old_man.c), même code)
SetOakOldManMonData (SetOldManMonData (battle_controller_old_man.c), même code)
OakOldManHandleReturnMonToBall (OldManHandleReturnMonToBall (battle_controller_old_man.c), même code)
OakOldManHandleDrawTrainerPic (OldManHandleDrawTrainerPic (battle_controller_old_man.c), dos du vieil homme ; sans la branche de CHEN)
OakOldManHandleTrainerSlide (OldManHandleTrainerSlide (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleFaintAnimation (OldManHandleFaintAnimation (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleMoveAnimation (OldManHandleMoveAnimation (battle_controller_old_man.c), même code)
OakOldManDoMoveAnimation (OldManDoMoveAnimation (battle_controller_old_man.c), même code)
OakOldManHandlePrintString (OldManHandlePrintString (battle_controller_old_man.c), BATTLE_TYPE_OLD_MAN_TUTORIAL = WALLY_TUTORIAL ; sans les textes de CHEN)
OakOldManHandlePrintSelectionString (OldManHandlePrintSelectionString (battle_controller_old_man.c), même code)
OakOldManHandleChooseAction (OldManHandleChooseAction (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleChooseMove (OldManHandleChooseMove (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleChoosePokemon (OldManHandleChoosePokemon (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleExpUpdate (OldManHandleExpUpdate (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleHitAnimation (OldManHandleHitAnimation (battle_controller_old_man.c), même code)
OakOldManHandlePlaySE (OldManHandlePlaySE (battle_controller_old_man.c), même code)
OakOldManHandlePlayFanfare (OldManHandlePlayFanfareOrBGM (battle_controller_old_man.c), même code)
OakOldManHandleFaintingCry (OldManHandleFaintingCry (battle_controller_old_man.c), même code)
OakOldManHandleIntroSlide (OldManHandleIntroSlide (battle_controller_old_man.c), même code)
OakOldManHandleIntroTrainerBallThrow (OldManHandleIntroTrainerBallThrow (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleDrawPartyStatusSummary (OldManHandleDrawPartyStatusSummary (battle_controller_old_man.c), même code)
OakOldManHandleEndBounceEffect (OldManHandleEndBounceEffect (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleBattleAnimation (OldManHandleBattleAnimation (battle_controller_old_man.c), même code)
OakOldManHandleLinkStandbyMsg (OldManHandleLinkStandbyMsg (battle_controller_old_man.c), sans la branche de CHEN)
OakOldManHandleCmd55 (OldManHandleEndLinkBattle (battle_controller_old_man.c), même code)
OakOldManHandleChooseItem → PokedudeHandleChooseItem (kanto_battle_controller_pokedude.c)

### field_player_avatar.c (23)
player_step (PlayerStep (field_player_avatar.c), dalles tournantes de RF déjà dedans ; + Vélo Cross d'Émeraude)
StartPlayerAvatarSummonMonForFieldMoveAnim (SetPlayerAvatarFieldMove (field_player_avatar.c), PLAYER_AVATAR_GFX_FIELD_MOVE = STATE_FIELD_MOVE)
Task_BumpBoulder (Task_PushBoulder (field_player_avatar.c), table appariée)
DoBoulderDust (PushBoulder_Move (field_player_avatar.c), + journal de RF ; WalkSlower de RF = WalkSlow)
DoBoulderFinish (PushBoulder_End (field_player_avatar.c), même code (trous et interrupteurs de la Route Victoire de RF))
Fishing2 (Fishing_GetRodOut (field_player_avatar.c), tables par canne (initialiseurs nommés))
Fishing3 (Fishing_WaitBeforeDots (field_player_avatar.c), même code)
Fishing8 (Fishing_WaitForA (field_player_avatar.c), tables par canne)
Fishing9 (Fishing_CheckMoreDots (field_player_avatar.c), tables par canne)
Fishing10 (Fishing_MonOnHook (field_player_avatar.c), même code)
Fishing11 (Fishing_StartEncounter (field_player_avatar.c), + télé et chaîne de pêche d'Émeraude)
Fishing12 (Fishing_NotEvenNibble (field_player_avatar.c), + chaîne de pêche d'Émeraude)
Fishing13 (Fishing_GotAway (field_player_avatar.c), + chaîne de pêche d'Émeraude)
Fishing14 (Fishing_NoMon (field_player_avatar.c), même code)
Fishing15 (Fishing_PutRodAway (field_player_avatar.c), même code)
Fishing16 (Fishing_EndNoMon (field_player_avatar.c), + télé d'Émeraude)
StartTeleportWarpOutPlayerAnim (DoPlayerSpinExit (field_player_avatar.c), téléporteurs de RF (KANTO-ETAT))
GetTeleportSavedFacingDirection (GetSpinStartFacingDir (field_player_avatar.c), même code)
Task_TeleportWarpOutPlayerAnim (Task_DoPlayerSpinExit (field_player_avatar.c), même code)
StartTeleportInPlayerAnim (DoPlayerSpinEntrance (field_player_avatar.c), téléporteurs de RF (KANTO-ETAT))
Task_TeleportWarpInPlayerAnim (Task_DoPlayerSpinEntrance (field_player_avatar.c), même rotation)
TeleportAnim_RotatePlayer (TrySpinPlayerForWarp (field_player_avatar.c), même code)
DoBoulderInit → WaterfallFieldEffect_Init (field_effect.c)

### evolution_graphics.c (22)
SpriteCB_PreEvoSparkleSet1 (SpriteCB_Sparkle_SpiralUpward (evolution_graphics.c), même calcul)
CreatePreEvoSparkleSet1 (CreateSparkle_SpiralUpward (evolution_graphics.c), même code)
SpriteCB_PreEvoSparkleSet2 (SpriteCB_Sparkle_ArcDown (evolution_graphics.c), même calcul)
CreatePreEvoSparkleSet2 (CreateSparkle_ArcDown (evolution_graphics.c), même code)
CreatePostEvoSparkleSet1 (CreateSparkle_CircleInward (evolution_graphics.c), 120 = DISPLAY_WIDTH / 2)
SpriteCB_PostEvoSparkleSet2 (SpriteCB_Sparkle_Spray (evolution_graphics.c), même calcul)
CreatePostEvoSparkleSet2 (CreateSparkle_Spray (evolution_graphics.c), même code)
EvoTask_PreEvoSparkleSet1Init (Task_Sparkles_SpiralUpward_Init (evolution_graphics.c), même code)
EvoTask_CreatePreEvoSparkleSet1 (Task_Sparkles_SpiralUpward (evolution_graphics.c), même calcul)
EvoTask_PreEvoSparkleSet2Init (Task_Sparkles_ArcDown_Init (evolution_graphics.c), même code)
EvoTask_CreatePreEvoSparklesSet2 (Task_Sparkles_ArcDown (evolution_graphics.c), même calcul)
EvoTask_PostEvoSparklesSet1Init (Task_Sparkles_CircleInward_Init (evolution_graphics.c), même code)
EvoTask_CreatePostEvoSparklesSet1 (Task_Sparkles_CircleInward (evolution_graphics.c), même code)
EvoTask_PostEvoSparklesSet2Init (Task_Sparkles_SprayAndFlash_Init (evolution_graphics.c), masque de palettes de l'écran)
EvoTask_CreatePostEvoSparklesSet2 (Task_Sparkles_SprayAndFlash (evolution_graphics.c), masque de palettes de l'écran)
EvoTask_PostEvoSparklesSet2TradeInit (Task_Sparkles_SprayAndFlash_Init (evolution_graphics.c), masque de palettes de l'écran (échange))
EvoTask_CreatePostEvoSparklesSet2Trade (Task_Sparkles_SprayAndFlash (evolution_graphics.c), masque de palettes de l'écran (échange))
EvoTask_PrePostEvoMonSpritesInit (Task_CycleEvolutionMonSprite_Init (evolution_graphics.c), même code)
EvoTask_ChooseNextEvoSpriteAnim (Task_CycleEvolutionMonSprite_TryEnd (evolution_graphics.c), même code)
EvoTask_ShrinkOrExpandEvoSprites (Task_CycleEvolutionMonSprite_UpdateSize (evolution_graphics.c), même calcul)
EvoTask_WaitForPre1SparklesToGoUp → Task_Sparkles_SpiralUpward_End (evolution_graphics.c)
SpriteCB_PostEvoSparkleSet1 → SpriteCB_Sparkle_CircleInward (evolution_graphics.c)

### easy_chat.c (20)
IsECGroupUnlocked (IsEasyChatGroupUnlocked (easy_chat.c), groupes débloqués d'Émeraude)
IsECWordInvalid (IsEasyChatWordInvalid (easy_chat.c), un dictionnaire)
Localize_ConvertEasyChatMessageToString (OtherConvertEasyChatWordsToString (easy_chat.c), un dictionnaire)
EC_DoesEasyChatStringFitOnLine (CanPhraseFitInXRowsYCols (easy_chat.c), un dictionnaire)
GetRandomWordFromGroup (GetRandomEasyChatWordFromGroup (easy_chat.c), un dictionnaire)
GetRandomWordFromAnyGroup (GetRandomEasyChatWordFromUnlockedGroup (easy_chat.c), un dictionnaire)
GetNumUnlockedTrendySayings (GetNumTrendySayingsUnlocked (easy_chat.c), un dictionnaire)
GetRandomECPokemon (GetRandomUnlockedEasyChatPokemon (easy_chat.c), un dictionnaire)
InitEasyChatSelection (InitEasyChatScreenWordData (easy_chat.c), KEC_InitEasyChatSelection)
DestroyEasyChatSelectionData (FreeEasyChatScreenWordData (easy_chat.c), KEC_DestroyEasyChatSelectionData)
GetSelectedGroupByIndex (GetUnlockedEasyChatGroupId (easy_chat.c), KEC_GetSelectedGroupByIndex)
PopulateAlphabeticalGroups (SetUnlockedWordsByAlphabet (easy_chat.c), un dictionnaire)
GetUnlockedECWords (SetSelectedWordGroup (easy_chat.c), KEC_GetUnlockedECWords)
GetDisplayedWordByIndex (GetWordFromSelectedGroup (easy_chat.c), KEC_GetDisplayedWordByIndex)
GetUnlockedWordsInECGroup (SetSelectedWordGroup_GroupMode (easy_chat.c), un dictionnaire)
GetUnlockedWordsInAlphabeticalGroup (SetSelectedWordGroup_AlphabetMode (easy_chat.c), un dictionnaire)
IsGroupSelectable (IsEasyChatGroupUnlocked2 (easy_chat.c), un dictionnaire)
UnlockedECMonOrMove (IsEasyChatIndexAndGroupUnlocked (easy_chat.c), un dictionnaire)
EC_IsDeoxys (IsRestrictedWordSpecies (easy_chat.c), un dictionnaire)
IsWordUnlocked (IsEasyChatWordUnlocked (easy_chat.c), même code)

### tileset_anims.c (17)
QueueAnimTiles_General_Water_Current_LandWatersEdge (QueueAnimTiles_KantoGeneral_Water_Current_LandWatersEdge (tileset_anims.c), table Kanto)
QueueAnimTiles_General_SandWatersEdge (QueueAnimTiles_KantoGeneral_SandWatersEdge (tileset_anims.c), table Kanto)
QueueAnimTiles_CeladonCity_Fountain (QueueAnimTiles_KantoCeladonCity_Fountain (tileset_anims.c), table Kanto)
TilesetAnim_CeladonCity (TilesetAnim_KantoCeladonCity (tileset_anims.c), même code)
InitTilesetAnim_CeladonCity (InitTilesetAnim_KantoCeladonCity (tileset_anims.c), même code)
QueueAnimTiles_SilphCo_Fountain (QueueAnimTiles_KantoSilphCo_Fountain (tileset_anims.c), table Kanto)
TilesetAnim_SilphCo (TilesetAnim_KantoSilphCo (tileset_anims.c), même code)
InitTilesetAnim_SilphCo (InitTilesetAnim_KantoSilphCo (tileset_anims.c), même code)
QueueAnimTiles_MtEmber_Steam (QueueAnimTiles_KantoMtEmber_Steam (tileset_anims.c), table Kanto)
TilesetAnim_MtEmber (TilesetAnim_KantoMtEmber (tileset_anims.c), même code)
InitTilesetAnim_MtEmber (InitTilesetAnim_KantoMtEmber (tileset_anims.c), même code)
QueueAnimTiles_VermilionGym_MotorizedDoor (QueueAnimTiles_KantoVermilionGym_MotorizedDoor (tileset_anims.c), table Kanto)
TilesetAnim_VermilionGym (TilesetAnim_KantoVermilionGym (tileset_anims.c), même code)
InitTilesetAnim_VermilionGym (InitTilesetAnim_KantoVermilionGym (tileset_anims.c), même code)
QueueAnimTiles_CeladonGym_Flowers (QueueAnimTiles_KantoCeladonGym_Flowers (tileset_anims.c), table Kanto)
TilesetAnim_CeladonGym (TilesetAnim_KantoCeladonGym (tileset_anims.c), même code)
InitTilesetAnim_CeladonGym (InitTilesetAnim_KantoCeladonGym (tileset_anims.c), même code)

### battle_anim_special.c (16)
AnimTask_ThrowBallSpecial (AnimTask_ThrowBall_StandingTrainer (battle_anim_throw.c), vieil homme compris (IsOldManTutorialBattle))
AnimTask_ThrowBallSpecial_PlaySfx (AnimTask_ThrowBall_StandingTrainer_Step (battle_anim_throw.c), même enchaînement)
SpriteCB_ThrowBall_ArcFlight (SpriteCB_Ball_Arc (battle_anim_throw.c), même code)
SpriteCB_ThrowBall_ShrinkMon (SpriteCB_Ball_MonShrink_Step (battle_anim_throw.c), même code)
SpriteCB_ThrowBall_DoClick (SpriteCB_Ball_Capture_Step (battle_anim_throw.c), même code)
SpriteCB_ThrowBall_FinishClick (SpriteCB_Ball_FadeOut (battle_anim_throw.c), même code)
CreateStarsWhenBallClicks (MakeCaptureStars (battle_anim_throw.c), même code (cases nommées))
SpriteCB_ThrowBall_BeginBreakOut (SpriteCB_Ball_Release_Step (battle_anim_throw.c), BATTLER_AFFINE_EMERGE = 1)
SpriteCB_ThrowBall_RunBreakOut (SpriteCB_Ball_Release_Wait (battle_anim_throw.c), même code)
TrainerBallBlock (SpriteCB_Ball_Block (battle_anim_throw.c), même code)
SpriteCB_SafariBaitOrRock_Init (SpriteCB_PokeBlock_Throw (battle_anim_throw.c), même code ; gSafariBaitSpriteTemplate et gSafariRockTemplate l'utilisent)
SpriteCB_SafariBaitOrRock_WaitPlayerThrow (SpriteCB_PokeBlock_LiftArm (battle_anim_throw.c), même code)
SpriteCB_SafariBaitOrRock_ArcFlight (SpriteCB_PokeBlock_Arc (battle_anim_throw.c), même code)
AnimTask_ShinySparkles_WaitSparkles → Task_ShinyStars_Wait (battle_anim_throw.c)
AnimTask_ThrowBall_WaitAnimObjComplete → AnimTask_ThrowBall_Step (battle_anim_throw.c)
BattleAnimObj_SignalEnd → DestroySpriteAfterOneFrame (battle_anim_throw.c)

### menu.c (15)
Menu_InitCursorInternal (InitMenu (menu.c d'Émeraude), même code)
Menu_InitCursor (InitMenuNormal (menu.c d'Émeraude), même code)
Menu_RedrawCursor (RedrawMenuCursor (menu.c d'Émeraude), même code)
Menu_ProcessInputNoWrapAround (Menu_ProcessInputNoWrap (menu.c d'Émeraude), même code)
Menu_ProcessInput_other (ProcessMenuInput_other (menu.c d'Émeraude), même code)
MultichoiceList_PrintItems (PrintMenuActionTextsWithSpacing (menu.c d'Émeraude), même code)
AddItemMenuActionTextPrinters (PrintMenuActionTexts (menu.c d'Émeraude), même code)
DestroyYesNoMenu (EraseYesNoWindow (alias dans kanto_bag_compat.h) ; la garde 0xFF de RF est REVISION >= 0xA, absente des cartouches)
MultichoiceGrid_PrintItems (PrintMenuGridTable (menu.c d'Émeraude) : police RF de 8 px → x 8, y 1, même rendu (scénario kanto_blackboard))
MultichoiceGrid_InitCursorInternal (InitMenuGrid (menu.c d'Émeraude), même code)
MultichoiceGrid_InitCursor (InitMenuGridDefaultCursorHeight (menu.c d'Émeraude) ; hauteur 16 = GetMenuCursorDimensionByFont)
MultichoiceGrid_RedrawCursor (MoveMenuGridCursor (menu.c d'Émeraude), même code)
MultichoiceGrid_MoveCursor (ChangeMenuGridCursorPosition (menu.c d'Émeraude), même code)
MultichoiceGrid_MoveCursorIfValid (ChangeGridMenuCursorPosition (menu.c d'Émeraude), même code)
Menu_ProcessInputGridLayout (Menu_ProcessGridInput (menu.c d'Émeraude), même code)

### party_menu.c (14)
PartyMenuPrintText (PrintMessage (party_menu.c), WIN_MSG = 6)
CursorCB_Item (CursorCb_Item (party_menu.c), MENU_B_PRESSED = 255)
CursorCB_Mail (CursorCb_Mail (party_menu.c), MENU_B_PRESSED = 255)
CursorCB_Cancel2 (CursorCb_Cancel2 (party_menu.c), MENU_B_PRESSED = 255)
CursorCB_Store (CursorCb_Store (party_menu.c), même dépôt)
CursorCB_FieldMove (CursorCb_FieldMove (party_menu.c), badges de la région (HasBadgeForFieldMove), carte de vol de la région)
CB2_ReturnToTMCaseMenu (KantoBag_TryGoToBagMenu (kanto_item_menu.c), ITEMMENULOCATION_LAST revient à la boîte CT)
CB2_ReturnToBerryPouchMenu (KantoBag_TryGoToBagMenu (kanto_item_menu.c), ITEMMENULOCATION_LAST revient au sac à baies)
ItemUseCB_MedicineStep (KantoItemUseCB_Medicine (item_use.c, SAC = KANTO) et ItemUseCB_Medicine (party_menu.c), + journal de RF)
Task_HandleRestoreWhichMoveInput (Task_HandleWhichMoveInput (party_menu.c), même code)
ItemUseCB_TryRestorePP (ItemUseCB_PPRecovery (party_menu.c), en combat ou non)
TryUsePPItemInBattle (TryUsePPItem (party_menu.c), sac de RF hors combat compris ; + journal de RF)
ItemUseCB_RareCandyStep (KantoItemUseCB_RareCandy (item_use.c, SAC = KANTO) et ItemUseCB_RareCandy (party_menu.c), + journal de RF)
EnterPartyFromItemMenuInBattle (ChooseMonForInBattleItem (party_menu.c), sans la branche de CHEN)

### fldeff_flash.c (13)
MapTransitionIsEnter (GetMapPairFadeToType (fldeff_flash.c), même boucle sur sTransitionTypes)
MapTransitionIsExit (GetMapPairFadeFromType (fldeff_flash.c), même boucle sur sTransitionTypes)
FlashTransition_Exit (DoExitCaveTransition (fldeff_flash.c), même code)
Task_FlashTransition_Exit_0 (Task_ExitCaveTransition1 (fldeff_flash.c), même code)
Task_FlashTransition_Exit_1 (Task_ExitCaveTransition2 (fldeff_flash.c), adresses VRAM, palette de sortie)
Task_FlashTransition_Exit_2 (Task_ExitCaveTransition3 (fldeff_flash.c), (16 << 8) + n = n + 0x1000)
Task_FlashTransition_Exit_3 (Task_ExitCaveTransition4 (fldeff_flash.c), BLDALPHA_BLEND)
Task_FlashTransition_Exit_4 (Task_ExitCaveTransition5 (fldeff_flash.c), même code)
FlashTransition_Enter (DoEnterCaveTransition (fldeff_flash.c), même code)
Task_FlashTransition_Enter_0 (Task_EnterCaveTransition1 (fldeff_flash.c), même code)
Task_FlashTransition_Enter_1 (Task_EnterCaveTransition2 (fldeff_flash.c), BG_CHAR_ADDR(3) = VRAM + 0xC000, BG_SCREEN_ADDR(31) = VRAM + 0xF800)
Task_FlashTransition_Enter_2 (Task_EnterCaveTransition3 (fldeff_flash.c), BLDALPHA_BLEND(16, 16))
Task_FlashTransition_Enter_3 (Task_EnterCaveTransition4 (fldeff_flash.c), (16 << 8) + n = n + 0x1000)

### trainer_see.c (11)
TrainerSeeFunc_StartExclMark (TrainerExclamationMark (trainer_see.c), états nommés)
TrainerSeeFunc_BeginJumpOutOfAsh (PopOutOfAshBuriedTrainer (trainer_see.c), FLDEFF_POP_OUT_OF_ASH = FLDEFF_ASH_PUFF)
TrainerSeeFunc_EndJumpOutOfAsh (WaitRevealBuriedTrainer (trainer_see.c), même code)
TrainerSeeFunc_OffscreenAboveTrainerCreateCameraObj (OffscreenAboveTrainerCreateCameraObj (trainer_see.c), MAP_OFFSET = 7)
TrainerSeeFunc_OffscreenAboveTrainerCameraObjMoveUp (OffscreenAboveTrainerCameraObjMoveUp (trainer_see.c), même code)
TrainerSeeFunc_OffscreenAboveTrainerCameraObjMoveDown (OffscreenAboveTrainerCameraObjMoveDown (trainer_see.c), même code)
Task_RevealTrainer_RunTrainerSeeFuncList (Task_RunTrainerSeeFuncList (trainer_see.c), pointeur (port 64 bits))
FldEff_ExclamationMarkIcon1 (FldEff_ExclamationMarkIcon (trainer_see.c), sprite des émoticônes de Kanto)
TrainerSeeFunc_WaitExclMark → WaitTrainerExclamationMark (trainer_see.c)
TrainerSeeFunc_WaitJumpOutOfAsh → JumpInPlaceBuriedTrainer (trainer_see.c)
TrainerSeeFunc_WaitRemoveDisguise → WaitRevealDisguisedTrainer (trainer_see.c)

### overworld.c (10)
Overworld_ResetStateOnContinue (UpdateMiscOverworldStates (overworld.c), avec la scène du Safari de Kanto et la Piste Cyclable)
Overworld_TryMapConnectionMusicTransition (TransitionMapMusic (overworld.c), règle de RF portée (Overworld_MusicCanOverrideMapMusic, MUS_RG_SURF))
InitOverworldBgs_NoResetHeap (InitOverworldBgs (overworld.c), crédits de RF (MapLdr_Credits) = Overworld_DoScrollSceneForCredits)
FieldCB_ShowMapNameOnContinue (FieldCB_FadeTryShowMapPopup (overworld.c), + bases secrètes d'Émeraude)
ReloadObjectsAndRunReturnToFieldMapScript (InitObjectEventsReturnToField (overworld.c), + portiques tournants d'Émeraude)
SetUpScrollSceneForCredits (Overworld_DoScrollSceneForCredits (overworld.c), WARP_ID_NONE = -1)
IsUpdateLinkStateCBActive → IsOverworldLinkActive (overworld.c)
LinkPlayerDetectCollision → LinkPlayerGetCollision (overworld.c)
Overworld_LinkRecvQueueLengthMoreThan2 → Overworld_IsRecvQueueAtMax (overworld.c)
ResetAllLinkStates → ResetAllPlayerLinkStates (overworld.c)

### trainer_card.c (10)
VBlankCB_TrainerCard (VblankCb_TrainerCard (trainer_card.c d'Émeraude), même code)
GetTrainerStarCount (étoiles de RF dans TrainerCard_GenerateCardForPlayer (carte de Kanto) : Panthéon, Pokédex de Kanto, Pokédex national, 200 baies et 200 sauts)
HandleGpuRegs (InitGpuRegs (trainer_card.c d'Émeraude), mêmes registres)
DmaClearOam (ClearVramOamPlttRegs (trainer_card.c d'Émeraude) : OAM vidée)
DmaClearPltt (ClearVramOamPlttRegs (trainer_card.c d'Émeraude) : palettes vidées)
ResetBgRegs (ResetGpuRegs et ClearVramOamPlttRegs d'Émeraude, mêmes registres)
SetTrainerCardCB2 (SetTrainerCardCb2 (trainer_card.c d'Émeraude), même code)
BufferTextForCardBack (BufferTextsVarsForCardPage2 (trainer_card.c d'Émeraude) : mêmes lignes + celles d'Émeraude)
SetTrainerCardBgsAndPals (SetCardBgsAndPals (trainer_card.c d'Émeraude) : palettes bleue/verte/bronze/argent/or de RF)
GetCardType (GetSetCardType (trainer_card.c d'Émeraude) : carte de RF pour la version Rouge Feu (carte de Kanto))

### item.c (9)
SetPcItemQuantity (SetPCItemQuantity (item.c d'Émeraude), même code)
SetBagPocketsPointers (SetBagItemsPointers (item.c d'Émeraude) : sac commun gSaveBlockBag)
BagPocketGetFirstEmptySlot (IsBagPocketNonEmpty et les recherches de case libre d'item.c d'Émeraude)
ClearPCItemSlots (ClearItemSlots (item.c d'Émeraude), même code)
CountItemsInPC (CountUsedPCItemSlots (item.c d'Émeraude), même code)
ItemPcCompaction (CompactPCItems (item.c d'Émeraude), même code)
BagPocketCompaction (CompactItemsInBagPocket (item.c d'Émeraude), même code)
SortAndCompactBagPocket (SortBerriesOrTMHMs (item.c d'Émeraude), même tri par numéro)
BagGetQuantityByItemId (CountTotalItemQuantityInBag (item.c d'Émeraude) : additionne les piles de 99 du sac commun (magasin de Kanto))

### field_weather.c (8)
UpdateWeatherGammaShift (UpdateWeatherColorMap (field_weather.c), renommage)
ApplyGammaShiftWithBlend (ApplyColorMapWithBlend (field_weather.c), renommage)
ApplyDroughtGammaShiftWithBlend (ApplyDroughtColorMapWithBlend (field_weather.c), renommage)
WeatherShiftGammaIfPalStateIdle (ApplyWeatherColorMapIfIdle (field_weather.c), renommage)
WeatherBeginGammaFade (ApplyWeatherColorMapIfIdle_Gradual (field_weather.c), renommage)
FadeSelectedPals (kanto_credits.c (macro FadeSelectedPals) et overworld.c (BeginNormalPaletteFade(0x3FFFFFFF, …)), ses deux appelants de RF)
ApplyWeatherGammaShiftToPal (ApplyWeatherColorMapToPal (field_weather.c), renommage)
SetDroughtGamma (SetDroughtColorMap (field_weather.c), renommage)

### script_menu.c (8)
Task_MultichoiceMenu_HandleInput (Task_HandleMultichoiceInput (script_menu.c d'Émeraude) : sDelay de RF = sProcessInputDelay (0 avec MENUS = KANTO))
MultiChoicePrintHelpDescription (DrawLinkServicesMultichoiceMenu (script_menu.c d'Émeraude) : aide des menus link)
Task_YesNoMenu_HandleInput (Task_HandleYesNoInput (script_menu.c d'Émeraude), même code)
Hask_MultichoiceGridMenu_HandleInput (Task_HandleMultichoiceGridInput (script_menu.c d'Émeraude) : SCR_MENU_CANCEL = MULTI_B_PRESSED (127))
CreatePCMenuWindow (CreatePCMultichoice (script_menu.c de la fusion : PC de LÉO/LANETTE, du joueur, du PROF. CHEN, Panthéon de la région) ; police et lignes de RF avec MENUS = KANTO)
Task_ScriptShowMonPic (Task_PokemonPicWindow (script_menu.c d'Émeraude), même code (fenêtre en data[6]))
PicboxWait (IsPicboxClosed (script_menu.c d'Émeraude), même code)
DestroyScriptMenuWindow (ClearToTransparentAndRemoveWindow (script_menu.c d'Émeraude) ; le ClearWindowTilemap de RF est fait par ClearStdWindowAndFrameToTransparent)

### battle_interface.c (7)
SpriteCB_PartySummaryBall_OnBattleStart (SpriteCB_StatusSummaryBalls_Enter (battle_interface.c), même code)
SpriteCB_PartySummaryBall_Exit (SpriteCB_StatusSummaryBalls_Exit (battle_interface.c), / 16 = >> 4, DISPLAY_WIDTH + 8 = 248)
SpriteCB_PartySummaryBall_OnSwitchout (SpriteCB_StatusSummaryBalls_OnSwitchout (battle_interface.c), même code)
DrawHealthbarOntoScreen (Debug_TestHealthBar_Helper (battle_interface.c), même dessin)
GetReceivedValueInPixels (GetScaledExpFraction (battle_interface.c), même calcul)
SpriteCB_PartySummaryBar → SpriteCB_StatusSummaryBar_Enter (battle_interface.c)
SpriteCB_PartySummaryBar_Exit → SpriteCB_StatusSummaryBar_Exit (battle_interface.c)

### battle_main.c (6)
SpriteCB_PlayerThrowInit (SpriteCB_TrainerThrowObject (battle_main.c), même code)
UpdatePlayerPosInThrowAnim (AnimSetCenterToCornerVecX (battle_main.c), même code)
SpriteCB_PlayerThrowUpdate (SpriteCB_TrainerThrowObject_Main (battle_main.c), même code)
BattleIntroPlayerSendsOutMonAnimation (BattleIntroPlayer1SendsOutMonAnimation (battle_main.c), + combats enregistrés d'Émeraude)
UpdatePartyOwnerOnSwitch_NonMulti (SwitchPartyOrder (battle_main.c), même code)
SpriteCB_AllyMon → SpriteCB_BattleSpriteStartSlideLeft (battle_main.c)

### fldeff_rocksmash.c (6)
CreateFieldEffectShowMon (CreateFieldMoveTask (fldeff_rocksmash.c), même code)
Task_FieldEffectShowMon_Init (Task_DoFieldMove_Init (fldeff_rocksmash.c), StartPlayerAvatarSummonMonForFieldMoveAnim = SetPlayerAvatarFieldMove)
Task_FieldEffectShowMon_WaitPlayerAnim (Task_DoFieldMove_ShowMonAfterPose (fldeff_rocksmash.c), même code)
Task_FieldEffectShowMon_WaitFldeff (Task_DoFieldMove_WaitForMon (fldeff_rocksmash.c), même code)
Task_FieldEffectShowMon_Cleanup (Task_DoFieldMove_RunFunc (fldeff_rocksmash.c), pointeur (port 64 bits))
FieldCallback_UseRockSmash (FieldCallback_RockSmash (fldeff_rocksmash.c), scripts équivalents)

### battle_anim_mons.c (5)
InitBattleAnimBg (ClearBattleAnimBg (battle_anim_mons.c), même code)
ToggleBg3Mode (UpdateAnimBg3ScreenSize (battle_anim_mons.c), + concours d'Émeraude)
PlayerThrowBall_StartAnimLinearTranslation (StartAnimLinearTranslation (battle_anim_mons.c), même code)
PlayerThrowBall_AnimTranslateLinear_WithFollowup (AnimTranslateLinear_WithFollowup_SetCornerVecX (battle_anim_mons.c), même code)
SetGreyscaleOrOriginalPalette (SetGrayscaleOrOriginalPalette (battle_anim_mons.c), même code)

### field_message_box.c (5)
Task_DrawFieldMessageBox (Task_DrawFieldMessage (field_message_box.c), + journal de RF ; cadre selon l'option DIALOGUE)
CreateTask_DrawFieldMessageBox (CreateTask_DrawFieldMessage (field_message_box.c), même code)
DestroyTask_DrawFieldMessageBox (DestroyTask_DrawFieldMessage (field_message_box.c), TASK_NONE = 255)
ExpandStringAndStartDrawFieldMessageBox (ExpandStringAndStartDrawFieldMessage (field_message_box.c), même code)
StartDrawFieldMessageBox (StartDrawFieldMessage (field_message_box.c), même code)

### metatile_behavior.c (5)
MetatileBehavior_IsSandOrShallowFlowingWater (kanto_battle_bg.c (Kanto_BattleSetup_GetTerrainId), écrite en ligne)
MetatileBehavior_IsWarpDoor_2 (MetatileBehavior_IsDoor (metatile_behavior.c), MB_WARP_DOOR importé en MB_ANIMATED_DOOR)
MetatileBehavior_IsSurfable (MetatileBehavior_IsSurfableWaterOrUnderwater (metatile_behavior.c), kanto_battle_bg.c)
MetatileBehavior_IsDeepWaterTerrain (MetatileBehavior_IsDeepOrOceanWater (metatile_behavior.c), décor de combat de Kanto (kanto_battle_bg.c) ; MB_FAST_WATER importé en MB_OCEAN_WATER)
TestMetatileAttributeBit (sTileBitAttributes (metatile_behavior.c), même table de bits)

### field_effect_helpers.c (4)
SynchroniseSurfAnim (SynchronizeSurfAnim (field_effect_helpers.c), + diagonales d'Émeraude)
SynchroniseSurfPosition (SynchronizeSurfPosition (field_effect_helpers.c), cases du sprite rangées autrement)
UpdateAshFieldEffect_Step0 → UpdateAshFieldEffect_Wait (field_effect_helpers.c)
UpdateAshFieldEffect_Step1 → UpdateAshFieldEffect_Show (field_effect_helpers.c)

### fldeff_cut.c (4)
SpriteCallback_CutGrass_Init (CutGrassSpriteCallback1 (fldeff_cut.c), même code)
SpriteCallback_CutGrass_Run (CutGrassSpriteCallback2 (fldeff_cut.c), même calcul)
SpriteCallback_CutGrass_Cleanup (CutGrassSpriteCallbackEnd (fldeff_cut.c), + MEW de l'Île Lointaine (Hoenn))
FieldMoveCallback_CutGrass → StartCutGrassFieldEffect (fldeff_cut.c)

### battle_ai_script_commands.c (3)
Cmd_if_would_go_first (Cmd_if_user_goes (battle_ai_script_commands.c), même code)
Cmd_if_would_not_go_first (Cmd_if_user_goes (battle_ai_script_commands.c), même code)
Cmd_count_alive_pokemon (Cmd_count_usable_party_mons (battle_ai_script_commands.c), position ^ BIT_FLANK = BATTLE_PARTNER)

### battle_script_commands.c (3)
Cmd_callterrainattack (Cmd_callenvironmentattack (battle_script_commands.c), terrain = environment)
Cmd_cureifburnedparalysedorpoisoned (Cmd_cureifburnedparalyzedorpoisoned (battle_script_commands.c), tailles d'arguments du port 64 bits)
Cmd_settypetoterrain (Cmd_settypetoenvironment (battle_script_commands.c), terrain = environment)

### battle_setup.c (3)
StartRoamerBattle (BattleSetup_StartRoamerBattle (battle_setup.c), musique des légendaires de RF à Kanto (portée 2026-11-02))
StartScriptedWildBattle (BattleSetup_StartScriptedWildBattle (battle_setup.c), BATTLE_TYPE_WILD_SCRIPTED de RF (gBattleWildScriptedFrlg))
StartWildBattle → BattleSetup_StartWildBattle (battle_setup.c)

### bike.c (3)
GetBikeTransitionId (CheckMovementInputAcroBike (bike.c), même aiguillage)
BikeTransition_TurnDirection (AcroBikeTransition_TurnDirection (bike.c), même code)
CanBikeFaceDirectionOnRail (CanBikeFaceDirOnMetatile (bike.c), même code)

### event_object_lock.c (3)
Task_WaitPlayerAndTargetNPCStopMoving (Task_FreezeSelectedObjectAndPlayer (event_object_lock.c), HandleEnforcedLookDirectionOnPlayerStopMoving = PlayerFreeze (même code))
Task_WaitPlayerStopMoving → Task_FreezePlayer (event_object_lock.c)
walkrun_is_standing_still → IsPlayerStandingStill (event_object_lock.c)

### field_camera.c (3)
tilemap_move_something (AddCameraTileOffset (field_camera.c), même code)
coords8_add (AddCameraPixelOffset (field_camera.c), même code)
FieldCameraGetPixelOffsetAtGround (GetCameraOffsetWithPan (field_camera.c), même code)

### field_fadetransition.c (3)
Task_WaitFadeAndCreateStartMenuTask (Task_WaitForFadeShowStartMenu (field_screen_effect.c), même code)
FieldCB_SafariZoneRanOutOfBalls (FieldCB_ReturnToFieldNoScriptCheckMusic (field_screen_effect.c), même enchaînement)
Task_ContinueScriptUnionRoom → Task_WaitForUnionRoomFade (field_screen_effect.c)

### battle_anim_mon_movement.c (2)
AnimTask_ShakeMon2Step (AnimTask_ShakeMon2_Step (battle_anim_mon_movement.c), même code)
AnimTask_SwayMon_Step (AnimTask_SwayMonStep (battle_anim_mon_movement.c), même code)

### battle_anim_normal.c (2)
AnimShakeMonOrBattleTerrain_Step (AnimShakeMonOrBattlePlatforms_Step (battle_anim_normal.c), même code)
AnimShakeMonOrBattleTerrain_UpdateCoordOffsetEnabled (AnimShakeMonOrBattlePlatforms_UpdateCoordOffsetEnabled (battle_anim_normal.c), même code)

### battle_controller_opponent.c (2)
OpponentHandlePlayFanfare (OpponentHandlePlayFanfareOrBGM (battle_controller_opponent.c), même code)
OpponentHandleCmd55 → OpponentHandleEndLinkBattle (battle_controller_opponent.c)

### battle_controller_player.c (2)
PlayerHandlePlayFanfare (PlayerHandlePlayFanfareOrBGM (battle_controller_player.c), même code)
PlayerHandleCmd55 (PlayerHandleEndLinkBattle (battle_controller_player.c), + combats enregistrés d'Émeraude)

### battle_controllers.c (2)
SetUpBattleVars (SetUpBattleVarsAndBirchZigzagoon (battle_controllers.c), sans le ZIGZATON de Seko)
BtlController_EmitPlayFanfare (BtlController_EmitPlayFanfareOrBGM (battle_controllers.c), même transfert)

### field_control_avatar.c (2)
UpdateHappinessStepCounter (UpdateFriendshipStepCounter (field_control_avatar.c), VAR_HAPPINESS = VAR_FRIENDSHIP)
Task_QuestLogPlayback_OpenStartMenu → Task_OpenStartMenuAfterSignpost (field_control_avatar.c)

### wild_encounter.c (2)
GenerateWildMon (CreateWildMon (wild_encounter.c), avec la lettre des ZARBI de Tanoby de RF)
GenerateFishingEncounter (GenerateFishingWildMon (wild_encounter.c))

### load_save.c (2)
LoadSerializedGame → CopyPartyAndObjectsFromSave (load_save.c)
SaveSerializedGame → CopyPartyAndObjectsToSave (load_save.c)

### mail_data.c (2)
ClearMailData → ClearAllMail (mail_data.c)
ClearMailStruct → ClearMail (mail_data.c)

### math_util.c (2)
Q_8_8_inv → MathUtil_Inv16 (math_util.c)
Q_N_S_div → MathUtil_Div16Shift (math_util.c)

### battle_anim_effects_2.c (1)
AirCutterProjectile_Step1 (AirCutterProjectileStep1 (battle_anim_effects_2.c), -SOUND_PAN_TARGET = SOUND_PAN_ATTACKER + 1)

### battle_anim_utility_funcs.c (1)
AnimTask_GetBattleTerrain (AnimTask_GetBattleEnvironment (battle_anim_utility_funcs.c), terrain = environment)

### battle_intro.c (1)
CopyBattlerSpriteToBg (DrawBattlerOnBg (battle_intro.c), même code)

### battle_util.c (1)
AtkCanceller_UnableToUseMove (AtkCanceler_UnableToUseMove (battle_util.c), canceller = canceler)

### fldeff_strength.c (1)
FieldCB_UseStrength (FieldCallback_Strength (fldeff_strength.c), scripts équivalents)

### heal_location.c (1)
GetHealLocationIndexFromMapGroupAndNum (GetHealLocationIndexByMap (heal_location.c), même code)

### reshow_battle_screen.c (1)
ReshowBattleScreen_TurnOnDisplay (CB2_ReshowBattleScreenAfterMenu (reshow_battle_screen.c), écran de combat rétabli par celui d'Émeraude)

### script.c (1)
ValidateRamScript (ValidateSavedRamScript (script.c), LOCALID_PLAYER = 255)

### battle_anim_fight.c (1)
AnimStompFootStep → AnimStompFoot_Step (battle_anim_fight.c)

### battle_bg.c (1)
CB2_unused → CB2_UnusedBattleInit (battle_bg.c)

### battle_controller_safari.c (1)
SafariHandleCmd55 → SafariHandleEndLinkBattle (battle_controller_safari.c)

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


## Triviale (113) : corps vide ou d'une instruction (« return TRUE; ») : se porte avec son appelant

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


## Morte (105) : jamais appelée ni référencée dans RF

### event_object_movement.c (30)
GetReflectionEffectPaletteSlot, CameraObjectGetFollowedObjectId, GetAcroBunnyHopFrontWheelDirectionAnimNum,
GetWalkSlowestMovementAction, UpdateWalkSlowest (walk_slowest_* jamais utilisé dans RF),
MovementAction_WalkSlowestDown_Step0 (walk_slowest_* jamais utilisé dans RF),
MovementAction_WalkSlowestDown_Step1 (walk_slowest_* jamais utilisé dans RF),
MovementAction_WalkSlowestUp_Step0 (walk_slowest_* jamais utilisé dans RF),
MovementAction_WalkSlowestUp_Step1 (walk_slowest_* jamais utilisé dans RF),
MovementAction_WalkSlowestLeft_Step0 (walk_slowest_* jamais utilisé dans RF),
MovementAction_WalkSlowestLeft_Step1 (walk_slowest_* jamais utilisé dans RF),
MovementAction_WalkSlowestRight_Step0 (walk_slowest_* jamais utilisé dans RF),
MovementAction_WalkSlowestRight_Step1 (walk_slowest_* jamais utilisé dans RF),
UpdateMovementGlide (glide_* jamais utilisé dans RF),
MovementAction_GlideDown_Step1 (glide_down jamais utilisé dans RF),
MovementAction_GlideUp_Step1 (glide_up jamais utilisé dans RF),
MovementAction_GlideLeft_Step1 (glide_left jamais utilisé dans RF),
MovementAction_GlideRight_Step1 (glide_right jamais utilisé dans RF),
FaceDirectionFast (face_*_fast : seul PlayerFaceDirectionFast de RF, jamais appelé),
MovementAction_JumpSpecialWithEffectDown_Step0 (jamais utilisé dans RF),
MovementAction_JumpSpecialWithEffectDown_Step1 (jamais utilisé dans RF),
MovementAction_JumpSpecialWithEffectUp_Step0 (jamais utilisé dans RF),
MovementAction_JumpSpecialWithEffectUp_Step1 (jamais utilisé dans RF),
MovementAction_JumpSpecialWithEffectLeft_Step0 (jamais utilisé dans RF),
MovementAction_JumpSpecialWithEffectLeft_Step1 (jamais utilisé dans RF),
MovementAction_JumpSpecialWithEffectRight_Step0 (jamais utilisé dans RF),
MovementAction_JumpSpecialWithEffectRight_Step1 (jamais utilisé dans RF),
MovementAction_EmoteSmile_Step0 (emote_smile jamais utilisé dans RF),
MovementAction_ShakeHeadOrWalkInPlace_Step0 (seul PlayerShakeHeadOrWalkInPlace de RF, jamais appelé),
UpdateWalkSlowestAnim (walk_slowest_* jamais utilisé dans RF)

### metatile_behavior.c (10)
MetatileBehavior_IsFastWater (jamais appelée dans RF), MetatileBehavior_IsArrowWarp,
MetatileBehavior_IsUnused01, MetatileBehavior_IsUnusedWater, MetatileBehavior_IsWater,
MetatileBehavior_IsCyclingRoadPullDownTileGrass,
MetatileBehavior_IsSnacks (MB_SNACKS dans aucun tileset de RF), MetatileBehavior_IsStrengthButton,
MetatileBehavior_IsImpressiveMachine (MB_IMPRESSIVE_MACHINE dans aucun tileset de RF),
MetatileBehavior_IsVideoGame (MB_VIDEO_GAME dans aucun tileset de RF)

### field_player_avatar.c (7)
PlayerWalkSlower, PlayerGlide, PlayerFaceDirectionFast, PlayerShakeHeadOrWalkInPlace, PlayerAcroWheelieCollide,
PlayerAcroPopWheelie, PlayerAcroWheelieMove

### text_window.c (5)
LoadHelpMessageWindowGfxOnBg, LoadMenuMessageWindowGfxOnBg, LoadSignpostWindowGfxOnBg,
LoadQuestLogWindowTilesOnBg, LoadUserWindowGfxByFrameOnBg

### field_special_scene.c (4)
FieldSpecialScene_Dummy0, FieldSpecialScene_Dummy1, FieldSpecialScene_Dummy2, FieldSpecialScene_Dummy3

### battle_interface.c (3)
UpdateAndDrawHealthbarOntoScreen, CalcNewHealthbarValue, DoDrawHealthbarOntoScreen

### battle_setup.c (3)
EndPokedudeBattle (« Unused » dans RF (StartPokedudeBattle jamais appelé)), StartPokedudeBattle,
SetBattledTrainerFlag2

### math_util.c (3)
Q_8_8_div, Q_N_S_inv, Q_24_8_inv

### menu.c (3)
Unused_ClearTopBarWindow, CreateYesNoMenu2, MultichoiceGrid_PrintItemsCustomOrder

### trainer_card.c (3)
Unref_InitTrainerCard, Unref_InitTrainerCardLink, Unref_InitTrainerCardLink2

### battle_bg.c (2)
CreateUnknownDebugSprite, GetBattleTerrainGfxPtrs

### battle_main.c (2)
SpriteCB_UnusedDebugSprite (jamais utilisé dans RF (debug)),
SpriteCB_UnusedDebugSprite_Step (jamais utilisé dans RF (debug))

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

### battle_transition.c (1)
Task_Spiral (B_TRANSITION_SPIRAL : aucun combat de RF ne l'utilise)

### coins.c (1)
ShowCoinsWindow_Parameterized

### field_control_avatar.c (1)
Unref_ClearHappinessStepCounter

### field_effect_helpers.c (1)
FldEff_UnusedWaterSurfacing (seulement dans la table des effets de RF, jamais lancé)

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


## Link (170) : link / E-Reader : à porter, désactivé

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

### battle_tower.c (7)
Task_WaitBT (Tour de Combat de RF (e-Reader)), SetBattleTowerParty (Tour de Combat de RF (e-Reader)),
SetPlayerBattleTowerRecord (Tour de Combat de RF (e-Reader)),
SetBattleTowerRecordChecksum (Tour de Combat de RF (e-Reader)),
CopyEReaderTrainerName5 (Tour de Combat de RF (e-Reader)),
BufferEReaderTrainerGreeting (Tour de Combat de RF (e-Reader)),
PrintEReaderTrainerFarewellMessage (Tour de Combat de RF (e-Reader))

### cereader_tool.c (6)
ValidateTrainerTowerTrainer, ValidateTrainerTowerData, CEReaderTool_SaveTrainerTower_r,
CEReaderTool_SaveTrainerTower, CEReaderTool_LoadTrainerTower_r, CEReaderTool_LoadTrainerTower

### party_menu.c (6)
DisplayPartyPokemonDataForChooseMultiple (choix de l'équipe des combats link / Tour de RF),
CursorCB_Enter (choix de l'équipe des combats link / Tour de RF),
CursorCB_NoEntry (choix de l'équipe des combats link / Tour de RF),
InitChooseMonsForBattle (choix de l'équipe des combats link / Tour de RF),
Task_ValidateChosenMonsForBattle (choix de l'équipe des combats link / Tour de RF),
Task_ContinueChoosingMonsForBattle (choix de l'équipe des combats link / Tour de RF)

### cable_club.c (5)
AnyConnectedPartnersPlayingRS, CableClub_AskSaveTheGame, EnterTradeSeat, StartWiredCableClubTrade,
GetSeeingLinkPlayerCardMsg

### berry_crush.c (4)
BerryCrush_SetVBlankCallback, BerryCrush_BuildLocalState, printCrushingResults, Task_ShowBerryCrushRankings

### mystery_gift_menu.c (4)
PrintMysteryGiftOrEReaderTopMenu, AddTextPrinterToWindow1, ClearTextWindow, HandleMysteryGiftListMenu

### start_menu.c (4)
SetUpStartMenu_Link (menu Start des combats link de RF),
SetUpStartMenu_UnionRoom (menu Start de l'Union Room de RF),
DoSetUpSaveAfterLinkBattle (sauvegarde après un combat link),
task50_after_link_battle_save (sauvegarde après un combat link)

### battle_controller_link_partner.c (3)
LinkPartnerDummy, LinkPartnerHandleUnknownYesNoBox, LinkPartnerHandlePlayFanfare

### battle_records.c (3)
IndexOfOpponentLinkBattleRecord (records du Club Câble de RF),
IncTrainerCardWinCount (records du Club Câble de RF), IncTrainerCardLossCount (records du Club Câble de RF)

### field_fadetransition.c (3)
DoTeleport2Warp (seul ScrCmd_warpspinenter de RF, pour l'Union Room (cable_club.inc)),
DoUnionRoomWarp (Union Room de RF), Task_Teleport2Warp (seul DoTeleport2Warp)

### link_rfu_2.c (3)
LinkRfu_ForceChangeSpParent, RfuGetErrorInfo, DestroyTask_RfuReconnectWithParent

### trade_scene.c (3)
CheckLinkTimeout, LoadTradeGbaSpriteGfx, TradeBufferOTnameAndNicknames

### union_room_battle.c (3)
SetUpPartiesAndStartBattle, UnionRoomBattle_CreateTextPrinter, UnionRoomBattle_PrintTextOnWindow0

### battle_controller_link_opponent.c (2)
LinkOpponentHandleUnknownYesNoBox, LinkOpponentHandlePlayFanfare

### battle_main.c (2)
LinkBattleComputeBattleTypeFlags (combats link de RF), PrepareOwnMultiPartnerBuffer (combats multi de RF)

### link_rfu_3.c (2)
ZeroName, NameIsEmpty

### metatile_behavior.c (2)
MetatileBehavior_IsPlayerFacingCableClubWirelessMonitor (moniteur sans fil de RF),
MetatileBehavior_IsPlayerFacingBattleRecords (écran des records du Club Câble de RF)

### script_pokemon_util.c (2)
CB2_ReturnFromChooseBattleTowerParty (Tour de Combat de RF (salle e-Reader)),
ReducePlayerPartyToThree (Tour de Combat de RF (salle e-Reader))

### trade.c (2)
CB2_ReturnToTradeMenuFromSummary, CommunicateWhetherMonCanBeTraded

### union_room.c (2)
Leader_DisconnectOnState, ItemPrintFunc_Unused

### berry_fix_program.c (1)
SetScene

### dodrio_berry_picking.c (1)
DBP_LoadStdWindowGfx

### easy_chat.c (1)
EnableRareWord (seul l'Événement Mystère de RF (mystery_event_script.c) débloque des mots rares)

### link.c (1)
SetLinkErrorFromRfu

### mystery_event_script.c (1)
MEventScript_Run

### overworld.c (1)
CreateConfirmLeaveTradeRoomPrompt (Centre d'échange de RF (RunConfirmLeaveCableClubScript d'Émeraude))

### union_room_player_avatar.c (1)
MakeGroupAssemblyAreasPassable

### wireless_communication_status_screen.c (1)
ExitWirelessCommunicationStatusScreen


## Écartée (427) : écartée par décision

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

### party_menu.c (19)
Task_FirstBattleEnterParty_WaitFadeIn (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_DarkenScreen (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_WaitDarken (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_CreatePrinter (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_RunPrinterMsg1 (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_LightenFirstMonIcon (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_WaitLightenFirstMonIcon (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_StartPrintMsg2 (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_RunPrinterMsg2 (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_FadeNormal (tutoriel du premier combat avec CHEN),
Task_FirstBattleEnterParty_WaitFadeNormal (tutoriel du premier combat avec CHEN),
PartyMenu_Oak_PrintText (tutoriel du premier combat avec CHEN (Kanto = post-game)),
FirstBattleEnterParty_CreateWindowAndMsg1Printer (tutoriel du premier combat avec CHEN),
FirstBattleEnterParty_DestroyVoiceoverWindow (tutoriel du premier combat avec CHEN),
SetSwitchedPartyOrderQuestLogEvent (journal de RF), SetSwappedHeldItemQuestLogEvent (journal de RF),
SetUsedFieldMoveQuestLogEvent (journal de RF), SetUsedFlyQuestLogEvent (journal de RF),
OpenPartyMenuInTutorialBattle (tutoriel du premier combat avec CHEN (Kanto = post-game))

### quest_log_player.c (15)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), QuestLogUpdatePlayerSprite,
QuestLogTryRecordPlayerAvatarGfxTransition, QuestLogCallUpdatePlayerSprite, QL_GfxTransition_Normal,
QL_GfxTransition_Bike, QL_GfxTransition_Fish, Task_QLFishMovement, QL_GfxTransition_StartSurf,
QL_GfxTransition_VSSeeker, Task_QLVSSeekerMovement, QL_SetObjectGraphicsId, QL_GfxTransition_StopSurfSouth,
QL_GfxTransition_StopSurfNorth, QL_GfxTransition_StopSurfWest, QL_GfxTransition_StopSurfEast

### wild_encounter.c (13)
DoWildEncounterRateDiceRoll (rencontres d'Émeraude partout (décision 2026-11-02) ; EncounterOddsCheck),
DoWildEncounterRateTest (rencontres d'Émeraude partout (décision 2026-11-02) ; WildEncounterCheck),
GetAbilityEncounterRateModType (rencontres d'Émeraude partout (décision 2026-11-02)),
DoGlobalWildEncounterDiceRoll (rencontres d'Émeraude partout (décision 2026-11-02) ; AllowWildCheckOnNewMetatile),
GetFluteEncounterRateModType (rencontres d'Émeraude partout (décision 2026-11-02) ; ApplyFluteEncounterRateMod),
IsLeadMonHoldingCleanseTag (rencontres d'Émeraude partout (décision 2026-11-02) ; ApplyCleanseTagEncounterRateMod),
SeedWildEncounterRng (rencontres d'Émeraude partout (décision 2026-11-02)),
WildEncounterRandom (rencontres d'Émeraude partout (décision 2026-11-02)),
GetMapBaseEncounterCooldown (rencontres d'Émeraude partout (décision 2026-11-02)),
ResetEncounterRateModifiers (rencontres d'Émeraude partout (décision 2026-11-02)),
HandleWildEncounterCooldown (rencontres d'Émeraude partout (décision 2026-11-02)),
TryStandardWildEncounter (rencontres d'Émeraude partout (décision 2026-11-02) ; StandardWildEncounter),
AddToWildEncounterRateBuff (rencontres d'Émeraude partout (décision 2026-11-02))

### battle_controller_oak_old_man.c (12)
OakOldManHandleInputChooseMove (tutoriel du premier combat avec CHEN (Kanto = post-game)),
PrintOakText_ForPetesSake (conseils de CHEN (Kanto = post-game)),
PrintOakText_InflictingDamageIsKey (conseils de CHEN (Kanto = post-game)),
PrintOakText_LoweringStats (conseils de CHEN (Kanto = post-game)),
PrintOakText_OakNoRunningFromATrainer (conseils de CHEN (Kanto = post-game)),
PrintOakText_WinEarnsPrizeMoney (conseils de CHEN (Kanto = post-game)),
PrintOakText_HowDisappointing (conseils de CHEN (Kanto = post-game)),
PrintOakTextWithMainBgDarkened (conseils de CHEN (Kanto = post-game)),
PrintOakText_KeepAnEyeOnHP (conseils de CHEN (Kanto = post-game)),
OakHandleChooseMove_WaitDma3 (tutoriel du premier combat avec CHEN (Kanto = post-game)),
BtlCtrl_OakOldMan_TestState2Flag (messages du tutoriel de CHEN (Kanto = post-game)),
BtlCtrl_OakOldMan_SetState2Flag (messages du tutoriel de CHEN (Kanto = post-game))

### field_player_avatar.c (4)
CreateStopSurfingTask_NoMusicChange (journal de RF (quest_log_player.c, seul appelant)),
Fishing5 (variante RF : Émeraude gardée (Fishing_ShowDots : un point toutes les 8 images et A arrête ; RF 12 images, pas d'arrêt) ; docs/VARIANTES-RF.md),
Fishing6 (variante RF : Émeraude gardée (Fishing_CheckForBite : VENTOUSE et GLUE aident à ferrer ; RF non) ; docs/VARIANTES-RF.md),
Fishing7 (variante RF : Émeraude gardée (Fishing_GotBite : « Oh! Ça mord! » puis A à temps ; RF ferre tout seul) ; docs/VARIANTES-RF.md)

### overworld.c (4)
CB2_SetUpOverworldForQLPlaybackWithWarpExit (journal de RF), CB2_LoadMapForQLPlayback (journal de RF),
DoLoadMap_QLPlayback (journal de RF), LoadMap_QLPlayback (journal de RF)

### quest_log_battle.c (3)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), TrySetQuestLogBattleEvent,
TrySetQuestLogLinkBattleEvent, GetLinkMultiBattlePlayerIndexes

### quest_log_objects.c (3)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), QL_RecordObjects, QL_LoadObjects,
QL_TryStopSurfing

### event_object_movement.c (3)
QL_UpdateObjectEventCurrentMovement (journal de RF (quest_log.c)),
QuestLogObjectEventExecHeldMovementAction (journal de RF (quest_log.c)),
ObjectEventCheckForReflectiveSurface (variante RF : Émeraude gardée (ObjectEventGetNearbyReflectionType : zone selon la taille du sprite ; RF 1×2 cases, pareil pour le joueur) ; docs/VARIANTES-RF.md)

### field_specials.c (3)
DoDeoxysTriangleInteraction (Île Naissance de RF : celle d'Émeraude (DoDeoxysRockInteraction)),
MoveDeoxysObject (Île Naissance de RF : celle d'Émeraude (ChangeDeoxysRockLevel)),
Task_WaitDeoxysFieldEffect (Île Naissance de RF : celle d'Émeraude (WaitForDeoxysRockMovement))

### help_message.c (1)
— aide L/R de RF (Kanto = post-game, décision 2026-11-02), MapNamePopupWindowIdSetDummy

### field_effect.c (1)
SpriteCB_FlyBirdWithPlayer (variante RF : Émeraude gardée (SpriteCB_FlyBirdSwoopDown : arc 140, pas de 4 ; RF 180, pas de 2) ; docs/VARIANTES-RF.md)

### field_effect_helpers.c (1)
CreateBobbingEffect (variante RF : Émeraude gardée (UpdateBobbingEffect : le Pokémon du Surf monte et descend 2× plus vite que dans RF) ; docs/VARIANTES-RF.md)

### field_screen_effect.c (1)
DoOutwardBarnDoorWipe (variante RF : Émeraude gardée (sortie d'un bâtiment : fondu d'Émeraude ; RF ouvre l'écran en portes de grange, Task_ExitDoor) ; docs/VARIANTES-RF.md)

### item.c (1)
TrySetObtainedItemQuestLogEvent (journal de RF)

### item_use.c (1)
ItemUse_SetQuestLogEvent (journal de RF)

### script.c (1)
IsQuestLogInputDpad (journal de RF)

### script_menu.c (1)
QL_DestroyAbortedDisplay (journal de RF)

### trainer_see.c (1)
TrainerSeeFunc_PrepareToEngage (variante RF : Émeraude gardée (PlayerFaceApproachingTrainer : le joueur se tourne vers le dresseur ; RF non) ; docs/VARIANTES-RF.md)
