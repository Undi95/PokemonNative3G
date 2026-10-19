# Build KANTO_DEBUG=1 : nouvelle partie qui démarre à Bourg Palette, puis marche.
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26)               # discours de Birch, nom
steps += wait(600)
steps += walk("DOWN", 3) + walk("LEFT", 4) + walk("UP", 3) + walk("RIGHT", 4) + wait(60)
steps += tap("START") + wait(60)
