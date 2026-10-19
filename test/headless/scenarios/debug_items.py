# Build KANTO_DEBUG=1 : menu DEBUG > Ajout objets, puis ouverture du sac.
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26) + wait(600)
steps += tap("START") + wait(30) + tap("A") + wait(30) + tap("DOWN") + wait(10) + tap("DOWN") + wait(10) + tap("DOWN") + wait(10) + tap("DOWN") + wait(10) + tap("DOWN") + wait(10) + tap("A") + wait(60) + tap("B") + wait(60)
steps += tap("START") + wait(30) + tap("DOWN") + wait(10) + tap("A") + wait(150)
