#ifndef GUARD_KANTO_TEACHY_TV_H
#define GUARD_KANTO_TEACHY_TV_H

// PokemonNative3G : Télé Pokémon de Rouge Feu (teachy_tv.h de RF), src/kanto_teachy_tv.c

enum TeachyTvScript
{
    TTVSCR_BATTLE,
    TTVSCR_STATUS,
    TTVSCR_MATCHUPS,
    TTVSCR_CATCHING,
    TTVSCR_TMS,
    TTVSCR_REGISTER
};

void InitTeachyTvController(u8 mode, void (*cb)(void));
void CB2_ReturnToTeachyTV(void);
void SetTeachyTvControllerModeToResume(void);

// Combats du Pokédude (src/kanto_battle_controller_pokedude.c) : BATTLE_TYPE_POKEDUDE de RF
extern bool8 gBattlePokedudeFrlg;
// Interface de combat de RF (option BOITES COMBAT = KANTO), toujours pour le Pokédude : sa voix off utilise ses tuiles
#define KANTO_BATTLE_UI (gSaveBlock2Ptr->optionsBattleUI || gBattlePokedudeFrlg)
struct PokedudeBattlerState
{
    u8 action_idx;
    u8 move_idx;
    u8 timer;
    u8 msg_idx;
    u8 saved_bg0y;
};
extern struct PokedudeBattlerState *gPokedudeBattlerStates[];
void SetControllerToPokedude(void);
void InitPokedudePartyAndOpponent(void);
void BtlCtrl_DrawVoiceoverMessageFrame(void);
void BtlCtrl_RemoveVoiceoverMessageFrame(void);
void Pokedude_OpenPartyMenuInBattle(void);    // party_menu.c
void Pokedude_ChooseMonForInBattleItem(void);
void InitPokedudeBag(u8 mode);                  // kanto_item_menu.c
void Pokedude_InitTMCase(void);                 // kanto_tm_case.c

#endif // GUARD_KANTO_TEACHY_TV_H
