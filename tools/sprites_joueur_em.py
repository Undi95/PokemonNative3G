"""Red et Leaf en style Émeraude (joueur à Hoenn, Options > PERSO) : le reflet de leur palette.

Les feuilles graphics/object_events/pics/people/{red,leaf}/*.png sont dessinées à la main (tools/pixel_grille.py :
« exporter » pour les retoucher en texte, « importer » pour réécrire le PNG), sur les poses de Brice et Flora
d'Émeraude, avec la tête et la tenue de Red/Leaf (graphics/object_events/pics/people/red.png, leaf.png) ; palette
red_leaf.pal (plongée : player_underwater.pal). Ce script écrit red_leaf_reflection.pal, le reflet (sur l'eau) de
red_leaf.pal : le reflet d'une couleur part du reflet de la couleur officielle d'Émeraude la plus proche.

usage : sprites_joueur_em.py
"""
import os

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
PALETTES = os.path.join(ROOT, "graphics", "object_events", "palettes") + os.sep
# Palettes d'Émeraude et leurs reflets
EM_REFLECTIONS = [("brendan", "brendan_reflection"), ("may", "may_reflection"), ("npc_1", "npc_1_reflection"),
                  ("npc_2", "npc_2_reflection"), ("npc_3", "npc_3_reflection"), ("npc_4", "npc_4_reflection"),
                  ("quinty_plump", "quinty_plump_reflection")]


def gba(c):
    return tuple(v >> 3 for v in c)


def pal_value(c):
    """valeur 8 bits d'une couleur, comme les .pal du décomp (5 bits × 255 / 31)"""
    return tuple(round((v >> 3) * 255 / 31) for v in c)


def read_pal(path):
    words = open(path).read().split()
    return [tuple(int(v) for v in words[3 + 3 * i:6 + 3 * i]) for i in range(16)]


def write_pal(path, colors):
    with open(path, "w", newline="\r\n") as f:
        f.write("JASC-PAL\n0100\n16\n")
        for c in colors:
            f.write("%d %d %d\n" % pal_value(c))


def reflection(colors):
    pairs = []
    for base, refl in EM_REFLECTIONS:
        pairs += zip(read_pal(PALETTES + base + ".pal")[1:], read_pal(PALETTES + refl + ".pal")[1:])
    out = [read_pal(PALETTES + "brendan_reflection.pal")[0]]
    for c in colors[1:]:
        b, r = min(pairs, key=lambda p: sum((x - y) ** 2 for x, y in zip(gba(c), gba(p[0]))))
        out.append(tuple(max(0, min(255, rv + cv - bv)) for rv, cv, bv in zip(r, c, b)))
    return out


def main():
    write_pal(PALETTES + "red_leaf_reflection.pal", reflection(read_pal(PALETTES + "red_leaf.pal")))
    print(PALETTES + "red_leaf_reflection.pal")


if __name__ == "__main__":
    main()
