
EventScript_RestorePrevTextColor::
	copyvar VAR_TEXT_COLOR, VAR_PREV_TEXT_COLOR
	return

EventScript_BufferPocketNameTryFanfare::
	switch VAR_RESULT
	case POCKET_ITEMS, Kanto_EventScript_BufferItemsPocket
	case POCKET_KEY_ITEMS, Kanto_EventScript_BufferKeyItemsPocket
	case POCKET_POKE_BALLS, EventScript_BufferPokeBallsPocket
	case POCKET_TM_CASE, EventScript_BufferTMCase
	case POCKET_BERRY_POUCH, EventScript_BufferBerryPouch
	end

Kanto_EventScript_BufferItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_KANTO_ITEMS_POCKET
	call_if_eq VAR_0x8007, TRUE, Kanto_EventScript_PlayFanfareObtainedItem
	return

Kanto_EventScript_BufferKeyItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_KANTO_KEY_ITEMS_POCKET
	call_if_eq VAR_0x8007, TRUE, Kanto_EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferPokeBallsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_KANTO_POKEBALLS_POCKET
	call_if_eq VAR_0x8007, TRUE, Kanto_EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferTMCase::
	bufferstdstring STR_VAR_3, STDSTRING_KANTO_TM_CASE
	call_if_eq VAR_0x8007, TRUE, Kanto_EventScript_PlayFanfareObtainedTMHM
	return

EventScript_BufferBerryPouch::
	bufferstdstring STR_VAR_3, STDSTRING_KANTO_BERRY_POUCH
	call_if_eq VAR_0x8007, TRUE, Kanto_EventScript_PlayFanfareObtainedItem
	return

Kanto_EventScript_PlayFanfareObtainedItem::
	playfanfare MUS_LEVEL_UP
	return

Kanto_EventScript_PlayFanfareObtainedTMHM::
	playfanfare MUS_LEVEL_UP
	return

Kanto_EventScript_HiddenItemScript::
	lockall
	textcolor NPC_TEXT_COLOR_NEUTRAL
	waitse
	goto_if_eq VAR_0x8005, 0, EventScript_TryPickUpHiddenCoins
	call EventScript_TryPickUpHiddenItem
	goto_if_eq VAR_0x8007, TRUE, EventScript_PickedUpHiddenItem
	goto_if_eq VAR_0x8007, FALSE, Kanto_EventScript_NoRoomForHiddenItem
	end

EventScript_TryPickUpHiddenItem::
	additem VAR_0x8005, VAR_0x8006
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemname STR_VAR_2, VAR_0x8005
	checkitemtype VAR_0x8005
	call EventScript_BufferPocketNameTryFanfare
	return

EventScript_PickedUpHiddenItem::
	call_if_eq VAR_0x8006, 1, EventScript_FoundSingleItem
	call_if_ne VAR_0x8006, 1, EventScript_FoundMultipleItems
	waitfanfare
	waitmessage
	msgbox Text_PutItemAway
	special SetHiddenItemFlag
	releaseall
	end

EventScript_FoundSingleItem::
	message Text_FoundOneItem
	return

EventScript_FoundCoins::
	buffernumberstring STR_VAR_1, VAR_0x8006
	message Text_FoundXCoins
	return

EventScript_FoundMultipleItems::
	buffernumberstring STR_VAR_1, VAR_0x8006
	message Text_FoundXItems
	return

Kanto_EventScript_NoRoomForHiddenItem::
	msgbox Text_FoundOneItem
	msgbox Text_TooBadBagFull
	setvar VAR_RESULT, 0
	releaseall
	end

EventScript_TryPickUpHiddenCoins::
	goto_if_unset FLAG_KANTO_GOT_COIN_CASE, EventScript_NoCaseForHiddenCoins
	checkcoins VAR_RESULT
	specialvar VAR_RESULT, CheckAddCoins
	goto_if_eq VAR_RESULT, FALSE, EventScript_HiddenCoinsButCaseIsFull
	addcoins VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_KANTO_COINS
	call Kanto_EventScript_PlayFanfareObtainedItem
	call EventScript_FoundCoins
	waitfanfare
	waitmessage
	msgbox Text_PutCoinsAwayInCoinCase
	special SetHiddenItemFlag
	releaseall
	end

EventScript_HiddenCoinsButCaseIsFull::
	buffernumberstring STR_VAR_1, VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_KANTO_COINS
	msgbox Text_FoundXCoins
	msgbox Text_CoinCaseIsFull
	setvar VAR_RESULT, 0
	releaseall
	end

EventScript_NoCaseForHiddenCoins::
	buffernumberstring STR_VAR_1, VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_KANTO_COINS
	msgbox Text_FoundXCoins
	msgbox Text_NothingToPutThemIn
	setvar VAR_RESULT, 0
	releaseall
	end
