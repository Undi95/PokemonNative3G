"""Plays the game from Python, deciding what to press from what's going on.

The game runs its test mode with its input coming from here a line at a time,
and after each line it writes its state: the map and position, whether a
script or a battle is running, the music and so on (see WriteTestState in
src/platform/test_state.c). Everything pressed is written to input.txt, so a
run can be replayed like any other scenario, and gives the same frames.

A scenario that defines play(game) is played this way, with the actions below:

    def play(game):
        continue_game(game)
        walk_to(game, 11, 0)          # on the current map, around people
        leave_map(game, "UP")
        finish_dialog(game)
"""

import hashlib
import json
import os
import queue
import re
import shutil
import subprocess
import threading
import unicodedata

import maps
import names


class GameError(Exception):
    pass


class CheckFailed(GameError):
    """A check of the scenario failed (see expect)."""


BATTLE_OUTCOMES = {0: "-", 1: "WON", 2: "LOST", 3: "DREW", 4: "RAN", 5: "PLAYER_TELEPORTED", 6: "MON_FLED",
                   7: "CAUGHT", 8: "NO_SAFARI_BALLS", 9: "FORFEITED", 10: "MON_TELEPORTED"}


class State:
    def __init__(self, data):
        self.__dict__.update(data)
        self.pos = tuple(self.pos)
        self.objects = [tuple(o) for o in self.objects]
        self.party = [tuple(m) for m in data.get("party", [])]
        self.foe = [tuple(m) for m in data.get("foe", [])]
        self.events = data.get("events", [])

    @property
    def map_name(self):
        return maps.map_name(*self.map) if self.map[0] >= 0 else None

    @property
    def free(self):
        """In the overworld with nothing going on, so the player can move."""
        return (self.overworld and not self.locked and not self.script and not self.battle
                and not self.fade and not self.moving)

    def __repr__(self):
        return (f"<frame {self.frame}: {self.map_name} {self.pos}, "
                f"{'battle' if self.battle else 'free' if self.free else 'busy'}, bgm {self.bgm}>")


# Variables that change at every step, left out of the journal
NOISY_VARS = ("STEP_COUNTER", "STEP_COUNT", "_STEPS_1", "_STEPS_2")


def mon_text(mon):
    species, level, hp, max_hp = mon[:4]
    return f"{names.name('SPECIES_', species)[8:]} N{level} {hp}/{max_hp}"


