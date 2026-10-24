#!/bin/bash
# Menu DEBUG actif partout (KANTO_DEBUG=1, sans départ à Kanto). PokemonNative3G : APK Android + exécutable Windows + exécutable Linux dans out/release/ (journal : out/build-all.log)
cd "$(dirname "$0")"
P="$(pwd -W 2>/dev/null || pwd)"; LOG=out/build-all.log; mkdir -p out/release; : > $LOG
run() { MSYS_NO_PATHCONV=1 docker run --rm -e MAKEFLAGS_EXTRA=KANTO_DEBUG=1 -v "$P:/repo:ro" -v "$P/out:/out" "$@" >> $LOG 2>&1 || { echo "ÉCHEC $1 $2 (voir $LOG)"; exit 1; }; }
run -v pn3g-work-release:/work pn3g-build bash /repo/docker/build.sh winwsl
run -v pn3g-work-linux:/work pn3g-build bash /repo/docker/build.sh linux
run -v pn3g-android-work:/work pn3g-android bash /repo/docker/build-android.sh
cp out/android/PokemonNative3G.apk out/winwsl/pokeemeraude64.exe out/winwsl/SDL2.dll out/release/
cp out/linux/pokeemeraude64 out/release/PokemonNative3G-linux
file out/release/pokeemeraude64.exe | grep -q PE32 || { echo "ÉCHEC : l'exe Windows n'est pas un PE"; exit 1; }
echo "OK : out/release/"
