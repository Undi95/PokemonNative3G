# Build KANTO_DEBUG=1 : menu DEBUG > Ajout objets, puis ouverture du sac.
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26) + wait(600)
steps += tap("START") + wait(30) + tap("A") + wait(30) + tap("DOWN") + wait(10) + tap("DOWN") + wait(10) + tap("DOWN") + wait(10) + tap("DOWN") + wait(10) + tap("DOWN") + wait(10) + tap("A") + wait(60) + tap("B") + wait(60)
steps += tap("START") + wait(30) + tap("DOWN") + wait(10) + tap("A") + wait(150)
steps += [(400, "DOWN")] + wait(60)                 # fin de la poche Objets
steps += tap("RIGHT", 4, gap=40) + wait(60) + [(300, "DOWN")] + wait(60)   # Objets Rares
