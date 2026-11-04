// Généré par tools/kanto/gen_objects.py depuis src/data/object_events/ de Rouge Feu.
// Ne pas modifier à la main.

#define ANIM_VS_SEEKER 0
#define ANIM_RAISE_HAND 20
#define ANIM_SPIN_SOUTH 24
#define ANIM_SPIN_NORTH 25
#define ANIM_SPIN_WEST 26
#define ANIM_SPIN_EAST 27
#define ANIM_SHAKE_HEAD_OR_WALK_IN_PLACE 28

// ---- base_oam.h ----
const struct OamData gKantoObjectEventBaseOam_8x8 = {
    .shape = SPRITE_SHAPE(8x8),
    .size = SPRITE_SIZE(8x8),
    .priority = 2
};

const struct OamData gKantoObjectEventBaseOam_16x8 = {
    .shape = SPRITE_SHAPE(16x8),
    .size = SPRITE_SIZE(16x8),
    .priority = 2
};

const struct OamData gKantoObjectEventBaseOam_16x16 = {
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 2
};

const struct OamData gKantoObjectEventBaseOam_32x16 = {
    .shape = SPRITE_SHAPE(32x16),
    .size = SPRITE_SIZE(32x16),
    .priority = 2
};

const struct OamData gKantoObjectEventBaseOam_32x8 = {
    .shape = SPRITE_SHAPE(32x8),
    .size = SPRITE_SIZE(32x8),
    .priority = 2
};

const struct OamData gKantoObjectEventBaseOam_64x32 = {
    .shape = SPRITE_SHAPE(64x32),
    .size = SPRITE_SIZE(64x32),
    .priority = 2
};

const struct OamData gKantoObjectEventBaseOam_16x32 = {
    .shape = SPRITE_SHAPE(16x32),
    .size = SPRITE_SIZE(16x32),
    .priority = 2
};

const struct OamData gKantoObjectEventBaseOam_32x32 = {
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 2
};

const struct OamData gKantoObjectEventBaseOam_64x64 = {
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 2
};


