#!/bin/bash
# PokemonNative3G : release complète SANS menu DEBUG (Windows, Linux, APK Android) dans out/release/, avec
# CHANGELOG.md, puis out/PokemonNative3G-VERSION.zip (journal : out/build-all.log).
# Volumes à part (pn3g-rel-*) : la build de test avec DEBUG (pn3g-work-release, out/winwsl, KANTO_DEBUG=1) reste
# intacte pour test/headless/suite.py. Usage : bash build-all.sh [VERSION]   (défaut : 1.1)
cd "$(dirname "$0")"
VERSION=${1:-1.1}
P="$(pwd -W 2>/dev/null || pwd)"; LOG=out/build-all.log; REL=out/release; mkdir -p out; : > $LOG
run() { MSYS_NO_PATHCONV=1 docker run --rm -v "$P:/repo:ro" -v "$P/out:/out" "$@" >> $LOG 2>&1 || { echo "ÉCHEC $* (voir $LOG)"; exit 1; }; }
run -e OUT_NAME=rel-windows -v pn3g-rel-windows:/work pn3g-build bash /repo/docker/build.sh winwsl
run -e OUT_NAME=rel-linux -v pn3g-rel-linux:/work pn3g-build bash /repo/docker/build.sh linux
run -v pn3g-android-work:/work pn3g-android bash /repo/docker/build-android.sh
rm -rf $REL; mkdir -p $REL/Windows $REL/Linux $REL/Android
cp out/rel-windows/pokeemeraude64.exe $REL/Windows/PokemonNative3G.exe
cp out/rel-windows/SDL2.dll $REL/Windows/
cp out/rel-linux/pokeemeraude64 $REL/Linux/PokemonNative3G
cp out/android/PokemonNative3G.apk $REL/Android/
cp CHANGELOG.md $REL/
cp docs/OU-TROUVER-LES-POKEMON.md "$REL/Où trouver les Pokémon.md"
file $REL/Windows/PokemonNative3G.exe | grep -q PE32 || { echo "ÉCHEC : l'exe Windows n'est pas un PE"; exit 1; }
rm -f out/PokemonNative3G-$VERSION.zip
python -c "import shutil,sys; shutil.make_archive(sys.argv[1], 'zip', sys.argv[2])" out/PokemonNative3G-$VERSION $REL
echo "OK : $REL/ et out/PokemonNative3G-$VERSION.zip"
