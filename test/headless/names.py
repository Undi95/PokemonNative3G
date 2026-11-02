"""Names for the numbers in the game's state: flags, variables, items and
species from include/constants, functions from the build's symbols, and text
from the game's charset (charmap.txt).
"""

import bisect
import functools
import glob
import os
import re

from headless import REPO_DIR

# --- Constants -------------------------------------------------------------

_PREFIXES = ("FLAG_", "VAR_", "ITEM_", "SPECIES_", "TRAINER_", "MOVE_")


@functools.lru_cache(None)
def _defines():
    """Every #define of include/constants, as name -> expression."""
    defines = {}
    for path in glob.glob(os.path.join(REPO_DIR, "include", "constants", "**", "*.h"), recursive=True):
        with open(path, encoding="utf-8", errors="replace") as f:
            for line in f:
                match = re.match(r"\s*#define\s+(\w+)\s+(.+?)\s*(//.*)?$", line)
                if match and "(" not in match.group(1):
                    defines.setdefault(match.group(1), match.group(2).split("/*")[0].strip())
    return defines


def _evaluate(name, seen=()):
    expression = _defines().get(name)
    if expression is None or name in seen:
        return None

    def replace(match):
        word = match.group(0)
        if re.fullmatch(r"0[xX][0-9a-fA-F]+|\d+", word):
            return str(int(word, 0))
        value = _evaluate(word, seen + (name,))
        if value is None:
            raise ValueError(word)
        return str(value)

    try:
        text = re.sub(r"\b[A-Za-z_]\w*\b|\b0[xX][0-9a-fA-F]+\b|\b\d+\b", replace, expression)
        if not re.fullmatch(r"[\d\s+\-*/()<>|&]+", text):
            return None
        return int(eval(text.replace("/", "//")))
    except (ValueError, SyntaxError, ZeroDivisionError):
        return None


@functools.lru_cache(None)
def value(name):
    """The value of a constant, like "FLAG_BADGE01_GET" or "ITEM_POTION"."""
    result = _evaluate(name)
    if result is None:
        raise KeyError(f"unknown constant {name}")
    return result


def number(name_or_number):
    return name_or_number if isinstance(name_or_number, int) else value(name_or_number)


# Other kinds of constants that share a prefix: a trainer is TRAINER_ROXANNE_1, not TRAINER_PIC_...
_OTHER_KINDS = {"TRAINER_": ("TRAINER_PIC_", "TRAINER_BACK_PIC_", "TRAINER_CLASS_", "TRAINER_ENCOUNTER_MUSIC_",
                             "TRAINER_TYPE_", "TRAINER_PARTY_", "TRAINER_ITEM", "TRAINER_SIGHT_", "TRAINER_FLAG",
                             "TRAINER_BATTLE_", "TRAINER_HILL_", "TRAINER_SLIDE_")}


@functools.lru_cache(None)
def _reverse(prefix):
    names = {}
    for name in _defines():
        if name.startswith(_OTHER_KINDS.get(prefix, ())):
            continue
        if name.startswith(prefix) and not name.endswith(("_COUNT", "_START", "_END")):
            number = _evaluate(name)
            if number is not None:
                names.setdefault(number, name)
    return names


def name(prefix, number):
    """A constant's name from its value, like name("ITEM_", 13) -> "ITEM_POTION"."""
    return _reverse(prefix).get(number, f"{prefix}{number:#x}")


# --- Functions -------------------------------------------------------------

class Symbols:
    """The functions and data of a build, from the .syms file next to it (see
    docker/build.sh), to name the offsets from AgbMain in the state and in the
    debug tools' text ("@N", see expand())."""

    def __init__(self, binary):
        self.addresses, self.names = [], []
        base = os.path.splitext(os.path.abspath(binary))[0]
        path = base + ".syms"
        if not os.path.exists(path):
            return
        symbols = []
        with open(path) as f:
            for line in f:
                parts = line.split()
                if len(parts) == 3:
                    symbols.append((int(parts[0], 16), parts[2]))
        symbols.sort()
        agb_main = next((address for address, sym in symbols if sym == "AgbMain"), None)
        if agb_main is None:
            return
        self.addresses = [address - agb_main for address, _ in symbols]
        self.names = [sym for _, sym in symbols]

    def __call__(self, offset):
        if offset == 0:
            return None
        i = bisect.bisect_right(self.addresses, offset) - 1
        if i < 0:
            return f"?{offset:+#x}"
        return self.names[i] if offset == self.addresses[i] else f"{self.names[i]}+{offset - self.addresses[i]:#x}"

    def offset(self, name):
        """The offset from AgbMain of a function or data (a script...), for the debug tools that take an address."""
        try:
            return self.addresses[self.names.index(name)]
        except ValueError:
            raise KeyError(f"{name} n'est pas dans les symboles de la build") from None

    def expand(self, text):
        """The debug tools' text (src/debug_tools.c) with each "@N" replaced by its symbol."""
        return re.sub(r"@(-?\d+)", lambda m: self(int(m.group(1))) or "NULL", text)


