# Version navigateur : étude et plan (v1.1, 2026-11-04)

Demande : une version pour navigateur, hébergeable, qui marche en local ou simplement déposée sur un site web, sans
serveur (pas de multijoueur pour l'instant).

**Réponse : oui, c'est possible.** Le résultat serait un dossier statique (`index.html` + le jeu compilé en
WebAssembly). On l'ouvre d'un double-clic ou on le dépose tel quel sur n'importe quel hébergeur statique (GitHub Pages,
itch.io, Netlify, un FTP…). Rien n'est encore fait : il faut d'abord la chaîne de compilation Emscripten, à télécharger
(voir « Ce qu'il faut »).

## Ce qui est déjà prêt dans la couche PC

- **Boucle de jeu image par image** (`main` de `src/platform/sdl2.c` : `RunMainLoop`, `VBlankIntrWait` vide). C'est la
  forme qu'un navigateur impose : il suffit d'appeler un tour de cette boucle à chaque image du navigateur
  (`emscripten_set_main_loop`), au lieu du `while (isRunning)` et du `SDL_Delay`.
- **SDL2 existe pour le web** (port SDL2 d'Emscripten) : image, son (Web Audio), clavier, manettes (Gamepad API),
  tactile (`src/platform/touch.c`, déjà fait pour Android).
- **Aucun thread** : pas d'en-têtes spéciaux à demander à l'hébergeur.

## Le gros morceau : les données assemblées

Les scripts, les cartes et les autres tables de `data/` (`.s`, des milliers de fichiers) sont assemblés par GNU as.
Ils contiennent des pointeurs vers d'autres données et vers des fonctions C (`special`, `callnative`…). Chaque
plateforme a sa solution :

| Plateforme | Données |
|---|---|
| Windows, Linux | GNU as pour x86-64 (ELF / COFF) |
| Android | GNU as pour aarch64 |
| macOS | GNU as (ELF), puis `tools/elf2macho` (668 lignes de C) les convertit en objets Mach-O |
| Navigateur | **à faire** : pas d'assembleur GNU pour WebAssembly |

Le plan suit le précédent de macOS :

1. Assembler les données **en 32 bits** (`as --32`). Les macros savent déjà le faire (`asm/macros/bit_width.inc`,
   `VER_64BIT`). Ce sont des pointeurs de 4 octets, ceux de WebAssembly (wasm32).
2. Un convertisseur `tools/elf2wasm` transforme chaque objet ELF en objet WebAssembly :
   - sections de données → segments de données ;
   - symboles → symboles de données ;
   - pointeurs vers des données (`R_386_32`) → `R_WASM_MEMORY_ADDR_I32` ;
   - pointeurs vers des fonctions C → `R_WASM_TABLE_INDEX_I32`. La signature de chaque fonction est relevée dans les
     objets C compilés, sinon l'éditeur de liens remplace la fonction par un piège.
3. Vérifier le **code C en 32 bits**. La fusion n'a été jouée qu'en 64 bits (`pokeemeraude64`) ; il y a 25 endroits
   `VER_64BIT` dans `src/` et `include/`. Le banc de test, lui, reste sur l'exe natif.

Autre voie possible : wasm64 (pointeurs de 8 octets, données en x86-64). Elle éviterait l'étape 3, mais Safari et
les navigateurs plus anciens ne la lisent pas. À écarter pour un jeu à partager.

## Le reste (connu, sans difficulté)

- **Sauvegarde** dans le navigateur (IndexedDB, via le système de fichiers IDBFS d'Emscripten), synchronisée après
  chaque écriture. Les options (`settings.c`) aussi.
  - Boutons **Exporter / Importer** : le `.sav` est le même que sur PC et Android, une partie passe d'un appareil à
    l'autre.
  - Les données d'un navigateur peuvent être effacées : export conseillé.
- **Ouvrir en local** : un navigateur refuse de charger un `.wasm` depuis `file://`. Le jeu est donc compilé **en un
  seul fichier** (`-sSINGLE_FILE` : le wasm dans le `.js`). La même version sert en ligne.
- **Son** : un navigateur exige un clic avant de jouer du son : écran « Cliquer pour jouer ».
- **Plein écran**, mise à l'échelle nette (pixels entiers), contrôles tactiles sur téléphone : comme Android.
- Pas de console des outils de debug (`devtools.c`, TCP) dans cette version.

## Ce qu'il faut

- **Emscripten**, dans une image Docker à part (`docker/Dockerfile.web`, depuis l'image officielle
  `emscripten/emsdk`, environ 1,5 Go à télécharger). C'est un téléchargement : **à faire avec ton accord**.
- Une cible `make web` et `docker/build.sh web`, avec une sortie `out/web/` (`index.html` + `pokeemeraude.js`).
- Test dans le navigateur intégré : intro, nouvelle partie, sauvegarde, rechargement, son, manette. Captures.

## Estimation

| Étape | Taille |
|---|---|
| `elf2wasm` et données en 32 bits | le plus long, une à deux sessions |
| Code C en 32 bits | dépend de ce qui casse |
| Boucle, sauvegarde, page HTML, export/import | une session |
| Tests et release « navigateur » dans `build-all.sh` | une session |