class Game:
    def __init__(self, binary, out_dir, save=None, config=None, shot_every=0, audio=False, max_frames=200000,
                 kanto_start=None, step_timeout=60, test_time=None):
        os.makedirs(out_dir, exist_ok=True)
        self.out_dir = out_dir
        self.save_path = os.path.join(out_dir, "game.sav")
        self.hashes_path = os.path.join(out_dir, "hashes.txt")
        self.max_frames = max_frames
        # Seconds the game can take to answer before it's taken to be frozen
        self.step_timeout = step_timeout
        self.symbols = names.Symbols(binary)
        if os.path.exists(self.save_path):
            os.remove(self.save_path)
        if save:
            shutil.copyfile(save, self.save_path)
        self.shots_dir = os.path.join(out_dir, "shots")
        shutil.rmtree(self.shots_dir, ignore_errors=True)
        os.makedirs(self.shots_dir)

        if kanto_start is None:
            kanto_start = os.environ.get("KANTO_START", "1")
        cmd = [os.path.abspath(binary), "--kanto-start", str(kanto_start), "--save", self.save_path,
               "--test-input", "-", "--test-state", "-", "--test-hashes", self.hashes_path]
        if config:
            cmd += ["--config", config]
        # Screenshots every shot_every frames go to out_dir, the ones asked for (shot) to shots/
        cmd += ["--test-shots", out_dir if shot_every else self.shots_dir]
        if shot_every:
            cmd += ["--test-shot-every", str(shot_every)]
        if audio:
            cmd += ["--test-audio", os.path.join(out_dir, "audio.wav")]
        # The game's clock at frame 0, in seconds (it advances one second every 60 frames): replay.py
        if test_time is not None:
            cmd += ["--test-time", str(int(test_time))]
        # TEST_FONT=0 ou 1 : l'option POLICE imposée (textes coupés : ANOMALIE texte coupé dans le journal)
        if os.environ.get("TEST_FONT"):
            cmd += ["--test-font", os.environ["TEST_FONT"]]
        self.stderr = open(os.path.join(out_dir, "stderr.txt"), "w")
        # Every state read, for looking into what happened
        self.states = open(os.path.join(out_dir, "states.jsonl"), "w")
        # What happened, to read: see note()
        self.journal = open(os.path.join(out_dir, "journal.txt"), "w", encoding="utf-8")
        self.proc = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=self.stderr,
                                     text=True, bufsize=1, encoding="utf-8", errors="replace")
        self._lines = queue.Queue()
        threading.Thread(target=self._read_lines, daemon=True).start()
        self.steps = []
        self.frames = 0
        self.texts = []           # (frame, window, text) of every text printed
        self.text_colors = []     # the text color (TEXT_COLOR_*) of each of self.texts
        self.anomalies = []       # (frame, kind, text) of every anomaly the game's checks found (src/debug_checks.c)
        self._anomaly_shots = []  # ANOMALY_SHOTS=1: a screenshot after each one (shots/anomalie_FRAME)
        self.events = []          # (frame, event) of every event
        self.battles = []         # every battle: {"trainer", "foes", "outcome"}
        self.songs = []           # (frame, song) of every song that started
        self.last_note = ""
        self.name = os.path.basename(os.path.normpath(out_dir))
        self.screens = False      # log() also checks the screen (a scenario's SCREENS)
        self.state = None
        self.state = self._read_state()

    def _read_lines(self):
        for line in self.proc.stdout:
            self._lines.put(line)
        self._lines.put(None)

    def _read_line(self):
        try:
            line = self._lines.get(timeout=self.step_timeout)
        except queue.Empty:
            self.proc.kill()
            raise GameError(f"frozen: no answer in {self.step_timeout} s, at {self.describe()}")
        if line is None:
            code = self.proc.wait()
            raise GameError(f"the game exited (exit code {code & 0xFFFFFFFF:#x}) at {self.describe()}")
        return line

    def _read_state(self):
        while True:
            line = self._read_line()
            if line.startswith("{"):
                self.states.write(line)
                state = State(json.loads(line))
                self._follow(self.state, state)
                return state

    # --- What happened ---

    def note(self, text, frame=None):
        """Writes a line to journal.txt, with the frame and where the player is.
        The same line again is counted instead of written."""
        state = self.state
        if state and state.overworld:
            self._in_game = True
        where = (f"{state.map_name} {state.pos[0]},{state.pos[1]}"
                 if state and state.map_name and getattr(self, "_in_game", False) else "-")
        if text == getattr(self, "_last_text", None):
            self._repeats += 1
            return
        self._flush_repeats()
        self._last_text, self._repeats = text, 0
        line = f"{self.frames if frame is None else frame:>7} {where:<30} {text}"
        self.journal.write(line + "\n")
        self.journal.flush()
        self.last_note = line

    def _flush_repeats(self):
        if getattr(self, "_repeats", 0):
            self.journal.write(f"{'':>7} {'':<30} (×{self._repeats + 1})\n")
            self._repeats = 0

    def function(self, offset):
        return self.symbols(offset) or "-"

    def describe(self):
        """The state, with what the game is running, for errors."""
        state = self.state
        if state is None:
            return "start"
        tasks = ", ".join(self.function(t) for t in state.tasks)
        return f"{state} cb2 {self.function(state.cb2)}, tasks [{tasks}]"

    def _follow(self, old, new):
        """Notes what changed in the journal."""
        self.state = new
        if old is None:
            return
        if new.map != old.map and new.map_name:
            self.note(f"CARTE {new.map_name}")
        if new.battle and not old.battle:
            foes = ", ".join(mon_text(m) for m in new.foe)
            is_trainer = new.battle_type & names.value("BATTLE_TYPE_TRAINER")
            trainer = f"dresseur {names.name('TRAINER_', new.trainer)}" if is_trainer else "sauvage"
            self.note(f"COMBAT début ({trainer}) : {foes}")
            self.battles.append({"trainer": names.name("TRAINER_", new.trainer) if is_trainer else None,
                                 "foes": [names.name("SPECIES_", m[0]) for m in new.foe], "outcome": None})
        if old.battle and not new.battle:
            self.note(f"COMBAT fin : {BATTLE_OUTCOMES.get(new.outcome, new.outcome)}")
            if self.battles:
                self.battles[-1]["outcome"] = BATTLE_OUTCOMES.get(new.outcome, new.outcome)
        if [m[:2] for m in new.party] != [m[:2] for m in old.party]:
            self.note("ÉQUIPE " + ", ".join(mon_text(m) for m in new.party))
        for event in new.events:
            self.events.append((self.frames, event))
            kind = event["t"]
            if kind == "text":
                text = names.decode(event["hex"])
                self.texts.append((self.frames, event["win"], text))
                self.text_colors.append(event.get("fg"))
                if text.strip() not in ("", "▶"):
                    self.note(f"TEXTE[{event['win']}] " + text.replace("\n", " / "))
            elif kind == "anomaly":
                text = self.symbols.expand(event["text"])
                self.anomalies.append((self.frames, event["kind"], text))
                self.note(f"ANOMALIE {event['kind']} : {text}")
                if os.environ.get("ANOMALY_SHOTS"):
                    self._anomaly_shots.append(f"anomalie_{self.frames}_{len(self.anomalies)}")
            elif kind == "flag":
                self.note(f"FLAG {names.name('FLAG_', event['id'])} = {event['v']}")
            elif kind == "var" and not names.name('VAR_', event['id']).endswith(NOISY_VARS):
                self.note(f"VAR {names.name('VAR_', event['id'])} = {event['v']}")
            elif kind == "item":
                self.note(f"OBJET {names.name('ITEM_', event['id'])} : {event['n']} dans le sac")
            elif kind == "bgm" and event["v"] >= 0:
                self.note(f"MUSIQUE {names.name('MUS_', event['v'])}", event["f"])
                self.songs.append((event["f"], names.name("MUS_", event["v"])))
            elif kind == "cb2":
                screen = self.function(event["v"])
                if any(word in screen for word in ("Copyright", "TitleScreen", "MainMenu", "Intro")):
                    self._in_game = False   # back to the title: the map is the last save's
                self.note(f"ÉCRAN {screen}", event["f"])
            elif kind == "bulk":
                self.note(f"({event['n']} flags/variables/objets changés : chargement ou nouvelle partie)")
            elif kind == "overflow":
                self.note("(trop d'événements, la suite est perdue)")

    # --- Playing ---

    def press(self, buttons="-", frames=1):
        """Holds buttons ("A", "UP+B", "-" for none) for some frames."""
        if self.frames + frames > self.max_frames:
            raise GameError(f"over {self.max_frames} frames")
        self.proc.stdin.write(f"{frames} {buttons}\n")
        self.proc.stdin.flush()
        self.steps.append((frames, buttons))
        self.frames += frames
        state = self._read_state()
        while self._anomaly_shots:
            self.shot(self._anomaly_shots.pop(0))
        return state

    def wait(self, frames):
        return self.press("-", frames)

    def tap(self, button, times=1, hold=2, gap=20):
        for _ in range(times):
            self.press(button, hold)
            self.press("-", gap)
        return self.state

    def command(self, *words):
        """Runs a test command (see RunTestCommand in src/platform/test_state.c)
        between two frames and returns its answer."""
        line = "!" + " ".join(str(w) for w in words)
        self.proc.stdin.write(line + "\n")
        self.proc.stdin.flush()
        self.steps.append((None, line))
        while True:
            text = self._read_line()
            if text.startswith("{"):
                reply = json.loads(text)
                if "reply" in reply:
                    if reply.get("error"):
                        raise GameError(f"{line}: {reply['error']}")
                    return reply["reply"]

    def dev(self, *words):
        """Runs a debug tool (src/debug_tools.c, "aide" lists them) and returns its
        text, with the functions and data named."""
        return self.symbols.expand(self.command("dev", *words))

    def flag(self, flag, set_to=None):
        """Reads a flag (a name like "FLAG_BADGE01_GET" or a number), or sets it."""
        args = [names.number(flag)] + ([int(set_to)] if set_to is not None else [])
        return self.command("flag", *args)

    def var(self, var, set_to=None):
        args = [names.number(var)] + ([set_to] if set_to is not None else [])
        return self.command("var", *args)

    def item(self, item, add=None):
        """How many of an item are in the bag, after adding (or removing) some."""
        args = [names.number(item)] + ([add] if add else [])
        return self.command("item", *args)

    def money(self, set_to=None):
        return self.command("money", *([set_to] if set_to is not None else []))

    def give_mon(self, species, level, item="ITEM_NONE"):
        return self.command("givemon", names.number(species), level, names.number(item))

    def heal(self):
        return self.command("heal")

    def warp(self, map_name, x, y):
        """Warps like the DEBUG menu, then waits until the player can move."""
        wait_until(self, lambda s: s.free)
        group, num = maps.find_map(map_name)
        self.command("warp", group, num, x, y)
        self.note(f"TÉLÉPORT {map_name} {x},{y}")
        self.wait(2)
        return wait_until(self, lambda s: s.free, limit=600)

    def shot(self, name):
        """Writes a screenshot of the last frame to shots/NAME.ppm, and returns its path."""
        self.command("shot", name)
        return os.path.join(self.shots_dir, name + ".ppm")

    def finish(self):
        """Ends the game and writes input.txt. Returns the exit code."""
        with open(os.path.join(self.out_dir, "input.txt"), "w") as f:
            for frames, buttons in self.steps:
                f.write(f"{buttons}\n" if frames is None else f"{frames} {buttons}\n")
        try:
            self.proc.stdin.close()
        except OSError:
            pass
        try:
            returncode = self.proc.wait(timeout=self.step_timeout)
        except subprocess.TimeoutExpired:
            self.proc.kill()
            returncode = self.proc.wait()
        self.stderr.close()
        self.states.close()
        self._flush_repeats()
        self.journal.close()
        return returncode


