
EventScript_RestorePrevTextColor::
	copyvar VAR_TEXT_COLOR, VAR_PREV_TEXT_COLOR
	return

EventScript_TryPickUpHiddenItem::
	additem VAR_0x8005, VAR_0x8006
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemname STR_VAR_2, VAR_0x8005
	checkitemtype VAR_0x8005
	call EventScript_BufferPocketNameAndTryFanfare @ PokemonNative3G : noms de poche communs (Std_ObtainItem)
	return

EventScript_FoundCoins::
	buffernumberstring STR_VAR_1, VAR_0x8006
	message Text_FoundXCoins
	return

EventScript_TryPickUpHiddenCoins::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, EventScript_NoCaseForHiddenCoins
	checkcoins VAR_RESULT
	specialvar VAR_RESULT, CheckAddCoins
	goto_if_eq VAR_RESULT, FALSE, EventScript_HiddenCoinsButCaseIsFull
	addcoins VAR_0x8006
	bufferstdstring STR_VAR_2, STDSTRING_KANTO_COINS
	call EventScript_PlayFanfareObtainedItem
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
