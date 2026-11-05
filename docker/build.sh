#!/bin/bash
# Usage (dans le conteneur) : build.sh linux|winwsl
# /repo = dépôt monté en lecture, /work = volume interne (build rapide), /out = sortie
set -eo pipefail
TARGET=${1:-linux}
if [ ! -d /work/src/.git ]; then git clone -q /repo /work/src; fi
cd /work/src
git fetch -q /repo HEAD && git reset -q --hard FETCH_HEAD
if [ "$TARGET" = winwsl ] && [ ! -e SDL2 ]; then ln -s /opt/SDL2 SDL2; fi
# Les options (ex. KANTO_DEBUG=1) ne déclenchent pas de recompilation : si elles changent,
# on force la recompilation des fichiers qui en dépendent.
STAMP="build/.flags_$TARGET"; mkdir -p build
if [ "$(cat "$STAMP" 2>/dev/null)" != "$MAKEFLAGS_EXTRA" ]; then touch src/new_game.c; echo "$MAKEFLAGS_EXTRA" > "$STAMP"; fi
make "$TARGET" -j"${JOBS:-$(nproc)}" $MAKEFLAGS_EXTRA 2>&1 | tail -n "${TAILN:-40}"
OUT=/out/${OUT_NAME:-$TARGET}; mkdir -p $OUT
# Version navigateur (image pn3g-web) : la page et le jeu, deux fichiers à déposer tels quels (docs/NAVIGATEUR.md)
if [ "$TARGET" = web ]; then
    cp -v pokeemeraude32.js $OUT/pokeemeraude.js
    sed "s/VERSION_DU_JEU/$(git rev-parse --short HEAD)/" src/platform/web/index.html > $OUT/index.html
    # Adresses des variables (HEAPU8 dans la console du navigateur), à côté et pas dans la version à déposer
    mkdir -p /out/web-debug && cp pokeemeraude.map /out/web-debug/
    exit 0
fi
if [ "$TARGET" = winwsl ]; then cp -v pokeemeraude64.exe $OUT/; else cp -v pokeemeraude64 $OUT/; fi
# Les symboles (fonctions et données), pour que les tests et les outils de debug nomment les adresses
# (test/headless/names.py)
if [ "$TARGET" = winwsl ]; then x86_64-w64-mingw32-nm --defined-only pokeemeraude64.exe | grep -i ' [tdrbs] ' > $OUT/pokeemeraude64.syms; else nm --defined-only pokeemeraude64 | grep -i ' [tdrbs] ' > $OUT/pokeemeraude64.syms; fi
if [ "$TARGET" = winwsl ]; then cp -v /opt/SDL2/x86_64-w64-mingw32/bin/SDL2.dll $OUT/; fi