# --- Text ------------------------------------------------------------------

# Length of each extended control code (FC xx), with the code: GetExtCtrlCodeLength
_EXT_LENGTHS = [1, 2, 2, 2, 4, 2, 2, 1, 2, 1, 1, 3, 2, 2, 2, 1, 3, 2, 2, 2, 2, 1, 1, 1, 1]


@functools.lru_cache(None)
def _charmap():
    # The glyphs of the POKé and POKéBLOC symbols, whose bytes are kana in Japanese
    chars = {0x53: "PK", 0x54: "MN", 0x55: "PO", 0x56: "Ké", 0x57: "BL", 0x58: "OC", 0x59: "K"}
    japanese = False
    with open(os.path.join(REPO_DIR, "charmap.txt"), encoding="utf-8") as f:
        for line in f:
            if line.startswith("@ "):
                japanese = line.startswith(("@ Hiragana", "@ Katakana", "@ Japanese"))
            if japanese:
                continue
            match = re.match(r"'(.+?)'\s*=\s*([0-9A-Fa-f]{2})\s*$", line.split("@")[0].strip())
            if match:
                char = match.group(1).replace("\\'", "'").replace('\\"', '"')
                chars.setdefault(int(match.group(2), 16), char)
    chars[0x00] = " "
    chars[0x77] = " "     # CHAR_SPACER, the space that aligns numbers (money...)
    # The glyphs with a name in charmap.txt (SUPER_E = 84...): superscripts of the French floors (9ᵉ, 1ᵉʳ), arrows
    chars.update({0x2C: "ᵉʳ", 0x34: "N.", 0x64: "PCo", 0x79: "↑", 0x7A: "↓", 0x7B: "←", 0x7C: "→", 0x84: "ᵉ",
                  0xA0: "ʳᵉ"})
    return chars


@functools.lru_cache(None)
def _braille():
    """Braille cells to letters, from the encoder of .braille strings (tools/preproc/asm_file.cpp) and the cells'
    values (BRAILLE_CHAR_* in include/constants/characters.h). The digits share the cells of A to J."""
    cells = {}
    with open(os.path.join(REPO_DIR, "tools", "preproc", "asm_file.cpp"), encoding="utf-8") as f:
        for char, name in re.findall(r"\{ '(\\?.)', (BRAILLE_CHAR_\w+) \}", f.read()):
            number = value(name)
            if number is not None and not char.isdigit():
                cells.setdefault(number, char.replace("\\", "").upper())
    return cells


def decode_braille(data):
    """Text in the braille font (FONT_BRAILLE), as "⠿ " and its letters: the number sign stays "#"."""
    if isinstance(data, str):
        data = bytes.fromhex(data)
    cells = _braille()
    out = []
    for byte in data:
        if byte == 0xFF:
            break
        out.append("\n" if byte == 0xFE else cells.get(byte, "�"))
    return "⠿ " + "".join(out)


def decode(data):
    """Text in the game's charset (bytes or hex) as a str. New lines are "\\n",
    and a wait for a button press is " ▼ "."""
    if isinstance(data, str):
        data = bytes.fromhex(data)
    chars = _charmap()
    out = []
    i = 0
    while i < len(data):
        byte = data[i]
        if byte == 0xFF:
            break
        if byte == 0xFE:
            out.append("\n")
        elif byte in (0xFA, 0xFB):
            out.append(" ▼ ")
        elif byte == 0xFC:
            code = data[i + 1] if i + 1 < len(data) else 0
            if code == 0x09:
                out.append(" ▼ ")
            i += 1 + (_EXT_LENGTHS[code] if code < len(_EXT_LENGTHS) else 1) - 1
        elif byte == 0xFD:
            out.append(f"{{{data[i + 1] if i + 1 < len(data) else 0:02X}}}")
            i += 1
        elif byte in (0xF7, 0xF8, 0xF9):
            i += 1
        else:
            out.append(chars.get(byte, "�"))   # un octet sans lettre : un texte mal encodé
        i += 1
    return "".join(out)
