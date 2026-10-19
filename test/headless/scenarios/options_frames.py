# Build KANTO_DEBUG=1 : Options > CADRE, gauche depuis le type 1 = type 29 (cadre 10 de Rouge Feu).
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26) + wait(600)
steps += tap("START") + wait(30) + tap("UP") + wait(10) + tap("UP") + wait(10) + tap("A") + wait(120)
steps += tap("DOWN", 5, gap=10) + wait(20) + tap("LEFT") + wait(60) + tap("LEFT") + wait(60)
