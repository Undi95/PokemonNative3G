# Headless tests

These scripts play the PC build without a window, using its test mode:

```
pokeemerald64 --test-input input.txt --test-hashes hashes.txt [--save game.sav] [--test-shots DIR --test-shot-every N]
```

The input file holds lines of `<frames> <buttons>`, like `30 A+UP` or `60 -`, and the
game exits when it ends. Each frame runs one audio update and the clock is fixed, so a
run only depends on its input and save file: the same build always produces the same
frames, and two builds that behave the same produce the same hashes.

Everything needs Python 3. The scripts work with any PC build (Linux or Windows).

## Checks

`smoke.py BINARY` plays a new game up to the first save, continues that save and saves
again, fights the first battle and saves with the starter, fights it again with keys
and controller inputs (default and remapped), plays on through the rival battle to the
Pokédex, resets with A+B+START+SELECT and saves again, and plays with random buttons. Every run has to finish, and the saves
have to be valid GBA-format saves with the expected contents. After the reset, the game
has to give the same frames as after power on. CI runs it on Linux and Windows for every
push and pull request.

(PokemonNative3G: with a `KANTO_DEBUG=1` build, which starts in Pallet Town, the frames and
the saves don't match what it expects, but every run, `random_play` included, still has to
finish.) Every run also has to give exactly the frames in `expected_frames.txt`, a SHA-256 of each
run's frame hashes. Builds agree on them across compilers and platforms, so a difference
means the game behaves differently. If a change is meant to do that, write the new frames
with `smoke.py BINARY --update-expected` and commit them with the change.

`smoke.py BINARY --audit` also runs `audit_data.py`, which checks every map and song in
the running game through gdb: each pointer, count and struct alignment, the way the C
code reads them. It covers data the scenarios never load. It needs Linux, gdb, and a
build with debug info (`make linux CFLAGS=-g`).

`compare.py BASELINE CANDIDATE` runs the same scenarios with two builds and reports the
first frame whose video or audio differs. Use it to confirm that a change doesn't alter
the game, e.g. by comparing a build of your branch against one of `vanilla`.

`savecheck.py SAVE` checks a save file against the GBA format, independently of the
game code, and prints what's in it.

## Test bench (PokemonNative3G)

`suite.py BINARY [SCENARIO ...]` plays every scenario that defines `play(game)` (or the
ones given) in parallel and writes a short report, `build/headless/suite/report.txt`: a
line per scenario, and for the ones that failed, why and the end of their journal. The
whole suite takes about 45 seconds. A scenario fails when one of its checks does, or when
the game crashes, freezes (no answer for 60 s), stops going anywhere (a `wait_until` that
never ends), or prints a sanitizer report.

Before a release, `bash test-release.sh` (at the top of the repository, after
`build-all.sh`) runs it on the release's Windows build, then on a Linux build with
AddressSanitizer and UBSan (`docker/test-sanitize.sh`), which also catches reads and
writes out of bounds that don't show.

