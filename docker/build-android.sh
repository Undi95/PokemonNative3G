#!/bin/bash
# Usage (dans le conteneur pn3g-android) : build-android.sh
# /repo = dépôt monté en lecture, /work = volume interne (build rapide), /out = sortie
# Produit /out/android/PokemonNative3G.apk (arm64-v8a) ; avec FLAVOR=debugtools et MAKEFLAGS_EXTRA=KANTO_DEBUG=1 :
# /out/android/PokemonNative3G-debug.apk (menu DEBUG, outils, rapport de bug ; volume de travail à part)
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
FLAVOR=${FLAVOR:-standard}
rm -rf android/app/debugAssets
if [ "$FLAVOR" = debugtools ]; then
  # Les symboles (fonctions et données) : les outils de debug nomment les adresses (src/platform/devtools.c)
  mkdir -p android/app/debugAssets
  "$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin/llvm-nm" --defined-only pokeemeraude64.so \
    | grep -i ' [tdrbs] ' > android/app/debugAssets/pokeemeraude64.syms
fi
cd android
TASK=assemble${FLAVOR^}Release
gradle --no-daemon -q "$TASK"
mkdir -p /out/android
if [ "$FLAVOR" = debugtools ]; then NAME=PokemonNative3G-debug.apk; else NAME=PokemonNative3G.apk; fi
cp -v app/build/outputs/apk/$FLAVOR/release/app-$FLAVOR-release.apk /out/android/$NAME
