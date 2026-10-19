Kanto_EventScript_CutTree::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_KANTO_BADGE02_GET, EventScript_CantCutTree
	checkpartymove MOVE_CUT
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantCutTree
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_CUT
	msgbox Text_CutTreeDown, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_DontCutTree
	msgbox Text_MonUsedMove
	closemessage
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto Kanto_EventScript_CutTreeDown
	end

EventScript_FldEffCut::
	lockall
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto Kanto_EventScript_CutTreeDown
	end

Kanto_EventScript_CutTreeDown::
	applymovement VAR_LAST_TALKED, Kanto_Movement_CutTreeDown
	waitmovement 0
	removeobject VAR_LAST_TALKED
	releaseall
	end

Kanto_Movement_CutTreeDown::
	cut_tree
	step_end

EventScript_CantCutTree::
	msgbox Text_TreeCanBeCutDown, MSGBOX_SIGN
	releaseall
	end

EventScript_DontCutTree::
	closemessage
	releaseall
	end

Text_CutTreeDown::
	.string "Cet arbre semble pouvoir être\n"
	.string "COUPE.\p"
	.string "Voulez-vous utiliser COUPE?$"

Text_MonUsedMove::
	.string "{STR_VAR_1} utilise {STR_VAR_2}.$"

Text_TreeCanBeCutDown::
	.string "Cet arbre semble pouvoir être\n"
	.string "COUPE.$"

Kanto_EventScript_RockSmash::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_KANTO_BADGE06_GET, Kanto_EventScript_CantSmashRock
	checkpartymove MOVE_ROCK_SMASH
	goto_if_eq VAR_RESULT, PARTY_SIZE, Kanto_EventScript_CantSmashRock
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH
	msgbox Text_UseRockSmash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_DontSmashRock
	msgbox Text_MonUsedMove
	closemessage
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto Kanto_EventScript_UseRockSmash
	end

EventScript_FldEffRockSmash::
	lockall
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto Kanto_EventScript_UseRockSmash
	end

Kanto_EventScript_UseRockSmash::
	applymovement VAR_LAST_TALKED, Movement_BreakRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	special RockSmashWildEncounter
	goto_if_eq VAR_RESULT, FALSE, EventScript_RockSmashNoEncounter
	waitstate
	releaseall
	end

EventScript_RockSmashNoEncounter::
	releaseall
	end

Movement_BreakRock::
	rock_smash_break
	step_end

Kanto_EventScript_CantSmashRock::
	msgbox Text_MonMaySmashRock, MSGBOX_SIGN
	end

EventScript_DontSmashRock::
	closemessage
	releaseall
	end

Text_UseRockSmash::
	.string "Cette pierre peut être brisée.\n"
	.string "Voulez-vous utiliser ECLATE-ROC?$"

Text_MonMaySmashRock::
	.string "C'est une pierre solide, mais un\n"
	.string "POKéMON pourrait la briser.$"

Kanto_EventScript_StrengthBoulder::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_KANTO_BADGE04_GET, EventScript_CantMoveBoulder
	goto_if_set FLAG_KANTO_SYS_USE_STRENGTH, EventScript_AlreadyUsedStrength
	checkpartymove MOVE_STRENGTH
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantMoveBoulder
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_UseStrength, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_DontUseStrength
	closemessage
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto Kanto_EventScript_UseStrength
	end

EventScript_FldEffStrength::
	lockall
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto Kanto_EventScript_UseStrength
	end

Kanto_EventScript_UseStrength::
	setflag FLAG_KANTO_SYS_USE_STRENGTH
	msgbox Text_MonUsedStrengthCanMoveBoulders, MSGBOX_SIGN
	end

EventScript_CantMoveBoulder::
	msgbox Text_MonMayPushBoulder, MSGBOX_SIGN
	end

EventScript_AlreadyUsedStrength::
	msgbox Text_StrengthMadeMovingBouldersPossible, MSGBOX_SIGN
	end

EventScript_DontUseStrength::
	closemessage
	releaseall
	end

