# Scripts : specials, commandes, macros

> Généré par `tools/cartographie.py` — ne pas éditer à la main.

## Specials (`data/specials.inc`)

Émeraude 524, Rouge Feu 272, communs 125.

**RF seul — portés (123)** :
NullFieldSpecial, Script_HasTrainerBeenFought, EndTrainerApproach, StartRematchBattle, HasLeadMonBeenRenamed,
Field_AskSaveTheGame, ShowEasyChatMessage, GetHeracrossSizeRecordInfo, CompareHeracrossSize,
GetMagikarpSizeRecordInfo, CompareMagikarpSize, NameRaterWasNicknameChanged,
BufferRandomHobbyOrLifestyleString, RegisteredItemHandleBikeSwap, GetPlayerXY, BufferBigGuyOrBigGirlString,
BufferSonOrDaughterString, StartOldManTutorialBattle, Script_IsFanClubMemberFanOfPlayer,
Script_GetNumFansOfPlayerInTrainerFanClub, Script_BufferFanClubTrainerName,
Script_TryLoseFansFromPlayTimeAfterLinkBattle, Script_TryLoseFansFromPlayTime, Script_SetPlayerGotFirstFans,
Script_UpdateTrainerFanClubGameClear, DaycareMonReceivedMail, ShowBattleRecords, GetPokedexCount,
GetProfOaksRatingMessage, AnimatePcTurnOn, AnimatePcTurnOff, GetElevatorFloor, SelectMoveDeleterMove,
GetLeadMonFriendship, ShowTownMap, CreatePCMenu, HallOfFamePCBeginFade, ShowDiploma, EnterHallOfFame,
AnimateElevator, GetRandomSlotMachineId, AreLeadMonEVsMaxedOut, PlayerHasGrassPokemonInParty,
IsStarterFirstStageInParty, IsThereRoomInAnyBoxForMorePokemon, DrawElevatorCurrentFloorWindow,
SetIcefallCaveCrackedIceMetatiles, ShakeScreen, StartLegendaryBattle, SetUpTrainerMovement,
StartSouthernIslandBattle, GetPartyMonSpecies, HasAllKantoMons, IsMonOTNameNotPlayers, SetPostgameFlags,
StartMarowakBattle, ForcePlayerOntoBike, ListMenu, ReturnToListMenu, DoPicboxCancel, SetVermilionTrashCans,
SeafoamIslandsB4F_CurrentDumpsPlayerOnLand, SampleResortGorgeousMonAndReward, CheckAddCoins,
GetDaycarePokemonCount, CloseElevatorCurrentFloorWindow, ForcePlayerToStartSurfing, GetStarterSpecies,
SetSeenMon, VsSeekerResetObjectMovementAfterChargeComplete, UpdateTrainerCardPhotoIcons,
StickerManGetBragFlags, SetUsedPkmnCenterQuestLogEvent, SetWalkingIntoSignVars, DisableMsgBoxWalkaway,
VsSeekerFreezeObjectsAfterChargeComplete, SetFlavorTextFlagFromSpecialVars, UpdatePickStateFromSpecialVar8005,
OverworldWhiteOutGetMoneyLoss, PutMonInRoute5Daycare, GetCostToWithdrawRoute5DaycareMon,
IsThereMonInRoute5Daycare, GetNumLevelsGainedForRoute5DaycareMon, TakePokemonFromRoute5Daycare,
DoSeagallopFerryScene, DoesPlayerPartyContainSpecies, Script_SetHelpContext, BackupHelpContext,
RestoreHelpContext, QuestLog_StartRecordingInputsAfterDeferredEvent, GetMartClerkObjectId, GetQuestLogState,
QuestLog_CutRecording, OpenMuseumFossilPic, CloseMuseumFossilPic, SetBattledTrainerFlag, SetHelpContextForMap,
DoSSAnneDepartureCutscene, IsNationalPokedexEnabled, CallTrainerTowerFunc, DaisyMassageServices,
HelpSystem_Disable, HelpSystem_Enable, Script_HasEnoughBerryPowder, Script_TakeBerryPowder,
DoPokemonLeagueLightingEffect, CapeBrinkGetMoveToTeachLeadPokemon, HasLearnedAllMovesFromCapeBrinkTutor,
DoCredits, DrawSeagallopDestinationMenu, GetSelectedSeagallopDestination, GetSeagallopNumber,
IsPlayerLeftOfVermilionSailor, ReadTrainerTowerAndValidate, HasAllMons, IsPlayerNotInTrainerTowerLobby,
BrailleCursorToggle, PlayerPartyContainsSpeciesWithPlayerID, AnimateTeleporterHousing, AnimateTeleporterCable,
InitElevatorFloorSelectMenuPos, UpdateLoreleiDollCollection, LoopWingFlapSound

