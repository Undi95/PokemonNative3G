Kanto_CableClub_OnTransition::
	call Kanto_CableClub_EventScript_HideOrShowMysteryGiftMan
	end

Kanto_CableClub_EventScript_HideOrShowMysteryGiftMan::
	specialvar VAR_RESULT, ValidateSavedWonderCard
	goto_if_eq VAR_RESULT, FALSE, EventScript_HideMysteryGiftMan
	clearflag FLAG_KANTO_HIDE_MG_DELIVERYMEN
	return

EventScript_HideMysteryGiftMan::
	setflag FLAG_KANTO_HIDE_MG_DELIVERYMEN
	return

Kanto_CableClub_EventScript_MysteryGiftMan::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	trywondercardscript

/* Unused */
EventScript_MysteryGiftThankYou::
	msgbox Text_ThankYouForAccessingMysteryGift, MSGBOX_NPC
	end

Kanto_CableClub_OnWarp::
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_SINGLE_BATTLE, EventScript_CheckTurnAttendant
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_DOUBLE_BATTLE, EventScript_CheckTurnAttendant
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_MULTI_BATTLE, EventScript_CheckTurnAttendant
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_TRADE_CENTER, EventScript_CheckTurnAttendant
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_UNION_ROOM, EventScript_CheckTurnAttendant
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_BERRY_CRUSH, EventScript_CheckTurnAttendant
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_MINIGAME, EventScript_CheckTurnAttendant
	.2byte 0

EventScript_CheckTurnAttendant::
	goto_if_eq VAR_0x8007, 0, EventScript_CheckTurnAttendantEnd
	turnobject VAR_0x8007, DIR_WEST
EventScript_CheckTurnAttendantEnd:
	end

Kanto_CableClub_OnLoad::
	goto_if_eq VAR_KANTO_CABLE_CLUB_STATE, USING_SINGLE_BATTLE, EventScript_OnLoadFromColosseum
	goto_if_eq VAR_KANTO_CABLE_CLUB_STATE, USING_DOUBLE_BATTLE, EventScript_OnLoadFromColosseum
	goto_if_eq VAR_KANTO_CABLE_CLUB_STATE, USING_MULTI_BATTLE, EventScript_OnLoadFromColosseum
	goto_if_eq VAR_KANTO_CABLE_CLUB_STATE, USING_TRADE_CENTER, EventScript_OnLoadFromTradeCenter
	goto_if_eq VAR_KANTO_CABLE_CLUB_STATE, USING_UNION_ROOM, EventScript_OnLoadFromUnionRoom
	goto_if_eq VAR_KANTO_CABLE_CLUB_STATE, USING_BERRY_CRUSH, EventScript_OnLoadFromBerryCrush
	goto_if_eq VAR_KANTO_CABLE_CLUB_STATE, USING_MINIGAME, EventScript_OnLoadFromGameCorner
	end

EventScript_OnLoadFromColosseum::
	call Kanto_CableClub_EventScript_OpenDirectCornerBarrier
	end

EventScript_OnLoadFromTradeCenter::
	call Kanto_CableClub_EventScript_OpenDirectCornerBarrier
	end

EventScript_OnLoadFromUnionRoom::
	call Kanto_CableClub_EventScript_OpenUnionRoomBarrier
	end

EventScript_OnLoadFromBerryCrush::
	call Kanto_CableClub_EventScript_OpenDirectCornerBarrier
	end

EventScript_OnLoadFromGameCorner::
	call CableClub_EventScript_OpenGameCornerBarrier
	end

Kanto_CableClub_OnFrame::
	map_script_2 VAR_KANTO_MAP_SCENE_POKEMON_CENTER_TEALA, 1, Kanto_CableClub_EventScript_Tutorial
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_SINGLE_BATTLE, Kanto_CableClub_EventScript_ExitLinkRoom
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_DOUBLE_BATTLE, Kanto_CableClub_EventScript_ExitLinkRoom
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_MULTI_BATTLE, Kanto_CableClub_EventScript_ExitLinkRoom
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_TRADE_CENTER, Kanto_CableClub_EventScript_ExitTradeCenter
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_UNION_ROOM, Kanto_CableClub_EventScript_ExitUnionRoom
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_BERRY_CRUSH, Kanto_CableClub_EventScript_ExitLinkRoom
	map_script_2 VAR_KANTO_CABLE_CLUB_STATE, USING_MINIGAME, Kanto_CableClub_EventScript_ExitMinigameRoom
	.2byte 0

Kanto_CableClub_EventScript_ExitLinkRoom::
	lockall
	call Kanto_CableClub_EventScript_CloseLinkAndExitLinkRoom
	call Kanto_CableClub_EventScript_CloseDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	erasebox 0, 0, 29, 19
	releaseall
	end

Kanto_CableClub_EventScript_ExitMinigameRoom::
	lockall
	call Kanto_CableClub_EventScript_CloseLinkAndExitLinkRoom
	call CableClub_EventScript_CloseGameCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	erasebox 0, 0, 29, 19
	releaseall
	end

Kanto_CableClub_EventScript_CloseLinkAndExitLinkRoom::
	special CloseLink
	special HelpSystem_Enable
	special QuestLog_StartRecordingInputsAfterDeferredEvent
	setvar VAR_KANTO_CABLE_CLUB_STATE, 0
	textcolor NPC_TEXT_COLOR_FEMALE
	goto_if_eq VAR_0x8007, 0, Kanto_CableClub_EventScript_PlayerExitLinkRoom
	applymovement VAR_0x8007, Kanto_Movement_AttendantFaceLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerExitLinkRoom
	waitmovement 0
	applymovement VAR_0x8007, Kanto_Movement_AttendantFaceDown
	waitmovement 0
	return

Kanto_CableClub_EventScript_ExitTradeCenter::
	lockall
	call Kanto_CableClub_EventScript_PlayerExitTradeCenter
	call Kanto_CableClub_EventScript_CloseDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	erasebox 0, 0, 29, 19
	releaseall
	end

Kanto_CableClub_EventScript_PlayerExitTradeCenter::
	special CloseLink
	special HelpSystem_Enable
	special QuestLog_StartRecordingInputsAfterDeferredEvent
	setvar VAR_KANTO_CABLE_CLUB_STATE, 0
	textcolor NPC_TEXT_COLOR_FEMALE
	goto_if_eq VAR_0x8007, 0, Kanto_CableClub_EventScript_PlayerExitLinkRoom
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerFaceAttendantRight
	waitmovement 0
	applymovement VAR_0x8007, Kanto_Movement_AttendantFaceLeft
	waitmovement 0
	call Kanto_CableClub_EventScript_TrainerCardDataOverwritten
	return

Kanto_CableClub_EventScript_ExitUnionRoom::
	lockall
	call Kanto_CableClub_EventScript_PlayerExitUnionRoom
	call Kanto_CableClub_EventScript_CloseUnionRoomBarrier
	special DrawWholeMapView
	playse SE_CLICK
	erasebox 0, 0, 29, 19
	releaseall
	end

Kanto_CableClub_EventScript_PlayerExitUnionRoom::
	special HelpSystem_Enable
	special QuestLog_StartRecordingInputsAfterDeferredEvent
	setvar VAR_KANTO_CABLE_CLUB_STATE, 0
	textcolor NPC_TEXT_COLOR_FEMALE
	goto_if_eq VAR_0x8007, 0, Kanto_CableClub_EventScript_PlayerExitLinkRoom
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerFaceAttendantRight
	waitmovement 0
	applymovement VAR_0x8007, Kanto_Movement_AttendantFaceLeft
	waitmovement 0
	call Kanto_CableClub_EventScript_TrainerCardDataOverwritten
	return

Kanto_CableClub_EventScript_TrainerCardDataOverwritten::
	message Kanto_CableClub_Text_TrainerCardDataOverwritten
	waitmessage
	delay 60
	playse SE_PIN
	message Kanto_CableClub_Text_HopeToSeeYouAgain
	waitmessage
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerExitLinkRoom
	waitmovement 0
	applymovement VAR_0x8007, Kanto_Movement_AttendantFaceDown
	waitmovement 0
	return

