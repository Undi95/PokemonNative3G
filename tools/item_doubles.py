import re, glob, os
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
RX = re.compile(r'\s*(giveitem|giveitem_msg|additem|finditem|msgreceiveditem|giveitemfanfaremsg)\s.*?\b(ITEM_\w+)')
HM = {'ITEM_HM0%d' % (i + 1): n for i, n in enumerate(['ITEM_HM_CUT', 'ITEM_HM_FLY', 'ITEM_HM_SURF', 'ITEM_HM_STRENGTH',
                                                       'ITEM_HM_FLASH', 'ITEM_HM_ROCK_SMASH', 'ITEM_HM_WATERFALL', 'ITEM_HM_DIVE'])}


def scan(paths):
    d = {}
    for f in paths:
        where = f.split('/maps/')[-1].split('/')[0] if '/maps/' in f else os.path.basename(f)
        for i, l in enumerate(open(f, encoding='utf-8', errors='ignore')):
            m = RX.match(l)
            if m:
                d.setdefault(HM.get(m.group(2), m.group(2)), []).append('%s:%d' % (where, i + 1))
    return d


allf = [f.replace(os.sep, '/') for f in glob.glob('data/**/*.inc', recursive=True)]
k = scan([f for f in allf if '/kanto/' in f])
h = scan([f for f in allf if '/kanto/' not in f])
items = open('src/data/items.h', encoding='utf-8').read()
key = set()
for m in re.finditer(r'\[(ITEM_\w+)\] =\s*\{(.*?)\n    \},', items, re.S):
    if 'POCKET_KEY_ITEMS' in m.group(2) or 'POCKET_TM_HM' in m.group(2):
        key.add(m.group(1))
print(len(k), len(h), len(key))
for it in sorted(set(k) & set(h)):
    if it in key or it.startswith('ITEM_HM'):
        print('|', it, '|', ', '.join(sorted(set(h[it]))), '|', ', '.join(sorted(set(k[it]))), '|')
