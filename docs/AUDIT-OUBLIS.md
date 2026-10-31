# Audit des oublis (2026-10-31)

Le jeu est jouable du début à la fin (les deux Ligues, post-game de Célio). Cet audit cherche ce qui aurait pu
être oublié. Ordre de travail convenu : 1) finitions ci-dessous, 2) APK Android, 3) playthrough de l'utilisateur
sur téléphone (`docs/A-TESTER.md` sert de liste de points à surveiller).

## Pokémon (Pokédex national 386)

**386/386 obtenables en solo** (`python tools/obtenables.py --trade`, avec le CÂBLE LINK pour les évolutions par
échange ; 374 sans). Guide pour les joueurs, lieu par lieu : `docs/OU-TROUVER-LES-POKEMON.md`, généré par
`tools/doc_pokemon_lieux.py` (rencontres avec méthode, niveaux et %, cadeaux expliqués, échanges avec leur lieu,
légendaires avec leurs conditions, reproduction, évolutions). Pas besoin de Johto pour le Pokédex.

Deux vrais oublis trouvés et corrigés (2026-10-31) :
- **Ramoloss / Flagadoss / Roigada** : exclusivité de Vert Feuille, absente d'Émeraude, oubliée par
  `tools/exclusifs.py` ; ajoutés aux endroits de Vert Feuille (Zone Safari, Caverne Azurée, Îles Écume, Bois Baies,
  Cap Falaise…), en alternance avec Psykokwak / Akwakwak qui restent. L'outil de comptage les croyait obtenables à
  cause d'un motif trop large (`setvar VAR_0x8004`), retiré.
- **Second Lati de l'Île du Sud** : le PASSE EON n'était donné que par le Club Câble (link). Ajouté au CADEAU
  MYSTÈRE de la fusion (4e carte, port de Nénucrique) ; scénario `fusion_mystery_gift` à quatre cadeaux.

L'outil de comptage lit aussi les dons par variable (Dojo, Casino, starters de RF) et connaît les chiens errants et
les starters de Hoenn.

## Objets

- Objets clés et CS donnés dans les deux régions : aucun (`tools/item_doubles.py`, `docs/OBJETS-EN-DOUBLE.md`).
- Objets jamais cités hors de leur définition : 66, tous des emplacements vides (`ITEM_034`… `ITEM_15C`) sauf
  ORBE ROUGE / ORBE BLEU, inutilisés aussi dans Émeraude (objets de Rubis/Saphir). Rien d'oublié.

## Scripts et specials

- Specials de RF encore en stub : 24 (`src/kanto_specials_stubs.c`), tous hors solo : link, Tour de Combat de RF
  (salle e-Reader de l'Île 7), triangle de Deoxys de RF (l'Île Naissance est celle d'Émeraude).
- Scripts morts et doublons RF/Émeraude : nettoyés (2026-10-31, `docs/CARTOGRAPHIE.md`) ; restent les doublons
  du link (hors solo).
- Aucune erreur ni stub signalé par le jeu sur les 83 scénarios headless (sortie d'erreur vide), ASan propre.

## Scénario

- Liaison Hoenn → Kanto : PAPA (PASSE BATEAU), destination KANTO du ferry, texte du marin (2026-10-31).
- Liaison Kanto → Hoenn : Ligue de Kanto + RUBIS/SAPHIR rendus à CÉLIO (quête de RF), puis ferry et vol.
- Après les deux Ligues : Celebi, Jirachi, cadeaux mystère, œufs de starters (docs/FUSION-OPTIONS.md).
- Décisions de l'utilisateur, pas des oublis : rival = BLUE sans choix du nom, pas de conseils de Chen, pas
  d'aide L/R ni de journal de RF, pas de décorations dans la maison de Bourg Palette.

## Pokédex

- Option POKéDEX HOENN / KANTO (écran de RF complet, zones de Kanto) ; Pokédex national.
- À vérifier en jouant : zones (« habitat ») des Pokémon ajoutés par la fusion (exclusivités de version,
  `tools/exclusifs.py`) dans les deux Pokédex.

## Finitions restantes (étape 1)

1. Vérifications visuelles listées dans A-TESTER que le headless ne peut pas montrer (clones de RF vus de loin,
   braille, menus défilants avec tous les billets…) : au playthrough.
2. Carte du PASSE EON au CADEAU MYSTÈRE : vue en headless sans capture, à regarder au playthrough.
3. Ancien point ouvert : la flèche d'attente du braille n'existe qu'avec DIALOGUE = KANTO (comme chaque jeu).

## Hors périmètre pour l'instant

- Multijoueur (Club Câble, Salle Union, échanges, connexion par mot de passe) : tout à la fin.
- Version Linux en AppImage.