Kanto_CableClub_EventScript_PlayerExitLinkRoom::
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerExitLinkRoom
	waitmovement 0
	return

Kanto_CableClub_EventScript_Tutorial::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	applymovement LOCALID_PLAYER, Kanto_Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Kanto_CableClub_Text_FirstTimeRightThisWay
	closemessage
	applymovement LOCALID_PLAYER, Movement_PlayerApproachCounter
	waitmovement 0
	delay 30
	msgbox Kanto_CableClub_Text_ExplainWirelessClubFirstTime
	setvar VAR_KANTO_MAP_SCENE_POKEMON_CENTER_TEALA, 2
	releaseall
	end

Movement_PlayerApproachCounter:
	walk_up
	walk_up
	step_end

Kanto_CableClub_EventScript_WelcomeToCableClub::
	message Kanto_CableClub_Text_WelcomeWhichCableClubService
	waitmessage
	delay 60
	goto Kanto_CableClub_EventScript_SelectCableClubRoom
	end

Kanto_CableClub_EventScript_UnusedWelcomeToCableClub::
	msgbox Kanto_CableClub_Text_WhichService
	goto Kanto_CableClub_EventScript_SelectCableClubRoom
	end

Kanto_CableClub_EventScript_SelectCableClubRoom::
	setvar VAR_0x8004, 0
	multichoice 0, 0, KANTO_MULTICHOICE_TRADE_CENTER_COLOSSEUM, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_TradeCenter
	case 1, Kanto_CableClub_EventScript_Colosseum
	case 2, Kanto_CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_Colosseum::
	copyvar VAR_0x8007, VAR_LAST_TALKED
	goto Kanto_CableClub_EventScript_SelectBattleMode
	end

Kanto_CableClub_EventScript_SelectBattleMode::
	message Kanto_CableClub_Text_PlayWhichBattleMode
	waitmessage
	multichoice 0, 0, KANTO_MULTICHOICE_SINGLE_DOUBLE_MULTI_INFO_EXIT, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_SingleBattleMode
	case 1, Kanto_CableClub_EventScript_DoubleBattleMode
	case 2, Kanto_CableClub_EventScript_MultiBattleMode
	case 3, Kanto_CableClub_EventScript_BattleModeInfo
	case 4, Kanto_CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_BattleModeInfo::
	msgbox Kanto_CableClub_Text_ExplainBattleModes
	goto Kanto_CableClub_EventScript_SelectBattleMode
	end

Kanto_CableClub_EventScript_SingleBattleMode::
	setvar VAR_0x8004, USING_SINGLE_BATTLE
	goto Kanto_CableClub_EventScript_TryEnterColosseum
	end

Kanto_CableClub_EventScript_DoubleBattleMode::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, Kanto_CableClub_EventScript_NeedTwoMonsForDoubleBattle
	setvar VAR_0x8004, USING_DOUBLE_BATTLE
	goto Kanto_CableClub_EventScript_TryEnterColosseum
	end

Kanto_CableClub_EventScript_NeedTwoMonsForDoubleBattle::
	msgbox Kanto_CableClub_Text_NeedTwoMonsForDoubleBattle
	goto Kanto_CableClub_EventScript_SelectBattleMode
	end

Kanto_CableClub_EventScript_MultiBattleMode::
	setvar VAR_0x8004, USING_MULTI_BATTLE
	goto Kanto_CableClub_EventScript_TryEnterColosseum
	end

Kanto_CableClub_EventScript_TryEnterColosseum::
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, Kanto_CableClub_EventScript_AbortLink
	message CableClub_Text_PleaseWaitBCancel
	waitmessage
	special HelpSystem_Disable
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special TryBattleLinkup
	call EventScript_RestorePrevTextColor
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Kanto_CableClub_EventScript_EnterColosseum
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, Kanto_CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, Kanto_CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, Kanto_CableClub_EventScript_AbortLinkIncorrectNumberOfBattlers
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Kanto_CableClub_EventScript_AbortLink
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, Kanto_CableClub_EventScript_AbortLinkConnectionError
	end

Kanto_CableClub_EventScript_EnterColosseum::
	special HealPlayerParty
	special SavePlayerParty
	special LoadPlayerBag
	copyvar VAR_KANTO_CABLE_CLUB_STATE, VAR_0x8004
	messageautoscroll Kanto_CableClub_Text_PleaseEnter
	waitmessage
	call Kanto_CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Kanto_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, MAP_UNDEFINED
	closedoor 9, 1
	waitdooranim
	release
	goto_if_eq VAR_0x8004, USING_MULTI_BATTLE, Kanto_CableClub_EventScript_WarpTo4PColosseum
	special SetCableClubWarp
	warp MAP_BATTLE_COLOSSEUM_2P, 6, 8
	special DoCableClubWarp
	end

/* Unused */
Kanto_CableClub_EventScript_PlayerApproachLinkRoomRight::
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerApproachLinkRoomRight
	waitmovement 0
	return

Kanto_CableClub_EventScript_WarpTo4PColosseum::
	special SetCableClubWarp
	warp MAP_BATTLE_COLOSSEUM_4P, 5, 8
	special DoCableClubWarp
	end

Kanto_CableClub_EventScript_AbortLinkIncorrectNumberOfBattlers::
	switch VAR_0x8004
	case USING_SINGLE_BATTLE, Kanto_CableClub_EventScript_AbortLinkWrongNumberForSingleBattle
	case USING_DOUBLE_BATTLE, Kanto_CableClub_EventScript_AbortLinkWrongNumberForDoubleBattle
	case USING_MULTI_BATTLE, Kanto_CableClub_EventScript_AbortLinkNeedFourPlayers
	goto Kanto_CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	end

Kanto_CableClub_EventScript_AbortLinkNeedFourPlayers::
	special CloseLink
	msgbox Kanto_CableClub_Text_NeedFourPlayers
	goto Kanto_CableClub_EventScript_ConfirmNumberAndRestart
	end

Kanto_CableClub_EventScript_AbortLinkWrongNumberForDoubleBattle::
	special CloseLink
	msgbox Kanto_CableClub_Text_CantDoubleBattleWithXPlayers
	goto Kanto_CableClub_EventScript_ConfirmNumberAndRestart
	end

Kanto_CableClub_EventScript_AbortLinkWrongNumberForSingleBattle::
	special CloseLink
	msgbox Kanto_CableClub_Text_CantSingleBattleWithXPlayers
	goto Kanto_CableClub_EventScript_ConfirmNumberAndRestart
	end

Kanto_CableClub_EventScript_ConfirmNumberAndRestart::
	special CloseLink  /* Redundant */
	special HelpSystem_Enable
	msgbox Kanto_CableClub_Text_PleaseConfirmNumberAndRestart
	release
	end

Kanto_CableClub_EventScript_TradeCenter::
	copyvar VAR_0x8007, VAR_LAST_TALKED
	call Kanto_CableClub_EventScript_CheckPartyTradeRequirements
	goto_if_eq VAR_RESULT, 0, Kanto_CableClub_EventScript_AbortLink
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, Kanto_CableClub_EventScript_AbortLink
	message CableClub_Text_PleaseWaitBCancel
	waitmessage
	special HelpSystem_Disable
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special TryTradeLinkup
	call EventScript_RestorePrevTextColor
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Kanto_CableClub_EventScript_EnterTradeCenter
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, Kanto_CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, Kanto_CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, Kanto_CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Kanto_CableClub_EventScript_AbortLink
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, Kanto_CableClub_EventScript_AbortLinkConnectionError
	goto_if_eq VAR_RESULT, LINKUP_PLAYER_NOT_READY, Kanto_CableClub_EventScript_AbortLinkPlayerNotReady
	goto_if_eq VAR_RESULT, LINKUP_PARTNER_NOT_READY, Kanto_CableClub_EventScript_AbortLinkOtherTrainerNotReady
	end

