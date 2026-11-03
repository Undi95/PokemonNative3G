#!/bin/bash
# PokemonNative3G : vérifie une release avant de la publier (après build-all.sh), en deux passes :
#  1. la suite des tests headless sur l'exe Windows de test (out/winwsl, build DEBUG), puis le rapport de bug
#     rejouable (test/headless/report_check.py) ;
#  2. la même suite sur une build Linux avec AddressSanitizer + UBSan (Docker, volume pn3g-work-asan).
# Rapports : build/headless/suite/report.txt et out/asan-suite/suite/report.txt. Code de sortie 0 = tout est OK.
# Usage : bash test-release.sh [--no-asan] [SCÉNARIO ...]
cd "$(dirname "$0")"
# Le code de retour d'une commande filtrée (suite.py | grep) est celui de la suite, pas du grep : sans ça, une suite
# en échec passait pour « RELEASE OK »
set -o pipefail
ASAN=1; [ "$1" = "--no-asan" ] && { ASAN=0; shift; }
P="$(pwd -W 2>/dev/null || pwd)"; FAIL=0
echo "== noms des drapeaux, variables et dresseurs des outils de debug (src/data/debug_names.h)"
python tools/debug_names.py --check || FAIL=1
python tools/debug_states.py --check || FAIL=1
echo "== 1/2 : suite sur out/winwsl/pokeemeraude64.exe"
python test/headless/suite.py out/winwsl/pokeemeraude64.exe "$@" | grep -v "^  " || FAIL=1
echo "== rapport de bug rejouable (console, rapport, rejeu identique)"
python test/headless/report_check.py out/winwsl/pokeemeraude64.exe > out/report_check.log 2>&1 || FAIL=1
tail -1 out/report_check.log
if [ $ASAN = 1 ]; then
  echo "== 2/2 : suite sur la build Linux AddressSanitizer + UBSan"
  MSYS_NO_PATHCONV=1 docker run --rm -v "$P:/repo:ro" -v pn3g-work-asan:/work -v "$P/out:/out" pn3g-build \
    bash /repo/docker/test-sanitize.sh "$@" | grep -v "^  " || FAIL=1
fi
[ $FAIL = 0 ] && echo "RELEASE OK" || echo "RELEASE EN ÉCHEC (voir les rapports)"
exit $FAIL
