LavenderTown_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Kanto_CableClub_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Kanto_CableClub_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, Kanto_CableClub_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, Kanto_CableClub_OnTransition
	.byte 0

/* The below 3 are unused and leftover from RS */
LavenderTown_PokemonCenter_2F_EventScript_Colosseum::
	call Kanto_CableClub_EventScript_Colosseum
	end

LavenderTown_PokemonCenter_2F_EventScript_TradeCenter::
	call Kanto_CableClub_EventScript_TradeCenter
	end

LavenderTown_PokemonCenter_2F_EventScript_RecordCorner::
	call Kanto_CableClub_EventScript_RecordCorner
	end