Kanto_CableClub_EventScript_EnterTradeCenter::
	setvar VAR_0x8004, USING_TRADE_CENTER
	copyvar VAR_KANTO_CABLE_CLUB_STATE, VAR_0x8004
	messageautoscroll Kanto_CableClub_Text_PleaseEnter
	waitmessage
	call Kanto_CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Kanto_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, MAP_UNDEFINED
	closedoor 9, 1
	waitdooranim
	release
	special SetCableClubWarp
	setwarp MAP_TRADE_CENTER, 5, 8
	special DoCableClubWarp
	end

Kanto_CableClub_EventScript_CheckPartyTradeRequirements::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_lt VAR_RESULT, 2, Kanto_CableClub_EventScript_NeedTwoMonsToTrade
	specialvar VAR_RESULT, DoesPartyHaveEnigmaBerry
	goto_if_eq VAR_RESULT, TRUE, Kanto_CableClub_EventScript_CantTradeEnigmaBerry
	setvar VAR_RESULT, TRUE
	return

Kanto_CableClub_EventScript_NeedTwoMonsToTrade::
	msgbox Kanto_CableClub_Text_NeedTwoMonsToTrade
	setvar VAR_RESULT, FALSE
	return

Kanto_CableClub_EventScript_CantTradeEnigmaBerry::
	msgbox Kanto_CableClub_Text_CantTradeEnigmaBerry
	setvar VAR_RESULT, FALSE
	return

/* Record Corner is nopped in FRLG */
Kanto_CableClub_EventScript_RecordCorner::
	end

Kanto_CableClub_EventScript_AbortLinkPlayerNotReady::
	special CloseLink
	special HelpSystem_Enable
	msgbox Kanto_CableClub_Text_NotSetUpForFarAwayRegion
	release
	end

Kanto_CableClub_EventScript_AbortLinkOtherTrainerNotReady::
	special CloseLink
	special HelpSystem_Enable
	msgbox Kanto_CableClub_Text_OtherTrainerNotReady
	release
	end

Kanto_CableClub_EventScript_AbortLinkConnectionError::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_LinkErrorPleaseReset
	release
	end

Kanto_CableClub_EventScript_AbortLinkSomeoneNotReady::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_SomeoneIsNotReadyToLink
	release
	end

Kanto_CableClub_EventScript_AbortLinkDifferentSelections::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_PlayersMadeDifferentSelections
	release
	end

Kanto_CableClub_EventScript_AbortLink::
	special CloseLink
	special HelpSystem_Enable
	msgbox Kanto_CableClub_Text_PleaseVisitAgain
	release
	end

CableClub_EventScript_AbortMinigame::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_ComeAgain
	release
	end

/* Unused */
Kanto_CableClub_EventScript_CableClubWarp::
	special SetCableClubWarp
	special DoCableClubWarp
	end

Kanto_CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants::
	special CloseLink
	special HelpSystem_Enable
	msgbox Kanto_CableClub_Text_IncorrectNumberOfParticipants
	release
	end

Kanto_CableClub_EventScript_AbortLinkPlayerHasBadEgg::
	special CloseLink
	special HelpSystem_Enable
	msgbox Kanto_CableClub_Text_YouHaveAMonThatCantBeTaken
	release
	end

Kanto_CableClub_EventScript_WirelessClubAdjustements::
	msgbox Text_WirelessClubUndergoingAdjustments
	release
	end

Kanto_CableClub_EventScript_NotReadyYet::
	msgbox Text_AppearsToBeUndergoingAdjustments
	releaseall
	end

Kanto_Movement_AttendantFaceDown::
	face_down
	step_end

/* Unused */
Kanto_Movement_AttendantFaceRight::
	face_right
	step_end

Kanto_Movement_AttendantFaceLeft::
	face_left
	step_end

Kanto_Movement_PlayerExitLinkRoom::
	walk_down
	walk_down
	step_end

Kanto_Movement_PlayerApproachLinkRoomRight::
	walk_right
	walk_up
	walk_up
	step_end

Kanto_Movement_PlayerApproachLinkRoomLeft::
	walk_left
	walk_up
	walk_up
	step_end

Kanto_Movement_PlayerEnterLinkRoom::
	walk_up
	step_end

/* Unused */
Kanto_Movement_PlayerFaceAttendantLeft::
	face_left
	step_end

Kanto_Movement_PlayerFaceAttendantRight::
	face_right
	step_end

Kanto_Movement_PlayerEnterMinigameRoom::
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

CableClub_EventScript_ShowBattleRecords::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 0
	special ShowBattleRecords
	waitstate
	releaseall
	end

BattleColosseum_2P_EventScript_PlayerSpot0::
	setvar VAR_0x8005, 0
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_2P_EventScript_PlayerSpot1::
	setvar VAR_0x8005, 1
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_PlayerSpot0::
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto_if_eq VAR_RESULT, 0, BattleColosseum_4P_EventScript_CancelSpotTrigger
	setvar VAR_0x8005, 0
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_PlayerSpot1::
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto_if_eq VAR_RESULT, 0, BattleColosseum_4P_EventScript_CancelSpotTrigger
	setvar VAR_0x8005, 1
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_PlayerSpot2::
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto_if_eq VAR_RESULT, 0, BattleColosseum_4P_EventScript_CancelSpotTrigger
	setvar VAR_0x8005, 2
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_PlayerSpot3::
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	goto_if_eq VAR_RESULT, 0, BattleColosseum_4P_EventScript_CancelSpotTrigger
	setvar VAR_0x8005, 3
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_CancelSpotTrigger::
	end

TradeCenter_EventScript_Chair0::
	setvar VAR_0x8005, 0
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterTradeSeat
	waitstate
	end

TradeCenter_EventScript_Chair1::
	setvar VAR_0x8005, 1
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterTradeSeat
	waitstate
	end

/* Unused */
TradeCenter_EventScript_Chair2::
	setvar VAR_0x8005, 2
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterTradeSeat
	waitstate
	end

/* Unused */
TradeCenter_EventScript_Chair3::
	setvar VAR_0x8005, 3
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterTradeSeat
	waitstate
	end

/* Nop in FRLG */
/* Separate labels to match GetDirectionForEventScript */
RecordCorner_EventScript_Spot0::
RecordCorner_EventScript_Spot1::
RecordCorner_EventScript_Spot2::
RecordCorner_EventScript_Spot3::
	end

Kanto_CableClub_EventScript_ReadTrainerCard::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox Text_LookedAtPlayersTrainerCard
	fadescreen FADE_TO_BLACK
	special Script_ShowLinkTrainerCard
	end

Kanto_CableClub_EventScript_ReadTrainerCardColored::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox Text_LookedAtPlayersTrainerCardColored
	fadescreen FADE_TO_BLACK
	special Script_ShowLinkTrainerCard
	end

Kanto_CableClub_EventScript_TooBusyToNotice::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox Text_TrainerTooBusyToNotice
	closemessage
	end

Kanto_BattleColosseum_2P_EventScript_Attendant::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special Script_FacePlayer
	msgbox Text_TakeSeatStartBattle
	special Script_ClearHeldMovement
	closemessage
	end

Kanto_TradeCenter_EventScript_Attendant::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special Script_FacePlayer
	msgbox Text_TakeSeatStartTrade
	special Script_ClearHeldMovement
	closemessage
	end

/* Nop in FRLG */
Kanto_RecordCorner_EventScript_Attendant::
	end

TradeCenter_ConfirmLeaveRoom::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox Text_TerminateLinkIfYouLeaveRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TradeCenter_TerminateLink
	erasebox 0, 0, 29, 19
	releaseall
	end

TradeCenter_TerminateLink::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	messageautoscroll Kanto_Text_TerminateLinkConfirmation
	waitmessage
	special ExitLinkRoom
	end

CableClub_EventScript_DoLinkRoomExit::
	special CleanupLinkRoomState
	special ReturnFromLinkRoom
	end

