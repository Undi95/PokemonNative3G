# Import de Kanto — état et reprise (2026-10-19)

## Fait
- Émeraude FR natif Windows/Linux (merge port pokeemerald-native), build Docker (`docker/build.sh`, `MAKEFLAGS_EXTRA="KANTO_DEBUG=1"`).
- Menu DEBUG (Start) : téléport villes Kanto/Sevii, murs, rencontres, soin.
- Bloc de sauvegarde Kanto (`src/kanto_save.c`) : flags 0x1000+, vars 0x5000+, après les 128 Ko du .sav.
- Géométrie de tout Kanto (`tools/kanto/import_kanto.py --all`, régénère tout) : 396 cartes, tilesets redécoupés, portes RF (`gen_door.py`).
- graphicsId 16 bits ; 152 sprites RF (`gen_objects.py`, ids 0x100+). Non-régression Hoenn vérifiée (`compare.py` = identique).
- Conversion scripts/textes RF (`import_scripts.py`, appelé par import_kanto) : labels, flags/vars, sprites, localid, musiques, macros RF (`asm/macros/kanto_event.inc`), commandes RF (`src/kanto_scrcmd.c`, opcodes 0xc7-0xcc/0xd0/0xe3), menus/chaînes/échanges RF ajoutés en fin de tables (`gen_script_menu.py`), braille RF.

## En cours (build échoue encore sur event_scripts.o / trade.o)
1. `src/data/trade.h` : ajouter une virgule après la dernière entrée Émeraude avant `#include "kanto_ingame_trades_entries.h"` (idem table mail).
2. Espaces autour des opérateurs hors parenthèses (`(MAX_COINS + 1) - 500`, CeladonCity_GameCorner) → les retirer dans les arguments (import_scripts.transform).
3. Inclure dans `data/event_scripts.s` les en-têtes constants que RF inclut et qu'Émeraude n'inclut pas (ex. `constants/mystery_gift.h` → NEWS_REWARD_*).
4. cable_club.inc : `warp MAP_BATTLE_COLOSSEUM_2P…` → erreur `.ifdef` de la macro `map` (salles de link ignorées) à examiner.
5. Puis relancer : générateurs (gen_script_menu puis import_kanto --all) → commit → build (`rm build/win64/data/event_scripts.o` avant, sinon objet périmé).

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
