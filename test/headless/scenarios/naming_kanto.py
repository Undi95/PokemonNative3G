# Build KANTO_DEBUG=1 : Options du menu principal (PERSO = RED, MENUS = KANTO) puis nouvelle partie
# jusqu'à l'écran de nom du joueur : écran de nom de Rouge Feu, sprite de Red.
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90)
steps += tap("DOWN") + tap("A") + wait(150)
steps += tap("DOWN", 6, gap=10) + tap("RIGHT") + wait(20)          # PERSO = RED
steps += tap("DOWN", 4, gap=10) + tap("RIGHT") + wait(20)          # MENUS = KANTO
steps += tap("B") + wait(150) + tap("UP") + tap("A") + wait(120)   # NOUVELLE PARTIE
steps += tap("A", 60, hold=4, gap=26) + wait(200)
