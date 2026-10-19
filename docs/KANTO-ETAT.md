# Import de Kanto — état et reprise (2026-10-19)

## Fait
- Émeraude FR natif Windows/Linux (merge port pokeemerald-native), build Docker (`docker/build.sh`, `MAKEFLAGS_EXTRA="KANTO_DEBUG=1"`).
- Menu DEBUG (Start) : téléport villes Kanto/Sevii, murs, rencontres, soin.
- Bloc de sauvegarde Kanto (`src/kanto_save.c`) : flags 0x1000+, vars 0x5000+, après les 128 Ko du .sav.
- Géométrie de tout Kanto (`tools/kanto/import_kanto.py --all`, régénère tout) : 396 cartes, tilesets redécoupés, portes RF (`gen_door.py`).
- graphicsId 16 bits ; 152 sprites RF (`gen_objects.py`, ids 0x100+). Non-régression Hoenn vérifiée (`compare.py` = identique).
- Conversion scripts/textes RF (`import_scripts.py`, appelé par import_kanto) : labels, flags/vars, sprites, localid, musiques, macros RF (`asm/macros/kanto_event.inc`), commandes RF (`src/kanto_scrcmd.c`, opcodes 0xc7-0xcc/0xd0/0xe3), menus/chaînes/échanges RF ajoutés en fin de tables (`gen_script_menu.py`), braille RF.

## En cours (2026-10-19) : le build winwsl passe, à tester
Le .exe est produit (`out/winwsl/pokeemeraude64.exe`, KANTO_DEBUG=1). Symboles ajoutés : METATILE_* RF (`include/constants/kanto/metatile_labels.h`), lieux de soin RF (fin de `src/data/heal_locations.json`), alias de scripts (`kanto/script_aliases.h` : NPC_TEXT_COLOR, SE_RS_*, STEP_CB_ICE provisoire), FLDEFF_PHOTO_FLASH/SMILEY_FACE_ICON (ids 67/68, scripts vides), layouts de remplacement (setmaplayoutindex), 3 specials en stubs.
Prochaine étape : lancer le .exe, tester le menu DEBUG (Start) puis marcher dans Kanto, corriger les plantages.

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
