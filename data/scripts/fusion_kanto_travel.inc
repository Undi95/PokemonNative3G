@ PokemonNative3G : passage Hoenn <-> Kanto et maison de Bourg Palette (tools/kanto_travel.py)

@ --- Poivressel / Nénucrique (Ligue de Hoenn finie) : appelé avant la demande de ticket ; ne revient pas si on part
Fusion_EventScript_HoennHarborKanto::
	goto_if_set FLAG_FUSION_KANTO_VISITED, Fusion_EventScript_HoennHarborKantoAgain
	msgbox Fusion_Text_KantoFirstOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_TravelReturn
	msgbox Fusion_Text_KantoOneWay, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_TravelCancel
	msgbox Fusion_Text_KantoBonVoyage, MSGBOX_DEFAULT
	closemessage
	special Fusion_StorePartyInPC
	setflag FLAG_FUSION_KANTO_VISITED
	setrespawn HEAL_LOCATION_PALLET_TOWN
	playse SE_SHIP
	warp MAP_PALLET_TOWN, 6, 8
	waitstate
	release
	end

Fusion_EventScript_HoennHarborKantoAgain::
	specialvar VAR_RESULT, CanFlyBetweenRegions
	goto_if_eq VAR_RESULT, FALSE, Fusion_EventScript_TravelReturn
	msgbox Fusion_Text_KantoAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_TravelReturn
	closemessage
	playse SE_SHIP
	warp MAP_VERMILION_CITY, 24, 32
	waitstate
	release
	end

Fusion_EventScript_TravelCancel::
	msgbox Fusion_Text_TravelCancel, MSGBOX_DEFAULT
Fusion_EventScript_TravelReturn::
	return

@ --- Carmin sur Mer (marin du port) : retour à Hoenn une fois la Ligue de Kanto finie et le Rubis/Saphir rendus
Fusion_EventScript_VermilionHoenn::
	specialvar VAR_RESULT, CanFlyBetweenRegions
	goto_if_eq VAR_RESULT, FALSE, Fusion_EventScript_TravelReturn
	msgbox Fusion_Text_HoennOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_TravelReturn
	closemessage
	playse SE_SHIP
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

@ --- Bourg Palette : la maison de RF est à vendre, fermée tant qu'elle n'est pas achetée
Fusion_PalletTown_OnLoad::
	call_if_unset FLAG_PALLET_HOUSE_BOUGHT, Fusion_EventScript_PalletCloseHouse
	end

Fusion_EventScript_PalletCloseHouse::
	setmetatile 6, 7, 0x2A3, TRUE
	setmetatile 4, 7, 0x002, TRUE @ pancarte en bois à la place de la boîte aux lettres
	return

Fusion_EventScript_PalletHouseDoor::
	goto_if_set FLAG_PALLET_HOUSE_BOUGHT, Fusion_EventScript_PalletDoorEnd
	msgbox Fusion_Text_PalletHouseLocked, MSGBOX_SIGN
Fusion_EventScript_PalletDoorEnd::
	end

Fusion_EventScript_PalletHouseForSale::
	lockall
	showmoneybox 0, 0
	msgbox Fusion_Text_PalletHouseForSale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_PalletHouseNotBought
	checkmoney 300000
	goto_if_eq VAR_RESULT, FALSE, Fusion_EventScript_PalletHouseNoMoney
	removemoney 300000
	updatemoneybox
	msgbox Fusion_Text_PalletHouseDeal, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	fadescreen FADE_TO_BLACK
	setflag FLAG_PALLET_HOUSE_BOUGHT
	setmetatile 6, 7, 0x2A3, FALSE
	setmetatile 4, 7, 0x2AD, TRUE
	special DrawWholeMapView
	delay 60
	fadescreen FADE_FROM_BLACK
	playfanfare MUS_OBTAIN_ITEM
	msgbox Fusion_Text_PalletHouseBought, MSGBOX_DEFAULT
	waitfanfare
	msgbox Fusion_Text_PalletHouseYours, MSGBOX_DEFAULT
	releaseall
	end

Fusion_EventScript_PalletHouseNoMoney::
	msgbox Fusion_Text_PalletHouseNoMoney, MSGBOX_DEFAULT
Fusion_EventScript_PalletHouseNotBought::
	hidemoneybox
	releaseall
	end

Fusion_Text_KantoFirstOffer:
	.string "Félicitations pour la LIGUE!\p"
	.string "Un navire spécial part pour\n"
	.string "KANTO, une région lointaine.\p"
	.string "Veux-tu en savoir plus?$"

Fusion_Text_KantoOneWay:
	.string "C'est un aller simple: aucun\n"
	.string "bateau ne revient de KANTO.\p"
	.string "Tes POKéMON restent ici, au PC.\n"
	.string "Là-bas, aucune connexion avec\l"
	.string "HOENN… Tu ne pourras pas les\l"
	.string "reprendre dans ton équipe.\p"
	.string "Il faudra devenir MAÎTRE de\n"
	.string "KANTO, et aider un certain CILEO\l"
	.string "à relier les deux régions.\p"
	.string "Tu repartirais de zéro.\n"
	.string "Tu embarques quand même?$"

Fusion_Text_KantoBonVoyage:
	.string "Très bien! Le navire te déposera\n"
	.string "à BOURG PALETTE.\p"
	.string "Bon voyage, {PLAYER}!$"

Fusion_Text_TravelCancel:
	.string "Reviens quand tu seras prêt!$"

Fusion_Text_KantoAgain:
	.string "Un navire part pour CARMIN SUR\n"
	.string "MER, à KANTO. Tu embarques?$"

Fusion_Text_HoennOffer:
	.string "Un navire part pour POIVRESSEL,\n"
	.string "à HOENN. Tu embarques?$"

Fusion_Text_PalletHouseLocked:
	.string "C'est fermé à clé.$"

Fusion_Text_PalletHouseForSale:
	.string "MAISON À VENDRE\n"
	.string "Prix: 300 000¥\p"
	.string "Contacter le vendeur et\n"
	.string "l'acheter?$"

Fusion_Text_PalletHouseDeal:
	.string "Tu appelles le vendeur…\n"
	.string "Rendez-vous chez le notaire!$"

Fusion_Text_PalletHouseNoMoney:
	.string "Tu n'as pas assez d'argent…$"

Fusion_Text_PalletHouseBought:
	.string "{PLAYER} achète la maison!$"

Fusion_Text_PalletHouseYours:
	.string "La boîte aux lettres porte\n"
	.string "maintenant ton nom!$"
