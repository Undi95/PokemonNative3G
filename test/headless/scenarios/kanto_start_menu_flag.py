# Menu Start et dame de Bourg Palette (ProcessPlayerFieldInput de RF, 2026-11-04), sauvegarde « kanto » : ouvrir le
# menu Start pose FLAG_KANTO_OPENED_START_MENU (FLAG_OPENED_START_MENU de RF), que lisent les scripts de la dame qui
# cache le panneau des conseils (PalletTown, PalletTown_ProfessorOaksLab). Avant, seul son propre script le posait.
FIXTURE = "kanto"
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from driver import continue_game, wait_until
from menu_helpers import press_until_free


def play(game):
    continue_game(game)
    game.flag("FLAG_KANTO_OPENED_START_MENU", 0)
    before = str(game.flag("FLAG_KANTO_OPENED_START_MENU")).strip()
    wait_until(game, lambda s: s.free)
    game.tap("START"); game.wait(40)
    press_until_free(game)
    after = str(game.flag("FLAG_KANTO_OPENED_START_MENU")).strip()
    game.note(f"FLAG_KANTO_OPENED_START_MENU : {before} -> {after}")
    expect(game, before in ("0", "False") and after in ("1", "True"), f"menu Start ouvert : drapeau posé ({before} -> {after})")
