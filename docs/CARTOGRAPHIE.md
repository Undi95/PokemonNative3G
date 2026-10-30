# Cartographie Émeraude / Rouge Feu / fusion

À lire avant toute tâche de fusion : on y trouve ce qui est propre à chaque jeu, où c'est dans les décomps
et où c'en est la fusion. Les listes détaillées sont générées ; cette page est la synthèse (mise à jour à la main).

```bash
python tools/cartographie.py
```

Le script relit `../decomps/pokeemeraude`, `../decomps/pokerougefeu` et ce dépôt (4 s), et réécrit `docs/carto/` :

| Fichier | Contenu | Usage |
|---|---|---|
| [carto/sources.md](carto/sources.md) | chaque `.c` de RF : fonctions propres, déjà portées, copie Kanto, fichiers de la fusion | « où en est le fichier X de RF ? » |
| [carto/fonctions-rf-absentes.md](carto/fonctions-rf-absentes.md) | fonctions propres à RF absentes de la fusion, par fichier | `grep NomDeFonction` avant de porter |
| [carto/fonctions-divergentes.md](carto/fonctions-divergentes.md) | même nom dans les deux jeux, code différent (✓ = variante Kanto dans la fusion) | trouver un comportement propre à RF |
| [carto/constantes.md](carto/constantes.md) | objets, espèces, types de combat, effets de terrain, déplacements, métatiles, musiques, dresseurs, sprites | « cette constante RF existe-t-elle ? » |
| [carto/scripts.md](carto/scripts.md) | specials (portés / stubs), opcodes de script, macros, `data/scripts/` | porter un script RF |
| [carto/donnees.md](carto/donnees.md) | dossiers `graphics/`, champs de sauvegarde, cartes | graphismes et sauvegarde |

Limites : le repérage se fait par nom. Une fonction de RF portée sous un autre nom n'est pas vue. Une fonction
« propre à RF » est souvent la même logique qu'Émeraude sous un autre nom (`SetUpStartMenu` de RF ↔
`BuildStartMenuActions` d'Émeraude) : « absente » ne veut pas dire « fonctionnalité manquante ». Le script
reconnaît les corps identiques (187 fonctions) mais pas les corps voisins.

## Chiffres (2026-10-23)

- Sources : 310 `.c` dans Émeraude, 283 dans RF, 350 dans la fusion. 207 fichiers communs, 76 propres à RF, 103 propres à Émeraude.
- Fonctions de RF : 12 033. 3 949 identiques à Émeraude ; 4 254 de même nom mais code différent ; 3 830 de nom
  propre à RF, dont 1 045 dans la fusion et 187 au code identique à une fonction d'Émeraude.
- Données de jeu : espèces (440), capacités (356), talents, effets de capacités et d'objets tenus **identiques**.
  Objets : mêmes numéros. Les 58 noms propres à RF ne sont que des alias de CT/CS (`ITEM_TM01_FOCUS_PUNCH = ITEM_TM01`).
