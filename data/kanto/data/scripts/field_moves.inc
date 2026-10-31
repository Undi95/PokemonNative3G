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
