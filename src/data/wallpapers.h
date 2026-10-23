enum {
    WALLPAPER_FOREST,
    WALLPAPER_CITY,
    WALLPAPER_DESERT,
    WALLPAPER_SAVANNA,
    WALLPAPER_CRAG,
    WALLPAPER_VOLCANO,
    WALLPAPER_SNOW,
    WALLPAPER_CAVE,
    WALLPAPER_BEACH,
    WALLPAPER_SEAFLOOR,
    WALLPAPER_RIVER,
    WALLPAPER_SKY,
    WALLPAPER_POLKADOT,
    WALLPAPER_POKECENTER,
    WALLPAPER_MACHINE,
    WALLPAPER_PLAIN,
    WALLPAPER_FRIENDS, // The one received as a gift from Walda's parents.
    // PokemonNative3G : fonds de Rouge Feu (dessins différents de ceux d'Émeraude)
    WALLPAPER_KANTO_FOREST,
    WALLPAPER_KANTO_CITY,
    WALLPAPER_KANTO_DESERT,
    WALLPAPER_KANTO_SAVANNA,
    WALLPAPER_KANTO_CRAG,
    WALLPAPER_KANTO_VOLCANO,
    WALLPAPER_KANTO_SNOW,
    WALLPAPER_KANTO_CAVE,
    WALLPAPER_KANTO_BEACH,
    WALLPAPER_KANTO_SEAFLOOR,
    WALLPAPER_KANTO_RIVER,
    WALLPAPER_KANTO_SKY,
    WALLPAPER_KANTO_STARS,
    WALLPAPER_KANTO_POKECENTER,
    WALLPAPER_KANTO_TILES,
    WALLPAPER_KANTO_SIMPLE,
    WALLPAPER_COUNT
};
#define MAX_DEFAULT_WALLPAPER WALLPAPER_SAVANNA

