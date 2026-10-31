VermilionCity_House1_MapScripts::
	.byte 0

VermilionCity_House1_EventScript_FishingGuru::
	lock
	faceplayer
	goto_if_set FLAG_KANTO_GOT_OLD_ROD, VermilionCity_House1_EventScript_AlreadyGotOldRod
	msgbox VermilionCity_House1_Text_ImFishingGuruDoYouLikeToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, VermilionCity_House1_EventScript_GiveOldRod
	msgbox VermilionCity_House1_Text_OhThatsSoDisappointing
	release
	end

VermilionCity_House1_EventScript_AlreadyGotOldRod::
	msgbox VermilionCity_House1_Text_HowAreTheFishBiting
	release
	end

VermilionCity_House1_EventScript_GiveOldRod::
	checkitem ITEM_OLD_ROD @ PokemonNative3G : déjà une CANNE (Hoenn) : il l'améliore (data/scripts/fusion_fishing.inc)
	goto_if_eq VAR_RESULT, TRUE, VermilionCity_House1_EventScript_UpgradeOldRod
	msgbox Fusion_Text_OldRodWhere @ PokemonNative3G : pas de CANNE -> il dit où la trouver (Hoenn)
	release
	end

VermilionCity_House1_EventScript_UpgradeOldRod::
	msgbox VermilionCity_House1_Text_ShowMeYourRod
VermilionCity_House1_EventScript_DoUpgradeOldRod::
	setflag FLAG_OLD_ROD_UPGRADED
	bufferitemname STR_VAR_1, ITEM_OLD_ROD
	call Fusion_EventScript_RodUpgraded
	msgbox VermilionCity_House1_Text_ExplainRodChain
	setflag FLAG_KANTO_GOT_OLD_ROD
	msgbox VermilionCity_House1_Text_FishingIsAWayOfLife
	release
	end
