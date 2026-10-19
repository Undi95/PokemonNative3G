# Build KANTO_DEBUG=1 : maison du joueur à Bourg Palette, escalier vers le 2e étage et retour.
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26) + wait(600)
steps += walk("LEFT", 4) + walk("UP", 1) + wait(120)
steps += walk("UP", 1) + walk("RIGHT", 6) + walk("UP", 5) + walk("RIGHT", 2) + wait(150)
steps += walk("LEFT", 1) + wait(150)
