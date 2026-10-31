// Généré par tools/day_night_lights.py : couleurs de vitre (masque par palette) éclairées la nuit
extern const struct Tileset gTileset_BattleFrontierOutsideEast;
extern const struct Tileset gTileset_BattleFrontierOutsideWest;
extern const struct Tileset gTileset_Dewford;
extern const struct Tileset gTileset_EverGrande;
extern const struct Tileset gTileset_Facility;
extern const struct Tileset gTileset_Fortree;
extern const struct Tileset gTileset_General;
extern const struct Tileset gTileset_KantoCeladonCity;
extern const struct Tileset gTileset_KantoCeruleanCity;
extern const struct Tileset gTileset_KantoCinnabarIsland;
extern const struct Tileset gTileset_KantoFuchsiaCity;
extern const struct Tileset gTileset_KantoGeneral;
extern const struct Tileset gTileset_KantoIndigoPlateau;
extern const struct Tileset gTileset_KantoLavenderTown;
extern const struct Tileset gTileset_KantoPalletTown;
extern const struct Tileset gTileset_KantoPewterCity;
extern const struct Tileset gTileset_KantoSaffronCity;
extern const struct Tileset gTileset_KantoSeviiIslands123;
extern const struct Tileset gTileset_KantoSeviiIslands45;
extern const struct Tileset gTileset_KantoSeviiIslands67;
extern const struct Tileset gTileset_KantoVermilionCity;
extern const struct Tileset gTileset_KantoViridianCity;
extern const struct Tileset gTileset_Lavaridge;
extern const struct Tileset gTileset_Lilycove;
extern const struct Tileset gTileset_Mauville;
extern const struct Tileset gTileset_Mossdeep;
extern const struct Tileset gTileset_Pacifidlog;
extern const struct Tileset gTileset_Petalburg;
extern const struct Tileset gTileset_Rustboro;
extern const struct Tileset gTileset_Slateport;
extern const struct Tileset gTileset_Sootopolis;

static const struct DayNightLights sDayNightLights[] =
{
    { &gTileset_BattleFrontierOutsideEast, { [6] = 0x0610, [7] = 0x0610, [9] = 0x0600, [10] = 0x0600, [11] = 0x0010 } },
    { &gTileset_BattleFrontierOutsideWest, { [6] = 0x0610, [7] = 0x0610, [9] = 0x0600, [10] = 0x0600, [11] = 0x0010 } },
    { &gTileset_Dewford, { [6] = 0x0610, [7] = 0x0610, [10] = 0x0600, [11] = 0x0010 } },
    { &gTileset_EverGrande, { [8] = 0x0200, [9] = 0x0200 } },
    { &gTileset_Facility, { [6] = 0x0008, [7] = 0x4000, [9] = 0x4008 } },
    { &gTileset_Fortree, { [8] = 0x0600 } },
    { &gTileset_General, { [1] = 0x0400, [5] = 0x0600 } },
    { &gTileset_KantoCeladonCity, { [8] = 0x20E0, [10] = 0x0400 } },
    { &gTileset_KantoCeruleanCity, { [8] = 0x0018, [10] = 0x0300, [12] = 0x0C00 } },
    { &gTileset_KantoCinnabarIsland, { [8] = 0x0020, [9] = 0x0200 } },
    { &gTileset_KantoFuchsiaCity, { [8] = 0x1800 } },
    { &gTileset_KantoGeneral, { [3] = 0x0C00 } },
    { &gTileset_KantoIndigoPlateau, { [10] = 0x1000 } },
    { &gTileset_KantoLavenderTown, { [10] = 0x0100, [11] = 0xE100 } },
    { &gTileset_KantoPalletTown, { [8] = 0x0300, [9] = 0x0300, [10] = 0x0700 } },
    { &gTileset_KantoPewterCity, { [8] = 0x0300, [9] = 0x0300, [11] = 0x0060 } },
    { &gTileset_KantoSaffronCity, { [9] = 0x6000, [10] = 0x6000, [12] = 0x8000 } },
    { &gTileset_KantoSeviiIslands123, { [9] = 0x0006, [11] = 0x0300 } },
    { &gTileset_KantoSeviiIslands45, { [9] = 0x4000 } },
    { &gTileset_KantoSeviiIslands67, { [9] = 0xC080 } },
    { &gTileset_KantoVermilionCity, { [9] = 0x4200 } },
    { &gTileset_KantoViridianCity, { [8] = 0x0038, [10] = 0x0018, [12] = 0x1000 } },
    { &gTileset_Lavaridge, { [7] = 0x0400, [8] = 0x0600 } },
    { &gTileset_Lilycove, { [8] = 0x060C, [9] = 0x0600, [10] = 0x1000 } },
    { &gTileset_Mauville, { [6] = 0x0200, [7] = 0x8000, [8] = 0x0002, [9] = 0x01C0, [10] = 0x0414, [11] = 0x1180, [12] = 0x1000 } },
    { &gTileset_Mossdeep, { [8] = 0x0600 } },
    { &gTileset_Pacifidlog, { [7] = 0x1E00, [8] = 0x0060, [9] = 0x8000 } },
    { &gTileset_Petalburg, { [6] = 0x0200, [8] = 0x0200, [9] = 0x0600, [10] = 0x0600 } },
    { &gTileset_Rustboro, { [8] = 0x0400, [9] = 0x0600, [10] = 0x0400, [11] = 0x0400 } },
    { &gTileset_Slateport, { [8] = 0x0600, [9] = 0x1800, [10] = 0x0400, [11] = 0x0810 } },
    { &gTileset_Sootopolis, { [8] = 0x0F00, [9] = 0x1E06, [11] = 0x1E00 } },
};