Kanto_CableClub_EventScript_UnionRoomAttendant::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	goto_if_unset FLAG_SYS_POKEDEX_GET, Kanto_CableClub_EventScript_WirelessClubAdjustements
	specialvar VAR_RESULT, IsBadEggInParty
	goto_if_eq VAR_RESULT, TRUE, Kanto_CableClub_EventScript_AbortLinkPlayerHasBadEgg
	copyvar VAR_0x8007, VAR_LAST_TALKED
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, FALSE, Kanto_CableClub_EventScript_UnionRoomAdapterNotConnected
	message Kanto_CableClub_Text_WelcomeUnionRoomEnter
	waitmessage
	goto CableClub_EventScript_AskEnterUnionRoom
	end

CableClub_EventScript_AskEnterUnionRoom::
	multichoice 18, 6, KANTO_MULTICHOICE_YES_NO_INFO, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_EnterUnionRoom
	case 1, Kanto_CableClub_EventScript_AbortLink
	case 2, Kanto_CableClub_EventScript_UnionRoomInfo
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_UnionRoomInfo::
	message Kanto_CableClub_Text_UnionRoomInfo
	waitmessage
	goto CableClub_EventScript_AskEnterUnionRoom
	end

Kanto_CableClub_EventScript_EnterUnionRoom::
	call Kanto_CableClub_EventScript_CheckPartyUnionRoomRequirements
	goto_if_eq VAR_RESULT, FALSE, Kanto_CableClub_EventScript_AbortLink
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, Kanto_CableClub_EventScript_AbortLink
	msgbox Kanto_CableClub_Text_EnjoyUnionRoom
	closemessage
	special HealPlayerParty
	setvar VAR_0x8004, USING_UNION_ROOM
	copyvar VAR_KANTO_CABLE_CLUB_STATE, VAR_0x8004
	special HelpSystem_Disable
	call Kanto_CableClub_EventScript_OpenUnionRoomBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Kanto_Movement_AttendantFaceLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 5, 1
	waitdooranim
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, MAP_UNDEFINED
	closedoor 5, 1
	waitdooranim
	special Script_ResetUnionRoomTrade
	special SetCableClubWarp
	warpspinenter MAP_UNION_ROOM, 7, 11
	waitstate
	special RunUnionRoom
	waitstate
	end

Kanto_CableClub_EventScript_CheckPartyUnionRoomRequirements::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_lt VAR_RESULT, 2, Kanto_CableClub_EventScript_NeedTwoMonsForUnionRoom
	specialvar VAR_RESULT, DoesPartyHaveEnigmaBerry
	goto_if_eq VAR_RESULT, TRUE, Kanto_CableClub_EventScript_NoEnigmaBerryInUnionRoom
	setvar VAR_RESULT, TRUE
	return

Kanto_CableClub_EventScript_NeedTwoMonsForUnionRoom::
	msgbox Kanto_CableClub_Text_NeedTwoMonsForUnionRoom
	goto EventScript_SetResultFalse
	end

Kanto_CableClub_EventScript_NoEnigmaBerryInUnionRoom::
	msgbox Kanto_CableClub_Text_NoEnigmaBerryInUnionRoom
	goto EventScript_SetResultFalse
	end

Kanto_CableClub_EventScript_UnionRoomAdapterNotConnected::
	msgbox Kanto_CableClub_Text_UnionRoomAdapterNotConnected
	release
	return

Kanto_CableClub_EventScript_WirelessClubAttendant::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_POKEDEX_GET, Kanto_CableClub_EventScript_WirelessClubAdjustements
	msgbox Kanto_CableClub_Text_AskAboutLinking, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Kanto_CableClub_EventScript_DontAskAboutLinking
	msgbox Kanto_CableClub_Text_ExplainWirelessClub
	release
	return

Kanto_CableClub_EventScript_DontAskAboutLinking::
	msgbox Kanto_CableClub_Text_HopeYouEnjoyWirelessSystem
	release
	return

Kanto_CableClub_EventScript_DirectCornerAttendant::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	goto_if_unset FLAG_SYS_POKEDEX_GET, Kanto_CableClub_EventScript_WirelessClubAdjustements
	specialvar VAR_RESULT, IsBadEggInParty
	goto_if_eq VAR_RESULT, TRUE, Kanto_CableClub_EventScript_AbortLinkPlayerHasBadEgg
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, FALSE, Kanto_CableClub_EventScript_WelcomeToCableClub
	message Kanto_CableClub_Text_WelcomeWhichDirectCornerRoom
	waitmessage
	delay 15
	goto Kanto_CableClub_EventScript_DirectCornerSelectService
	end

Kanto_CableClub_EventScript_DirectCornerSelectService::
	goto_if_unset FLAG_KANTO_GOT_POWDER_JAR, Kanto_CableClub_EventScript_DirectCornerNoBerry
	multichoice 0, 0, KANTO_MULTICHOICE_TRADE_COLOSSEUM_CRUSH, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_WirelessTrade
	case 1, Kanto_CableClub_EventScript_WirelessBattleSelect
	case 2, Kanto_CableClub_EventScript_WirelessBerryCrush
	case 3, Kanto_CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_DirectCornerNoBerry::
	multichoice 0, 0, KANTO_MULTICHOICE_TRADE_COLOSSEUM_2, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_WirelessTrade
	case 1, Kanto_CableClub_EventScript_WirelessBattleSelect
	case 2, Kanto_CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_WirelessTrade::
	msgbox Kanto_CableClub_Text_TradePokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Kanto_CableClub_EventScript_AbortLink
	call Kanto_CableClub_EventScript_CheckPartyTradeRequirements
	goto_if_eq VAR_RESULT, FALSE, Kanto_CableClub_EventScript_AbortLink
	setvar VAR_0x8004, LINK_GROUP_TRADE
	goto Kanto_CableClub_EventScript_SaveAndChooseLinkLeader
	end

Kanto_CableClub_EventScript_WirelessBattleSelect::
	message Kanto_CableClub_Text_PlayWhichBattleMode
	waitmessage
	multichoice 0, 0, KANTO_MULTICHOICE_SINGLE_DOUBLE_MULTI_INFO_EXIT, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_WirelessSingleBattle
	case 1, Kanto_CableClub_EventScript_WirelessDoubleBattle
	case 2, Kanto_CableClub_EventScript_WirelessMultiBattle
	case 3, Kanto_CableClub_EventScript_WirelessBattleInfo
	case 4, Kanto_CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_WirelessSingleBattle::
	setvar VAR_0x8004, LINK_GROUP_SINGLE_BATTLE
	goto Kanto_CableClub_EventScript_SaveAndChooseLinkLeader
	end

Kanto_CableClub_EventScript_WirelessDoubleBattle::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, Kanto_CableClub_EventScript_TwoMonsNeededForWirelessDoubleBattle
	setvar VAR_0x8004, LINK_GROUP_DOUBLE_BATTLE
	goto Kanto_CableClub_EventScript_SaveAndChooseLinkLeader
	end

Kanto_CableClub_EventScript_TwoMonsNeededForWirelessDoubleBattle::
	msgbox Kanto_CableClub_Text_NeedTwoMonsForDoubleBattle
	goto Kanto_CableClub_EventScript_WirelessBattleSelect
	end

Kanto_CableClub_EventScript_WirelessMultiBattle::
	setvar VAR_0x8004, LINK_GROUP_MULTI_BATTLE
	goto Kanto_CableClub_EventScript_SaveAndChooseLinkLeader
	end

Kanto_CableClub_EventScript_WirelessBattleInfo::
	msgbox Kanto_CableClub_Text_ExplainBattleModes
	goto Kanto_CableClub_EventScript_WirelessBattleSelect
	end

Kanto_CableClub_EventScript_WirelessBerryCrush::
	msgbox Kanto_CableClub_Text_UseBerryCrush, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Kanto_CableClub_EventScript_AbortLink
	special HasAtLeastOneBerry
	goto_if_eq VAR_RESULT, FALSE, Kanto_CableClub_EventScript_NeedBerryForBerryCrush
	setvar VAR_0x8004, LINK_GROUP_BERRY_CRUSH
	goto Kanto_CableClub_EventScript_SaveAndChooseLinkLeader
	end