# --- Checks ------------------------------------------------------------------

def expect(game, condition, message):
    """Fails the scenario with message if condition is false. Either way, the
    check goes to the journal."""
    if not condition:
        game.note(f"ÉCHEC : {message}")
        raise CheckFailed(message)
    game.note(f"OK : {message}")


def mark(game):
    """A point in the scenario to look for text from, with saw_text(since=...)."""
    return len(game.texts)


def saw_text(game, words, since=0):
    """Whether text with these words (any case, any spacing) was printed since a mark."""
    words = " ".join(words.split()).lower()
    return any(words in " ".join(text.replace("▼", " ").split()).lower() for _, _, text in game.texts[since:])


def wait_text(game, words, since=None, limit=600):
    """Waits until text with these words is printed (since a mark, by default now)."""
    since = mark(game) if since is None else since
    return wait_until(game, lambda s: saw_text(game, words, since), step=2, limit=limit)


def expect_text(game, words, since=0):
    expect(game, saw_text(game, words, since), f"texte « {words} »")


def expect_no_text(game, words, since=0):
    expect(game, not saw_text(game, words, since), f"pas de texte « {words} »")


def expect_map(game, map_name, pos=None):
    state = game.state
    ok = state.map_name == map_name and (pos is None or state.pos == tuple(pos))
    expect(game, ok, f"à {map_name}{f' {pos}' if pos else ''} (on est à {state.map_name} {state.pos})")


