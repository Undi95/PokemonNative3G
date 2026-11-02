# Connaissance du jeu (ce qu'on attend de chaque écran)

Ce que le jeu doit faire, écran par écran, selon les options et la région, pour voir tout de suite un comportement
anormal. Tenu à jour à partir de l'explorateur et de la grille (`docs/DEVTOOLS.md`, « Explorateur et grille ») : ce
fichier dit ce qui est **attendu**, les planches montrent ce qui **est**.

Sources : Émeraude = `decomps/pokeemeraude`, Rouge Feu (RF) = `decomps/pokerougefeu` ; options = `docs/FUSION-OPTIONS.md`.

## Les options d'affichage (page 2 des Options)

Toutes à deux valeurs, 0 = HOENN (Émeraude), 1 = KANTO (RF). Index de `jeu.options` entre parenthèses.

| Option | Ce qu'elle change | Ce qu'elle ne change pas |
|---|---|---|
| PERSO (6) | le joueur : Brice/Flora ou Red/Leaf (carte, sprite de terrain, dos en combat, carte de dresseur) | — |
| DIALOGUE (8) | la boîte de dialogue (cadre RF : tiles 0-13 sauf 7 ; Émeraude : 1, 3-7, 9, 10 ; détecteur « cadre de boîte ») et les couleurs de texte des PNJ (bleu/rouge de RF, `AddTextPrinterDiffStyle`) | le texte gris des messages du jeu |
| POLICE (9) | les lettres de **tous** les textes (`DecompressGlyph_Kanto`) | les mesures des fenêtres : `FONT_NORMAL` garde les mesures d'Émeraude (16 px de haut), `FONT_KANTO` celles de RF (14 px) |
| POKéDEX (10) | le Pokédex : écran d'Émeraude ou de RF (sommaire, habitats) | — |
| MENUS (11) | menu Start (police RF, entrées tous les 15 px, aide en bas), équipe (palette RF), résumé (écran de RF : 3 pages), boutique (écran d'achat de RF), PC (menus), écran des noms, maître des capacités | la carte de dresseur (voir plus bas) |
| BOITES COMBAT (12) | les boîtes de combat (action, capacités, PV) | — |
| SAC (13) | le sac : Émeraude (5 poches, CT & CS, BAIES) ou RF (3 poches ; BOITE CT et SAC A BAIES en OBJ. RARES) ; aussi le sac de la démonstration du vieil homme de Jadielle (Wally d'Émeraude ou `InitOldManBag` de RF, scénario `kanto_old_man_bag`) | — |
| POKéMON (14) | les sprites des Pokémon (Émeraude animés, RF) | — |
| JOUR/NUIT (16) | la teinte du terrain, qui tient pendant la transition vers un combat (`CB2_OverworldBasic`) jusqu'au fondu ; pas de teinte dans l'écran de combat | — |

## Écrans et ce qu'ils doivent montrer

| Écran | Attendu | Piège connu |
|---|---|---|
| Carte de dresseur | le style suit la **région** (`Fusion_IsInKanto` dans `ShowPlayerTrainerCard`), pas MENUS ; le sprite suit PERSO ; les deux points de la DUREE JEU clignotent (une capture peut les montrer éteints). Carte de Kanto = données de RF : étoiles (Panthéon avec date, Pokédex de Kanto, Pokédex national, 200 baies et 200 sauts) → bleue, verte, bronze, argent, or ; au dos les icônes de la photo du Casino de Céladopole et les STICKERS de l'homme de l'Île 4 (en haut à gauche) ; Pokédex de Kanto tant que le national n'est pas obtenu | avant le 2026-11-02, la carte de Kanto prenait les données d'Émeraude : ni photo ni sticker, étoiles d'Émeraude (scénario `kanto_card_stickers`) |
| Options | titre « OPTIONS » à gauche, « L R 1/2 : JEU » ou « L R 2/2 : HOENN/KANTO » à droite | avant le 2026-11-02, « PAGE 2/2 » recouvrait « OPTIONS » avec la police de RF |
| PC | « PC de ??? » tant que le joueur n'a pas rencontré LANETTE (Hoenn) ou LÉO (Kanto) ; Kanto ajoute « PC du PROF. CHEN » | — |
| Boutique | Émeraude : « Bienvenue! » puis « En quoi puis-je vous aider? » puis ACHETER/VENDRE/QUITTER ; RF : « Bonjour! Je peux vous aider? » avec le menu tout de suite | — |
| Pokédex | Émeraude en mode Hoenn ne compte pas un Pokémon hors du Pokédex de Hoenn (MEWTWO : VUS 0) ; RF compte le Pokédex de Kanto | — |
| Listes de RF (`kanto_list_menu.c` : badges d'Azuria, ascenseurs) | 4 lignes de 14 px dans 7 tiles, avec `FONT_KANTO` | avant le 2026-11-02, `FONT_NORMAL` (16 px) coupait la 4ᵉ ligne |
| Étages (ascenseurs de RF) | « RC », « 1ᵉʳ », « 2ᵉ »… : `{SUPER_ER}` (0x2C) et `{SUPER_E}` (0x84) sont de vraies lettres | — |
| Crédits de Kanto | le métier (orange) sur sa ligne, les noms (blancs) en dessous, décalés à droite : deux textes dans la même fenêtre, placés par des lignes vides (« \n\n\nJunichi Masuda\n\n\n ») | `WrapTextToWindow` ne compte que les lignes jusqu'à la dernière non vide ; avant le 2026-11-02, il remettait ces lignes bout à bout (titre et noms sur une seule ligne) |
| Maison à vendre (Bourg Palette, fusion) | boîte d'argent « 3000¥ » alignée par des `CHAR_SPACER` (0x77) | — |

## Règle pour le code importé de RF

`FONT_NORMAL` de RF = 14 px de haut et ses propres largeurs ; dans la fusion c'est **`FONT_KANTO`**. Un écran de RF qui
écrit avec `FONT_NORMAL` prend les mesures d'Émeraude (16 px) : des lignes coupées en bas de fenêtre. À chaque écran
de RF : vérifier la police des listes et des textes de plusieurs lignes (le détecteur « texte coupé » et la grille le
montrent).

## États de partie explorés (`crawl.py --etat`)

| État | Ce que c'est | Dernier passage (2026-11-02) |
|---|---|---|
| `debut` | sauvegarde de début de partie de chaque région | 845 cartes, 4 604 interactions, 0 anomalie (police Hoenn et KANTO) |
| `champion` | Hoenn fini (`FLAG_SYS_GAME_CLEAR`, 8 badges, Pokédex, PokéNav) : l'arrivée réelle à Kanto, le ferry ne part qu'après la Ligue de Hoenn | 835 cartes, 4 586 interactions, 837 combats, 0 anomalie |
| `fin` | les deux Ligues finies, comme le menu DEBUG (« Deux Ligues finies », POKé MONTURE + badges, passes, Pokédex, objets) | 835 cartes, 4 586 interactions, 862 combats, 0 anomalie |
| `histoire` | `fin` + toute l'histoire des deux régions (`scripts.histoire 2` : drapeaux et variables d'avancement déduits des scripts, sans sauvegarde) | 0 anomalie, 0 texte suspect |

Pas besoin d'une sauvegarde pour atteindre un point du jeu : `scripts.histoire` met l'histoire finie, et
`scripts.drapeaux` (menu DEBUG ou banc) met chaque drapeau ou variable à la main.

## Défis (`challenges.py`) : ce qu'il faut savoir

- **Mont Combat** : les étages sont générés en jeu (`GenerateTrainerHillFloorLayout`) depuis les données du défi
  choisi. `SetUpDataStruct` copiait le défi et ses étages d'un seul bloc, en supposant les étages rangés juste après
  le défi en mémoire (vrai sur la cartouche, pas sur PC) : étages en tuiles magenta, sans dresseurs. Correctif UBFIX :
  deux copies. Les barres bleues des étages sont des **rebords** (`MB_JUMP_SOUTH`) qui ont le bit de collision : le
  jeu les fait sauter quand même (`CheckForObjectEventCollision` teste `ShouldJumpLedge` avant la collision). C'est
  le seul chemin vers les dresseurs au 1er étage du défi normal. L'étage suivant ne s'ouvre qu'après avoir battu les
  dresseurs ; combats doubles à deux dresseurs, adversaires au niveau du plus fort Pokémon de l'équipe.
- **Rebords avec collision** : 1 988 cases, surtout sur les routes de Kanto (Route 9, 22, 15…). Un chemin calculé
  sur les fichiers de carte doit les traiter comme des rebords, pas comme des murs (`maps.py`, `carte.grille`).
- **Tour Dresseur de l'Île 7** (RF) : l'entrée et les étages se prennent par des **escaliers latéraux**
  (`MB_UP_RIGHT_STAIR_WARP`…) : sur la case, on maintient la direction de l'escalier (DROITE) ; le jeu attend une
  quarantaine d'images (animation de l'escalier) avant le warp.
- **Concours** : l'hôtesse envoie dans la salle de la catégorie choisie (`ContestHallCool`…), pas dans
  `LilycoveCity_ContestHall` ; le jeu choisit, appels (une capacité par tour, 5 tours), résultats, retour au hall.
- **Dôme** : la fiche du joueur dans le tableau divise par la somme des EV de ses Pokémon (0 sur GBA si aucun EV ;
  plantage sur PC) : correctif UBFIX.
- **Antre, Pyramide, Mont Combat** remettent `gBattleOutcome` à zéro après un combat : la victoire se lit à la suite
  (l'étage suivant, le défi qui continue), pas dans l'issue du combat.

## Règle pour les numéros de dresseurs

Les dresseurs de Kanto suivent ceux d'Émeraude (`KANTO_TRAINERS_START` = 864 à 1606). Deux numéros sont aussi ceux
d'adversaires spéciaux d'Émeraude : 1022 `TRAINER_FRONTIER_BRAIN` (PIQUE-NIQUE SOFIA, Grotte B1F) et 1024
`TRAINER_SECRET_BASE` (PIQUE-NIQUE TINA, Arène de Céladopole). Hors des fichiers de la Zone de Combat, tout test sur
ces valeurs passe par `IS_SECRET_BASE_OPPONENT` / `IS_FRONTIER_BRAIN_OPPONENT` (`include/battle_setup.h`), qui
vérifient aussi le type de combat. Renuméroter Kanto déplacerait les drapeaux de victoire des sauvegardes. Scénario :
`kanto_trainer_ids`.

## Règle pour les classes de dresseurs de Kanto

Les dresseurs de Kanto ont leurs propres classes (`TRAINER_CLASS_KANTO_LEADER`, `_ELITE_FOUR`, `_CHAMPION`…). Tout
code d'Émeraude qui teste `TRAINER_CLASS_LEADER`, `_ELITE_FOUR` ou `_CHAMPION` doit aussi tester la classe Kanto
quand RF fait ce test : sinon Kanto tombe dans le cas général. Trouvés ainsi (2026-11-02) : la transition à portrait
de la Ligue de Kanto (`GetTrainerBattleTransition`) et le bonus d'amitié des combats de Ligue (`AdjustFriendship`).
Vérifiés conformes : musique de combat et de victoire, table d'argent (`src/data/kanto/trainer_money.h`), décor de
combat (`kanto_battle_bg.c`), nom du rival (`battle_message.c`). Pour repérer les autres :
`grep -n "TRAINER_CLASS_[A-Z_]*" src/*.c | grep "==\|case "` et comparer avec les mêmes tests dans RF.

## Parc Safari : Hoenn (Émeraude) et Kanto (Rouge Feu)

| | Hoenn | Kanto |
|---|---|---|
| Pas | 500 | 600 (`EnterSafariMode`) |
| Menu START | SAFARI BALLS, Nb | pas restants / 600, BALLS (`DrawSafariZoneStatsWindow`) |
| Menu de combat | BALL, POKéBLOC, SE RAP., FUITE | BALL, APPAT, PIERRE, FUITE (mêmes actions 6 et 7) |
| Fuite de départ | 3 | `safariZoneFleeRate` de l'espèce × 100 / 1275 (2 au moins) |
| Action 6 | POKéBLOC (choix dans la boîte) | APPAT : capture ÷ 2, fuite ÷ 4 tant que le Pokémon mange (2 à 6 tours) |
| Action 7 | SE RAP. | PIERRE : capture × 2 (20 au plus), fuite × 2 tant qu'il est fâché |
| Tour du Pokémon | « surveille attentivement » | « surveille », « se fâche », « mange » (`gSafariReactionStringIds`, animation `B_ANIM_SAFARI_REACTION`) |
| Sortie | émission « Safari » de la télé de Hoenn | rien |
| Fin (temps, balls, PARTIR) | `SafariZone_EventScript_*` : entrée de la Route 121, `VAR_SAFARI_ZONE_STATE` | `Kanto_SafariZone_EventScript_*` (`data/kanto/data/scripts/safari_zone.inc`) : entrée de Parmanie, `VAR_KANTO_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE` (1 ou 3 : « Bonne chasse? ») |

Tout le Safari de Kanto passe par `Fusion_IsInKanto()` (battle_util.c, battle_main.c, battle_ai_script_commands.c,
battle_controller_safari.c, safari_zone.c, start_menu.c). Avant le 2026-11-02, la fin du Safari de Kanto lançait les
scripts d'Émeraude et envoyait le joueur à Hoenn (Route 121) ; ceux de RF avaient été retirés comme « jamais
appelés » — un script jamais appelé peut être le symptôme d'un aiguillage manquant. Scénarios : `kanto_safari`,
`kanto_safari_exit` (`jeu.safari` met les pas et les balls).

## Sons de Kanto

L'identité d'un son est son **nom d'origine** (commentaire de `include/constants/songs.h`, « `// MUS_ME_ASA` »), pas
sa constante : RF et Émeraude ont 17 constantes de même nom mais de son différent. `MUS_HEAL` de RF = `MUS_ME_ASA` =
`MUS_HEAL` d'Émeraude, alors que `MUS_RG_HEAL` est `MUS_HEAL_UNUSED` de RF (jamais joué) ; `SE_SHOP` et `SE_DOOR` de RF
sont `SE_RG_SHOP` et `SE_RG_DOOR` (ceux d'Émeraude sont `SE_RS_SHOP` et `SE_RS_DOOR` de RF) ; `MUS_GYM`, `MUS_VS_*`,
`MUS_VICTORY_*`, `MUS_TITLE`… de RF sont les `MUS_RG_*`. Inversement Émeraude réutilise des noms d'origine pour ses
propres morceaux (`MUS_AJITO` = repaire Aqua/Magma, `MUS_RG_AJITO` = repaire Rocket) : on prend la copie `RG_`
d'abord. Quatre constantes ont ainsi le même nom **et** le même nom d'origine dans les deux jeux, mais pas le même
morceau : `MUS_SURF`, `MUS_CYCLING`, `MUS_HALL_OF_FAME`, `MUS_POKE_CENTER` de RF sont les `MUS_RG_*` de la fusion.
Le code commun choisit selon la région : `Overworld_GetSurfMusic`, `Overworld_GetCyclingMusic`, et la règle de RF
`Overworld_MusicCanOverrideMapMusic` (pas de musique de vélo ni de Surf sur la Route Victoire, la Route 23 et au
Plateau Indigo ; toujours vrai à Hoenn). L'importeur des scripts (`tools/kanto/import_kanto.py`, `music` / `sound`) suit cette règle depuis le
2026-11-02 ; avant, `MUS_X` devenait `MUS_RG_X` s'il existait et les `SE_` restaient tels quels.

Corrigé le 2026-11-02 (scénario `kanto_sounds`) : toutes les portes de Kanto (porte d'Émeraude), la caisse des écrans
de RF (boutique, vente au sac, boîte CT, sac à baies), du Casino de Céladopole, du Musée d'Argenta et de la photo de
la carte de dresseur, la fanfare des soins hors Centre (toilettage de la sœur du rival, capitaine de l'Océane,
`EventScript_OutOfCenterPartyHeal`) ; puis (lecture des « à vérifier ») la musique du Surf, du vélo, de la Piste
Cyclable et du Panthéon de Kanto (scénarios `poke_monture`, `redleaf_acro`).

`python tools/audit_sons.py` (après `tools/audit_sons.sh`) :
- **pieges** : il ne reste que des usages justifiés (machine à sous de Kanto : `SE_RS_SHOP` de RF ; Route Victoire
  d'Émeraude, carte commune) ;
- **fichiers** : 501 fichiers de RF ont les mêmes sons que leur copie ; les autres sont des cartes communes gardées
  d'Émeraude (Colisée, Centre d'échange, Union : link), du code déplacé (ascenseurs dans `kanto_list_menu.c`,
  Deoxys et trou de la Coupe dans `field_effect.c` / `fldeff_cut.c`), des choix de la fusion (POKé MONTURE au lieu de
  la CS du capitaine, chute d'Émeraude) ;
- **chansons** : 335 chansons de RF sur 346 sont identiques (octets joués) à leur équivalent dans la fusion. Les 11
  autres : fin de piste plus tardive (`MUS_LEVEL_UP`, `MUS_OBTAIN_ITEM` : inaudible, la fanfare s'arrête au bout de
  sa durée dans `sFanfares`, la même), priorité sur le lecteur de musique (sans effet), mini-jeu link
  (`SE_RG_POKE_JUMP_FAILURE`), et 4 vraies différences de version de RF : `MUS_SLOTS_JACKPOT` et `MUS_SLOTS_WIN`
  (volume 100 contre 90), `MUS_EVOLVED` (vélocités, une note), `SE_RG_CARD_FLIPPING` (une vélocité).
- **instruments** : les samples de RF sont à 13 379 Hz (ceux d'Émeraude, les mêmes instruments, à 42 048 ou 44 100 Hz)
  et sa batterie « rs » est recouverte par le groupe suivant au-delà de la note 40 ; les copies des musiques de RF
  dans Émeraude (`mus_rg_*`) jouent donc avec les instruments d'Émeraude.

**Décision (2026-11-02)** : on garde les copies d'Émeraude (instruments HQ, batterie complète) et ses versions des 4
sons qui diffèrent ; ce ne sont pas des manques à porter.

## Easy Chat (messages en mots choisis)

- **L'écran suit MENUS** : avec MENUS = KANTO, le profil, les phrases de combat (début, victoire, défaite), la LETTRE
  et le questionnaire s'ouvrent dans l'écran de RF (`src/kanto_easy_chat_2.c`, `_3.c` : `KEC_DoEasyChatScreen`) ; les
  autres types (Bard, interview, tendance, mot de passe de l'Antre…) n'existent qu'à Hoenn et gardent l'écran
  d'Émeraude. `include/kanto_easy_chat_internal.h` renomme ce que RF partage de nom avec Émeraude (préfixe `KEC_`).
- **Un seul dictionnaire** : les deux écrans lisent les mots d'Émeraude (`src/easy_chat.c`, `KEC_*` = enveloppes de
  ses fonctions) ; les 6 mots de RF que le jeu d'Émeraude gardait cachés (ROUGE, VERT, OR, ARGENT, FEUILLE, FLAMME,
  groupe DRESSEUR) sont activés. Les deux jeux ont les mêmes groupes et numéros de mots.
- **Les effets de fin suivent la région** (les scripts qui lisent le résultat sont ceux de la région), pas l'écran :
  | | Hoenn (Émeraude) | Kanto (RF) |
  |---|---|---|
  | Profil | `FLAG_SYS_CHAT_USED` | `FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE` ; `VAR_0x8004` = 1 si la phrase n'est pas `EC_WORD_EVENT MYSTERY IS EXCITING` (club Événement Mystère de Kanto) |
  | Questionnaire | `VAR_0x8004` = 2 si la phrase du Cadeau Mystère, sinon 0 | `VAR_0x8004` = 1 si la phrase n'est pas `EC_WORD_LINK WITH CASE TRAINER` |
  Avant le 2026-11-02, le profil fait à Kanto laissait `VAR_0x8004` à 0 (son type d'écran) : le club répondait
  toujours comme à la phrase secrète. Fonctions : `KEC_SetKantoResult`, `EasyChat_SetHoennResult`.
- **Sur PC**, l'OAM n'est pas à `VRAM + 0x1000000` (adresse de la GBA) : `KEC_LoadEasyChatGraphics` vide `OAM`.
- Scénarios : `kanto_easy_chat` (écrans de RF, LETTRE), `easy_chat_regions` (les 4 combinaisons région × écran).

## Comportements de la GBA que le PC doit refaire (UBFIX)

Une lecture hors limites ou mal alignée ne plante pas une GBA : elle lit autre chose, toujours la même chose. Le PC
doit refaire cette valeur quand on la connaît, sinon garder le comportement en évitant la lecture :
- **u16 lu à une adresse impaire** (`LDRH`) : le demi-mot de l'adresse paire d'avant, tourné de 8 bits (GBATEK). Les
  scripts d'IA (`if_has_move`) en dépendent ; la parité des adresses y est la même que sur la cartouche (pointeurs
  de 8 octets au lieu de 4).
- **Case après la fin d'un tableau en EWRAM** : la variable déclarée juste après dans le même fichier (ordre de
  `sym_ewram.txt`) : `gActionsByTurnOrder[4]` = `gBattlerByTurnOrder[0]`.
- **Division par zéro** : 0.
- **Avant le début d'une table en ROM** (`Sin` avec un indice négatif) : contenu inconnu ; on prend la lecture que le
  code voulait faire (indice non signé).
Les scénarios de défis (`challenge_*`) sous ASan ont trouvé ces cas ; `docker/test-sanitize.sh` les vérifie.

## Ce que l'explorateur ne fait pas (à tester autrement)

Limites connues, qui restent dans ses « interactions en erreur » sans être des bugs :
- **MARC** (Grotte Originelle B1F) repose sa question tant qu'on ne répond pas PILIER CELESTE (3ᵉ choix) ; l'explorateur
  répond A (1ᵉʳ choix) ou B (« Aucun souvenir »).
- **Le garçon de l'Arène de Clémenti-Ville** : la case à côté de lui déclenche sa visite de l'Arène à chaque
  téléport, le budget s'épuise.
- PNJ « insaisissables » (ils marchent sans cesse, Koichi Route 115) et « inaccessibles » (décor du camion, panneaux
  au-dessus d'un mur, tunnel de l'Île 3 derrière des rochers) : listés à part.

- **Salles de défi, de concours, de link** (Zone de Combat, Tentes, Mont Combat, Pyramide, concours, Colisée,
  Centre Troc, Union Room) : on n'y entre que pendant un défi. Par téléport, hors défi, un combat démarre sans
  données (division par zéro en `CB2_HandleStartBattle`, 0xc0000094) : pas un chemin du jeu. Les défis eux-mêmes
  sont joués par `challenges.py` (scénarios `challenge_*`, voir plus haut) ; restent les salles de link.
- **Bases Secrètes** (`SecretBase_*`) : la salle se charge avec la base du joueur, ou une base reçue par Record Mixing
  (link). Par téléport, sans base chargée, le dresseur de la base lance un combat de Base Secrète sans données
  (division par zéro dans son équipe) : à vérifier avec le Record Mixing, en phase 5 (link).
- **Dresseur E-Reader** de l'Île 7 (`SevenIsland_House_Room2`, où l'on n'entre par `SevenIsland_House_Room1` que si
  un dresseur E-Reader est enregistré) : `BufferEReaderTrainerGreeting` et `StartSpecialBattle` sont encore des stubs
  (link / E-Reader : à porter, désactivés).
