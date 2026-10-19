# Build KANTO_DEBUG=1 : nouvelle partie à Bourg Palette, puis téléport DEBUG vers chaque destination.
import json, os
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26) + wait(600)
marks = []
for i in range(int(os.environ.get('KW_FIRST', 0)), int(os.environ.get('KW_LAST', 22))):
    steps += tap("START") + wait(30) + tap("A") + wait(30) + tap("A") + wait(30)
    steps += tap("DOWN", i) + tap("A") + wait(240)
    marks.append(sum(f for f, _ in steps))
    steps += walk("DOWN", 2) + walk("UP", 2) + wait(30)
open(os.environ.get('KW_MARKS', 'marks.json'), 'w').write(json.dumps(marks))