// ---- object_event_graphics.h ----
const u16 gKantoObjectEventPal_Player[] = INCGFX_U16("graphics/kanto/object_events/palettes/player.pal", ".gbapal");
const u16 gKantoObjectEventPal_PlayerUnused[] = INCGFX_U16("graphics/kanto/object_events/palettes/player_unused.pal", ".gbapal"); // Identical except for the transparency
const u16 gKantoObjectEventPaletteNull1[16] = {};
const u16 gKantoObjectEventPaletteNull2[16] = {};
const u16 gKantoObjectEventPaletteNull3[16] = {};
const u16 gKantoObjectEventPaletteNull4[16] = {};
const u16 gKantoObjectEventPaletteNull5[16] = {};
const u16 gKantoObjectEventPaletteNull6[16] = {};
const u16 gKantoObjectEventPaletteNull7[16] = {};
const u16 gKantoObjectEventPaletteNull8[16] = {};
const u16 gKantoObjectEventPaletteNull9[16] = {};
const u16 gKantoObjectEventPaletteNull10[16] = {};
const u16 gKantoObjectEventPaletteNull11[16] = {};
const u16 gKantoObjectEventPaletteNull12[16] = {};
const u16 gKantoObjectEventPaletteNull13[16] = {};
const u16 gKantoObjectEventPaletteNull14[16] = {};
const u16 gKantoObjectEventPic_RedNormal[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_normal.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_RedSurfRun[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_surf_run.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_GreenNormal[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_normal.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_GreenSurfRun[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_surf_run.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPal_PlayerReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/player_reflection.pal", ".gbapal");
const u16 gKantoObjectEventPal_BridgeReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/bridge_reflection.pal", ".gbapal");
const u16 gKantoObjectEventPic_RedItem[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_item.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_GreenItem[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_item.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_RedSurf[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_surf.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_GreenSurf[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_surf.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_RedBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_RedVSSeekerBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_vs_seeker_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_GreenBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_GreenVSSeekerBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_vs_seeker_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_RSBrendan[] = INCGFX_U16("graphics/kanto/object_events/pics/people/rs_brendan.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_RSMay[] = INCGFX_U16("graphics/kanto/object_events/pics/people/rs_may.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_RedFish[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_fish.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_GreenFish[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_fish.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_Pokedex[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/pokedex.png", ".4bpp");
const u16 gKantoObjectEventPic_TownMap[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/town_map.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_UnusedMan[] = INCGFX_U16("graphics/kanto/object_events/pics/people/unused_man.png", ".4bpp", "-mwidth 2 -mheight 4"); // Unused
const u16 gKantoObjectEventPic_Giovanni[] = INCGFX_U16("graphics/kanto/object_events/pics/people/giovanni.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Blaine[] = INCGFX_U16("graphics/kanto/object_events/pics/people/blaine.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Sabrina[] = INCGFX_U16("graphics/kanto/object_events/pics/people/sabrina.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Daisy[] = INCGFX_U16("graphics/kanto/object_events/pics/people/daisy.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Lorelei[] = INCGFX_U16("graphics/kanto/object_events/pics/people/lorelei.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Erika[] = INCGFX_U16("graphics/kanto/object_events/pics/people/erika.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Koga[] = INCGFX_U16("graphics/kanto/object_events/pics/people/koga.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Brock[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brock.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_LtSurge[] = INCGFX_U16("graphics/kanto/object_events/pics/people/lt_surge.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Bill[] = INCGFX_U16("graphics/kanto/object_events/pics/people/bill.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPal_NpcBlue[] = INCGFX_U16("graphics/kanto/object_events/palettes/npc_blue.pal", ".gbapal");
const u16 gKantoObjectEventPal_NpcPink[] = INCGFX_U16("graphics/kanto/object_events/palettes/npc_pink.pal", ".gbapal");
const u16 gKantoObjectEventPal_NpcGreen[] = INCGFX_U16("graphics/kanto/object_events/palettes/npc_green.pal", ".gbapal");
const u16 gKantoObjectEventPal_NpcWhite[] = INCGFX_U16("graphics/kanto/object_events/palettes/npc_white.pal", ".gbapal");
const u16 gKantoObjectEventPal_NpcBlueReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/npc_blue_reflection.pal", ".gbapal");
const u16 gKantoObjectEventPal_NpcPinkReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/npc_pink_reflection.pal", ".gbapal");
const u16 gKantoObjectEventPal_NpcGreenReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/npc_green_reflection.pal", ".gbapal");
const u16 gKantoObjectEventPal_NpcWhiteReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/npc_white_reflection.pal", ".gbapal");
const u16 gKantoObjectEventPic_LittleBoy[] = INCGFX_U16("graphics/kanto/object_events/pics/people/little_boy.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_LittleGirl[] = INCGFX_U16("graphics/kanto/object_events/pics/people/little_girl.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_SittingBoy[] = INCGFX_U16("graphics/kanto/object_events/pics/people/sitting_boy.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Lass[] = INCGFX_U16("graphics/kanto/object_events/pics/people/lass.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Youngster[] = INCGFX_U16("graphics/kanto/object_events/pics/people/youngster.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Boy[] = INCGFX_U16("graphics/kanto/object_events/pics/people/boy.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Woman1[] = INCGFX_U16("graphics/kanto/object_events/pics/people/woman_1.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Woman3[] = INCGFX_U16("graphics/kanto/object_events/pics/people/woman_3.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_BugCatcher[] = INCGFX_U16("graphics/kanto/object_events/pics/people/bug_catcher.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_CrushGirl[] = INCGFX_U16("graphics/kanto/object_events/pics/people/crush_girl.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_RichBoy[] = INCGFX_U16("graphics/kanto/object_events/pics/people/rich_boy.png", ".4bpp", "-mwidth 2 -mheight 4"); // Unused
const u16 gKantoObjectEventPic_FatMan[] = INCGFX_U16("graphics/kanto/object_events/pics/people/fat_man.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_BaldingMan[] = INCGFX_U16("graphics/kanto/object_events/pics/people/balding_man.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Woman2[] = INCGFX_U16("graphics/kanto/object_events/pics/people/woman_2.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_OldMan1[] = INCGFX_U16("graphics/kanto/object_events/pics/people/old_man_1.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_OldManLyingDown[] = INCGFX_U16("graphics/kanto/object_events/pics/people/old_man_lying_down.png", ".4bpp");
const u16 gKantoObjectEventPic_WorkerM[] = INCGFX_U16("graphics/kanto/object_events/pics/people/worker_m.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_WorkerF[] = INCGFX_U16("graphics/kanto/object_events/pics/people/worker_f.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Beauty[] = INCGFX_U16("graphics/kanto/object_events/pics/people/beauty.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Chef[] = INCGFX_U16("graphics/kanto/object_events/pics/people/chef.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_OldMan2[] = INCGFX_U16("graphics/kanto/object_events/pics/people/old_man_2.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_OldWoman[] = INCGFX_U16("graphics/kanto/object_events/pics/people/old_woman.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Camper[] = INCGFX_U16("graphics/kanto/object_events/pics/people/camper.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Picnicker[] = INCGFX_U16("graphics/kanto/object_events/pics/people/picnicker.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_CooltrainerM[] = INCGFX_U16("graphics/kanto/object_events/pics/people/cooltrainer_m.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_CooltrainerF[] = INCGFX_U16("graphics/kanto/object_events/pics/people/cooltrainer_f.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Psyduck[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/psyduck.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_PokeManiac[] = INCGFX_U16("graphics/kanto/object_events/pics/people/poke_maniac.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Channeler[] = INCGFX_U16("graphics/kanto/object_events/pics/people/channeler.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_RocketF[] = INCGFX_U16("graphics/kanto/object_events/pics/people/rocket_f.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_SwimmerMWater[] = INCGFX_U16("graphics/kanto/object_events/pics/people/swimmer_m_water.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_SwimmerFWater[] = INCGFX_U16("graphics/kanto/object_events/pics/people/swimmer_f_water.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_SwimmerMLand[] = INCGFX_U16("graphics/kanto/object_events/pics/people/swimmer_m_land.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_SwimmerFLand[] = INCGFX_U16("graphics/kanto/object_events/pics/people/swimmer_f_land.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_BlackBelt[] = INCGFX_U16("graphics/kanto/object_events/pics/people/black_belt.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Scientist[] = INCGFX_U16("graphics/kanto/object_events/pics/people/scientist.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Gentleman[] = INCGFX_U16("graphics/kanto/object_events/pics/people/gentleman.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Sailor[] = INCGFX_U16("graphics/kanto/object_events/pics/people/sailor.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Captain[] = INCGFX_U16("graphics/kanto/object_events/pics/people/captain.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Fisher[] = INCGFX_U16("graphics/kanto/object_events/pics/people/fisher.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_TeachyTVHost[] = INCGFX_U16("graphics/kanto/object_events/pics/people/teachy_tv_host.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_UnusedWoman[] = INCGFX_U16("graphics/kanto/object_events/pics/people/unused_woman.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_TuberF[] = INCGFX_U16("graphics/kanto/object_events/pics/people/tuber_f.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_TuberMWater[] = INCGFX_U16("graphics/kanto/object_events/pics/people/tuber_m_water.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_TuberMLand[] = INCGFX_U16("graphics/kanto/object_events/pics/people/tuber_m_land.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Hiker[] = INCGFX_U16("graphics/kanto/object_events/pics/people/hiker.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Biker[] = INCGFX_U16("graphics/kanto/object_events/pics/people/biker.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_GymGuy[] = INCGFX_U16("graphics/kanto/object_events/pics/people/gym_guy.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Man[] = INCGFX_U16("graphics/kanto/object_events/pics/people/man.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Rocker[] = INCGFX_U16("graphics/kanto/object_events/pics/people/rocker.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_ProfOak[] = INCGFX_U16("graphics/kanto/object_events/pics/people/prof_oak.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Blue[] = INCGFX_U16("graphics/kanto/object_events/pics/people/blue.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Nurse[] = INCGFX_U16("graphics/kanto/object_events/pics/people/nurse.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_CableClubReceptionist[] = INCGFX_U16("graphics/kanto/object_events/pics/people/cable_club_receptionist.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_UnionRoomReceptionist[] = INCGFX_U16("graphics/kanto/object_events/pics/people/union_room_receptionist.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_UnusedMaleReceptionist[] = INCGFX_U16("graphics/kanto/object_events/pics/people/unused_male_receptionist.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_ItemBall[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/item_ball.png", ".4bpp");
const u16 gKantoObjectEventPic_MrFuji[] = INCGFX_U16("graphics/kanto/object_events/pics/people/mr_fuji.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Bruno[] = INCGFX_U16("graphics/kanto/object_events/pics/people/bruno.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Clerk[] = INCGFX_U16("graphics/kanto/object_events/pics/people/clerk.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_MGDeliveryman[] = INCGFX_U16("graphics/kanto/object_events/pics/people/mg_deliveryman.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_TrainerTowerDude[] = INCGFX_U16("graphics/kanto/object_events/pics/people/trainer_tower_dude.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Cameraman[] = INCGFX_U16("graphics/kanto/object_events/pics/people/cameraman.png", ".4bpp", "-mwidth 2 -mheight 4"); // Unused
const u16 gKantoObjectEventPic_RocketM[] = INCGFX_U16("graphics/kanto/object_events/pics/people/rocket_m.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Celio[] = INCGFX_U16("graphics/kanto/object_events/pics/people/celio.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Lapras[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/lapras.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Zapdos[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/zapdos.png", ".4bpp");
const u16 gKantoObjectEventPic_Moltres[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/moltres.png", ".4bpp");
const u16 gKantoObjectEventPic_Articuno[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/articuno.png", ".4bpp");
const u16 gKantoObjectEventPic_Mewtwo[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/mewtwo.png", ".4bpp");
const u16 gKantoObjectEventPic_Mew[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/mew.png", ".4bpp");
const u16 gKantoObjectEventPic_Entei[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/entei.png", ".4bpp");
const u16 gKantoObjectEventPic_Raikou[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/raikou.png", ".4bpp");
const u16 gKantoObjectEventPic_Suicune[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/suicune.png", ".4bpp");
const u16 gKantoObjectEventPic_Lugia[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/lugia.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_HoOh[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/ho_oh.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_Celebi[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/celebi.png", ".4bpp");
const u16 gKantoObjectEventPic_DeoxysD[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/deoxys_d.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_DeoxysA[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/deoxys_a.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_DeoxysN[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/deoxys_n.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_Agatha[] = INCGFX_U16("graphics/kanto/object_events/pics/people/agatha.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Misty[] = INCGFX_U16("graphics/kanto/object_events/pics/people/misty.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Lance[] = INCGFX_U16("graphics/kanto/object_events/pics/people/lance.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_GBAKid[] = INCGFX_U16("graphics/kanto/object_events/pics/people/gba_kid.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Mom[] = INCGFX_U16("graphics/kanto/object_events/pics/people/mom.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_Pidgeot[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/pidgeot.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Omanyte[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/omanyte.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Kangaskhan[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/kangaskhan.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_NidoranF[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/nidoran_f.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_NidoranM[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/nidoran_m.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Nidorino[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/nidorino.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Meowth[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/meowth.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Seel[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/seel.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Voltorb[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/voltorb.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Slowpoke[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/slowpoke.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Slowbro[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/slowbro.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Machop[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/machop.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Wigglytuff[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/wigglytuff.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Doduo[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/doduo.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Fearow[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/fearow.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Kabuto[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/kabuto.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Machoke[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/machoke.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Snorlax[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/snorlax.png", ".4bpp");
const u16 gKantoObjectEventPic_Spearow[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/spearow.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Cubone[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/cubone.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Poliwrath[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/poliwrath.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Chansey[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/chansey.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Pikachu[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/pikachu.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Jigglypuff[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/jigglypuff.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Pidgey[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/pidgey.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_Clefairy[] = INCGFX_U16("graphics/kanto/object_events/pics/pokemon/clefairy.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_CutTree[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/cut_tree.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_RockSmashRock[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/rock_smash_rock.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoObjectEventPic_StrengthBoulder[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/strength_boulder.png", ".4bpp");
const u16 gKantoObjectEventPic_Fossil[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/fossil.png", ".4bpp");
const u16 gKantoObjectEventPic_Ruby[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/ruby.png", ".4bpp");
const u16 gKantoObjectEventPic_Sapphire[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/sapphire.png", ".4bpp");
const u16 gKantoObjectEventPic_OldAmber[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/old_amber.png", ".4bpp");
const u16 gKantoObjectEventPic_GymSign[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/gym_sign.png", ".4bpp");
const u16 gKantoObjectEventPic_Sign[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/sign.png", ".4bpp");
const u16 gKantoObjectEventPic_WoodenSign[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/wooden_sign.png", ".4bpp");
const u16 gKantoObjectEventPic_Clipboard[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/clipboard.png", ".4bpp");
const u16 gKantoObjectEventPal_Meteorite[] = INCGFX_U16("graphics/kanto/object_events/palettes/meteorite.pal", ".gbapal");
const u16 gKantoObjectEventPic_BirthIslandStone[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/birth_island_stone.png", ".4bpp");
const u16 gKantoObjectEventPic_LaprasDoll[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/lapras_doll.png", ".4bpp");
const u16 gKantoObjectEventPal_Seagallop[] = INCGFX_U16("graphics/kanto/object_events/palettes/seagallop.pal", ".gbapal");
const u16 gKantoObjectEventPic_Seagallop[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/seagallop.png", ".4bpp");
const u16 gKantoObjectEventPal_SSAnne[] = INCGFX_U16("graphics/kanto/object_events/palettes/ss_anne.pal", ".gbapal");
const u16 gKantoObjectEventPic_SSAnne[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/ss_anne.png", ".4bpp", "-mwidth 8 -mheight 4");
const u16 gKantoObjectEventPic_SurfBlob[] = INCGFX_U16("graphics/kanto/object_events/pics/misc/surf_blob.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_Policeman[] = INCGFX_U16("graphics/kanto/object_events/pics/people/policeman.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPal_RSQuintyPlump[] = INCGFX_U16("graphics/kanto/object_events/palettes/rs_quinty_plump.pal", ".gbapal");
const u16 gKantoObjectEventPal_RSQuintyPlumpReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/rs_quinty_plump_reflection.pal", ".gbapal");
const u16 gKantoFieldEffectObjectPic_ShadowSmall[] = INCGFX_U16("graphics/kanto/field_effects/pics/shadow_small.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_ShadowMedium[] = INCGFX_U16("graphics/kanto/field_effects/pics/shadow_medium.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_ShadowLarge[] = INCGFX_U16("graphics/kanto/field_effects/pics/shadow_large.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_ShadowExtraLarge[] = INCGFX_U16("graphics/kanto/field_effects/pics/shadow_extra_large.png", ".4bpp");
const u16 sKantoFiller1[0x90] = {};
const u16 gKantoFieldEffectObjectPic_CutGrass[] = INCGFX_U16("graphics/kanto/field_effects/fldeff_cut.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_CutGrass2[] = INCGFX_U16("graphics/kanto/field_effects/fldeff_cut.png", ".4bpp"); // Unused
const u16 gKantoFieldEffectPal_CutGrass[] = INCGFX_U16("graphics/kanto/field_effects/fldeff_cut.png", ".gbapal");
const u16 gKantoFieldEffectObjectPic_Ripple[] = INCGFX_U16("graphics/kanto/field_effects/pics/ripple.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_Ash[] = INCGFX_U16("graphics/kanto/field_effects/pics/ash.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_Arrow[] = INCGFX_U16("graphics/kanto/field_effects/pics/arrow.png", ".4bpp");
const u16 gKantoFieldEffectObjectPalette0[] = INCGFX_U16("graphics/kanto/field_effects/palettes/general_0.pal", ".gbapal");
const u16 gKantoFieldEffectObjectPalette1[] = INCGFX_U16("graphics/kanto/field_effects/palettes/general_1.pal", ".gbapal");
const u16 sKantoFiller2[0x10] = {};
const u16 gKantoFieldEffectObjectPic_GroundImpactDust[] = INCGFX_U16("graphics/kanto/field_effects/pics/ground_impact_dust.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_UnusedGrass3[] = INCGFX_U16("graphics/kanto/field_effects/pics/unused_grass_3.png", ".4bpp"); // Unused
const u16 gKantoFieldEffectObjectPic_JumpTallGrass[] = INCGFX_U16("graphics/kanto/field_effects/pics/jump_tall_grass.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_UnusedGrass4[] = INCGFX_U16("graphics/kanto/field_effects/pics/unused_grass_4.png", ".4bpp"); // Unused
const u16 gKantoFieldEffectObjectPic_JumpLongGrass[] = INCGFX_U16("graphics/kanto/field_effects/pics/jump_long_grass.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_UnusedGrass[] = INCGFX_U16("graphics/kanto/field_effects/pics/unused_grass.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_UnusedGrass2[] = INCGFX_U16("graphics/kanto/field_effects/pics/unused_grass_2.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_LongGrass[] = INCGFX_U16("graphics/kanto/field_effects/pics/long_grass.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_TallGrass[] = INCGFX_U16("graphics/kanto/field_effects/pics/tall_grass.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_ShortGrass[] = INCGFX_U16("graphics/kanto/field_effects/pics/short_grass.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_SandFootprints[] = INCGFX_U16("graphics/kanto/field_effects/pics/sand_footprints.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_DeepSandFootprints[] = INCGFX_U16("graphics/kanto/field_effects/pics/deep_sand_footprints.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_BikeTireTracks[] = INCGFX_U16("graphics/kanto/field_effects/pics/bike_tire_tracks.png", ".4bpp", "-mwidth 2 -mheight 2");
const u16 gKantoFieldEffectObjectPic_UnusedSand[] = INCGFX_U16("graphics/kanto/field_effects/pics/unused_sand.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_SandPile[] = INCGFX_U16("graphics/kanto/field_effects/pics/sand_pile.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_JumpBigSplash[] = INCGFX_U16("graphics/kanto/field_effects/pics/jump_big_splash.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_Splash[] = INCGFX_U16("graphics/kanto/field_effects/pics/splash.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_JumpSmallSplash[] = INCGFX_U16("graphics/kanto/field_effects/pics/jump_small_splash.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_WaterSurfacing[] = INCGFX_U16("graphics/kanto/field_effects/pics/water_surfacing.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_TreeDisguise[] = INCGFX_U16("graphics/kanto/field_effects/pics/tree_disguise.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoFieldEffectObjectPic_MountainDisguise[] = INCGFX_U16("graphics/kanto/field_effects/pics/mountain_disguise.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoFieldEffectObjectPic_SandDisguisePlaceholder[] = INCGFX_U16("graphics/kanto/field_effects/pics/sand_disguise.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoFieldEffectObjectPic_HotSpringsWater[] = INCGFX_U16("graphics/kanto/field_effects/pics/hot_springs_water.png", ".4bpp");
const u16 gKantoFieldEffectPal_Ash[] = INCGFX_U16("graphics/kanto/field_effects/palettes/ash.pal", ".gbapal");
const u16 gKantoFieldEffectObjectPic_AshPuff[] = INCGFX_U16("graphics/kanto/field_effects/pics/pop_out_of_ash.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_AshLaunch[] = INCGFX_U16("graphics/kanto/field_effects/pics/lavaridge_warp.png", ".4bpp");
const u16 gKantoFieldEffectObjectPic_Bubbles[] = INCGFX_U16("graphics/kanto/field_effects/pics/underwater_bubbles.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoFieldEffectObjectPic_SmallSparkle[] = INCGFX_U16("graphics/kanto/field_effects/pics/small_sparkle.png", ".4bpp");
const u16 gKantoFieldEffectPal_SmallSparkle[] = INCGFX_U16("graphics/kanto/field_effects/palettes/small_sparkle.pal", ".gbapal");
const u16 gKantoFieldEffectObjectPic_Bird[] = INCGFX_U16("graphics/kanto/field_effects/pics/bird.png", ".4bpp");


// ---- object_event_pic_tables.h ----
static const struct SpriteFrameImage sKantoPicTable_RedNormal[] = {
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_RedNormal, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 9),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 10),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 11),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 12),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 13),
};

static const struct SpriteFrameImage sKantoPicTable_RedBike[] = {
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_RedBike, 4, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_GreenNormal[] = {
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_GreenNormal, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 9),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 10),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 11),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 12),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 13),
};

static const struct SpriteFrameImage sKantoPicTable_GreenBike[] = {
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_GreenBike, 4, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_RedSurf[] = {
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedSurfRun, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_GreenSurf[] = {
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenSurfRun, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_RedItem[] = {
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_RedItem, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_GreenItem[] = {
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_GreenItem, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_RedVSSeekerBike[] = {
    overworld_frame(gKantoObjectEventPic_RedVSSeekerBike, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedVSSeekerBike, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedVSSeekerBike, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedVSSeekerBike, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedVSSeekerBike, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedVSSeekerBike, 4, 4, 5),
};

static const struct SpriteFrameImage sKantoPicTable_GreenVSSeekerBike[] = {
    overworld_frame(gKantoObjectEventPic_GreenVSSeekerBike, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenVSSeekerBike, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenVSSeekerBike, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenVSSeekerBike, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenVSSeekerBike, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenVSSeekerBike, 4, 4, 5),
};

static const struct SpriteFrameImage sKantoPicTable_RSBrendan[] = {
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_RSBrendan, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_RSMay[] = {
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_RSMay, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_RedFish, 2, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Policeman[] = {
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Policeman, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_LittleBoy[] = {
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 3),
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 4),
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 5),
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 6),
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 7),
    overworld_frame(gKantoObjectEventPic_LittleBoy, 2, 2, 8),
};

static const struct SpriteFrameImage sKantoPicTable_LittleGirl[] = {
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 3),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 4),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 5),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 6),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 7),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 8),
    overworld_frame(gKantoObjectEventPic_LittleGirl, 2, 2, 9),
};

static const struct SpriteFrameImage sKantoPicTable_SittingBoy[] = {
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_SittingBoy, 2, 4, 1),
};

static const struct SpriteFrameImage sKantoPicTable_Lass[] = {
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Lass, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Youngster[] = {
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Youngster, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Woman1[] = {
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Woman1, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Woman3[] = {
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Woman3, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_CrushGirl[] = {
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_CrushGirl, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_BugCatcher[] = {
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_BugCatcher, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_FatMan[] = {
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_FatMan, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_BaldingMan[] = {
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_BaldingMan, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Woman2[] = {
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Woman2, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_OldMan1[] = {
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_OldMan1, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_WorkerM[] = {
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_WorkerM, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_WorkerF[] = {
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_WorkerF, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Beauty[] = {
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Beauty, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Chef[] = {
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Chef, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_OldMan2[] = {
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_OldMan2, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_OldManLyingDown[] = {
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldManLyingDown, 4, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_OldWoman[] = {
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_OldWoman, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Camper[] = {
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Camper, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Picnicker[] = {
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Picnicker, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_CooltrainerM[] = {
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_CooltrainerM, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_CooltrainerF[] = {
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_CooltrainerF, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Boy[] = {
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Boy, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_PokeManiac[] = {
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_PokeManiac, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Channeler[] = {
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Channeler, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_RocketF[] = {
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_RocketF, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_SwimmerMWater[] = {
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_SwimmerMWater, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_SwimmerFWater[] = {
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_SwimmerFWater, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_SwimmerMLand[] = {
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_SwimmerMLand, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_SwimmerFLand[] = {
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_SwimmerFLand, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_BlackBelt[] = {
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_BlackBelt, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Scientist[] = {
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Scientist, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Gentleman[] = {
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Gentleman, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Sailor[] = {
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Sailor, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Captain[] = {
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Captain, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Fisher[] = {
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Fisher, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_TeachyTVHost[] = {
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_TeachyTVHost, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_UnusedWoman[] = {
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_UnusedWoman, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_TuberF[] = {
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 3),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 4),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 5),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 6),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 7),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 8),
    overworld_frame(gKantoObjectEventPic_TuberF, 2, 2, 9),
};

static const struct SpriteFrameImage sKantoPicTable_TuberMWater[] = {
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 3),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 4),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 5),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 6),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 7),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 8),
    overworld_frame(gKantoObjectEventPic_TuberMWater, 2, 2, 9),
};

static const struct SpriteFrameImage sKantoPicTable_TuberMLand[] = {
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 3),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 4),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 5),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 6),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 7),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 8),
    overworld_frame(gKantoObjectEventPic_TuberMLand, 2, 2, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Hiker[] = {
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Hiker, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Biker[] = {
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 8),
    overworld_frame(gKantoObjectEventPic_Biker, 4, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_GymGuy[] = {
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_GymGuy, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Nurse[] = {
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Nurse, 2, 4, 3),
};

static const struct SpriteFrameImage sKantoPicTable_UnusedMaleReceptionist[] = {
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_UnusedMaleReceptionist, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_ItemBall[] = {
    overworld_frame(gKantoObjectEventPic_ItemBall, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_ProfOak[] = {
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_ProfOak, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Man[] = {
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Man, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_Rocker[] = {
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 8),
    overworld_frame(gKantoObjectEventPic_Rocker, 2, 4, 9),
};

static const struct SpriteFrameImage sKantoPicTable_MrFuji[] = {
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_MrFuji, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Bruno[] = {
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Bruno, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_CutTree[] = {
    overworld_frame(gKantoObjectEventPic_CutTree, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_CutTree, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_CutTree, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_CutTree, 2, 2, 3),
};

static const struct SpriteFrameImage sKantoPicTable_Clerk[] = {
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Clerk, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_MGDeliveryman[] = {
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_MGDeliveryman, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_TrainerTowerDude[] = {
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_TrainerTowerDude, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_CableClubReceptionist[] = {
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_CableClubReceptionist, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_UnionRoomReceptionist[] = {
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_UnionRoomReceptionist, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_RockSmashRock[] = {
    overworld_frame(gKantoObjectEventPic_RockSmashRock, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_RockSmashRock, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_RockSmashRock, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_RockSmashRock, 2, 2, 3),
};

static const struct SpriteFrameImage sKantoPicTable_StrengthBoulder[] = {
    overworld_frame(gKantoObjectEventPic_StrengthBoulder, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_RocketM[] = {
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_RocketM, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Celio[] = {
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Celio, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Agatha[] = {
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Agatha, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Brock[] = {
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Brock, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Misty[] = {
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Misty, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_LtSurge[] = {
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_LtSurge, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Erika[] = {
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Erika, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Koga[] = {
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Koga, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Giovanni[] = {
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Giovanni, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Blaine[] = {
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Blaine, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Sabrina[] = {
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Sabrina, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Bill[] = {
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Bill, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Daisy[] = {
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Daisy, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Lorelei[] = {
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Lorelei, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_Lance[] = {
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Lance, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Blue[] = {
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 3),
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 4),
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 5),
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 6),
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 7),
    overworld_frame(gKantoObjectEventPic_Blue, 2, 4, 8),
};

static const struct SpriteFrameImage sKantoPicTable_RedFish[] = {
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 8),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 9),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 10),
    overworld_frame(gKantoObjectEventPic_RedFish, 4, 4, 11),
};

static const struct SpriteFrameImage sKantoPicTable_GreenFish[] = {
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 8),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 9),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 10),
    overworld_frame(gKantoObjectEventPic_GreenFish, 4, 4, 11),
};

static const struct SpriteFrameImage sKantoPicTable_TownMap[] = {
    overworld_frame(gKantoObjectEventPic_TownMap, 2, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Pokedex[] = {
    overworld_frame(gKantoObjectEventPic_Pokedex, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_GBAKid[] = {
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_GBAKid, 2, 4, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Fossil[] = {
    overworld_frame(gKantoObjectEventPic_Fossil, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Ruby[] = {
    overworld_frame(gKantoObjectEventPic_Ruby, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Sapphire[] = {
    overworld_frame(gKantoObjectEventPic_Sapphire, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_OldAmber[] = {
    overworld_frame(gKantoObjectEventPic_OldAmber, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_GymSign[] = {
    overworld_frame(gKantoObjectEventPic_GymSign, 2, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Sign[] = {
    overworld_frame(gKantoObjectEventPic_Sign, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_WoodenSign[] = {
    overworld_frame(gKantoObjectEventPic_WoodenSign, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Clipboard[] = {
    overworld_frame(gKantoObjectEventPic_Clipboard, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_BirthIslandStone[] = {
    overworld_frame(gKantoObjectEventPic_BirthIslandStone, 4, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_LaprasDoll[] = {
    overworld_frame(gKantoObjectEventPic_LaprasDoll, 4, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Seagallop[] = {
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gKantoObjectEventPic_Seagallop, 4, 16, 0),
};

static const struct SpriteFrameImage sKantoPicTable_SSAnne[] = {
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gKantoObjectEventPic_SSAnne, 8, 16, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Snorlax[] = {
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Snorlax, 4, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Spearow[] = {
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Spearow, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Pidgeot[] = {
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Pidgeot, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Omanyte[] = {
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Omanyte, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Kangaskhan[] = {
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Kangaskhan, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Psyduck[] = {
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Psyduck, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_NidoranF[] = {
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_NidoranF, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_NidoranM[] = {
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_NidoranM, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Nidorino[] = {
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Nidorino, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Meowth[] = {
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Meowth, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Seel[] = {
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Seel, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Voltorb[] = {
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Voltorb, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Slowpoke[] = {
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Slowpoke, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Slowbro[] = {
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Slowbro, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Machop[] = {
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Machop, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Wigglytuff[] = {
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Wigglytuff, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Doduo[] = {
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Doduo, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Fearow[] = {
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Fearow, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Lapras[] = {
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Lapras, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Zapdos[] = {
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Zapdos, 4, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Moltres[] = {
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Moltres, 4, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Articuno[] = {
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Articuno, 4, 4, 0),
};

static const struct SpriteFrameImage sKantoPicTable_DeoxysD[] = {
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysD, 4, 4, 1),
};

static const struct SpriteFrameImage sKantoPicTable_DeoxysA[] = {
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysA, 4, 4, 1),
};

static const struct SpriteFrameImage sKantoPicTable_DeoxysN[] = {
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_DeoxysN, 4, 4, 1),
};

static const struct SpriteFrameImage sKantoPicTable_Mewtwo[] = {
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mewtwo, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Mew[] = {
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Mew, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Entei[] = {
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Entei, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Raikou[] = {
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Raikou, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Suicune[] = {
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Suicune, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Lugia[] = {
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_Lugia, 4, 4, 1),
};

static const struct SpriteFrameImage sKantoPicTable_HoOh[] = {
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_HoOh, 4, 4, 1),
};

static const struct SpriteFrameImage sKantoPicTable_Celebi[] = {
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Celebi, 2, 2, 0),
};

static const struct SpriteFrameImage sKantoPicTable_Cubone[] = {
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Cubone, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Poliwrath[] = {
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Poliwrath, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Chansey[] = {
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Chansey, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Pikachu[] = {
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Pikachu, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Jigglypuff[] = {
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Jigglypuff, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Pidgey[] = {
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Pidgey, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Clefairy[] = {
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Clefairy, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Machoke[] = {
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Machoke, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Kabuto[] = {
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 0),
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 1),
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 2),
    overworld_frame(gKantoObjectEventPic_Kabuto, 2, 2, 2),
};

static const struct SpriteFrameImage sKantoPicTable_Mom[] = {
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 0),
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 1),
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 2),
    overworld_frame(gKantoObjectEventPic_Mom, 2, 4, 2),
};


// ---- object_event_anims.h ----
static const union AnimCmd sKantoAnim_StayStill[] = {
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpFaceSouth[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpFaceNorth[] = {
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpFaceWest[] = {
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpFaceEast[] = {
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoSouth[] = {
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(3, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoNorth[] = {
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(4, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoWest[] = {
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(6, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoEast[] = {
    ANIMCMD_FRAME(5, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFastSouth[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFastNorth[] = {
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(4, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFastWest[] = {
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFastEast[] = {
    ANIMCMD_FRAME(5, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFasterSouth[] = {
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(3, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFasterNorth[] = {
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(4, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFasterWest[] = {
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFasterEast[] = {
    ANIMCMD_FRAME(5, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFastestSouth[] = {
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(3, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFastestNorth[] = {
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(4, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFastestWest[] = {
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_QuintyPlumpGoFastestEast[] = {
    ANIMCMD_FRAME(5, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_FaceSouth[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_FaceNorth[] = {
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_FaceWest[] = {
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_FaceEast[] = {
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoSouth[] = {
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoNorth[] = {
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(6, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoWest[] = {
    ANIMCMD_FRAME(7, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(8, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoEast[] = {
    ANIMCMD_FRAME(7, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFastSouth[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFastNorth[] = {
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFastWest[] = {
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFastEast[] = {
    ANIMCMD_FRAME(7, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFasterSouth[] = {
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFasterNorth[] = {
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFasterWest[] = {
    ANIMCMD_FRAME(7, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(8, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFasterEast[] = {
    ANIMCMD_FRAME(7, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFastestSouth[] = {
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFastestNorth[] = {
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFastestWest[] = {
    ANIMCMD_FRAME(7, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(8, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GoFastestEast[] = {
    ANIMCMD_FRAME(7, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

// For indicating a VS Seeker rematch
static const union AnimCmd sKantoAnim_RaiseHand[] = {
    ANIMCMD_FRAME(9, 0),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_HoOhFlapWings[] = {
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_HoOhStayStill[] = {
    ANIMCMD_FRAME(3, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_SurfFaceSouth[] = {
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_SurfFaceNorth[] = {
    ANIMCMD_FRAME(1, 60),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_SurfFaceWest[] = {
    ANIMCMD_FRAME(2, 60),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_SurfFaceEast[] = {
    ANIMCMD_FRAME(2, 60, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownFaceSouth[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownFaceNorth[] = {
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownFaceWest[] = {
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownFaceEast[] = {
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoSouth[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoNorth[] = {
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoWest[] = {
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoEast[] = {
    ANIMCMD_FRAME(11, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFastNorth[] = {
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFastSouth[] = {
    ANIMCMD_FRAME(7, 2),
    ANIMCMD_FRAME(8, 2),
    ANIMCMD_FRAME(7, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(9, 2),
    ANIMCMD_FRAME(10, 2),
    ANIMCMD_FRAME(9, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFastWest[] = {
    ANIMCMD_FRAME(11, 2),
    ANIMCMD_FRAME(12, 2),
    ANIMCMD_FRAME(11, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(13, 2),
    ANIMCMD_FRAME(14, 2),
    ANIMCMD_FRAME(13, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFastEast[] = {
    ANIMCMD_FRAME(11, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFasterNorth[] = {
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFasterSouth[] = {
    ANIMCMD_FRAME(7, 1),
    ANIMCMD_FRAME(8, 1),
    ANIMCMD_FRAME(7, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(9, 1),
    ANIMCMD_FRAME(10, 1),
    ANIMCMD_FRAME(9, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFasterWest[] = {
    ANIMCMD_FRAME(11, 1),
    ANIMCMD_FRAME(12, 1),
    ANIMCMD_FRAME(11, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(13, 1),
    ANIMCMD_FRAME(14, 1),
    ANIMCMD_FRAME(13, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFasterEast[] = {
    ANIMCMD_FRAME(11, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFastestNorth[] = {
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_FRAME(4, 0),
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_FRAME(5, 0),
    ANIMCMD_FRAME(6, 0),
    ANIMCMD_FRAME(5, 0),
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFastestSouth[] = {
    ANIMCMD_FRAME(7, 0),
    ANIMCMD_FRAME(8, 0),
    ANIMCMD_FRAME(7, 0),
    ANIMCMD_FRAME(1, 0),
    ANIMCMD_FRAME(9, 0),
    ANIMCMD_FRAME(10, 0),
    ANIMCMD_FRAME(9, 0),
    ANIMCMD_FRAME(1, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFastestWest[] = {
    ANIMCMD_FRAME(11, 0),
    ANIMCMD_FRAME(12, 0),
    ANIMCMD_FRAME(11, 0),
    ANIMCMD_FRAME(2, 0),
    ANIMCMD_FRAME(13, 0),
    ANIMCMD_FRAME(14, 0),
    ANIMCMD_FRAME(13, 0),
    ANIMCMD_FRAME(2, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_UnknownGoFastestEast[] = {
    ANIMCMD_FRAME(11, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 0, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_SpinSouth[] = {
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_SpinNorth[] = {
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_SpinWest[] = {
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE), // Starts by facing East?
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_SpinEast[] = {
    ANIMCMD_FRAME(2, 2), // Starts by facing West?
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_ShakeHeadOrWalkInPlace[] = {
    ANIMCMD_FRAME(18, 16),
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_FRAME(19, 16),
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_RunSouth[] = {
    ANIMCMD_FRAME(9, 5),
    ANIMCMD_FRAME(10, 3),
    ANIMCMD_FRAME(9, 5),
    ANIMCMD_FRAME(11, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_RunNorth[] = {
    ANIMCMD_FRAME(12, 5),
    ANIMCMD_FRAME(13, 3),
    ANIMCMD_FRAME(12, 5),
    ANIMCMD_FRAME(14, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_RunWest[] = {
    ANIMCMD_FRAME(15, 5),
    ANIMCMD_FRAME(16, 3),
    ANIMCMD_FRAME(15, 5),
    ANIMCMD_FRAME(17, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_RunEast[] = {
    ANIMCMD_FRAME(15, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(16, 3, .hFlip = TRUE),
    ANIMCMD_FRAME(15, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(17, 3, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_FieldMove[] = {
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_VSSeeker[] = {
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_LOOP(0),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_LOOP(6),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_VSSeekerBike[] = {
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_LOOP(0),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_LOOP(6),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_GetOnOffSurfSouth[] = {
    ANIMCMD_FRAME(9, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GetOnOffSurfNorth[] = {
    ANIMCMD_FRAME(10, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GetOnOffSurfWest[] = {
    ANIMCMD_FRAME(11, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_GetOnOffSurfEast[] = {
    ANIMCMD_FRAME(11, 32, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_BunnyHopBackWheelSouth[] = {
    ANIMCMD_FRAME(15, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BunnyHopBackWheelNorth[] = {
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_FRAME(20, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BunnyHopBackWheelWest[] = {
    ANIMCMD_FRAME(23, 4),
    ANIMCMD_FRAME(24, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BunnyHopBackWheelEast[] = {
    ANIMCMD_FRAME(23, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BunnyHopFrontWheelSouth[] = {
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BunnyHopFrontWheelNorth[] = {
    ANIMCMD_FRAME(21, 4),
    ANIMCMD_FRAME(22, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BunnyHopFrontWheelWest[] = {
    ANIMCMD_FRAME(25, 4),
    ANIMCMD_FRAME(26, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BunnyHopFrontWheelEast[] = {
    ANIMCMD_FRAME(25, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(26, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_StandingWheelieBackWheelSouth[] = {
    ANIMCMD_FRAME(15, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_StandingWheelieBackWheelNorth[] = {
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_StandingWheelieBackWheelWest[] = {
    ANIMCMD_FRAME(23, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_StandingWheelieBackWheelEast[] = {
    ANIMCMD_FRAME(23, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_StandingWheelieFrontWheelSouth[] = {
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_StandingWheelieFrontWheelNorth[] = {
    ANIMCMD_FRAME(21, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_StandingWheelieFrontWheelWest[] = {
    ANIMCMD_FRAME(25, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_StandingWheelieFrontWheelEast[] = {
    ANIMCMD_FRAME(25, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_MovingWheelieSouth[] = {
    ANIMCMD_FRAME(27, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(28, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_MovingWheelieNorth[] = {
    ANIMCMD_FRAME(29, 4),
    ANIMCMD_FRAME(20, 4),
    ANIMCMD_FRAME(30, 4),
    ANIMCMD_FRAME(20, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_MovingWheelieWest[] = {
    ANIMCMD_FRAME(31, 4),
    ANIMCMD_FRAME(24, 4),
    ANIMCMD_FRAME(32, 4),
    ANIMCMD_FRAME(24, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_MovingWheelieEast[] = {
    ANIMCMD_FRAME(31, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(32, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_BerryTreeStage0[] = {
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BerryTreeStage1[] = {
    ANIMCMD_FRAME(1, 32),
    ANIMCMD_FRAME(2, 32),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BerryTreeStage2[] = {
    ANIMCMD_FRAME(3, 48),
    ANIMCMD_FRAME(4, 48),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BerryTreeStage3[] = {
    ANIMCMD_FRAME(5, 32),
    ANIMCMD_FRAME(5, 32),
    ANIMCMD_FRAME(6, 32),
    ANIMCMD_FRAME(6, 32),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_BerryTreeStage4[] = {
    ANIMCMD_FRAME(7, 48),
    ANIMCMD_FRAME(7, 48),
    ANIMCMD_FRAME(8, 48),
    ANIMCMD_FRAME(8, 48),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_NurseBow[] = {
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(9, 32),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_RockBreak[] = {
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_TreeCut[] = {
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_TakeOutRodSouth[] = {
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_TakeOutRodNorth[] = {
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_TakeOutRodWest[] = {
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_TakeOutRodEast[] = {
    ANIMCMD_FRAME(0, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_PutAwayRodSouth[] = {
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(10, 6),
    ANIMCMD_FRAME(9, 6),
    ANIMCMD_FRAME(8, 6),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_PutAwayRodNorth[] = {
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(6, 6),
    ANIMCMD_FRAME(5, 6),
    ANIMCMD_FRAME(4, 6),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_PutAwayRodWest[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_PutAwayRodEast[] = {
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sKantoAnim_HookedPokemonSouth[] = {
    ANIMCMD_FRAME(10, 6),
    ANIMCMD_FRAME(11, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(11, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_HookedPokemonNorth[] = {
    ANIMCMD_FRAME(6, 6),
    ANIMCMD_FRAME(7, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(7, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_HookedPokemonWest[] = {
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(3, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sKantoAnim_HookedPokemonEast[] = {
    ANIMCMD_FRAME(2, 6, .hFlip = TRUE),
    ANIMCMD_FRAME(3, 6, .hFlip = TRUE),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(3, 30, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

// Unused
static const union AffineAnimCmd sKantoAffineAnim_KyogreGroudon_GoSouthStart[] = {
    AFFINEANIMCMD_FRAME(0, 0, 1, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_LOOP(7),
    AFFINEANIMCMD_JUMP(0),
};

// Unused
static const union AffineAnimCmd sKantoAffineAnim_KyogreGroudon_GoSouth[] = {
    AFFINEANIMCMD_FRAME(0, 0, -1, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_LOOP(15),
    AFFINEANIMCMD_FRAME(0, 0, 1, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_LOOP(15),
    AFFINEANIMCMD_JUMP(0),
};

static const union AnimCmd *const sKantoAnimTable_Inanimate[] = {
    [ANIM_STAY_STILL] = sKantoAnim_StayStill
};

// Leftover from Ruby/Sapphire
static const union AnimCmd *const sKantoAnimTable_QuintyPlump[] = {
    [ANIM_STD_FACE_SOUTH] = sKantoAnim_QuintyPlumpFaceSouth,
    [ANIM_STD_FACE_NORTH] = sKantoAnim_QuintyPlumpFaceNorth,
    [ANIM_STD_FACE_WEST] = sKantoAnim_QuintyPlumpFaceWest,
    [ANIM_STD_FACE_EAST] = sKantoAnim_QuintyPlumpFaceEast,
    [ANIM_STD_GO_SOUTH] = sKantoAnim_QuintyPlumpGoSouth,
    [ANIM_STD_GO_NORTH] = sKantoAnim_QuintyPlumpGoNorth,
    [ANIM_STD_GO_WEST] = sKantoAnim_QuintyPlumpGoWest,
    [ANIM_STD_GO_EAST] = sKantoAnim_QuintyPlumpGoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sKantoAnim_QuintyPlumpGoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sKantoAnim_QuintyPlumpGoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sKantoAnim_QuintyPlumpGoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sKantoAnim_QuintyPlumpGoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sKantoAnim_QuintyPlumpGoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sKantoAnim_QuintyPlumpGoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sKantoAnim_QuintyPlumpGoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sKantoAnim_QuintyPlumpGoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sKantoAnim_QuintyPlumpGoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sKantoAnim_QuintyPlumpGoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sKantoAnim_QuintyPlumpGoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sKantoAnim_QuintyPlumpGoFastestEast,
};

static const union AnimCmd *const sKantoAnimTable_Standard[] = {
    [ANIM_STD_FACE_SOUTH] = sKantoAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sKantoAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sKantoAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sKantoAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sKantoAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sKantoAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sKantoAnim_GoWest,
    [ANIM_STD_GO_EAST] = sKantoAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sKantoAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sKantoAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sKantoAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sKantoAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sKantoAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sKantoAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sKantoAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sKantoAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sKantoAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sKantoAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sKantoAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sKantoAnim_GoFastestEast,
    [ANIM_RAISE_HAND] = sKantoAnim_RaiseHand,
};

static const union AnimCmd *const sKantoAnimTable_HoOh[] = {
    [ANIM_STD_FACE_SOUTH] = sKantoAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sKantoAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sKantoAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sKantoAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sKantoAnim_HoOhFlapWings,
    [ANIM_STD_GO_NORTH] = sKantoAnim_HoOhStayStill,
    [ANIM_STD_GO_WEST] = sKantoAnim_GoWest,
    [ANIM_STD_GO_EAST] = sKantoAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sKantoAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sKantoAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sKantoAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sKantoAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sKantoAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sKantoAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sKantoAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sKantoAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sKantoAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sKantoAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sKantoAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sKantoAnim_GoFastestEast,
    [ANIM_RAISE_HAND] = sKantoAnim_RaiseHand,
};

static const union AnimCmd *const sKantoAnimTable_Unknown[] = {
    [ANIM_STD_FACE_SOUTH] = sKantoAnim_UnknownFaceSouth,
    [ANIM_STD_FACE_NORTH] = sKantoAnim_UnknownFaceNorth,
    [ANIM_STD_FACE_WEST] = sKantoAnim_UnknownFaceWest,
    [ANIM_STD_FACE_EAST] = sKantoAnim_UnknownFaceEast,
    [ANIM_STD_GO_SOUTH] = sKantoAnim_UnknownGoSouth,
    [ANIM_STD_GO_NORTH] = sKantoAnim_UnknownGoNorth,
    [ANIM_STD_GO_WEST] = sKantoAnim_UnknownGoWest,
    [ANIM_STD_GO_EAST] = sKantoAnim_UnknownGoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sKantoAnim_UnknownGoFastNorth,
    [ANIM_STD_GO_FAST_NORTH] = sKantoAnim_UnknownGoFastSouth,
    [ANIM_STD_GO_FAST_WEST] = sKantoAnim_UnknownGoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sKantoAnim_UnknownGoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sKantoAnim_UnknownGoFasterNorth,
    [ANIM_STD_GO_FASTER_NORTH] = sKantoAnim_UnknownGoFasterSouth,
    [ANIM_STD_GO_FASTER_WEST] = sKantoAnim_UnknownGoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sKantoAnim_UnknownGoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sKantoAnim_UnknownGoFastestNorth,
    [ANIM_STD_GO_FASTEST_NORTH] = sKantoAnim_UnknownGoFastestSouth,
    [ANIM_STD_GO_FASTEST_WEST] = sKantoAnim_UnknownGoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sKantoAnim_UnknownGoFastestEast,
    [ANIM_RUN_SOUTH] = sKantoAnim_RunSouth,
    [ANIM_RUN_NORTH] = sKantoAnim_RunNorth,
    [ANIM_RUN_WEST] = sKantoAnim_RunWest,
    [ANIM_RUN_EAST] = sKantoAnim_RunEast,
};

static const union AnimCmd *const sKantoAnimTable_RedGreenNormal[] = {
    [ANIM_STD_FACE_SOUTH] = sKantoAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sKantoAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sKantoAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sKantoAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sKantoAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sKantoAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sKantoAnim_GoWest,
    [ANIM_STD_GO_EAST] = sKantoAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sKantoAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sKantoAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sKantoAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sKantoAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sKantoAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sKantoAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sKantoAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sKantoAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sKantoAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sKantoAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sKantoAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sKantoAnim_GoFastestEast,
    [ANIM_RUN_SOUTH] = sKantoAnim_RunSouth,
    [ANIM_RUN_NORTH] = sKantoAnim_RunNorth,
    [ANIM_RUN_WEST] = sKantoAnim_RunWest,
    [ANIM_RUN_EAST] = sKantoAnim_RunEast,
    [ANIM_SPIN_SOUTH] = sKantoAnim_SpinSouth,
    [ANIM_SPIN_NORTH] = sKantoAnim_SpinNorth,
    [ANIM_SPIN_WEST] = sKantoAnim_SpinWest,
    [ANIM_SPIN_EAST] = sKantoAnim_SpinEast,
    [ANIM_SHAKE_HEAD_OR_WALK_IN_PLACE] = sKantoAnim_ShakeHeadOrWalkInPlace,
};

// Leftover from Ruby/Sapphire
static const union AnimCmd *const sKantoAnimTable_AcroBike[] = {
    [ANIM_STD_FACE_SOUTH] = sKantoAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sKantoAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sKantoAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sKantoAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sKantoAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sKantoAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sKantoAnim_GoWest,
    [ANIM_STD_GO_EAST] = sKantoAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sKantoAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sKantoAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sKantoAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sKantoAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sKantoAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sKantoAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sKantoAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sKantoAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sKantoAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sKantoAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sKantoAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sKantoAnim_GoFastestEast,
    [ANIM_BUNNY_HOP_BACK_WHEEL_SOUTH] = sKantoAnim_BunnyHopBackWheelSouth,
    [ANIM_BUNNY_HOP_BACK_WHEEL_NORTH] = sKantoAnim_BunnyHopBackWheelNorth,
    [ANIM_BUNNY_HOP_BACK_WHEEL_WEST] = sKantoAnim_BunnyHopBackWheelWest,
    [ANIM_BUNNY_HOP_BACK_WHEEL_EAST] = sKantoAnim_BunnyHopBackWheelEast,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_SOUTH] = sKantoAnim_BunnyHopFrontWheelSouth,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_NORTH] = sKantoAnim_BunnyHopFrontWheelNorth,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_WEST] = sKantoAnim_BunnyHopFrontWheelWest,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_EAST] = sKantoAnim_BunnyHopFrontWheelEast,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTH] = sKantoAnim_StandingWheelieBackWheelSouth,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_NORTH] = sKantoAnim_StandingWheelieBackWheelNorth,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_WEST] = sKantoAnim_StandingWheelieBackWheelWest,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_EAST] = sKantoAnim_StandingWheelieBackWheelEast,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_SOUTH] = sKantoAnim_StandingWheelieFrontWheelSouth,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_NORTH] = sKantoAnim_StandingWheelieFrontWheelNorth,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_WEST] = sKantoAnim_StandingWheelieFrontWheelWest,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_EAST] = sKantoAnim_StandingWheelieFrontWheelEast,
    [ANIM_MOVING_WHEELIE_SOUTH] = sKantoAnim_MovingWheelieSouth,
    [ANIM_MOVING_WHEELIE_NORTH] = sKantoAnim_MovingWheelieNorth,
    [ANIM_MOVING_WHEELIE_WEST] = sKantoAnim_MovingWheelieWest,
    [ANIM_MOVING_WHEELIE_EAST] = sKantoAnim_MovingWheelieEast,
};

static const union AnimCmd *const sKantoAnimTable_RedGreenSurf[] = {
    [ANIM_STD_FACE_SOUTH] = sKantoAnim_SurfFaceSouth,
    [ANIM_STD_FACE_NORTH] = sKantoAnim_SurfFaceNorth,
    [ANIM_STD_FACE_WEST] = sKantoAnim_SurfFaceWest,
    [ANIM_STD_FACE_EAST] = sKantoAnim_SurfFaceEast,
    [ANIM_STD_GO_SOUTH] = sKantoAnim_SurfFaceSouth,
    [ANIM_STD_GO_NORTH] = sKantoAnim_SurfFaceNorth,
    [ANIM_STD_GO_WEST] = sKantoAnim_SurfFaceWest,
    [ANIM_STD_GO_EAST] = sKantoAnim_SurfFaceEast,
    [ANIM_STD_GO_FAST_SOUTH] = sKantoAnim_SurfFaceSouth,
    [ANIM_STD_GO_FAST_NORTH] = sKantoAnim_SurfFaceNorth,
    [ANIM_STD_GO_FAST_WEST] = sKantoAnim_SurfFaceWest,
    [ANIM_STD_GO_FAST_EAST] = sKantoAnim_SurfFaceEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sKantoAnim_SurfFaceSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sKantoAnim_SurfFaceNorth,
    [ANIM_STD_GO_FASTER_WEST] = sKantoAnim_SurfFaceWest,
    [ANIM_STD_GO_FASTER_EAST] = sKantoAnim_SurfFaceEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sKantoAnim_SurfFaceSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sKantoAnim_SurfFaceNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sKantoAnim_SurfFaceWest,
    [ANIM_STD_GO_FASTEST_EAST] = sKantoAnim_SurfFaceEast,
    [ANIM_GET_ON_OFF_POKEMON_SOUTH] = sKantoAnim_GetOnOffSurfSouth,
    [ANIM_GET_ON_OFF_POKEMON_NORTH] = sKantoAnim_GetOnOffSurfNorth,
    [ANIM_GET_ON_OFF_POKEMON_WEST] = sKantoAnim_GetOnOffSurfWest,
    [ANIM_GET_ON_OFF_POKEMON_EAST] = sKantoAnim_GetOnOffSurfEast,
};

static const union AnimCmd *const sKantoAnimTable_Nurse[] = {
    [ANIM_STD_FACE_SOUTH] = sKantoAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sKantoAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sKantoAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sKantoAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sKantoAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sKantoAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sKantoAnim_GoWest,
    [ANIM_STD_GO_EAST] = sKantoAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sKantoAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sKantoAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sKantoAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sKantoAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sKantoAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sKantoAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST]  = sKantoAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST]  = sKantoAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sKantoAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sKantoAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sKantoAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sKantoAnim_GoFastestEast,
    [ANIM_NURSE_BOW] = sKantoAnim_NurseBow,
};

static const union AnimCmd *const sKantoAnimTable_RedGreenFieldMove[] = {
    [ANIM_FIELD_MOVE] = sKantoAnim_FieldMove,
};

static const union AnimCmd *const sKantoAnimTable_RedGreenVSSeeker[] = {
    [ANIM_VS_SEEKER] = sKantoAnim_VSSeeker,
};

static const union AnimCmd *const sKantoAnimTable_RedGreenVSSeekerBike[] = {
    [ANIM_VS_SEEKER] = sKantoAnim_VSSeekerBike,
};

// Unused
static const union AnimCmd *const sKantoAnimTable_BerryTree[] = {
    sKantoAnim_BerryTreeStage0,
    sKantoAnim_BerryTreeStage1,
    sKantoAnim_BerryTreeStage2,
    sKantoAnim_BerryTreeStage3,
    sKantoAnim_BerryTreeStage4,
};

static const union AnimCmd *const sKantoAnimTable_RockSmashRock[] = {
    [ANIM_STAY_STILL] = sKantoAnim_StayStill,
    [ANIM_REMOVE_OBSTACLE] = sKantoAnim_RockBreak,
};

static const union AnimCmd *const sKantoAnimTable_CutTree[] = {
    [ANIM_STAY_STILL] = sKantoAnim_StayStill,
    [ANIM_REMOVE_OBSTACLE] = sKantoAnim_TreeCut,
};

static const union AnimCmd *const sKantoAnimTable_RedGreenFish[] = {
    [ANIM_TAKE_OUT_ROD_SOUTH] = sKantoAnim_TakeOutRodSouth,
    [ANIM_TAKE_OUT_ROD_NORTH] = sKantoAnim_TakeOutRodNorth,
    [ANIM_TAKE_OUT_ROD_WEST] = sKantoAnim_TakeOutRodWest,
    [ANIM_TAKE_OUT_ROD_EAST] = sKantoAnim_TakeOutRodEast,
    [ANIM_PUT_AWAY_ROD_SOUTH] = sKantoAnim_PutAwayRodSouth,
    [ANIM_PUT_AWAY_ROD_NORTH] = sKantoAnim_PutAwayRodNorth,
    [ANIM_PUT_AWAY_ROD_WEST] = sKantoAnim_PutAwayRodWest,
    [ANIM_PUT_AWAY_ROD_EAST] = sKantoAnim_PutAwayRodEast,
    [ANIM_HOOKED_POKEMON_SOUTH] = sKantoAnim_HookedPokemonSouth,
    [ANIM_HOOKED_POKEMON_NORTH] = sKantoAnim_HookedPokemonNorth,
    [ANIM_HOOKED_POKEMON_WEST] = sKantoAnim_HookedPokemonWest,
    [ANIM_HOOKED_POKEMON_EAST] = sKantoAnim_HookedPokemonEast,
};

static const struct StepAnimTable sKantoStepAnimTables[] = {
    {
        .anims = sKantoAnimTable_QuintyPlump,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sKantoAnimTable_Standard,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sKantoAnimTable_RedGreenNormal,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sKantoAnimTable_AcroBike,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sKantoAnimTable_RedGreenSurf,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sKantoAnimTable_Nurse,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sKantoAnimTable_RedGreenFish,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sKantoAnimTable_Unknown,
        .animPos = {3, 7, 0, 4},
    },
    {}
};


// ---- object_event_subsprites.h ----
const struct Subsprite gKantoObjectEventSpriteOamTable_16x16_0[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x16_1[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x16_2[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 2,
        .priority = 3
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x16_3[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 3
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x16_4[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 3
    }
};

const struct SubspriteTable gKantoObjectEventSpriteOamTables_16x16[] = {
    {0, NULL},
    {1, gKantoObjectEventSpriteOamTable_16x16_0},
    {1, gKantoObjectEventSpriteOamTable_16x16_1},
    {2, gKantoObjectEventSpriteOamTable_16x16_2},
    {2, gKantoObjectEventSpriteOamTable_16x16_3},
    {2, gKantoObjectEventSpriteOamTable_16x16_4},
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x32_0[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x32_1[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x32_2[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = -8,
        .y = 8,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 6,
        .priority = 3
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x32_3[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 4,
        .priority = 3
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_16x32_4[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 4,
        .priority = 3
    }
};

const struct SubspriteTable gKantoObjectEventSpriteOamTables_16x32[] = {
    {0, NULL},
    {1, gKantoObjectEventSpriteOamTable_16x32_0},
    {1, gKantoObjectEventSpriteOamTable_16x32_1},
    {3, gKantoObjectEventSpriteOamTable_16x32_2},
    {2, gKantoObjectEventSpriteOamTable_16x32_3},
    {2, gKantoObjectEventSpriteOamTable_16x32_4},
};

const struct Subsprite gKantoObjectEventSpriteOamTable_32x32_0[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_32x32_1[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_32x32_2[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = 0,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = -16, 
        .y = 8, 
        .shape = SPRITE_SHAPE(32x8), 
        .size = SPRITE_SIZE(32x8), 
        .tileOffset = 12, 
        .priority = 3
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_32x32_3[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = 0,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 8,
        .priority = 3
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_32x32_4[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = 0,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 8,
        .priority = 3
    }
};

const struct SubspriteTable gKantoObjectEventSpriteOamTables_32x32[] = {
    {0, NULL},
    {1, gKantoObjectEventSpriteOamTable_32x32_0},
    {1, gKantoObjectEventSpriteOamTable_32x32_1},
    {3, gKantoObjectEventSpriteOamTable_32x32_2},
    {2, gKantoObjectEventSpriteOamTable_32x32_3},
    {2, gKantoObjectEventSpriteOamTable_32x32_4},
};

const struct Subsprite gKantoObjectEventSpriteOamTable_48x48[] = {
    {
        .x = -24,
        .y = -24,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = 8,
        .y = -24,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = -24,
        .y = -16,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 6,
        .priority = 2
    },
    {
        .x = 8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 10,
        .priority = 2
    },
    {
        .x = -24,
        .y = -8,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 2
    },
    {
        .x = 8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 16,
        .priority = 2
    },
    {
        .x = -24,
        .y = 0,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 18,
        .priority = 2
    },
    {
        .x = 8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 22,
        .priority = 2
    },
    {
        .x = -24,
        .y = 8,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 2
    },
    {
        .x = 8,
        .y = 8,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 28,
        .priority = 2
    },
    {
        .x = -24,
        .y = 16,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 30,
        .priority = 2
    },
    {
        .x = 8,
        .y = 16,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 34,
        .priority = 2
    }
};

// Unused. Used by the moving truck in RS
const struct SubspriteTable gKantoObjectEventSpriteOamTables_48x48[] = {
    {12, gKantoObjectEventSpriteOamTable_48x48},
    {12, gKantoObjectEventSpriteOamTable_48x48},
    {12, gKantoObjectEventSpriteOamTable_48x48},
    {12, gKantoObjectEventSpriteOamTable_48x48},
    {12, gKantoObjectEventSpriteOamTable_48x48},
    {12, gKantoObjectEventSpriteOamTable_48x48},
};

const struct Subsprite gKantoObjectEventSpriteOamTable_64x32_0[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_64x32_1[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_64x32_2[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_64x32_3[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 2
    }
};

// Unused
const struct SubspriteTable gKantoObjectEventSpriteOamTables_64x32[] = {
    {0, NULL},
    {1, gKantoObjectEventSpriteOamTable_64x32_0},
    {1, gKantoObjectEventSpriteOamTable_64x32_1},
    {1, gKantoObjectEventSpriteOamTable_64x32_2},
    {1, gKantoObjectEventSpriteOamTable_64x32_3},
    {1, gKantoObjectEventSpriteOamTable_64x32_3},
};

const struct Subsprite gKantoObjectEventSpriteOamTable_64x64_0[] = {
    {
        .x = -32,
        .y = -32,
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_64x64_1[] = {
    {
        .x = -32,
        .y = -32,
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_64x64_2[] = {
    {
        .x = -32,
        .y = -32,
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_64x64_3[] = {
    {
        .x = -32,
        .y = -32,
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct SubspriteTable gKantoObjectEventSpriteOamTables_64x64[] = {
    {0, NULL},
    {1, gKantoObjectEventSpriteOamTable_64x64_0},
    {1, gKantoObjectEventSpriteOamTable_64x64_1},
    {1, gKantoObjectEventSpriteOamTable_64x64_2},
    {1, gKantoObjectEventSpriteOamTable_64x64_3},
    {1, gKantoObjectEventSpriteOamTable_64x64_3},
};

const struct Subsprite gKantoObjectEventSpriteOamTable_96x40_0[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 2
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 16,
        .priority = 2
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 20,
        .priority = 2
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 28,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 36,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 40,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 44,
        .priority = 2
    },
    {
        .x = -48,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 48,
        .priority = 2
    },
    {
        .x = -16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 52,
        .priority = 2
    },
    {
        .x = 16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 56,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_96x40_1[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 1
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 1
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 16,
        .priority = 1
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 20,
        .priority = 1
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 1
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 28,
        .priority = 1
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 32,
        .priority = 1
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 36,
        .priority = 1
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 40,
        .priority = 1
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 44,
        .priority = 1
    },
    {
        .x = -48,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 48,
        .priority = 1
    },
    {
        .x = -16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 52,
        .priority = 1
    },
    {
        .x = 16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 56,
        .priority = 1
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_96x40_2[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 2
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 16,
        .priority = 2
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 20,
        .priority = 2
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 28,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 36,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 40,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 44,
        .priority = 2
    },
    {
        .x = -48,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 48,
        .priority = 2
    },
    {
        .x = -16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 52,
        .priority = 2
    },
    {
        .x = 16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 56,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_96x40_3[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 1
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 1
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 16,
        .priority = 1
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 20,
        .priority = 1
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 28,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 36,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 40,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 44,
        .priority = 2
    },
    {
        .x = -48,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 48,
        .priority = 2
    },
    {
        .x = -16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 52,
        .priority = 2
    },
    {
        .x = 16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 56,
        .priority = 2
    }
};

// Unused. Used by the SS Tidal in RS
const struct SubspriteTable gKantoObjectEventSpriteOamTables_96x40[] = {
    {15, gKantoObjectEventSpriteOamTable_96x40_0},
    {15, gKantoObjectEventSpriteOamTable_96x40_0},
    {15, gKantoObjectEventSpriteOamTable_96x40_1},
    {15, gKantoObjectEventSpriteOamTable_96x40_2},
    {15, gKantoObjectEventSpriteOamTable_96x40_3},
    {15, gKantoObjectEventSpriteOamTable_96x40_3},
};

const struct Subsprite gKantoObjectEventSpriteOamTable_128x64_0[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = 32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 64,
        .priority = 2
    },
    {
        .x = 32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 96,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_128x64_1[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = 32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 32,
        .priority = 1
    },
    {
        .x = -32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 64,
        .priority = 1
    },
    {
        .x = 32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 96,
        .priority = 1
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_128x64_2[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = 32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 32,
        .priority = 1
    },
    {
        .x = -32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 64,
        .priority = 2
    },
    {
        .x = 32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 96,
        .priority = 2
    }
};

const struct SubspriteTable gKantoObjectEventSpriteOamTables_128x64[] = {
    {4, gKantoObjectEventSpriteOamTable_128x64_0},
    {4, gKantoObjectEventSpriteOamTable_128x64_0},
    {4, gKantoObjectEventSpriteOamTable_128x64_1},
    {4, gKantoObjectEventSpriteOamTable_128x64_2},
    {4, gKantoObjectEventSpriteOamTable_128x64_2},
    {4, gKantoObjectEventSpriteOamTable_128x64_2},
};

const struct Subsprite gKantoObjectEventSpriteOamTable_88x32_0[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = 32,
        .y = -20,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 10,
        .priority = 2
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 11,
        .priority = 2
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 15,
        .priority = 2
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 19,
        .priority = 2
    },
    {
        .x = 32,
        .y = -12,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 21,
        .priority = 2
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 22,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 26,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 30,
        .priority = 2
    },
    {
        .x = 32,
        .y = -4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 33,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 37,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 41,
        .priority = 2
    },
    {
        .x = 32,
        .y = 4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 43,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_88x32_1[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 8,
        .priority = 1
    },
    {
        .x = 32,
        .y = -20,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 10,
        .priority = 1
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 11,
        .priority = 1
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 15,
        .priority = 1
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 19,
        .priority = 1
    },
    {
        .x = 32,
        .y = -12,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 21,
        .priority = 1
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 22,
        .priority = 1
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 26,
        .priority = 1
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 30,
        .priority = 1
    },
    {
        .x = 32,
        .y = -4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 32,
        .priority = 1
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 33,
        .priority = 1
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 37,
        .priority = 1
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 41,
        .priority = 1
    },
    {
        .x = 32,
        .y = 4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 43,
        .priority = 1
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_88x32_2[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = 32,
        .y = -20,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 10,
        .priority = 2
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 11,
        .priority = 2
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 15,
        .priority = 2
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 19,
        .priority = 2
    },
    {
        .x = 32,
        .y = -12,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 21,
        .priority = 2
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 22,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 26,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 30,
        .priority = 2
    },
    {
        .x = 32,
        .y = -4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 33,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 37,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 41,
        .priority = 2
    },
    {
        .x = 32,
        .y = 4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 43,
        .priority = 2
    }
};

const struct Subsprite gKantoObjectEventSpriteOamTable_88x32_3[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 8,
        .priority = 1
    },
    {
        .x = 32,
        .y = -20,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 10,
        .priority = 1
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 11,
        .priority = 1
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 15,
        .priority = 1
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 19,
        .priority = 1
    },
    {
        .x = 32,
        .y = -12,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 21,
        .priority = 1
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 22,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 26,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 30,
        .priority = 2
    },
    {
        .x = 32,
        .y = -4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 33,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 37,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 41,
        .priority = 2
    },
    {
        .x = 32,
        .y = 4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 43,
        .priority = 2
    }
};

// Unused. Used by the submarine shadow in RS
const struct SubspriteTable gKantoObjectEventSpriteOamTables_88x32[] = {
    {16, gKantoObjectEventSpriteOamTable_88x32_0},
    {16, gKantoObjectEventSpriteOamTable_88x32_0},
    {16, gKantoObjectEventSpriteOamTable_88x32_1},
    {16, gKantoObjectEventSpriteOamTable_88x32_2},
    {16, gKantoObjectEventSpriteOamTable_88x32_3},
    {16, gKantoObjectEventSpriteOamTable_88x32_3},
};


// ---- object_event_graphics_info.h ----
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedNormal = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_RedGreenNormal,
    .images = sKantoPicTable_RedNormal,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_RedBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedSurf = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = TRUE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_RedGreenSurf,
    .images = sKantoPicTable_RedSurf,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedFieldMove = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_RedGreenFieldMove,
    .images = sKantoPicTable_RedItem,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Policeman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Policeman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RSBrendan = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_RSBrendan,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RSMay = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_RSMay,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_LittleBoy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_LittleBoy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_LittleGirl = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_LittleGirl,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_SittingBoy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_SittingBoy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Lass = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Lass,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Youngster = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Youngster,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Woman1 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Woman1,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Woman3 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Woman3,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Boy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Boy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_CrushGirl = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_CrushGirl,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BugCatcher = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_BugCatcher,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_FatMan = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_FatMan,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BaldingMan = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_BaldingMan,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Woman2 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Woman2,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_OldMan1 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_OldMan1,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_WorkerM = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_WorkerM,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_WorkerF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_WorkerF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Beauty = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Beauty,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Chef = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Chef,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_OldMan2 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_OldMan2,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_OldWoman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_OldWoman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Camper = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Camper,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Picnicker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Picnicker,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_CooltrainerM = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_CooltrainerM,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_CooltrainerF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_CooltrainerF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_PokeManiac = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_PokeManiac,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Channeler = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Channeler,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RocketF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_RocketF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_SwimmerMWater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_SwimmerMWater,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_SwimmerFWater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_SwimmerFWater,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_SwimmerMLand = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_SwimmerMLand,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_SwimmerFLand = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_SwimmerFLand,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BlackBelt = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_BlackBelt,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Scientist = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Scientist,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Gentleman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Gentleman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Sailor = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Sailor,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Captain = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Captain,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Fisher = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Fisher,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_TeachyTVHost = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_TeachyTVHost,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_UnusedWoman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_UnusedWoman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_TuberF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_TuberF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_TuberMWater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_TuberMWater,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_TuberMLand = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_TuberMLand,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Hiker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Hiker,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Biker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Biker,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GymGuy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_GymGuy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Nurse = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Nurse,
    .images = sKantoPicTable_Nurse,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_UnusedMaleReceptionist = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_UnusedMaleReceptionist,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_ItemBall = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_ItemBall,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_ProfOak = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_ProfOak,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Man = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Man,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Rocker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Rocker,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MrFuji = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_MrFuji,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Bruno = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Bruno,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_OldManLyingDown = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_OldManLyingDown,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_CutTree = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_CutTree,
    .images = sKantoPicTable_CutTree,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Clerk = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Clerk,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MGDeliveryman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_MGDeliveryman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_TrainerTowerDude = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_TrainerTowerDude,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_CableClubReceptionist = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_CableClubReceptionist,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_UnionRoomReceptionist = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_UnionRoomReceptionist,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RockSmashRock = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_RockSmashRock,
    .images = sKantoPicTable_RockSmashRock,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_StrengthBoulder = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_StrengthBoulder,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenNormal = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_RedGreenNormal,
    .images = sKantoPicTable_GreenNormal,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_GreenBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenSurf = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = TRUE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_RedGreenSurf,
    .images = sKantoPicTable_GreenSurf,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenFieldMove = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_RedGreenFieldMove,
    .images = sKantoPicTable_GreenItem,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedBikeAlt = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_RedBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RocketM = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_RocketM,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Celio = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Celio,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Agatha = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Agatha,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Brock = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Brock,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Misty = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Misty,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_LtSurge = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_LtSurge,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Erika = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Erika,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Koga = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Koga,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Giovanni = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Giovanni,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Blaine = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Blaine,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Sabrina = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Sabrina,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Bill = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Bill,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Daisy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Daisy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Lorelei = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Lorelei,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Lance = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Lance,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Blue = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Blue,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedFish = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_RedGreenFish,
    .images = sKantoPicTable_RedFish,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenFish = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_RedGreenFish,
    .images = sKantoPicTable_GreenFish,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedVSSeeker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_RedGreenVSSeeker,
    .images = sKantoPicTable_RedItem,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedVSSeekerBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_RedGreenVSSeekerBike,
    .images = sKantoPicTable_RedVSSeekerBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenVSSeeker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_RedGreenVSSeeker,
    .images = sKantoPicTable_GreenItem,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenVSSeekerBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_RedGreenVSSeekerBike,
    .images = sKantoPicTable_GreenVSSeekerBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_TownMap = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 32,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_32x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_TownMap,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Pokedex = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_Pokedex,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GBAKid = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_GBAKid,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Snorlax = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Snorlax,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Fossil = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_Fossil,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Ruby = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_Ruby,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Sapphire = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_Sapphire,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_OldAmber = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_OldAmber,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GymSign = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_GymSign,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Sign = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_Sign,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_TrainerTips = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_WoodenSign,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Clipboard = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_Clipboard,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Meteorite = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_METEORITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_BirthIslandStone,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_LaprasDoll = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Inanimate,
    .images = sKantoPicTable_LaprasDoll,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Spearow = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Spearow,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Omanyte = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Omanyte,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Kangaskhan = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Kangaskhan,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Psyduck = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Psyduck,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_NidoranF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_NidoranF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_NidoranM = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_NidoranM,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Nidorino = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Nidorino,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Meowth = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Meowth,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Seel = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Seel,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Voltorb = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Voltorb,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Slowpoke = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Slowpoke,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Slowbro = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Slowbro,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Machop = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Machop,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Wigglytuff = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Wigglytuff,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Doduo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Doduo,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Fearow = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Fearow,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Lapras = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Lapras,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Zapdos = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Zapdos,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Moltres = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Moltres,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Articuno = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Articuno,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_DeoxysD = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_DeoxysD,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_DeoxysA = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_DeoxysA,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_DeoxysN = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_DeoxysN,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Mewtwo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Mewtwo,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Mew = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Mew,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Entei = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Entei,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Raikou = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Raikou,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Suicune = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Suicune,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Lugia = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Lugia,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_HoOh = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_32x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_32x32,
    .anims = sKantoAnimTable_HoOh,
    .images = sKantoPicTable_HoOh,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Celebi = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Celebi,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Cubone = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Cubone,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Machoke = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Machoke,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Kabuto = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Kabuto,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Poliwrath = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Poliwrath,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Pidgeot = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Pidgeot,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Chansey = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Chansey,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Pikachu = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Pikachu,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Jigglypuff = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Jigglypuff,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Pidgey = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Pidgey,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Clefairy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x16,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x16,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Clefairy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Mom = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gKantoObjectEventBaseOam_16x32,
    .subspriteTables = gKantoObjectEventSpriteOamTables_16x32,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Mom,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Seagallop = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_SEAGALLOP,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 2048,
    .width = 64,
    .height = 64,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_64x64,
    .subspriteTables = gKantoObjectEventSpriteOamTables_64x64,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_Seagallop,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_SSAnne = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_KANTO_SS_ANNE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 4096,
    .width = 128,
    .height = 64,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gKantoObjectEventBaseOam_8x8,
    .subspriteTables = gKantoObjectEventSpriteOamTables_128x64,
    .anims = sKantoAnimTable_Standard,
    .images = sKantoPicTable_SSAnne,
    .affineAnims = gDummySpriteAffineAnimTable,
};


#include "kanto_player_extra.h"
#include "kanto_player_brendan_may.h"
#include "hoenn_player_red_leaf.h"

const struct ObjectEventGraphicsInfo *const gKantoObjectEventGraphicsInfoPointers[NUM_KANTO_OBJ_EVENT_GFX] = {
    [OBJ_EVENT_GFX_KANTO_RED_NORMAL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedNormal,
    [OBJ_EVENT_GFX_KANTO_RED_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedBike,
    [OBJ_EVENT_GFX_KANTO_RED_SURF - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedSurf,
    [OBJ_EVENT_GFX_KANTO_RED_FIELD_MOVE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedFieldMove,
    [OBJ_EVENT_GFX_KANTO_RED_FISH - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedFish,
    [OBJ_EVENT_GFX_KANTO_RED_VS_SEEKER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedVSSeeker,
    [OBJ_EVENT_GFX_KANTO_RED_VS_SEEKER_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedVSSeekerBike,
    [OBJ_EVENT_GFX_KANTO_GREEN_NORMAL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenNormal,
    [OBJ_EVENT_GFX_KANTO_GREEN_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenBike,
    [OBJ_EVENT_GFX_KANTO_GREEN_SURF - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenSurf,
    [OBJ_EVENT_GFX_KANTO_GREEN_FIELD_MOVE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenFieldMove,
    [OBJ_EVENT_GFX_KANTO_GREEN_FISH - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenFish,
    [OBJ_EVENT_GFX_KANTO_GREEN_VS_SEEKER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenVSSeeker,
    [OBJ_EVENT_GFX_KANTO_GREEN_VS_SEEKER_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenVSSeekerBike,
    [OBJ_EVENT_GFX_KANTO_RS_BRENDAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RSBrendan,
    [OBJ_EVENT_GFX_KANTO_RS_MAY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RSMay,
    [OBJ_EVENT_GFX_KANTO_LITTLE_BOY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_LittleBoy,
    [OBJ_EVENT_GFX_KANTO_LITTLE_GIRL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_LittleGirl,
    [OBJ_EVENT_GFX_KANTO_YOUNGSTER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Youngster,
    [OBJ_EVENT_GFX_KANTO_BOY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Boy,
    [OBJ_EVENT_GFX_KANTO_BUG_CATCHER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BugCatcher,
    [OBJ_EVENT_GFX_KANTO_SITTING_BOY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_SittingBoy,
    [OBJ_EVENT_GFX_KANTO_LASS - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Lass,
    [OBJ_EVENT_GFX_KANTO_WOMAN_1 - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Woman1,
    [OBJ_EVENT_GFX_KANTO_CRUSH_GIRL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_CrushGirl,
    [OBJ_EVENT_GFX_KANTO_MAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Man,
    [OBJ_EVENT_GFX_KANTO_ROCKER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Rocker,
    [OBJ_EVENT_GFX_KANTO_FAT_MAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_FatMan,
    [OBJ_EVENT_GFX_KANTO_WOMAN_2 - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Woman2,
    [OBJ_EVENT_GFX_KANTO_BEAUTY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Beauty,
    [OBJ_EVENT_GFX_KANTO_BALDING_MAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BaldingMan,
    [OBJ_EVENT_GFX_KANTO_WOMAN_3 - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Woman3,
    [OBJ_EVENT_GFX_KANTO_OLD_MAN_1 - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_OldMan1,
    [OBJ_EVENT_GFX_KANTO_OLD_MAN_2 - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_OldMan2,
    [OBJ_EVENT_GFX_KANTO_OLD_MAN_LYING_DOWN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_OldManLyingDown,
    [OBJ_EVENT_GFX_KANTO_OLD_WOMAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_OldWoman,
    [OBJ_EVENT_GFX_KANTO_TUBER_M_WATER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_TuberMWater,
    [OBJ_EVENT_GFX_KANTO_TUBER_F - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_TuberF,
    [OBJ_EVENT_GFX_KANTO_TUBER_M_LAND - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_TuberMLand,
    [OBJ_EVENT_GFX_KANTO_CAMPER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Camper,
    [OBJ_EVENT_GFX_KANTO_PICNICKER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Picnicker,
    [OBJ_EVENT_GFX_KANTO_COOLTRAINER_M - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_CooltrainerM,
    [OBJ_EVENT_GFX_KANTO_COOLTRAINER_F - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_CooltrainerF,
    [OBJ_EVENT_GFX_KANTO_SWIMMER_M_WATER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_SwimmerMWater,
    [OBJ_EVENT_GFX_KANTO_SWIMMER_F_WATER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_SwimmerFWater,
    [OBJ_EVENT_GFX_KANTO_SWIMMER_M_LAND - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_SwimmerMLand,
    [OBJ_EVENT_GFX_KANTO_SWIMMER_F_LAND - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_SwimmerFLand,
    [OBJ_EVENT_GFX_KANTO_WORKER_M - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_WorkerM,
    [OBJ_EVENT_GFX_KANTO_WORKER_F - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_WorkerF,
    [OBJ_EVENT_GFX_KANTO_ROCKET_M - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RocketM,
    [OBJ_EVENT_GFX_KANTO_ROCKET_F - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RocketF,
    [OBJ_EVENT_GFX_KANTO_GBA_KID - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GBAKid,
    [OBJ_EVENT_GFX_KANTO_POKE_MANIAC - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_PokeManiac,
    [OBJ_EVENT_GFX_KANTO_BIKER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Biker,
    [OBJ_EVENT_GFX_KANTO_BLACK_BELT - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BlackBelt,
    [OBJ_EVENT_GFX_KANTO_SCIENTIST - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Scientist,
    [OBJ_EVENT_GFX_KANTO_HIKER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Hiker,
    [OBJ_EVENT_GFX_KANTO_FISHER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Fisher,
    [OBJ_EVENT_GFX_KANTO_CHANNELER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Channeler,
    [OBJ_EVENT_GFX_KANTO_CHEF - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Chef,
    [OBJ_EVENT_GFX_KANTO_POLICEMAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Policeman,
    [OBJ_EVENT_GFX_KANTO_GENTLEMAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Gentleman,
    [OBJ_EVENT_GFX_KANTO_SAILOR - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Sailor,
    [OBJ_EVENT_GFX_KANTO_CAPTAIN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Captain,
    [OBJ_EVENT_GFX_KANTO_NURSE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Nurse,
    [OBJ_EVENT_GFX_KANTO_CABLE_CLUB_RECEPTIONIST - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_CableClubReceptionist,
    [OBJ_EVENT_GFX_KANTO_UNION_ROOM_RECEPTIONIST - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_UnionRoomReceptionist,
    [OBJ_EVENT_GFX_KANTO_UNUSED_MALE_RECEPTIONIST - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_UnusedMaleReceptionist,
    [OBJ_EVENT_GFX_KANTO_CLERK - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Clerk,
    [OBJ_EVENT_GFX_KANTO_MG_DELIVERYMAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MGDeliveryman,
    [OBJ_EVENT_GFX_KANTO_TRAINER_TOWER_DUDE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_TrainerTowerDude,
    [OBJ_EVENT_GFX_KANTO_PROF_OAK - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_ProfOak,
    [OBJ_EVENT_GFX_KANTO_BLUE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Blue,
    [OBJ_EVENT_GFX_KANTO_BILL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Bill,
    [OBJ_EVENT_GFX_KANTO_LANCE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Lance,
    [OBJ_EVENT_GFX_KANTO_AGATHA - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Agatha,
    [OBJ_EVENT_GFX_KANTO_DAISY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Daisy,
    [OBJ_EVENT_GFX_KANTO_LORELEI - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Lorelei,
    [OBJ_EVENT_GFX_KANTO_MR_FUJI - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MrFuji,
    [OBJ_EVENT_GFX_KANTO_BRUNO - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Bruno,
    [OBJ_EVENT_GFX_KANTO_BROCK - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Brock,
    [OBJ_EVENT_GFX_KANTO_MISTY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Misty,
    [OBJ_EVENT_GFX_KANTO_LT_SURGE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_LtSurge,
    [OBJ_EVENT_GFX_KANTO_ERIKA - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Erika,
    [OBJ_EVENT_GFX_KANTO_KOGA - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Koga,
    [OBJ_EVENT_GFX_KANTO_SABRINA - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Sabrina,
    [OBJ_EVENT_GFX_KANTO_BLAINE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Blaine,
    [OBJ_EVENT_GFX_KANTO_GIOVANNI - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Giovanni,
    [OBJ_EVENT_GFX_KANTO_MOM - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Mom,
    [OBJ_EVENT_GFX_KANTO_CELIO - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Celio,
    [OBJ_EVENT_GFX_KANTO_TEACHY_TV_HOST - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_TeachyTVHost,
    [OBJ_EVENT_GFX_KANTO_GYM_GUY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GymGuy,
    [OBJ_EVENT_GFX_KANTO_ITEM_BALL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_ItemBall,
    [OBJ_EVENT_GFX_KANTO_TOWN_MAP - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_TownMap,
    [OBJ_EVENT_GFX_KANTO_POKEDEX - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Pokedex,
    [OBJ_EVENT_GFX_KANTO_CUT_TREE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_CutTree,
    [OBJ_EVENT_GFX_KANTO_ROCK_SMASH_ROCK - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RockSmashRock,
    [OBJ_EVENT_GFX_KANTO_PUSHABLE_BOULDER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_StrengthBoulder,
    [OBJ_EVENT_GFX_KANTO_FOSSIL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Fossil,
    [OBJ_EVENT_GFX_KANTO_RUBY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Ruby,
    [OBJ_EVENT_GFX_KANTO_SAPPHIRE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Sapphire,
    [OBJ_EVENT_GFX_KANTO_OLD_AMBER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_OldAmber,
    [OBJ_EVENT_GFX_KANTO_GYM_SIGN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GymSign,
    [OBJ_EVENT_GFX_KANTO_SIGN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Sign,
    [OBJ_EVENT_GFX_KANTO_TRAINER_TIPS - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_TrainerTips,
    [OBJ_EVENT_GFX_KANTO_CLIPBOARD - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Clipboard,
    [OBJ_EVENT_GFX_KANTO_METEORITE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Meteorite,
    [OBJ_EVENT_GFX_KANTO_LAPRAS_DOLL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_LaprasDoll,
    [OBJ_EVENT_GFX_KANTO_SEAGALLOP - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Seagallop,
    [OBJ_EVENT_GFX_KANTO_SNORLAX - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Snorlax,
    [OBJ_EVENT_GFX_KANTO_SPEAROW - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Spearow,
    [OBJ_EVENT_GFX_KANTO_CUBONE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Cubone,
    [OBJ_EVENT_GFX_KANTO_POLIWRATH - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Poliwrath,
    [OBJ_EVENT_GFX_KANTO_CLEFAIRY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Clefairy,
    [OBJ_EVENT_GFX_KANTO_PIDGEOT - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Pidgeot,
    [OBJ_EVENT_GFX_KANTO_JIGGLYPUFF - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Jigglypuff,
    [OBJ_EVENT_GFX_KANTO_PIDGEY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Pidgey,
    [OBJ_EVENT_GFX_KANTO_CHANSEY - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Chansey,
    [OBJ_EVENT_GFX_KANTO_OMANYTE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Omanyte,
    [OBJ_EVENT_GFX_KANTO_KANGASKHAN - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Kangaskhan,
    [OBJ_EVENT_GFX_KANTO_PIKACHU - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Pikachu,
    [OBJ_EVENT_GFX_KANTO_PSYDUCK - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Psyduck,
    [OBJ_EVENT_GFX_KANTO_NIDORAN_F - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_NidoranF,
    [OBJ_EVENT_GFX_KANTO_NIDORAN_M - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_NidoranM,
    [OBJ_EVENT_GFX_KANTO_NIDORINO - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Nidorino,
    [OBJ_EVENT_GFX_KANTO_MEOWTH - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Meowth,
    [OBJ_EVENT_GFX_KANTO_SEEL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Seel,
    [OBJ_EVENT_GFX_KANTO_VOLTORB - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Voltorb,
    [OBJ_EVENT_GFX_KANTO_SLOWPOKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Slowpoke,
    [OBJ_EVENT_GFX_KANTO_SLOWBRO - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Slowbro,
    [OBJ_EVENT_GFX_KANTO_MACHOP - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Machop,
    [OBJ_EVENT_GFX_KANTO_WIGGLYTUFF - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Wigglytuff,
    [OBJ_EVENT_GFX_KANTO_DODUO - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Doduo,
    [OBJ_EVENT_GFX_KANTO_FEAROW - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Fearow,
    [OBJ_EVENT_GFX_KANTO_MACHOKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Machoke,
    [OBJ_EVENT_GFX_KANTO_LAPRAS - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Lapras,
    [OBJ_EVENT_GFX_KANTO_ZAPDOS - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Zapdos,
    [OBJ_EVENT_GFX_KANTO_MOLTRES - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Moltres,
    [OBJ_EVENT_GFX_KANTO_ARTICUNO - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Articuno,
    [OBJ_EVENT_GFX_KANTO_MEWTWO - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Mewtwo,
    [OBJ_EVENT_GFX_KANTO_MEW - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Mew,
    [OBJ_EVENT_GFX_KANTO_ENTEI - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Entei,
    [OBJ_EVENT_GFX_KANTO_SUICUNE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Suicune,
    [OBJ_EVENT_GFX_KANTO_RAIKOU - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Raikou,
    [OBJ_EVENT_GFX_KANTO_LUGIA - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Lugia,
    [OBJ_EVENT_GFX_KANTO_HO_OH - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_HoOh,
    [OBJ_EVENT_GFX_KANTO_CELEBI - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Celebi,
    [OBJ_EVENT_GFX_KANTO_KABUTO - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Kabuto,
    [OBJ_EVENT_GFX_KANTO_DEOXYS_D - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_DeoxysD,
    [OBJ_EVENT_GFX_KANTO_DEOXYS_A - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_DeoxysA,
    [OBJ_EVENT_GFX_KANTO_DEOXYS_N - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_DeoxysN,
    [OBJ_EVENT_GFX_KANTO_SS_ANNE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_SSAnne,
    [OBJ_EVENT_GFX_KANTO_RED_ACRO_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedAcroBike,
    [OBJ_EVENT_GFX_KANTO_RED_WATERING - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedWatering,
    [OBJ_EVENT_GFX_KANTO_RED_UNDERWATER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedUnderwater,
    [OBJ_EVENT_GFX_KANTO_GREEN_ACRO_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenAcroBike,
    [OBJ_EVENT_GFX_KANTO_GREEN_WATERING - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenWatering,
    [OBJ_EVENT_GFX_KANTO_GREEN_UNDERWATER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenUnderwater,
    [OBJ_EVENT_GFX_KANTO_SHRINE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_Shrine,
    [OBJ_EVENT_GFX_FUSION_METEORITE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_FusionMeteorite,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_NORMAL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanNormal,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanBike,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_ACRO_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanAcroBike,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_SURF - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanSurf,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_FIELD_MOVE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanFieldMove,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_VS_SEEKER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanVSSeeker,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_VS_SEEKER_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanVSSeekerBike,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_FISH - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanFish,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_UNDERWATER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanUnderwater,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_WATERING - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanWatering,
    [OBJ_EVENT_GFX_KANTO_BRENDAN_DECORATING - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_BrendanDecorating,
    [OBJ_EVENT_GFX_KANTO_MAY_NORMAL - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayNormal,
    [OBJ_EVENT_GFX_KANTO_MAY_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayBike,
    [OBJ_EVENT_GFX_KANTO_MAY_ACRO_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayAcroBike,
    [OBJ_EVENT_GFX_KANTO_MAY_SURF - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MaySurf,
    [OBJ_EVENT_GFX_KANTO_MAY_FIELD_MOVE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayFieldMove,
    [OBJ_EVENT_GFX_KANTO_MAY_VS_SEEKER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayVSSeeker,
    [OBJ_EVENT_GFX_KANTO_MAY_VS_SEEKER_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayVSSeekerBike,
    [OBJ_EVENT_GFX_KANTO_MAY_FISH - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayFish,
    [OBJ_EVENT_GFX_KANTO_MAY_UNDERWATER - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayUnderwater,
    [OBJ_EVENT_GFX_KANTO_MAY_WATERING - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayWatering,
    [OBJ_EVENT_GFX_KANTO_MAY_DECORATING - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_MayDecorating,
    [OBJ_EVENT_GFX_KANTO_RED_DECORATING - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_RedDecorating,
    [OBJ_EVENT_GFX_KANTO_GREEN_DECORATING - KANTO_OBJ_EVENT_GFX_START] = &gKantoObjectEventGraphicsInfo_GreenDecorating,
    // PokemonNative3G : Red et Leaf en style Émeraude, à Hoenn (hoenn_player_red_leaf.h)
    [OBJ_EVENT_GFX_HOENN_RED_NORMAL - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedNormal,
    [OBJ_EVENT_GFX_HOENN_RED_MACH_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedMachBike,
    [OBJ_EVENT_GFX_HOENN_RED_ACRO_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedAcroBike,
    [OBJ_EVENT_GFX_HOENN_RED_SURFING - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedSurfing,
    [OBJ_EVENT_GFX_HOENN_RED_FIELD_MOVE - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedFieldMove,
    [OBJ_EVENT_GFX_HOENN_RED_FISHING - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedFishing,
    [OBJ_EVENT_GFX_HOENN_RED_UNDERWATER - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedUnderwater,
    [OBJ_EVENT_GFX_HOENN_RED_WATERING - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedWatering,
    [OBJ_EVENT_GFX_HOENN_RED_DECORATING - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_RedDecorating,
    [OBJ_EVENT_GFX_HOENN_LEAF_NORMAL - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafNormal,
    [OBJ_EVENT_GFX_HOENN_LEAF_MACH_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafMachBike,
    [OBJ_EVENT_GFX_HOENN_LEAF_ACRO_BIKE - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafAcroBike,
    [OBJ_EVENT_GFX_HOENN_LEAF_SURFING - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafSurfing,
    [OBJ_EVENT_GFX_HOENN_LEAF_FIELD_MOVE - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafFieldMove,
    [OBJ_EVENT_GFX_HOENN_LEAF_FISHING - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafFishing,
    [OBJ_EVENT_GFX_HOENN_LEAF_UNDERWATER - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafUnderwater,
    [OBJ_EVENT_GFX_HOENN_LEAF_WATERING - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafWatering,
    [OBJ_EVENT_GFX_HOENN_LEAF_DECORATING - KANTO_OBJ_EVENT_GFX_START] = &gHoennObjectEventGraphicsInfo_LeafDecorating,
};
