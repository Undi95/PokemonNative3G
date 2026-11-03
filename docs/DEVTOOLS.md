# Outils de debug (builds DEBUG)

Les mêmes commandes, de trois façons : **toi** par le menu DEBUG du jeu, **moi** par le banc headless ou par la
console d'une partie qui tourne. Une commande ajoutée au registre apparaît partout. Uniquement dans les builds
`KANTO_DEBUG=1` (build de test `out/winwsl`, APK debug) ; la release n'en a rien.

## Utilisation

| Où | Comment |
|---|---|
| **En jeu** | Menu Start > DEBUG > **Outils (sondes)** : catégorie, commande, nombres (HAUT/BAS change le chiffre, GAUCHE/DROITE choisit le chiffre, A valide), puis le résultat : HAUT/BAS une ligne, GAUCHE/DROITE une page, **A relance** (état en direct), B revient. |
| **Banc headless** | `game.dev("gfx.sprites")` dans un scénario (texte, fonctions et données nommées) ; ligne d'entrée `!dev ID ARGS`. |
| **Partie en cours (PC)** | La build DEBUG écoute sur `127.0.0.1:7777` (`--devtools PORT`, `0` = sans). `python test/headless/dev.py jeu.etat`, `dev.py capture image.png` (dernière image), `dev.py touche A+UP 10` (appuie 10 images, en plus du joueur), `dev.py touches 20` (les 20 dernières plages de touches **reçues par le jeu** : clavier, manette, écran tactile, console ; 1re ligne `image I`, puis `DÉBUT IMAGES BOUTONS`), `dev.py` seul = une commande par ligne. Bancs Windows, Linux et Android qui s'en servent : `tools/env/README.md`. |
| **Partie en cours (téléphone)** | APK debug branché en USB : `adb forward tcp:7777 tcp:7777`, puis les mêmes `dev.py`. |

