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
Prochaine étape : contrôleur de combat « Chen / vieil homme » de RF (tutoriel du combat du labo,
démonstration de capture à Jadielle).

## Dettes (provisoire → importer depuis RF)
- Combat : `RIVAL_BATTLE_TUTORIAL` sans les conseils de Chen (contrôleur `battle_controller_oak_old_man.c` de RF à porter) ; rematchs RF (Cherche VS) ; Tour Dresseurs.
- 142 specials RF en stubs (`src/kanto_specials_stubs.c`, log console).
- Polices homme/femme RF (FONT_MALE/FEMALE → police normale), textcolor/signmsg (couleur/style boîte RF), système d'aide RF, `walk_slower_*` → walk_slow.
- Objets « clone » RF, objets cachés quantité/underfoot, comportements de tuiles décoratifs/énigmes (BEHAVIOR_ALIASES), anims de tilesets (callback NULL), effets de terrain RF.
- Graphismes présents dans les deux jeux (boîtes, interface de combat, transitions, sprites du joueur, de Red…) : choix dans les options plus tard (décision utilisateur). Combat : lettres des ZARBI de Tanoby (choix par chambre de RF) non importées.
- Std msgbox RF (Kanto_Std_*), scénario (mamans, Rocket…) ; le choix du nom du rival (oak_speech) : plus tard avec l'utilisateur.
- Bateau Nénucrique → Kanto ; son pas fluide.
- {RIVAL} à Kanto = `gSaveBlockKanto.rivalName`, « BLUE » par défaut. Fame Checker (drapeaux) dans `gSaveBlockKanto`.
- Objets cachés renouvelables de RF (`renewable_hidden_items.c`, `SetAllRenewableItemFlags` à la nouvelle partie) non importés.
- Journal (Quest Log) de RF non importé : `GetQuestLogState` = 0, `SetUsedPkmnCenterQuestLogEvent` sans effet (`src/kanto_field_specials.c`).
- Normal, pas un bug : pas de musique au départ debug à Bourg Palette (on y arrive normalement par le camion), scène du rival à l'Île 4 (on y arrive en bateau).

## Pièges
- Python Windows écrit en CRLF → `newline=''` ; heredoc bash mange les `\\` → utiliser Edit/Write.
- En-têtes Émeraude incluent des fichiers générés : les générateurs créent des versions vides au 1er passage.
