@ PokemonNative3G : météorite de Jirachi (Chutes Météore B1F, salle du fond). Après les deux Ligues, la TV de
@ Hoenn annonce la comète du millénaire (une fois) ; la météorite est là tant que JIRACHI n'est ni capturé ni
@ vaincu (pas de limite de temps). Il dort dedans : la POKé FLÛTE le réveille, puis combat légendaire.
@ La météorite est cachée avant les Ligues (FLAG_TEMP_1, MeteorFalls_B1F_2R_OnTransition).

@ appelé par EventScript_TV : flash spécial, une fois ; sinon retour à la TV normale
Fusion_EventScript_TryCometNews::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Fusion_EventScript_Return
	goto_if_unset FLAG_KANTO_SYS_GAME_CLEAR, Fusion_EventScript_Return
	goto_if_set FLAG_JIRACHI_NEWS_SEEN, Fusion_EventScript_Return
	goto_if_set FLAG_CAUGHT_JIRACHI, Fusion_EventScript_Return
	goto_if_set FLAG_DEFEATED_JIRACHI, Fusion_EventScript_Return
	msgbox Fusion_Text_CometNewsFlash, MSGBOX_DEFAULT
	setflag FLAG_JIRACHI_NEWS_SEEN
	special TurnOffTVScreen
	releaseall
	end

Fusion_EventScript_Return::
	return

MeteorFalls_B1F_2R_OnTransition::
	setflag FLAG_TEMP_1
	goto_if_unset FLAG_SYS_GAME_CLEAR, Fusion_EventScript_End
	goto_if_unset FLAG_KANTO_SYS_GAME_CLEAR, Fusion_EventScript_End
	clearflag FLAG_TEMP_1
	end

Fusion_EventScript_End::
	end

Fusion_EventScript_JirachiMeteorite::
	lock
	goto_if_set FLAG_CAUGHT_JIRACHI, Fusion_EventScript_MeteoriteDull
	goto_if_set FLAG_DEFEATED_JIRACHI, Fusion_EventScript_MeteoriteDull
	msgbox Fusion_Text_MeteoriteGlows, MSGBOX_DEFAULT
	checkitem ITEM_POKE_FLUTE
	goto_if_eq VAR_RESULT, FALSE, Fusion_EventScript_MeteoriteNoFlute
	msgbox Fusion_Text_UsePokeFluteOnMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_MeteoriteLeave
	message Text_PlayedPokeFlute
	waitmessage
	playfanfare MUS_RG_POKE_FLUTE
	waitfanfare
	closemessage
	@ pas de waitse : la mélodie de la POKé FLÛTE occupe le lecteur d'effets 2 pendant 51 s (piste du MIDI de RF,
	@ qui finit bien après ses notes) ; RF n'attend jamais ce lecteur après elle (Ronflex). La clochette est finie
	@ avant les deux fondus au blanc.
	playse SE_M_HEAL_BELL
	fadescreen FADE_TO_WHITE
	fadescreen FADE_FROM_WHITE
	message Fusion_Text_Jirachi
	playmoncry SPECIES_JIRACHI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	seteventmon SPECIES_JIRACHI, 30
	special BattleSetup_StartLegendaryBattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Fusion_EventScript_JirachiDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Fusion_EventScript_JirachiBackToSleep
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Fusion_EventScript_JirachiBackToSleep
	goto_if_eq VAR_RESULT, B_OUTCOME_MON_TELEPORTED, Fusion_EventScript_JirachiBackToSleep
	setflag FLAG_CAUGHT_JIRACHI
	release
	end

Fusion_EventScript_JirachiDefeated::
	setflag FLAG_DEFEATED_JIRACHI
	msgbox Fusion_Text_JirachiFlewAway, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_JirachiBackToSleep::
	msgbox Fusion_Text_JirachiBackToSleep, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_MeteoriteNoFlute::
	msgbox Fusion_Text_MeteoriteNeedsMelody, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_MeteoriteLeave::
	release
	end

Fusion_EventScript_MeteoriteDull::
	msgbox Fusion_Text_MeteoriteDull, MSGBOX_DEFAULT
	release
	end

Fusion_Text_CometNewsFlash:
	.string "FLASH SPÉCIAL!\p"
	.string "La comète du millénaire, qui ne passe\n"
	.string "qu'une fois tous les mille ans, est\l"
	.string "visible ce soir dans le ciel de HOENN!\p"
	.string "Un fragment se serait détaché et\n"
	.string "serait tombé au fond des CHUTES\l"
	.string "MÉTÉORE, près de VERMILAVA…\p"
	.string "Selon la légende, un POKéMON qui\n"
	.string "exauce les vœux dormirait dans ces\l"
	.string "pierres venues du ciel…$"

Fusion_Text_MeteoriteGlows:
	.string "Une météorite tombée du ciel…\n"
	.string "Elle brille d'une douce lumière.\p"
	.string "Quelque chose semble dormir\n"
	.string "à l'intérieur…$"

Fusion_Text_MeteoriteNeedsMelody:
	.string "On dirait un profond sommeil…\p"
	.string "Une mélodie apaisante, comme celle\n"
	.string "de la POKé FLÛTE de KANTO, pourrait\l"
	.string "peut-être le réveiller…$"

Fusion_Text_UsePokeFluteOnMeteorite:
	.string "Jouer de la POKé FLÛTE?$"

Fusion_Text_Jirachi:
	.string "Jiraaa!$"

Fusion_Text_JirachiFlewAway:
	.string "JIRACHI s'est envolé vers le ciel…\n"
	.string "La météorite ne brille plus.$"

Fusion_Text_JirachiBackToSleep:
	.string "JIRACHI s'est rendormi dans\n"
	.string "la météorite…$"

Fusion_Text_MeteoriteDull:
	.string "Une météorite tombée du ciel.\n"
	.string "Elle ne brille plus.$"
