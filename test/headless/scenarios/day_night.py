# Build KANTO_DEBUG=1 : cycle jour/nuit (option JOUR/NUIT, day_night.c). Bourg Palette à midi, au coucher du
# soleil et la nuit avec l'option, puis la nuit sans l'option (même écran qu'à midi), puis un intérieur
# la nuit (pas de teinte à l'intérieur).
SCREENS = True   # chaque étape (log) est comparée à son écran de référence (refs/)
from driver import *  # les vérifications (expect...)
import os, sys
import driver
sys.path.insert(0, os.path.join(os.path.dirname(driver.__file__), 'scenarios'))
from kanto_tour import log
from driver import wait_until


def at(game, hour, minute=0):
    game.command("clock", hour, minute)
    game.wait(70)   # la teinte relit l'heure une fois par seconde


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.command("daynight", 1)
    at(game, 12); log(game, "midi")
    at(game, 19); log(game, "coucher")
    at(game, 23); log(game, "nuit")
    game.command("daynight", 0); game.wait(10); log(game, "nuit sans option")
    game.command("daynight", 1); game.wait(10)
    game.warp("CeladonCity_Condominiums_RoofRoom", 7, 4); game.wait(60)
    log(game, "intérieur la nuit")
