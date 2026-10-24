EventScript_RepelWoreOff::
	specialvar VAR_0x8004, AutoRepel_Check @ PokemonNative3G : AUTO-REPOUSSE (Kanto, Route 11)
	goto_if_ne VAR_0x8004, ITEM_NONE, Fusion_EventScript_AutoRepel
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
	end

Fusion_EventScript_AutoRepel::
	lockall
	msgbox Fusion_Text_AutoRepelAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_AutoRepelNo
	special AutoRepel_Use
	playse SE_REPEL
	msgbox Fusion_Text_AutoRepelUsed, MSGBOX_DEFAULT
Fusion_EventScript_AutoRepelNo::
	releaseall
	end

Fusion_Text_AutoRepelAsk:
	.string "L'effet de REPOUSSE se dissipe…\p"
	.string "AUTO-REPOUSSE: utiliser un autre\n"
	.string "{STR_VAR_1}?$"

Fusion_Text_AutoRepelUsed:
	.string "{PLAYER} utilise\n"
	.string "{STR_VAR_1}.$"

Text_RepelWoreOff:
	.string "L'effet de REPOUSSE se dissipe…$"