Kanto_CableClub_EventScript_NeedBerryForBerryCrush::
	msgbox Kanto_CableClub_Text_NeedBerryForBerryCrush
	goto Kanto_CableClub_EventScript_DirectCornerSelectService
	end

Kanto_CableClub_EventScript_SaveAndChooseLinkLeader::
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, Kanto_CableClub_EventScript_AbortLink
	switch VAR_0x8004
	case LINK_GROUP_TRADE, Kanto_CableClub_EventScript_ChooseLinkLeaderFrom2
	case LINK_GROUP_SINGLE_BATTLE, Kanto_CableClub_EventScript_ChooseLinkLeaderFrom2
	case LINK_GROUP_DOUBLE_BATTLE, Kanto_CableClub_EventScript_ChooseLinkLeaderFrom2
	case LINK_GROUP_MULTI_BATTLE, Kanto_CableClub_EventScript_ChooseLinkLeaderFrom4
	case LINK_GROUP_BERRY_CRUSH, Kanto_CableClub_EventScript_ChooseLinkLeader
	end

Kanto_CableClub_EventScript_ChooseLinkLeaderFrom2::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message Kanto_CableClub_Text_ChooseGroupLeaderOfTwo
	waitmessage
	call EventScript_RestorePrevTextColor
	multichoice 13, 6, KANTO_MULTICHOICE_JOIN_OR_LEAD, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_TryJoinGroup2Players
	case 1, Kanto_CableClub_EventScript_TryLeadGroup2Players
	case 2, Kanto_CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_TryLeadGroup2Players::
	call Kanto_CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Kanto_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Kanto_CableClub_EventScript_ChooseLinkLeaderFrom2
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, Kanto_CableClub_EventScript_TryLeadGroup2Players
	release
	return

Kanto_CableClub_EventScript_TryJoinGroup2Players::
	call Kanto_CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Kanto_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Kanto_CableClub_EventScript_ChooseLinkLeaderFrom2
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, Kanto_CableClub_EventScript_TryJoinGroup2Players
	release
	return

Kanto_CableClub_EventScript_ChooseLinkLeaderFrom4::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message Kanto_CableClub_Text_ChooseGroupLeaderOfFour
	waitmessage
	call EventScript_RestorePrevTextColor
	multichoice 13, 6, KANTO_MULTICHOICE_JOIN_OR_LEAD, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_TryJoinGroup4Players
	case 1, Kanto_CableClub_EventScript_TryLeadGroup4Players
	case 2, Kanto_CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_TryLeadGroup4Players::
	call Kanto_CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Kanto_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Kanto_CableClub_EventScript_ChooseLinkLeaderFrom4
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, Kanto_CableClub_EventScript_TryLeadGroup4Players
	release
	return

Kanto_CableClub_EventScript_TryJoinGroup4Players::
	call Kanto_CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Kanto_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Kanto_CableClub_EventScript_ChooseLinkLeaderFrom4
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, Kanto_CableClub_EventScript_TryJoinGroup4Players
	release
	return

Kanto_CableClub_EventScript_ChooseLinkLeader::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message Kanto_CableClub_Text_ChooseGroupLeader
	waitmessage
	call EventScript_RestorePrevTextColor
	multichoice 13, 6, KANTO_MULTICHOICE_JOIN_OR_LEAD, FALSE
	switch VAR_RESULT
	case 0, Kanto_CableClub_EventScript_TryJoinGroupXPlayers
	case 1, Kanto_CableClub_EventScript_TryLeadGroupXPlayers
	case 2, Kanto_CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, Kanto_CableClub_EventScript_AbortLink
	end

Kanto_CableClub_EventScript_TryLeadGroupXPlayers::
	call Kanto_CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Kanto_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Kanto_CableClub_EventScript_ChooseLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, Kanto_CableClub_EventScript_TryLeadGroupXPlayers
	release
	return

Kanto_CableClub_EventScript_TryJoinGroupXPlayers::
	call Kanto_CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Kanto_CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Kanto_CableClub_EventScript_ChooseLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, Kanto_CableClub_EventScript_TryJoinGroupXPlayers
	release
	return

Kanto_CableClub_EventScript_TryBecomeLinkLeader::
	special HelpSystem_Disable
	special TryBecomeLinkLeader
	return

Kanto_CableClub_EventScript_TryJoinLinkGroup::
	special HelpSystem_Disable
	special TryJoinLinkGroup
	return

Kanto_CableClub_EventScript_EnterWirelessLinkRoom::
	messageautoscroll Kanto_CableClub_Text_DirectYouToYourRoom
	waitmessage
	delay 60
	closemessage
	copyvar VAR_0x8007, VAR_LAST_TALKED
	call Kanto_CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Kanto_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, MAP_UNDEFINED
	closedoor 9, 1
	waitdooranim
	release
	waitstate
	end

CableClub_EventScript_ShowWirelessCommunicationScreen::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_SYS_POKEDEX_GET, Kanto_CableClub_EventScript_NotReadyYet
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, FALSE, Kanto_CableClub_EventScript_AdapterNotConnected
	special HelpSystem_Disable
	fadescreen FADE_TO_BLACK
	special ShowWirelessCommunicationScreen
	msgbox Kanto_CableClub_Text_ParticipantsStepUpToCounter
	special HelpSystem_Enable
	releaseall
	end

Kanto_CableClub_EventScript_AdapterNotConnected::
	msgbox Kanto_CableClub_Text_AdapterNotConnected
	releaseall
	end

Kanto_CableClub_EventScript_OpenUnionRoomBarrier::
	setmetatile 5, 3, METATILE_PokemonCenter_Floor_ShadeLeft, 0
	return

Kanto_CableClub_EventScript_CloseUnionRoomBarrier::
	setmetatile 5, 3, KANTO_METATILE_PokemonCenter_CounterBarrier, 1
	return

Kanto_CableClub_EventScript_OpenDirectCornerBarrier::
	setmetatile 9, 3, METATILE_PokemonCenter_Floor_ShadeLeft, 0
	return

Kanto_CableClub_EventScript_CloseDirectCornerBarrier::
	setmetatile 9, 3, KANTO_METATILE_PokemonCenter_CounterBarrier, 1
	return

CableClub_EventScript_OpenGameCornerBarrier::
	setmetatile 5, 3, METATILE_GameCorner_CheckeredFloor_ShadeLeft, 0
	return

CableClub_EventScript_CloseGameCornerBarrier::
	setmetatile 5, 3, METATILE_GameCorner_CounterBarrier, 1
	return

Kanto_CableClub_OnResume::
	special InitUnionRoom
	end

JoyfulGameCorner_EventScript_InfoMan2::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	message Text_DescribeWhichGame
	waitmessage
	multichoice 0, 0, KANTO_MULTICHOICE_POKEJUMP_DODRIO, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_PokemonJumpInfo
	case 1, CableClub_EventScript_DodrioBerryPickingInfo
	case 2, CableClub_EventScript_MinigameInfoExit
	case SCR_MENU_CANCEL, CableClub_EventScript_MinigameInfoExit
	end

CableClub_EventScript_PokemonJumpInfo::
	msgbox Text_PokemonJumpInfo
	release
	end

CableClub_EventScript_DodrioBerryPickingInfo::
	msgbox Text_DodrioBerryPickingInfo
	release
	end

CableClub_EventScript_MinigameInfoExit::
	msgbox Text_TalkToManToPlay
	release
	end

JoyfulGameCorner_EventScript_MinigameAttendant::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	message Text_WelcomeCanYouWait
	waitmessage
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_AdapterNotConnectedMinigame
	delay 60
	special HelpSystem_Disable
	message Text_PlayWhichGame
	waitmessage
	multichoice 0, 0, KANTO_MULTICHOICE_POKEJUMP_DODRIO, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_PlayPokemonJump
	case 1, CableClub_EventScript_PlayDodrioBerryPicking
	case 2, CableClub_EventScript_AbortMinigame
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortMinigame
	end

