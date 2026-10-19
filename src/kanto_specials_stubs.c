// Généré par tools/kanto/import_scripts.py — PROVISOIRE : specials de Rouge Feu
// pas encore portés. Chaque appel est signalé dans la console.
#include "global.h"

#ifdef PORTABLE
#include <stdio.h>
static void KantoSpecialStub(const char *name) { fprintf(stderr, "[Kanto] special RF non porte : %s\n", name); }
#else
static void KantoSpecialStub(const char *name) { }
#endif

u16 EnterColosseumPlayerSpot(void) { KantoSpecialStub("EnterColosseumPlayerSpot"); return 0; }
u16 EnterTradeSeat(void) { KantoSpecialStub("EnterTradeSeat"); return 0; }
u16 StartWiredCableClubTrade(void) { KantoSpecialStub("StartWiredCableClubTrade"); return 0; }
u16 CableClub_AskSaveTheGame(void) { KantoSpecialStub("CableClub_AskSaveTheGame"); return 0; }
u16 TryContestLinkup(void) { KantoSpecialStub("TryContestLinkup"); return 0; }
u16 Field_AskSaveTheGame(void) { KantoSpecialStub("Field_AskSaveTheGame"); return 0; }
u16 ShowEasyChatMessage(void) { KantoSpecialStub("ShowEasyChatMessage"); return 0; }
u16 GetHeracrossSizeRecordInfo(void) { KantoSpecialStub("GetHeracrossSizeRecordInfo"); return 0; }
u16 CompareHeracrossSize(void) { KantoSpecialStub("CompareHeracrossSize"); return 0; }
u16 GetMagikarpSizeRecordInfo(void) { KantoSpecialStub("GetMagikarpSizeRecordInfo"); return 0; }
u16 CompareMagikarpSize(void) { KantoSpecialStub("CompareMagikarpSize"); return 0; }
u16 BufferRandomHobbyOrLifestyleString(void) { KantoSpecialStub("BufferRandomHobbyOrLifestyleString"); return 0; }
u16 RegisteredItemHandleBikeSwap(void) { KantoSpecialStub("RegisteredItemHandleBikeSwap"); return 0; }
u16 Script_IsFanClubMemberFanOfPlayer(void) { KantoSpecialStub("Script_IsFanClubMemberFanOfPlayer"); return 0; }
u16 Script_GetNumFansOfPlayerInTrainerFanClub(void) { KantoSpecialStub("Script_GetNumFansOfPlayerInTrainerFanClub"); return 0; }
u16 Script_BufferFanClubTrainerName(void) { KantoSpecialStub("Script_BufferFanClubTrainerName"); return 0; }
u16 Script_TryLoseFansFromPlayTimeAfterLinkBattle(void) { KantoSpecialStub("Script_TryLoseFansFromPlayTimeAfterLinkBattle"); return 0; }
u16 Script_TryLoseFansFromPlayTime(void) { KantoSpecialStub("Script_TryLoseFansFromPlayTime"); return 0; }
u16 Script_SetPlayerGotFirstFans(void) { KantoSpecialStub("Script_SetPlayerGotFirstFans"); return 0; }
u16 Script_UpdateTrainerFanClubGameClear(void) { KantoSpecialStub("Script_UpdateTrainerFanClubGameClear"); return 0; }
u16 ShowBattleRecords(void) { KantoSpecialStub("ShowBattleRecords"); return 0; }
u16 GetProfOaksRatingMessage(void) { KantoSpecialStub("GetProfOaksRatingMessage"); return 0; }
u16 GetElevatorFloor(void) { KantoSpecialStub("GetElevatorFloor"); return 0; }
u16 SelectMoveDeleterMove(void) { KantoSpecialStub("SelectMoveDeleterMove"); return 0; }
u16 BattleTowerMapScript2(void) { KantoSpecialStub("BattleTowerMapScript2"); return 0; }
u16 ChooseNextBattleTowerTrainer(void) { KantoSpecialStub("ChooseNextBattleTowerTrainer"); return 0; }
u16 CheckPartyBattleTowerBanlist(void) { KantoSpecialStub("CheckPartyBattleTowerBanlist"); return 0; }
u16 PrintBattleTowerTrainerGreeting(void) { KantoSpecialStub("PrintBattleTowerTrainerGreeting"); return 0; }
u16 BufferEReaderTrainerGreeting(void) { KantoSpecialStub("BufferEReaderTrainerGreeting"); return 0; }
u16 StartSpecialBattle(void) { KantoSpecialStub("StartSpecialBattle"); return 0; }
u16 SetBattleTowerProperty(void) { KantoSpecialStub("SetBattleTowerProperty"); return 0; }
u16 BattleTowerUtil(void) { KantoSpecialStub("BattleTowerUtil"); return 0; }
u16 SetBattleTowerParty(void) { KantoSpecialStub("SetBattleTowerParty"); return 0; }
u16 SaveBattleTowerProgress(void) { KantoSpecialStub("SaveBattleTowerProgress"); return 0; }
u16 BattleTower_SoftReset(void) { KantoSpecialStub("BattleTower_SoftReset"); return 0; }
u16 DetermineBattleTowerPrize(void) { KantoSpecialStub("DetermineBattleTowerPrize"); return 0; }
u16 GiveBattleTowerPrize(void) { KantoSpecialStub("GiveBattleTowerPrize"); return 0; }
u16 AwardBattleTowerRibbons(void) { KantoSpecialStub("AwardBattleTowerRibbons"); return 0; }
u16 ChooseBattleTowerPlayerParty(void) { KantoSpecialStub("ChooseBattleTowerPlayerParty"); return 0; }
u16 ReducePlayerPartyToThree(void) { KantoSpecialStub("ReducePlayerPartyToThree"); return 0; }
u16 ShowTownMap(void) { KantoSpecialStub("ShowTownMap"); return 0; }
u16 CreatePCMenu(void) { KantoSpecialStub("CreatePCMenu"); return 0; }
u16 HallOfFamePCBeginFade(void) { KantoSpecialStub("HallOfFamePCBeginFade"); return 0; }
u16 ShowDiploma(void) { KantoSpecialStub("ShowDiploma"); return 0; }
u16 EnterHallOfFame(void) { KantoSpecialStub("EnterHallOfFame"); return 0; }
u16 AnimateElevator(void) { KantoSpecialStub("AnimateElevator"); return 0; }
u16 DrawElevatorCurrentFloorWindow(void) { KantoSpecialStub("DrawElevatorCurrentFloorWindow"); return 0; }
u16 SetIcefallCaveCrackedIceMetatiles(void) { KantoSpecialStub("SetIcefallCaveCrackedIceMetatiles"); return 0; }
u16 Dummy_TryEnableBravoTrainerBattleTower(void) { KantoSpecialStub("Dummy_TryEnableBravoTrainerBattleTower"); return 0; }
u16 SetPostgameFlags(void) { KantoSpecialStub("SetPostgameFlags"); return 0; }
u16 StartMarowakBattle(void) { KantoSpecialStub("StartMarowakBattle"); return 0; }
u16 ListMenu(void) { KantoSpecialStub("ListMenu"); return 0; }
u16 ReturnToListMenu(void) { KantoSpecialStub("ReturnToListMenu"); return 0; }
u16 DoPicboxCancel(void) { KantoSpecialStub("DoPicboxCancel"); return 0; }
u16 SeafoamIslandsB4F_CurrentDumpsPlayerOnLand(void) { KantoSpecialStub("SeafoamIslandsB4F_CurrentDumpsPlayerOnLand"); return 0; }
u16 CloseElevatorCurrentFloorWindow(void) { KantoSpecialStub("CloseElevatorCurrentFloorWindow"); return 0; }
u16 VsSeekerResetObjectMovementAfterChargeComplete(void) { KantoSpecialStub("VsSeekerResetObjectMovementAfterChargeComplete"); return 0; }
u16 SetWalkingIntoSignVars(void) { KantoSpecialStub("SetWalkingIntoSignVars"); return 0; }
u16 DisableMsgBoxWalkaway(void) { KantoSpecialStub("DisableMsgBoxWalkaway"); return 0; }
u16 VsSeekerFreezeObjectsAfterChargeComplete(void) { KantoSpecialStub("VsSeekerFreezeObjectsAfterChargeComplete"); return 0; }
u16 OverworldWhiteOutGetMoneyLoss(void) { KantoSpecialStub("OverworldWhiteOutGetMoneyLoss"); return 0; }
u16 DoSeagallopFerryScene(void) { KantoSpecialStub("DoSeagallopFerryScene"); return 0; }
u16 OpenMuseumFossilPic(void) { KantoSpecialStub("OpenMuseumFossilPic"); return 0; }
u16 CloseMuseumFossilPic(void) { KantoSpecialStub("CloseMuseumFossilPic"); return 0; }
u16 DoSSAnneDepartureCutscene(void) { KantoSpecialStub("DoSSAnneDepartureCutscene"); return 0; }
u16 CallTrainerTowerFunc(void) { KantoSpecialStub("CallTrainerTowerFunc"); return 0; }
u16 Script_HasEnoughBerryPowder(void) { KantoSpecialStub("Script_HasEnoughBerryPowder"); return 0; }
u16 Script_TakeBerryPowder(void) { KantoSpecialStub("Script_TakeBerryPowder"); return 0; }
u16 DoPokemonLeagueLightingEffect(void) { KantoSpecialStub("DoPokemonLeagueLightingEffect"); return 0; }
u16 DoCredits(void) { KantoSpecialStub("DoCredits"); return 0; }
u16 DrawSeagallopDestinationMenu(void) { KantoSpecialStub("DrawSeagallopDestinationMenu"); return 0; }
u16 GetSelectedSeagallopDestination(void) { KantoSpecialStub("GetSelectedSeagallopDestination"); return 0; }
u16 GetSeagallopNumber(void) { KantoSpecialStub("GetSeagallopNumber"); return 0; }
u16 DoDeoxysTriangleInteraction(void) { KantoSpecialStub("DoDeoxysTriangleInteraction"); return 0; }
u16 SetDeoxysTrianglePalette(void) { KantoSpecialStub("SetDeoxysTrianglePalette"); return 0; }
u16 IsPlayerLeftOfVermilionSailor(void) { KantoSpecialStub("IsPlayerLeftOfVermilionSailor"); return 0; }
u16 ReadTrainerTowerAndValidate(void) { KantoSpecialStub("ReadTrainerTowerAndValidate"); return 0; }
u16 BrailleCursorToggle(void) { KantoSpecialStub("BrailleCursorToggle"); return 0; }
u16 AnimateTeleporterHousing(void) { KantoSpecialStub("AnimateTeleporterHousing"); return 0; }
u16 AnimateTeleporterCable(void) { KantoSpecialStub("AnimateTeleporterCable"); return 0; }
u16 InitElevatorFloorSelectMenuPos(void) { KantoSpecialStub("InitElevatorFloorSelectMenuPos"); return 0; }
