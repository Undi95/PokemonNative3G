# Easy Chat de Rouge Feu (option MENUS = KANTO, src/kanto_easy_chat_*.c) : le profil, à Kanto. Les écrans de RF
# (phrase, groupes, mots, confirmation), un mot placé, OK ; puis les effets qu'attendent les scripts de RF (club
# Événement Mystère) : FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE, et VAR_0x8004 = 1 (pas la phrase secrète).
from driver import *

FIXTURE = "kanto"


def play(game):
    continue_game(game)
    game.dev("jeu.options", 0, 2)               # texte rapide
    game.dev("jeu.options", 11, 1)              # MENUS = KANTO
    expect(game, game.flag("FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE") == 0, "pas encore de profil")
    game.var("VAR_0x8004", 0)                   # EASY_CHAT_TYPE_PROFILE
    since = mark(game)
    game.script("Common_ShowEasyChatScreen")
    wait_text(game, "PROFIL", since, limit=600)
    game.wait(60)
    check_screen(game, "kanto_easy_chat-profil")

    game.tap("A", gap=40)                       # le 1er mot : les groupes
    game.wait(30)
    check_screen(game, "kanto_easy_chat-groupes")
    game.tap("A", gap=40)                       # le 1er groupe : ses mots
    game.wait(30)
    check_screen(game, "kanto_easy_chat-mots")
    game.tap("A", gap=40)                       # le 1er mot, placé
    game.wait(30)
    check_screen(game, "kanto_easy_chat-mot_place")

    since = mark(game)
    game.tap("START", gap=30)                   # START : « … est comme ceci. OK? »
    wait_text(game, "OK?", since, limit=300)
    game.wait(30)
    check_screen(game, "kanto_easy_chat-confirmation")
    game.tap("A", gap=20)                       # OUI
    wait_until(game, lambda s: s.free or s.script or s.locked, limit=600)
    game.wait(60)
    expect(game, game.flag("FLAG_KANTO_SYS_SET_TRAINER_CARD_PROFILE") == 1, "drapeau du profil de RF mis")
    expect(game, game.var("VAR_0x8004") == 1, "VAR_0x8004 = 1 : pas la phrase secrète")

    # La LETTRE (EASY_CHAT_TYPE_MAIL : 9 mots, la 1re lettre du sac), puis B : « Ne plus donner LETTRE à PKMN? » OUI
    game.var("VAR_0x8004", 4)
    game.var("VAR_0x8005", 0)
    since = mark(game)
    game.script("Common_ShowEasyChatScreen")
    wait_text(game, "neuf", since, limit=600)   # pas de titre dans RF : « Avec neuf (groupes de) mots, »
    game.wait(60)
    check_screen(game, "kanto_easy_chat-lettre")
    since = mark(game)
    game.tap("B", gap=30)
    wait_text(game, "Ne plus donner", since, limit=300)
    game.wait(30)
    game.tap("UP", gap=20)                      # le curseur part sur NON (EC_CreateYesNoMenuWithInitialCursorPos(1))
    game.tap("A", gap=20)
    expect(game, wait_until(game, lambda s: s.free, limit=600).free, "retour sur la carte après la LETTRE")