CableClub_EventScript_PlayPokemonJump::
	setvar VAR_0x8005, 0
	special IsPokemonJumpSpeciesInParty
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_NoEligiblePkmn
	msgbox Text_EnterWhichPokemon
	setvar VAR_0x8005, 0
	special ChooseMonForWirelessMinigame
	goto_if_ge VAR_0x8004, PARTY_SIZE, CableClub_EventScript_AbortMinigame
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortMinigame
	setvar VAR_0x8004, LINK_GROUP_POKEMON_JUMP
	goto CableClub_EventScript_ChooseLinkLeaderMinigame
	end

CableClub_EventScript_PlayDodrioBerryPicking::
	setvar VAR_0x8005, 1
	special IsDodrioInParty
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_NoEligiblePkmn
	msgbox Text_EnterWhichPokemon
	setvar VAR_0x8005, 1
	special ChooseMonForWirelessMinigame
	goto_if_ge VAR_0x8004, PARTY_SIZE, CableClub_EventScript_AbortMinigame
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortMinigame
	setvar VAR_0x8004, LINK_GROUP_BERRY_PICKING
	goto CableClub_EventScript_ChooseLinkLeaderMinigame
	end

CableClub_EventScript_ChooseLinkLeaderMinigame::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message Kanto_CableClub_Text_ChooseGroupLeader
	waitmessage
	call EventScript_RestorePrevTextColor
	multichoice 13, 6, KANTO_MULTICHOICE_JOIN_OR_LEAD, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_TryJoinMinigameLinkGroup
	case 1, CableClub_EventScript_TryBecomeMinigameLinkLeader
	case 2, CableClub_EventScript_AbortMinigame
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortMinigame
	end

CableClub_EventScript_TryBecomeMinigameLinkLeader::
	call Kanto_CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterMinigame
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeaderMinigame
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryBecomeMinigameLinkLeader
	release
	return

CableClub_EventScript_TryJoinMinigameLinkGroup::
	call Kanto_CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterMinigame
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeaderMinigame
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryJoinMinigameLinkGroup
	release
	return

CableClub_EventScript_EnterMinigame::
	messageautoscroll Text_AllGoodToGo
	waitmessage
	delay 120
	closemessage
	copyvar VAR_0x8007, VAR_LAST_TALKED
	call CableClub_EventScript_OpenGameCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Kanto_Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement LOCALID_PLAYER, Kanto_Movement_PlayerEnterMinigameRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, MAP_UNDEFINED
	release
	waitstate
	end

CableClub_EventScript_AdapterNotConnectedMinigame::
	msgbox Text_AdapterNotConnectedMinigame
	release
	end

CableClub_EventScript_NoEligiblePkmn::
	msgbox EventScript_ExplainPokemonJumpRequirements, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CableClub_EventScript_AbortMinigame
	call_if_eq VAR_0x8005, 0, CableClub_EventScript_ExplainPokemonJumpRequirements
	call_if_eq VAR_0x8005, 1, CableClub_EventScript_ExplainDodrioBerryPickingRequirements
	goto CableClub_EventScript_AbortMinigame
	end

CableClub_EventScript_ExplainPokemonJumpRequirements::
	msgbox Text_ShortJumpingPokemonAllowed
	return

CableClub_EventScript_ExplainDodrioBerryPickingRequirements::
	msgbox Text_OnlyDodrioAllowed
	return

TwoIsland_JoyfulGameCorner_EventScript_ShowPokemonJumpRecords::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	special ShowPokemonJumpRecords
	releaseall
	end

TwoIsland_JoyfulGameCorner_EventScript_ShowDodrioBerryPickingRecords::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	special ShowDodrioBerryPickingRecords
	releaseall
	end

Kanto_CableClub_Text_WelcomeWhichCableClubService::
	.string "Bienvenue au CENTRE TROC\n"
	.string "du CLUB LINK POKéMON.\p"
	.string "Lequel de nos services\n"
	.string "souhaiteriez-vous utiliser?$"

Kanto_CableClub_Text_WhichService::
	.string "Lequel de nos services\n"
	.string "souhaiteriez-vous utiliser?$"

CableClub_Text_TradeMonsUsingLinkCable::
	.string "Echanger ses POKéMON avec un\n"
	.string "câble GBA Game Link.$"

Kanto_CableClub_Text_BattleUsingLinkCable::
	.string "Vous pouvez affronter un autre\n"
	.string "joueur avec un câble Game Link.$"

/* Unused, translated in Emerald */
Kanto_CableClub_Text_CloseThisMenu::
	.string "おわります$"

Kanto_CableClub_Text_NeedTwoMonsForDoubleBattle::
	.string "Pour jouer en COMBAT DUO, il faut\n"
	.string "avoir au moins deux POKéMON.$"

Kanto_CableClub_Text_NeedTwoMonsToTrade::
	.string "Pour un échange, \p"
	.string "il faut avoir au moins deux\n"
	.string "POKéMON en sa possession.$"

Kanto_CableClub_Text_CantTradeEnigmaBerry::
	.string "Un POKéMON tenant la BAIE\n"
	.string "{STR_VAR_1} ne peut pas être échangé.$"

CableClub_Text_PleaseWaitBCancel::
	.string "Veuillez patienter.\n"
	.string "Bouton B: Annuler$"

CableClub_Text_WhenAllPlayersReadyAConfirmBCancel::
	.string "Quand tous les joueurs sont prêts…\n"
	.string "Bouton A: Confirmer\l"
	.string "Bouton B: Annuler$"

CableClub_Text_StartLinkWithXPlayersAConfirmBCancel::
	.string "Démarrer connexion entre les {STR_VAR_1}\n"
	.string "joueurs.\l"
	.string "Bouton A: Confirmer\l"
	.string "Bouton B: Annuler$"

CableClub_Text_AwaitingLinkupBCancel::
	.string "Connexion en cours…\n"
	.string "Bouton B: Annuler$"

/* Unused, translated in Emerald */
Kanto_CableClub_Text_OkayToSaveProgress::
	.string "はじめる　まえに　レポートを\n"
	.string "かきますが　よろしいですか？$"

Kanto_CableClub_Text_PleaseEnter::
	.string "Veuillez entrer.$"

Kanto_CableClub_Text_DirectYouToYourRoom::
	.string "Je vais vous mener à la salle.$"

CableClub_Text_SomeoneIsNotReadyToLink::
	.string "Quelqu'un n'est pas prêt à se\n"
	.string "connecter.\p"
	.string "Veuillez revenir une fois que tous\n"
	.string "les joueurs seront prêts.$"

CableClub_Text_LinkErrorPleaseReset::
	.string "Erreur de connexion…\n"
	.string "Vérifier les branchements et\l"
	.string "réinitialiser les consoles.$"

CableClub_Text_PlayersMadeDifferentSelections::
	.string "Les joueurs connectés semblent\n"
	.string "ne pas avoir fait le même choix.$"

Kanto_CableClub_Text_PleaseVisitAgain::
	.string "Revenez quand vous voulez.$"

Kanto_CableClub_Text_IncorrectNumberOfParticipants::
	.string "Le nombre de participants n'est pas\n"
	.string "correct.$"

Kanto_CableClub_Text_CantSingleBattleWithXPlayers::
	.string "Il est impossible de jouer avec {STR_VAR_1}\n"
	.string "joueurs en mode COMBAT SOLO.$"

Kanto_CableClub_Text_CantDoubleBattleWithXPlayers::
	.string "Il est impossible de jouer avec {STR_VAR_1}\n"
	.string "joueurs en mode COMBAT DUO.$"

Kanto_CableClub_Text_NeedFourPlayers::
	.string "Il faut être quatre joueurs pour\n"
	.string "jouer à ce mode de combat.$"

Kanto_CableClub_Text_PleaseConfirmNumberAndRestart::
	.string "Veuillez confirmer le nombre de\n"
	.string "joueurs et recommencer.$"

Text_TerminateLinkIfYouLeaveRoom::
	.string "La connexion prendra fin si vous\n"
	.string "quittez la pièce. Sortir?$"

