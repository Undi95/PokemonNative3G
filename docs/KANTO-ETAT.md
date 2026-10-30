# Import de Kanto — état et reprise (2026-10-19)

## Fait
- Émeraude FR natif Windows/Linux (merge port pokeemerald-native), build Docker (`docker/build.sh`, `MAKEFLAGS_EXTRA="KANTO_DEBUG=1"`).
- Menu DEBUG (Start) : téléport villes Kanto/Sevii, murs, rencontres, soin.
- Bloc de sauvegarde Kanto (`src/kanto_save.c`) : flags 0x1000+, vars 0x5000+, après les 128 Ko du .sav.
- Géométrie de tout Kanto (`tools/kanto/import_kanto.py --all`, régénère tout) : 396 cartes, tilesets redécoupés, portes RF (`gen_door.py`).
- graphicsId 16 bits ; 152 sprites RF (`gen_objects.py`, ids 0x100+). Non-régression Hoenn vérifiée (`compare.py` = identique).
- Conversion scripts/textes RF (`import_scripts.py`, appelé par import_kanto) : labels, flags/vars, sprites, localid, musiques, macros RF (`asm/macros/kanto_event.inc`), commandes RF (`src/kanto_scrcmd.c`, opcodes 0xc7-0xcc/0xd0/0xe3), menus/chaînes/échanges RF ajoutés en fin de tables (`gen_script_menu.py`), braille RF.

