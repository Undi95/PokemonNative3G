# Outils de debug (builds DEBUG)

Les mêmes commandes, de trois façons : **toi** par le menu DEBUG du jeu, **moi** par le banc headless ou par la
console d'une partie qui tourne. Une commande ajoutée au registre apparaît partout. Uniquement dans les builds
`KANTO_DEBUG=1` (build de test `out/winwsl`, APK debug) ; la release n'en a rien.

## Utilisation

| Où | Comment |
|---|---|
| **En jeu** | Menu Start > DEBUG > **Outils (sondes)** : catégorie, commande, nombres (HAUT/BAS change le chiffre, GAUCHE/DROITE choisit le chiffre, A valide), puis le résultat : HAUT/BAS une ligne, GAUCHE/DROITE une page, **A relance** (état en direct), B revient. |
| **Banc headless** | `game.dev("gfx.sprites")` dans un scénario (texte, fonctions et données nommées) ; ligne d'entrée `!dev ID ARGS`. |
| **Partie en cours (PC)** | La build DEBUG écoute sur `127.0.0.1:7777` (`--devtools PORT`, `0` = sans). `python test/headless/dev.py jeu.etat`, `dev.py capture image.png` (dernière image), `dev.py` seul = une commande par ligne. |

`aide` donne la liste à jour (c'est elle qui fait foi, pas ce fichier).

## Commandes (2026-11-02)

| Catégorie | Commande | Ce qu'elle lit |
|---|---|---|
| Jeu | `jeu.etat` | callbacks (cb1, cb2, VBlank, HBlank), fondu, verrous, tâches actives |
| | `jeu.options [N V]` | toutes les options (bits de la sauvegarde) ; `N V` met l'option N à V |
| Carte | `carte.info` | carte, section, région, disposition, météo, musique, joueur, connexions |
| | `carte.objets` | objets actifs : id, sprite, position, mouvement |
| Scripts | `scripts.contexte` | contextes global et immédiat : script en cours (label), pile |
| | `scripts.flag N [V]`, `scripts.var N [V]` | lit ou met un flag, une variable |
| Joueur | `joueur.equipe` | équipe : espèce, PV, objet, dresseur d'origine, lieu et jeu de rencontre |
| | `joueur.sac` | argent, poches |
| Combat | `combat.etat` | type, combattants, contrôleurs |
| Graphismes | `gfx.sprites` | sprites : position, tile, palette, priorité, animation (finie, en pause), callback |
| | `gfx.palette TYPE BANQUE` | 16 couleurs (0 BG, 1 OBJ) : non fondues, fondues, à l'écran (après jour/nuit) |
| | `gfx.bg` | registres d'affichage et des 4 BG |
| | `gfx.bgligne BG RANGÉE` | 32 cases `tile:palette` de la carte du BG en VRAM |
| | `gfx.tile BLOC TILE` | indices de couleur d'un tile 4bpp |
| | `gfx.fenetres` | fenêtres ouvertes |
| Texte | `texte.imprimantes` | textes en train de s'écrire : police, couleurs, position |
| Son | `son.etat` | musique et effets en cours |
| Système | `sys.etat` | RNG, heure du jeu, teinte jour/nuit |
| | `sys.anomalies` | anomalies vues par les détecteurs depuis le lancement |

## Anomalies (`src/debug_checks.c`)

Des détecteurs regardent le jeu pendant qu'il tourne (builds DEBUG) et signalent une fois par cause ce qui est
anormal : liste `sys.anomalies` (menu DEBUG > Outils > Système > Anomalies vues), console (`ANOMALIE …` sur stderr),
banc headless (journal `ANOMALIE détecteur : texte` ; le scénario échoue si `test/headless/anomalies_known.txt` ne
la connaît pas).

| Détecteur | Ce qu'il voit | Où |
|---|---|---|
| texte coupé | une lettre d'une police de l'option POLICE dont des pixels tombent hors de sa fenêtre | `text.c`, `IsGlyphInkOutsideWindow` |
| flèche hors fenêtre | la flèche d'attente (après `\l`, `\p`) dépasse du bord droit de sa fenêtre | `text.c`, `TextPrinterDrawDownArrow` |
| cadre de boîte | un cadre de boîte de dialogue dessiné avec une tile que le style chargé (Émeraude ou RF) ne place jamais | `DebugChecks_OnMessageBoxGfx` (chargement) + carte du BG en VRAM toutes les 8 images |
| Pokémon figé | un sprite de Pokémon (animations de face) qui garde son image 1 pendant 2 s | à chaque image |
| teinte jour/nuit coupée | la teinte cesse (option active) alors que les couleurs du terrain sont toujours à l'écran | `day_night.c` |
| special non porté | un special encore en stub est appelé | `kanto_specials_stubs.c` |

Chaque détecteur a été validé sur son bug avant la correction (2026-11-02 : boîte de l'intro avec DIALOGUE =
KANTO, sprite figé dans la fiche de RF, flèche hors de la boîte de RF, teinte coupée pendant la transition vers un
combat).

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

Ajouter une commande : une fonction `static void Cmd_X(const s32 *args, u32 argCount, struct DebugToolsOutput *out)`
qui écrit avec `DebugTools_Print`, son nom dans le jeu (`static const u8 sName_X[] = _("…")`) et une ligne dans
`gDebugTools` (id, catégorie, nom, aide, nombre d'arguments obligatoires).