Kanto_Text_TerminateLinkConfirmation::
	.string "Fin de la connexion. On vous\n"
	.string "conduira à la sortie de la pièce.\l"
	.string "Veuillez patienter.$"

Text_TrainerTooBusyToNotice::
	.string "Ce DRESSEUR est trop occupé\n"
	.string "pour vous voir…$"

Text_LookedAtPlayersTrainerCard::
	.string "Bravo! Tu peux regarder la CARTE\n"
	.string "DRESSEUR de {STR_VAR_1}!$"

Text_LookedAtPlayersTrainerCardColored::
	.string "Bravo! Tu peux regarder la CARTE\n"
	.string "DRESSEUR de {STR_VAR_1}!\p"
	.string "C'est une carte en {STR_VAR_2}!$"

Text_TakeSeatStartBattle::
	.string "Veuillez prendre place et\n"
	.string "commencer à combattre.$"

Text_TakeSeatStartTrade::
	.string "Veuillez prendre place et\n"
	.string "commencer l'échange.$"

/* Unused, leftover from RS */
Kanto_RecordCorner_Text_ThanksForComing::
	.string "ごりよう　ありがとう　ございました$"

Kanto_CableClub_Text_TrainerCardDataOverwritten::
	.string "Les données sur la CARTE DRESSEUR\n"
	.string "vont être écrasées.$"

Kanto_CableClub_Text_HopeToSeeYouAgain::
	.string "A une prochaine fois!$"

Kanto_CableClub_Text_NotSetUpForFarAwayRegion::
	.string "Je suis terriblement désolée.\p"
	.string "Nous ne sommes pas équipés pour\n"
	.string "effectuer des échanges avec des\l"
	.string "DRESSEURS d'une région si lointaine.$"

Kanto_CableClub_Text_OtherTrainerNotReady::
	.string "L'autre DRESSEUR n'est pas prêt.$"

Kanto_CableClub_Text_YouHaveAMonThatCantBeTaken::
	.string "Au moins un POKéMON ne peut\n"
	.string "pas être pris.$"

Kanto_CableClub_Text_AdapterNotConnected::
	.string "L'adaptateur sans fil GBA n'est pas\n"
	.string "connecté correctement.$"

Kanto_CableClub_Text_ParticipantsStepUpToCounter::
	.string "Les participants doivent se\n"
	.string "présenter à la réception.$"

/* Unused, translated in Emerald */
Kanto_CableClub_Text_Hello::
	.string "こんにちは！$"

/* Unused, translated in Emerald */
Kanto_CableClub_Text_PleaseWait::
	.string "しょうしょう　おまちください$"

Kanto_CableClub_Text_YouMayTradeHere::
	.string "Vous pouvez y faire des échanges\n"
	.string "de POKéMON avec un ami.$"

Kanto_CableClub_Text_YouMayBattleHere::
	.string "Vous pouvez affronter vos amis ici.$"

Kanto_CableClub_Text_CanMakeBerryPowder::
	.string "De deux à cinq DRESSEURS peuvent\n"
	.string "faire de la POUDRE BAIE ensemble.$"

/* Unused, Record Mix nopped */
Kanto_CableClub_Text_CanMixRecords::
	.string "ワイヤレス　クラブでの\n"
	.string "あそびかたを　せつめいします$"

Kanto_CableClub_Text_CancelSelectedItem::
	.string "Annule le MENU sélectionné.$"

/* Unused, translated in Emerald */
Kanto_CableClub_Text_WhichBattleMode::
	.string "どちらの　しょうぶに　しますか？$"

/* Unused, translated in Emerald */
Kanto_CableClub_Text_ReturnsToPreviousStep::
	.string "ひとつ　まえに　もどります$"

Kanto_CableClub_Text_NeedBerryForBerryCrush::
	.string "Pour utiliser le BROYEUR DE BAIES,\n"
	.string "il faut avoir au moins une BAIE.$"

Kanto_CableClub_Text_NeedTwoMonsForUnionRoom::
	.string "Pour entrer dans la SALLE UNION,\n"
	.string "il faut avoir au moins deux PKMN.$"

Kanto_CableClub_Text_NoEnigmaBerryInUnionRoom::
	.string "Un PKMN tenant la BAIE {STR_VAR_1} ne\n"
	.string "peut entrer dans la SALLE UNION.$"

Kanto_CableClub_Text_UnionRoomAdapterNotConnected::
	.string "C'est la SALLE UNION du\n"
	.string "CLUB SANS FIL POKéMON.\p"
	.string "Votre adaptateur sans fil GBA\n"
	.string "n'est pas connecté correctement.\p"
	.string "Revenez plus tard.$"

/* Unused, translated in Emerald */
Kanto_CableClub_Text_OhExcuseMe::
	.string "あ‥‥\n"
	.string "おきゃくさま！$"

Text_PlayerIsPlayingRightNowGoForIt::
	.string "On dirait que {STR_VAR_1} est en\n"
	.string "train de jouer.\l"
	.string "Allez-y!$"

Text_DescribeWhichGame::
	.string "Je peux vous expliquer les règles\n"
	.string "du jeu, si vous le souhaitez.\p"
	.string "Vous voulez des infos sur\n"
	.string "quel jeu?$"

Text_PokemonJumpInfo::
	.string "SAUT POKéMON\p"
	.string "Faites sauter votre POKéMON à\n"
	.string "la corde avec le bouton A.\p"
	.string "Seuls les POKéMON jusqu'à\n"
	.string "environ 70 cm peuvent participer.\p"
	.string "Les POKéMON capables seulement\n"
	.string "de nager, creuser ou voler\p"
	.string "ne sont pas vraiment bons au saut\n"
	.string "et ne peuvent donc pas participer.\p"
	.string "Des choses intéressantes arrivent\n"
	.string "si tout le monde saute en rythme.$"

Text_DodrioBerryPickingInfo::
	.string "ATTRAPE-BAIES DODRIO\p"
	.string "Faites bouger les têtes de DODRIO\n"
	.string "pour attraper les BAIES.\p"
	.string "Appuyez sur gauche, haut et droite\n"
	.string "sur la manette {PLUS}.\p"
	.string "Pour jouer à ce jeu, vous devez\n"
	.string "avoir un DODRIO.$"

Text_TalkToManToPlay::
	.string "Si vous voulez commencer un jeu,\n"
	.string "allez voir l'homme à côté.$"

Text_WelcomeCanYouWait::
	.string "Salut! Vous pouvez jouer en\n"
	.string "utilisant le système de\l"
	.string "communication sans fil.\p"
	.string "Vous pouvez patienter encore\n"
	.string "un petit peu? $"

CableClub_Text_ComeAgain::
	.string "Très bien, à bientôt.$"

Text_AdapterNotConnectedMinigame::
	.string "L'adaptateur sans fil GBA n'est\n"
	.string "pas connecté.\p"
	.string "Revenez quand il sera branché!$"

Text_PlayWhichGame::
	.string "Très bien, quel jeu\n"
	.string "voulez-vous commencer?$"

Text_EnterWhichPokemon::
	.string "Quel POKéMON choisissez-vous?$"

Text_AllGoodToGo::
	.string "Parfait, ça va bientôt commencer.\n"
	.string "Ne vous faites pas battre.$"

/* Unused, translated in Emerald */
Text_LeavingDoComeAgain::
	.string "きょうは　けえるのか？\n"
	.string "またこいよ！$"

EventScript_ExplainPokemonJumpRequirements::
	.string "Aucun de vos POKéMON ne peut\n"
	.string "participer…\p"
	.string "Voulez-vous savoir quels POKéMON\n"
	.string "peuvent participer?$"

Text_ShortJumpingPokemonAllowed::
	.string "Le SAUT POKéMON est ouvert aux\n"
	.string "POKéMON jusqu'à environ 70 cm.\p"
	.string "Les POKéMON ne pouvant pas sauter\n"
	.string "ne peuvent pas participer.\p"
	.string "Comme ceux qui ne peuvent que\n"
	.string "nager, voler ou creuser.\p"
	.string "Voilà, c'est tout ce qu'il faut\n"
	.string "savoir.$"

