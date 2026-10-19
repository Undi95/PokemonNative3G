BattleFrontier_Mart_MapScripts::
	.byte 0

BattleFrontier_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart BattleFrontier_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart:
	.short ITEM_ULTRA_BALL
	.short ITEM_HYPER_POTION
	.short ITEM_MAX_POTION
	.short ITEM_FULL_RESTORE
	.short ITEM_FULL_HEAL
	.short ITEM_REVIVE
	.short ITEM_MAX_REPEL
	.short ITEM_PROTEIN
	.short ITEM_CALCIUM
	.short ITEM_IRON
	.short ITEM_ZINC
	.short ITEM_CARBOS
	.short ITEM_HP_UP
	pokemartlistend

BattleFrontier_Mart_EventScript_OldMan::
	msgbox BattleFrontier_Mart_Text_ChaperonGrandson, MSGBOX_NPC
	end

BattleFrontier_Mart_EventScript_OldWoman::
	lock
	applymovement LOCALID_FRONTIER_MART_OLD_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_ProteinMakeNiceGift, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Mart_EventScript_Boy::
	msgbox BattleFrontier_Mart_Text_FacilitiesDontAllowItems, MSGBOX_NPC
	end

BattleFrontier_Mart_Text_ChaperonGrandson:
	.string "Nous sommes venus accompagner\n"
	.string "notre petit-fils.\p"
	.string "On en profite pour acheter quelques\n"
	.string "souvenirs.$"

BattleFrontier_Mart_Text_ProteinMakeNiceGift:
	.string "Que penses-tu de ça, chéri?\n"
	.string "Ça ferait un joli cadeau, non?\p"
	.string "PRO… TE… INE?\n"
	.string "Ça m'a l'air d'être délicieux!$"

BattleFrontier_Mart_Text_FacilitiesDontAllowItems:
	.string "Dans la ZONE DE COMBAT, on n'a pas\n"
	.string "toujours le droit d'utiliser des objets\l"
	.string "en combat.\p"
	.string "Ça rend les choses encore plus\n"
	.string "difficiles!$"

