#!/usr/bin/env python3
"""Runs every scenario that plays with the driver, in parallel, and reports
in a few lines: what passed, and for what didn't, why and how it ended.

usage: suite.py BINARY [SCENARIO ...] [--jobs N] [--update-refs] [--out DIR]

Without SCENARIO, runs all of scenarios/ that define play(game), apart from
those that set SUITE = False (like the fixtures). A scenario fails when one of
its checks does (expect...), when the game crashes, freezes or stops going
anywhere, or when it writes a sanitizer report. Each one's journal.txt says
what happened in the game, in order; the report quotes its end.
"""

import argparse
import concurrent.futures
import glob
import os
import re
import sys
import time

from headless import BUILD_DIR, REPO_DIR, SCENARIO_DIR, run_scenario, scenario_variables

# Where the copies are made (BIOS, DMA, palettes, tiles): a report names who asked for the copy
COPY_HELPERS = ("src/platform/bios.c", "src/platform/dma.c", "src/palette.c", "src/dma3_manager.c", "src/bg.c")
KNOWN_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "sanitizer_known.txt")


def sanitizer_reports(stderr):
    """The sanitizers' reports in a run's output, as (place, message): UBSan's
    "src/x.c:L:C: runtime error: ..." and AddressSanitizer's "ERROR: ...",
    placed at the first frame of the game's code."""
    reports = []
    lines = stderr.splitlines()
    for i, line in enumerate(lines):
        ubsan = re.match(r"(src/[\w/.]+:\d+):\d+: runtime error: (.*)", line)
        if ubsan:
            reports.append((ubsan.group(1), ubsan.group(2)))
        asan = re.search(r"ERROR: (AddressSanitizer|LeakSanitizer): ([\w-]+)", line)
        if asan:
            # The first frame of the game's code that is not a copy helper
            place = next((m.group(1) for later in lines[i + 1:i + 40]
                          for m in [re.search(r" in \w+ (src/[\w/.]+:\d+)", later)]
                          if m and not m.group(1).startswith(COPY_HELPERS)), "?")
            located = next((j for j in range(i + 1, min(i + 80, len(lines))) if "is located" in lines[j]), None)
            detail = re.sub(r"0x[0-9a-f]+ ?", "", lines[located].strip())[:150] if located else ""
            if located and "in stack" in lines[located]:     # whose stack it was
                frame = next((m.group(1) for later in lines[located + 1:located + 4]
                              for m in [re.search(r" in (\w+ src/[\w/.]+:\d+)", later)] if m), "")
                detail = f"pile de {frame}"
            reports.append((place, f"{asan.group(2)} : {detail}"))
    return reports


def known_reports():
    """The places of sanitizer_known.txt: reports already known, which don't fail the suite."""
    known = {}
    if os.path.exists(KNOWN_PATH):
        with open(KNOWN_PATH, encoding="utf-8") as f:
            for line in f:
                place, _, note = line.partition("#")
                if place.strip():
                    known[place.strip()] = note.strip()
    return known


def suite_scenarios():
    names = []
    for path in sorted(glob.glob(os.path.join(SCENARIO_DIR, "*.py"))):
        name = os.path.splitext(os.path.basename(path))[0]
        with open(path, encoding="utf-8") as f:
            source = f.read()
        if "def play(" not in source:
            continue
        variables = scenario_variables(name)
        if variables.get("SUITE", True):
            names.append(name)
    return names


class Result:
    def __init__(self, name, out_dir):
        self.name = name
        self.out_dir = out_dir
        self.status = "?"
        self.message = ""
        self.frames = 0
        self.seconds = 0
        self.checks = 0
        self.new_refs = []
        self.tail = []
        self.known = []
        self.stale_refs = []


