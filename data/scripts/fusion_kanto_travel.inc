@ PokemonNative3G : passage Hoenn <-> Kanto et maison de Bourg Palette (tools/kanto_travel.py)

@ --- Poivressel / Nénucrique (Ligue de Hoenn finie) : destination KANTO du menu du ferry (Fusion_CanTakeFerryToKanto).
@ Le port demande la confirmation (VAR_RESULT = YES / NO), fait embarquer le joueur, puis appelle le voyage.
Fusion_EventScript_KantoFerryConfirm::
	goto_if_set FLAG_FUSION_KANTO_VISITED, Fusion_EventScript_KantoFerryConfirmAgain
	msgbox Fusion_Text_KantoFirstTrip, MSGBOX_YESNO
	return

Fusion_EventScript_KantoFerryConfirmAgain::
	msgbox Fusion_Text_KantoItIs, MSGBOX_YESNO
	return

@ Premier voyage : aller simple vers Bourg Palette, l'équipe reste au PC de Hoenn ; ensuite Carmin sur Mer
Fusion_EventScript_KantoFerryWarp::
	goto_if_set FLAG_FUSION_KANTO_VISITED, Fusion_EventScript_KantoFerryVermilion
	special Fusion_StorePartyInPC
	setflag FLAG_FUSION_KANTO_VISITED
	setrespawn HEAL_LOCATION_PALLET_TOWN
	warp MAP_PALLET_TOWN, 6, 8
	waitstate
	release
	end

Fusion_EventScript_KantoFerryVermilion::
	warp MAP_VERMILION_CITY, 24, 32
	waitstate
	release
	end

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
	setmetatile 4, 6, 0x011, FALSE @ pancarte en bois à la place de la boîte aux lettres (2 cases ; haut : herbe, comme en 4,5)
	setmetatile 4, 7, 0x002, TRUE
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
	setmetatile 4, 6, 0x2A5, FALSE
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

Fusion_Text_KantoFirstTrip:
	.string "KANTO? Le voyage d'une vie!\p"
	.string "Un conseil de vieux marin…\n"
	.string "Là-bas, personne ne connaît\l"
	.string "tes exploits de HOENN.\p"
	.string "Et les PC de KANTO ne sont pas\n"
	.string "reliés aux nôtres: tes POKéMON\l"
	.string "t'attendront ici, au chaud.\p"
	.string "Tu repartirais comme au premier\n"
	.string "jour, avec ton SAC et ton\l"
	.string "courage pour seuls bagages.\p"
	.string "Et ce bateau-là ne fait pas\n"
	.string "le retour… Les rares dresseurs\l"
	.string "revenus de KANTO en sont tous\l"
	.string "rentrés MAÎTRES.\p"
	.string "On dit aussi qu'un certain CILEO\n"
	.string "cherche à relier les deux régions.\p"
	.string "Alors, on lève l'ancre?$"

Fusion_Text_KantoItIs:
	.string "Cap sur CARMIN SUR MER, à KANTO?$"

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