**RF seul — stubs (24)** (`src/kanto_specials_stubs.c`) :
EnterColosseumPlayerSpot, EnterTradeSeat, StartWiredCableClubTrade, CableClub_AskSaveTheGame, TryContestLinkup,
BattleTowerMapScript2, ChooseNextBattleTowerTrainer, CheckPartyBattleTowerBanlist,
PrintBattleTowerTrainerGreeting, BufferEReaderTrainerGreeting, StartSpecialBattle, SetBattleTowerProperty,
BattleTowerUtil, SetBattleTowerParty, SaveBattleTowerProgress, BattleTower_SoftReset,
DetermineBattleTowerPrize, GiveBattleTowerPrize, AwardBattleTowerRibbons, ChooseBattleTowerPlayerParty,
ReducePlayerPartyToThree, Dummy_TryEnableBravoTrainerBattleTower, DoDeoxysTriangleInteraction,
SetDeoxysTrianglePalette

**RF seul — absents (0)** :
(aucun)

**Émeraude seul (399)** :
SetPlayerSecretBase, CheckPlayerHasSecretBase, EnterSecretBase, ClearAndLeaveSecretBase, MoveOutOfSecretBase,
IsCurSecretBaseOwnedByAnotherPlayer, GetCurSecretBaseRegistrationValidity, ToggleCurSecretBaseRegistry,
ShowSecretBaseDecorationMenu, ShowSecretBaseRegistryMenu, PrepSecretBaseBattleFlags,
GetSecretBaseOwnerAndState, InitSecretBaseDecorationSprites, SetDecoration, GetObjectEventLocalIdByFlag,
GetSecretBaseTypeInFrontOfPlayer, SetSecretBaseOwnerGfxId, PutAwayDecorationIteration,
EnterNewlyCreatedSecretBase, SetBattledOwnerFromResult, DoSecretBasePCTurnOffEffect,
RecordMixingPlayerSpotTriggered, ValidateMixingGameLanguage, ColosseumPlayerSpotTriggered,
PlayerEnteredTradeSeat, Script_StartWiredTrade, CableClubSaveGame, TryBerryBlenderLinkup, GetLinkPartnerNames,
SpawnLinkPartnerObjectEvent, ObjectEventInteractionGetBerryTreeData, ObjectEventInteractionGetBerryName,
ObjectEventInteractionGetBerryCountString, Bag_ChooseBerry, ObjectEventInteractionPlantBerryTree,
ObjectEventInteractionPickBerryTree, ObjectEventInteractionRemoveBerryTree,
ObjectEventInteractionWaterBerryTree, PlayerHasBerries, GetTrainerFlag, DoTrainerApproach,
BattleSetup_StartRematchBattle, TurnOffTVScreen, DoTVShow, DoPokeNews, GetRandomActiveShowIdx,
GetSelectedTVShow, InterviewBefore, InterviewAfter, IsLeadMonNicknamedOrNotEnglish,
SetContestCategoryStringVarForInterview, GetNextActiveShowIfMassOutbreak, IsTVShowAlreadyInQueue,
CheckForPlayersHouseNews, GetMomOrDadStringForTVMessage, ResetTVShowState, GetContestWinnerId,
GetContestPlayerId, GetNpcContestantLocalId, BufferContestWinnerTrainerName, BufferContestWinnerMonName,
BufferContestTrainerAndMonNames, GetContestMonConditionRanking, SetContestTrainerGfxIds, TryEnterContestMon,
GetContestantNamesAtRank, SetLinkContestPlayerGfx, GetContestMonCondition, HasMonWonThisContestBefore,
GiveMonContestRibbon, IsContestDebugActive, GiveMonArtistRibbon, TryContestGModeLinkup, SaveGame,
ShowEasyChatProfile, Script_GetCurrentMauvilleMan, HasBardSongBeenChanged, SaveBardSongLyrics,
HasHipsterTaughtWord, SetHipsterTaughtWord, HipsterTryTeachWord, PlayBardSong, SetMauvilleOldManObjEventGfx,
GenerateGiddyLine, GiddyShouldTellAnotherTale, StorytellerGetFreeStorySlot, Script_StorytellerDisplayStory,
StorytellerStoryListMenu, StorytellerUpdateStat, Script_StorytellerInitializeRandomStat,
HasStorytellerAlreadyRecorded, TraderMenuGetDecoration, GetTraderTradedFlag, DoesPlayerHaveNoDecorations,
IsDecorationCategoryFull, TraderShowDecorationMenu, TraderDoDecorationTrade, GetSeedotSizeRecordInfo,
CompareSeedotSize, GetLotadSizeRecordInfo, CompareLotadSize, TryPutNameRaterShowOnTheAir,
BufferTrendyPhraseString, IsTrendyPhraseBoring, BufferDeepLinkPhrase, GetDewfordHallPaintingNameIndex,
SwapRegisteredBike, ShouldReadyContestArtist, SaveMuseumContestPainting, DoesContestCategoryHaveMuseumPainting,
CountPlayerMuseumPaintings, ShowContestPainting, MauvilleGymSetDefaultBarriers, MauvilleGymPressSwitch,
StorePlayerCoordsInVars, MauvilleGymDeactivatePuzzle, PetalburgGymSlideOpenRoomDoors,
PetalburgGymUnlockRoomDoors, GetPlayerBigGuyGirlString, GetRivalSonDaughterString, CableCarWarp, CableCar,
StartWallClock, Special_ViewWallClock, ChooseStarter, StartWallyTutorialBattle, GetFirstFreePokeblockSlot,
DoBerryBlending, PlayRoulette, IsFanClubMemberFanOfPlayer, GetNumFansOfPlayerInTrainerFanClub,
BufferFanClubTrainerName, TryLoseFansFromPlayTimeAfterLinkBattle, TryLoseFansFromPlayTime,
SetPlayerGotFirstFans, UpdateTrainerFanClubGameClear, GabbyAndTyGetBattleNum, GabbyAndTyAfterInterview,
GabbyAndTyBeforeInterview, DoTVShowInSearchOfTrainers, IsGabbyAndTyShowOnTheAir, GabbyAndTyGetLastQuote,
GabbyAndTyGetLastBattleTrivia, GetGabbyAndTyLocalIds, CheckDaycareMonReceivedMail, ShowLinkBattleRecords,
RotatingGate_InitPuzzle, RotatingGate_InitPuzzleAndGraphics, SetSSTidalFlag, ResetSSTidalFlag,
GetPokeblockFeederInFront, OpenPokeblockCaseOnFeeder, IsMirageIslandPresent, UpdateShoalTideFlag,
InitBirchState, ScriptGetPokedexInfo, ShowPokedexRatingMessage, DoPCTurnOnEffect, DoPCTurnOffEffect,
SetDeptStoreFloor, DoLotteryCornerComputerEffect, EndLotteryCornerComputerEffect,
MoveDeleterChooseMoveToForget, GetRecordedCyclingRoadResults, Special_BeginCyclingRoadChallenge,
FinishCyclingRoadChallenge, UpdateCyclingRoadState, GetLeadMonFriendshipScore, CallFrontierUtilFunc,
CallBattleTowerFunc, CallBattleDomeFunction, CallBattlePalaceFunction, CopyEReaderTrainerGreeting,
DoSpecialTrainerBattle, CallBattleArenaFunction, CallBattleFactoryFunction, CallBattlePikeFunction,
CallBattlePyramidFunction, StopMapMusic, CallVerdanturfTentFunction, CallFallarborTentFunction,
CallSlateportTentFunction, ChoosePartyForBattleFrontier, GetBattleTowerSinglesStreak,
ReducePlayerPartyToSelectedMons, FieldShowRegionMap, GetWeekCount, RetrieveLotteryNumber,
PickLotteryCornerTicket, ShowBerryBlenderRecordWindow, ResetTrickHouseNuggetFlag, SetTrickHouseNuggetFlag,
ScriptMenu_CreatePCMultichoice, AccessHallOfFamePC, Special_ShowDiploma, CheckLeadMonCool, CheckLeadMonBeauty,
CheckLeadMonCute, CheckLeadMonSmart, CheckLeadMonTough, GameClear, MoveElevator, ShowGlassWorkshopMenu,
GetPokeblockNameByMonNature, GetSecretBaseNearbyMapName, CheckRelicanthWailord,
ShouldDoBrailleRegirockEffectOld, DoOrbEffect, FadeOutOrbEffect, WaitWeather, GetSlotMachineId,
FoundAbandonedShipRoom1Key, FoundAbandonedShipRoom2Key, FoundAbandonedShipRoom4Key, FoundAbandonedShipRoom6Key,
Special_AreLeadMonEVsMaxedOut, TryUpdateRusturfTunnelState, IsGrassTypeInParty, DoContestHallWarp,
LoadWallyZigzagoon, IsStarterInParty, CopyCurSecretBaseOwnerName_StrVar1, ScriptCheckFreePokemonStorageSpace,
DoSealedChamberShakingEffect_Long, ShowDeptStoreElevatorFloorSelect, InteractWithShieldOrTVDecoration,
SetSootopolisGymCrackedIceMetatiles, ShakeCamera, BattleSetup_StartLegendaryBattle, SetTrainerFacingDirection,
DoSealedChamberShakingEffect_Short, FoundBlackGlasses, ShowContestEntryMonPic, HideContestEntryMonPic,
BattleSetup_StartLatiBattle, SetRoute119Weather, SetRoute123Weather, GetContestMultiplayerId,
ScriptGetPartyMonSpecies, TryInitBattleTowerAwardManObjectEvent, MoveOutOfSecretBaseFromOutside,
SetPacifidlogTMReceivedDay, GetDaysUntilPacifidlogTMAvailable, HasAllHoennMons, MonOTNameNotPlayer,
BufferLottoTicketNumber, TryHideBattleTowerReporter, GenerateContestRand, SetChampionSaveWarp,
TryPutTreasureInvestigatorsOnAir, TryPutLotteryWinnerReportOnAir, TryPutTrainerFanClubOnAir,
ShouldHideFanClubInterviewer, PutFanClubSpecialOnTheAir, IncrementDailyPlantedBerries,
IncrementDailyPickedBerries, InitSecretBaseVars, CheckInteractedWithFriendsSandOrnament,
DeclinedSecretBaseBattle, DrewSecretBaseBattle, WonSecretBaseBattle, LostSecretBaseBattle,
CheckInteractedWithFriendsDollDecor, CheckInteractedWithFriendsCushionDecor,
CheckInteractedWithFriendsFurnitureBottom, CheckInteractedWithFriendsFurnitureMiddle,
CheckInteractedWithFriendsFurnitureTop, CheckInteractedWithFriendsPosterDecor, SetLilycoveLadyGfx,
Script_GetLilycoveLadyId, GetFavorLadyState, BufferFavorLadyRequest, HasAnotherPlayerGivenFavorLadyItem,
BufferFavorLadyItemName, BufferFavorLadyPlayerName, DidFavorLadyLikeItem, Script_FavorLadyOpenBagMenu,
Script_DoesFavorLadyLikeItem, IsFavorLadyThresholdMet, FavorLadyGetPrize, SetFavorLadyState_Complete,
GetQuizLadyState, GetQuizAuthor, IsQuizLadyWaitingForChallenger, QuizLadyShowQuizQuestion,
QuizLadyGetPlayerAnswer, IsQuizAnswerCorrect, BufferQuizPrizeItem, SetQuizLadyState_Complete,
BufferQuizAuthorNameAndCheckIfLady, SetQuizLadyState_GivePrize, ClearQuizLadyPlayerAnswer,
Script_QuizLadyOpenBagMenu, ClearQuizLadyQuestionAndAnswer, QuizLadySetCustomQuestion,
QuizLadyTakePrizeForCustomQuiz, QuizLadyRecordCustomQuizData, QuizLadySetWaitingForChallenger,
BufferQuizCorrectAnswer, BufferQuizPrizeName, QuizLadyPickNewQuestion, ShouldContestLadyShowGoOnAir,
HasPlayerGivenContestLadyPokeblock, Script_BufferContestLadyCategoryAndMonName,
OpenPokeblockCaseForContestLady, SetContestLadyGivenPokeblock, GetContestLadyMonSpecies,
GetContestLadyCategory, PutLilycoveContestLadyShowOnTheAir, CloseBattlePikeCurtain, CallApprenticeFunction,
ShouldTryGetTrainerScript, ShowMapNamePopup, DoMirageTowerCeilingCrumble, SetMirageTowerVisibility,
StartPlayerDescendMirageTower, OffsetCameraForBattle, GetDeptStoreDefaultFloorChoice, BufferVarsForIVRater,
LinkContestWaitForConnection, GetWirelessCommType, LinkContestTryShowWirelessIndicator,
LinkContestTryHideWirelessIndicator, IsWirelessContest, ShowRankingHallRecordsWindow,
ScrollRankingHallRecordsWindow, ShowFrontierManiacMessage, IsContestWithRSPlayer, ClearLinkContestFlags,
TryContestEModeLinkup, ShowScrollableMultichoice, ScrollableMultichoice_TryReturnToList,
BufferBattleTowerElevatorFloors, TryStoreHeldItemsInPyramidBag, ChooseItemsToTossFromPyramidBag,
DoBattlePyramidMonsHaveHeldItem, BattlePyramidChooseMonHeldItems, SetBattleTowerLinkPlayerGfx,
ShowNatureGirlMessage, ShowBattlePointsWindow, UpdateBattlePointsWindow, CloseBattlePointsWindow,
GiveFrontierBattlePoints, TakeFrontierBattlePoints, GetFrontierBattlePoints,
ShowFrontierExchangeCornerItemIconWindow, CloseFrontierExchangeCornerItemIconWindow, HasEnoughBerryPowder,
TakeBerryPowder, ShowFrontierGamblerLookingMessage, ShowFrontierGamblerGoMessage, Script_DoRayquazaScene,
OpenPokenavForTutorial, ScriptMenu_CreateStartMenuForPokenavTutorial, CountPlayerTrainerStars,
BufferBattleFrontierTutorMoveName, CloseBattleFrontierTutorWindow, ScrollableMultichoice_RedrawPersistentMenu,
GetBattleFrontierTutorMoveIndex, ScrollableMultichoice_ClosePersistentMenu, DoDeoxysRockInteraction,
SetDeoxysRockPalette, StartMirageTowerDisintegration, StartMirageTowerShake, StartMirageTowerFossilFallAndSink,
SetMatchCallRegisteredFlag, DoDomeConfetti, CreateAbnormalWeatherEvent, GetAbnormalWeatherMapNameAndType,
GetMartEmployeeObjectEventId, SaveForBattleTowerLink, Unused_SetWeatherSunny, IsTrainerRegistered,
ShouldDoBrailleRegicePuzzle, ScriptMenu_CreateLilycoveSSTidalMultichoice, GetLilycoveSSTidalSelection,
TurnOnTVScreen, SetMewAboveGrass, ShouldDistributeEonTicket, LinkRetireStatusWithBattleTowerPartner,
BattleTowerReconnectLink, CallTrainerHillFunction, LoopWingFlapSE, DestroyMewEmergingGrassSprite,
TryBufferWaldaPhrase, DoWaldaNamingScreen, TryGetWallpaperWithWaldaPhrase, PlayerNotAtTrainerHillEntrance,
GetBattlePyramidHint, LoadLinkContestPlayerPalettes, ShowTrainerHillRecords, PlayerFaceTrainerAfterBattle,
ResetHealLocationFromDewford, IsLastMonThatKnowsSurf, CountPartyAliveNonEggMons,
TryPrepareSecondApproachingTrainer, RemoveRecordsWindow, CloseDeptStoreElevatorWindow,
TrySetBattleTowerLinkType

