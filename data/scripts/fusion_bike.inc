@ PokemonNative3G : vendeur du magasin de vélos d'Azuria (tools/kanto_bike.py). Le joueur a un vélo de Hoenn :
@ il lui donne l'autre modèle, pour passer de l'un à l'autre depuis le SAC.
Fusion_EventScript_BikeShopGiveOtherBike::
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, Fusion_EventScript_BikeShopGiveAcroBike
	msgbox Fusion_Text_BikeShopHoennBike
	giveitem ITEM_MACH_BIKE
	goto Fusion_EventScript_BikeShopGaveBike

Fusion_EventScript_BikeShopGiveAcroBike::
	msgbox Fusion_Text_BikeShopHoennBike
	giveitem ITEM_ACRO_BIKE
Fusion_EventScript_BikeShopGaveBike::
	setflag FLAG_KANTO_GOT_BICYCLE
	msgbox Fusion_Text_BikeShopExplainSwitch
	release
	end

Fusion_Text_BikeShopGoToMauville:
	.string "Bonjour! Ici, on répare et on\n"
	.string "règle les vélos!\p"
	.string "Tu n'as pas de vélo? Le magasin\n"
	.string "de vélos de LAVANDIA, à HOENN,\l"
	.string "en donne aux bons dresseurs!\p"
	.string "Reviens me voir avec, je te le\n"
	.string "réglerai!$"

Fusion_Text_BikeShopHoennBike:
	.string "Oh! Un vélo de HOENN!\n"
	.string "Fais voir… Superbe machine!\p"
	.string "Tiens, j'ai justement l'autre\n"
	.string "modèle en réserve. Prends-le!$"

Fusion_Text_BikeShopExplainSwitch:
	.string "Avec les deux, tu peux changer\n"
	.string "de vélo quand tu veux depuis\l"
	.string "ton SAC, même en roulant!\p"
	.string "Sur la PISTE CYCLABLE, laisse-toi\n"
	.string "descendre la pente!\p"
	.string "Retiens B pour freiner!$"