def expect_flag(game, flag, value=1):
    actual = game.flag(flag)
    expect(game, actual == int(value), f"{flag} = {int(value)}" + ("" if actual == int(value) else f" (vaut {actual})"))


def expect_var(game, var, value):
    actual = game.var(var)
    expect(game, actual == value, f"{var} = {value}" + ("" if actual == value else f" (vaut {actual})"))


def expect_item(game, item, count):
    actual = game.item(item)
    expect(game, actual == count, f"{count} × {item} dans le sac" + ("" if actual == count else f" (il y en a {actual})"))


def expect_party(game, species, level=None):
    """A Pokémon of this species (and level) is in the party."""
    number = names.number(species)
    found = any(m[0] == number and (level is None or m[1] == level) for m in game.state.party)
    expect(game, found, f"{species}{f' N{level}' if level else ''} dans l'équipe")


def expect_battle_outcome(game, outcome):
    actual = BATTLE_OUTCOMES.get(game.state.outcome, game.state.outcome)
    expect(game, actual == outcome, f"combat terminé par {outcome}" + ("" if actual == outcome else f" (pas {actual})"))


def expect_song(game, song, since_frame=0):
    """A song (MUS_...) started playing, since a frame."""
    played = [name for frame, name in game.songs if frame >= since_frame]
    expect(game, song in played, f"musique {song}" + ("" if song in played else f" (jouées : {played[-6:]})"))


