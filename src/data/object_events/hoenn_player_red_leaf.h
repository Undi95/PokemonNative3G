// PokemonNative3G : Red et Leaf en style Émeraude, le joueur à Hoenn avec Options > PERSO (à Kanto : leurs sprites
// de Rouge Feu). Feuilles dessinées à la main sur les poses de Brice et Flora d'Émeraude, avec la tête et la tenue de
// Red/Leaf d'Émeraude (graphics/object_events/pics/people/red.png, leaf.png : leur marche) ; tools/sprites_joueur_em.py.
// Mêmes images, animations, tailles et emplacements de palette que les sprites du joueur d'Émeraude
// (object_event_graphics_info.h) ; palette red_leaf.pal sous OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF.

#define HOENN_PLAYER_GFX(_palTag, _reflTag, _disableRefl, _size, _w, _slot, _inanimate, _tracks, _anims, _images) { \
    .tileTag = TAG_NONE,                                                                    \
    .paletteTag = _palTag,                                                                  \
    .reflectionPaletteTag = _reflTag,                                                       \
    .size = _size,                                                                          \
    .width = _w,                                                                            \
    .height = 32,                                                                           \
    .paletteSlot = _slot,                                                                   \
    .shadowSize = SHADOW_SIZE_M,                                                            \
    .inanimate = _inanimate,                                                                \
    .disableReflectionPaletteLoad = _disableRefl,                                           \
    .tracks = _tracks,                                                                      \
    .oam = (_w) == 32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_16x32,            \
    .subspriteTables = (_w) == 32 ? sOamTables_32x32 : sOamTables_16x32,                    \
    .anims = _anims,                                                                        \
    .images = _images,                                                                      \
    .affineAnims = gDummySpriteAffineAnimTable,                                             \
}

// Les états du joueur d'Émeraude : comme gObjectEventGraphicsInfo_Brendan* et May* (Flora : plongée en
// PALSLOT_NPC_SPECIAL)
#define HOENN_PLAYER_GFX_SET(_name, _underwaterSlot)                                                                     \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##Normal = HOENN_PLAYER_GFX(                     \
    OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF, OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION, FALSE, 512, 16, PALSLOT_PLAYER, FALSE,   \
    TRACKS_FOOT, sAnimTable_BrendanMayNormal, sHoennPicTable_##_name##Normal);                                            \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##MachBike = HOENN_PLAYER_GFX(                   \
    OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF, OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION, FALSE, 512, 32, PALSLOT_PLAYER, FALSE,   \
    TRACKS_BIKE_TIRE, sAnimTable_Standard, sHoennPicTable_##_name##MachBike);                                             \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##AcroBike = HOENN_PLAYER_GFX(                   \
    OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF, OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION, FALSE, 512, 32, PALSLOT_PLAYER, FALSE,   \
    TRACKS_BIKE_TIRE, sAnimTable_AcroBike, sHoennPicTable_##_name##AcroBike);                                             \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##Surfing = HOENN_PLAYER_GFX(                    \
    OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF, OBJ_EVENT_PAL_TAG_NONE, TRUE, 512, 32, PALSLOT_PLAYER, FALSE,                \
    TRACKS_FOOT, sAnimTable_Surfing, sHoennPicTable_##_name##Surfing);                                                    \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##FieldMove = HOENN_PLAYER_GFX(                  \
    OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF, OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION, FALSE, 512, 32, PALSLOT_PLAYER, FALSE,   \
    TRACKS_FOOT, sAnimTable_FieldMove, sHoennPicTable_##_name##FieldMove);                                                \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##Fishing = HOENN_PLAYER_GFX(                    \
    OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF, OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION, FALSE, 512, 32, PALSLOT_PLAYER, FALSE,   \
    TRACKS_FOOT, sAnimTable_Fishing, sHoennPicTable_##_name##Fishing);                                                    \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##Underwater = HOENN_PLAYER_GFX(                 \
    OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER, OBJ_EVENT_PAL_TAG_NONE, TRUE, 512, 32, _underwaterSlot, FALSE,                  \
    TRACKS_FOOT, sAnimTable_Standard, sHoennPicTable_##_name##Underwater);                                                \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##Watering = HOENN_PLAYER_GFX(                   \
    OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF, OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION, FALSE, 512, 32, PALSLOT_PLAYER, FALSE,   \
    TRACKS_FOOT, sAnimTable_Standard, sHoennPicTable_##_name##Watering);                                                  \