`aide` donne la liste à jour (c'est elle qui fait foi, pas ce fichier).

## Commandes (2026-11-02)

| Catégorie | Commande | Ce qu'elle lit |
|---|---|---|
| Jeu | `jeu.etat` | callbacks (cb1, cb2, VBlank, HBlank), fondu, verrous, tâches actives |
| | `jeu.options [N V]` | toutes les options (bits de la sauvegarde) ; `N V` met l'option N à V |
| | `jeu.murs [1\|0]`, `jeu.rencontres [1\|0]` | traverser les murs, Pokémon sauvages (les réglages du menu DEBUG) |
| | `jeu.safari [PAS [BALLS]]` | Parc Safari : en mode Safari ou non, pas restants, SAFARI BALLS ; les met (fin du temps ou des balls en un pas, scénario `kanto_safari_exit`) |
| | `joueur.lettre N OBJET [1\|2]` | lettre `ITEM_*_MAIL` à 9 mots (Easy Chat) signée du joueur, donnée au Pokémon `N` de l'équipe ; `1` ouvre l'écran de lecture (`ReadMail`, retour sur la carte), comme LIRE dans le menu de l'équipe (scénario `kanto_mail`) ; `2` l'envoie dans la boîte aux lettres du PC (`TakeMailFromMonAndSave`, comme ENVOYER AU PC ; scénario `kanto_mailbox`) |
| | `joueur.oeuf N` | le Pokémon `N` de l'équipe devient un œuf prêt à éclore ; `scripts.lancer EventScript_EggHatch` avec `VAR_0x8004 = N` le fait éclore (scénario `egg_hatch_kanto`) |
| | `jeu.hasard [GRAINE]` | état du hasard (`gRngValue`, `gRng2Value`) ; `GRAINE` les fixe : la suite d'un scénario (rencontre, combat) ne dépend plus du minutage d'avant, le hasard avançant à chaque image (scénarios `kanto_rival`, `kanto_bag_battle` : graine 4) |
| | `joueur.pv N PV` | PV du Pokémon `N` de l'équipe (au plus ses PV max) ; à régler **avant** un combat, ses PV y sont copiés (scénario `kanto_whiteout` : 1 PV, K.O. au premier coup) |
| | `joueur.statut N [STATUT]` | statut du Pokémon `N` (`STATUS1_*` : 1 à 7 endormi pour autant de tours, 8 poison, 16 brûlure, 32 gel, 64 paralysie, 128 poison grave) ; à régler **avant** un combat, il y est copié (scénario `kanto_poke_flute_wake`) |
| | `joueur.dresseur N ID` | dresseur d'origine (ID) du Pokémon `N` : un autre ID que celui du joueur = un Pokémon échangé (obéissance selon les badges, plus d'expérience). Le Pokémon est recréé (même espèce, niveau, personnalité, capacités, PP) : ses données sont chiffrées avec l'ID (scénario `obedience_regions`) |
| | `jeu.stat N [V]` | statistique de jeu `GAME_STAT_*` (nombre d'entrées au Panthéon, date de la première, œufs éclos, victoires en link…), mise à `V` si donné (scénario `kanto_card_stickers`) |
| | `jeu.pokedex [N [1]]` | Pokédex reçus (Hoenn, Kanto, national), vus et attrapés dans chaque Pokédex (ce que comptent les cartes de dresseur des deux régions, le PC du Prof. Chen), puis les numéros nationaux des Pokémon attrapés ; `N` marque les numéros 1 à `N` vus et attrapés (386 : POKéDEX NATIONAL complet, scénario `fusion_charms`) ; `1` en plus donne le POKéDEX NATIONAL (`EnableNationalPokedex`, scénario `kanto_oak_rating`) |
| | `jeu.errants [1\|2]` | Pokémon errants de la région (espèce, niveau, actif, carte, PV, statut, IV) ; `1` les lâche (`InitRoamer`, comme leur script), `2` les met sur la carte du joueur jusqu'au prochain changement de carte (scénario `kanto_roamer`) |
| | `jeu.peche` | chaîne de pêche : POKéMON remontés d'affilée au même endroit, canne, tirages chromatiques en plus pour la prise en cours, cannes améliorées (scénario `fishing_chain_more`) |
| | `jeu.menustart` | entrées du menu Start (`MENU_ACTION_*`) et curseur (`game.start_menu()` dans le banc) |
| | `jeu.debug [N]` | les actions du menu DEBUG ; `N` fait l'action N (celles sans écran : soins, objets, Pokédex, passes, « Deux Ligues finies », POKé MONTURE + badges…), le même code que le menu (`DebugMenu_ApplyAction`) |
| Carte | `carte.info` | carte, section, région, disposition, météo, musique, étage (`floorNum` : panneau de RF), joueur, déplacement (direction, état de course, vitesse et compteur du vélo, mouvement en cours), connexions |
| | `carte.objets` | objets actifs : id, sprite, position, mouvement |
| | `carte.grille` | **la carte telle qu'elle est en jeu**, avec les lettres de `test/headless/maps.py` (`#` bloqué, `g` herbe, `~` eau, `o` trou où l'on tombe, `<>^v` rebord ; les chemins évitent les trous sauf s'ils sont le but) : les étages générés (Mont Combat, Pyramide) et les cases changées par les scripts (`setmetatile`), que les fichiers de la carte ne montrent pas. Dans le banc : `live_map(game)` (un `maps.GridMap`), `walk_to(..., live=True)` |
| | `carte.metatuiles X Y [L H]` | les métatuiles en jeu (coordonnées de `carte.grille`) : numéro, comportement, et à Kanto le **terrain** (0 normal, 1 herbe, 2 eau, 3 cascade) et le **type de rencontre** de RF (0 aucune, 1 sol, 2 eau), élévation, collision ; 3 × 3 autour de X Y, ou L × H depuis X Y. Pour vérifier une case changée par un script ou un effet (COUPE : scénario `kanto_cut_surf`) |
| Scripts | `scripts.contexte` | contextes global et immédiat : script en cours (label), pile |
| | `scripts.lancer @ADRESSE` | lance un script de carte, joueur libre (`game.script("EventScript_PC")` : le banc donne l'adresse par le nom) |
| | `scripts.flag N [V]`, `scripts.var N [V]` | lit ou met un flag, une variable (avec son nom) |
| | `scripts.drapeaux [CAT]` | **tous les drapeaux, dresseurs et variables du jeu**, par région et catégorie (système, badges, personnages cachés, objets, cadeaux, combats, PokéNav, carte, temporaires, dresseurs, variables…) : sans argument les catégories (combien à ON), avec `CAT` chaque nom et son état. Dans le menu : un curseur, **A** ouvre une catégorie ou bascule ON/OFF (une variable : remise à 0), **L / R** variable -1 / +1, B revient. Les noms viennent de `tools/debug_names.py` → `src/data/debug_names.h` |
| | `scripts.histoire [N]` | **l'histoire finie sans sauvegarde** : `0` Hoenn, `1` Kanto, `2` les deux. Met chaque drapeau que les scripts mettent et ne retirent jamais (hors objets, cachés, temporaires, quotidiens), et chaque variable d'avancement à la dernière valeur que les scripts lui donnent (pas les variables remises à 0 : files d'attente, salles de défi). Déduit des scripts par `tools/debug_states.py` → `src/data/debug_states.h` (`--liste` les montre) |
| Joueur | `joueur.equipe` | équipe : espèce, PV, objet, dresseur d'origine, lieu et jeu de rencontre, amitié, capacités et leurs PP |
| | `joueur.sac` | argent, poches, objets du PC, objet enregistré sur SELECT |
| | `joueur.poudre [N]` | Poudre Baie ; `N` en ajoute (scénario `kanto_specials_b` : vendeur d'Azuria) |
| | `joueur.amitie N [V]` | amitié du Pokémon N ; `V` la met (0-255 ; Daisy, tuteur du Cap Falaise) |
| | `joueur.enregistre OBJET` | l'objet enregistré sur SELECT (scénario `fishing_chain_more` : la canne) |
| | `joueur.objetpc OBJET N` | dépose N objets au PC du joueur (`AddPCItem`), sans passer par le sac (scénario `kanto_item_pc_more`) |
| | `joueur.jetons [N]` | jetons du Casino ; `N` les met (au plus 9 999) (scénario `kanto_money_coins_box`) |
| | `joueur.capacite N PLACE CAPACITE [PP]` | donne une capacité (et ses PP) au Pokémon N, à la place 0-3 ; `PP` : PP restants, moins que le maximum (HUILE, scénario `kanto_item_use_scenes`) ; capacité `0` : place vide |
| Combat | `combat.etat` | type, combattants, contrôleurs |
| Graphismes | `gfx.sprites` | sprites : position, tile, palette, priorité, animation (finie, en pause), callback |
| | `gfx.palette TYPE BANQUE` | 16 couleurs (0 BG, 1 OBJ) : non fondues, fondues, à l'écran (après jour/nuit) |
| | `gfx.bg` | registres d'affichage et des 4 BG |
| | `gfx.bgligne BG RANGÉE` | 32 cases `tile:palette` de la carte du BG en VRAM |
| | `gfx.tile BLOC TILE` | indices de couleur d'un tile 4bpp |
| | `gfx.fenetres` | fenêtres ouvertes |
| Texte | `texte.imprimantes` | textes en train de s'écrire : police, couleurs, position |
| Son | `son.etat` | musique et effets en cours |
| Système | `sys.etat` | RNG, ID dresseur (public, secret), drapeaux d'après-Ligue (`specialSaveWarpFlags`, `gcnLinkFlags`), heure du jeu, teinte jour/nuit |
| | `sys.anomalies` | anomalies vues par les détecteurs depuis le lancement |
| | `sys.sauvegarde` | tailles des blocs dans cette build (SaveBlock2, SaveBlock1 au format GBA, PC) et chaque secteur des deux emplacements du fichier : vide, id, compteur, checksum OK / FAUX pour cette build (« ancien format Windows » : sauvegarde Windows 1.0-1.1, convertie au chargement) ; compteur et état chargés |

Avant le chargement de la sauvegarde (écran de copyright), les outils qui lisent SaveBlock1 (carte, scripts, joueur,
la plupart de « jeu ») répondent « pas encore de sauvegarde chargée », et ceux de la carte « pas de carte chargée »
tant qu'aucune carte n'est chargée (intro, menu principal, discours de Birch) : ils faisaient planter le jeu. Le
banc Windows (`test/desktop/run.py outils`) les lance tous à chaque étape.
| | `sys.rapport` | rapport de bug rejouable (voir plus bas) |

Partout (banc, console, menu), un argument peut être un **nom** de drapeau, de variable ou de dresseur au lieu d'un
nombre : `dev.py scripts.flag FLAG_SYS_GAME_CLEAR 1`, `game.dev("scripts.var", "VAR_KANTO_MAP_SCENE_VIRIDIAN_CITY", 2)`.
`tools/debug_names.py --check` et `tools/debug_states.py --check` (lancés par `test-release.sh`) vérifient que les
tables générées suivent les en-têtes et les scripts.

## Rapport de bug rejouable

Menu DEBUG > **Rapport de bug** (ou `sys.rapport`) écrit `rapport_DATE.tar` : `rapports/` dans le dossier des
données sur PC, `Android/data/fr.undi.pokemonnative3g.debug/files/rapports/` sur le téléphone, où le partage est
proposé tout de suite (mail, messagerie, Drive… : `GameActivity.shareReport`, `ReportProvider`). Il contient :

| Fichier | Contenu |
|---|---|
| `rapport.txt` | l'heure du lancement et du rapport, puis l'état du jeu par les outils (anomalies, moteur, options, carte, scripts, équipe, sac, combat, textes, fenêtres, BG, sprites, son, système) |
| `touches.txt` | les touches de chaque image depuis le lancement (entrée du banc headless) |
| `lancement.sav`, `maintenant.sav` | la sauvegarde au lancement (point de départ du rejeu) et maintenant |
| `capture.ppm`, `avant_00…19.ppm` | la dernière image, et les 10 secondes d'avant (une image toutes les 30) : ce qui était à l'écran avant d'ouvrir le menu |

`python test/headless/replay.py BINAIRE rapport.tar [--images N]` rejoue la session dans le banc (même sauvegarde,
même heure, mêmes touches, jeu déterministe) jusqu'au rapport, ou N images avant : `journal.txt`, `etat.txt`
(les outils à la fin), `shots/fin.ppm`, comparée à la capture du rapport. `report_check.py BINAIRE` vérifie toute la
chaîne avec la build DEBUG du PC (console, rapport, rejeu identique).

APK debug : `build-all.sh` produit `out/PokemonNative3G-VERSION-debug.apk` (variante `debugtools` de
`android/app/build.gradle`, build KANTO_DEBUG=1, nom « PN3G DEBUG », identifiant `fr.undi.pokemonnative3g.debug` :
s'installe à côté de la release, avec sa propre sauvegarde ; symboles dans ses assets pour nommer les fonctions).

## Anomalies (`src/debug_checks.c`)

Des détecteurs regardent le jeu pendant qu'il tourne (builds DEBUG) et signalent une fois par cause ce qui est
anormal : liste `sys.anomalies` (menu DEBUG > Outils > Système > Anomalies vues), console (`ANOMALIE …` sur stderr),
banc headless (journal `ANOMALIE détecteur : texte` ; le scénario échoue si `test/headless/anomalies_known.txt` ne
la connaît pas).

| Détecteur | Ce qu'il voit | Où |
|---|---|---|
| texte coupé | une lettre d'une police de l'option POLICE dont des pixels tombent hors de sa fenêtre | `text.c`, `IsGlyphInkOutsideWindow` |
| flèche hors fenêtre | la flèche d'attente (après `\l`, `\p`) dépasse du bord droit de sa fenêtre | `text.c`, `TextPrinterDrawDownArrow` |
| texte superposé | une lettre ou une icône (L, R…) d'un texte écrase l'encre d'un autre texte de la même fenêtre, commencé ailleurs, avec une lettre placée ailleurs (à plus de 2 pixels) ; redessiner un texte au même endroit n'en est pas un. Le message donne le pixel touché et les deux lettres | `text.c`, `CheckTextOverlap` ; ce que chaque pixel d'encre a écrit : `DebugChecks_GetTextOwners`, libéré par tout ce qui efface la fenêtre (`window.c`) |
| cadre de boîte | un cadre de boîte de dialogue dessiné avec une tile que le style chargé (Émeraude ou RF) ne place jamais | `DebugChecks_OnMessageBoxGfx` (chargement) + carte du BG en VRAM toutes les 8 images |
| Pokémon figé | un sprite de Pokémon (animations de face) qui garde son image 1 pendant 2 s | à chaque image |
| teinte jour/nuit coupée | la teinte cesse (option active) alors que les couleurs du terrain sont toujours à l'écran | `day_night.c` |
| special non porté | un special encore en stub est appelé | `kanto_specials_stubs.c` |

Chaque détecteur a été validé sur son bug avant la correction (2026-11-02 : boîte de l'intro avec DIALOGUE =
KANTO, sprite figé dans la fiche de RF, flèche hors de la boîte de RF, teinte coupée pendant la transition vers un
combat ; texte superposé : le titre des Options « L R PAGE 2/2 » sur « OPTIONS » en police KANTO, puis il a trouvé les
crédits de Kanto écrits sur une seule ligne).

## Explorateur et grille (connaître tout le jeu)

| Outil | Ce qu'il fait |
|---|---|
| `python test/headless/crawl.py BINAIRE [--cartes REGEX] [--jobs N] [--etat debut\|champion\|fin\|histoire]` | **Explorateur** (état de partie : `debut` la sauvegarde de début de partie, `champion` Hoenn fini = l'arrivée réelle à Kanto, `fin` les deux Ligues comme avec le menu DEBUG, `histoire` = `fin` + `scripts.histoire 2` : toute l'histoire des deux régions finie ; `build/headless/crawl-ETAT`) : chaque carte (914), depuis la sauvegarde de début de partie de sa région ; arrivée sur son premier warp et capture, puis téléport à côté de chaque PNJ (visé par son localId : l'état du banc donne `object_ids`), de chaque panneau (du bon côté) et de chaque objet caché, A jusqu'au bout (B pour sortir d'un menu), combats faits avec un MEWTWO N.100 aux 4 attaques (`joueur.capacite`), texte rapide et sans animations de combat. Style de combat DÉFINI (pas de « changer de POKéMON ? »). Salles de défi, de concours, de link et d'E-Reader listées à part (on n'y entre que pendant un défi) ; un PNJ qui lance un défi (écran de choix de la Zone de Combat, concours) est noté « défi lancé » ; Panthéon et crédits vont au bout. 20 000 images au plus par interaction (un script sans fin est une erreur, pas un gel du banc) ; un jeu qui plante est relancé. `build/headless/crawl/atlas.json` (textes, combats, anomalies, erreurs par carte et par interaction) et `rapport.txt` : anomalies, erreurs, PNJ muets ou inaccessibles, **textes suspects** (octet sans lettre `�`, code `{XX}` non remplacé, reste d'anglais). `--rapport-seul` refait le rapport depuis l'atlas. |
| `python test/headless/matrix.py BINAIRE [--ecrans REGEX] [--regions kanto,hoenn]` | **Grille options × écrans** : les 9 options d'affichage (PERSO, DIALOGUE, POLICE, POKéDEX, MENUS, BOITES COMBAT, SAC, POKéMON, JOUR/NUIT) en 9 combinaisons qui montrent chaque paire de valeurs, le cadre des fenêtres changé à chaque fois, dans les deux régions ; écrans : menu Start, équipe, résumé, sac, Pokédex, carte de dresseur (recto, verso, puis celle de l'autre région avec SELECT), sauvegarde, options, panneau, PNJ, boutique, PC, combat sauvage, combat de dresseur. Une planche par écran (`build/headless/matrix/planches/`, une ligne par jeu), anomalies et erreurs dans `rapport.txt`. |

### Défis (`test/headless/challenges.py`, scénarios `challenge_*`)

Le pilote des défis fait ce que ferait un joueur : il parle au préposé (ou monte sur la case de départ), répond aux
questions (A, ou les touches d'`ANSWERS` : « COMBATTRE » du Dôme), choisit l'équipe (le nombre lu dans le texte :
« les deux POKéMON » à chaque match du Dôme) ou les Pokémon de location, fait les combats (style DÉFINI), passe le
tableau du Dôme et l'échange de l'Usine. Libre dans une salle de défi, il marche sur la **grille en jeu**
(`carte.grille`) : il va parler à chaque dresseur, objet ou PNJ qu'il n'a pas encore abordé, sinon il prend une porte
plus haut que lui (jamais celle par laquelle il est entré ; la direction maintenue, pour les escaliers latéraux de
RF), sinon il fait un bout de marche.

| Paramètre de `run` | Sens |
|---|---|
| `battles` | combats gagnés attendus ; `0` : aucun (concours) |
| `rentals`, `walking` | un combat joué jusqu'au bout suffit : Pokémon loués tirés au hasard, ou défi qui remet l'issue à zéro (Antre, Pyramide, Mont Combat) |
| `reach` | une carte, ou une suite de cartes, à atteindre dans l'ordre après les combats : l'étage suivant du Mont Combat ou de la Tour Dresseur (il ne s'ouvre qu'aux vainqueurs), la salle du concours puis le hall |
| `trigger`, `flags`, `team`, `level` | case de départ (on y monte par le bas), drapeaux demandés (`FLAG_SYS_GAME_CLEAR` du Mont Combat), équipe (`TEAM` autorisée à la Zone de Combat ; `HILL_TEAM` de légendaires pour les combats doubles à deux dresseurs) et niveau |

Les 15 défis passent (2026-11-02) : Tour (simple, double), Dôme, Palais, Arène, Usine, Antre, Pyramide, les 3 Tentes,
Mont Combat, Tour Dresseur de l'Île 7, concours de Nénucrique. Ils ont trouvé deux plantages ou blocages du port PC :
la fiche du joueur dans le tableau du Dôme (division par zéro sans EV) et les étages du Mont Combat (voir
CONNAISSANCE-JEU.md).

### Sons

Chaque son lancé (`m4aSongNumStart` : PlaySE, sons des animations de combat `playsewithpan`, fanfares, musiques)
envoie un événement au banc (`TestState_OnSong`). Il va dans `game.sounds` et dans le journal (`SON SE_M_JUMP_KICK`,
`SON MUS_HEAL`) ; un scénario vérifie qu'un effet ou une fanfare a son son avec `expect_sound(game, "SE_…", image)`
(kanto_safari, kanto_sounds, battle_levelup_stripes, kanto_league_mugshot). Une fanfare se joue sur un autre lecteur
que la musique de la carte, qui garde son événement `MUSIQUE` (`expect_song`).

`tools/audit_sons.sh` (Docker, voir son en-tête) puis `python tools/audit_sons.py [pieges|fichiers|chansons]` :
les sons de Kanto sont-ils ceux de RF ? Constantes de même nom mais de son différent et leurs usages dans le code
venu de RF, mêmes sons fichier par fichier, chansons compilées des deux jeux comparées, samples (voir
CONNAISSANCE-JEU.md, « Sons de Kanto »). `fight_battle(game, watch=f)` appelle `f(game)` à chaque tour de sa boucle : un scénario y capture
un moment précis du combat (menu des capacités, montée de niveau).

## Architecture

| Fichier | Rôle |
|---|---|
| `include/debug_tools.h`, `src/debug_tools.c` | Registre (`gDebugTools`) et commandes. Le texte est en UTF-8 ; une adresse s'écrit `@N` (distance à `AgbMain`). |
| `src/debug_tools_menu.c` | Écran du menu DEBUG (listes, saisie des nombres, résultat défilant, police petite). |
| `include/debug_checks.h`, `src/debug_checks.c` | Détecteurs d'anomalies (signalement, détecteurs par image). |
| `src/platform/devtools.c` | Noms des adresses (fichier `.syms` à côté du jeu, posé par `docker/build.sh` : fonctions et données) et console TCP. |
| `src/platform/test_state.c` | Commande `!dev` du banc. |
| `test/headless/names.py` | `Symbols.expand` : `@N` → nom, côté banc. |
| `test/headless/dev.py` | Client de la console. |
| `test/headless/replay.py`, `report_check.py` | Rejeu d'un rapport, vérification de bout en bout. |
| `android/app/src/debugtools/`, `ReportProvider.java`, `GameActivity.shareReport` | APK debug : réseau local (console), partage des rapports. |

Ajouter une commande : une fonction `static void Cmd_X(const s32 *args, u32 argCount, struct DebugToolsOutput *out)`
qui écrit avec `DebugTools_Print`, son nom dans le jeu (`static const u8 sName_X[] = _("…")`) et une ligne dans
`gDebugTools` (id, catégorie, nom, aide, nombre d'arguments obligatoires).
