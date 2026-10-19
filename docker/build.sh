#!/bin/bash
# Usage (dans le conteneur) : build.sh linux|winwsl
# /repo = dépôt monté en lecture, /work = volume interne (build rapide), /out = sortie
set -e
TARGET=${1:-linux}
if [ ! -d /work/src/.git ]; then git clone -q /repo /work/src; fi
cd /work/src
git fetch -q /repo HEAD && git reset -q --hard FETCH_HEAD
if [ "$TARGET" = winwsl ] && [ ! -e SDL2 ]; then ln -s /opt/SDL2 SDL2; fi
# Les options (ex. KANTO_DEBUG=1) ne déclenchent pas de recompilation : si elles changent,
# on force la recompilation des fichiers qui en dépendent.
STAMP="build/.flags_$TARGET"; mkdir -p build
if [ "$(cat "$STAMP" 2>/dev/null)" != "$MAKEFLAGS_EXTRA" ]; then touch src/new_game.c; echo "$MAKEFLAGS_EXTRA" > "$STAMP"; fi
make "$TARGET" -j"$(nproc)" $MAKEFLAGS_EXTRA 2>&1 | tail -n 40
mkdir -p /out/$TARGET
cp -v pokeemeraude64* /out/$TARGET/
if [ "$TARGET" = winwsl ]; then cp -v /opt/SDL2/x86_64-w64-mingw32/bin/SDL2.dll /out/$TARGET/; fi
