LilycoveCity_DepartmentStore_3F_MapScripts::
	.byte 0

LilycoveCity_DepartmentStore_3F_EventScript_ClerkLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins:
	.short ITEM_PROTEIN
	.short ITEM_CALCIUM
	.short ITEM_IRON
	.short ITEM_ZINC
	.short ITEM_CARBOS
	.short ITEM_HP_UP
	pokemartlistend

LilycoveCity_DepartmentStore_3F_EventScript_ClerkRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_StatBoosters
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_3F_Pokemart_StatBoosters:
	.short ITEM_X_SPEED
	.short ITEM_X_SPECIAL
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_DIRE_HIT
	.short ITEM_GUARD_SPEC
	.short ITEM_X_ACCURACY
	pokemartlistend

LilycoveCity_DepartmentStore_3F_EventScript_TriathleteM::
	msgbox LilycoveCity_DepartmentStore_3F_Text_ItemsBestForTougheningPokemon, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_EventScript_PokefanM::
	msgbox LilycoveCity_DepartmentStore_3F_Text_WantMoreEndurance, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_EventScript_Woman::
	msgbox LilycoveCity_DepartmentStore_3F_Text_GaveCarbosToSpeedUpMon, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_Text_ItemsBestForTougheningPokemon:
	.string "Pour endurcir les POKéMON en un rien\n"
	.string "de temps, rien de mieux que les objets.\p"
	.string "Les PROTEINES accroissent l'ATTAQUE et\n"
	.string "le CALCIUM augmente l'ATQ. SPE.$"

LilycoveCity_DepartmentStore_3F_Text_WantMoreEndurance:
	.string "Je veux que mon POKéMON ait plus\n"
	.string "d'endurance.\p"
	.string "Je ne sais pas si je dois élever sa\n"
	.string "DEFENSE avec le FER ou sa DEF. SPE.\l"
	.string "avec le ZINC.$"

LilycoveCity_DepartmentStore_3F_Text_GaveCarbosToSpeedUpMon:
	.string "J'ai donné du CARBONE à mon POKéMON\n"
	.string "et sa VITESSE a augmenté.$"

