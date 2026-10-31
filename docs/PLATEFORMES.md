# Windows, Linux, Android

Tout se construit dans Docker, depuis le **commit courant** (committer d'abord : le build
part de HEAD). Sous Git Bash, à la racine du dépôt :

```bash
P="$(pwd -W)"
```

Ajouter `-e "MAKEFLAGS_EXTRA=KANTO_DEBUG=1"` pour le menu DEBUG.

## Windows (`out/winwsl/`)

```bash
MSYS_NO_PATHCONV=1 docker run --rm -v "$P:/repo:ro" -v pn3g-work:/work -v "$P/out:/out" pn3g-build bash /repo/docker/build.sh winwsl
```

À distribuer : `pokeemeraude64.exe` + `SDL2.dll`.

## Linux (`out/linux/`)

```bash
MSYS_NO_PATHCONV=1 docker run --rm -v "$P:/repo:ro" -v pn3g-work:/work -v "$P/out:/out" pn3g-build bash /repo/docker/build.sh linux
```

Binaire `pokeemeraude64` (x86_64), compilé sur Ubuntu 24.04. Il faut SDL2 sur la machine
(`sudo apt install libsdl2-2.0-0`). Vérifié : le scénario headless `new_game` passe en entier.
À faire plus tard pour une vraie sortie : AppImage (SDL2 inclus, glibc plus ancienne).

## Android (`out/android/PokemonNative3G.apk`)

Image à construire une fois (SDK, NDK r27, Gradle, SDL2 compilé pour Android, ~5 Go) :

```bash
docker build -t pn3g-android -f docker/Dockerfile.android docker
```

Puis :

```bash
MSYS_NO_PATHCONV=1 docker run --rm -v "$P:/repo:ro" -v pn3g-work:/work -v "$P/out:/out" -v pn3g-gradle:/root/.gradle -v pn3g-android-home:/root/.android pn3g-android bash /repo/docker/build-android.sh
```

- arm64-v8a seulement (tous les téléphones récents), Android 7.0+.
- `make android` : le jeu en `libmain.so` (clang du NDK, données assemblées par `as` aarch64),
  chargé par l'activité Java de SDL (`android/`, `GameActivity`).
- APK signé avec la clé de debug gardée dans le volume `pn3g-android-home` : garder ce volume,
  sinon une mise à jour demandera de désinstaller (et perdre la sauvegarde).
- Sauvegarde et réglages dans le stockage interne de l'appli (`SDL_GetPrefPath`).
- Icône : `icon.png` (comme l'exe Windows), dans `android/app/src/main/res/mipmap-xxxhdpi/`.

## Cadence et performances (`src/platform/sdl2.c`, boucle principale)

- 60 frames de jeu par seconde ; avec la vsync d'un écran à 60 ou 120 Hz, chaque image avance du même nombre de
  frames (vsync snapping : le jitter de l'affichage ne crée plus d'à-coups). Autres écrans (144 Hz…) : temps réel
  simple.
- Sans vsync (fenêtre réduite, pilote qui l'ignore) ou en pause, la boucle dort au lieu de tourner à vide.
- Un blocage de plus de 100 ms (fenêtre déplacée, appli en arrière-plan) est perdu, pas rattrapé en accéléré.
- Mesure : variable d'environnement `PN3G_FPS=1` ; toutes les 5 s, sur la sortie d'erreur : frames/s, part du temps
  passée à calculer et dessiner, à-coups (images où passent plusieurs frames d'un coup, hors avance rapide).
  Mesuré le 2026-10-31 (RTX 5090, écran 60 Hz) : 60 frames/s, calcul et dessin 6-7 % du temps, 0 à 1 à-coup
  par 5 s ; 10-11 % d'un cœur avec ou sans vsync (avant : 95 % sans vsync, et 0 ou ~30 à-coups par 5 s selon
  le lancement).

```powershell
$env:PN3G_FPS = '1'; .\pokeemeraude64.exe 2> fps.txt
```

## Touches tactiles (`src/platform/touch.c`)

Toujours affichées sur Android ; sur PC, dès qu'on touche un écran tactile. Croix à gauche,
A/B à droite, L/R en haut, SELECT / RESET / START en bas au centre. RESET = reset du jeu,
à maintenir 1 seconde.
