KantoSafariZone_SecretHouse_MapScripts::
	.byte 0

KantoSafariZone_SecretHouse_EventScript_Attendant::
	lock
	faceplayer
	goto_if_set FLAG_KANTO_GOT_HM03, KantoSafariZone_SecretHouse_EventScript_ExplainSurf
	msgbox KantoSafariZone_SecretHouse_Text_CongratsYouveWon
	setvar VAR_0x8009, MOVE_SURF @ PokemonNative3G : POKé MONTURE au lieu de la CS (data/scripts/fusion_poke_monture.inc)
	call Fusion_EventScript_PokeMontureUpgrade
	msgbox KantoSafariZone_SecretHouse_Text_ExplainSurf
	setflag FLAG_KANTO_GOT_HM03
	release
	end

KantoSafariZone_SecretHouse_EventScript_NoRoomForHM03::
	msgbox KantoSafariZone_SecretHouse_Text_DontHaveRoomForPrize
	release
	end

KantoSafariZone_SecretHouse_EventScript_ExplainSurf::
	msgbox KantoSafariZone_SecretHouse_Text_ExplainSurf
	release
	end
