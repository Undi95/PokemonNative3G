# Inventaire des fonctions de Rouge Feu absentes de la fusion

> Généré par `tools/cartographie.py` — ne pas éditer à la main.

Les 1621 fonctions propres à Rouge Feu absentes de la fusion par leur nom (`fonctions-rf-absentes.md`), chacune dans une seule catégorie. « Équivalente » est une preuve (même suite de jetons ; seuls diffèrent des noms de fonctions déjà prouvées équivalentes, jusqu'au point fixe, ou une variante Kanto du même nom) ; « à vérifier » et « manquante » se lisent à la main, puis se classent dans `tools/carto_classement.txt` avec leur preuve.

| Catégorie | Sens | Fonctions |
|---|---|---|
| manquante | rien de proche dans la fusion : à porter | 0 |
| à vérifier | ressemble à une fonction de la fusion (donnée) sans en être prouvée la même : à lire | 0 |
| équivalente | prouvée : même code sous un autre nom (seuls diffèrent des noms eux-mêmes équivalents) | 708 |
| triviale | corps vide ou d'une instruction (« return TRUE; ») : se porte avec son appelant | 111 |
| morte | jamais appelée ni référencée dans RF | 149 |
| link | link / E-Reader : à porter, désactivé | 0 |
| écartée | écartée par décision | 653 |

## Manquante (0) : rien de proche dans la fusion : à porter


## À vérifier (0) : ressemble à une fonction de la fusion (donnée) sans en être prouvée la même : à lire


## Équivalente (708) : prouvée : même code sous un autre nom (seuls diffèrent des noms eux-mêmes équivalents)

### field_effect.c (83)
FieldEffectScript_LoadFadedPal (FieldEffectScript_LoadFadedPalette (field_effect.c d'Émeraude) : + teinte du journal de RF, écartée)
FieldEffectScript_LoadPal (FieldEffectScript_LoadPalette (field_effect.c d'Émeraude) : + teinte du journal de RF, écartée)
PokeballGlowEffect_FlashFirstThree (PokeballGlowEffect_Flash1 (field_effect.c), 0x1007 = FLDEFF_PAL_TAG_POKEBALL_GLOW, >= 3 = > 2)
FallWarpEffect_1 (FallWarpEffect_Init (field_effect.c), même code)
FallWarpEffect_2 (FallWarpEffect_WaitWeather (field_effect.c), même code)
FallWarpEffect_4 (FallWarpEffect_Fall (field_effect.c), même code)
FallWarpEffect_6 (FallWarpEffect_CameraShake (field_effect.c), même code)
FallWarpEffect_7 (FallWarpEffect_End (field_effect.c de la fusion) : eau des Îles Écume portée le 2026-11-02 (scénario kanto_seafoam_current))
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
ShowMonEffect_Outdoors_5 (FieldMoveShowMonOutdoorsEffect_ShrinkBanner (field_effect.c d'Émeraude), même code)
ShowMonEffect_Outdoors_6 (FieldMoveShowMonOutdoorsEffect_RestoreBg (field_effect.c), WIN_RANGE(0, 241) = DISPLAY_WIDTH + 1)
ShowMonEffect_Outdoors_7 (FieldMoveShowMonOutdoorsEffect_End (field_effect.c d'Émeraude) : InitTextBoxGfxAndPrinters = Menu_LoadStdPal + fonds remis)
VBlankCB_ShowMonEffect_Outdoors (VBlankCB_FieldMoveShowMonOutdoors (field_effect.c), pointeur, cases de tâche)
LoadFieldMoveStreaksTilemapToVram (LoadFieldMoveOutdoorStreaksTilemap (field_effect.c), 10 * 32 = ARRAY_COUNT(sFieldMoveStreaksOutdoors_Tilemap))
Task_ShowMon_Indoors (Task_FieldMoveShowMonIndoors (field_effect.c), table appariée)
ShowMonEffect_Indoors_1 (FieldMoveShowMonIndoorsEffect_Init (field_effect.c), pointeur de VBlank (port 64 bits))
ShowMonEffect_Indoors_2 (FieldMoveShowMonIndoorsEffect_LoadGfx (field_effect.c), même code)
ShowMonEffect_Indoors_3 (FieldMoveShowMonIndoorsEffect_SlideBannerOn (field_effect.c d'Émeraude), mêmes fenêtres)
ShowMonEffect_Indoors_4 (FieldMoveShowMonIndoorsEffect_WaitForMon (field_effect.c), même code)
ShowMonEffect_Indoors_5 (FieldMoveShowMonIndoorsEffect_RestoreBg (field_effect.c), RF remet aussi WININ (invisible : fenêtres coupées))
ShowMonEffect_Indoors_6 (FieldMoveShowMonIndoorsEffect_SlideBannerOff (field_effect.c), même code)
ShowMonEffect_Indoors_7 (FieldMoveShowMonIndoorsEffect_End (field_effect.c d'Émeraude) : InitTextBoxGfxAndPrinters = Menu_LoadStdPal + fonds remis)
VBlankCB_ShowMonEffect_Indoors (VBlankCB_FieldMoveShowMonIndoors (field_effect.c), pointeur (port 64 bits))
Task_FldEffUseSurf (Task_SurfFieldEffect (field_effect.c), table appariée)
UseSurfEffect_2 (SurfFieldEffect_FieldMovePose (field_effect.c), même code)
UseSurfEffect_3 (SurfFieldEffect_ShowMon (field_effect.c), case de tâche, 0x80000000 = 1 << 31)
UseSurfEffect_4 (SurfFieldEffect_JumpOnSurfBlob (field_effect.c), PLAYER_AVATAR_GFX_RIDE de RF = PLAYER_AVATAR_STATE_SURFING)
UseSurfEffect_5 (SurfFieldEffect_End (field_effect.c), + aide de RF)
DoBirdSpriteWithPlayerAffineAnim (étapes de Vol d'Émeraude (FlyOutFieldEffect_*, FlyInFieldEffect_*) ; l'arc de RF : VARIANTES-RF.md)
TryChangeBirdSprite (FlyInFieldEffect_* d'Émeraude (fin de l'agrandissement de l'oiseau))
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

### start_menu.c (43)
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

### battle_anim_special.c (29)
AnimTask_IsBallBlockedByTrainerOrDodged (AnimTask_IsBallBlockedByTrainer (battle_anim_throw.c), switch au lieu de if, mêmes cas)
AnimTask_ThrowBallSpecial (AnimTask_ThrowBall_StandingTrainer (battle_anim_throw.c), vieil homme compris (IsOldManTutorialBattle))
AnimTask_ThrowBallSpecial_PlaySfx (AnimTask_ThrowBall_StandingTrainer_Step (battle_anim_throw.c), même enchaînement)
SpriteCB_ThrowBall_Init (SpriteCB_Ball_Throw (battle_anim_throw.c), même code (sTransl_* = data[1..5]))
SpriteCB_ThrowBall_ArcFlight (SpriteCB_Ball_Arc (battle_anim_throw.c), même code)
SpriteCB_ThrowBall_TenFrameDelay (SpriteCB_Ball_MonShrink (battle_anim_throw.c d'Émeraude), même code (sTimer = data[5] à cet endroit))
SpriteCB_ThrowBall_ShrinkMon (SpriteCB_Ball_MonShrink_Step (battle_anim_throw.c), même code)
SpriteCB_ThrowBall_InitialFall (SpriteCB_Ball_Bounce (battle_anim_throw.c), même code (champs nommés))
SpriteCB_ThrowBall_Bounce (SpriteCB_Ball_Bounce_Step (battle_anim_throw.c), même code (états nommés))
SpriteCB_ThrowBall_InitShake (SpriteCB_Ball_Wobble (battle_anim_throw.c d'Émeraude), même code (sTimer = data[3] à cet endroit))
SpriteCB_ThrowBall_DoShake (SpriteCB_Ball_Wobble_Step (battle_anim_throw.c), même code (états et animations affines nommés))
SpriteCB_ThrowBall_DelayThenBreakOut (SpriteCB_Ball_Release (battle_anim_throw.c), même code (sTimer = data[5] à cet endroit))
SpriteCB_ThrowBall_InitClick (SpriteCB_Ball_Capture (battle_anim_throw.c), même code)
SpriteCB_ThrowBall_DoClick (SpriteCB_Ball_Capture_Step (battle_anim_throw.c), même code)
SpriteCB_ThrowBall_FinishClick (SpriteCB_Ball_FadeOut (battle_anim_throw.c), même code)
CreateStarsWhenBallClicks (MakeCaptureStars (battle_anim_throw.c), même code (cases nommées))
SpriteCB_ThrowBall_BeginBreakOut (SpriteCB_Ball_Release_Step (battle_anim_throw.c), BATTLER_AFFINE_EMERGE = 1)
SpriteCB_ThrowBall_RunBreakOut (SpriteCB_Ball_Release_Wait (battle_anim_throw.c), même code)
TrainerBallBlock (SpriteCB_Ball_Block (battle_anim_throw.c), même code)
TrainerBallBlock2 (SpriteCB_Ball_Block_Step (battle_anim_throw.c), DISPLAY_HEIGHT = 160 ; BattleAnimObj_SignalEnd = DestroySpriteAfterOneFrame)
AnimTask_ShinySparkles (Task_ShinyStars (battle_anim_throw.c), même code (& 3 = % 4, SOUND_PAN_ATTACKER = -64))
SpriteCB_ShinySparkles_1 (SpriteCB_ShinyStars_Encircle (battle_anim_throw.c), même code)
SpriteCB_ShinySparkles_2 (SpriteCB_ShinyStars_Diagonal (battle_anim_throw.c d'Émeraude), même code)
SpriteCB_SafariBaitOrRock_Init (SpriteCB_PokeBlock_Throw (battle_anim_throw.c), même code ; gSafariBaitSpriteTemplate et gSafariRockTemplate l'utilisent)
SpriteCB_SafariBaitOrRock_WaitPlayerThrow (SpriteCB_PokeBlock_LiftArm (battle_anim_throw.c), même code)
SpriteCB_SafariBaitOrRock_ArcFlight (SpriteCB_PokeBlock_Arc (battle_anim_throw.c), même code)
AnimTask_ShinySparkles_WaitSparkles → Task_ShinyStars_Wait (battle_anim_throw.c)
AnimTask_ThrowBall_WaitAnimObjComplete → AnimTask_ThrowBall_Step (battle_anim_throw.c)
BattleAnimObj_SignalEnd → DestroySpriteAfterOneFrame (battle_anim_throw.c)

### field_player_avatar.c (25)
player_step (PlayerStep (field_player_avatar.c), dalles tournantes de RF déjà dedans ; + Vélo Cross d'Émeraude)
PlayerAvatarTransition_Bike (PlayerAvatarTransition_MachBike / AcroBike (field_player_avatar.c), sprite du vélo et BikeClearState (un seul vélo, celui de Hoenn) ; journal écarté)
StartPlayerAvatarSummonMonForFieldMoveAnim (SetPlayerAvatarFieldMove (field_player_avatar.c), PLAYER_AVATAR_GFX_FIELD_MOVE = STATE_FIELD_MOVE)
GetPlayerAvatarVsSeekerGfxId (StartPlayerAvatarVsSeekerAnim (field_player_avatar.c), table sPlayerAvatarVsSeekerGfxIds (à pied ou à vélo))
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
GetRandomWordFromGroup (GetRandomEasyChatWordFromGroup (easy_chat.c), un dictionnaire)
GetRandomWordFromAnyGroup (GetRandomEasyChatWordFromUnlockedGroup (easy_chat.c), un dictionnaire)
GetNumUnlockedTrendySayings (GetNumTrendySayingsUnlocked (easy_chat.c), un dictionnaire)
GetRandomECPokemon (GetRandomUnlockedEasyChatPokemon (easy_chat.c), un dictionnaire)
InitEasyChatSelection (InitEasyChatScreenWordData (easy_chat.c), KEC_InitEasyChatSelection)
DestroyEasyChatSelectionData (FreeEasyChatScreenWordData (easy_chat.c), KEC_DestroyEasyChatSelectionData)
PopulateECGroups (SetUnlockedEasyChatGroups (easy_chat.c), même déblocage ; + PHRASES TENDANCE d'Émeraude (les deux écrans d'Easy Chat lisent ces groupes))
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

### trainer_see.c (14)
TrainerApproachPlayer (InitTrainerApproachTask (trainer_see.c), + deux dresseurs d'Émeraude)
StartTrainerApproachWithFollowupTask (StartTrainerApproach (trainer_see.c), + deux dresseurs d'Émeraude)
TrainerSeeFunc_StartExclMark (TrainerExclamationMark (trainer_see.c), états nommés)
TrainerSeeFunc_BeginJumpOutOfAsh (PopOutOfAshBuriedTrainer (trainer_see.c), FLDEFF_POP_OUT_OF_ASH = FLDEFF_ASH_PUFF)
TrainerSeeFunc_EndJumpOutOfAsh (WaitRevealBuriedTrainer (trainer_see.c), même code)
TrainerSeeFunc_OffscreenAboveTrainerCreateCameraObj (OffscreenAboveTrainerCreateCameraObj (trainer_see.c), MAP_OFFSET = 7)
TrainerSeeFunc_OffscreenAboveTrainerCameraObjMoveUp (OffscreenAboveTrainerCameraObjMoveUp (trainer_see.c), même code)
TrainerSeeFunc_OffscreenAboveTrainerCameraObjMoveDown (OffscreenAboveTrainerCameraObjMoveDown (trainer_see.c), même code)
Task_RevealTrainer_RunTrainerSeeFuncList (Task_RunTrainerSeeFuncList (trainer_see.c), pointeur (port 64 bits))
MovementAction_RevealTrainer_RunTrainerSeeFuncList (SetBuriedTrainerMovement (trainer_see.c), même rôle (dresseur caché dans le sable))
FldEff_ExclamationMarkIcon1 (FldEff_ExclamationMarkIcon (trainer_see.c), sprite des émoticônes de Kanto)
TrainerSeeFunc_WaitExclMark → WaitTrainerExclamationMark (trainer_see.c)
TrainerSeeFunc_WaitJumpOutOfAsh → JumpInPlaceBuriedTrainer (trainer_see.c)
TrainerSeeFunc_WaitRemoveDisguise → WaitRevealDisguisedTrainer (trainer_see.c)

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

### overworld.c (12)
CountBadgesForOverworldWhiteOutLossCalculation (CountRegionBadges (fusion_events.c), badges de la région où l'on est (K.O. de RF, 2026-10-31))
Overworld_ResetStateAfterWhitingOut (Overworld_ResetStateAfterWhiteOut (overworld.c), Piste Cyclable et Parc Safari de Kanto dans Overworld_ResetKantoStateAfterWarp ; drapeaux du journal écartés)
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

### pokemon_storage_system_data.c (12)
MonPlaceChange_MoveCursorDown (MonPlaceChange_CursorDown (pokemon_storage_system.c), même code)
MonPlaceChange_MoveCursorUp (MonPlaceChange_CursorUp (pokemon_storage_system.c d'Émeraude), même code)
SetMovedMonData (SetMovingMonData (pokemon_storage_system.c d'Émeraude), même code)
TrySetDisplayMonData (TryRefreshDisplayMon (pokemon_storage_system.c d'Émeraude), même code)
HandleInput_InBox_Normal (InBoxInput_Normal (pokemon_storage_system.c), même code (INPUT_NONE = 0))
HandleInput_InBox_GrabbingMultiple (InBoxInput_SelectingMultiple (pokemon_storage_system.c d'Émeraude), même code)
HandleInput_InBox_MovingMultiple (InBoxInput_MovingMultiple (pokemon_storage_system.c d'Émeraude), même code)
HandleInput_BoxTitle (HandleInput_OnBox (pokemon_storage_system.c d'Émeraude) : SELECT = ToggleCursorAutoAction (ToggleCursorMultiMoveMode de RF))
AddBoxMenu (AddBoxOptionsMenu (pokemon_storage_system.c), même code)
SetMenuTextsForMon (SetMenuTexts_Mon (pokemon_storage_system.c), même code (CURSOR_AREA_IN_BOX = 0))
SetMenuTextsForItem (SetMenuTexts_Item (pokemon_storage_system.c), même code)
ToggleCursorMultiMoveMode (ToggleCursorAutoAction (pokemon_storage_system.c), même code)

### text.c (12)
FontFunc_NormalCopy1 (FontFunc_Kanto (text.c), même code)
FontFunc_NormalCopy2 (FontFunc_Kanto (text.c), même code)
FontFunc_Male (FontFunc_Kanto (text.c), même code)
FontFunc_Female (FontFunc_Kanto (text.c), même code)
DecompressGlyph_NormalCopy1 (DecompressGlyph_Kanto (text.c), mêmes lettres en français)
GetGlyphWidth_NormalCopy1 (FONT_KANTO (text.c de la fusion : largeurs des lettres de RF))
DecompressGlyph_NormalCopy2 (DecompressGlyph_Kanto (text.c), DecompressGlyph_Normal en français)
GetGlyphWidth_NormalCopy2 (FONT_KANTO (text.c de la fusion : largeurs des lettres de RF))
DecompressGlyph_Male (DecompressGlyph_Kanto (text.c), mêmes lettres en français)
GetGlyphWidth_Male (GetGlyphWidth_Kanto (text.c), même table de largeurs en français)
DecompressGlyph_Female (DecompressGlyph_Kanto (text.c), mêmes lettres en français)
GetGlyphWidth_Female (GetGlyphWidth_Kanto (text.c), même table de largeurs en français)

### daycare.c (11)
DayCare_GetMonNickname (GetMonNickname2 (daycare.c d'Émeraude), même code)
DayCare_GetBoxMonNickname (GetBoxMonNickname (daycare.c d'Émeraude), même code)
CreatedHatchedMon (CreateHatchedMon (egg_hatch.c d'Émeraude) : Émeraude garde aussi la langue de l'œuf)
CB2_EggHatch_0 (CB2_LoadEggHatch (egg_hatch.c d'Émeraude), même code)
CB2_EggHatch_1 (CB2_EggHatch (egg_hatch.c d'Émeraude) ; sprites de RF : PlayCry_Normal puis IsCryFinished, comme RF (scénario egg_hatch_kanto))
SpriteCB_Egg_0 (SpriteCB_Egg_Shake1 (egg_hatch.c d'Émeraude), même code)
SpriteCB_Egg_1 (SpriteCB_Egg_Shake2 (egg_hatch.c d'Émeraude), même code)
SpriteCB_Egg_2 (SpriteCB_Egg_Shake3 (egg_hatch.c d'Émeraude) ; sprites de RF : y2 = y_offset, sprite en y 70, comme RF)
SpriteCB_Egg_3 (SpriteCB_Egg_WaitHatch (egg_hatch.c d'Émeraude), même code)
SpriteCB_Egg_4 (SpriteCB_Egg_Hatch (egg_hatch.c d'Émeraude), même code)
SpriteCB_Egg_5 (SpriteCB_Egg_Reveal (egg_hatch.c d'Émeraude), même code)

### pokemon_storage_system_misc.c (11)
MultiMove_Function_Start (MultiMove_Start (pokemon_storage_system.c d'Émeraude), même code)
MultiMove_Function_ChangeSelection (MultiMove_ChangeSelection (pokemon_storage_system.c d'Émeraude), même code)
MultiMove_Function_GrabSelection (MultiMove_GrabSelection (pokemon_storage_system.c d'Émeraude), même code)
MultiMove_Function_MoveMons (MultiMove_MoveMons (pokemon_storage_system.c), MultiMove_UpdateBg = MultiMove_UpdateMove)
MultiMove_Function_PlaceMons (MultiMove_PlaceMons (pokemon_storage_system.c d'Émeraude), même code (Q_8_8(-1) = -256))
MultiMove_InitBg (MultiMove_InitMove (pokemon_storage_system.c), même code)
Item_FromMonToMoving (TakeItemFromMon (pokemon_storage_system.c d'Émeraude), même code)
Item_SwitchMonsWithMoving (SwapItemsWithMon (pokemon_storage_system.c d'Émeraude), même code)
Item_GiveMovingToMon (GiveItemToMon (pokemon_storage_system.c d'Émeraude), même code)
Item_TakeMons (MoveItemFromMonToBag (pokemon_storage_system.c d'Émeraude), même code)
IsActiveItemMoving (IsMovingItem (pokemon_storage_system.c), MAX_ITEM_ICONS = 3)

### field_weather.c (10)
BuildGammaShiftTables (BuildColorMaps (field_weather.c), même calcul (divisions écrites autrement))
UpdateWeatherGammaShift (UpdateWeatherColorMap (field_weather.c), renommage)
ApplyGammaShift (ApplyColorMap (field_weather.c), renommée (+ sécheresse d'Émeraude))
ApplyGammaShiftWithBlend (ApplyColorMapWithBlend (field_weather.c), renommage)
ApplyDroughtGammaShiftWithBlend (ApplyDroughtColorMapWithBlend (field_weather.c), renommage)
WeatherShiftGammaIfPalStateIdle (ApplyWeatherColorMapIfIdle (field_weather.c), renommage)
WeatherBeginGammaFade (ApplyWeatherColorMapIfIdle_Gradual (field_weather.c), renommage)
FadeSelectedPals (kanto_credits.c (macro FadeSelectedPals) et overworld.c (BeginNormalPaletteFade(0x3FFFFFFF, …)), ses deux appelants de RF)
ApplyWeatherGammaShiftToPal (ApplyWeatherColorMapToPal (field_weather.c), renommage)
SetDroughtGamma (SetDroughtColorMap (field_weather.c), renommage)

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

### field_fadetransition.c (9)
Task_ContinueScript (Task_WaitForFadeAndEnableScriptCtx (field_screen_effect.c), même code)
ExitWarpFadeInScreen (FieldCB_DefaultWarpExit / FieldCB_WarpExitFadeFromBlack (field_screen_effect.c), le même fondu avant SetUpWarpExitTask (portes : variante RF DoOutwardBarnDoorWipe))
Task_WaitFadeAndCreateStartMenuTask (Task_WaitForFadeShowStartMenu (field_screen_effect.c), même code)
FadeTransition_FadeInOnReturnToStartMenu (ReturnToFieldOpenStartMenu (field_screen_effect.c), même code)
Task_SafariZoneRanOutOfBalls (Task_ReturnToFieldNoScript (field_screen_effect.c), ClearPlayerHeldMovementAndUnfreezeObjectEvents = ScriptUnfreezeObjectEvents (même code))
FieldCB_SafariZoneRanOutOfBalls (FieldCB_ReturnToFieldNoScriptCheckMusic (field_screen_effect.c), même enchaînement)
Task_Teleport2Warp (Task_WarpAndLoadMap (field_screen_effect.c), + effacement de la Tour Mirage (Hoenn) ; DoWarp, DoDiveWarp et Task_DoorWarp de RF l'utilisent aussi)
Task_DoorWarp (Task_DoDoorWarp (field_screen_effect.c), même code (le cas 5 de RF n'est jamais atteint))
Task_ContinueScriptUnionRoom → Task_WaitForUnionRoomFade (field_screen_effect.c)

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

### new_menu_helpers.c (9)
DecompressAndCopyTileDataToVram2 (DecompressAndCopyTileDataToVram (menu.c), sauf la borne à la taille décompressée (tilesets de carte : Émeraude copie aussi la suite du tas dans des tuiles que la carte n'affiche pas ; le tas est un tableau, pas de lecture hors objet))
DecompressAndLoadBgGfxUsingHeap2 (DecompressAndLoadBgGfxUsingHeap (menu.c), même borne que DecompressAndCopyTileDataToVram2)
TaskFreeBufAfterCopyingTileDataToVram (task_free_buf_after_copying_tile_data_to_vram (menu.c d'Émeraude), WaitDma3Request = CheckForSpaceForDma3Request)
MallocAndDecompress (malloc_and_decompress (menu.c d'Émeraude), même code)
CopyDecompressedTileDataToVram (copy_decompressed_tile_data_to_vram (menu.c), modes 0 et 1 (les seuls utilisés) identiques)
LoadStdWindowFrameGfx (LoadMessageBoxAndBorderGfx (menu.c), DIALOGUE = KANTO -> LoadKantoMenuMessageWindowGfx (LoadMenuMessageWindowGfx de RF) ; son Menu_LoadStdPal est aussitôt recouvert par la palette du cadre (emplacement 14) ; branche du journal écartée)
DisplayYesNoMenuDefaultNo (DisplayYesNoMenuWithDefault (menu.c) avec 1, OUI/NON de RF avec MENUS = KANTO)
GetTextSpeedSetting (GetPlayerTextSpeedDelay (menu.c d'Émeraude) : + forceMidTextSpeed d'Émeraude)
CreateStartMenuWindow (AddStartMenuWindow (menu.c), gabarit de RF avec MENUS = KANTO (base 0x139 au lieu de 0x13D : voir le commentaire))

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

### battle_main.c (7)
SpriteCB_PlayerThrowInit (SpriteCB_TrainerThrowObject (battle_main.c), même code)
UpdatePlayerPosInThrowAnim (AnimSetCenterToCornerVecX (battle_main.c), même code)
SpriteCB_PlayerThrowUpdate (SpriteCB_TrainerThrowObject_Main (battle_main.c), même code)
BattleIntroOpponentSendsOutMonAnimation (BattleIntroOpponent1SendsOutMonAnimation (battle_main.c), + doubles et combats enregistrés d'Émeraude)
BattleIntroPlayerSendsOutMonAnimation (BattleIntroPlayer1SendsOutMonAnimation (battle_main.c), + combats enregistrés d'Émeraude)
UpdatePartyOwnerOnSwitch_NonMulti (SwitchPartyOrder (battle_main.c), même code)
SpriteCB_AllyMon → SpriteCB_BattleSpriteStartSlideLeft (battle_main.c)

### mailbox_pc.c (7)
MailboxPC_InitBuffers (MailboxMenu_Alloc (menu_specialized.c), même code)
MailboxPC_GetAddWindow (MailboxMenu_AddWindow (menu_specialized.c), fenêtres de RF avec MENUS = KANTO)
MailboxPC_RemoveWindow (MailboxMenu_RemoveWindow (menu_specialized.c), même code)
ItemPrintFunc (MailboxMenu_ItemPrintFunc (menu_specialized.c), police de RF avec MENUS = KANTO)
MailboxPC_InitListMenu (MailboxMenu_CreateList (menu_specialized.c), liste de RF avec MENUS = KANTO)
MailboxPC_AddScrollIndicatorArrows (MailboxMenu_AddScrollArrows (menu_specialized.c), x de RF (0xC2) avec MENUS = KANTO (2026-11-02, scénario kanto_mailbox))
MoveCursorFunc → MailboxMenu_MoveCursorFunc (menu_specialized.c)

### pokemon.c (7)
Battle_PrintStatBoosterEffectMessage (UseStatIncreaseItem (pokemon.c d'Émeraude) : mêmes messages (textes de combat d'Émeraude))
SetMonExpWithMaxLevelCheck (TryIncrementMonLevel (pokemon.c), même plafond d'expérience (pension seulement) ; RF monte de niveau au-delà du seuil (exp >), Émeraude dès le seuil : un pas de pension d'écart)
InitMonSpritesGfx_Mode0 (InitMonSpritesGfx_FullParty (pokemon.c d'Émeraude), même code)
es_sub_8044D1C (échange classe / nom français de BufferStringBattle (battle_message.c) : recherche de {B_TRAINER1_CLASS} puis {B_TRAINER1_NAME})
es_sub_8044D64 (échange classe / nom français de BufferStringBattle (battle_message.c) : échange des deux codes)
Localize_BattleStrings (échange classe / nom français de BufferStringBattle (battle_message.c), étendu à la TEAM ROCKET de Kanto (IsKantoTeamRocketTrainer, 2026-11-02, scénario kanto_rocket_grunt))
GetSecretBaseTrainerNameIndex → GetSecretBaseTrainerClass (pokemon.c)

### battle_anim_mons.c (6)
GetBattleAnimBgDataByPriorityRank (GetBgDataForTransform (battle_anim_mons.c), + Concours d'Émeraude)
InitBattleAnimBg (ClearBattleAnimBg (battle_anim_mons.c), même code)
ToggleBg3Mode (UpdateAnimBg3ScreenSize (battle_anim_mons.c), + concours d'Émeraude)
PlayerThrowBall_StartAnimLinearTranslation (StartAnimLinearTranslation (battle_anim_mons.c), même code)
PlayerThrowBall_AnimTranslateLinear_WithFollowup (AnimTranslateLinear_WithFollowup_SetCornerVecX (battle_anim_mons.c), même code)
SetGreyscaleOrOriginalPalette (SetGrayscaleOrOriginalPalette (battle_anim_mons.c), même code)

### fldeff_rocksmash.c (6)
CreateFieldEffectShowMon (CreateFieldMoveTask (fldeff_rocksmash.c), même code)
Task_FieldEffectShowMon_Init (Task_DoFieldMove_Init (fldeff_rocksmash.c), StartPlayerAvatarSummonMonForFieldMoveAnim = SetPlayerAvatarFieldMove)
Task_FieldEffectShowMon_WaitPlayerAnim (Task_DoFieldMove_ShowMonAfterPose (fldeff_rocksmash.c), même code)
Task_FieldEffectShowMon_WaitFldeff (Task_DoFieldMove_WaitForMon (fldeff_rocksmash.c), même code)
Task_FieldEffectShowMon_Cleanup (Task_DoFieldMove_RunFunc (fldeff_rocksmash.c), pointeur (port 64 bits))
FieldCallback_UseRockSmash (FieldCallback_RockSmash (fldeff_rocksmash.c), scripts équivalents)

### pokemon_storage_system_graphics.c (6)
DestroyAllIconsInColumn (DestroyBoxMonIconsInColumn (pokemon_storage_system.c d'Émeraude), même code)
SetBoxSpeciesAndPersonalities (GetIncomingBoxMonData (pokemon_storage_system.c d'Émeraude), même code)
SpriteCB_MovePartySpriteToNextSlot (SpriteCB_MovePartyMonToNextSlot (pokemon_storage_system.c d'Émeraude), même code)
DoReleaseMonComeBackAnim (ReshowReleaseMon (pokemon_storage_system.c d'Émeraude), même code)
SpriteCB_BoxScrollArrow (SpriteCB_Arrow (pokemon_storage_system.c d'Émeraude), même code)
GetMonIconPriorityByCursorArea → GetMonIconPriorityByCursorPos (pokemon_storage_system.c)

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

### battle_ai_script_commands.c (4)
Cmd_if_would_go_first (Cmd_if_user_goes (battle_ai_script_commands.c), même code)
Cmd_if_would_not_go_first (Cmd_if_user_goes (battle_ai_script_commands.c), même code)
Cmd_count_alive_pokemon (Cmd_count_usable_party_mons (battle_ai_script_commands.c), position ^ BIT_FLANK = BATTLE_PARTNER)
Cmd_if_level_compare (Cmd_if_level_cond (battle_ai_script_commands.c), gBattlerAttacker = sBattler_AI pendant l'IA)

### battle_anim_normal.c (4)
AnimShakeMonOrBattleTerrain (AnimShakeMonOrBattlePlatforms (battle_anim_normal.c), renommée)
AnimShakeMonOrBattleTerrain_Step (AnimShakeMonOrBattlePlatforms_Step (battle_anim_normal.c), même code)
AnimShakeMonOrBattleTerrain_UpdateCoordOffsetEnabled (AnimShakeMonOrBattlePlatforms_UpdateCoordOffsetEnabled (battle_anim_normal.c), même code)
AnimTask_ShakeBattleTerrain (AnimTask_ShakeBattlePlatforms (battle_anim_normal.c), renommée (macro shake_battle_platforms))

### battle_setup.c (4)
StartRoamerBattle (BattleSetup_StartRoamerBattle (battle_setup.c), musique des légendaires de RF à Kanto (portée 2026-11-02))
StartScriptedWildBattle (BattleSetup_StartScriptedWildBattle (battle_setup.c), BATTLE_TYPE_WILD_SCRIPTED de RF (gBattleWildScriptedFrlg))
StartTrainerBattle (BattleSetup_StartTrainerBattle (battle_setup.c), + Pyramide, Colline d'Entraînement et doubles d'Émeraude ; combat-tutoriel du rival (CHEN) écarté)
StartWildBattle → BattleSetup_StartWildBattle (battle_setup.c)

### bike.c (4)
GetBikeTransitionId (CheckMovementInputAcroBike (bike.c), même aiguillage)
BikeTransition_TurnDirection (AcroBikeTransition_TurnDirection (bike.c), même code)
MetatileBehaviorForbidsBiking (IsRunningDisallowedByMetatile (bike.c), même test)
CanBikeFaceDirectionOnRail (CanBikeFaceDirOnMetatile (bike.c), même code)

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

### mail_data.c (4)
GiveMailToMon2 (GiveMailToMon (mail_data.c d'Émeraude), même code)
TakeMailFromMon2 (TakeMailFromMonAndSave (mail_data.c d'Émeraude), même code)
ClearMailData → ClearAllMail (mail_data.c)
ClearMailStruct → ClearMail (mail_data.c)

### text_window.c (4)
LoadUserWindowGfx2 (LoadUserWindowBorderGfx (text_window.c d'Émeraude), même code)
LoadMenuMessageWindowGfx (LoadKantoMenuMessageWindowGfx (text_window.c de la fusion), cadre de RF)
LoadUserWindowGfxByFrame (LoadWindowGfx (text_window.c d'Émeraude) : gUserFrames = sWindowFrames (cadres des deux jeux))
LoadUserWindowGfx (LoadUserWindowBorderGfx (text_window.c d'Émeraude), même code)

### battle_gfx_sfx_util.c (3)
DecompressTrainerBackPalette (DecompressTrainerBackPic (battle_gfx_sfx_util.c), qui charge aussi la palette)
FreeTrainerFrontPicPaletteAndTile (FreeTrainerFrontPicPalette (battle_gfx_sfx_util.c d'Émeraude) : Émeraude ne charge pas l'image du dresseur en feuille, DestroySprite libère)
BattleInterfaceSetWindowPals (FillAroundBattleWindows (battle_gfx_sfx_util.c), 1re boucle ; la 2e (18 tiles à 0x600, voix off du Pokédude) ajoutée le 2026-11-03 avec BOITES COMBAT = KANTO)

### battle_script_commands.c (3)
Cmd_callterrainattack (Cmd_callenvironmentattack (battle_script_commands.c), terrain = environment)
Cmd_cureifburnedparalysedorpoisoned (Cmd_cureifburnedparalyzedorpoisoned (battle_script_commands.c), tailles d'arguments du port 64 bits)
Cmd_settypetoterrain (Cmd_settypetoenvironment (battle_script_commands.c), terrain = environment)

### event_object_lock.c (3)
Task_WaitPlayerAndTargetNPCStopMoving (Task_FreezeSelectedObjectAndPlayer (event_object_lock.c), HandleEnforcedLookDirectionOnPlayerStopMoving = PlayerFreeze (même code))
Task_WaitPlayerStopMoving → Task_FreezePlayer (event_object_lock.c)
walkrun_is_standing_still → IsPlayerStandingStill (event_object_lock.c)

### field_camera.c (3)
tilemap_move_something (AddCameraTileOffset (field_camera.c), même code)
coords8_add (AddCameraPixelOffset (field_camera.c), même code)
FieldCameraGetPixelOffsetAtGround (GetCameraOffsetWithPan (field_camera.c), même code)

### fieldmap.c (3)
ExtractMetatileAttribute (MapGridGetMetatileEncounterTypeAt / MapGridGetMetatileTerrainAt (fieldmap.c), UNPACK des bits 8-9 et 10-11 (rencontre, terrain))
MapGridGetMetatileAttributeAt (MapGridGetMetatileEncounterTypeAt / MapGridGetMetatileTerrainAt / MapGridGetMetatileBehaviorAt (fieldmap.c), un accesseur par attribut)
GetAttributeByMetatileIdAndMapLayout (GetMetatileAttributesById (fieldmap.c), même choix primaire / secondaire)

### battle_anim_mon_movement.c (2)
AnimTask_ShakeMon2Step (AnimTask_ShakeMon2_Step (battle_anim_mon_movement.c), même code)
AnimTask_SwayMon_Step (AnimTask_SwayMonStep (battle_anim_mon_movement.c), même code)

### battle_controller_opponent.c (2)
OpponentHandlePlayFanfare (OpponentHandlePlayFanfareOrBGM (battle_controller_opponent.c), même code)
OpponentHandleCmd55 → OpponentHandleEndLinkBattle (battle_controller_opponent.c)

### battle_controller_player.c (2)
PlayerHandlePlayFanfare (PlayerHandlePlayFanfareOrBGM (battle_controller_player.c), même code)
PlayerHandleCmd55 (PlayerHandleEndLinkBattle (battle_controller_player.c), + combats enregistrés d'Émeraude)

### battle_controllers.c (2)
SetUpBattleVars (SetUpBattleVarsAndBirchZigzagoon (battle_controllers.c), sans le ZIGZATON de Seko)
BtlController_EmitPlayFanfare (BtlController_EmitPlayFanfareOrBGM (battle_controllers.c), même transfert)

### battle_message.c (2)
Localize_TrainerClass_Names (GetTrainerClassNameGenderSpecific (international_string_util.c) : en français, ses Localize_TrainerClass_* rendent le nom normal)
BattleStringShouldBeColored (sans effet visible : police MALE / FEMALE des messages des dresseurs = police normale en français)

### battle_tower.c (2)
Debug_FillEReaderTrainerWithPlayerData (FillEReaderTrainerWithPlayerData (battle_tower.c), même code sur frontier.ereaderTrainer ; outil de debug combat.ereader)
CopyEReaderTrainerName5 (GetEreaderTrainerName (battle_tower.c), même code (5 lettres + EOS) sur frontier.ereaderTrainer : nom du dresseur e-Reader de l'Île 7)

### event_data.c (2)
GetFlagAddr (GetFlagPointer (event_data.c), + drapeaux de Kanto (gSaveBlockKanto) ; journal écarté)
ResetSpecialVars (remise à zéro de la RAM au démarrage et au redémarrage (SoftReset, src/platform/system.c) : RF l'appelle avant le menu principal (ResetMenuAndMonGlobals), quand aucune variable spéciale n'a servi ; ses autres appels sont ceux du journal)

### field_control_avatar.c (2)
UpdateHappinessStepCounter (UpdateFriendshipStepCounter (field_control_avatar.c), VAR_HAPPINESS = VAR_FRIENDSHIP)
Task_QuestLogPlayback_OpenStartMenu → Task_OpenStartMenuAfterSignpost (field_control_avatar.c)

### heal_location.c (2)
GetHealLocationIndexFromMapGroupAndNum (GetHealLocationIndexByMap (heal_location.c), même code)
SetWhiteoutRespawnHealerNpcAsLastTalked (SetWhiteoutRespawnWarpAndHealerNpc (heal_location.c), K.O. de RF (2026-10-31))

### pokemon_icon.c (2)
CreateMonIcon_HandleDeoxys (CreateMonIconNoPersonality (pokemon_icon.c d'Émeraude), même code)
MailSpeciesToIconSpecies (GetIconSpeciesNoPersonality (pokemon_icon.c d'Émeraude) : ne diffère que pour une espèce invalide)

### pokemon_storage_system_tasks.c (2)
StartDisplayMonMosaic (StartDisplayMonMosaicEffect (pokemon_storage_system.c d'Émeraude), même code)
IsDisplayMonMosaicActive (IsDisplayMosaicActive (pokemon_storage_system.c), même code)

### wild_encounter.c (2)
GenerateWildMon (CreateWildMon (wild_encounter.c), avec la lettre des ZARBI de Tanoby de RF)
GenerateFishingEncounter (GenerateFishingWildMon (wild_encounter.c))

### load_save.c (2)
LoadSerializedGame → CopyPartyAndObjectsFromSave (load_save.c)
SaveSerializedGame → CopyPartyAndObjectsToSave (load_save.c)

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

### dma3_manager.c (1)
WaitDma3Request (CheckForSpaceForDma3Request (dma3_manager.c), même code)

### field_weather_effects.c (1)
SetThunderCounter (EnqueueThunder (field_weather_effect.c), renommée)

### fldeff_strength.c (1)
FieldCB_UseStrength (FieldCallback_Strength (fldeff_strength.c), scripts équivalents)

### menu_helpers.c (1)
GetDialogBoxFontId (FONT_KANTO (kanto_bag_compat.h) : FONT_MALE / FONT_FEMALE = police normale en français)

### pokemon_storage_system.c (1)
SeekToNextMonInBox (StorageSystemGetNextMonIndex (pokemon_storage_system.c d'Émeraude), même code)

### reshow_battle_screen.c (1)
ReshowBattleScreen_TurnOnDisplay (CB2_ReshowBattleScreenAfterMenu (reshow_battle_screen.c), écran de combat rétabli par celui d'Émeraude)

### save_failed_screen.c (1)
WipeDamagedSectors (WipeSectors (save_failed_screen.c d'Émeraude), même code)

### script.c (1)
ValidateRamScript (ValidateSavedRamScript (script.c), LOCALID_PLAYER = 255)

### sprite.c (1)
FreeSpriteTilesIfNotUsingSheet (DestroySprite (sprite.c d'Émeraude), même libération)

### text_window_graphics.c (1)
GetUserWindowGraphics (GetWindowFrameTilesPal (text_window.c), ->tiles et ->pal)

### battle_anim_fight.c (1)
AnimStompFootStep → AnimStompFoot_Step (battle_anim_fight.c)

### battle_bg.c (1)
CB2_unused → CB2_UnusedBattleInit (battle_bg.c)

### battle_controller_safari.c (1)
SafariHandleCmd55 → SafariHandleEndLinkBattle (battle_controller_safari.c)

### intro.c (1)
CB2_WaitFadeBeforeSetUpIntro → KantoIntro_Start (kanto_intro.c)

### naming_screen.c (1)
DecompressToBgTilemapBuffer → DrawBgTilemap (naming_screen.c)


## Triviale (111) : corps vide ou d'une instruction (« return TRUE; ») : se porte avec son appelant

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


## Morte (149) : jamais appelée ni référencée dans RF

### event_object_movement.c (38)
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
MovementAction_GlideDown_Step0 (jamais lancée dans RF (PlayerGlide n'est pas appelée, aucun script glide_*)),
MovementAction_GlideDown_Step1 (glide_down jamais utilisé dans RF),
MovementAction_GlideUp_Step0 (jamais lancée dans RF (PlayerGlide n'est pas appelée, aucun script glide_*)),
MovementAction_GlideUp_Step1 (glide_up jamais utilisé dans RF),
MovementAction_GlideLeft_Step0 (jamais lancée dans RF (PlayerGlide n'est pas appelée, aucun script glide_*)),
MovementAction_GlideLeft_Step1 (glide_left jamais utilisé dans RF),
MovementAction_GlideRight_Step0 (jamais lancée dans RF (PlayerGlide n'est pas appelée, aucun script glide_*)),
MovementAction_GlideRight_Step1 (glide_right jamais utilisé dans RF),
FaceDirectionFast (face_*_fast : seul PlayerFaceDirectionFast de RF, jamais appelé),
MovementAction_FaceDownFast_Step0 (jamais lancée dans RF (PlayerFaceDirectionFast n'est pas appelée, aucun script face_*_fast)),
MovementAction_FaceUpFast_Step0 (jamais lancée dans RF (PlayerFaceDirectionFast n'est pas appelée, aucun script face_*_fast)),
MovementAction_FaceLeftFast_Step0 (jamais lancée dans RF (PlayerFaceDirectionFast n'est pas appelée, aucun script face_*_fast)),
MovementAction_FaceRightFast_Step0 (jamais lancée dans RF (PlayerFaceDirectionFast n'est pas appelée, aucun script face_*_fast)),
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

### battle_tower.c (25)
BattleTowerMapScript2 (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
ResetBattleTowerStreak (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
ShouldBattleEReaderTrainer (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
ChooseNextBattleTowerTrainer (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
SetBattleTowerTrainerGfxId (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
UpdateOrInsertReceivedBattleTowerRecord (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
GetBattleTowerTrainerFrontSpriteId (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF (BATTLE_TYPE_BATTLE_TOWER n'est lancé que par elle)),
GetBattleTowerTrainerClassNameId (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF (BATTLE_TYPE_BATTLE_TOWER n'est lancé que par elle)),
GetBattleTowerTrainerName (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF (BATTLE_TYPE_BATTLE_TOWER n'est lancé que par elle)),
FillBattleTowerTrainerParty (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
AppendBattleTowerBannedSpeciesName (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
CheckMonBattleTowerBanlist (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
CheckPartyBattleTowerBanlist (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
PrintBattleTowerTrainerGreeting (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
SetBattleTowerProperty (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
BattleTowerUtil (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
SetBattleTowerParty (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
SetPlayerBattleTowerRecord (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
SaveBattleTowerProgress (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
BattleTower_SoftReset (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
SetBattleTowerRecordChecksum (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
PopulateBravoTrainerBattleTowerLostData (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
DetermineBattleTowerPrize (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
GiveBattleTowerPrize (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
Dummy_TryEnableBravoTrainerBattleTower (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF)

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

### battle_transition.c (5)
Task_Spiral (B_TRANSITION_SPIRAL : aucun combat de RF ne l'utilise),
Spiral_UpdateFrame (B_TRANSITION_SPIRAL jamais choisie dans RF),
Spiral_Init (B_TRANSITION_SPIRAL jamais choisie dans RF),
Spiral_End (B_TRANSITION_SPIRAL jamais choisie dans RF),
VBlankCB_Spiral (B_TRANSITION_SPIRAL jamais choisie dans RF)

### text_window.c (5)
LoadHelpMessageWindowGfxOnBg, LoadMenuMessageWindowGfxOnBg, LoadSignpostWindowGfxOnBg,
LoadQuestLogWindowTilesOnBg, LoadUserWindowGfxByFrameOnBg

### field_special_scene.c (4)
FieldSpecialScene_Dummy0, FieldSpecialScene_Dummy1, FieldSpecialScene_Dummy2, FieldSpecialScene_Dummy3

### title_screen.c (4)
SpriteCallback_TitleScreenLeaf (Vert Feuille seulement (#elif defined(LEAFGREEN))),
SpriteCallback_Streak (Vert Feuille seulement (#elif defined(LEAFGREEN))),
CreateStreakSprites (Vert Feuille seulement (#elif defined(LEAFGREEN))),
Task_LeafSpawner (Vert Feuille seulement (#elif defined(LEAFGREEN)))

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

### battle_anim_flying.c (2)
AnimUnusedFeather (seul sUnusedFeatherSpriteTemplate l'emploie, qu'aucune animation n'utilise),
AnimUnusedFeather_Step (appelée par AnimUnusedFeather seulement)

### battle_bg.c (2)
CreateUnknownDebugSprite, GetBattleTerrainGfxPtrs

### battle_main.c (2)
SpriteCB_UnusedDebugSprite (jamais utilisé dans RF (debug)),
SpriteCB_UnusedDebugSprite_Step (jamais utilisé dans RF (debug))

### cable_car_util.c (2)
CableCarUtil_FillWrapped, CableCarUtil_CopyWrapped

### cable_club.c (2)
CableClub_AskSaveTheGame (aucun script de RF ne l'appelle (special retiré de la table de Kanto le 2026-11-04)),
StartWiredCableClubTrade (aucun script de RF ne l'appelle (special retiré de la table de Kanto le 2026-11-04))

### coins.c (2)
PrintCoinsString_Parameterized (seul appelant ShowCoinsWindow_Parameterized, inutilisée (son commentaire)),
ShowCoinsWindow_Parameterized

### event_data.c (2)
DisableNationalPokedex_RSE, IsNationalPokedexEnabled_RSE

### new_menu_helpers.c (2)
GetStdMenuPalette, GetDlgWindowBaseTileNum

### script_pokemon_util.c (2)
ChooseBattleTowerPlayerParty (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF),
CB2_ReturnFromChooseBattleTowerParty (Tour de Combat de Rubis/Saphir : aucune carte ni script de RF)

### battle_anim_special.c (1)
AnimTask_LevelUpHealthBox

### battle_controller_safari.c (1)
SafariDummy

### battle_controllers.c (1)
BtlController_EmitUnknownYesNoBox

### battle_gfx_sfx_util.c (1)
DoBattleSpriteAffineAnim

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

### naming_screen.c (1)
Debug_NamingScreenRival

### pokemon_storage_system.c (1)
RestorePokemonStorage

### start_menu.c (1)
SetHasPokedexAndPokemon

### text_printer.c (1)
CopyGlyphToWindow_Parameterized


## Link (0) : link / E-Reader : à porter, désactivé


## Écartée (653) : écartée par décision

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

### union_room_chat_display.c (49)
UnionRoomChat_TryAllocGraphicsWork (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_RunDisplaySubtask0 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_FreeGraphicsWork (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
InitWork (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_ResetDisplaySubtasks (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_RunDisplaySubtasks (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_StartDisplaySubtask (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
RunDisplaySubtask (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_LoadGfx (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_PrintWin3 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_HideWin3 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_SwitchPages (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_MoveSelectorCursorObj (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_ShowQuitChattingDialog (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_UpdateMessageBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_PrintRegisterWhere (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_CancelRegister (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_ReturnToKeyboard (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_ScrollChat (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_AnimateSelectorCursorBlink (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_PrintInputText (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_PrintExitingChat (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_PrintLeaderLeft (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_AskSave (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_AskOverwriteSave (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_PrintSavingDontTurnOffPower (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_PrintSavedTheGame (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtask_ShowConfirmLeaderLeaveDialog (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DisplaySubtaskDummy (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
PlaceYesNoMenuAt (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_ProcessInput (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
PlaceStdMessageWindow (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
FillWin1Rect (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
PrintOnWin1Parameterized (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
AnimateMoveBg1Right (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
AnimateMoveBg1Left (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
PrintKeyboardSwapTextsOnWin3 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ClearWin3 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
PrintTextOnWin0Colorized (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
SetBgTilemapWorkBuffers (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
LoadUnionRoomChatPanelGfx (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
LoadLinkMiscMenuGfx (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
LoadBg1Pal8 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
LoadWin0 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
LoadWin2 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
LoadWin1 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
LoadWin3 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
FillScanlineEffectWithValue1col (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
FillScanlineEffectWithValue2col (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions)

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

### union_room_chat.c (34)
InitChatWork (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
FreeChatWork (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_Join (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_HandleInput (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_Switch (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_AskQuitChatting (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_ExitChat (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_Drop (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_Disbanded (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_SendMessage (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_Register (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatEntryRoutine_SaveAndExit (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
GoToRoutine (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
TypeChatMessage_HandleDPad (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
AppendCharacterToChatMessageBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
DeleteLastCharacterOfChatMessageBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ToggleCaseOfLastCharacterInChatMessageBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
ChatMsgHasAtLeastOneCharcter (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
SaveRegisteredTextsToSB1 (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetWorkRegisteredText (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
GetEndOfUnk1A (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
GetPtrToLastCharOfUnk1A (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
GetNumCharsInMessageEntryBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetCursorColAndRow (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetMessageEntryBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_LenMessageEntryBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetBufferSelectionRegion (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetEndOfMessageEntryBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetNumCharsInMessageEntryBuffer (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetLastReceivedMessage (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetReceivedPlayerIndex (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetMessageEntryCursorPosition (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetWhetherShouldShowCaseToggleIcon (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_GetNameOfPlayerWhoDisbandedChat (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions)

### party_menu.c (25)
DisplayPartyPokemonDataForChooseMultiple (choix d'équipe des combats link d'Émeraude (InitChooseHalfPartyForBattle), aussi pour l'Île 7),
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
SetSwitchedPartyOrderQuestLogEvent (journal de RF),
CursorCB_Enter (choix d'équipe des combats link d'Émeraude (InitChooseHalfPartyForBattle), aussi pour l'Île 7),
CursorCB_NoEntry (choix d'équipe des combats link d'Émeraude (InitChooseHalfPartyForBattle), aussi pour l'Île 7),
SetSwappedHeldItemQuestLogEvent (journal de RF), SetUsedFieldMoveQuestLogEvent (journal de RF),
SetUsedFlyQuestLogEvent (journal de RF),
InitChooseMonsForBattle (choix d'équipe des combats link d'Émeraude (InitChooseHalfPartyForBattle), aussi pour l'Île 7),
Task_ValidateChosenMonsForBattle (choix d'équipe des combats link d'Émeraude (InitChooseHalfPartyForBattle), aussi pour l'Île 7),
Task_ContinueChoosingMonsForBattle (choix d'équipe des combats link d'Émeraude (InitChooseHalfPartyForBattle), aussi pour l'Île 7),
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

### union_room_chat_objects.c (11)
UnionRoomChat_TryAllocSpriteWork (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_FreeSpriteWork (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_CreateSelectorCursorObj (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_ToggleSelectorCursorObjVisibility (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_MoveSelectorCursorObj (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_UpdateObjPalCycle (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_SetSelectorCursorClosedImage (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_AnimateSelectorCursorReopen (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UnionRoomChat_SpawnTextEntryPointerSprites (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
CreatePageSwitchUISprites (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions),
UpdateVisibleUnionRoomChatIcon (Union Room et chat d'Émeraude (union_room_chat.c) dans les deux régions)

### overworld.c (9)
QL_LoadMapNormal (journal de RF), DoCB1_Overworld_QuestLogPlayback (journal de RF),
CB2_SetUpOverworldForQLPlaybackWithWarpExit (journal de RF), CB2_SetUpOverworldForQLPlayback (journal de RF),
CB2_LoadMapForQLPlayback (journal de RF), DoLoadMap_QLPlayback (journal de RF),
LoadMap_QLPlayback (journal de RF), CB2_EnterFieldFromQuestLog (journal de RF),
CreateConfirmLeaveTradeRoomPrompt (link d'Émeraude (RunConfirmLeaveCableClubScript, overworld.c) dans les deux régions)

### save_failed_screen.c (9)
RunSaveFailedScreen (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle)),
BlankPalettes (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle)),
RequestDmaCopyFromScreenBuffer (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle)),
RequestDmaCopyFromCharBuffer (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle)),
FillBgMapBufferRect (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle)),
UpdateMapBufferWithText (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle)),
ClearMapBuffer (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle)),
PrintTextOnSaveFailedScreen (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle)),
TryWipeDamagedSectors (variante RF : écran d'échec de sauvegarde d'Émeraude gardé (DoSaveFailedScreen, même rôle))

### field_specials.c (7)
QuestLog_CheckDepartingIndoorsMap (journal de RF), QuestLog_TryRecordDepartedLocation (journal de RF),
DoDeoxysTriangleInteraction (Île Naissance de RF : celle d'Émeraude (DoDeoxysRockInteraction)),
Task_DoDeoxysTriangleInteraction (Île Naissance de RF : celle d'Émeraude (WaitForDeoxysRockMovement)),
MoveDeoxysObject (Île Naissance de RF : celle d'Émeraude (ChangeDeoxysRockLevel)),
Task_WaitDeoxysFieldEffect (Île Naissance de RF : celle d'Émeraude (WaitForDeoxysRockMovement)),
SetDeoxysTrianglePalette (Île Naissance de RF : celle d'Émeraude)

### bike.c (6)
BikeInputHandler_Normal (vélo de RF : un seul vélo, celui de Hoenn ; ses pentes de la Piste Cyclable sont dans MovePlayerOnCyclingRoadSlope (bike.c)),
BikeInputHandler_Turning (vélo de RF : un seul vélo, celui de Hoenn),
BikeInputHandler_Slope (vélo de RF : un seul vélo, celui de Hoenn ; repris dans MovePlayerOnCyclingRoadSlope (bike.c)),
BikeTransition_MoveDirection (vélo de RF : un seul vélo, celui de Hoenn ; escaliers de roche repris dans MachBikeTransition_TrySpeedUp (bike.c)),
BikeTransition_Downhill (vélo de RF : un seul vélo, celui de Hoenn ; même code dans MovePlayerOnCyclingRoadSlope (bike.c)),
BikeTransition_Uphill (vélo de RF : un seul vélo, celui de Hoenn ; même code dans MovePlayerOnCyclingRoadSlope (bike.c))

### cereader_tool.c (6)
ValidateTrainerTowerTrainer (étages e-Reader de la Tour des Dresseurs : seulement d'une carte e-Reader (ReadTrainerTowerAndValidate : étages de RF)),
ValidateTrainerTowerData (étages e-Reader de la Tour des Dresseurs : seulement d'une carte e-Reader (ReadTrainerTowerAndValidate : étages de RF)),
CEReaderTool_SaveTrainerTower_r (étages e-Reader de la Tour des Dresseurs : seulement d'une carte e-Reader (ReadTrainerTowerAndValidate : étages de RF)),
CEReaderTool_SaveTrainerTower (étages e-Reader de la Tour des Dresseurs : seulement d'une carte e-Reader (ReadTrainerTowerAndValidate : étages de RF)),
CEReaderTool_LoadTrainerTower_r (étages e-Reader de la Tour des Dresseurs : seulement d'une carte e-Reader (ReadTrainerTowerAndValidate : étages de RF)),
CEReaderTool_LoadTrainerTower (étages e-Reader de la Tour des Dresseurs : seulement d'une carte e-Reader (ReadTrainerTowerAndValidate : étages de RF))

### field_player_avatar.c (6)
QL_TryRecordPlayerStepWithDuration0 (journal de RF), QL_TryRecordNPCStepWithDuration32 (journal de RF),
CreateStopSurfingTask_NoMusicChange (journal de RF (quest_log_player.c, seul appelant)),
Fishing5 (variante RF : Émeraude gardée (Fishing_ShowDots : un point toutes les 8 images et A arrête ; RF 12 images, pas d'arrêt) ; docs/VARIANTES-RF.md),
Fishing6 (variante RF : Émeraude gardée (Fishing_CheckForBite : VENTOUSE et GLUE aident à ferrer ; RF non) ; docs/VARIANTES-RF.md),
Fishing7 (variante RF : Émeraude gardée (Fishing_GotBite : « Oh! Ça mord! » puis A à temps ; RF ferre tout seul) ; docs/VARIANTES-RF.md)

### battle_records.c (5)
IndexOfOpponentLinkBattleRecord (records link d'Émeraude (UpdatePlayerLinkBattleRecords), lus par ShowBattleRecords de RF),
AddOpponentLinkBattleRecord (records link d'Émeraude (UpdatePlayerLinkBattleRecords), lus par ShowBattleRecords de RF),
IncTrainerCardWinCount (records link d'Émeraude (UpdatePlayerLinkBattleRecords), lus par ShowBattleRecords de RF),
IncTrainerCardLossCount (records link d'Émeraude (UpdatePlayerLinkBattleRecords), lus par ShowBattleRecords de RF),
UpdateBattleOutcomeOnTrainerCards (records link d'Émeraude (UpdatePlayerLinkBattleRecords), lus par ShowBattleRecords de RF)

### field_effect.c (5)
ApplyGlobalFieldPaletteTint (journal de RF (teintes grise et sépia des souvenirs)),
SpinObjectEvent (variante RF : Émeraude gardée (Corde Sortie, VARIANTES-RF.md)),
WarpOutObjectEventUpwards (variante RF : Émeraude gardée (Corde Sortie, VARIANTES-RF.md)),
WarpInObjectEventDownwards (variante RF : Émeraude gardée (Corde Sortie, VARIANTES-RF.md)),
SpriteCB_FlyBirdWithPlayer (variante RF : Émeraude gardée (SpriteCB_FlyBirdSwoopDown : arc 140, pas de 4 ; RF 180, pas de 2) ; docs/VARIANTES-RF.md)

### field_fadetransition.c (5)
WarpFadeInScreenWithDelay (variante RF : Émeraude gardée (seul le volet de grange de RF, Task_ExitDoor, l'appelle) ; docs/VARIANTES-RF.md),
DoTeleport2Warp (link d'Émeraude (field_fadetransition.c : DoSpinEnterWarp de warpspinenter) dans les deux régions),
DoUnionRoomWarp (link d'Émeraude (field_fadetransition.c) dans les deux régions),
Task_CableClubWarp (link d'Émeraude (field_fadetransition.c) dans les deux régions),
Task_ReturnFromLinkRoomWarp (link d'Émeraude (field_fadetransition.c) dans les deux régions)

### field_screen_effect.c (5)
DoOutwardBarnDoorWipe (variante RF : Émeraude gardée (sortie d'un bâtiment : fondu d'Émeraude ; RF ouvre l'écran en portes de grange, Task_ExitDoor) ; docs/VARIANTES-RF.md),
BarnDoorWipeSaveGpuRegs (variante RF : Émeraude gardée (volet de grange, DoOutwardBarnDoorWipe) ; docs/VARIANTES-RF.md),
BarnDoorWipeLoadGpuRegs (variante RF : Émeraude gardée (volet de grange, DoOutwardBarnDoorWipe) ; docs/VARIANTES-RF.md),
Task_BarnDoorWipe (variante RF : Émeraude gardée (volet de grange, DoOutwardBarnDoorWipe) ; docs/VARIANTES-RF.md),
Task_BarnDoorWipeChild (variante RF : Émeraude gardée (volet de grange, DoOutwardBarnDoorWipe) ; docs/VARIANTES-RF.md)

### berry_crush.c (4)
BerryCrush_SetVBlankCallback (link d'Émeraude (berry_crush.c) dans les deux régions),
BerryCrush_BuildLocalState (link d'Émeraude (berry_crush.c) dans les deux régions),
printCrushingResults (link d'Émeraude (berry_crush.c) dans les deux régions),
Task_ShowBerryCrushRankings (link d'Émeraude (berry_crush.c) dans les deux régions)

### mystery_gift_menu.c (4)
PrintMysteryGiftOrEReaderTopMenu (Cadeau Mystère d'Émeraude (mystery_gift_menu.c) dans les deux régions),
AddTextPrinterToWindow1 (Cadeau Mystère d'Émeraude (mystery_gift_menu.c) dans les deux régions),
ClearTextWindow (Cadeau Mystère d'Émeraude (mystery_gift_menu.c) dans les deux régions),
HandleMysteryGiftListMenu (Cadeau Mystère d'Émeraude (mystery_gift_menu.c) dans les deux régions)

### pokemon_storage_system_menu.c (4)
PrintStringToBufferCopyNow (interface du PC de RF : celle d'Émeraude (choix utilisateur 2026-10-23)),
CreatePCMainMenu (interface du PC de RF : celle d'Émeraude (menu principal du stockage ; choix utilisateur 2026-10-23)),
ChooseBoxMenu_PrintBoxNameAndCount (interface du PC de RF : celle d'Émeraude (ChooseBoxMenu_PrintInfo ; choix utilisateur 2026-10-23)),
ChooseBoxMenu_PrintTextToSprite (interface du PC de RF : celle d'Émeraude (ChooseBoxMenu_PrintInfo ; choix utilisateur 2026-10-23))

### quest_log_battle.c (3)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), TrySetQuestLogBattleEvent,
TrySetQuestLogLinkBattleEvent, GetLinkMultiBattlePlayerIndexes

### quest_log_objects.c (3)
— « Précédemment » de RF (Kanto = post-game, décision 2026-11-02), QL_RecordObjects, QL_LoadObjects,
QL_TryStopSurfing

### start_menu.c (4)
SetUpStartMenu_Link (link d'Émeraude (start_menu.c) dans les deux régions),
SetUpStartMenu_UnionRoom (link d'Émeraude (start_menu.c) dans les deux régions),
DoSetUpSaveAfterLinkBattle (link d'Émeraude (start_menu.c) dans les deux régions),
task50_after_link_battle_save (link d'Émeraude (start_menu.c) dans les deux régions)

### battle_controller_link_partner.c (3)
LinkPartnerDummy (link d'Émeraude (battle_controller_link_partner.c) dans les deux régions),
LinkPartnerHandleUnknownYesNoBox (link d'Émeraude (battle_controller_link_partner.c) dans les deux régions),
LinkPartnerHandlePlayFanfare (link d'Émeraude (battle_controller_link_partner.c) dans les deux régions)

### event_object_movement.c (3)
QL_UpdateObjectEventCurrentMovement (journal de RF (quest_log.c)),
QuestLogObjectEventExecHeldMovementAction (journal de RF (quest_log.c)),
ObjectEventCheckForReflectiveSurface (variante RF : Émeraude gardée (ObjectEventGetNearbyReflectionType : zone selon la taille du sprite ; RF 1×2 cases, pareil pour le joueur) ; docs/VARIANTES-RF.md)

### link_rfu_2.c (3)
LinkRfu_ForceChangeSpParent (link d'Émeraude (link_rfu_2.c) dans les deux régions),
RfuGetErrorInfo (link d'Émeraude (link_rfu_2.c) dans les deux régions),
DestroyTask_RfuReconnectWithParent (link d'Émeraude (link_rfu_2.c) dans les deux régions)

### pokemon_storage_system_graphics.c (3)
SetShiftMonSpritePtr (interface du PC de RF : celle d'Émeraude (SetShiftedMonData ; choix utilisateur 2026-10-23)),
ShiftMons (interface du PC de RF : celle d'Émeraude (DoMonPlaceChange ; choix utilisateur 2026-10-23)),
DoReleaseMonAnim (interface du PC de RF : celle d'Émeraude (TryHideReleaseMon ; choix utilisateur 2026-10-23))

### trade_scene.c (3)
CheckLinkTimeout (link d'Émeraude (trade.c) dans les deux régions),
LoadTradeGbaSpriteGfx (link d'Émeraude (trade.c) dans les deux régions),
TradeBufferOTnameAndNicknames (link d'Émeraude (trade.c) dans les deux régions)

### union_room_battle.c (3)
SetUpPartiesAndStartBattle (link d'Émeraude (union_room_battle.c) dans les deux régions),
UnionRoomBattle_CreateTextPrinter (link d'Émeraude (union_room_battle.c) dans les deux régions),
UnionRoomBattle_PrintTextOnWindow0 (link d'Émeraude (union_room_battle.c) dans les deux régions)

### battle_controller_link_opponent.c (2)
LinkOpponentHandleUnknownYesNoBox (link d'Émeraude (battle_controller_link_opponent.c) dans les deux régions),
LinkOpponentHandlePlayFanfare (link d'Émeraude (battle_controller_link_opponent.c) dans les deux régions)

### battle_main.c (2)
LinkBattleComputeBattleTypeFlags (link d'Émeraude (battle_main.c) dans les deux régions),
PrepareOwnMultiPartnerBuffer (link d'Émeraude (battle_main.c) dans les deux régions)

### cable_club.c (2)
AnyConnectedPartnersPlayingRS (link d'Émeraude (cable_club.c) dans les deux régions),
GetSeeingLinkPlayerCardMsg (link d'Émeraude (cable_club.c) dans les deux régions)

### event_data.c (2)
EnableNationalPokedex_RSE (effet nul : VAR_0x403C, pokedex.unused et FLAG_0x838 ne sont jamais lus dans RF (son commentaire)),
IsFlagOrVarStoredInQuestLog (journal de RF)

### help_message.c (1)
— aide L/R de RF (Kanto = post-game, décision 2026-11-02), MapNamePopupWindowIdSetDummy

### link_rfu_3.c (2)
ZeroName (link d'Émeraude (link_rfu_3.c) dans les deux régions),
NameIsEmpty (link d'Émeraude (link_rfu_3.c) dans les deux régions)

### new_game.c (2)
ClearBattleTower (Tour de Combat de Rubis/Saphir absente : rien à effacer),
WarpToPlayersRoom (nouvelle partie de RF : la fusion commence à Hoenn (Kanto = post-game))

### pokemon_storage_system_tasks.c (2)
PrintStorageMessage (interface du PC de RF : celle d'Émeraude (PrintMessage : police et fenêtre d'Émeraude ; choix utilisateur 2026-10-23)),
SetPokeStorageQuestLogEvent (journal de RF)

### scrcmd.c (2)
ScriptContext_NextCommandEndsScript (journal de RF (seul appelant : le contexte de script du journal)),
ScriptContext_GetQuestLogInput (journal de RF)

### shop.c (2)
RecordItemTransaction (journal de RF (achats et ventes notés pour le journal)),
RecordTransactionForQuestLog (journal de RF)

### sound.c (2)
SetBGMVolume_SuppressHelpSystemReduction (aide de RF (volume baissé sous l'aide L/R)),
BGMVolumeMax_EnableHelpSystemReduction (aide de RF (volume baissé sous l'aide L/R))

### text_window.c (2)
LoadHelpMessageWindowGfx (aide de RF (help_system)), LoadQuestLogWindowTiles (journal de RF)

### trade.c (2)
CB2_ReturnToTradeMenuFromSummary (link d'Émeraude (trade.c) dans les deux régions),
CommunicateWhetherMonCanBeTraded (link d'Émeraude (trade.c) dans les deux régions)

### union_room.c (2)
Leader_DisconnectOnState (link d'Émeraude (union_room.c) dans les deux régions),
ItemPrintFunc_Unused (link d'Émeraude (union_room.c) dans les deux régions)

### berry.c (1)
InitEnigmaBerry (Baie Enigma (e-Reader) ; Émeraude prend la baie par défaut (IsEnigmaBerryValid), même affichage)

### berry_fix_program.c (1)
SetScene (link d'Émeraude (berry_fix_program.c) dans les deux régions)

### bg.c (1)
AdjustBgMosaic (variante RF : mosaïque du poison sur le terrain d'Émeraude gardée (Task_FieldPoisonEffect, fldeff_misc.c) ; docs/VARIANTES-RF.md)

### blend_palette.c (1)
BlendPalettesAt (journal de RF (seul appelant SlightlyDarkenPalsInWeather))

### dodrio_berry_picking.c (1)
DBP_LoadStdWindowGfx (link d'Émeraude (dodrio_berry_picking.c) dans les deux régions)

### easy_chat.c (1)
EnableRareWord (l'Événement Mystère d'Émeraude (mystery_event_script.c) sert aux deux régions ; un seul dictionnaire Easy Chat (décision 2026-11-02))

### field_control_avatar.c (1)
QuestLogOverrideJoyVars (journal de RF)

### field_effect_helpers.c (1)
CreateBobbingEffect (variante RF : Émeraude gardée (UpdateBobbingEffect : le Pokémon du Surf monte et descend 2× plus vite que dans RF) ; docs/VARIANTES-RF.md)

### field_weather.c (1)
SlightlyDarkenPalsInWeather (journal de RF)

### item.c (1)
TrySetObtainedItemQuestLogEvent (journal de RF)

### item_use.c (1)
ItemUse_SetQuestLogEvent (journal de RF)

### link.c (1)
SetLinkErrorFromRfu (link d'Émeraude (link.c) dans les deux régions)

### mystery_event_script.c (1)
MEventScript_Run (Événement Mystère d'Émeraude (mystery_event_script.c) dans les deux régions)

### naming_screen.c (1)
NamingScreen_CreateRivalIcon (nom du rival : pas de choix du nom du rival (BLUE, décision 2026-10-30))

### new_menu_helpers.c (1)
DrawHelpMessageWindowWithText (aide de RF : description du menu Start, seulement en mode BOUTONS = AIDE (aide L/R écartée) ; loadhelp n'est utilisée par aucun script)

### palette.c (1)
CopyPaletteInvertedTint (journal de RF)

### pokemon.c (1)
InitMonSpritesGfx_Mode1 (discours de Chen : seul appelant CreateMonSpritesGfxManager(1, 1) (oak_speech.c))

### pokemon_icon.c (1)
LoadMonIconPalettesAt (interface du PC de RF : celle d'Émeraude (déplacement multiple ; choix utilisateur 2026-10-23))

### script.c (1)
IsQuestLogInputDpad (journal de RF)

### script_menu.c (1)
QL_DestroyAbortedDisplay (journal de RF)

### tilemap_util.c (1)
TilemapUtil_SetTilemap (interface du PC de RF : celle d'Émeraude (choix utilisateur 2026-10-23))

### title_screen.c (1)
CreateLeafSprite (version Vert Feuille (la fusion est Rouge Feu))

### trainer_see.c (1)
TrainerSeeFunc_PrepareToEngage (variante RF : Émeraude gardée (PlayerFaceApproachingTrainer : le joueur se tourne vers le dresseur ; RF non) ; docs/VARIANTES-RF.md)

### union_room_player_avatar.c (1)
MakeGroupAssemblyAreasPassable (link d'Émeraude (union_room_player_avatar.c) dans les deux régions)

### wireless_communication_status_screen.c (1)
ExitWirelessCommunicationStatusScreen (écran sans fil d'Émeraude (wireless_communication_status_screen.c), ouvert aussi par le moniteur de Kanto)
