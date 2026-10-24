@ PokemonNative3G : les pêcheurs de Kanto améliorent la canne au lieu d'en donner une 2e (chaîne de pêche,
@ src/fusion_events.c). STR_VAR_1 = nom de la canne.
Fusion_EventScript_RodUpgraded::
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	msgbox Fusion_Text_RodUpgraded, MSGBOX_DEFAULT
	waitfanfare
	return

Fusion_Text_RodUpgraded:
	.string "La {STR_VAR_1} de {PLAYER}\n"
	.string "est améliorée!$"

@ CANNE (Carmin sur Mer, le GOUROU de la pêche)
VermilionCity_House1_Text_ShowMeYourRod:
	.string "Oh! Tu as déjà une CANNE!\n"
	.string "Fais-moi voir ça…\p"
	.string "Elle n'est pas mal, mais je vais\n"
	.string "l'améliorer à ma façon!$"

VermilionCity_House1_Text_ExplainRodChain:
	.string "Écoute bien, c'est le secret\n"
	.string "des GOUROUS de la pêche!\p"
	.string "Si tu remontes des POKéMON l'un\n"
	.string "après l'autre sans bouger,\p"
	.string "chaque prise rend les POKéMON aux\n"
	.string "couleurs rares un peu plus\l"
	.string "faciles à pêcher!\p"
	.string "Mais si rien ne mord, ou si tu\n"
	.string "fais un seul pas, la série\l"
	.string "repart de zéro!$"

@ SUPER CANNE (Parmanie, le frère du GOUROU)
FuchsiaCity_House2_Text_ShowMeYourRod:
	.string "Tiens! Tu as déjà une SUPER CANNE!\n"
	.string "Passe-la-moi…\p"
	.string "Je vais lui mettre mon\n"
	.string "moulinet spécial!$"

FuchsiaCity_House2_Text_ExplainRodChain:
	.string "Avec mon moulinet, enchaîne les\n"
	.string "prises au même endroit!\p"
	.string "Plus la série est longue, plus tu\n"
	.string "as de chances de remonter un\l"
	.string "POKéMON chromatique!\p"
	.string "Un raté ou un pas de côté, et\n"
	.string "la série est perdue. Pigé?$"

@ MEGA CANNE (Route 12, l'autre frère, celui des records de MAGICARPE)
Route12_FishingHouse_Text_ShowMeYourRod:
	.string "Une MEGA CANNE? Hmpf, pas mal…\n"
	.string "Mais laisse faire un pro!\p"
	.string "Je vais y nouer mon fil d'or!$"

Route12_FishingHouse_Text_ExplainRodChain:
	.string "Le fil d'or ne pardonne pas!\p"
	.string "Reste à la même place et remonte\n"
	.string "prise sur prise: chaque POKéMON\l"
	.string "pêché attire les chromatiques!\p"
	.string "Si ça ne mord pas, ou si tu\n"
	.string "bouges, tout est à refaire!$"
