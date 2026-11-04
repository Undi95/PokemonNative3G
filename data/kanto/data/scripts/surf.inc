@ PokemonNative3G : data/scripts/surf.inc de RF. EventScript_UseSurf est celui d'Émeraude dans les deux régions
@ (doublon retiré) ; reste celui-ci, propre à RF : face au courant rapide des Îles Écume (MB_FAST_WATER),
@ GetInteractedWaterScript (field_control_avatar.c) le lance au lieu de proposer SURF.
EventScript_CurrentTooFast::
	lockall
	msgbox Text_CurrentTooFast
	releaseall
	end
