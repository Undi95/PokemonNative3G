# Build KANTO_DEBUG=1 : Bourg Palette, attente : les fleurs (tileset_anims de RF) doivent changer d'image.
steps = wait(300) + tap("START") + wait(120) + tap("START") + wait(90) + tap("A") + wait(120)
steps += tap("A", 210, hold=4, gap=26) + wait(900)
