CeladonCity_Restaurant_MapScripts::
	.byte 0

CeladonCity_Restaurant_EventScript_Chef::
	msgbox CeladonCity_Restaurant_Text_TakingBreakRightNow, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_Woman::
	msgbox CeladonCity_Restaurant_Text_OftenGoToDrugstore, MSGBOX_NPC
	end

@ PokemonNative3G : il a tout perdu, même sa BOITE JETONS (celle de Hoenn suffit). 9999 jetons : LEVEINARD chromatique
CeladonCity_Restaurant_EventScript_CoinCaseMan::
	lock
	faceplayer
	setflag FLAG_KANTO_GOT_COIN_CASE
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Restaurant_EventScript_CoinCaseManSad
	checkcoins VAR_0x8004
	goto_if_lt VAR_0x8004, 9999, CeladonCity_Restaurant_EventScript_CoinCaseManSad
	msgbox Fusion_Text_CoinCaseManSad, MSGBOX_DEFAULT
	msgbox Fusion_Text_CoinCaseManOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CeladonCity_Restaurant_EventScript_CoinCaseManRelease
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, CeladonCity_Restaurant_EventScript_CoinCaseManNoRoom
	removecoins 9999
	msgbox Fusion_Text_CoinCaseManThanks, MSGBOX_DEFAULT
	special GiveShinyChansey
	playfanfare MUS_OBTAIN_ITEM
	msgbox Fusion_Text_ReceivedChansey, MSGBOX_DEFAULT
	waitfanfare
	msgbox Fusion_Text_CoinCaseManBye, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

CeladonCity_Restaurant_EventScript_CoinCaseManSad::
	msgbox Fusion_Text_CoinCaseManSad, MSGBOX_DEFAULT
CeladonCity_Restaurant_EventScript_CoinCaseManRelease::
	release
	end

CeladonCity_Restaurant_EventScript_CoinCaseManNoRoom::
	msgbox Fusion_Text_CoinCaseManNoRoom, MSGBOX_DEFAULT
	release
	end

Fusion_Text_CoinCaseManSad:
	.string "J'ai tout perdu aux machines…\p"
	.string "Mes jetons, mes économies…\n"
	.string "Même ma BOITE JETONS!\p"
	.string "Je n'ai plus rien… Snif…$"

Fusion_Text_CoinCaseManOffer:
	.string "Hein? Ta BOITE JETONS est pleine?\n"
	.string "Tu… tu me donnerais tes jetons?$"

Fusion_Text_CoinCaseManThanks:
	.string "C'est vrai?! Merci, merci!\p"
	.string "Tiens, prends mon plus grand trésor.\n"
	.string "Il m'a toujours porté chance!$"

Fusion_Text_ReceivedChansey:
	.string "{PLAYER} reçoit\n"
	.string "un LEVEINARD!$"

Fusion_Text_CoinCaseManBye:
	.string "Cette fois, je ne jouerai plus\n"
	.string "jamais… Adieu!$"

Fusion_Text_CoinCaseManNoRoom:
	.string "Ton équipe est pleine…\n"
	.string "Je ne peux rien te donner.$"

CeladonCity_Restaurant_EventScript_NoRoomForCoinCase::
	msgbox CeladonCity_Restaurant_Text_MakeRoomForThis
	release
	end

CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase::
	msgbox CeladonCity_Restaurant_Text_ThoughtIdWinItBack
	release
	end

CeladonCity_Restaurant_EventScript_WorkerM::
	msgbox CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_FatMan::
	msgbox CeladonCity_Restaurant_Text_ManLostItAllAtSlots, MSGBOX_NPC
	end
