@ PokemonNative3G : POKé MONTURE, à la place des CS données à Kanto (les CS restent à Hoenn). Appelé là où RF donnait
@ la CS, avec VAR_0x8009 = la capacité ; l'appelant pose ensuite le flag de RF (FLAG_KANTO_GOT_HM0x), qui débloque
@ la capacité (src/fusion_events.c). Premier don : l'objet lui-même.

Fusion_EventScript_PokeMontureUpgrade::
	checkitem ITEM_POKE_MONTURE
	goto_if_eq VAR_RESULT, TRUE, Fusion_EventScript_PokeMontureNewMove
	giveitem_msg Fusion_Text_ReceivedPokeMonture, ITEM_POKE_MONTURE, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox Fusion_Text_ExplainPokeMonture, MSGBOX_DEFAULT
Fusion_EventScript_PokeMontureNewMove::
	buffermovename STR_VAR_2, VAR_0x8009
	playfanfare MUS_OBTAIN_TMHM
	msgbox Fusion_Text_PokeMontureNewMove, MSGBOX_DEFAULT
	waitfanfare
	return

@ CS07 de RF (objet au sol, Grotte de Glace, Île 4) : ramasser la boule pose son flag, qui débloque CASCADE
FourIsland_IcefallCave_1F_EventScript_ItemHM07::
	lock
	msgbox Fusion_Text_FoundWaterfallChip, MSGBOX_DEFAULT
	removeobject VAR_LAST_TALKED
	setvar VAR_0x8009, MOVE_WATERFALL
	call Fusion_EventScript_PokeMontureUpgrade
	release
	end

Fusion_Text_ReceivedPokeMonture:
	.string "{PLAYER} reçoit\n"
	.string "la POKé MONTURE!$"

Fusion_Text_ExplainPokeMonture:
	.string "Avec la POKé MONTURE, un POKéMON\n"
	.string "des environs vient t'aider sur le\l"
	.string "terrain.\p"
	.string "Tes POKéMON n'ont plus besoin\n"
	.string "d'apprendre de CS!$"

Fusion_Text_PokeMontureNewMove:
	.string "La POKé MONTURE peut maintenant\n"
	.string "appeler un POKéMON pour {STR_VAR_2}!$"

Fusion_Text_FoundWaterfallChip:
	.string "Il y a une puce électronique…\p"
	.string "Elle semble faite pour une\n"
	.string "POKé MONTURE!$"
