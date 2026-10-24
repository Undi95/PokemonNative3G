@ PokemonNative3G : assistant des pensions (Route 117 et Île 4) qui donne les œufs des starters manquants
@ après la Ligue de la région (src/fusion_events.c)

Fusion_EventScript_StarterEggsHoenn::
	setvar VAR_0x8004, 1
	goto Fusion_EventScript_StarterEggs

Fusion_EventScript_StarterEggsKanto::
	setvar VAR_0x8004, 0
	goto Fusion_EventScript_StarterEggs

Fusion_EventScript_StarterEggs::
	lock
	faceplayer
	specialvar VAR_0x8005, GetStarterEggToGive
	goto_if_eq VAR_0x8005, 0xFFFF, Fusion_EventScript_StarterEggsNotYet
	goto_if_eq VAR_0x8005, SPECIES_NONE, Fusion_EventScript_StarterEggsNoMore
	msgbox Fusion_Text_StarterEggTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_StarterEggDeclined
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, Fusion_EventScript_StarterEggNoRoom
	special SetStarterEggGiven
	playfanfare MUS_OBTAIN_ITEM
	message Fusion_Text_ReceivedStarterEgg
	waitfanfare
	giveegg VAR_0x8005
	specialvar VAR_0x8005, GetStarterEggToGive
	goto_if_eq VAR_0x8005, SPECIES_NONE, Fusion_EventScript_StarterEggsLastOne
	msgbox Fusion_Text_StarterEggMoreLeft, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_StarterEggsLastOne::
	msgbox Fusion_Text_StarterEggsLastOne, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_StarterEggsNotYet::
	goto_if_eq VAR_0x8004, 0, Fusion_EventScript_StarterEggsNotYetKanto
	msgbox Fusion_Text_StarterEggsNotYetHoenn, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_StarterEggsNotYetKanto::
	msgbox Fusion_Text_StarterEggsNotYetKanto, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_StarterEggsNoMore::
	msgbox Fusion_Text_StarterEggsNoMore, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_StarterEggDeclined::
	msgbox Fusion_Text_StarterEggDeclined, MSGBOX_DEFAULT
	release
	end

Fusion_EventScript_StarterEggNoRoom::
	msgbox Fusion_Text_StarterEggNoRoom, MSGBOX_DEFAULT
	release
	end

Fusion_Text_StarterEggsNotYetHoenn:
	.string "Je suis l'assistant du PROF. SEKO.\p"
	.string "Les POKéMON de départ que les\n"
	.string "dresseurs n'ont pas choisis grandissent\l"
	.string "ici, et ils pondent des OEUFS.\p"
	.string "Je les garde pour un dresseur digne\n"
	.string "de ce nom… Le MAÎTRE de la LIGUE\l"
	.string "POKéMON de HOENN, par exemple!$"

Fusion_Text_StarterEggsNotYetKanto:
	.string "Je suis l'assistant du PROF. CHEN.\p"
	.string "Les POKéMON de départ que les\n"
	.string "dresseurs n'ont pas choisis grandissent\l"
	.string "ici, et ils pondent des OEUFS.\p"
	.string "Je les garde pour un dresseur digne\n"
	.string "de ce nom… Le MAÎTRE du PLATEAU\l"
	.string "INDIGO, par exemple!$"

Fusion_Text_StarterEggTakeIt:
	.string "Ah! Le MAÎTRE de la LIGUE!\p"
	.string "J'ai ici l'OEUF d'un POKéMON de départ\n"
	.string "que tu n'as pas encore.\p"
	.string "Tu veux bien t'en occuper?$"

Fusion_Text_ReceivedStarterEgg:
	.string "{PLAYER} reçoit l'OEUF.$"

Fusion_Text_StarterEggMoreLeft:
	.string "Il m'en reste d'autres.\n"
	.string "Reviens me voir quand tu veux!$"

Fusion_Text_StarterEggsLastOne:
	.string "C'était le dernier OEUF.\n"
	.string "Prends-en bien soin!$"

Fusion_Text_StarterEggsNoMore:
	.string "Tu as tous les POKéMON de départ.\n"
	.string "Le professeur serait fier de toi!$"

Fusion_Text_StarterEggDeclined:
	.string "Je comprends. Reviens quand tu veux.$"

Fusion_Text_StarterEggNoRoom:
	.string "Ton équipe est pleine…\n"
	.string "Fais de la place et reviens me voir.$"