What a scenario did can be read in its `journal.txt`, without screenshots: the text the
game printed (decoded with `charmap.txt`), flags, variables and items that changed,
maps, screens (the main callback, by name, from the build's symbols), music, sounds
(`SON`, `game.sounds`), Pokémon cries (`CRI`, `game.cries`: `PlayCryInternal`, which doesn't
go through `m4aSongNumStart`), battles with their Pokémon and outcome, and the party, each
with the frame and where the player was.
The game writes these with its state (see `src/platform/test_state.c`); `cb1`, `cb2` and
`tasks` in the state name what it's running, which tells a menu and a freeze apart.
`party` and `foe` list each Pokémon as `[species, level, hp, max hp, status, egg, personality]`
(the personality gives, for example, an Unown's letter: see `scenarios/kanto_unown.py`).
The game's own checks (`src/debug_checks.c`, `docs/DEVTOOLS.md`) report what looks wrong:
a letter cut by the edge of its window, the wait arrow outside its window, a text box frame
drawn with the tiles of the other style, a Pokémon's sprite stuck on its second frame, the
day/night tint cut while the field is still shown, a special that isn't ported yet. Each
shows once in the journal as `ANOMALIE kind : text` (`game.anomalies`), and fails its
scenario unless `anomalies_known.txt` lists it. `ANOMALY_SHOTS=1` also takes a screenshot
after each one (`shots/anomalie_FRAME_N.ppm`). `TEST_FONT=0` or `1` sets the POLICE option
(Hoenn or Kanto letters) for the whole run: `TEST_FONT=1 suite.py BINARY --out DIR` checks
for anomalies with the other font (the screen references are made with the default,
Hoenn, so they don't match then). Each text event also has its color (`game.text_colors`).

Between frames, a scenario can also run test commands (lines starting with `!` in the
input, so a run can still be replayed from `input.txt`), to set a scenario up quickly or
check what it did: `game.flag(name, value)`, `game.var`, `game.item(name, add)`,
`game.money`, `game.give_mon(species, level)`, `game.heal()`, `game.warp(map, x, y)`,
`save(game)` and `game.shot(name)`. Names are the constants of `include/constants`.
`game.shot(name)` writes the last frame as it was drawn, before its VBlank; a name used twice keeps
only the last screenshot (give each call its own name). For a diagnosis, `game.shot_now(name)` draws
the current state (after the VBlank) on demand, and `game.dev("gfx.pixel", x, y)` tells what each
background and sprite gives at one point of the screen.
`game.dev("gfx.sprites")` runs one of the debug tools (`docs/DEVTOOLS.md`, `aide` lists them) and
returns its text, with functions and data named; `dev.py` sends the same commands to a DEBUG game
that runs on the PC. A bug report made in a DEBUG game (DEBUG > Rapport de bug: the save at launch, the
keys of every frame, the state and the last screens) is played again with `replay.py BINARY report.tar`,
up to the same frame; `report_check.py BINARY` checks that whole chain. `game.script("EventScript_PC")`
starts a map script by its name (the screen references keep the name, not the address, which changes
from one build to another), `game.start_menu()` gives the start menu's entries and cursor.

Two tools go through the whole game: `crawl.py BINARY` visits every map and talks to every person,
sign and hidden item (`build/headless/crawl/atlas.json` and `rapport.txt`: texts, battles, anomalies,
errors, suspect texts), and `matrix.py BINARY` opens every screen with the display options combined
two by two, in both regions (one contact sheet per screen in `build/headless/matrix/planches/`).
See `docs/DEVTOOLS.md`.

Checks fail the scenario and go to the journal: `expect(game, condition, message)`,
`expect_text` (words of a text the game printed, since a `mark`), `expect_map`,
`expect_flag`, `expect_var`, `expect_item`, `expect_party`, `expect_battle` (a battle
against a trainer or a species, and how it ended) and `expect_song`. What can only be
seen is checked with `check_screen(game, name)`, against `refs/NAME.png`: a scenario that
sets `SCREENS = True` checks the screen at each of its `log` steps. A missing reference
is made from the screen, to look at once: `refs_sheet.py` puts the new ones (or `--all`)
on one image. `suite.py --update-refs` replaces them, when the screens change on purpose.
A reference that wasn't compared because the scenario played differently before it fails
the scenario: a screen nobody compares can hide a regression.

A scenario that sets `FIXTURE = "kanto"` starts from the save that
`scenarios/fixture_kanto.py` ends with (a new game in Pallet Town), made once per build.
One that sets `SAVE = "windows-1.1-hoenn.sav"` starts from that file of `saves/`: saves
kept as an older version wrote them, which the game has to keep loading (`save_old_windows`).

`boulders.py` finds the pushes that take a STRENGTH boulder onto a tile (a hole, a
switch) on the map as it is in the game, and plays them (`kanto_strength_puzzles`).

`KANTO_START = 0` (the Hoenn intro, the truck) works for both kinds of scenarios; without
it, a new game starts in Pallet Town (`--kanto-start 1`, or the `KANTO_START` environment
variable). The `steps` scenarios of `compare.py` (`new_game`, then `continue_game`,
`first_battle`, `soft_reset`, `rival_battle` from its save) were timed for an older game:
they no longer reach the save, so the chain past `new_game` plays from no save (to redo
with `play(game)`).

## Scenarios

Scenarios are in `scenarios/`, in one of two kinds.

A scenario that defines `play(game)` decides what to press from the game's state, which
the game writes after each input: the map and position, whether a script or a battle is
going on, the music. `driver.py` has the actions to build one from: `continue_game`,
`walk_to` (finds the way on the map, around people and as far as it can through no
grass), `leave_map`, `talk_to`, `finish_dialog`, `fight_battle` and `save_game`:

```python
def play(game):
    continue_game(game)
    walk_to(game, 11, 0)
    leave_map(game, "UP")                 # to the next map
    walk_to(game, 10, 4)
    talk_to(game, "UP")                   # and anything that follows, like a battle
```

These keep working when something changes on the way, like a wild Pokémon appearing,
so new scenarios should be written like this (see `scenarios/rival_battle.py`). Their
input goes to `input.txt` as usual, and `states.jsonl` has every state.

The first scenarios build `steps`, a list of `(frames, buttons)`, with the helpers
`tap`, `wait` and `walk` (see `headless.py`):

```python
steps = wait(300) + tap("START")          # skip the intro
steps += walk("UP", 3)                    # 16 frames per tile
steps += tap("A", 10, hold=4, gap=26)     # press A 10 times
```

Besides the GBA buttons, a step can press keys and controller inputs, which go through
the bindings in the settings like when playing: `key:Z`, `pad:a`, `pad:lefty-` (the
names are the settings file's). A scenario that sets `CONFIG` to a settings file in
this directory plays with it (see `scenarios/controls.py`).

They are timed to the frame, so a change to game timing can make one go off track. To
write or fix one, take screenshots and look at them on a contact sheet (needs
ImageMagick):

```
python3 test/headless/run.py ./pokeemerald64 new_game --shots 60 --sheet
```

`--save FILE` starts from a save, `--param NAME=VALUE` passes values like `SEED`
and `FRAMES` to `random_play`, and `--audio` writes the sound to `audio.wav`. Output
goes to `build/headless/`.