def expect_battle(game, trainer=None, foe=None, outcome="WON"):
    """A battle took place (against this trainer, or with this foe), and ended with outcome."""
    for battle in game.battles:
        if ((trainer is None or battle["trainer"] == trainer) and (foe is None or foe in battle["foes"])
                and (outcome is None or battle["outcome"] == outcome)):
            expect(game, True, f"combat {trainer or foe or ''} → {outcome}")
            return
    expect(game, False, f"combat {trainer or foe or ''} → {outcome} (combats : {game.battles})")


REFS_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "refs")


def check_screen(game, name, max_pixels=0):
    """Compares the screen with refs/NAME.png, for what can only be checked by
    looking. Without a reference, the screen becomes it, to look at once to
    approve it (refs_sheet.py puts the new ones on one image); suite.py
    --update-refs replaces them. A difference fails, and writes
    shots/NAME.diff.png with the different pixels in red.

    The reference is only compared when the scenario pressed the same buttons
    up to it (refs/NAME.inputs has their hash): a scenario that plays
    differently (changed, or the driver reacting to the game) takes the screen
    at another moment, so it's noted as a reference to look at again instead."""
    from PIL import Image

    # ASCII, for the file names on every system
    name = unicodedata.normalize("NFKD", name).encode("ascii", "ignore").decode()
    name = re.sub(r"[^A-Za-z0-9-]+", "_", name).strip("_")
    # The same name twice in a scenario: the second screen is NAME_2
    used = game.__dict__.setdefault("_screen_names", {})
    used[name] = used.get(name, 0) + 1
    if used[name] > 1:
        name = f"{name}_{used[name]}"
    shot = Image.open(game.shot(name)).convert("RGB")
    ref = os.path.join(REFS_DIR, name + ".png")
    inputs_path = os.path.join(REFS_DIR, name + ".inputs")
    inputs = hashlib.sha1(repr(game.steps).encode()).hexdigest()
    if os.environ.get("UPDATE_REFS") == "1" or not os.path.exists(ref):
        os.makedirs(REFS_DIR, exist_ok=True)
        if not os.path.exists(ref) or list(Image.open(ref).convert("RGB").getdata()) != list(shot.getdata()):
            shot.save(ref)
            game.note(f"NOUVELLE RÉFÉRENCE écran {name} : à valider en la regardant (refs/{name}.png)")
        with open(inputs_path, "w") as f:
            f.write(f"{inputs} {game.frames}\n")
        return
    if os.path.exists(inputs_path):
        with open(inputs_path) as f:
            ref_inputs, ref_frame = f.read().split()
        if ref_inputs != inputs:
            game.note(f"RÉFÉRENCE À REVOIR écran {name} : le scénario a joué autrement avant "
                      f"(frame {game.frames}, la référence est de la frame {ref_frame})")
            return
    actual = list(shot.getdata())
    expected = list(Image.open(ref).convert("RGB").getdata())
    different = [i for i, (a, b) in enumerate(zip(actual, expected)) if a != b]
    detail = ""
    if different:
        diff = Image.new("RGB", shot.size)
        diff.putdata([(255, 0, 0) if a != b else tuple(c // 3 for c in a) for a, b in zip(actual, expected)])
        diff.save(os.path.join(game.shots_dir, name + ".diff.png"))
        xs = [i % shot.width for i in different]
        ys = [i // shot.width for i in different]
        detail = f" ({len(different)} pixels différents, x {min(xs)}-{max(xs)}, y {min(ys)}-{max(ys)})"
    expect(game, len(different) <= max_pixels, f"écran {name} comme la référence{detail}")


def wait_until(game, condition, step=2, limit=3000):
    """Waits until condition(state) is true."""
    start = game.frames
    while not condition(game.state):
        if game.frames - start > limit:
            raise GameError(f"waited {limit} frames, now {game.describe()}")
        game.wait(step)
    return game.state


def continue_game(game):
    """From power on: skips the intro and continues the save."""
    game.wait(300)
    game.tap("START")
    game.wait(120)
    game.tap("START")
    game.wait(200)
    game.tap("A")
    game.wait(200)
    game.tap("A")                   # CONTINUE
    return wait_until(game, lambda s: s.free)


def new_kanto_game(game):
    """From power on, with --kanto-start 1 (the default of the tests): a new
    game, through Birch's speech, until the player can move in Pallet Town."""
    game.wait(300)
    game.tap("START")
    game.wait(120)
    game.tap("START")
    game.wait(90)
    game.tap("A")                   # NEW GAME
    game.wait(120)
    for _ in range(400):
        if game.state.free:
            return game.state
        game.tap("A", hold=4, gap=26)
    raise GameError(f"the new game didn't start: {game.describe()}")


def save(game):
    """Saves the game like the start menu's SAVE (with a test command, quicker)."""
    wait_until(game, lambda s: s.free)
    if not game.command("save"):
        raise GameError("the save failed")
    game.note("SAUVEGARDE")
    return game.state


def finish_dialog(game, button="A", limit=400, on_battle=None, settle=20, answers=None):
    """Presses button until the player can move: through text, cutscenes, and
    battles that come up (see fight_battle). The player has to stay free for
    settle frames, since a script can start a little after a map loads.
    answers gives another button for a question, by its words: {"surnom": "B"}
    answers NO when the last text printed asks for a nickname."""
    for _ in range(limit):
        if answers and game.texts and not game.state.free and not game.state.battle:
            # The question, in the dialogue box: the menu of answers is printed after it
            dialogue = [text for _, window, text in game.texts if window == 0]
            last = " ".join(dialogue[-1].split()).lower() if dialogue else ""
            chosen = next((b for words, b in answers.items() if words.lower() in last), None)
            if chosen:
                game.tap(chosen, hold=2, gap=10)
                continue
        if game.state.free:
            for _ in range(settle // 2):
                game.wait(2)
                if not game.state.free:
                    break
            else:
                return game.state
            continue
        if game.state.battle:
            (on_battle or fight_battle)(game)
        else:
            game.tap(button, hold=2, gap=10)
    raise GameError(f"still busy after {limit} presses: {game.describe()}")


def fight_battle(game, limit=600):
    """Fights with the first move until the battle ends, and the next one when
    it runs out of PP. A goes through everything else, like the text and
    learning a move."""
    seen = mark(game)
    change_move = False
    turns = 0   # the moves' cursor goes 0 -RIGHT-> 1 -DOWN-> 3 -LEFT-> 2 -UP-> 0
    for _ in range(limit):
        if not game.state.battle:
            return wait_until(game, lambda s: not s.fade and s.overworld)
        new_texts = [text for _, _, text in game.texts[seen:]]
        seen = mark(game)
        if any("plus de PP" in t or "affecte pas" in t for t in new_texts):
            change_move = True
        # The moves are on screen: their type was just printed
        if change_move and any(t.startswith("TYPE/") for t in new_texts):
            game.tap(("RIGHT", "DOWN", "LEFT", "UP")[turns % 4], hold=2, gap=10)
            turns += 1
            change_move = False
        game.tap("A", hold=2, gap=10)
    raise GameError(f"the battle didn't end: {game.describe()}")


def walk_to(game, x, y, grass_cost=20, on_battle=fight_battle):
    """Walks to (x, y) on the current map, around people and through as little
    grass as it can. Battles that come up go to on_battle, and scripts that
    start are finished with finish_dialog. Stops if something takes the player
    to another map."""
    goal = (x, y)
    start_map = game.state.map
    blocked = set()
    tried = 0
    while True:
        state = game.state
        if state.map != start_map:
            return wait_until(game, lambda s: s.free or s.locked or s.script or s.battle)
        if state.battle:
            on_battle(game)
            continue
        if state.locked or state.script:
            finish_dialog(game, on_battle=on_battle)
            continue
        if not state.overworld or state.fade:
            game.wait(2)
            continue
        if state.pos == goal:
            if not state.moving:
                return state
            game.wait(1)
            continue

        path = maps.load(state.map_name).path(state.pos, goal, blocked | set(state.objects), grass_cost)
        if path is None:
            raise GameError(f"no way to {goal} from {state}")
        dx, dy = maps.DIRECTIONS[path[0]]
        next_tile = (state.pos[0] + dx, state.pos[1] + dy)
        game.press(path[0], 2)
        if game.state.pos != state.pos:
            tried = 0
            blocked.clear()
        else:
            # Something the map doesn't know about is in the way
            tried += 2
            if tried > 40:
                blocked.add(next_tile)
                tried = 0


FACING = {"DOWN": 1, "UP": 2, "LEFT": 3, "RIGHT": 4}


def talk_to(game, direction, finish=True):
    """Turns to face direction and talks to whoever is there, until the player
    can move again (or, without finish, until something starts)."""
    for _ in range(10):
        if game.state.facing == FACING[direction]:
            break
        game.press(direction, 1)
        game.wait(8)
    game.tap("A")
    # The script can take a few frames to start, while the player turns
    for _ in range(30):
        if not game.state.free:
            break
        game.wait(2)
    return finish_dialog(game) if finish else game.state


def talk_to_object(game, x, y, finish=True):
    """Walks next to whoever is at (x, y) on the current map and talks to them.
    Tries each side, from the nearest."""
    px, py = game.state.pos
    sides = sorted(maps.DIRECTIONS.items(), key=lambda d: abs(x - d[1][0] - px) + abs(y - d[1][1] - py))
    for direction, (dx, dy) in sides:
        try:
            walk_to(game, x - dx, y - dy)
        except GameError:
            continue
        if game.state.pos == (x - dx, y - dy):
            return talk_to(game, direction, finish)
    raise GameError(f"can't get next to {(x, y)}: {game.describe()}")


def _same_map(a, b):
    """Map names compared like their constants: "LittlerootTown" is MAP_LITTLEROOT_TOWN."""
    norm = lambda n: n[4:].replace("_", "").lower() if n.startswith("MAP_") else n.replace("_", "").lower()
    return norm(a) == norm(b)


def take_warp(game, dest_map):
    """Walks onto the warp (stairs, door...) of the current map that leads to
    dest_map, and waits until the next map is loaded."""
    start = game.state.map
    warps = [pos for pos, dest in maps.load(game.state.map_name).warps.items() if _same_map(dest, dest_map)]
    if not warps:
        raise GameError(f"no warp to {dest_map} on {game.state.map_name}")
    px, py = game.state.pos
    x, y = min(warps, key=lambda w: abs(w[0] - px) + abs(w[1] - py))
    walk_to(game, x, y)
    for direction in ("UP", "DOWN", "LEFT", "RIGHT"):     # a door is entered by walking into it
        if game.state.map != start:
            break
        game.press(direction, 8)
        game.wait(4)
    if game.state.map == start:
        raise GameError(f"the warp to {dest_map} didn't work: {game.describe()}")
    return wait_until(game, lambda s: s.free or s.locked or s.script or s.battle)


def new_hoenn_game(game):
    """From power on, with --kanto-start 0 (KANTO_START = 0 in a scenario): a
    new game of Emerald, through Birch's speech and the truck ride, until the
    player can move in it."""
    game.wait(300)
    game.tap("START")
    game.wait(120)
    game.tap("START")
    game.wait(90)
    game.tap("A")                   # NEW GAME
    game.wait(120)
    for _ in range(400):
        if game.state.overworld and game.state.map_name == "InsideOfTruck":
            break
        game.tap("A", hold=4, gap=26)
    else:
        raise GameError(f"the truck didn't come: {game.describe()}")
    return wait_until(game, lambda s: s.free, limit=6000)


def leave_map(game, direction, limit=300):
    """Walks off the map, or through a door, in a direction until the map
    changes. Scripts that start on the way (a trigger) are finished first."""
    start = game.state.map
    for _ in range(limit):
        if game.state.map != start:
            return wait_until(game, lambda s: s.free or s.locked or s.script or s.battle)
        if (game.state.script or game.state.locked) and game.state.overworld and not game.state.fade:
            finish_dialog(game)
            continue
        game.press(direction, 2)
    raise GameError(f"didn't leave {game.state.map_name} going {direction}: {game.describe()}")


def save_game(game, menu_position):
    """Saves from the start menu, where SAVE is menu_position items down."""
    game.tap("START")
    game.wait(30)
    game.tap("DOWN", menu_position)
    game.tap("A")
    game.wait(90)
    game.tap("A")                   # YES
    game.wait(300)
    game.tap("A")
    game.wait(240)
    game.tap("A")                   # overwrite: YES
    game.wait(300)
    game.tap("B")
    return wait_until(game, lambda s: s.free)
