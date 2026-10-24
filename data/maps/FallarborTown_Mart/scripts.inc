FallarborTown_Mart_MapScripts::
	.byte 0

FallarborTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FallarborTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FallarborTown_Mart_Pokemart:
	.short ITEM_GREAT_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_ESCAPE_ROPE
	.short ITEM_SUPER_REPEL
	.short ITEM_X_SPECIAL
	.short ITEM_X_SPEED
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_DIRE_HIT
	.short ITEM_GUARD_SPEC
	.short ITEM_LINK_CABLE
	pokemartlistend

FallarborTown_Mart_EventScript_Woman::
	msgbox FallarborTown_Mart_Text_DecidingSkittyEvolve, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_PokefanM::
	msgbox FallarborTown_Mart_Text_SellNuggetIFound, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox FallarborTown_Mart_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_Mart_Text_DecidingSkittyEvolve:
	.string "J'ai du mal à me décider. Faut-il que\n"
	.string "je fasse évoluer mon SKITTY?\p"
	.string "Il me suffirait d'utiliser cette PIERRE\n"
	.string "LUNE, mais je n'arrive pas à me décider…\p"
	.string "Si je le fais évoluer, il sera bien plus\n"
	.string "puissant.\p"
	.string "Mais il changera aussi d'apparence.$"

FallarborTown_Mart_Text_Skitty:
	.string "SKITTY: Kiiiiity?$"

FallarborTown_Mart_Text_SellNuggetIFound:
	.string "J'ai trouvé une PEPITE, ici…\n"
	.string "Je suppose que je vais devoir la vendre,\l"
	.string "puisqu'elle ne sert à rien d'autre.$"

