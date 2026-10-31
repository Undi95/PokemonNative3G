# Build KANTO_DEBUG=1 : fenêtres éclairées du cycle jour/nuit (tools/day_night_lights.py). Chaque ville la nuit,
# vitres marquées en magenta (commande de test daynight 2), une capture par ville dans shots/ : à regarder quand
# on change les couleurs de vitre (seules les fenêtres doivent être en magenta).
from driver import *  # les vérifications (expect...)
import glob, json, os
import driver
import maps
from driver import fight_battle, finish_dialog, wait_until

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(driver.__file__))))


def towns():
    layouts = {l['id']: l for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts'] if 'id' in l}
    for f in sorted(glob.glob(os.path.join(ROOT, 'data/maps/*/map.json'))):
        m = json.load(open(f, encoding='utf-8'))
        if m.get('map_type') in ('MAP_TYPE_TOWN', 'MAP_TYPE_CITY') and m.get('layout') in layouts:
            l = layouts[m['layout']]
            yield m['name'], l['width'] // 2, l['height'] // 2


def play(game):
    game.wait(300); game.tap("START"); game.wait(120); game.tap("START"); game.wait(90); game.tap("A")
    game.wait(120)
    game.tap("A", 210, hold=4, gap=26)
    wait_until(game, lambda s: s.free); game.wait(30)
    game.command("clock", 23, 0)
    game.command("daynight", int(os.environ.get("DN_MARK", "2")))  # DN_MARK=1 : rendu réel
    for name, x, y in towns():
        group, num = maps.find_map(name)
        game.command("warp", group, num, x, y); game.wait(90)
        game.shot(name)
        # Une scène peut démarrer à l'arrivée : on la passe pour pouvoir repartir
        finish_dialog(game, button="B", on_battle=lambda g: fight_battle(g))
    game.command("daynight", 0)
