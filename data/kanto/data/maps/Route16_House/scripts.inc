Route16_House_MapScripts::
	.byte 0

Route16_House_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KANTO_GOT_HM02, Route16_House_EventScript_AlreadyGotHM02
	msgbox Route16_House_Text_FoundMySecretRetreat
	setvar VAR_0x8009, MOVE_FLY @ PokemonNative3G : POKé MONTURE au lieu de la CS (data/scripts/fusion_poke_monture.inc)
	call Fusion_EventScript_PokeMontureUpgrade
	msgbox Route16_House_Text_ExplainHM02
	setflag FLAG_KANTO_GOT_HM02
	release
	end

Route16_House_EventScript_NoRoomForHM02::
	msgbox Route16_House_Text_DontHaveAnyRoomForThis
	release
	end

Route16_House_EventScript_AlreadyGotHM02::
	msgbox Route16_House_Text_ExplainHM02
	release
	end

Route16_House_EventScript_Fearow::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_FEAROW, CRY_MODE_NORMAL
	msgbox Route16_House_Text_Fearow
	waitmoncry
	release
	end
