BirthIsland_Harbor_MapScripts::
	.byte 0

BirthIsland_Harbor_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_ISLAND_TRIP_FROM_KANTO, BirthIsland_Harbor_EventScript_SeagallopSailor @ PokemonNative3G
	msgbox BirthIsland_Harbor_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BirthIsland_Harbor_EventScript_AsYouLike
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_BIRTH_ISLAND_SAILOR, MAP_BIRTH_ISLAND_HARBOR
	setvar VAR_0x8004, LOCALID_BIRTH_ISLAND_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BirthIsland_Harbor_EventScript_AsYouLike::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

@ PokemonNative3G : venu par le ferry de Carmin sur Mer (RF) : retour à Carmin, comme dans RF (NavelRock_Harbor de RF)
BirthIsland_Harbor_EventScript_SeagallopSailor::
	message Text_WhereDoYouWantToSail
	waitmessage
	setvar VAR_0x8004, SEAGALLOP_BIRTH_ISLAND
	multichoice 20, 8, KANTO_MULTICHOICE_SEAGALLOP_VERMILION, FALSE
	switch VAR_RESULT
	case 0, BirthIsland_Harbor_EventScript_SailBackToVermilion
	case 1, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

BirthIsland_Harbor_EventScript_SailBackToVermilion::
	clearflag FLAG_ISLAND_TRIP_FROM_KANTO
	goto EventScript_SailToVermilionCity
	end
