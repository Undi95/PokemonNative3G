# Version navigateur (depuis la 1.2)

Le jeu tourne dans un navigateur, sans serveur : deux fichiers, `index.html` (la page) et `pokeemeraude.js` (le jeu,
WebAssembly compris). On les ouvre d'un double-clic sur `index.html`, ou on les dépose tels quels sur n'importe quel
hébergeur statique (GitHub Pages, itch.io, Netlify, un FTP…). Pas de multijoueur pour l'instant.

## Jouer

- **Lancer** : un clic sur « Cliquer pour jouer » (ou Entrée). Un navigateur ne joue du son qu'après un geste du
  joueur, d'où ce bouton.
- **Touches** : celles du PC (`src/platform/settings.c`) : flèches, A = Z, B = X, Start = Entrée, Select = Retour
  arrière, L = A, R = S, accélérer = Espace. Comme sur PC, une touche est celle où la lettre est écrite, quelle que
  soit la disposition (AZERTY comme QWERTY) : le SDL2 d'Emscripten garde une table de touches QWERTY, le jeu suit
  donc les touches tenues par le keycode de leurs événements (tiré de `keyCode`, la lettre de la touche). Une touche
  accentuée (« key_a = ù » sur PC) n'est pas reconnue dans le navigateur. F5 recharge la page (celle du navigateur, pas la
  réinitialisation du jeu : A+B+Start+Select la fait). Manettes : celles que le navigateur reconnaît (API Gamepad). Écran tactile : les touches d'Android apparaissent au premier toucher (`touch.c`).
- **Plein écran** : le bouton de la barre du bas.
- **Sauvegarde** : gardée dans le navigateur (IndexedDB), recopiée après chaque sauvegarde du jeu ; la barre du bas
  affiche l'heure de la dernière. Le bouton **Exporter** télécharge `pokeemerald.sav`, le même fichier que sur PC et
  Android ; **Importer** remplace la partie du navigateur par un `.sav` et recharge la page. Effacer les données du
  site efface la partie : exporter de temps en temps.

## Construire

Image Docker à part (Emscripten, depuis l'image officielle `emscripten/emsdk`), à construire une fois :

```bash
docker build -t pn3g-web -f docker/Dockerfile.web docker
```

Puis, comme les autres plateformes (le build part du dernier commit) :

```bash
MSYS_NO_PATHCONV=1 docker run --rm -v "$(pwd -W):/repo:ro" -v "$(pwd -W)/out:/out" -v pn3g-work-web:/work pn3g-web bash /repo/docker/build.sh web
```

Sortie : `out/web/index.html` et `out/web/pokeemeraude.js` (environ 30 Mo). `out/web-debug/pokeemeraude.map` donne
l'adresse de chaque variable, pour lire l'état du jeu dans la console du navigateur (`Module.HEAPU8`). La release
(`build-all.sh`) les met dans `Navigateur/`.

## Comment c'est fait

| Morceau | Fichier |
|---|---|
| Cible `make web` : emcc, 32 bits (`IS64BIT=0`), port SDL2 d'Emscripten | `Makefile`, `docker/Dockerfile.web` |
| Données assemblées (scripts, cartes, musiques) converties en objets WebAssembly | `tools/elf2wasm.py` |
| Boucle principale : une image par rafraîchissement du navigateur | `src/platform/sdl2.c` (`RunFrame`) |
| Sauvegarde et options dans IndexedDB | `src/platform/web/pre.js`, `SyncStorage` dans `sdl2.c` |
| Variables du jeu effacées par la réinitialisation logicielle | `src/platform/web/ram_*.inc.c`, `system.c` |
| La page : lancement, plein écran, export et import | `src/platform/web/index.html` |

- **Les données** : les fichiers de `data/` sont écrits pour GNU as, avec des macros que l'assembleur de clang ne sait
  pas lire. Comme pour macOS (`tools/elf2macho`), GNU as les assemble, ici en 32 bits (`as --32` : des pointeurs de
  4 octets, ceux de wasm32), puis `elf2wasm.py` traduit chaque objet ELF en assembleur WebAssembly de LLVM, qu'emcc
  assemble :
  - une section devient un segment de données d'un seul tenant, car un script peut continuer dans le label suivant ;
  - un pointeur vers une donnée devient une relocation `R_WASM_MEMORY_ADDR_I32` ;
  - un pointeur vers une fonction C (special, callnative…) devient une entrée de la table des fonctions. Sa
    signature est relevée dans les objets C compilés : avec une autre signature, wasm-ld la remplacerait par un
    piège. La conversion se fait donc au moment du lien.
- **Les appels de fonctions par pointeur** : le jeu appelle souvent une fonction avec une autre signature que la
  sienne (une fonction `void` de la table des specials appelée comme `u16 (*)(void)`). C'est sans effet sur PC, mais
  un piège en WebAssembly : d'où `-sEMULATE_FUNCTION_POINTER_CASTS`. Le jeu ne prend qu'environ 1 ms par image.
- **Un seul fichier** : `-sSINGLE_FILE` met le WebAssembly dans le `.js`. Ouverte depuis le disque (`file://`), une
  page n'a pas le droit de charger un `.wasm` à part.
- **Réinitialisation logicielle** : sur PC, les variables du jeu ont une section à elles (`gba_ram`), que
  `RegisterRamReset` efface. Clang n'applique pas `#pragma clang section` en WebAssembly : les objets du jeu sont liés
  entre deux marqueurs (`gWebGameRamStart`, `gWebGameRamEnd`), avant ceux de `src/platform/`, et wasm-ld range les
  variables dans l'ordre des objets.
- **32 bits** : la sauvegarde garde la disposition de la GBA (`save.c`). Une partie passe donc d'une plateforme à
  l'autre, y compris les blocs annexes de la fusion. Vérifié : une sauvegarde faite sur PC se charge dans le
  navigateur (Kanto, sac de Rouge Feu).

## Vérifié (2026-11-05, Chrome du panneau navigateur de l'appli)

Intro, écran titre, nouvelle partie jusqu'au camion, sauvegarde, rechargement de la page puis « Continuer »,
import d'une sauvegarde faite sur PC, sac de Kanto, réinitialisation logicielle puis reprise, son (contexte audio
actif à 48 kHz), vitesse (environ 0,8 ms de calcul par image).

## Limites

- Pas de console des outils de debug (`devtools.c`, TCP) : la version navigateur est construite sans le menu DEBUG.
- Le banc de test (`test/headless`) reste sur l'exe natif.
