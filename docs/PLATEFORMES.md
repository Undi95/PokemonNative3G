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

## Touches tactiles (`src/platform/touch.c`)

Toujours affichées sur Android ; sur PC, dès qu'on touche un écran tactile. Croix à gauche,
A/B à droite, L/R en haut, SELECT / RESET / START en bas au centre. RESET = reset du jeu,
à maintenir 1 seconde.
