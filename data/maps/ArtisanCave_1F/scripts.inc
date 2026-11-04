ArtisanCave_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArtisanCave_1F_OnTransition
	.byte 0

@ PokemonNative3G : lieu visité, pour l'aperçu de RF (kanto_map_preview_screen.c)
ArtisanCave_1F_OnTransition:
	setworldmapflag FLAG_HOENN_WORLD_MAP_ARTISAN_CAVE_1F
	end