## En cours (2026-10-19) : le jeu tourne dans Kanto
Testé en headless (`test/headless/run.py out/winwsl/pokeemeraude64.exe kanto_tour|kanto_warps --shots 60`,
sous Windows l'exe tourne directement) :
- les 22 téléports DEBUG s'affichent sans gel ; Bourg Palette, maison, labo, Centre de Jadielle (soin) jouables ;
- PNJ Kanto visibles et aux couleurs RF (corrigé : découpe -mwidth/-mheight des sprites, palettes RF hors
  `#ifdef BUGFIX`, cases PNJ remplies avec les palettes RF sur les cartes Kanto).
Outils : DEBUG > « Recevoir MEWTWO » (nv 70) ; l'état de test (build KANTO_DEBUG) donne aussi les sprites
(graphicsId, spriteId, inUse, invisible, priorité, palette, x, y, tuile, somme tuiles, somme palette…).
- nouvelle partie RF (`Kanto_EventScript_ResetAllMapFlags`, `ResetFameChecker`) : Chen caché, scène de Chen
  à la sortie vers la Route 1 jouée jusqu'au labo ;
- rencontres sauvages RF (`tools/kanto/gen_wild.py`, version Rouge Feu) ; combat sauvage complet (`kanto_wild`)
  avec décor et musique RF (`tools/kanto/gen_battle_bg.py`, `src/kanto_battle_bg.c`, scènes
  `MAP_BATTLE_SCENE_KANTO_*`).
- dresseurs RF (`tools/kanto/gen_trainers.py`) : 743 dresseurs, équipes, classes, portraits, après ceux
  d'Émeraude (`TRAINER_KANTO_*`, `TRAINER_CLASS_KANTO_*`, `TRAINER_PIC_KANTO_*`) ; drapeaux « battu » à leur
  place RF dans le bloc Kanto ; musiques RF (approche, combat, victoire) ; nom du rival en combat ;
  `TRAINER_BATTLE_EARLY_RIVAL` (13) de RF. Testés : arène d'Argenta (`kanto_trainer`), rival du labo (`kanto_rival`) ;
- pas des PNJ RF alternés (`sKantoStepAnimTables` dans `GetStepAnimTable`).
- démonstration de capture du vieil homme de Jadielle (`src/battle_controller_old_man.c`, d'après le
  contrôleur RF, sur la base de celui de Wally : même type de combat ; `IsOldManTutorialBattle()`).
  Testée avec `kanto_old_man` (nécessite VAR_KANTO_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN = 1, c.-à-d. le POKéDEX reçu).
  Sac : celui d'Émeraude en mode démonstration.
Specials RF : portés dans `src/kanto_field_specials.c`, `src/kanto_specials.c` (PC, vendeurs, Resort Gorgeous, massage, Cap Falaise, poudre de baies, perte d'argent, Seagallop n°…), `src/kanto_list_menu.c` (ascenseurs + ListMenu, non testés en jeu), `src/kanto_trainer_fan_club.c` (Fan Club de Safrania), `daycare.c` (pension Route 5 dans gSaveBlockKanto), `pokemon_size_record.c`, `battle_setup.c` (légendaires, revanches), `field_tasks.c` (glace de la grotte Gelée). Aide et journal de RF : sans effet. Approximations d'Émeraude assumées : PC du Panthéon, effaceur de capacités, menu PC, sauvegarde (mêmes rôles). Restent 48 stubs (`src/kanto_specials_stubs.c`) : link/Tour de Combat de RF inaccessible (CableClub*, EnterColosseum/TradeSeat, TryContestLinkup, BattleTower*, ChooseBattleTowerPlayerParty, ReducePlayerPartyToThree, EReader, ReadTrainerTowerAndValidate) ; à importer avec leurs graphismes/textes : VsSeeker*, DoSeagallopFerryScene + menus Seagallop, DoSSAnneDepartureCutscene, CallTrainerTowerFunc, EnterHallOfFame + DoCredits (fin de jeu RF), ShowTownMap (carte de Kanto), ShowDiploma, ShowBattleRecords, ShowEasyChatMessage, BufferRandomHobbyOrLifestyleString, GetProfOaksRatingMessage, Open/CloseMuseumFossilPic, DoPicboxCancel, AnimateTeleporterHousing/Cable, DoPokemonLeagueLightingEffect, DoDeoxysTriangleInteraction, SetDeoxysTrianglePalette, BrailleCursorToggle. IA des légendaires de RF (BATTLE_TYPE_LEGENDARY_FRLG) non reprise.

Warps RF : escaliers latéraux (`MB_*_STAIR_WARP`, scénario `kanto_stairs`), téléporteurs `MB_REGULAR_WARP` (DoTeleportWarp ; animation = DoPlayerSpinExit/Entrance d'Émeraude, scénario `kanto_warp_pad`), trous `MB_FALL_WARP` (EventScript_DoFallWarp, non testé), escaliers de roche `MB_ROCK_STAIRS` (PlayerWalkSlow/PlayerRunSlow de RF, actions MOVEMENT_ACTION_KANTO_WALK_SLOW_* et PLAYER_RUN_*_SLOW ; marche vérifiée par `kanto_rock_stairs`, course non testée ; à vélo, PlayerWalkFast comme RF : Vélo Course bridé à sa 2e vitesse (bike.c), Vélo Cross inchangé), rochers de Force qui tombent dans les trous et interrupteurs `MB_STRENGTH_BUTTON` de la Route Victoire (non testés) portés tels quels. Reste `MB_CAVE_DOOR` -> porte non animée (équivalent).

## Dettes (provisoire → importer depuis RF)
- **Tour des Dresseurs (Île 7, `CallTrainerTowerFunc`)** — à faire en effort Élevé. Différente des installations d'Émeraude (proche de l'Arbre de Dresseurs). À importer : `trainer_tower.c` de RF (~1 100 lignes), ses données de dresseurs, un type de combat dédié (BATTLE_TYPE_TRAINER_TOWER de RF = bit de BATTLE_TYPE_FACTORY dans Émeraude : plus aucun bit libre, il faudra un autre moyen, ex. variable globale), le chronomètre affiché sur le terrain, les records sauvegardés (`trainerTower[]` de SaveBlock1 RF → gSaveBlockKanto), ses textes et portraits en combat, les combats doubles.
- Combat : conseils de Chen pendant le combat du labo : NON (décision de l'utilisateur, 2026-10-30).
- Système d'aide RF, `walk_slower_*` → walk_slow. (Panneaux, textcolor/signmsg, couleurs homme/femme : faits le 2026-10-30.)
- Objets « clone » RF, comportements de tuiles décoratifs/énigmes (BEHAVIOR_ALIASES), anims de tilesets (callback NULL), effets de terrain RF.
- Graphismes présents dans les deux jeux (boîtes, interface de combat, transitions, sprites du joueur, de Red…) : choix dans les options plus tard (décision utilisateur).
- Std msgbox RF (Kanto_Std_*), scénario (mamans, Rocket…) ; le choix du nom du rival (oak_speech) : plus tard avec l'utilisateur.
- {RIVAL} à Kanto = `gSaveBlockKanto.rivalName`, « BLUE » par défaut. Fame Checker (drapeaux) dans `gSaveBlockKanto`.
- Journal (Quest Log) de RF non importé : `GetQuestLogState` = 0, `SetUsedPkmnCenterQuestLogEvent` sans effet (`src/kanto_field_specials.c`).
- Normal, pas un bug : pas de musique au départ debug à Bourg Palette (on y arrive normalement par le camion), scène du rival à l'Île 4 (on y arrive en bateau).

## Pièges
- Python Windows écrit en CRLF → `newline=''` ; heredoc bash mange les `\\` → utiliser Edit/Write.
- En-têtes Émeraude incluent des fichiers générés : les générateurs créent des versions vides au 1er passage.
