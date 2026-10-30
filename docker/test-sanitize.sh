#!/bin/bash
# Usage (dans le conteneur) : test-sanitize.sh [SCÉNARIO ...]
# Compile le jeu pour Linux avec AddressSanitizer et UBSan (/out/asan), puis lance la suite des tests
# headless : une lecture ou écriture hors limites, ou un comportement indéfini, la fait échouer.
# En -O0 -g (GCC 13 plante sur m4a.c avec UBSan en -O3), peu de tâches à la fois (Docker n'a que 2 Go).
set -eo pipefail
JOBS=${JOBS:-6} MAKEFLAGS_EXTRA="KANTO_DEBUG=1 DINFO=1 SANITIZE=address,undefined" OUT_NAME=asan TAILN=${TAILN:-5} bash /repo/docker/build.sh linux
export SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy PYTHONDONTWRITEBYTECODE=1 HEADLESS_OUT=/out/asan-suite
export ASAN_OPTIONS=detect_leaks=0:halt_on_error=0:detect_stack_use_after_return=1 UBSAN_OPTIONS=print_stacktrace=1
cd /repo/test/headless
python3 suite.py /out/asan/pokeemeraude64 --jobs ${SUITE_JOBS:-6} "$@"
