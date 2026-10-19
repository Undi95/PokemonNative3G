# Import de Kanto — état et reprise (2026-10-19)

## Fait
- Émeraude FR natif Windows/Linux (merge port pokeemerald-native), build Docker (`docker/build.sh`, `MAKEFLAGS_EXTRA="KANTO_DEBUG=1"`).
- Menu DEBUG (Start) : téléport villes Kanto/Sevii, murs, rencontres, soin.
- Bloc de sauvegarde Kanto (`src/kanto_save.c`) : flags 0x1000+, vars 0x5000+, après les 128 Ko du .sav.
- Géométrie de tout Kanto (`tools/kanto/import_kanto.py --all`, régénère tout) : 396 cartes, tilesets redécoupés, portes RF (`gen_door.py`).
- graphicsId 16 bits ; 152 sprites RF (`gen_objects.py`, ids 0x100+). Non-régression Hoenn vérifiée (`compare.py` = identique).
- Conversion scripts/textes RF (`import_scripts.py`, appelé par import_kanto) : labels, flags/vars, sprites, localid, musiques, macros RF (`asm/macros/kanto_event.inc`), commandes RF (`src/kanto_scrcmd.c`, opcodes 0xc7-0xcc/0xd0/0xe3), menus/chaînes/échanges RF ajoutés en fin de tables (`gen_script_menu.py`), braille RF.

## En cours (2026-10-19) : assemblage OK, reste l'édition de liens
Les 5 points précédents sont soldés (event_scripts.o et trade.o compilent). Build : `TAILN=100000` dans `docker run -e` donne tout le log ; `grep -oE "undefined reference to .[A-Za-z0-9_]+"` liste les symboles.
Symboles non définis à l'édition de liens (~150), à générer/importer depuis RF dans les générateurs (import_scripts / import_kanto) :
1. `NPC_TEXT_COLOR_{MALE,FEMALE,NEUTRAL,MON}` (constantes RF de textcolor).
2. `METATILE_*` (SilphCo, PokemonMansion, CinnabarGym, VermilionGym, PokemonLeague, GameCorner, Cave_*, PokemonCenter_*, Mart_*, TrainerTower, SeviiIslands, MtEmber) : copier include/constants/metatile_labels.h de RF (préfixer KANTO_ si collision, valeurs = numéros RF).
3. `HEAL_LOCATION_*` de Kanto (19 villes) : étendre la table de heal_locations d'Émeraude à la fin.
4. `LAYOUT_*` utilisés par les scripts (THREE_ISLAND_DUNSPARCE_TUNNEL_DUG_OUT, SEVEN_ISLAND_HOUSE_ROOM1_DOOR_OPEN, SEAFOAM_ISLANDS_B3F/B4F_CURRENT_STOPPED) : noms de layouts Kanto à mapper.
5. Divers : `FLDEFF_PHOTO_FLASH`, `FLDEFF_SMILEY_FACE_ICON`, `SE_RS_DOOR`, `SE_RS_SHOP`, `MOVEMENT_TYPE_WANDER_AROUND_SLOWER` (alias de WANDER_AROUND), `STEP_CB_ICE`, fonctions `SetBattledTrainerFlag`, `GetDaycarePokemonCount`, `AwardBattleTowerRibbons` (stubs).
Puis : régénérer (gen_script_menu puis import_kanto --all, nécessite `pip install pillow` sous Windows), commit, build Docker winwsl.

## Dettes (provisoire → importer depuis RF)
- Dresseurs : `TRAINER_KANTO_*` = TRAINER_NONE (478) — importer dresseurs, classes, sprites, `TRAINER_BATTLE_EARLY_RIVAL`, flags dresseurs Kanto, décors de combat du Conseil 4 + transitions.
- 142 specials RF en stubs (`src/kanto_specials_stubs.c`, log console).
- Polices homme/femme RF (FONT_MALE/FEMALE → police normale), textcolor/signmsg (couleur/style boîte RF), système d'aide RF, `walk_slower_*` → walk_slow.
- Objets « clone » RF, objets cachés quantité/underfoot, comportements de tuiles décoratifs/énigmes (BEHAVIOR_ALIASES), anims de tilesets (callback NULL), rencontres sauvages, effets de terrain RF.
- Std msgbox RF (Kanto_Std_*), {RIVAL}=nom du rival de Kanto, scénario (mamans, Rocket…) : plus tard avec l'utilisateur.
- Bateau Nénucrique → Kanto ; son pas fluide.

## Pièges
- Python Windows écrit en CRLF → `newline=''` ; heredoc bash mange les `\\` → utiliser Edit/Write.
- En-têtes Émeraude incluent des fichiers générés : les générateurs créent des versions vides au 1er passage.
