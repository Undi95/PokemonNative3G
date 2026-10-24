LilycoveCity_DepartmentStore_2F_MapScripts::
	.byte 0

LilycoveCity_DepartmentStore_2F_EventScript_Cook::
	msgbox LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_PokefanF::
	msgbox LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_Sailor::
	msgbox LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_ClerkLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart1
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart1:
	.short ITEM_POKE_BALL
	.short ITEM_GREAT_BALL
	.short ITEM_ULTRA_BALL
	.short ITEM_ESCAPE_ROPE
	.short ITEM_FULL_HEAL
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_BURN_HEAL
	.short ITEM_ICE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_FLUFFY_TAIL
	.short ITEM_LINK_CABLE
	pokemartlistend

LilycoveCity_DepartmentStore_2F_EventScript_ClerkRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart2:
	.short ITEM_POTION
	.short ITEM_SUPER_POTION
	.short ITEM_HYPER_POTION
	.short ITEM_MAX_POTION
	.short ITEM_REVIVE
	.short ITEM_REPEL
	.short ITEM_SUPER_REPEL
	.short ITEM_MAX_REPEL
	.short ITEM_WAVE_MAIL
	.short ITEM_MECH_MAIL
	.short ITEM_LINK_CABLE
	pokemartlistend

LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly:
	.string "Apprendre à utiliser correctement les\n"
	.string "objets, c'est vraiment la base de tout.$"

LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband:
	.string "Mon mari m'attend à la maison.\n"
	.string "Qu'est-ce qui pourrait lui faire plaisir?$"

LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems:
	.string "Je pars pour un long voyage.\n"
	.string "Il faut que je fasse le plein d'objets.$"