static const u16 sWallpaperPalettes_Forest[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/forest/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/forest/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Forest[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/forest/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Forest[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/forest/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_City[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/city/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/city/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_City[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/city/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_City[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/city/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Desert[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/desert/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/desert/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Desert[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/desert/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Desert[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/desert/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Savanna[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/savanna/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/savanna/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Savanna[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/savanna/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Savanna[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/savanna/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Crag[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/crag/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/crag/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Crag[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/crag/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Crag[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/crag/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Volcano[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/volcano/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/volcano/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Volcano[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/volcano/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Volcano[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/volcano/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Snow[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/snow/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/snow/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Snow[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/snow/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Snow[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/snow/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Cave[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/cave/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/cave/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Cave[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/cave/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Cave[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/cave/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Beach[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/beach/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/beach/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Beach[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/beach/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Beach[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/beach/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Seafloor[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/seafloor/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/seafloor/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Seafloor[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/seafloor/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Seafloor[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/seafloor/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_River[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/river/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/river/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_River[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/river/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_River[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/river/tilemap.bin", ".lz");
static const u16 sWallpaperPalettes_Sky[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/sky/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/sky/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Sky[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/sky/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Sky[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/sky/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_PolkaDot[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/polkadot/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/polkadot/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_PolkaDot[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/polkadot/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_PolkaDot[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/polkadot/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Pokecenter[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/pokecenter/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/pokecenter/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Pokecenter[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/pokecenter/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Pokecenter[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/pokecenter/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Machine[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/machine/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/machine/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Machine[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/machine/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Machine[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/machine/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Plain[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/plain/frame.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/plain/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Plain[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/plain/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Plain[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/plain/tilemap.bin", ".lz");

// 12x18 tilemap
static const u32 sWallpaperTilemap_Unused[] = INCBIN_U32("graphics/pokemon_storage/wallpapers/unused.bin");


// Rouge Feu (pokemon_storage_system_graphics.c)
static const u16 sKantoWallpaperPalettes_Forest[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/forest/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Forest[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/forest/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Forest[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/forest/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_City[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/city/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_City[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/city/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_City[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/city/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Desert[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/desert/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Desert[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/desert/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Desert[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/desert/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Savanna[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/savanna/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Savanna[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/savanna/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Savanna[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/savanna/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Crag[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/crag/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Crag[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/crag/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Crag[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/crag/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Volcano[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/volcano/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Volcano[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/volcano/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Volcano[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/volcano/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Snow[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/snow/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Snow[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/snow/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Snow[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/snow/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Cave[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/cave/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Cave[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/cave/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Cave[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/cave/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Beach[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/beach/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Beach[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/beach/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Beach[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/beach/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Seafloor[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/seafloor/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Seafloor[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/seafloor/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Seafloor[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/seafloor/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_River[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/river/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_River[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/river/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_River[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/river/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Sky[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/sky/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Sky[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/sky/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Sky[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/sky/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Stars[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/stars/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Stars[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/stars/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Stars[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/stars/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Pokecenter[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/pokecenter/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Pokecenter[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/pokecenter/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Pokecenter[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/pokecenter/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Tiles[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/tiles/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Tiles[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/tiles/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Tiles[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/tiles/tilemap.bin", ".lz");
static const u16 sKantoWallpaperPalettes_Simple[][16] = INCGFX_U16("graphics/kanto/pokemon_storage/wallpapers/simple/tiles.png", ".gbapal");
static const u32 sKantoWallpaperTiles_Simple[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/simple/tiles.png", ".4bpp.lz");
static const u32 sKantoWallpaperTilemap_Simple[] = INCGFX_U32("graphics/kanto/pokemon_storage/wallpapers/simple/tilemap.bin", ".lz");

// Shadow color, text color
static const u16 sBoxTitleColors[WALLPAPER_COUNT][2] =
{
    [WALLPAPER_FOREST]     = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_CITY]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_DESERT]     = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SAVANNA]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_CRAG]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_VOLCANO]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SNOW]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_CAVE]       = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_BEACH]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SEAFLOOR]   = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_RIVER]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_SKY]        = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_POLKADOT]   = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_POKECENTER] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_MACHINE]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_PLAIN]      = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_FRIENDS]    = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_FOREST] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_CITY] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_DESERT] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_SAVANNA] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_CRAG] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_VOLCANO] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_SNOW] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_CAVE] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_BEACH] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_SEAFLOOR] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_RIVER] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_SKY] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_STARS] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_POKECENTER] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_TILES] = {RGB(7, 7, 7), RGB_WHITE},
    [WALLPAPER_KANTO_SIMPLE] = {RGB(7, 7, 7), RGB_WHITE}

};

#define WALLPAPER_ENTRY(name) {sWallpaperTiles_##name, sWallpaperTilemap_##name, sWallpaperPalettes_##name[0]}
// A few wallpapers are not defined in this file
#define WALLPAPER_ENTRY_G(name) {gWallpaperTiles_##name, gWallpaperTilemap_##name, gWallpaperPalettes_##name[0]}

static const struct Wallpaper sWallpapers[WALLPAPER_COUNT] = // [WALLPAPER_FRIENDS] : sWaldaWallpapers
{
    [WALLPAPER_FOREST]     = WALLPAPER_ENTRY(Forest),
    [WALLPAPER_CITY]       = WALLPAPER_ENTRY(City),
    [WALLPAPER_DESERT]     = WALLPAPER_ENTRY(Desert),
    [WALLPAPER_SAVANNA]    = WALLPAPER_ENTRY(Savanna),
    [WALLPAPER_CRAG]       = WALLPAPER_ENTRY(Crag),
    [WALLPAPER_VOLCANO]    = WALLPAPER_ENTRY(Volcano),
    [WALLPAPER_SNOW]       = WALLPAPER_ENTRY(Snow),
    [WALLPAPER_CAVE]       = WALLPAPER_ENTRY(Cave),
    [WALLPAPER_BEACH]      = WALLPAPER_ENTRY(Beach),
    [WALLPAPER_SEAFLOOR]   = WALLPAPER_ENTRY(Seafloor),
    [WALLPAPER_RIVER]      = WALLPAPER_ENTRY(River),
    [WALLPAPER_SKY]        = WALLPAPER_ENTRY(Sky),
    [WALLPAPER_POLKADOT]   = WALLPAPER_ENTRY(PolkaDot),
    [WALLPAPER_POKECENTER] = WALLPAPER_ENTRY(Pokecenter),
    [WALLPAPER_MACHINE]    = WALLPAPER_ENTRY(Machine),
    [WALLPAPER_PLAIN]      = WALLPAPER_ENTRY(Plain),
    [WALLPAPER_KANTO_FOREST] = {sKantoWallpaperTiles_Forest, sKantoWallpaperTilemap_Forest, sKantoWallpaperPalettes_Forest[0]},
    [WALLPAPER_KANTO_CITY] = {sKantoWallpaperTiles_City, sKantoWallpaperTilemap_City, sKantoWallpaperPalettes_City[0]},
    [WALLPAPER_KANTO_DESERT] = {sKantoWallpaperTiles_Desert, sKantoWallpaperTilemap_Desert, sKantoWallpaperPalettes_Desert[0]},
    [WALLPAPER_KANTO_SAVANNA] = {sKantoWallpaperTiles_Savanna, sKantoWallpaperTilemap_Savanna, sKantoWallpaperPalettes_Savanna[0]},
    [WALLPAPER_KANTO_CRAG] = {sKantoWallpaperTiles_Crag, sKantoWallpaperTilemap_Crag, sKantoWallpaperPalettes_Crag[0]},
    [WALLPAPER_KANTO_VOLCANO] = {sKantoWallpaperTiles_Volcano, sKantoWallpaperTilemap_Volcano, sKantoWallpaperPalettes_Volcano[0]},
    [WALLPAPER_KANTO_SNOW] = {sKantoWallpaperTiles_Snow, sKantoWallpaperTilemap_Snow, sKantoWallpaperPalettes_Snow[0]},
    [WALLPAPER_KANTO_CAVE] = {sKantoWallpaperTiles_Cave, sKantoWallpaperTilemap_Cave, sKantoWallpaperPalettes_Cave[0]},
    [WALLPAPER_KANTO_BEACH] = {sKantoWallpaperTiles_Beach, sKantoWallpaperTilemap_Beach, sKantoWallpaperPalettes_Beach[0]},
    [WALLPAPER_KANTO_SEAFLOOR] = {sKantoWallpaperTiles_Seafloor, sKantoWallpaperTilemap_Seafloor, sKantoWallpaperPalettes_Seafloor[0]},
    [WALLPAPER_KANTO_RIVER] = {sKantoWallpaperTiles_River, sKantoWallpaperTilemap_River, sKantoWallpaperPalettes_River[0]},
    [WALLPAPER_KANTO_SKY] = {sKantoWallpaperTiles_Sky, sKantoWallpaperTilemap_Sky, sKantoWallpaperPalettes_Sky[0]},
    [WALLPAPER_KANTO_STARS] = {sKantoWallpaperTiles_Stars, sKantoWallpaperTilemap_Stars, sKantoWallpaperPalettes_Stars[0]},
    [WALLPAPER_KANTO_POKECENTER] = {sKantoWallpaperTiles_Pokecenter, sKantoWallpaperTilemap_Pokecenter, sKantoWallpaperPalettes_Pokecenter[0]},
    [WALLPAPER_KANTO_TILES] = {sKantoWallpaperTiles_Tiles, sKantoWallpaperTilemap_Tiles, sKantoWallpaperPalettes_Tiles[0]},
    [WALLPAPER_KANTO_SIMPLE] = {sKantoWallpaperTiles_Simple, sKantoWallpaperTilemap_Simple, sKantoWallpaperPalettes_Simple[0]},
};

static const u8 sArrow_Gfx[] = INCGFX_U8("graphics/pokemon_storage/arrow.png", ".4bpp");

static const u16 sWallpaperPalettes_Zigzagoon[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame1.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/zigzagoon/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Zigzagoon[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/zigzagoon/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Zigzagoon[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/zigzagoon/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Screen[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame1.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/screen/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Screen[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/screen/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Screen[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/screen/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Diagonal[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame1.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/diagonal/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Diagonal[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/diagonal/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Diagonal[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/diagonal/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Block[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/block/bg.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/block/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Block[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/block/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Block[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/block/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Pokecenter2[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/pokecenter2/bg.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/pokecenter2/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Pokecenter2[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/pokecenter2/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Pokecenter2[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/pokecenter2/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Frame[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/frame/bg.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/frame/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Frame[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/frame/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Frame[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/frame/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Blank[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame1.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/zigzagoon/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Blank[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/blank/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Blank[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/blank/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Circles[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame2.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/circles/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Circles[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/circles/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Circles[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/circles/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Azumarill[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame2.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/azumarill/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Azumarill[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/azumarill/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Azumarill[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/azumarill/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Pikachu[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame2.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/pikachu/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Pikachu[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/pikachu/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Pikachu[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/pikachu/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Legendary[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame2.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/legendary/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Legendary[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/legendary/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Legendary[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/legendary/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Dusclops[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame2.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/dusclops/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Dusclops[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/dusclops/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Dusclops[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/dusclops/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Ludicolo[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame2.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/ludicolo/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Ludicolo[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/ludicolo/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Ludicolo[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/ludicolo/tilemap.bin", ".lz");

static const u16 sWallpaperPalettes_Whiscash[][16] =
{
    INCGFX_U16("graphics/pokemon_storage/wallpapers/friends_frame2.png", ".gbapal"),
    INCGFX_U16("graphics/pokemon_storage/wallpapers/whiscash/bg.png", ".gbapal"),
};
static const u32 sWallpaperTiles_Whiscash[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/whiscash/tiles.4bpp", ".lz");
static const u32 sWallpaperTilemap_Whiscash[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/whiscash/tilemap.bin", ".lz");

static const u32 sWallpaperIcon_Aqua[]         = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/aqua.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Heart[]        = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/heart.png", ".4bpp.lz");
static const u32 sWallpaperIcon_FiveStar[]     = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/five_star.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Brick[]        = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/brick.png", ".4bpp.lz");
static const u32 sWallpaperIcon_FourStar[]     = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/four_star.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Asterisk[]     = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/asterisk.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Dot[]          = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/dot.png", ".4bpp.lz");
static const u32 sWallpaperIcon_LineCircle[]   = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/line_circle.png", ".4bpp.lz");
static const u32 sWallpaperIcon_PokeBall[]     = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/pokeball.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Maze[]         = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/maze.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Footprint[]    = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/footprint.png", ".4bpp.lz");
static const u32 sWallpaperIcon_BigAsterisk[]  = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/big_asterisk.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Circle[]       = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/circle.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Koffing[]      = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/koffing.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Ribbon[]       = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/ribbon.png", ".4bpp.lz");
static const u32 sWallpaperIcon_FourCircles[]  = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/four_circles.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Lotad[]        = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/lotad.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Crystal[]      = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/crystal.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Pichu[]        = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/pichu.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Diglett[]      = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/diglett.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Luvdisc[]      = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/luvdisc.png", ".4bpp.lz");
static const u32 sWallpaperIcon_StarInCircle[] = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/star_in_circle.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Spinda[]       = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/spinda.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Latis[]        = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/latis.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Minun[]        = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/minun.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Togepi[]       = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/togepi.png", ".4bpp.lz");
static const u32 sWallpaperIcon_Magma[]        = INCGFX_U32("graphics/pokemon_storage/wallpapers/icons/magma.png", ".4bpp.lz");

static const struct Wallpaper sWaldaWallpapers[] =
{
    WALLPAPER_ENTRY(Zigzagoon),
    WALLPAPER_ENTRY(Screen),
    WALLPAPER_ENTRY_G(Horizontal),
    WALLPAPER_ENTRY(Diagonal),
    WALLPAPER_ENTRY(Block),
    WALLPAPER_ENTRY_G(Ribbon),
    WALLPAPER_ENTRY(Pokecenter2),
    WALLPAPER_ENTRY(Frame),
    WALLPAPER_ENTRY(Blank),
    WALLPAPER_ENTRY(Circles),
    WALLPAPER_ENTRY(Azumarill),
    WALLPAPER_ENTRY(Pikachu),
    WALLPAPER_ENTRY(Legendary),
    WALLPAPER_ENTRY(Dusclops),
    WALLPAPER_ENTRY(Ludicolo),
    WALLPAPER_ENTRY(Whiscash),
};

static const u32 *const sWaldaWallpaperIcons[] =
{
    sWallpaperIcon_Aqua,
    sWallpaperIcon_Heart,
    sWallpaperIcon_FiveStar,
    sWallpaperIcon_Brick,
    sWallpaperIcon_FourStar,
    sWallpaperIcon_Asterisk,
    sWallpaperIcon_Dot,
    gWallpaperIcon_Cross,
    sWallpaperIcon_LineCircle,
    sWallpaperIcon_PokeBall,
    sWallpaperIcon_Maze,
    sWallpaperIcon_Footprint,
    sWallpaperIcon_BigAsterisk,
    sWallpaperIcon_Circle,
    sWallpaperIcon_Koffing,
    sWallpaperIcon_Ribbon,
    gWallpaperIcon_Bolt,
    sWallpaperIcon_FourCircles,
    sWallpaperIcon_Lotad,
    sWallpaperIcon_Crystal,
    sWallpaperIcon_Pichu,
    sWallpaperIcon_Diglett,
    sWallpaperIcon_Luvdisc,
    sWallpaperIcon_StarInCircle,
    sWallpaperIcon_Spinda,
    sWallpaperIcon_Latis,
    gWallpaperIcon_Plusle,
    sWallpaperIcon_Minun,
    sWallpaperIcon_Togepi,
    sWallpaperIcon_Magma,
};
