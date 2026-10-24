@ PokemonNative3G : charmes des jeux suivants (tools/fusion_charms.py), donnés par les concepteurs de GAME FREAK
@ quand le POKéDEX NATIONAL est complet (HasAllMons, comme le diplôme national).
Fusion_EventScript_TryGiveShinyCharm::
	goto_if_set FLAG_GOT_SHINY_CHARM, Fusion_EventScript_CharmReturn
	specialvar VAR_RESULT, HasAllMons
	goto_if_eq VAR_RESULT, FALSE, Fusion_EventScript_CharmReturn
	msgbox Fusion_Text_NationalDexShinyCharm, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM
	goto_if_eq VAR_RESULT, FALSE, Fusion_EventScript_CharmReturn
	setflag FLAG_GOT_SHINY_CHARM
	msgbox Fusion_Text_ExplainShinyCharm, MSGBOX_DEFAULT
Fusion_EventScript_CharmReturn::
	return

Fusion_EventScript_TryGiveOvalCharm::
	goto_if_set FLAG_GOT_OVAL_CHARM, Fusion_EventScript_CharmReturn
	specialvar VAR_RESULT, HasAllMons
	goto_if_eq VAR_RESULT, FALSE, Fusion_EventScript_CharmReturn
	msgbox Fusion_Text_NationalDexOvalCharm, MSGBOX_DEFAULT
	giveitem ITEM_OVAL_CHARM
	goto_if_eq VAR_RESULT, FALSE, Fusion_EventScript_CharmReturn
	setflag FLAG_GOT_OVAL_CHARM
	msgbox Fusion_Text_ExplainOvalCharm, MSGBOX_DEFAULT
	return

Fusion_Text_NationalDexShinyCharm:
	.string "Mais… Ce n'est pas seulement le\n"
	.string "POKéDEX de HOENN!\p"
	.string "Tu as complété le POKéDEX\n"
	.string "NATIONAL! Incroyable!\p"
	.string "Tiens, prends ce charme spécial!$"

Fusion_Text_ExplainShinyCharm:
	.string "Le CHARME CHROMA attire les\n"
	.string "POKéMON aux couleurs rares!\p"
	.string "Tu en croiseras bien plus\n"
	.string "souvent dans les hautes herbes!$"

Fusion_Text_NationalDexOvalCharm:
	.string "Attends… Tous les POKéMON du\n"
	.string "POKéDEX NATIONAL?\p"
	.string "Tu es un vrai maître! Prends ce\n"
	.string "charme, il te sera utile!$"

Fusion_Text_ExplainOvalCharm:
	.string "Avec le CHARME OVALE, la PENSION\n"
	.string "trouvera des OEUFS bien plus\l"
	.string "souvent!$"
