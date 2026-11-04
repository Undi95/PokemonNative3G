CaveOfOrigin_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CaveOfOrigin_Entrance_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, CaveOfOrigin_Entrance_OnTransition
	.byte 0

@ PokemonNative3G : lieu visité, pour l'aperçu de RF (kanto_map_preview_screen.c)
CaveOfOrigin_Entrance_OnTransition:
	setworldmapflag FLAG_HOENN_WORLD_MAP_CAVE_OF_ORIGIN_ENTRANCE
	end

CaveOfOrigin_Entrance_OnResume:
	setescapewarp MAP_SOOTOPOLIS_CITY, 31, 17
	end