Text_OnlyDodrioAllowed::
	.string "ATTRAPE-BAIES DODRIO\n"
	.string "Le nom parle de lui-même.\p"
	.string "Il vous faut un DODRIO pour\n"
	.string "participer.$"

/* Unused, translated in Emerald */
Text_RetryFromStartPlease::
	.string "もういちど　はじめから\n"
	.string "やりなおして　みて　くれ$"

Kanto_CableClub_Text_WelcomeWhichDirectCornerRoom::
	.string "Bienvenue au CLUB SANS FIL\n"
	.string "POKéMON.\p"
	.string "Vous pouvez communiquer avec\n"
	.string "vos amis à partir d'ici.\p"
	.string "A quelle salle voulez-vous\n"
	.string "accéder?$"

Kanto_CableClub_Text_TradePokemon::
	.string "Voulez-vous échanger un POKéMON?$"

Kanto_CableClub_Text_PlayWhichBattleMode::
	.string "A quel mode de combat\n"
	.string "voulez-vous jouer?$"

Kanto_CableClub_Text_UseBerryCrush::
	.string "Voulez-vous utiliser le\n"
	.string "BROYEUR DE BAIES?$"

Kanto_CableClub_Text_ExplainBattleModes::
	.string "Il existe trois modes de combat.\p"
	.string "En COMBAT SOLO, deux DRESSEURS\n"
	.string "avec au moins un POKéMON chacun\l"
	.string "combattent.\p"
	.string "Chaque DRESSEUR ne peut envoyer\n"
	.string "qu'un seul POKéMON à la fois au\l"
	.string "combat. \p"
	.string "En COMBAT DUO, deux DRESSEURS\n"
	.string "avec au moins deux POKéMON chacun\l"
	.string "combattent.\p"
	.string "Chaque DRESSEUR envoie au combat\n"
	.string "deux POKéMON en même temps.\p"
	.string "En COMBAT MULTI, quatre DRESSEURS\n"
	.string "avec au moins un POKéMON chacun\l"
	.string "combattent.\p"
	.string "Chaque DRESSEUR ne peut envoyer\n"
	.string "qu'un seul POKéMON à la fois au\l"
	.string "combat.$"

Kanto_CableClub_Text_ChooseGroupLeaderOfTwo::
	.string "Veuillez choisir lequel de vous\n"
	.string "deux sera le MENEUR.\p"
	.string "L'autre joueur devra ensuite\n"
	.string "choisir “JOINDRE”.$"

Kanto_CableClub_Text_ChooseGroupLeaderOfFour::
	.string "Veuillez choisir lequel d'entre\n"
	.string "vous sera le MENEUR du GROUPE.\p"
	.string "Les autres joueurs devront ensuite\n"
	.string "choisir “JOINDRE”.$"

Kanto_CableClub_Text_ChooseGroupLeader::
	.string "Veuillez choisir lequel d'entre\n"
	.string "vous sera le MENEUR du GROUPE.\p"
	.string "Les autres joueurs devront ensuite\n"
	.string "choisir “JOINDRE”.$"

Kanto_CableClub_Text_WelcomeUnionRoomEnter::
	.string "Bienvenue à la SALLE UNION du\n"
	.string "CLUB SANS FIL POKéMON.\p"
	.string "Vous pouvez y communiquer avec\n"
	.string "d'autres DRESSEURS. Même avec\l"
	.string "ceux que vous ne connaissez pas.$"

Kanto_CableClub_Text_UnionRoomInfo::
	.string "Les DRESSEURS dans la SALLE\n"
	.string "UNION sont ceux autour de vous qui\l"
	.string "ont aussi pénétré dans la salle.\p"
	.string "Vous pouvez faire plein de choses\n"
	.string "ici, comme par exemple discuter.\p"
	.string "Vous pouvez faire entrer 2 POKéMON\n"
	.string "jusqu'au niveau 30 pour un combat\p"
	.string "un contre un. Vous pouvez aussi\n"
	.string "participer à des tchats\p"
	.string "réunissant de 2 à 5 personnes.\p"
	.string "Ou vous pouvez encore enregistrer\n"
	.string "un POKéMON pour un échange.\p"
	.string "Voulez-vous entrer dans la SALLE?$"

Kanto_CableClub_Text_EnjoyUnionRoom::
	.string "J'espère que vous aimerez votre\n"
	.string "visite dans la SALLE UNION.$"

Kanto_CableClub_Text_FirstTimeRightThisWay::
	.string "Bonjour!\n"
	.string "Je suis ZADIA.\p"
	.string "C'est la première fois que je\n"
	.string "vous vois ici.\p"
	.string "Je vais vous montrer comment le\n"
	.string "système sans fil fonctionne.\p"
	.string "Je dois d'abord vous faire visiter\n"
	.string "cet étage du CENTRE POKéMON.\p"
	.string "Par ici, s'il vous plaît.$"

Kanto_CableClub_Text_ExplainWirelessClubFirstTime::
	.string "Au niveau supérieur, il y a\n"
	.string "deux salles.\p"
	.string "Tout d'abord, la salle à gauche\n"
	.string "est la SALLE UNION.\p"
	.string "Vous pouvez vous connecter avec\n"
	.string "les DRESSEURS autour de vous\l"
	.string "qui sont dans la SALLE UNION.\p"
	.string "Vous pouvez parler, faire des\n"
	.string "échanges ou combattre avec eux.\p"
	.string "Ensuite, la salle à droite\n"
	.string "est la SALLE LINK DIRECT. \p"
	.string "Vous pouvez combattre ou faire\n"
	.string "des échanges avec vos amis.\p"
	.string "Si l'adaptateur sans fil n'est pas\n"
	.string "utilisé, vous pouvez toujours vous\l"
	.string "connecter avec un câble Game Link.\p"
	.string "Si c'est le cas, allez directement\n"
	.string "dans la SALLE LINK DIRECT.\p"
	.string "J'espère que vous apprécierez\n"
	.string "le système sans fil.$"

Kanto_CableClub_Text_AskAboutLinking::
	.string "Bonjour {PLAYER}!\p"
	.string "Je suis ZADIA, je m'occupe du 1er\n"
	.string "étage du CENTRE POKéMON.\p"
	.string "Y a-t-il quelque chose que vous\n"
	.string "aimeriez savoir sur la connexion?$"

Kanto_CableClub_Text_ExplainWirelessClub::
	.string "Laissez-moi vous décrire le\n"
	.string "CLUB SANS FIL POKéMON.\p"
	.string "Au niveau supérieur, il y a\n"
	.string "deux salles.\p"
	.string "Tout d'abord, la salle à gauche\n"
	.string "est la SALLE UNION.\p"
	.string "Vous pouvez vous connecter avec\n"
	.string "les DRESSEURS autour de vous\l"
	.string "qui sont dans la SALLE UNION.\p"
	.string "Vous pouvez parler, faire des\n"
	.string "échanges ou combattre avec eux.\p"
	.string "Ensuite, la salle à droite\n"
	.string "est la SALLE LINK DIRECT. \p"
	.string "Vous pouvez combattre ou faire\n"
	.string "des échanges avec vos amis.\p"
	.string "Dans certains cas, vous ne\n"
	.string "pourrez vous connecter avec\l"
	.string "vos amis dans aucune des salles.\p"
	.string "Si c'est le cas, rapprochez-vous\n"
	.string "de vos amis.\p"
	.string "Si l'adaptateur sans fil n'est pas\n"
	.string "utilisé, vous pouvez toujours vous\l"
	.string "connecter avec un câble Game Link.\p"
	.string "Si c'est le cas, allez directement\n"
	.string "dans la SALLE LINK DIRECT.\p"
	.string "J'espère que vous apprécierez\n"
	.string "le système sans fil.$"

Kanto_CableClub_Text_HopeYouEnjoyWirelessSystem::
	.string "J'espère que vous apprécierez\n"
	.string "le système sans fil.$"
