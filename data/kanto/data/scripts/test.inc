Test_EventScript_NPC::
	msgbox Test_Text_WelcomeToWorldOfPokemon, MSGBOX_NPC
	end

Kanto_EventScript_TestSignpostMsg::
	msgbox Test_Text_ThisIsASignpost, MSGBOX_SIGN
	end

Test_EventScript_CoordEvent::
	msgbox Test_Text_ThisIsACoordEvent, MSGBOX_SIGN
	end

Test_Text_WelcomeToWorldOfPokemon::
	.string "テストよう　メッセージです！\n"
	.string "ポケモンの　せかいへ　ようこそ！$"

Test_Text_ThisIsASignpost::
	.string "テストよう　メッセージです！\n"
	.string "かんばん　です$"

Test_Text_ThisIsACoordEvent::
	.string "テストよう　メッセージです！\n"
	.string "ざひょう　チェックの　イベントです$"

	ptr_align
Test_Text_Empty::
	.string "$"
