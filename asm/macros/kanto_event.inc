/* Macros de script de Rouge Feu absentes d'Émeraude (définitions de asm/macros/event.inc de RF),
   utilisées par les scripts de Kanto (data/kanto/). */

	/* Scripts standard de RF ajoutés à la fin de gStdScripts (data/event_scripts.s) */
	STD_PUT_ITEM_AWAY = 11
	STD_RECEIVED_ITEM = 12

	/* Compare une statistique de jeu (GAME_STAT_*) à une valeur ; résultat dans VAR_RESULT. */
	.macro comparestat statId:req, value:req
	.byte SCR_OP_COMPAREHIDDENVAR  /* même opcode que RF (0xcc) */
	.byte \statId
	.4byte \value
	.endm

	/* Mêmes commandes qu'Émeraude sous un autre nom */
	.macro setmonmodernfatefulencounter slot:req
	setmodernfatefulencounter \slot
	.endm

	.macro checkmonmodernfatefulencounter slot:req
	checkmodernfatefulencounter \slot
	.endm

	/* Largeur du message braille (pour le curseur) */
	.macro getbraillestringwidth msg:req
	.byte SCR_OP_GETBRAILLESTRINGWIDTH
	ptrvalue \msg
	.endm

	.macro putitemaway item:req, amount=1
	setorcopyvar VAR_0x8000, \item
	setorcopyvar VAR_0x8001, \amount
	callstd STD_PUT_ITEM_AWAY
	.endm

	.macro msgreceiveditem msg:req, item:req, amount=1, fanfare=MUS_LEVEL_UP
	loadword 0, \msg
	setorcopyvar VAR_0x8000, \item
	setorcopyvar VAR_0x8001, \amount
	setorcopyvar VAR_0x8002, \fanfare
	callstd STD_RECEIVED_ITEM
	.endm

	.macro giveitem_msg msg:req, item:req, amount=1, fanfare=MUS_LEVEL_UP
	additem \item, \amount
	msgreceiveditem \msg, \item, \amount, \fanfare
	.endm

	.macro famechecker person:req, index:req, function=SetFlavorTextFlagFromSpecialVars
	setvar VAR_0x8004, \person
	setvar VAR_0x8005, \index
	special \function
	.endm

	.macro set_gym_trainers gym:req
	setvar VAR_0x8008, \gym
	call EventScript_SetGymTrainers
	.endm

	.macro goto_if_questlog dest:req
	special GetQuestLogState
	compare VAR_RESULT, 2
	goto_if_eq \dest
	.endm

	.macro braillemessage_wait text:req
	closemessage @ PokemonNative3G : comme dans RF, le braille remplace le message en cours
	setvar VAR_0x8006, 0
	braillemessage \text
	getbraillestringwidth \text
	call EventScript_BrailleCursorWaitButton
	closebraillemessage @ PokemonNative3G : le braille d'Émeraude a sa propre fenêtre
	.endm

	/* Combat contre le rival avec texte de victoire s'il gagne ; flags : RIVAL_BATTLE_* */
	.macro trainerbattle_earlyrival trainer:req, flags:req, defeat_text:req, victory_text:req
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, \trainer, \flags, \defeat_text, \victory_text
	.endm

	/* MOVEMENT_ACTION_WALK_SLOWER_* de RF = MOVEMENT_ACTION_WALK_SLOW_* d'Émeraude : même vitesse (1 pixel toutes
	   les 2 images, UpdateWalkSlowerAnim de RF = UpdateWalkSlowAnim d'Émeraude). Le WALK_SLOW de RF, plus rapide,
	   est MOVEMENT_ACTION_KANTO_WALK_SLOW_* (escaliers de roche). */
	.macro walk_slower_down
	walk_slow_down
	.endm
	.macro walk_slower_up
	walk_slow_up
	.endm
	.macro walk_slower_left
	walk_slow_left
	.endm
	.macro walk_slower_right
	walk_slow_right
	.endm
