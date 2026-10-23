# Build KANTO_DEBUG=1 : Options > DIALOGUE = KANTO, puis SAUVEGARDER (boîte de dialogue de Rouge Feu).
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26) + wait(600)
steps += tap("START") + wait(30) + tap("UP") + wait(10) + tap("UP") + wait(10) + tap("A") + wait(120)
steps += tap("R") + wait(30) + tap("DOWN", 2, gap=10) + wait(20) + tap("RIGHT") + wait(60) + tap("B") + wait(120) + tap("B") + wait(60)
steps += tap("START") + wait(30) + tap("UP") + wait(10) + tap("A") + wait(120)
