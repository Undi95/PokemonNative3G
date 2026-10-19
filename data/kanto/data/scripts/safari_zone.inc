Kanto_SafariZone_EventScript_OutOfBallsMidBattle::
	setvar VAR_KANTO_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 3
	special ExitSafariMode
	setwarp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
	end

Kanto_SafariZone_EventScript_Exit::
	setvar VAR_KANTO_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 1
	special ExitSafariMode
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
	waitstate
	end

Kanto_SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox Kanto_SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Kanto_SafariZone_EventScript_Retire
	releaseall
	end

Kanto_SafariZone_EventScript_Retire::
	goto Kanto_SafariZone_EventScript_Exit

Kanto_SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	msgbox Kanto_SafariZone_Text_TimesUp
	goto Kanto_SafariZone_EventScript_Exit
	end

Kanto_SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	msgbox Kanto_SafariZone_Text_OutOfBalls
	goto Kanto_SafariZone_EventScript_Exit
	end
