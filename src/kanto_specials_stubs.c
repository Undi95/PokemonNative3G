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
u16 ShowEasyChatMessage(void) { KantoSpecialStub("ShowEasyChatMessage"); return 0; }
u16 BufferRandomHobbyOrLifestyleString(void) { KantoSpecialStub("BufferRandomHobbyOrLifestyleString"); return 0; }
u16 ShowBattleRecords(void) { KantoSpecialStub("ShowBattleRecords"); return 0; }
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
u16 ShowDiploma(void) { KantoSpecialStub("ShowDiploma"); return 0; }
u16 Dummy_TryEnableBravoTrainerBattleTower(void) { KantoSpecialStub("Dummy_TryEnableBravoTrainerBattleTower"); return 0; }
u16 DoPicboxCancel(void) { KantoSpecialStub("DoPicboxCancel"); return 0; }
u16 DoSeagallopFerryScene(void) { KantoSpecialStub("DoSeagallopFerryScene"); return 0; }
u16 OpenMuseumFossilPic(void) { KantoSpecialStub("OpenMuseumFossilPic"); return 0; }
u16 CloseMuseumFossilPic(void) { KantoSpecialStub("CloseMuseumFossilPic"); return 0; }
u16 DoSSAnneDepartureCutscene(void) { KantoSpecialStub("DoSSAnneDepartureCutscene"); return 0; }
u16 CallTrainerTowerFunc(void) { KantoSpecialStub("CallTrainerTowerFunc"); return 0; }
u16 DoPokemonLeagueLightingEffect(void) { KantoSpecialStub("DoPokemonLeagueLightingEffect"); return 0; }

u16 DrawSeagallopDestinationMenu(void) { KantoSpecialStub("DrawSeagallopDestinationMenu"); return 0; }
u16 GetSelectedSeagallopDestination(void) { KantoSpecialStub("GetSelectedSeagallopDestination"); return 0; }
u16 DoDeoxysTriangleInteraction(void) { KantoSpecialStub("DoDeoxysTriangleInteraction"); return 0; }
u16 SetDeoxysTrianglePalette(void) { KantoSpecialStub("SetDeoxysTrianglePalette"); return 0; }
u16 ReadTrainerTowerAndValidate(void) { KantoSpecialStub("ReadTrainerTowerAndValidate"); return 0; }
u16 BrailleCursorToggle(void) { KantoSpecialStub("BrailleCursorToggle"); return 0; }
u16 AnimateTeleporterHousing(void) { KantoSpecialStub("AnimateTeleporterHousing"); return 0; }
u16 AnimateTeleporterCable(void) { KantoSpecialStub("AnimateTeleporterCable"); return 0; }