- Cartes : Émeraude 518, RF 425, fusion 914 (518 + 396 de RF). Non importées : Nombril du Monde de RF
  (celui d'Émeraude est gardé), salles link et Île Aurore (mêmes cartes). Route Victoire et Parc Safari
  Nord de RF : `KantoVictoryRoad_*`, `KantoSafariZone_North*`.
- Specials : RF en a 272. 147 lui sont propres : 104 portés, 43 stubs (`src/kanto_specials_stubs.c`).
- Musiques de RF : déjà dans Émeraude sous `MUS_RG_*`, sauf `MUS_RS_VS_GYM_LEADER` et `MUS_RS_VS_TRAINER`.

## Propre à Rouge Feu

✓ porté · ◐ partiel · ✗ absent · ⊘ hors solo (link) · — écarté par décision.

| Contenu | Fichiers RF | Fusion |
|---|---|---|
| Sac, Boîte à CT, Sac à Baies | bag, item_menu, item_menu_icons, tm_case, berry_pouch | ✓ option SAC (`kanto_bag.c`, `kanto_item_menu*.c`, `kanto_tm_case.c`, `kanto_berry_pouch.c`) |
| Pokédex de Kanto | pokedex_screen, pokedex_area_markers, wild_pokemon_area | ✓ option POKéDEX (`kanto_pokedex_screen.c`, `kanto_pokedex_area.c`) |
| Résumé du Pokémon | pokemon_summary_screen | ✓ option MENUS (`kanto_summary_screen.c`) |
| Écran titre, intro, crédits, Panthéon | title_screen, intro, credits, hall_of_fame | ✓ (`kanto_title_screen.c`, `kanto_intro.c`, `kanto_credits.c`, `kanto_hall_of_fame.c`) |
| Carte de Kanto, Vol, objet Carte | region_map | ✓ (`kanto_region_map.c`) |
| Cherche VS | vs_seeker | ✓ à Kanto et à Hoenn (`kanto_vs_seeker.c` ; Hoenn = revanches du PokéNav) |
| Cherch'Objet | itemfinder | ✓ à Kanto (`kanto_itemfinder.c`) |
| Fan Club de Safrania, portes | trainer_fan_club, field_door | ✓ (`kanto_trainer_fan_club.c`, `kanto_field_door.c`) |
| Specials de terrain | field_specials (118 fonctions) | ◐ 47 dans `kanto_field_specials.c` / `kanto_specials.c` / `kanto_list_menu.c` ; 43 stubs |
| Commandes de script RF | scrcmd | ✓ opcodes RF dans `kanto_scrcmd.c` (les autres = ceux d'Émeraude) |
| Décors de combat | battle_bg | ✓ (`kanto_battle_bg.c`, généré) |
| Warps et transitions | field_fadetransition | ◐ 43 % (escaliers, téléporteurs, trous portés) |
| Vieil homme de Jadielle | battle_controller_oak_old_man | ◐ vieil homme (`battle_controller_old_man.c`) ; conseils de Chen — écartés |
| Aperçus de donjons | map_preview_screen | ◐ données dans `kanto_region_map.c`, écran à faire |
| Aide (touche L/R) | help_system, help_system_util, help_message | ◐ messages (`kanto_help_message.c`) ; système sans effet |
| Journal « Précédemment dans votre quête » | quest_log, quest_log_* (5 fichiers) | ✗ à faire (option, désactivé par défaut) |
| Tour des Dresseurs (Île 7) | trainer_tower | ✗ dette (cf. KANTO-ETAT.md) |
| Objets cachés qui réapparaissent | renewable_hidden_items | ✗ |
| Fame Checker (objet rare) | fame_checker | ✗ (sauvegarde déjà réservée dans `gSaveBlockKanto`) |
| Discours de Chen (nouvelle partie) | oak_speech | ✗ (la partie commence à Hoenn) |
| Note du Pokédex par Chen (PC) | prof_pc | ✗ stub `GetProfOaksRatingMessage` |
| Animation d'objet sur un Pokémon (CT, Super Bonbon…) | pokemon_special_anim, pokemon_special_anim_scene | ✗ |
| Ferry Seagallop, départ du S.S. Anne | seagallop, ss_anne | ◐ menus / ✗ cinématiques (stubs) |
| Combat FANTÔME (Tour Pokémon), IA des légendaires RF | battle_main, battle_ai… (`BATTLE_TYPE_GHOST`, `_LEGENDARY_FRLG`) | ✗ stub `StartMarowakBattle` |
| Teachy TV, combats du Pokédude | teachy_tv, battle_controller_pokedude | — retirés du sac |
| PC (stockage), Easy Chat | pokemon_storage_system_*, easy_chat_2/3 | — Émeraude gardé (décisions 2026-10-23) |
| PC objets / boîte aux lettres, Maître des capacités, boutique, machine à sous, menu Start de RF | item_pc, mailbox_pc, learn_move, buy_menu_helpers, slot_machine, start_menu | ✗ version d'Émeraude partout (candidats à HOENN/KANTO) |
| Link : E-Reader, Union Room, Tour de Combat RF, Colisée | cereader_tool, union_room_chat_*, battle_tower | ⊘ stubs |


## Reste à importer de Rouge Feu (bilan du 2026-10-23, d'après `carto/`)

Ordre proposé : d'abord ce qui bloque ou manque dans l'aventure de Kanto, puis la présentation (options), le reste à décider.

**A. Aventure (solo)**
1. ~~Ferry Seagallop~~ : fait le 2026-10-23 (`src/kanto_seagallop.c`, menu des destinations dans `script_menu.c`).
2. ~~Fame Checker~~ : fait le 2026-10-23 (`src/kanto_fame_checker.c`, MEMORYDEX depuis le sac des deux styles ou SELECT).
3. ~~Cinématiques et scènes en stub~~ : faites le 2026-10-23 (S.S. Anne, diplôme, éclairage de la Ligue, téléporteurs de Léo, fossiles du musée). Sans objet : triangle de Deoxys (l'Île Aurore est celle d'Émeraude, avec son puzzle), `DoPicboxCancel` et `BrailleCursorToggle` (aucun script ne les appelle).
4. ~~Poké Flûte~~ : faite le 2026-10-23 (terrain + combat).
5. ~~Tour des Dresseurs~~ : faite le 2026-10-24 (`src/kanto_trainer_tower.c` + `kanto_trainer_tower_sets.c` ; combats au type de la Colline des Dresseurs d'Émeraude, aiguillés par `gBattleTrainerTowerFrlg` ; 16 dispositions d'étage ajoutées, cf. `tools/kanto/import_kanto.py`).
6. ~~Combats sauvages scriptés de RF~~ : faits le 2026-10-24 (`gBattleWildScriptedFrlg`, posé par `dowildbattle` à Kanto). NB : dans RF comme dans Émeraude, le contrôleur adverse ne consulte l'IA que pour les dresseurs, le Safari, les errants et le premier combat ; les réglages d'IA des sauvages scriptés et des légendaires de RF n'ont donc aucun effet en jeu (portés pour être complets).
7. ~~Aperçus des donjons~~ : faits le 2026-10-24 (`src/kanto_map_preview_screen.c` ; grottes dans fldeff_flash.c, forêts au chargement de la carte, attente des fondus `FieldFadeTransitionBackgroundEffectIsFinished`).
8. ~~PNJ en stub~~ : faits le 2026-10-24 (`kanto_field_specials.c` : `ShowEasyChatMessage` = `ShowEasyChatProfile` d'Émeraude ; `BufferRandomHobbyOrLifestyleString` n'est appelé par aucun script de RF).
9. ~~Journal « Précédemment dans votre quête »~~ : ABANDONNÉ (décision de l'utilisateur, 2026-10-24). Bilan du
   2026-10-24 : 4 500 lignes de RF, 238 points d'accroche dans 39 fichiers du moteur (terrain, déplacements des objets,
   entrées du joueur, combats, sac, boutique, PC, sauvegarde) et 84 gardes `goto_if_questlog` dans les scripts. Le rejeu
   repasse les touches enregistrées dans le moteur du terrain et restaure équipe, PC, drapeaux et variables de chaque
   scène (4 scènes). Plan par étapes :
   a. Bloc de sauvegarde annexe (Platform_WriteExtraSave, comme le Panthéon) : 4 scènes avec drapeaux/variables
      d'Émeraude ET de Kanto (≈ 2 Ko par scène), option JOURNAL (page 2, NON par défaut).
   b. Enregistrement : quest_log.c (scènes, actions), quest_log_player.c / quest_log_objects.c, accroches dans
      field_control_avatar.c (QL_RecordFieldInput), event_object_movement.c, field_player_avatar.c, overworld.c.
   c. Rejeu : écran « Précédemment… », restauration de l'état, fin de rejeu et retour à la partie sauvegardée.
   d. Événements (quest_log_events.c, ~40 types : achats, combats, objets, Centres Pokémon…) avec leurs accroches.
   Chaque étape testable seule ; risque de régression dans le moteur du terrain : tout reste derrière l'option.

**B. Présentation (choix HOENN/KANTO ou règle par région)**
- ~~Animation d'objet sur un Pokémon avec le sac KANTO~~ : faite le 2026-10-24 (`kanto_pokemon_special_anim*.c`, préambules de RF dans party_menu.c, `PokemonItemUseNoEffect` de RF dans pokemon.c).
- Interfaces de RF en option (MENUS = KANTO) : ~~PC objets + boîte aux lettres~~ (2026-10-24), ~~boutique~~ (2026-10-24, `kanto_shop.c`), ~~menu Start~~ (déjà fait par MENUS : police, espacement, descriptions), ~~Maître des capacités~~ (2026-10-24, `kanto_learn_move.c`, descriptions de RF dans `kanto_move_descriptions.c`).
- ~~Machine à sous de RF au Casino de Céladopole~~ (2026-10-24, `kanto_slot_machine.c` ; effets de terrain de RF FLDEFF_SMILEY_FACE_ICON et FLDEFF_PHOTO_FLASH portés, ils bloquaient les scripts).
- ~~Panneaux de RF, polices homme/femme et couleurs de texte~~ : faits le 2026-10-30. Tuiles MB_SIGNPOST / enseignes Centre, Boutique, Plateau Indigo rétablies (`tools/kanto_signposts.py`, 0xC8-0xCC) ; on ouvre un panneau en marchant vers lui et on le ferme en s'éloignant (field_control_avatar.c, script.c) ; avec DIALOGUE = KANTO, cadre « panneau » de RF et texte bleu/rouge des PNJ de Kanto (`ContextNpcGetTextColor`, kanto_field_specials.c). Les polices FONT_MALE/FEMALE de RF ont les glyphes et couleurs de sa police normale (= FONT_KANTO). Scénario `kanto_signposts`.

**C. À décider (écartés jusqu'ici)**
- Aide L/R de RF (help_system*.c) : aujourd'hui sans effet.
- Teachy TV et combats du Pokédude (teachy_tv.c, battle_controller_pokedude.c) : retirés du sac.
- Conseils de Chen pendant le combat du labo (battle_controller_oak_old_man.c) : NON (décision de l'utilisateur, 2026-10-30).
- Discours de Chen de nouvelle partie (oak_speech.c) : la partie commence à Hoenn.

**D. Hors solo (link)** : Colisée, échanges câble, Union Room, Tour de Combat de RF, E-Reader, records de combat.

**E. Données perdues à l'import** : objets « sous les pieds » (traités comme des objets cachés normaux).

**Déjà conformes, contrairement à ce que suggère la carte** : animations de tilesets de Kanto (tileset_anims.c), musiques RF (`MUS_RG_*`, sauf `MUS_RS_VS_*` = musiques d'Émeraude), déplacements `walk_slower` (convertis en `walk_slow`) ; les autres actions de déplacement propres à RF (rotation, glissade…) ne servent qu'aux cinématiques du point A3.

## Propre à Émeraude (contenu de Hoenn, intact dans la fusion)

- Concours : contest*, contest_painting, berry_blender, pokeblock*, use_pokeblock.
- Zone de Combat : battle_dome/pike/pyramid/palace/arena/factory(_screen)/tent, frontier_*, apprentice, battle_pyramid_bag.
- PokéNav et appels : pokenav_* (14 fichiers), match_call (revanches de Hoenn).
- Monde : secret_base, tv, record_mixing, dewford_trend, lilycove_lady, mauville_old_man, trader, mirage_tower,
  rayquaza_scene, faraway_island, trainer_hill, rotating_gate, rotating_tile_puzzle, braille_puzzles, cable_car, roulette, lottery_corner.
- Horloge : rtc, clock, time_events, wallclock, reset_rtc_screen.
- Début de partie : starter_choose, birch_pc. Combat : battle_controller_wally (base du vieil homme),
  battle_controller_player_partner, recorded_battle, battle_tv, pokemon_animation (sprites animés = option POKéMON).

## Communs mais différents (présentation propre à chaque jeu)

Détail : `carto/fonctions-divergentes.md`. Fichiers communs où RF a le plus de fonctions propres non couvertes :
event_object_movement 101, field_effect 90, slot_machine 73, party_menu 60, start_menu 53, field_player_avatar 52,
item_use 48, metatile_behavior 48, player_pc 43, overworld 30, easy_chat 27, evolution_graphics 26, main_menu 25,
script_menu 20, menu 19, field_specials 18, wild_encounter 18, option_menu 17, tileset_anims 17, trainer_see 17.
Une bonne part est du renommage ; à vérifier fichier par fichier avant de porter.

Les choix HOENN/KANTO déjà faits sont dans [FUSION-OPTIONS.md](FUSION-OPTIONS.md).

## Sauvegarde

- Champs propres à RF (SaveBlock1/2) : questLog, fameChecker, rivalName, route5DayCareMon, trainerTower, battleTower RF.
  Ils vont dans `gSaveBlockKanto` (`include/kanto_save.h`), qui a déjà rivalName, fameChecker, route5DayCareMon,
  roamers et les revanches du Cherche VS.
- Champs propres à Émeraude : décorations, bases secrètes, TV, concours, Zone de Combat, apprentis, dame de Nénucrique : inchangés.

## Fichiers propres à la fusion

`src/kanto_*.c` (25 fichiers : copies de RF, cf. colonne « copie » de `carto/sources.md`), `battle_controller_old_man.c`,
`debug_menu.c`, `kanto_save.c`, `kanto_specials_stubs.c`, `fusion_events.c` (événements propres à la fusion : œufs de
starters…, scripts dans `data/scripts/fusion_*.inc`). Outils d'import : `tools/kanto/*.py`, `tools/import_rf_mon_pics.py`,
`tools/redleaf_sprites.py`, `tools/item_doubles.py`, `tools/cartographie.py`, `tools/link_cable.py` (CÂBLE LINK), `tools/poke_monture.py` (POKé MONTURE), `tools/exclusifs.py`
(exclusivités de version dans les tables sauvages, à relancer après `tools/kanto/gen_wild.py`), `tools/obtenables.py`
(espèces obtenables / manquantes).
