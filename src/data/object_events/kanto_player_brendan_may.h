// PokemonNative3G : le joueur en style Rouge Feu à Kanto, quel que soit le personnage (Options > PERSO). Brice et
// Flora dans leur tenue d'Émeraude, dessinés en style Rouge Feu par Poffin_Case (pack « FRHoenn », PokéCommunity),
// importés par tools/sprites_joueur_rf.py, et la décoration de Red/Leaf du même pack. Mêmes images et animations que
// Red/Leaf (kanto_object_events.h, kanto_player_extra.h) ; Flora a des images de 32 pixels de large quand son
// chignon dépasse (marche, course, objet). Palettes : graphics/kanto/object_events/palettes/{brendan,may}.pal, dans
// l'ordre de la palette des PNJ de Rouge Feu, le jaune de Rubis/Saphir devenu le vert d'Émeraude.

#define KANTO_PLAYER_GFX(_palTag, _w, _h, _slot, _tracks, _anims, _images, _inanimate) {    \
    .tileTag = TAG_NONE,                                                                    \
    .paletteTag = _palTag,                                                                  \
    .reflectionPaletteTag = (_palTag) == OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER                \
                            ? OBJ_EVENT_PAL_TAG_NONE : OBJ_EVENT_PAL_TAG_KANTO_BRIDGE_REFLECTION, \
    .size = (_inanimate) ? 256 : 512,                /* comme Émeraude et Rouge Feu */      \
    .width = _w,                                                                            \
    .height = _h,                                                                           \
    .paletteSlot = _slot,                                                                   \
    .shadowSize = SHADOW_SIZE_M,                                                            \
    .inanimate = _inanimate,                                                                \
    .disableReflectionPaletteLoad = (_palTag) == OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER,       \
    .tracks = _tracks,                                                                      \
    .oam = (_w) == 32 ? &gKantoObjectEventBaseOam_32x32 : &gKantoObjectEventBaseOam_16x32,  \
    .subspriteTables = (_w) == 32 ? gKantoObjectEventSpriteOamTables_32x32                 \
                                  : gKantoObjectEventSpriteOamTables_16x32,                 \
    .anims = _anims,                                                                        \
    .images = _images,                                                                      \
    .affineAnims = gDummySpriteAffineAnimTable,                                             \
}

// 9 images d'une feuille, dans l'ordre (vélo, arrosoir, plongée : les tables d'Émeraude déroulées par le pack)
#define FRAMES_9(_pic, _w) \
    overworld_frame(_pic, _w, 4, 0), overworld_frame(_pic, _w, 4, 1), overworld_frame(_pic, _w, 4, 2), \
    overworld_frame(_pic, _w, 4, 3), overworld_frame(_pic, _w, 4, 4), overworld_frame(_pic, _w, 4, 5), \
    overworld_frame(_pic, _w, 4, 6), overworld_frame(_pic, _w, 4, 7), overworld_frame(_pic, _w, 4, 8)
// Marche (0-8) et course (9-17) ; 18-19 = la tête secouée de Rouge Feu (ANIM_SHAKE_HEAD_OR_WALK_IN_PLACE), qu'aucun
// script ne fait faire au joueur et que le pack n'a pas : l'image de face
#define FRAMES_NORMAL(_pic, _w) \
    FRAMES_9(_pic, _w), \
    overworld_frame(_pic, _w, 4, 9), overworld_frame(_pic, _w, 4, 10), overworld_frame(_pic, _w, 4, 11), \
    overworld_frame(_pic, _w, 4, 12), overworld_frame(_pic, _w, 4, 13), overworld_frame(_pic, _w, 4, 14), \
    overworld_frame(_pic, _w, 4, 15), overworld_frame(_pic, _w, 4, 16), overworld_frame(_pic, _w, 4, 17), \
    overworld_frame(_pic, _w, 4, 0), overworld_frame(_pic, _w, 4, 0)
#define FRAMES_12(_pic, _w) \
    FRAMES_9(_pic, _w), \
    overworld_frame(_pic, _w, 4, 9), overworld_frame(_pic, _w, 4, 10), overworld_frame(_pic, _w, 4, 11)
