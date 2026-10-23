# Graphismes, sauvegarde, cartes

> Généré par `tools/cartographie.py` — ne pas éditer à la main.

## Dossiers `graphics/`

**RF seul** (✓ = un dossier du même nom existe dans `graphics/` ou `graphics/kanto/` de la fusion) :
battle_records, battle_terrain ✓, berry_pouch ✓, fame_checker, field_specials, hall_of_fame ✓, help_system ✓,
item_menu ✓, item_pc, itemfinder ✓, learn_move, main_menu, map_preview ✓, oak_speech, pokemon_special_anim,
quest_log, region_map ✓, script_menu, seagallop, shop_menu, spinda_spots, ss_anne, teachy_tv, tm_case ✓

**Émeraude seul** :
bag, balls, battle_environment, battle_frontier, berries, birch_speech, cable_car, decorations, frontier_pass,
map_popup, picture_frame, pokeblock, pokenav, rayquaza_scene, reset_rtc_screen, rotating_gates, roulette, shop,
starter_choose, trainer_hill, types, wallclock

**Communs** (contenu souvent différent ; les variantes RF importées sont sous `graphics/kanto/`) :
battle_anims, battle_interface (kanto ✓), battle_transitions, berry_blender, berry_crush, berry_fix,
cave_transition, contest, credits (kanto ✓), diploma, dodrio_berry_picking, door_anims, easy_chat,
evolution_scene, field_effects (kanto ✓), fonts (kanto ✓), interface (kanto ✓), intro (kanto ✓), items, link,
mail, misc (kanto ✓), naming_screen (kanto ✓), object_events (kanto ✓), party_menu (kanto ✓),
pokedex (kanto ✓), pokemon (kanto ✓), pokemon_jump, pokemon_storage (kanto ✓), slot_machine,
summary_screen (kanto ✓), text_window (kanto ✓), title_screen (kanto ✓), trade, trainer_card,
trainers (kanto ✓), union_room_chat, unused, weather, wireless_status_screen, wonder_card, wonder_news

**Dans `graphics/kanto/` de la fusion** :
battle_interface, battle_terrain, berry_pouch, credits, field_effects, fonts, hall_of_fame, help_system,
interface, intro, item_menu, itemfinder, map_preview, misc, naming_screen, object_events, party_menu, pokedex,
pokemon, pokemon_ghost, pokemon_storage, region_map, summary_screen, text_window, title_screen, tm_case,
trainers

## Sauvegarde (`include/global.h`)

### SaveBlock1

**RF seul** :
unused_632, questLog, additionalPhrases, unused_348C, rivalName, fameChecker, unused_3A94, route5DayCareMon,
unused_3D24, towerChallengeId, trainerTower

**Émeraude seul** :
mapView, pokeblocks, unused_9C2, berryTrees, secretBases, playerRoomDecorations, playerRoomDecorationPositions,
decorationDesks, decorationChairs, decorationPlants, decorationOrnaments, decorationMats, decorationPosters,
decorationDolls, decorationCushions, tvShows, pokeNews, outbreakPokemonSpecies, outbreakLocationMapNum,
outbreakLocationMapGroup, outbreakPokemonLevel, outbreakUnused1, outbreakUnused2, outbreakPokemonMoves,
outbreakUnused3, outbreakPokemonProbability, outbreakDaysLeft, gabbyAndTyData, unlockedTrendySayings,
contestWinners, linkBattleRecords, unused_3598, trainerHillTimes, lilycoveLady, unused_3D5A, trainerHill,
waldaPhrase

### SaveBlock2

**RF seul** :
unkFlag1, unkFlag2, battleTower, mapView, linkBattleRecords, filler_B20

**Émeraude seul** :
playerApprentice, apprentices, hallRecords1P, hallRecords2P, contestLinkResults, frontier

### SaveBlockKanto (fusion, `include/kanto_save.h`)

magic, saveCounter, flags, vars, rivalName, fameChecker, route5DayCareMon, roamers, trainerRematchStepCounter,
trainerRematches, reserved, checksum

## Cartes (`data/maps/map_groups.json`)

Émeraude : 34 groupes, 518 cartes. Rouge Feu : 43 groupes, 425 cartes. Fusion : 76 groupes, 914 cartes.

Cartes de RF absentes de la fusion (par nom) : 18
NavelRock_1F, NavelRock_Summit, NavelRock_Base, NavelRock_SummitPath_2F, NavelRock_SummitPath_3F,
NavelRock_SummitPath_4F, NavelRock_SummitPath_5F, NavelRock_BasePath_B1F, NavelRock_BasePath_B2F,
NavelRock_BasePath_B3F, NavelRock_BasePath_B4F, NavelRock_BasePath_B5F, NavelRock_BasePath_B6F,
NavelRock_BasePath_B7F, NavelRock_BasePath_B8F, NavelRock_BasePath_B9F, NavelRock_BasePath_B10F,
NavelRock_BasePath_B11F

Cartes de RF de même nom qu'une carte d'Émeraude : 13 (→ Kanto<Nom> = importée sous ce nom ; sinon la fusion n'a que celle d'Émeraude)
BattleColosseum_2P, TradeCenter, RecordCorner, BattleColosseum_4P, UnionRoom,
VictoryRoad_1F → KantoVictoryRoad_1F, SafariZone_North → KantoSafariZone_North, NavelRock_Exterior,
NavelRock_B1F, NavelRock_Fork, BirthIsland_Exterior, BirthIsland_Harbor, NavelRock_Harbor
