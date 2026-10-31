EventScript_AfterWhiteOutHeal::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox Text_FirstShouldRestoreMonsHealth
	copyvar VAR_0x800B, VAR_LAST_TALKED
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	specialvar VAR_RESULT, CountRegionBadges  @ RF : FLAG_DEFEATED_BROCK
	call_if_eq VAR_RESULT, 0, EventScript_AfterWhiteOutHealMsgPreBrock
	call_if_ne VAR_RESULT, 0, EventScript_AfterWhiteOutHealMsg
	applymovement VAR_LAST_TALKED, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	fadedefaultbgm
	releaseall
	end

EventScript_AfterWhiteOutHealMsgPreBrock::
	msgbox Text_MonsHealedShouldBuyPotions
	return

EventScript_AfterWhiteOutHealMsg::
	msgbox Text_MonsHealed
	return

@ PokemonNative3G : le K.O. par le poison de RF (Kanto_EventScript_FieldPoison) est EventScript_FieldPoison
@ (data/scripts/field_poison.inc), avec le texte de RF annonçant la perte d'argent.