#define FRAMES_27(_pic) \
    FRAMES_9(_pic, 4), \
    overworld_frame(_pic, 4, 4, 9), overworld_frame(_pic, 4, 4, 10), overworld_frame(_pic, 4, 4, 11), \
    overworld_frame(_pic, 4, 4, 12), overworld_frame(_pic, 4, 4, 13), overworld_frame(_pic, 4, 4, 14), \
    overworld_frame(_pic, 4, 4, 15), overworld_frame(_pic, 4, 4, 16), overworld_frame(_pic, 4, 4, 17), \
    overworld_frame(_pic, 4, 4, 18), overworld_frame(_pic, 4, 4, 19), overworld_frame(_pic, 4, 4, 20), \
    overworld_frame(_pic, 4, 4, 21), overworld_frame(_pic, 4, 4, 22), overworld_frame(_pic, 4, 4, 23), \
    overworld_frame(_pic, 4, 4, 24), overworld_frame(_pic, 4, 4, 25), overworld_frame(_pic, 4, 4, 26)

const u16 gKantoObjectEventPal_Brendan[] = INCGFX_U16("graphics/kanto/object_events/palettes/brendan.pal", ".gbapal");
const u16 gKantoObjectEventPal_BrendanReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/brendan_reflection.pal", ".gbapal");
const u16 gKantoObjectEventPal_May[] = INCGFX_U16("graphics/kanto/object_events/palettes/may.pal", ".gbapal");
const u16 gKantoObjectEventPal_MayReflection[] = INCGFX_U16("graphics/kanto/object_events/palettes/may_reflection.pal", ".gbapal");