const struct ObjectEventGraphicsInfo gHoennObjectEventGraphicsInfo_##_name##Decorating = HOENN_PLAYER_GFX(                 \
    OBJ_EVENT_PAL_TAG_HOENN_PLAYER_RED_LEAF, OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION, FALSE, 256, 16, PALSLOT_NPC_SPECIAL, TRUE, \
    TRACKS_FOOT, sAnimTable_Inanimate, sHoennPicTable_##_name##Decorating);

// Les tables d'images d'Émeraude (object_event_pic_tables.h) : marche puis course ; surf, plongée et arrosoir
// réutilisent leurs images comme celles de Brice
#define HOENN_PLAYER_PIC_TABLES(_name, _walk)                                                                            \
static const struct SpriteFrameImage sHoennPicTable_##_name##Normal[] = {                                                 \
    overworld_frame(_walk, 2, 4, 0), overworld_frame(_walk, 2, 4, 1), overworld_frame(_walk, 2, 4, 2),                   \
    overworld_frame(_walk, 2, 4, 3), overworld_frame(_walk, 2, 4, 4), overworld_frame(_walk, 2, 4, 5),                   \
    overworld_frame(_walk, 2, 4, 6), overworld_frame(_walk, 2, 4, 7), overworld_frame(_walk, 2, 4, 8),                   \
    overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 2), overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 3), \
    overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 4), overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 5), \
    overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 6), overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 7), \
    overworld_frame(gHoennObjectEventPic_##_name##Running, 2, 4, 8),                                                     \
};                                                                                                                       \
static const struct SpriteFrameImage sHoennPicTable_##_name##MachBike[] = {                                               \
    overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 2), overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 3), \
    overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 4), overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 5), \
    overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 6), overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 7), \
    overworld_frame(gHoennObjectEventPic_##_name##MachBike, 4, 4, 8),                                                    \
};                                                                                                                       \
static const struct SpriteFrameImage sHoennPicTable_##_name##AcroBike[] = {                                               \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 2), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 3), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 4), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 5), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 6), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 7), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 8), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 9), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 10), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 11), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 12), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 13), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 14), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 15), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 16), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 17), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 18), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 19), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 20), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 21), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 22), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 23), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 24), overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 25), \
    overworld_frame(gHoennObjectEventPic_##_name##AcroBike, 4, 4, 26),                                                   \
};                                                                                                                       \
static const struct SpriteFrameImage sHoennPicTable_##_name##Surfing[] = {                                                \
    overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 2), \
    overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 4), overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 0), \
    overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 2), \
    overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 2), overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 4), \
    overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 4), overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 3), overworld_frame(gHoennObjectEventPic_##_name##Surfing, 4, 4, 5), \
};                                                                                                                       \
static const struct SpriteFrameImage sHoennPicTable_##_name##FieldMove[] = {                                              \
    overworld_frame(gHoennObjectEventPic_##_name##FieldMove, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##FieldMove, 4, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##FieldMove, 4, 4, 2), overworld_frame(gHoennObjectEventPic_##_name##FieldMove, 4, 4, 3), \
    overworld_frame(gHoennObjectEventPic_##_name##FieldMove, 4, 4, 4),                                                   \
};                                                                                                                       \
static const struct SpriteFrameImage sHoennPicTable_##_name##Fishing[] = {                                                \
    overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 2), overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 3), \
    overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 4), overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 5), \
    overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 6), overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 7), \
    overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 8), overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 9), \
    overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 10), overworld_frame(gHoennObjectEventPic_##_name##Fishing, 4, 4, 11), \
};                                                                                                                       \
static const struct SpriteFrameImage sHoennPicTable_##_name##Underwater[] = {                                             \
    overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 2), overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 0), \
    overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 1), overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 2), \
    overworld_frame(gHoennObjectEventPic_##_name##Underwater, 4, 4, 2),                                                  \
};                                                                                                                       \
static const struct SpriteFrameImage sHoennPicTable_##_name##Watering[] = {                                               \
    overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 0), overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 2), \
    overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 4), overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 1), \
    overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 1), overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 3), \
    overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 3), overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 5), \
    overworld_frame(gHoennObjectEventPic_##_name##Watering, 4, 4, 5),                                                    \
};                                                                                                                       \
static const struct SpriteFrameImage sHoennPicTable_##_name##Decorating[] = {                                             \
    overworld_frame(gHoennObjectEventPic_##_name##Decorating, 2, 4, 0),                                                  \
};

