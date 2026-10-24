MauvilleCity_Mart_MapScripts::
	.byte 0

MauvilleCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart:
	.short ITEM_POKE_BALL
	.short ITEM_GREAT_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_X_SPEED
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_GUARD_SPEC
	.short ITEM_DIRE_HIT
	.short ITEM_X_ACCURACY
	.short ITEM_LINK_CABLE
	pokemartlistend

MauvilleCity_Mart_EventScript_ExpertM::
	msgbox MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_Man::
	msgbox MauvilleCity_Mart_Text_DecisionsDetermineBattle, MSGBOX_NPC
	end

MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats:
	.string "Certains objets augmentent de façon\n"
	.string "temporaire les stats d'un POKéMON.\p"
	.string "Ceux qu'on utilise au combat sont\n"
	.string "l'ATTAQUE + et la DEFENSE +.\p"
	.string "Je crois qu'il y en a encore \n"
	.string "d'autres comme ça.$"

MauvilleCity_Mart_Text_DecisionsDetermineBattle:
	.string "Utiliser une certaine capacité ou\n"
	.string "utiliser un objet à la place…\p"
	.string "A mon avis, les décisions des DRESSEURS\n"
	.string "influent sur le déroulement du combat.$"