Text_UseStrength::
	.string "C'est un gros rocher, mais un\n"
	.string "POKéMON peut être apte à le\l"
	.string "déplacer.\p"
	.string "Voulez-vous utiliser FORCE?$"

Text_MonUsedStrengthCanMoveBoulders::
	.string "{STR_VAR_1} utilise FORCE.\p"
	.string "La capacité FORCE de {STR_VAR_1}\n"
	.string "permet de déplacer le rocher.$"

Text_MonMayPushBoulder::
	.string "C'est un gros rocher, mais un\n"
	.string "POKéMON peut être apte à le\l"
	.string "déplacer.$"

Text_StrengthMadeMovingBouldersPossible::
	.string "FORCE permet de déplacer le\n"
	.string "rocher.$"

EventScript_Waterfall::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	checkpartymove MOVE_WATERFALL
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_WaterCrashingDown
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_UseWaterfall, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Kanto_EventScript_EndWaterfall
	msgbox Kanto_Text_MonUsedWaterfall
	dofieldeffect FLDEFF_USE_WATERFALL
	goto Kanto_EventScript_EndWaterfall

EventScript_CantUseWaterfall::
	lockall
EventScript_WaterCrashingDown:
	msgbox Text_WallOfWaterCrashingDown
Kanto_EventScript_EndWaterfall:
	releaseall
	end

Text_WallOfWaterCrashingDown::
	.string "Un mur d'eau s'abat dans un vacarme\n"
	.string "assourdissant.$"

Text_UseWaterfall::
	.string "C'est une grande chute d'eau.\n"
	.string "Voulez-vous utiliser CASCADE?$"

Kanto_Text_MonUsedWaterfall::
	.string "{STR_VAR_1} utilise CASCADE.$"

/* Unused leftover from R/S */
EventScript_DeepWater::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_MayGoUnderwater
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_SeaIsDeepUseDive, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Kanto_EventScript_EndDive
	msgbox Kanto_Text_MonUsedDive
	dofieldeffect FLDEFF_USE_DIVE
	goto Kanto_EventScript_EndDive

Kanto_EventScript_CantDive::
	lockall
EventScript_MayGoUnderwater:
	msgbox Text_MonMayGoUnderwater
Kanto_EventScript_EndDive:
	releaseall
	end

EventScript_TrySurface::
	lockall
	checkpartymove MOVE_DIVE
	goto_if_eq VAR_RESULT, PARTY_SIZE, Kanto_EventScript_CantSurface
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_LightFilteringUseDive, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Kanto_EventScript_EndSurface
	msgbox Kanto_Text_MonUsedDive
	dofieldeffect FLDEFF_USE_DIVE
	goto Kanto_EventScript_EndSurface

Kanto_EventScript_CantSurface::
	lockall
	msgbox Text_MonMaySurface
	goto Kanto_EventScript_EndSurface

EventScript_ObstacleCantSurface::
	lockall
	msgbox Text_DiveCantBeUsedHere
Kanto_EventScript_EndSurface:
	releaseall
	end

Text_MonMayGoUnderwater::
	.string "La mer est profonde. Un POKéMON\n"
	.string "doit pouvoir aller sous l'eau ici.$"

Text_SeaIsDeepUseDive::
	.string "La mer est profonde ici.\n"
	.string "Voulez-vous utiliser PLONGEE?$"

Kanto_Text_MonUsedDive::
	.string "{STR_VAR_1} utilise PLONGEE.$"

Text_MonMaySurface::
	.string "Une lumière vient d'en haut.\n"
	.string "Un POKéMON doit pouvoir remonter\l"
	.string "à la surface.$"

Text_LightFilteringUseDive::
	.string "Une lumière vient d'en haut.\n"
	.string "Voulez-vous utiliser PLONGEE?$"

Text_DiveCantBeUsedHere::
	.string "Quelque chose empêche le retour\n"
	.string "à la surface.\p"
	.string "Il est impossible d'utiliser\n"
	.string "PLONGEE ici.$"

Kanto_EventScript_FailSweetScent::
	msgbox Text_LooksLikeNothingHere, MSGBOX_SIGN
	end

Text_LooksLikeNothingHere::
	.string "Apparemment, il n'y a rien ici…$"
