@ PokemonNative3G : autel de la Forêt Baies (Île 3). Après les deux Ligues, CELEBI apparaît quand on examine
@ l'autel. Vaincu : il ne revient plus (comme les légendaires d'Émeraude) ; fuite : il revient à la visite suivante.
@ L'objet CELEBI est caché à l'arrivée sur la carte (FLAG_TEMP_11, ThreeIsland_BerryForest_OnTransition).

Fusion_EventScript_CelebiShrine::
	lock
	goto_if_set FLAG_CAUGHT_CELEBI, Fusion_EventScript_CelebiShrineQuiet
	goto_if_set FLAG_DEFEATED_CELEBI, Fusion_EventScript_CelebiShrineQuiet
	goto_if_unset FLAG_SYS_GAME_CLEAR, Fusion_EventScript_CelebiShrineQuiet
	goto_if_unset FLAG_KANTO_SYS_GAME_CLEAR, Fusion_EventScript_CelebiShrineQuiet
	msgbox Fusion_Text_CelebiShrinePresence, MSGBOX_DEFAULT
	closemessage
	playse SE_M_HEAL_BELL
	fadescreen FADE_TO_WHITE
	addobject LOCALID_KANTO_BERRY_FOREST_CELEBI
	fadescreen FADE_FROM_WHITE
	waitse
	applymovement LOCALID_KANTO_BERRY_FOREST_CELEBI, Fusion_Movement_CelebiAppear
	waitmovement 0
	message Fusion_Text_Celebi
	waitse
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_KANTO_BERRY_FOREST_CELEBI
	seteventmon SPECIES_CELEBI, 30
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Fusion_EventScript_CelebiDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Fusion_EventScript_PlayerOrCelebiRan
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Fusion_EventScript_PlayerOrCelebiRan
	goto_if_eq VAR_RESULT, B_OUTCOME_MON_TELEPORTED, Fusion_EventScript_PlayerOrCelebiRan
	setflag FLAG_CAUGHT_CELEBI
	release
	end

Fusion_EventScript_CelebiDefeated::
	setflag FLAG_DEFEATED_CELEBI
	setvar VAR_0x8004, SPECIES_CELEBI
	goto Common_EventScript_LegendaryFlewAway
	end

Fusion_EventScript_PlayerOrCelebiRan::
	setvar VAR_0x8004, SPECIES_CELEBI
	goto Common_EventScript_LegendaryFlewAway
	end

Fusion_EventScript_CelebiShrineQuiet::
	msgbox Fusion_Text_CelebiShrine, MSGBOX_DEFAULT
	release
	end

Fusion_Movement_CelebiAppear:
	face_down
	jump_in_place_down
	step_end

Fusion_Text_CelebiShrine:
	.string "C'est un petit autel en bois.\n"
	.string "Il a l'air très ancien…$"

Fusion_Text_CelebiShrinePresence:
	.string "C'est un petit autel en bois.\n"
	.string "Il a l'air très ancien…\p"
	.string "… … … … … …\p"
	.string "Une présence mystérieuse se fait\n"
	.string "sentir tout autour de l'autel!$"

Fusion_Text_Celebi:
	.string "Bibiii!$"
