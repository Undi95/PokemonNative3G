NavelRock_Harbor_MapScripts::
	.byte 0

NavelRock_Harbor_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_ISLAND_TRIP_FROM_KANTO, NavelRock_Harbor_EventScript_SeagallopSailor @ PokemonNative3G
	msgbox NavelRock_Harbor_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NavelRock_Harbor_EventScript_AsYouLike
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_NAVEL_ROCK_SAILOR, MAP_NAVEL_ROCK_HARBOR
	setvar VAR_0x8004, LOCALID_NAVEL_ROCK_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

NavelRock_Harbor_EventScript_AsYouLike::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

@ PokemonNative3G : venu par le ferry de Carmin sur Mer (RF) : retour à Carmin, comme dans RF (NavelRock_Harbor de RF)
NavelRock_Harbor_EventScript_SeagallopSailor::
	message Text_WhereDoYouWantToSail
	waitmessage
	setvar VAR_0x8004, SEAGALLOP_NAVEL_ROCK
	multichoice 20, 8, KANTO_MULTICHOICE_SEAGALLOP_VERMILION, FALSE
	switch VAR_RESULT
	case 0, NavelRock_Harbor_EventScript_SailBackToVermilion
	case 1, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

NavelRock_Harbor_EventScript_SailBackToVermilion::
	clearflag FLAG_ISLAND_TRIP_FROM_KANTO
	goto EventScript_SailToVermilionCity
	end
