TerraCave_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TerraCave_Entrance_OnTransition
	.byte 0

TerraCave_Entrance_OnTransition:
	setworldmapflag FLAG_HOENN_WORLD_MAP_TERRA_CAVE_ENTRANCE @ PokemonNative3G : lieu visité, pour l'aperçu de RF
	setflag FLAG_ARRIVED_AT_TERRA_CAVE_ENTRANCE
	end

