#!/usr/bin/env python3
"""Écrit src/data/debug_states.h : les états « histoire finie » de Hoenn et de Kanto, déduits des scripts du jeu
(data/**/*.inc), pour l'outil jeu.histoire des builds DEBUG (src/debug_tools.c, docs/DEVTOOLS.md) et l'explorateur
(crawl.py --etat histoire).

- Une variable d'avancement (*_STATE, *_MAP_SCENE_*, …) ne fait qu'avancer : sa valeur finale est la plus grande que
  les scripts lui donnent (setvar).
- Un drapeau que les scripts allument (setflag) sans jamais l'éteindre (clearflag) est à ON à la fin.
- Ne sont pas posés : les objets au sol et cachés (à ramasser encore), les dresseurs, les drapeaux temporaires et
  journaliers, les compteurs.

usage: debug_states.py [--check] [--liste]   (--liste : les variables et leur valeur finale, pour relire)
"""

import glob
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "test", "headless"))
import names  # noqa: E402

OUT = os.path.join(REPO, "src", "data", "debug_states.h")

# Les variables d'avancement de l'histoire, par leur nom
STORY_VAR = re.compile(r"_STATE$|_MAP_SCENE_|_STATE_|_PROGRESS|_INTRO_STATE")
# Ni des étapes de l'histoire, ni sûres à forcer
SKIPPED_VAR = re.compile(r"^VAR_(TEMP_|0x|RESULT|FACING|INTERNAL|OBJ_GFX|SPECIAL|FRONTIER|APPRENTICE|CONTEST|"
                         r"LOTTERY|POKELOT|SECRET_BASE|RECORD_MIX|TRICK_HOUSE|ABNORMAL_WEATHER|DAYS|DAILY|PACIFIDLOG_TM|"
                         r"MIRAGE|WEATHER_INSTITUTE_CLEARED|.*COUNTER|.*_COUNT$|.*STEP)"
                         # un moment, pas une étape : trajet, défi ou Ligue en cours, fossile en résurrection, résultat
                         # d'un combat E-Reader, jeux, vantardises
                         r"|.*(SS_TIDAL_STATE|CABLE_CAR_STATION|BOARD_BRINEY_BOAT|SAFARI_ZONE_STATE|CYCLING_CHALLENGE|"
                         r"GLASS_WORKSHOP|ELITE_4_STATE|MAP_SCENE_POKEMON_LEAGUE|BRAG_STATE|POKEMON_CENTER_TEALA|"
                         r"JOYFUL_GAME_CORNER|SEVEN_ISLAND_HOUSE_ROOM1|REVIVE_STATE|MAP_SCENE_TRAINER_TOWER|"
                         r"FOSSIL_RESURRECTION)")
SKIPPED_FLAG = re.compile(r"^FLAG_(KANTO_)?(TEMP_|DAILY_|ITEM_|HIDDEN_ITEM|HIDDEN_|UNUSED|0X|SPECIAL_FLAG|"
                          r"HIDE_.*_ITEM)")


def scripts():
    for path in glob.glob(os.path.join(REPO, "data", "**", "*.inc"), recursive=True):
        with open(path, encoding="utf-8", errors="replace") as f:
            yield path, f.read()


def number(text):
    try:
        return int(text, 0)
    except ValueError:
        try:
            return names.value(text)
        except KeyError:
            return None


def analyse():
    var_values, set_flags, cleared_flags = {}, set(), set()
    for _, text in scripts():
        for var, value in re.findall(r"^\s*setvar\s+(VAR_\w+)\s*,\s*([\w()+ ]+?)\s*(?:@.*)?$", text, re.M):
            value = number(value)
            if value is not None:
                var_values.setdefault(var, set()).add(value)
        set_flags.update(re.findall(r"^\s*setflag\s+(FLAG_\w+)", text, re.M))
        cleared_flags.update(re.findall(r"^\s*clearflag\s+(FLAG_\w+)", text, re.M))
    # Une variable que les scripts remettent à 0 n'est pas une étape de l'histoire mais un moment (le peintre du
    # hall des concours après une victoire : VAR_LILYCOVE_CONTEST_LOBBY_STATE)
    story_vars = {var: max(values) for var, values in var_values.items()
                  if STORY_VAR.search(var) and not SKIPPED_VAR.match(var) and max(values) > 0 and 0 not in values}
    story_flags = sorted(f for f in set_flags - cleared_flags if not SKIPPED_FLAG.match(f))
    return story_vars, story_flags


def region(name):
    return "Kanto" if "_KANTO_" in name else "Hoenn"


def build():
    story_vars, story_flags = analyse()
    lines = ["// Généré par tools/debug_states.py depuis les scripts (data/**/*.inc) : ne pas modifier à la main.",
             "// Les états « histoire finie » : variables d'avancement à leur plus grande valeur, drapeaux allumés",
             "// sans jamais être éteints. Inclus seulement par src/debug_tools.c (builds DEBUG).", ""]
    for zone in ("Hoenn", "Kanto"):
        flags = [f for f in story_flags if region(f) == zone]
        variables = sorted((v, n) for v, n in story_vars.items() if region(v) == zone)
        lines.append(f"static const u16 sStoryFlags_{zone}[] = {{")
        lines += [f"    {f}," for f in flags]
        lines += ["};", "", f"static const u16 sStoryVars_{zone}[][2] = {{"]
        lines += [f"    {{{v}, {n}}}," for v, n in variables]
        lines += ["};", ""]
    return "\n".join(lines), story_vars, story_flags


def main():
    text, story_vars, story_flags = build()
    if "--liste" in sys.argv:
        for var, value in sorted(story_vars.items()):
            print(f"{var} = {value}")
        print(f"{len(story_vars)} variables, {len(story_flags)} drapeaux")
        return
    current = open(OUT, encoding="utf-8").read() if os.path.exists(OUT) else ""
    if "--check" in sys.argv:
        if current != text:
            sys.exit("src/data/debug_states.h n'est pas à jour : python tools/debug_states.py")
        return
    if current != text:
        with open(OUT, "w", encoding="utf-8", newline="\n") as f:
            f.write(text)
    print(f"{OUT} : {len(story_vars)} variables, {len(story_flags)} drapeaux")


if __name__ == "__main__":
    main()
