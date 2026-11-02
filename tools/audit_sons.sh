#!/bin/bash
# Compile les chansons (mid2agb) et convertit les samples (wav2agb) de la fusion et de Rouge Feu, avec les outils et
# les options de la fusion (midi.cfg de chaque jeu), pour tools/audit_sons.py. Dans le conteneur de build :
#   docker run --rm -v "$(pwd -W):/repo:ro" -v "$(pwd -W)/out:/out" \
#       -v "$(pwd -W)/../decomps/pokerougefeu:/rf:ro" pn3g-build bash /repo/tools/audit_sons.sh
# Résultat : /out/audit-sons/{fusion,rf}/*.s et /out/audit-sons/samples/{fusion,rf}/*.bin
set -e
OUT=/out/audit-sons
rm -rf "$OUT" /tmp/mid2agb /tmp/wav2agb
mkdir -p /tmp/mid2agb "$OUT/fusion" "$OUT/rf" "$OUT/samples/fusion" "$OUT/samples/rf"
cp /repo/tools/mid2agb/*.cpp /repo/tools/mid2agb/*.h /tmp/mid2agb/
g++ -O2 -std=c++11 -o /tmp/mid2agb/mid2agb /tmp/mid2agb/*.cpp
cp -r /repo/tools/wav2agb /tmp/wav2agb
make -s -C /tmp/wav2agb >/dev/null

songs() {  # $1 = racine du jeu, $2 = sortie : chaque ligne de midi.cfg, comme audio_rules.mk
    while IFS= read -r line; do
        name="$(echo "${line%%:*}" | tr -d '[:space:]')"
        case "$name" in *.mid) ;; *) name="$name.mid" ;; esac
        [ -f "$1/sound/songs/midi/$name" ] || continue
        /tmp/mid2agb/mid2agb "$1/sound/songs/midi/$name" "$2/${name%.mid}.s" ${line#*:}
    done < "$1/sound/songs/midi/midi.cfg"
}
samples() {  # $1 = racine du jeu, $2 = sortie (wav2agb -b, comme audio_rules.mk)
    for f in "$1"/sound/direct_sound_samples/*.wav; do
        /tmp/wav2agb/wav2agb -b "$f" "$2/$(basename "${f%.wav}").bin"
    done
}
songs /repo "$OUT/fusion"
songs /rf "$OUT/rf"
samples /repo "$OUT/samples/fusion"
samples /rf "$OUT/samples/rf"
echo "chansons : $(ls "$OUT/fusion" | wc -l) fusion, $(ls "$OUT/rf" | wc -l) RF ; samples : $(ls "$OUT/samples/fusion" | wc -l) fusion, $(ls "$OUT/samples/rf" | wc -l) RF"
