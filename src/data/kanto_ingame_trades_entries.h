// Généré par tools/kanto/gen_script_menu.py — échanges en jeu de Rouge Feu (fin de sIngameTrades)
#define FIRERED
#define TEXT_INGAME_TRADE_NICKNAME_MR_MIME      _("MARCI")
#define TEXT_INGAME_TRADE_OTNAME_MR_MIME        _("NASSIM")
#define TEXT_INGAME_TRADE_NICKNAME_JYNX         _("LIPOUTI")
#define TEXT_INGAME_TRADE_OTNAME_JYNX           _("JOHAN")
#define TEXT_INGAME_TRADE_NICKNAME_NIDORAN_FR   _("MS. NIDO")
#define TEXT_INGAME_TRADE_NICKNAME_NIDORAN_LG   _("MR. NIDO")
#define TEXT_INGAME_TRADE_OTNAME_NIDORAN        _("FLORA")
#define TEXT_INGAME_TRADE_NICKNAME_FARFETCHD    _("PTICHO")
#define TEXT_INGAME_TRADE_OTNAME_FARFETCHD      _("ADELINE")
#define TEXT_INGAME_TRADE_NICKNAME_NIDORINOA_FR _("NINO")
#define TEXT_INGAME_TRADE_NICKNAME_NIDORINOA_LG _("NINO")
#define TEXT_INGAME_TRADE_OTNAME_NIDORINOA      _("ELIOTT")
#define TEXT_INGAME_TRADE_NICKNAME_LICKITUNG    _("GLAVIOTEUR")
#define TEXT_INGAME_TRADE_OTNAME_LICKITUNG      _("ISMAEL")
#define TEXT_INGAME_TRADE_NICKNAME_ELECTRODE    _("RODY")
#define TEXT_INGAME_TRADE_OTNAME_ELECTRODE      _("ALBAN")
#define TEXT_INGAME_TRADE_NICKNAME_TANGELA      _("TISSAC")
#define TEXT_INGAME_TRADE_OTNAME_TANGELA        _("PERRINE")
#define TEXT_INGAME_TRADE_NICKNAME_SEEL         _("OBAMI")
#define TEXT_INGAME_TRADE_OTNAME_SEEL           _("FELIX")

    [KANTO_INGAME_TRADE_MR_MIME] = 
    {
        .nickname = TEXT_INGAME_TRADE_NICKNAME_MR_MIME,
        .species = SPECIES_MR_MIME,
        .ivs = {20, 15, 17, 24, 23, 22},
        .abilityNum = 0,
        .otId = 1985,
        .conditions = {5, 5, 5, 30, 5},
        .personality = 0x00009cae,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_MR_MIME,
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_ABRA
    }, 
    [KANTO_INGAME_TRADE_JYNX] = 
    {
        .nickname = TEXT_INGAME_TRADE_NICKNAME_JYNX,
        .species = SPECIES_JYNX,
        .ivs = {18, 17, 18, 22, 25, 21},
        .abilityNum = 0,
        .otId = 36728,
        .conditions = {5, 30, 5, 5, 5},
        .personality = 0x498a2e1d,
        .heldItem = ITEM_FAB_MAIL,
        .mailNum = 1,
        .otName = TEXT_INGAME_TRADE_OTNAME_JYNX,
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_POLIWHIRL
    }, 
    [KANTO_INGAME_TRADE_NIDORAN] = 
    {
#if defined(FIRERED)
        .nickname = TEXT_INGAME_TRADE_NICKNAME_NIDORAN_FR,
        .species = SPECIES_NIDORAN_F,
        .ivs = {22, 18, 25, 19, 15, 22},
        .abilityNum = 0,
        .otId = 63184,
        .conditions = {5, 5, 5, 5, 30},
        .personality = 0x4c970b89,
        .heldItem = ITEM_TINY_MUSHROOM,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_NIDORAN,
        .otGender = FEMALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_NIDORAN_M
#elif defined(LEAFGREEN)
        .nickname = TEXT_INGAME_TRADE_NICKNAME_NIDORAN_LG,
        .species = SPECIES_NIDORAN_M,
        .ivs = {19, 25, 18, 22, 22, 15},
        .abilityNum = 0,
        .otId = 63184,
        .conditions = {30, 5, 5, 5, 5},
        .personality = 0x4c970b9e,
        .heldItem = ITEM_TINY_MUSHROOM,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_NIDORAN,
        .otGender = FEMALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_NIDORAN_F
#endif
    }, 
    [KANTO_INGAME_TRADE_FARFETCHD] = 
    {
        .nickname = TEXT_INGAME_TRADE_NICKNAME_FARFETCHD,
        .species = SPECIES_FARFETCHD,
        .ivs = {20, 25, 21, 24, 15, 20},
        .abilityNum = 0,
        .otId = 8810,
        .conditions = {30, 5, 5, 5, 5},
        .personality = 0x151943d7,
        .heldItem = ITEM_STICK,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_FARFETCHD,
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_SPEAROW
    }, 
    [KANTO_INGAME_TRADE_NIDORINOA] = 
    {
#if defined(FIRERED)
        .nickname = TEXT_INGAME_TRADE_NICKNAME_NIDORINOA_FR,
        .species = SPECIES_NIDORINA,
        .ivs = {22, 25, 18, 19, 22, 15},
        .abilityNum = 0,
        .otId = 13637,
        .conditions = {5, 5, 30, 5, 5},
        .personality = 0x00eeca15,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_NIDORINOA,
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_NIDORINO
#elif defined(LEAFGREEN)
        .nickname = TEXT_INGAME_TRADE_NICKNAME_NIDORINOA_LG,
        .species = SPECIES_NIDORINO,
        .ivs = {19, 18, 25, 22, 15, 22},
        .abilityNum = 0,
        .otId = 13637,
        .conditions = {5, 5, 5, 5, 30},
        .personality = 0x00eeca19,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_NIDORINOA,
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_NIDORINA
#endif
    }, 
    [KANTO_INGAME_TRADE_LICKITUNG] = 
    {
        .nickname = TEXT_INGAME_TRADE_NICKNAME_LICKITUNG,
        .species = SPECIES_LICKITUNG,
        .ivs = {24, 19, 21, 15, 23, 21},
        .abilityNum = 0,
        .otId = 1239,
        .conditions = {5, 5, 5, 5, 30},
        .personality = 0x451308ab,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_LICKITUNG,
        .otGender = MALE,
        .sheen = 10,
#if defined(FIRERED)
        .requestedSpecies = SPECIES_GOLDUCK
#elif defined(LEAFGREEN)
        .requestedSpecies = SPECIES_SLOWBRO
#endif
    }, 
    [KANTO_INGAME_TRADE_ELECTRODE] = 
    {
        .nickname = TEXT_INGAME_TRADE_NICKNAME_ELECTRODE,
        .species = SPECIES_ELECTRODE,
        .ivs = {19, 16, 18, 25, 25, 19},
        .abilityNum = 1,
        .otId = 50298,
        .conditions = {30, 5, 5, 5, 5},
        .personality = 0x06341016,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_ELECTRODE,
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_RAICHU
    }, 
    [KANTO_INGAME_TRADE_TANGELA] = 
    {
        .nickname = TEXT_INGAME_TRADE_NICKNAME_TANGELA,
        .species = SPECIES_TANGELA,
        .ivs = {22, 17, 25, 16, 23, 20},
        .abilityNum = 0,
        .otId = 60042,
        .conditions = {5, 5, 30, 5, 5},
        .personality = 0x5c77ecfa,
        .heldItem = ITEM_STARDUST,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_TANGELA,
        .otGender = FEMALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_VENONAT
    },
    [KANTO_INGAME_TRADE_SEEL] = 
    {
        .nickname = TEXT_INGAME_TRADE_NICKNAME_SEEL,
        .species = SPECIES_SEEL,
        .ivs = {24, 15, 22, 16, 23, 22},
        .abilityNum = 0,
        .otId = 9853,
        .conditions = {5, 5, 5, 5, 30},
        .personality = 0x482cac89,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = TEXT_INGAME_TRADE_OTNAME_SEEL,
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_PONYTA
    },
#undef FIRERED
