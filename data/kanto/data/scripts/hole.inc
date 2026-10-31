@ Rouge Feu : chute par un trou dont la destination est déjà fixée (MB_FALL_WARP, field_control_avatar.c). La chute
@ ordinaire est EventScript_FallDownHole d'Émeraude (data/scripts/cave_hole.inc).
EventScript_DoFallWarp::
	lockall
	delay 20
	applymovement LOCALID_PLAYER, Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	special DoFallWarp
	end
