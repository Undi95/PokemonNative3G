// PokemonNative3G : sprites de Red/Leaf absents de Rouge Feu (Vélo Cross, arrosoir, plongée, décoration), en style
// Rouge Feu, de Poffin_Case (pack « FRHoenn », PokéCommunity ; tools/sprites_joueur_rf.py). Les 9 premières images
// du Vélo Cross sont le vélo de Rouge Feu. Mêmes images et animations que Brendan/May d'Émeraude (arrosoir et
// plongée : les 9 images de leur table, déroulées), dans la palette du joueur de Rouge Feu (la plongée garde la
// sienne).

const u16 gKantoObjectEventPic_RedAcroBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_acro_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
static const struct SpriteFrameImage sKantoPicTable_RedAcroBike[] = {
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 8),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 9),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 10),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 11),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 12),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 13),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 14),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 15),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 16),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 17),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 18),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 19),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 20),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 21),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 22),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 23),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 24),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 25),
    overworld_frame(gKantoObjectEventPic_RedAcroBike, 4, 4, 26),
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedAcroBike = {
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
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_AcroBike,
    .images = sKantoPicTable_RedAcroBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const u16 gKantoObjectEventPic_RedWatering[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_watering.png", ".4bpp", "-mwidth 4 -mheight 4");
static const struct SpriteFrameImage sKantoPicTable_RedWatering[] = {
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_RedWatering, 4, 4, 8),
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedWatering = {
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
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sKantoPicTable_RedWatering,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const u16 gKantoObjectEventPic_RedUnderwater[] = INCGFX_U16("graphics/kanto/object_events/pics/people/red_underwater.png", ".4bpp", "-mwidth 4 -mheight 4");
static const struct SpriteFrameImage sKantoPicTable_RedUnderwater[] = {
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_RedUnderwater, 4, 4, 8),
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_RedUnderwater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = TRUE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sKantoPicTable_RedUnderwater,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const u16 gKantoObjectEventPic_GreenAcroBike[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_acro_bike.png", ".4bpp", "-mwidth 4 -mheight 4");
static const struct SpriteFrameImage sKantoPicTable_GreenAcroBike[] = {
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 8),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 9),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 10),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 11),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 12),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 13),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 14),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 15),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 16),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 17),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 18),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 19),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 20),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 21),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 22),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 23),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 24),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 25),
    overworld_frame(gKantoObjectEventPic_GreenAcroBike, 4, 4, 26),
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenAcroBike = {
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
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_AcroBike,
    .images = sKantoPicTable_GreenAcroBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const u16 gKantoObjectEventPic_GreenWatering[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_watering.png", ".4bpp", "-mwidth 4 -mheight 4");
static const struct SpriteFrameImage sKantoPicTable_GreenWatering[] = {
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_GreenWatering, 4, 4, 8),
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenWatering = {
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
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sKantoPicTable_GreenWatering,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const u16 gKantoObjectEventPic_GreenUnderwater[] = INCGFX_U16("graphics/kanto/object_events/pics/people/green_underwater.png", ".4bpp", "-mwidth 4 -mheight 4");
static const struct SpriteFrameImage sKantoPicTable_GreenUnderwater[] = {
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 0),
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 1),
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 2),
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 3),
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 4),
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 5),
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 6),
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 7),
    overworld_frame(gKantoObjectEventPic_GreenUnderwater, 4, 4, 8),
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_GreenUnderwater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = TRUE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sKantoPicTable_GreenUnderwater,
    .affineAnims = gDummySpriteAffineAnimTable,
};

// PokemonNative3G : autel de Celebi (Forêt Baies), dessiné pour la fusion dans la palette des PNJ de Kanto
// (graphics/fusion/object_events/shrine.png ; même format que le panneau d'arène)
const u16 gKantoObjectEventPic_Shrine[] = INCGFX_U16("graphics/fusion/object_events/shrine.png", ".4bpp");
static const struct SpriteFrameImage sKantoPicTable_Shrine[] = {
    overworld_frame(gKantoObjectEventPic_Shrine, 2, 4, 0),
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_Shrine = {
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
    .images = sKantoPicTable_Shrine,
    .affineAnims = gDummySpriteAffineAnimTable,
};

// PokemonNative3G : météorite de Jirachi (Chutes Météore, Hoenn), dessinée pour la fusion dans la palette
// des PNJ d'Émeraude (NPC_1, comme le rocher cassable) : graphics/fusion/object_events/meteorite.png
const u16 gKantoObjectEventPic_FusionMeteorite[] = INCGFX_U16("graphics/fusion/object_events/meteorite.png", ".4bpp");
static const struct SpriteFrameImage sKantoPicTable_FusionMeteorite[] = {
    overworld_frame(gKantoObjectEventPic_FusionMeteorite, 2, 2, 0),
};

const struct ObjectEventGraphicsInfo gKantoObjectEventGraphicsInfo_FusionMeteorite = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_1,
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
    .images = sKantoPicTable_FusionMeteorite,
    .affineAnims = gDummySpriteAffineAnimTable,
};
