FuchsiaCity_House2_MapScripts::
	.byte 0

FuchsiaCity_House2_EventScript_FishingGurusBrother::
	lock
	faceplayer
	goto_if_set FLAG_KANTO_GOT_GOOD_ROD, FuchsiaCity_House2_EventScript_AlreadyGotGoodRod
	msgbox FuchsiaCity_House2_Text_DoYouLikeToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_House2_EventScript_GiveGoodRod
	msgbox FuchsiaCity_House2_Text_OhThatsDisappointing
	release
	end

FuchsiaCity_House2_EventScript_AlreadyGotGoodRod::
	msgbox FuchsiaCity_House2_Text_HowAreTheFishBiting
	release
	end

FuchsiaCity_House2_EventScript_GiveGoodRod::
	checkitem ITEM_GOOD_ROD @ PokemonNative3G : déjà une SUPER CANNE (Hoenn) : il l'améliore (data/scripts/fusion_fishing.inc)
	goto_if_eq VAR_RESULT, TRUE, FuchsiaCity_House2_EventScript_UpgradeGoodRod
	msgbox Fusion_Text_GoodRodWhere @ PokemonNative3G : pas de SUPER CANNE -> il dit où la trouver (Hoenn)
	release
	end
	msgbox FuchsiaCity_House2_Text_LikeYourStyleTakeThis
	checkitemspace ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, FALSE, FuchsiaCity_House2_EventScript_NoRoomForGoodRod
	giveitem_msg FuchsiaCity_House2_Text_ReceivedGoodRod, ITEM_GOOD_ROD
	msgbox FuchsiaCity_House2_Text_GoodRodCanCatchBetterMons
	goto FuchsiaCity_House2_EventScript_DoUpgradeGoodRod
FuchsiaCity_House2_EventScript_UpgradeGoodRod::
	msgbox FuchsiaCity_House2_Text_ShowMeYourRod
FuchsiaCity_House2_EventScript_DoUpgradeGoodRod::
	setflag FLAG_GOOD_ROD_UPGRADED
	bufferitemname STR_VAR_1, ITEM_GOOD_ROD
	call Fusion_EventScript_RodUpgraded
	msgbox FuchsiaCity_House2_Text_ExplainRodChain
	setflag FLAG_KANTO_GOT_GOOD_ROD
	release
	end

FuchsiaCity_House2_EventScript_NoRoomForGoodRod::
	msgbox FuchsiaCity_House2_Text_YouHaveNoRoomForGift
	release
	end