## Commandes de script (`data/script_cmd_table.inc`)

Émeraude 1, Rouge Feu 214. Opcodes qui diffèrent (la fusion garde ceux d'Émeraude ; ceux de RF sont dans `src/kanto_scrcmd.c`) :

| Opcode | Émeraude | Rouge Feu |
|---|---|---|
| 0x01 | — | ScrCmd_nop1 |
| 0x02 | — | ScrCmd_end |
| 0x03 | — | ScrCmd_return |
| 0x04 | — | ScrCmd_call |
| 0x05 | — | ScrCmd_goto |
| 0x06 | — | ScrCmd_goto_if |
| 0x07 | — | ScrCmd_call_if |
| 0x08 | — | ScrCmd_gotostd |
| 0x09 | — | ScrCmd_callstd |
| 0x0a | — | ScrCmd_gotostd_if |
| 0x0b | — | ScrCmd_callstd_if |
| 0x0c | — | ScrCmd_returnram |
| 0x0d | — | ScrCmd_endram |
| 0x0e | — | ScrCmd_setmysteryeventstatus |
| 0x0f | — | ScrCmd_loadword |
| 0x10 | — | ScrCmd_loadbyte |
| 0x11 | — | ScrCmd_setptr |
| 0x12 | — | ScrCmd_loadbytefromptr |
| 0x13 | — | ScrCmd_setptrbyte |
| 0x14 | — | ScrCmd_copylocal |
| 0x15 | — | ScrCmd_copybyte |
| 0x16 | — | ScrCmd_setvar |
| 0x17 | — | ScrCmd_addvar |
| 0x18 | — | ScrCmd_subvar |
| 0x19 | — | ScrCmd_copyvar |
| 0x1a | — | ScrCmd_setorcopyvar |
| 0x1b | — | ScrCmd_compare_local_to_local |
| 0x1c | — | ScrCmd_compare_local_to_value |
| 0x1d | — | ScrCmd_compare_local_to_ptr |
| 0x1e | — | ScrCmd_compare_ptr_to_local |
| 0x1f | — | ScrCmd_compare_ptr_to_value |
| 0x20 | — | ScrCmd_compare_ptr_to_ptr |
| 0x21 | — | ScrCmd_compare_var_to_value |
| 0x22 | — | ScrCmd_compare_var_to_var |
| 0x23 | — | ScrCmd_callnative |
| 0x24 | — | ScrCmd_gotonative |
| 0x25 | — | ScrCmd_special |
| 0x26 | — | ScrCmd_specialvar |
| 0x27 | — | ScrCmd_waitstate |
| 0x28 | — | ScrCmd_delay |
| 0x29 | — | ScrCmd_setflag |
| 0x2a | — | ScrCmd_clearflag |
| 0x2b | — | ScrCmd_checkflag |
| 0x2c | — | ScrCmd_initclock |
| 0x2d | — | ScrCmd_dotimebasedevents |
| 0x2e | — | ScrCmd_gettime |
| 0x2f | — | ScrCmd_playse |
| 0x30 | — | ScrCmd_waitse |
| 0x31 | — | ScrCmd_playfanfare |
| 0x32 | — | ScrCmd_waitfanfare |
| 0x33 | — | ScrCmd_playbgm |
| 0x34 | — | ScrCmd_savebgm |
| 0x35 | — | ScrCmd_fadedefaultbgm |
| 0x36 | — | ScrCmd_fadenewbgm |
| 0x37 | — | ScrCmd_fadeoutbgm |
| 0x38 | — | ScrCmd_fadeinbgm |
| 0x39 | — | ScrCmd_warp |
| 0x3a | — | ScrCmd_warpsilent |
| 0x3b | — | ScrCmd_warpdoor |
| 0x3c | — | ScrCmd_warphole |
| 0x3d | — | ScrCmd_warpteleport |
| 0x3e | — | ScrCmd_setwarp |
| 0x3f | — | ScrCmd_setdynamicwarp |
| 0x40 | — | ScrCmd_setdivewarp |
| 0x41 | — | ScrCmd_setholewarp |
| 0x42 | — | ScrCmd_getplayerxy |
| 0x43 | — | ScrCmd_getpartysize |
| 0x44 | — | ScrCmd_additem |
| 0x45 | — | ScrCmd_removeitem |
| 0x46 | — | ScrCmd_checkitemspace |
| 0x47 | — | ScrCmd_checkitem |
| 0x48 | — | ScrCmd_checkitemtype |
| 0x49 | — | ScrCmd_addpcitem |
| 0x4a | — | ScrCmd_checkpcitem |
| 0x4b | — | ScrCmd_adddecoration |
| 0x4c | — | ScrCmd_removedecoration |
| 0x4d | — | ScrCmd_checkdecor |
| 0x4e | — | ScrCmd_checkdecorspace |
| 0x4f | — | ScrCmd_applymovement |
| 0x50 | — | ScrCmd_applymovementat |
| 0x51 | — | ScrCmd_waitmovement |
| 0x52 | — | ScrCmd_waitmovementat |
| 0x53 | — | ScrCmd_removeobject |
| 0x54 | — | ScrCmd_removeobjectat |
| 0x55 | — | ScrCmd_addobject |
| 0x56 | — | ScrCmd_addobjectat |
| 0x57 | — | ScrCmd_setobjectxy |
| 0x58 | — | ScrCmd_showobjectat |
| 0x59 | — | ScrCmd_hideobjectat |
| 0x5a | — | ScrCmd_faceplayer |
| 0x5b | — | ScrCmd_turnobject |
| 0x5c | — | ScrCmd_trainerbattle |
| 0x5d | — | ScrCmd_dotrainerbattle |
| 0x5e | — | ScrCmd_gotopostbattlescript |
| 0x5f | — | ScrCmd_gotobeatenscript |
| 0x60 | — | ScrCmd_checktrainerflag |
| 0x61 | — | ScrCmd_settrainerflag |
| 0x62 | — | ScrCmd_cleartrainerflag |
| 0x63 | — | ScrCmd_setobjectxyperm |
| 0x64 | — | ScrCmd_copyobjectxytoperm |
| 0x65 | — | ScrCmd_setobjectmovementtype |
| 0x66 | — | ScrCmd_waitmessage |
| 0x67 | — | ScrCmd_message |
| 0x68 | — | ScrCmd_closemessage |
| 0x69 | — | ScrCmd_lockall |
| 0x6a | — | ScrCmd_lock |
| 0x6b | — | ScrCmd_releaseall |
| 0x6c | — | ScrCmd_release |
| 0x6d | — | ScrCmd_waitbuttonpress |
| 0x6e | — | ScrCmd_yesnobox |
| 0x6f | — | ScrCmd_multichoice |
| 0x70 | — | ScrCmd_multichoicedefault |
| 0x71 | — | ScrCmd_multichoicegrid |
| 0x72 | — | ScrCmd_drawbox |
| 0x73 | — | ScrCmd_erasebox |
| 0x74 | — | ScrCmd_drawboxtext |
| 0x75 | — | ScrCmd_showmonpic |
| 0x76 | — | ScrCmd_hidemonpic |
| 0x77 | — | ScrCmd_showcontestpainting |
| 0x78 | — | ScrCmd_braillemessage |
| 0x79 | — | ScrCmd_givemon |
| 0x7a | — | ScrCmd_giveegg |
| 0x7b | — | ScrCmd_setmonmove |
| 0x7c | — | ScrCmd_checkpartymove |
| 0x7d | — | ScrCmd_bufferspeciesname |
| 0x7e | — | ScrCmd_bufferleadmonspeciesname |
| 0x7f | — | ScrCmd_bufferpartymonnick |
| 0x80 | — | ScrCmd_bufferitemname |
| 0x81 | — | ScrCmd_bufferdecorationname |
| 0x82 | — | ScrCmd_buffermovename |
| 0x83 | — | ScrCmd_buffernumberstring |
| 0x84 | — | ScrCmd_bufferstdstring |
| 0x85 | — | ScrCmd_bufferstring |
| 0x86 | — | ScrCmd_pokemart |
| 0x87 | — | ScrCmd_pokemartdecoration |
| 0x88 | — | ScrCmd_pokemartdecoration2 |
| 0x89 | — | ScrCmd_playslotmachine |
| 0x8a | — | ScrCmd_setberrytree |
| 0x8b | — | ScrCmd_choosecontestmon |
| 0x8c | — | ScrCmd_startcontest |
| 0x8d | — | ScrCmd_showcontestresults |
| 0x8e | — | ScrCmd_contestlinktransfer |
| 0x8f | — | ScrCmd_random |
| 0x90 | — | ScrCmd_addmoney |
| 0x91 | — | ScrCmd_removemoney |
| 0x92 | — | ScrCmd_checkmoney |
| 0x93 | — | ScrCmd_showmoneybox |
| 0x94 | — | ScrCmd_hidemoneybox |
| 0x95 | — | ScrCmd_updatemoneybox |
| 0x96 | — | ScrCmd_getpokenewsactive |
| 0x97 | — | ScrCmd_fadescreen |
| 0x98 | — | ScrCmd_fadescreenspeed |
| 0x99 | — | ScrCmd_setflashlevel |
| 0x9a | — | ScrCmd_animateflash |
| 0x9b | — | ScrCmd_messageautoscroll |
| 0x9c | — | ScrCmd_dofieldeffect |
| 0x9d | — | ScrCmd_setfieldeffectargument |
| 0x9e | — | ScrCmd_waitfieldeffect |
| 0x9f | — | ScrCmd_setrespawn |
| 0xa0 | — | ScrCmd_checkplayergender |
| 0xa1 | — | ScrCmd_playmoncry |
| 0xa2 | — | ScrCmd_setmetatile |
| 0xa3 | — | ScrCmd_resetweather |
| 0xa4 | — | ScrCmd_setweather |
| 0xa5 | — | ScrCmd_doweather |
| 0xa6 | — | ScrCmd_setstepcallback |
| 0xa7 | — | ScrCmd_setmaplayoutindex |
| 0xa8 | — | ScrCmd_setobjectsubpriority |
| 0xa9 | — | ScrCmd_resetobjectsubpriority |
| 0xaa | — | ScrCmd_createvobject |
| 0xab | — | ScrCmd_turnvobject |
| 0xac | — | ScrCmd_opendoor |
| 0xad | — | ScrCmd_closedoor |
| 0xae | — | ScrCmd_waitdooranim |
| 0xaf | — | ScrCmd_setdooropen |
| 0xb0 | — | ScrCmd_setdoorclosed |
| 0xb1 | — | ScrCmd_addelevmenuitem |
| 0xb2 | — | ScrCmd_showelevmenu |
| 0xb3 | — | ScrCmd_checkcoins |
| 0xb4 | — | ScrCmd_addcoins |
| 0xb5 | — | ScrCmd_removecoins |
| 0xb6 | — | ScrCmd_setwildbattle |
| 0xb7 | — | ScrCmd_dowildbattle |
| 0xb8 | — | ScrCmd_setvaddress |
| 0xb9 | — | ScrCmd_vgoto |
| 0xba | — | ScrCmd_vcall |
| 0xbb | — | ScrCmd_vgoto_if |
| 0xbc | — | ScrCmd_vcall_if |
| 0xbd | — | ScrCmd_vmessage |
| 0xbe | — | ScrCmd_vbuffermessage |
| 0xbf | — | ScrCmd_vbufferstring |
| 0xc0 | — | ScrCmd_showcoinsbox |
| 0xc1 | — | ScrCmd_hidecoinsbox |
| 0xc2 | — | ScrCmd_updatecoinsbox |
| 0xc3 | — | ScrCmd_incrementgamestat |
| 0xc4 | — | ScrCmd_setescapewarp |
| 0xc5 | — | ScrCmd_waitmoncry |
| 0xc6 | — | ScrCmd_bufferboxname |
| 0xc7 | — | ScrCmd_textcolor |
| 0xc8 | — | ScrCmd_loadhelp |
| 0xc9 | — | ScrCmd_unloadhelp |
| 0xca | — | ScrCmd_signmsg |
| 0xcb | — | ScrCmd_normalmsg |
| 0xcc | — | ScrCmd_comparestat |
| 0xcd | — | ScrCmd_setmonmodernfatefulencounter |
| 0xce | — | ScrCmd_checkmonmodernfatefulencounter |
| 0xcf | — | ScrCmd_trywondercardscript |
| 0xd0 | — | ScrCmd_setworldmapflag |
| 0xd1 | — | ScrCmd_warpspinenter |
| 0xd2 | — | ScrCmd_setmonmetlocation |
| 0xd3 | — | ScrCmd_getbraillestringwidth |
| 0xd4 | — | ScrCmd_bufferitemnameplural |
| 0xd5 | — | ScrCmd_nop |

## Macros de script (`asm/macros/event.inc`)

Émeraude 270, Rouge Feu 257.

**RF seul** (✗ = absent de la fusion) :
trainerbattle_earlyrival, comparestat, setmonmodernfatefulencounter, checkmonmodernfatefulencounter,
getbraillestringwidth, putitemaway, msgreceiveditem, giveitem_msg, famechecker, set_gym_trainers,
goto_if_questlog, braillemessage_wait

**Émeraude seul** :
showplayer, hideplayer, pokemartlistend, comparehiddenvar, setmodernfatefulencounter,
checkmodernfatefulencounter, moverotatingtileobjects, turnrotatingtileobjects, initrotatingtilepuzzle,
freerotatingtilepuzzle, warpmossdeepgym, selectapproachingtrainer, lockfortrainer, closebraillemessage,
messageinstant, fadescreenswapbuffers, buffertrainerclassname, buffertrainername, pokenavcall, warpwhitefade,
buffercontestname, givedecoration, register_matchcall, dofieldeffectsparkle, braillemsgbox

## Macros de script de combat (`asm/macros/battle_script.inc`)

Émeraude 300, Rouge Feu 285.

**RF seul** (✗ = absent de la fusion) :
callterrainattack ✗, cureifburnedparalysedorpoisoned ✗, settypetoterrain ✗, pursuitrelated ✗,
getbattlersforrecall ✗, checkpokeflute, waitfanfare

**Émeraude seul** :
callenvironmentattack, cureifburnedparalyzedorpoisoned, settypetoenvironment, pursuitdoubles, trainerslideout,
palaceflavortext, arenajudgmentwindow, arenaopponentmonlost, arenaplayermonlost, arenabothmonlost,
forfeityesnobox, arenadrawreftextbox, arenaerasereftextbox, arenajudgmentstring, arenawaitmessage, waitcry,
volumedown, volumeup, setalreadystatusedmoveattempt, palacetryescapestatus, setoutcomeonteleport,
playtrainerdefeatbgm

## Macros de mouvement (`asm/macros/movement.inc`)

Émeraude 1, Rouge Feu 1.

**RF seul** (✗ = absent de la fusion) :
(aucun)

**Émeraude seul** :
(aucun)

## Scripts communs (`data/scripts/`)

**RF seul** :
aide.inc, bag_full.inc, fame_checker.inc, field_moves.inc, flavor_text.inc, hole.inc, itemfinder.inc,
mystery_event_club.inc, pokedex_rating.inc, pokemon_league.inc, pokemon_mansion.inc, route23.inc,
seagallop.inc, silphco_doors.inc, static_pokemon.inc, test.inc, trainer_card.inc, trainer_tower.inc,
trainers.inc, white_out.inc

**Émeraude seul** :
abnormal_weather.inc, apprentice.inc, battle_pike.inc, berry_blender.inc, berry_tree.inc, cave_hole.inc,
check_furniture.inc, contest_hall.inc, elite_four.inc, field_move_scripts.inc, field_poison.inc,
gabby_and_ty.inc, gift_altering_cave.inc, gift_aurora_ticket.inc, gift_battle_card.inc, gift_mystic_ticket.inc,
gift_old_sea_map.inc, gift_pichu.inc, gift_stamp_card.inc, gift_trainer.inc, interview.inc, kecleon.inc,
lilycove_lady.inc, mauville_man.inc, new_game.inc, players_house.inc, prof_birch.inc, profile_man.inc,
record_mix.inc, rival_graphics.inc, roulette.inc, secret_base.inc, secret_power_tm.inc, shared_secret_base.inc,
test_signpost.inc, trainer_hill.inc, trainer_script.inc, tv.inc

**Communs** :
cable_club.inc, cave_of_origin.inc, day_care.inc, flash.inc, hall_of_fame.inc, item_ball_scripts.inc,
move_tutors.inc, movement.inc, obtain_item.inc, pc.inc, pc_transfer.inc, pkmn_center_nurse.inc,
questionnaire.inc, repel.inc, safari_zone.inc, set_gym_trainers.inc, std_msgbox.inc, surf.inc,
trainer_battle.inc
