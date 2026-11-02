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
| SAC (13) | le sac : Émeraude (5 poches, CT & CS, BAIES) ou RF (3 poches ; BOITE CT et SAC A BAIES en OBJ. RARES) | — |
| POKéMON (14) | les sprites des Pokémon (Émeraude animés, RF) | — |
| JOUR/NUIT (16) | la teinte du terrain, qui tient pendant la transition vers un combat (`CB2_OverworldBasic`) jusqu'au fondu ; pas de teinte dans l'écran de combat | — |

## Écrans et ce qu'ils doivent montrer

| Écran | Attendu | Piège connu |
|---|---|---|
| Carte de dresseur | le style suit la **région** (`Fusion_IsInKanto` dans `ShowPlayerTrainerCard`), pas MENUS ; le sprite suit PERSO ; les deux points de la DUREE JEU clignotent (une capture peut les montrer éteints) | — |
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

## Règle pour les numéros de dresseurs

Les dresseurs de Kanto suivent ceux d'Émeraude (`KANTO_TRAINERS_START` = 864 à 1606). Deux numéros sont aussi ceux
d'adversaires spéciaux d'Émeraude : 1022 `TRAINER_FRONTIER_BRAIN` (PIQUE-NIQUE SOFIA, Grotte B1F) et 1024
`TRAINER_SECRET_BASE` (PIQUE-NIQUE TINA, Arène de Céladopole). Hors des fichiers de la Zone de Combat, tout test sur
ces valeurs passe par `IS_SECRET_BASE_OPPONENT` / `IS_FRONTIER_BRAIN_OPPONENT` (`include/battle_setup.h`), qui
vérifient aussi le type de combat. Renuméroter Kanto déplacerait les drapeaux de victoire des sauvegardes. Scénario :
`kanto_trainer_ids`.

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
  données (division par zéro en `CB2_HandleStartBattle`, 0xc0000094) : pas un chemin du jeu, mais à tester par un vrai
  défi (phase 5).
- **Dresseur E-Reader** de l'Île 7 (`SevenIsland_House_Room2`, où l'on n'entre par `SevenIsland_House_Room1` que si
  un dresseur E-Reader est enregistré) : `BufferEReaderTrainerGreeting` et `StartSpecialBattle` sont encore des stubs
  (link / E-Reader : à porter, désactivés).
