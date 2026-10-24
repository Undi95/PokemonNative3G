#!/bin/bash
# Usage (dans le conteneur pn3g-android) : build-android.sh
# /repo = dépôt monté en lecture, /work = volume interne (build rapide), /out = sortie
# Produit /out/android/PokemonNative3G.apk (arm64-v8a)
set -eo pipefail
# clé de debug gardée dans le volume : même signature d'un build à l'autre (mise à jour sans perdre la sauvegarde)
mkdir -p /work/.android; rm -rf ~/.android; ln -sfn /work/.android ~/.android
if [ ! -d /work/src/.git ]; then git clone -q /repo /work/src; fi
cd /work/src
git fetch -q /repo HEAD && git reset -q --hard FETCH_HEAD
STAMP="build/.flags_android"; mkdir -p build
if [ "$(cat "$STAMP" 2>/dev/null)" != "$MAKEFLAGS_EXTRA" ]; then touch src/new_game.c; echo "$MAKEFLAGS_EXTRA" > "$STAMP"; fi
make android -j"$(nproc)" $MAKEFLAGS_EXTRA 2>&1 | tail -n "${TAILN:-40}"
mkdir -p android/app/jniLibs/arm64-v8a
cp pokeemeraude64.so android/app/jniLibs/arm64-v8a/libmain.so
cp /opt/sdl-android/lib/libSDL2.so android/app/jniLibs/arm64-v8a/
cd android
gradle --no-daemon -q assembleRelease
mkdir -p /out/android
cp -v app/build/outputs/apk/release/app-release.apk /out/android/PokemonNative3G.apk
