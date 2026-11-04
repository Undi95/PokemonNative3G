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
| MENUS (11) | menu Start (police RF, entrées tous les 15 px, aide en bas), équipe (palette RF), résumé (écran de RF : 3 pages), boutique (écran d'achat de RF), PC (menus), écran des noms, maître des capacités ; depuis le 2026-11-02, les choix multiples des scripts (`DrawVerticalMultichoiceMenu` de RF : `FONT_KANTO`, lignes de 14 px, fenêtre de `GetMCWindowHeight` : 7 tiles pour 4 choix), leur grille (tableau de l'école de Jadielle), le menu « Accéder à quel PC? » (texte 1 px plus bas) et le OUI / NON (6 × 4 tiles au lieu de 5 × 4, lignes de 14 px) ; les touches comptent dès la 1ʳᵉ image (Émeraude attend 2 images) — scénario `kanto_menus_rf` ; la lecture d'une lettre (`kanto_mail.c` : message en (3,4), signature dans sa fenêtre en (15,15), `FONT_KANTO` ; mêmes images de lettres) — scénario `kanto_mail` ; l'écran Options (celui de RF dans `option_menu.c` : bandeau « CHOIX / CHANGER / ANNUL. », titre au cadre standard de RF, une valeur rouge par ligne de 13 px, ◀▶ change, A ou B ferme, ligne choisie éclairée ; avec les 2 pages de la fusion (L/R) et 7 lignes visibles qui défilent ; MODE BOUTONS commence à NORMAL : l'aide de RF est écartée) — scénario `kanto_options_rf` ; les boîtes d'argent et de jetons des scripts (`Kanto_DrawMoneyBox`, `Kanto_ShowCoinsWindow` : 8 × 3, « ARGENT » / « JETONS » en `FONT_KANTO`, montant en petite police, cadre standard de RF en 0x21D palette 13 ; les scripts de RF placent la boîte des jetons par son cadre, ceux d'Émeraude par sa fenêtre : `ScrCmd_showcoinsbox` corrige, aussi avec la boîte d'Émeraude ; la roulette de Lavandia garde la sienne) — scénario `kanto_money_coins_box`, les flèches de la boîte aux lettres du PC — scénario `kanto_mailbox`, et la fenêtre d'infos de la sauvegarde (2026-11-03, `kanto_save_menu_util.c` : `PrintSaveStats` de RF, 14 × 9 en (1,1) même sans Pokédex, lieu centré en bleu, libellés et valeurs en petite police, cadre standard de RF en 0x21D palette 13 ; badges et Pokédex de la région où l'on sauvegarde, comme le menu principal de RF ; MENUS = HOENN : celle d'Émeraude, 14 × 10 ou 14 × 8, qui compte toujours les badges et le Pokédex de Hoenn) — scénario `kanto_save_window` | la carte de dresseur (voir plus bas) |
| BOITES COMBAT (12) | les boîtes de combat (action, capacités, PV) | — |
| SAC (13) | le sac : Émeraude (5 poches, CT & CS, BAIES) ou RF (3 poches ; BOITE CT et SAC A BAIES en OBJ. RARES) ; aussi le sac de la démonstration du vieil homme de Jadielle (Wally d'Émeraude ou `InitOldManBag` de RF, scénario `kanto_old_man_bag`) | — |
| POKéMON (14) | les sprites des Pokémon (Émeraude animés, RF) ; à l'éclosion d'un œuf, avec les sprites de RF : le cri seul et son attente, Pokémon en y 70 + son `y_offset` (`CB2_EggHatch_1` de RF ; Émeraude : animation, y 75) — scénario `egg_hatch_kanto` | — |
| JOUR/NUIT (16) | la teinte du terrain, qui tient pendant la transition vers un combat (`CB2_OverworldBasic`) jusqu'au fondu ; pas de teinte dans l'écran de combat | — |

## Écrans et ce qu'ils doivent montrer

| Écran | Attendu | Piège connu |
|---|---|---|
| Carte de dresseur | le style suit la **région** (`Fusion_IsInKanto` dans `ShowPlayerTrainerCard`), pas MENUS ; SELECT passe à l'autre carte ; le sprite suit PERSO ; les deux points de la DUREE JEU clignotent (une capture peut les montrer éteints). Carte de Kanto = **`trainer_card.c` de RF** (`kanto_trainer_card.c`, depuis le 2026-11-04) : « NOM /… », argent et POKéDEX alignés à droite vers 134 px, ID centré sur 88 px, heure du Panthéon en x = 164 au dos ; étoiles (Panthéon avec date, Pokédex de Kanto, Pokédex national, 200 baies et 200 sauts) → bleue, verte, bronze, argent, or ; au dos les icônes de la photo du Casino de Céladopole et les STICKERS de l'homme de l'Île 4 (en haut à gauche) ; Pokédex de Kanto tant que le national n'est pas obtenu ; pas de phrase de profil sur sa propre carte (RF ne l'écrit qu'en link) | avant le 2026-11-02, la carte de Kanto prenait les données d'Émeraude : ni photo ni sticker, étoiles d'Émeraude ; jusqu'au 2026-11-04, la branche « carte de RF » d'Émeraude, placée autrement (scénarios `kanto_card_stickers`, `trainer_card_regions`) |
| Panneau du nom de lieu | suit la **région** (choix user 2026-11-02, comme la carte de dresseur) : à Kanto, celui de RF (`kanto_map_name_popup.c` : boîte blanche au cadre standard, collée au bord haut, 2 px par image, 120 images ; l'étage des cartes, `floorNum` dans l'octet libre de `MapHeader` d'Émeraude : « SYLPHE SARL 4ᵉ » pour le 5F, « REPAIRE ROCKET 2 SS », « CELADOPOLE TOIT ») ; en passant une connexion, seulement si la section change ; après l'aperçu d'une grotte (Mont Sélénite, Repaire Rocket), le panneau vient une fois la carte chargée ; à Hoenn, le panneau en bois d'Émeraude | les étages de Kanto manquaient à l'import (`tools/kanto/add_floor_numbers.py`, `import_kanto.py` les garde) ; scénario `kanto_map_popup` |
| Effacement de la sauvegarde (Haut + SELECT + B sur l'écran titre) | suit Options > TITRE : avec R.FEU, l'écran de RF (`kanto_clear_save_data_screen.c` : question en bas au cadre standard de RF, OUI / NON de RF en haut à gauche, NON par défaut) ; fond **vert vif** : RF ne charge pas la palette 0, il reste la couleur 0 du logo de l'écran titre (0, 248, 40), comme sur la cartouche ; `Platform_StoreSaveFile` après `ClearSaveData`, comme l'écran d'Émeraude du portage | scénario `kanto_clear_save` |
| Menu principal | suit Options > TITRE : celui d'Émeraude après l'écran titre d'Émeraude ; celui de RF (`kanto_main_menu.c`) après l'écran titre de RF : CONTINUER (JOUEUR, DUREE JEU, POKéDEX, BADGES de la région où reprend la sauvegarde, `Fusion_IsSaveInKanto`), NOUVELLE PARTIE, CADEAU MYST. ; pas d'OPTIONS (comme RF) ; fond assombri sauf la fenêtre choisie (WIN0) ; NOUVELLE PARTIE → discours du Prof. Seko (`StartNewGameBirchSpeech`), B → écran titre | scénario `kanto_main_menu` |
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

| État | Ce que c'est | Dernier passage (2026-11-04) |
|---|---|---|
| `debut` | sauvegarde de début de partie de chaque région | 811 cartes, 4 565 interactions, 827 combats, 0 erreur de carte, 0 anomalie, 0 texte suspect (aussi avec DIALOGUE = KANTO) |
| `champion` | Hoenn fini (`FLAG_SYS_GAME_CLEAR`, 8 badges, Pokédex, PokéNav) : l'arrivée réelle à Kanto, le ferry ne part qu'après la Ligue de Hoenn | 811 cartes, 0 erreur de carte, 0 anomalie |
| `fin` | les deux Ligues finies, comme le menu DEBUG (« Deux Ligues finies », POKé MONTURE + badges, passes, Pokédex, objets) | 811 cartes, 4 564 interactions, 859 combats, 0 erreur de carte, 0 anomalie |
| `histoire` | `fin` + toute l'histoire des deux régions (`scripts.histoire 2` : drapeaux et variables d'avancement déduits des scripts, sans sauvegarde) | 811 cartes, 4 414 interactions, 781 combats, 0 erreur de carte, 0 anomalie, 0 texte suspect |

Dans chaque passage, seules restent les limites connues de l'explorateur (section « Ce que l'explorateur ne fait
pas ») : MARC, le garçon de Clémenti-Ville, la pente de la Piste Cyclable, et la porte de la maison de Bourg Palette
une fois achetée (elle n'affiche plus rien, on entre directement). La grille (`matrix.py`, 18 jeux) : 0 erreur,
0 anomalie ; planches relues le 2026-11-04.

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
Même chose pour les dresseurs de Kanto (numéros à partir de `KANTO_TRAINERS_START` = 864, au-delà de
`TRAINERS_COUNT`) : un test `trainerId < TRAINERS_COUNT` d'Émeraude les exclut. Trouvé ainsi (2026-11-02) : l'échange
classe / nom de la version française (`BufferStringBattle`), qu'Émeraude fait pour MAGMA et AQUA et RF pour la TEAM
ROCKET (`Localize_BattleStrings`) : « SBIRE TEAM ROCKET » (scénario `kanto_rocket_grunt`).

## Terrain des métatuiles de Kanto (RF)

RF range dans chaque métatuile, en plus du comportement, un type de rencontre (aucune, sol, eau) et un terrain (normal,
herbe, eau, cascade). La fusion les garde dans les bits libres de l'attribut d'Émeraude : rencontre en bits 8-9,
terrain en bits 10-11 (`tools/kanto_tile_attributes.py` ; 0 sur les tilesets de Hoenn ; `carte.metatuiles X Y` les
affiche). RF décide avec eux, Émeraude avec le comportement :
- rencontres sauvages de chaque case (`MapGridGetMetatileEncounterTypeAt`, wild_encounter.c) ;
- eau en face du joueur, pour le Surf et les cannes (`MetatileAtCoordsIsWaterTile`, `IsPlayerFacingSurfableFishableWater`) :
  sur la plage de la Route 18, le rivage de l'étang a le comportement « océan » mais pas le terrain « eau », donc pas de
  Surf depuis le sable ;
- herbe que COUPE tond (`MetatileAtCoordsIsGrassTile`, `SetCutGrassMetatileAt`, carré de 3 × 3 autour du joueur, sans
  Hyper Cutter) : herbe haute, cimes d'arbre sur herbe, herbe de la Piste Cyclable, du Parc Safari, de la Forêt de Jade.
À Kanto, les numéros de métatuile sont ceux de RF (le primaire de RF, 640 métatuiles, est coupé en 512 + les 128
dernières en tête de chaque secondaire) : les `METATILE_*` de `constants/kanto/metatile_labels.h` s'emploient tels
quels, ceux d'Émeraude (`constants/metatile_labels.h`) désignent d'autres métatuiles. Scénario `kanto_cut_surf`.

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
- **Copie plus longue que le tableau, dont le surplus ne sert pas** : on copie le tableau seul. Éclosion d'un œuf
  (Émeraude et RF) : 5 palettes depuis `gTradeGba2_Pal` qui en a 3 (palettes 4 et 5 inutilisées), 0x1420 octets de
  tiles depuis `gTradeGba_Gfx` qui en a 0x1400 (le tile 160 n'est pas dans la carte de la plateforme).
- **Fenêtre absente ou déjà supprimée** : rien. Lettre d'Émeraude : `PrintMailText` écrit dans une fenêtre 1 qui
  n'existe pas ; OUI / NON effacé deux fois (`Menu_ProcessInputNoWrapClearOnChoose` puis l'écran d'effacement de RF) :
  `EraseYesNoWindow` ne refait rien, comme `DestroyYesNoMenu` de RF à partir de `REVISION 0xA`.
- **Personne en face** (`GetObjectEventIdByPosition` rend `OBJECT_EVENTS_COUNT`) : pas d'objet. COUPE ou ÉCLATE-ROC
  depuis l'équipe sans rien en face : `CheckObjectGraphicsInFrontOfPlayer` (Émeraude et RF) lisait `gObjectEvents[16]`,
  après le tableau, jamais un arbre ni un rocher : FALSE.
Les scénarios de défis (`challenge_*`) sous ASan ont trouvé ces cas ; `docker/test-sanitize.sh` les vérifie (les
derniers : `egg_hatch_kanto`, `kanto_mail`, `kanto_clear_save`, `kanto_cut_surf`, le 2026-11-02).

## Ce que l'explorateur ne fait pas (à tester autrement)

Limites connues, qui restent dans ses « interactions en erreur » sans être des bugs :
- **MARC** (Grotte Originelle B1F) repose sa question tant qu'on ne répond pas PILIER CELESTE (3ᵉ choix) ; l'explorateur
  répond A (1ᵉʳ choix) ou B (« Aucun souvenir »).
- **Le garçon de l'Arène de Clémenti-Ville** : la case à côté de lui déclenche sa visite de l'Arène à chaque
  téléport, le budget s'épuise.
- PNJ « insaisissables » (ils marchent sans cesse, Koichi Route 115) et « inaccessibles » (décor du camion, panneaux
  au-dessus d'un mur, tunnel de l'Île 3 derrière des rochers, dresseurs de l'énigme 7 de la Maison des Pièges derrière
  ses portes tournantes) : listés à part. On ne parle à deux cases que par-dessus un comptoir (`MB_COUNTER`, comme
  `GetInteractedObjectEventScript`), jamais à travers un mur.
- **Objets cachés renouvelables de RF** (Forêt Baie, Plage Trésor, Île 5, Souterrains, Mont Sélénite… : 67) : RF les
  marque pris au début de la partie (`SetAllRenewableItemFlags`) et en fait revenir au hasard avec les pas
  (`kanto_renewable_hidden_items.c`) ; l'explorateur les compte « déjà pris », avec les objets « sous les pieds »
  (trouvés au CHERCH'OBJET).
- **Bas de la Piste Cyclable** (Route 17 : panneau en (11, 157), MAX ELIXIR caché en (14, 157)) : la pente fait glisser
  le joueur vers le bas (`MB_CYCLING_ROAD_PULL_DOWN`) avant que l'explorateur appuie sur A ; mêmes données que RF.

- **Salles de défi, de concours, de link** (Zone de Combat, Tentes, Mont Combat, Pyramide, concours, Colisée,
  Centre Troc, Union Room) : on n'y entre que pendant un défi. Par téléport, hors défi, un combat démarre sans
  données (division par zéro en `CB2_HandleStartBattle`, 0xc0000094) : pas un chemin du jeu. Les défis eux-mêmes
  sont joués par `challenges.py` (scénarios `challenge_*`, voir plus haut) ; restent les salles de link.
- **Bases Secrètes** (`SecretBase_*`) : la salle se charge avec la base du joueur, ou une base reçue par Record Mixing
  (link). Par téléport, sans base chargée, le dresseur de la base lance un combat de Base Secrète sans données
  (division par zéro dans son équipe) : pas un chemin du jeu ; le Record Mixing est du link, caché (`LINK_ENABLED`).
- **Dresseur E-Reader** de l'Île 7 (`SevenIsland_House_Room2`, où l'on n'entre par `SevenIsland_House_Room1` que si
  un dresseur E-Reader est enregistré) : porté le 2026-11-04 (`kanto_battle_tower.c`) ; sans e-Reader, l'outil
  `combat.ereader 1` enregistre l'équipe du joueur (scénario `kanto_ereader_house` : porte ouverte, choix de 3
  POKéMON, sauvegarde, combat e-Reader, adieu, commentaire de la vieille dame).

## Link (caché en jeu)

Décision du 2026-11-02 : le link est codé et caché jusqu'à la phase multijoueur. `LINK_ENABLED` (`include/config.h`,
FALSE) est lu par le special `Fusion_IsLinkEnabled` au début de chaque entrée : hôtesses de l'Union Room et du coin
direct des 2ᵉ étages (les deux régions : « Le CLUB SANS FIL POKéMON est encore en préparation », le message d'avant
le POKéDEX), guichet des concours en link et Mixeur à plusieurs de Nénucrique, combats multi en link de la Tour de
Combat (« Ils sont en train d'effectuer des réglages… ») — scénario `link_disabled`. Le link est celui d'Émeraude dans
les deux régions (règle des variantes du code commun) ; les salles de Kanto y mènent par `EnterTradeSeat` et
`EnterColosseumPlayerSpot` de RF. Restent ouverts, comme dans les deux jeux : le moniteur sans fil (« L'adaptateur
sans fil GBA n'est pas connecté correctement. ») et l'écran des records des 2ᵉ étages (scénario `kanto_center_2f`).