// ---- Brice ----
const u16 gKantoObjectEventPic_BrendanNormal[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_normal.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_BrendanBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_BrendanAcroBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_acro_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_BrendanSurf[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_surf.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_BrendanItem[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_item.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_BrendanVSSeekerBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_vs_seeker_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_BrendanFish[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_fish.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_BrendanUnderwater[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_underwater.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_BrendanWatering[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_watering.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_BrendanDecorating[] = INCGFX_U16("graphics/kanto/object_events/pics/people/brendan_decorating.png", ".4bpp", "-mwidth 2 -mheight 4");

static const struct SpriteFrameImage sKantoPicTable_BrendanNormal[] = {FRAMES_NORMAL(gKantoObjectEventPic_BrendanNormal, 2)};
static const struct SpriteFrameImage sKantoPicTable_BrendanBike[] = {FRAMES_9(gKantoObjectEventPic_BrendanBike, 4)};
static const struct SpriteFrameImage sKantoPicTable_BrendanAcroBike[] = {FRAMES_27(gKantoObjectEventPic_BrendanAcroBike)};
static const struct SpriteFrameImage sKantoPicTable_BrendanSurf[] = {FRAMES_12(gKantoObjectEventPic_BrendanSurf, 2)};
static const struct SpriteFrameImage sKantoPicTable_BrendanItem[] = {FRAMES_9(gKantoObjectEventPic_BrendanItem, 2)};
static const struct SpriteFrameImage sKantoPicTable_BrendanVSSeekerBike[] = {
    overworld_frame(gKantoObjectEventPic_BrendanVSSeekerBike, 4, 4, 0), overworld_frame(gKantoObjectEventPic_BrendanVSSeekerBike, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_BrendanVSSeekerBike, 4, 4, 2), overworld_frame(gKantoObjectEventPic_BrendanVSSeekerBike, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_BrendanVSSeekerBike, 4, 4, 4), overworld_frame(gKantoObjectEventPic_BrendanVSSeekerBike, 4, 4, 5),
};
static const struct SpriteFrameImage sKantoPicTable_BrendanFish[] = {FRAMES_12(gKantoObjectEventPic_BrendanFish, 4)};
static const struct SpriteFrameImage sKantoPicTable_BrendanUnderwater[] = {FRAMES_9(gKantoObjectEventPic_BrendanUnderwater, 4)};
static const struct SpriteFrameImage sKantoPicTable_BrendanWatering[] = {FRAMES_9(gKantoObjectEventPic_BrendanWatering, 4)};
static const struct SpriteFrameImage sKantoPicTable_BrendanDecorating[] = {overworld_frame(gKantoObjectEventPic_BrendanDecorating, 2, 4, 0)};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanNormal = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 16, 32, PALSLOT_PLAYER, TRACKS_FOOT, sKantoAnimTable_RedGreenNormal, sKantoPicTable_BrendanNormal, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanBike = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 32, 32, PALSLOT_PLAYER, TRACKS_BIKE_TIRE, sKantoAnimTable_Standard, sKantoPicTable_BrendanBike, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanAcroBike = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 32, 32, PALSLOT_PLAYER, TRACKS_BIKE_TIRE, sAnimTable_AcroBike, sKantoPicTable_BrendanAcroBike, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanSurf = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 16, 32, PALSLOT_PLAYER, TRACKS_NONE, sKantoAnimTable_RedGreenSurf, sKantoPicTable_BrendanSurf, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanFieldMove = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 16, 32, PALSLOT_PLAYER, TRACKS_FOOT, sKantoAnimTable_RedGreenFieldMove, sKantoPicTable_BrendanItem, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanVSSeeker = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 16, 32, PALSLOT_PLAYER, TRACKS_FOOT, sKantoAnimTable_RedGreenVSSeeker, sKantoPicTable_BrendanItem, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanVSSeekerBike = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 32, 32, PALSLOT_PLAYER, TRACKS_BIKE_TIRE, sKantoAnimTable_RedGreenVSSeekerBike, sKantoPicTable_BrendanVSSeekerBike, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanFish = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 32, 32, PALSLOT_PLAYER, TRACKS_FOOT, sKantoAnimTable_RedGreenFish, sKantoPicTable_BrendanFish, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanUnderwater = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER, 32, 32, PALSLOT_PLAYER, TRACKS_FOOT, sAnimTable_Standard, sKantoPicTable_BrendanUnderwater, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanWatering = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 32, 32, PALSLOT_PLAYER, TRACKS_FOOT, sAnimTable_Standard, sKantoPicTable_BrendanWatering, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_BrendanDecorating = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_BRENDAN, 16, 32, PALSLOT_NPC_SPECIAL, TRACKS_FOOT, sAnimTable_Inanimate, sKantoPicTable_BrendanDecorating, TRUE);

// ---- Flora (marche, course et objet en 32 de large : son chignon dépasse) ----
const u16 gKantoObjectEventPic_MayNormal[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_normal.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_MayBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_MayAcroBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_acro_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_MaySurf[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_surf.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_MayItem[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_item.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_MayVSSeekerBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_vs_seeker_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_MayFish[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_fish.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_MayUnderwater[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_underwater.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_MayWatering[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_watering.png", ".4bpp", "-mwidth 4 -mheight 4");
const u16 gKantoObjectEventPic_MayDecorating[] = INCGFX_U16("graphics/kanto/object_events/pics/people/may_decorating.png", ".4bpp", "-mwidth 2 -mheight 4");

static const struct SpriteFrameImage sKantoPicTable_MayNormal[] = {FRAMES_NORMAL(gKantoObjectEventPic_MayNormal, 4)};
static const struct SpriteFrameImage sKantoPicTable_MayBike[] = {FRAMES_9(gKantoObjectEventPic_MayBike, 4)};
static const struct SpriteFrameImage sKantoPicTable_MayAcroBike[] = {FRAMES_27(gKantoObjectEventPic_MayAcroBike)};
static const struct SpriteFrameImage sKantoPicTable_MaySurf[] = {FRAMES_12(gKantoObjectEventPic_MaySurf, 2)};
static const struct SpriteFrameImage sKantoPicTable_MayItem[] = {FRAMES_9(gKantoObjectEventPic_MayItem, 4)};
static const struct SpriteFrameImage sKantoPicTable_MayVSSeekerBike[] = {
    overworld_frame(gKantoObjectEventPic_MayVSSeekerBike, 4, 4, 0), overworld_frame(gKantoObjectEventPic_MayVSSeekerBike, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_MayVSSeekerBike, 4, 4, 2), overworld_frame(gKantoObjectEventPic_MayVSSeekerBike, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_MayVSSeekerBike, 4, 4, 4), overworld_frame(gKantoObjectEventPic_MayVSSeekerBike, 4, 4, 5),
};
static const struct SpriteFrameImage sKantoPicTable_MayFish[] = {FRAMES_12(gKantoObjectEventPic_MayFish, 4)};
static const struct SpriteFrameImage sKantoPicTable_MayUnderwater[] = {FRAMES_9(gKantoObjectEventPic_MayUnderwater, 4)};
static const struct SpriteFrameImage sKantoPicTable_MayWatering[] = {FRAMES_9(gKantoObjectEventPic_MayWatering, 4)};
static const struct SpriteFrameImage sKantoPicTable_MayDecorating[] = {overworld_frame(gKantoObjectEventPic_MayDecorating, 2, 4, 0)};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayNormal = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 32, 32, PALSLOT_PLAYER, TRACKS_FOOT, sKantoAnimTable_RedGreenNormal, sKantoPicTable_MayNormal, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayBike = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 32, 32, PALSLOT_PLAYER, TRACKS_BIKE_TIRE, sKantoAnimTable_Standard, sKantoPicTable_MayBike, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayAcroBike = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 32, 32, PALSLOT_PLAYER, TRACKS_BIKE_TIRE, sAnimTable_AcroBike, sKantoPicTable_MayAcroBike, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MaySurf = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 16, 32, PALSLOT_PLAYER, TRACKS_NONE, sKantoAnimTable_RedGreenSurf, sKantoPicTable_MaySurf, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayFieldMove = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 32, 32, PALSLOT_PLAYER, TRACKS_FOOT, sKantoAnimTable_RedGreenFieldMove, sKantoPicTable_MayItem, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayVSSeeker = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 32, 32, PALSLOT_PLAYER, TRACKS_FOOT, sKantoAnimTable_RedGreenVSSeeker, sKantoPicTable_MayItem, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayVSSeekerBike = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 32, 32, PALSLOT_PLAYER, TRACKS_BIKE_TIRE, sKantoAnimTable_RedGreenVSSeekerBike, sKantoPicTable_MayVSSeekerBike, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayFish = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 32, 32, PALSLOT_PLAYER, TRACKS_FOOT, sKantoAnimTable_RedGreenFish, sKantoPicTable_MayFish, FALSE);
// Plongée : PALSLOT_NPC_SPECIAL comme MayUnderwater d'Émeraude
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayUnderwater = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER, 32, 32, PALSLOT_NPC_SPECIAL, TRACKS_FOOT, sAnimTable_Standard, sKantoPicTable_MayUnderwater, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayWatering = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 32, 32, PALSLOT_PLAYER, TRACKS_FOOT, sAnimTable_Standard, sKantoPicTable_MayWatering, FALSE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_MayDecorating = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_MAY, 16, 32, PALSLOT_NPC_SPECIAL, TRACKS_FOOT, sAnimTable_Inanimate, sKantoPicTable_MayDecorating, TRUE);

// ---- Red et Leaf : décoration (Base Secrète) ----
const u16 gKantoObjectEventPic_RedDecorating[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_decorating.png", ".4bpp", "-mwidth 2 -mheight 4");
const u16 gKantoObjectEventPic_GreenDecorating[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_decorating.png", ".4bpp", "-mwidth 2 -mheight 4");
static const struct SpriteFrameImage sKantoPicTable_RedDecorating[] = {overworld_frame(gKantoObjectEventPic_RedDecorating, 2, 4, 0)};
static const struct SpriteFrameImage sKantoPicTable_GreenDecorating[] = {overworld_frame(gKantoObjectEventPic_GreenDecorating, 2, 4, 0)};
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedDecorating = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_RED, 16, 32, PALSLOT_NPC_SPECIAL, TRACKS_FOOT, sAnimTable_Inanimate, sKantoPicTable_RedDecorating, TRUE);
const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenDecorating = KANTO_PLAYER_GFX(OBJ_EVENT_PAL_TAG_KANTO_PLAYER_GREEN, 16, 32, PALSLOT_NPC_SPECIAL, TRACKS_FOOT, sAnimTable_Inanimate, sKantoPicTable_GreenDecorating, TRUE);

#undef KANTO_PLAYER_GFX
#undef FRAMES_9
#undef FRAMES_NORMAL
#undef FRAMES_12
#undef FRAMES_27