const u16 gHoennObjectEventPal_RedLeafReflection[] = INCGFX_U16("graphics/object_events/palettes/red_leaf_reflection.pal", ".gbapal");

// ---- Red ---- (marche : gObjectEventPic_Red d'Émeraude)
const u32 gHoennObjectEventPic_RedRunning[] = INCGFX_U32("graphics/object_events/pics/people/red/running.png", ".4bpp", "-mwidth 2 -mheight 4");
const u32 gHoennObjectEventPic_RedMachBike[] = INCGFX_U32("graphics/object_events/pics/people/red/mach_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_RedAcroBike[] = INCGFX_U32("graphics/object_events/pics/people/red/acro_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_RedSurfing[] = INCGFX_U32("graphics/object_events/pics/people/red/surfing.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_RedFieldMove[] = INCGFX_U32("graphics/object_events/pics/people/red/field_move.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_RedFishing[] = INCGFX_U32("graphics/object_events/pics/people/red/fishing.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_RedUnderwater[] = INCGFX_U32("graphics/object_events/pics/people/red/underwater.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_RedWatering[] = INCGFX_U32("graphics/object_events/pics/people/red/watering.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_RedDecorating[] = INCGFX_U32("graphics/object_events/pics/people/red/decorating.png", ".4bpp");

// ---- Leaf ---- (marche : leaf.png d'Émeraude sans les pointes rouges du bord du chapeau, un pixel isolé de chaque
// côté ; la Leaf PNJ d'Émeraude garde gObjectEventPic_Leaf)
const u32 gHoennObjectEventPic_LeafWalking[] = INCGFX_U32("graphics/object_events/pics/people/leaf/walking.png", ".4bpp", "-mwidth 2 -mheight 4");
const u32 gHoennObjectEventPic_LeafRunning[] = INCGFX_U32("graphics/object_events/pics/people/leaf/running.png", ".4bpp", "-mwidth 2 -mheight 4");
const u32 gHoennObjectEventPic_LeafMachBike[] = INCGFX_U32("graphics/object_events/pics/people/leaf/mach_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_LeafAcroBike[] = INCGFX_U32("graphics/object_events/pics/people/leaf/acro_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_LeafSurfing[] = INCGFX_U32("graphics/object_events/pics/people/leaf/surfing.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_LeafFieldMove[] = INCGFX_U32("graphics/object_events/pics/people/leaf/field_move.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_LeafFishing[] = INCGFX_U32("graphics/object_events/pics/people/leaf/fishing.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_LeafUnderwater[] = INCGFX_U32("graphics/object_events/pics/people/leaf/underwater.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_LeafWatering[] = INCGFX_U32("graphics/object_events/pics/people/leaf/watering.png", ".4bpp", "-mwidth 4 -mheight 4");
const u32 gHoennObjectEventPic_LeafDecorating[] = INCGFX_U32("graphics/object_events/pics/people/leaf/decorating.png", ".4bpp");

HOENN_PLAYER_PIC_TABLES(Red, gObjectEventPic_Red)
HOENN_PLAYER_PIC_TABLES(Leaf, gHoennObjectEventPic_LeafWalking)

HOENN_PLAYER_GFX_SET(Red, PALSLOT_PLAYER)
HOENN_PLAYER_GFX_SET(Leaf, PALSLOT_NPC_SPECIAL)

#undef HOENN_PLAYER_GFX
#undef HOENN_PLAYER_GFX_SET
#undef HOENN_PLAYER_PIC_TABLES
