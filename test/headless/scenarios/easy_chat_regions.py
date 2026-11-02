# Easy Chat : les effets de fin d'écran suivent la région (les scripts de son jeu), pas l'écran (option MENUS).
# - Kanto, MENUS = HOENN (écran d'Émeraude) : effets de RF, ceux qu'attend le club Événement Mystère de Kanto
#   (FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE, VAR_0x8004 = 1 sans la phrase secrète). Avant : VAR_0x8004 restait 0
#   (EASY_CHAT_TYPE_PROFILE) et le club répondait toujours comme à la phrase secrète.
# - Hoenn, MENUS = KANTO (écran de RF) : effets d'Émeraude (FLAG_SYS_CHAT_USED).
from driver import *

FIXTURE = "kanto"


def write_profile(game, menus):
    """Ouvre le profil (Common_ShowEasyChatScreen, VAR_0x8004 = 0), place le 1er mot du 1er groupe, confirme."""
    game.dev("jeu.options", 11, menus)
    game.var("VAR_0x8004", 0)
    since = mark(game)
    game.script("Common_ShowEasyChatScreen")
    wait_text(game, "PROFIL", since, limit=600)
    game.wait(60)
    for _ in range(3):                          # le 1er mot, ses groupes, le 1er groupe, son 1er mot
        game.tap("A", gap=40)
        game.wait(20)
    since = mark(game)
    game.tap("START", gap=30)
    for _ in range(4):                          # Émeraude : START met le curseur sur OK, A demande « OK? »
        if saw_text(game, "OK?", since):
            break
        game.tap("A", gap=30)
    wait_text(game, "OK?", since, limit=300)
    game.wait(30)
    game.tap("A", gap=20)                       # OUI
    wait_until(game, lambda s: s.free or s.script or s.locked, limit=600)
    game.wait(60)


def play(game):
    continue_game(game)
    game.dev("jeu.options", 0, 2)               # texte rapide

    write_profile(game, 0)                      # Kanto (Bourg Palette), écran d'Émeraude
    expect(game, game.flag("FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE") == 1, "Kanto, écran d'Émeraude : drapeau de RF")
    expect(game, game.var("VAR_0x8004") == 1, "Kanto, écran d'Émeraude : VAR_0x8004 = 1 (pas la phrase secrète)")

    game.warp("LittlerootTown", 10, 10)         # Hoenn
    game.wait(60)
    game.flag("FLAG_SYS_CHAT_USED", 0)
    game.flag("FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE", 0)
    write_profile(game, 1)                      # Hoenn, écran de RF
    expect(game, game.flag("FLAG_SYS_CHAT_USED") == 1, "Hoenn, écran de RF : FLAG_SYS_CHAT_USED d'Émeraude")
    expect(game, game.flag("FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE") == 0, "Hoenn, écran de RF : pas le drapeau de RF")
