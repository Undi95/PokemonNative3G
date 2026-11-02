#!/usr/bin/env python3
"""Écrit src/data/debug_names.h : le nom de chaque drapeau, variable et dresseur du jeu (Émeraude et Rouge Feu),
rangés par région et par catégorie, pour l'outil scripts.drapeaux des builds DEBUG (src/debug_tools.c, docs/DEVTOOLS.md)
et les noms acceptés par la console (« scripts.flag FLAG_SYS_GAME_CLEAR 1 »).

usage: debug_names.py [--check]   (--check : échoue si le fichier n'est pas à jour, sans l'écrire)
"""

import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "test", "headless"))
import names  # noqa: E402  (évalue les #define de include/constants)

OUT = os.path.join(REPO, "src", "data", "debug_names.h")

# (catégorie, préfixes des drapeaux après FLAG_ ou FLAG_KANTO_), la première qui va gagne
FLAG_CATEGORIES = [
    ("Système", ("SYS_",)),
    ("Badges", ("BADGE",)),
    ("Personnages", ("HIDE_",)),
    ("Objets ramassés", ("ITEM_",)),
    ("Objets cachés", ("HIDDEN_",)),
    ("Reçus", ("RECEIVED_", "GOT_")),
    ("Combats", ("DEFEATED_", "FOUGHT_")),
    ("PokéNav", ("REGISTERED_", "ENABLE_SHIP_", "MATCH_CALL")),
    ("Carte", ("LANDMARK_", "VISITED_", "WORLD_MAP_")),
    ("Temporaires", ("TEMP_",)),
    ("Journaliers", ("DAILY_",)),
    ("Sans nom", ("UNUSED_", "0X")),
    ("Autres", ("",)),
]

# Les noms de constantes qui ne sont pas des drapeaux / variables
NOT_A_NAME = re.compile(r"_(START|END|COUNT)$|^FLAGS_COUNT$|^VARS_")


def defines(path, prefix):
    with open(os.path.join(REPO, path), encoding="utf-8") as f:
        return [m.group(1) for m in re.finditer(r"^#define\s+(" + prefix + r"\w*)\s", f.read(), re.M)
                if not NOT_A_NAME.search(m.group(1))]


def unique(found):
    """(nom, valeur) sans doublon de valeur (le premier nom reste)."""
    seen = set()
    result = []
    for name in found:
        try:
            value = names.value(name)
        except KeyError:            # un enum (REMATCH_…) que l'évaluateur ne lit pas : gardé tel quel
            value = None
        if value is not None and value in seen:
            continue
        seen.add(value)
        result.append((name, value))
    return result


def flag_category(name):
    kanto = name.startswith("FLAG_KANTO_")
    rest = name[len("FLAG_KANTO_" if kanto else "FLAG_"):].upper()
    for title, prefixes in FLAG_CATEGORIES:
        if rest.startswith(prefixes):
            return f"{'Kanto' if kanto else 'Hoenn'} : {title}"
    raise AssertionError(name)


def build():
    flags = unique(defines("include/constants/flags.h", "FLAG_") + defines("include/constants/kanto.h", "FLAG_")
                   + defines("include/constants/kanto_flags_vars.h", "FLAG_"))
    variables = unique(defines("include/constants/vars.h", "VAR_")
                       + defines("include/constants/kanto_flags_vars.h", "VAR_"))
    trainers = unique(defines("include/constants/opponents.h", "TRAINER_")
                      + defines("include/constants/kanto_trainers.h", "TRAINER_"))
    trainers = [(n, v) for n, v in trainers if not n.endswith("_NONE")]

    # Les catégories, dans l'ordre : drapeaux de Hoenn, de Kanto, puis dresseurs et variables
    entries = []    # (catégorie, genre, nom)
    for name, _ in flags:
        entries.append((flag_category(name), "DEBUG_NAME_FLAG", name))
    for name, value in trainers:
        region = "Kanto" if name.startswith("TRAINER_KANTO_") else "Hoenn"
        entries.append((f"{region} : Dresseurs", "DEBUG_NAME_TRAINER", name))
    for name, _ in variables:
        region = "Kanto" if name.startswith("VAR_KANTO_") else "Hoenn"
        entries.append((f"{region} : Variables", "DEBUG_NAME_VAR", name))
    order = []
    for region in ("Hoenn", "Kanto"):
        order += [f"{region} : {title}" for title, _ in FLAG_CATEGORIES]
        order += [f"{region} : Dresseurs", f"{region} : Variables"]
    order = [c for c in order if any(e[0] == c for e in entries)]
    entries.sort(key=lambda e: order.index(e[0]))     # sort stable : l'ordre des en-têtes dans chaque catégorie

    lines = ["// Généré par tools/debug_names.py depuis include/constants (flags, vars, kanto, opponents,",
             "// kanto_trainers) : ne pas modifier à la main. Inclus seulement par src/debug_tools.c (builds DEBUG).",
             "",
             "static const char *const sDebugNameCategories[] = {"]
    lines += [f'    "{c}",' for c in order]
    lines += ["};", "", "static const struct DebugName sDebugNames[] = {"]
    for category, kind, name in entries:
        lines.append(f'    {{{name}, {order.index(category)}, {kind}, "{name}"}},')
    lines += ["};", ""]
    return "\n".join(lines)


def main():
    text = build()
    current = open(OUT, encoding="utf-8").read() if os.path.exists(OUT) else ""
    if "--check" in sys.argv:
        if current != text:
            sys.exit("src/data/debug_names.h n'est pas à jour : python tools/debug_names.py")
        return
    if current != text:
        with open(OUT, "w", encoding="utf-8", newline="\n") as f:
            f.write(text)
    print(f"{OUT} : {text.count(chr(10))} lignes")


if __name__ == "__main__":
    main()