def run_one(binary, name, out_root):
    result = Result(name, os.path.join(out_root, name))
    start = time.time()
    try:
        run = run_scenario(binary, name, result.out_dir)
    except Exception as e:  # a fixture that failed, or a mistake in the scenario
        result.status, result.message = "ERREUR", f"{type(e).__name__}: {e}"
        result.seconds = time.time() - start
        return result
    result.seconds = time.time() - start
    result.frames = run.frames

    journal_path = os.path.join(result.out_dir, "journal.txt")
    journal = []
    if os.path.exists(journal_path):
        with open(journal_path, encoding="utf-8") as f:
            journal = f.read().splitlines()
    result.checks = sum(" OK : " in line for line in journal)
    result.new_refs = [line.split("écran ", 1)[1].split(" ")[0] for line in journal if "NOUVELLE RÉFÉRENCE" in line]
    result.stale_refs = [line.split("écran ", 1)[1].split(" ")[0] for line in journal if "RÉFÉRENCE À REVOIR" in line]
    result.tail = journal[-12:]

    stderr = run.stderr or ""
    wrong = re.search(r"went wrong: (.*)", stderr)
    known = known_reports()
    reports = list(dict.fromkeys(sanitizer_reports(stderr)))
    result.known = sorted({place for place, _ in reports if place in known})
    new = [(place, message) for place, message in reports if place not in known]
    if new:
        result.status = "ERREUR"
        result.message = "sanitizer : " + " | ".join(f"{place} {message}" for place, message in new[:4])
    elif wrong:
        failed_check = any(" ÉCHEC : " in line for line in journal[-3:])
        result.status = "ÉCHEC" if failed_check else "ERREUR"
        result.message = wrong.group(1)
    elif not run.ok:
        result.status = "ERREUR"
        result.message = f"le jeu s'est arrêté (code {run.returncode & 0xFFFFFFFF:#x}) : {stderr.strip()[-300:]}"
    else:
        result.status = "OK"
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("binary")
    parser.add_argument("scenarios", nargs="*")
    parser.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 2) // 2))
    parser.add_argument("--update-refs", action="store_true", help="replace the reference screens (refs/)")
    parser.add_argument("--out", default=os.path.join(BUILD_DIR, "suite"))
    args = parser.parse_args()
    if args.update_refs:
        os.environ["UPDATE_REFS"] = "1"

    names = args.scenarios or suite_scenarios()
    start = time.time()
    results = []
    with concurrent.futures.ThreadPoolExecutor(args.jobs) as pool:
        futures = [pool.submit(run_one, args.binary, name, args.out) for name in names]
        for future in concurrent.futures.as_completed(futures):
            result = future.result()
            results.append(result)
            print(f"  {result.status:<6} {result.name}", flush=True)

    results.sort(key=lambda r: (r.status == "OK", r.name))
    lines = []
    for r in results:
        detail = f"{r.frames:>6} frames {r.seconds:5.1f} s  {r.checks:>2} vérifs"
        lines.append(f"{r.status:<6} {r.name:<32} {detail}" + ("  SANS VÉRIF" if r.status == "OK" and not r.checks else ""))
        if r.status != "OK":
            lines.append(f"       → {r.message}")
            lines += [f"       | {line}" for line in r.tail[-8:]]
            lines.append(f"       (journal : {os.path.relpath(os.path.join(r.out_dir, 'journal.txt'), REPO_DIR)})")
        for ref in r.new_refs:
            lines.append(f"       NOUVELLE RÉFÉRENCE à valider : test/headless/refs/{ref}.png")
        if r.stale_refs:
            lines.append(f"       {len(r.stale_refs)} RÉFÉRENCE(S) À REVOIR (le scénario joue autrement : --update-refs "
                         f"puis refs_sheet.py) : {' '.join(r.stale_refs[:4])}{' ...' if len(r.stale_refs) > 4 else ''}")
    known = sorted({place for r in results for place in r.known})
    if known:
        notes = known_reports()
        lines.append(f"\nDéfauts connus vus par les sanitizers (sanitizer_known.txt) : {len(known)}")
        lines += [f"       {place}  {notes[place]}" for place in known]
    failed = [r for r in results if r.status != "OK"]
    lines.append(f"\n{len(results) - len(failed)}/{len(results)} OK en {time.time() - start:.0f} s"
                 + (f", {len(failed)} en échec : {' '.join(r.name for r in failed)}" if failed else ""))

    report = "\n".join(lines)
    os.makedirs(args.out, exist_ok=True)
    with open(os.path.join(args.out, "report.txt"), "w", encoding="utf-8") as f:
        f.write(report + "\n")
    print(report)
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
