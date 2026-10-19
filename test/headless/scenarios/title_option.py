# Build KANTO_DEBUG=1 : option TITRE = R.FEU puis sauvegarde (relancer title_check avec cette sauvegarde).
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26) + wait(600)
steps += tap("START") + wait(30) + tap("UP") + wait(10) + tap("UP") + wait(10) + tap("A") + wait(120)
for _ in range(7):
    steps += tap("DOWN") + wait(10)
steps += wait(20) + tap("RIGHT") + wait(60) + tap("B") + wait(120) + tap("B") + wait(60)
steps += tap("START") + wait(30) + tap("UP") + wait(10) + tap("A") + wait(90)
steps += tap("A") + wait(300) + tap("A") + wait(240) + tap("A") + wait(300) + tap("B") + wait(60)
