AbandonedShip_Deck_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbandonedShip_Deck_OnTransition
	.byte 0

AbandonedShip_Deck_OnTransition:
	setworldmapflag FLAG_LANDMARK_ABANDONED_SHIP @ PokemonNative3G : aperçu de RF (durée plus longue à la 1re visite)
	setflag FLAG_LANDMARK_ABANDONED_SHIP
	end

