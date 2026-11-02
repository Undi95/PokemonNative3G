#ifndef GUARD_PLATFORM_DEVTOOLS_H
#define GUARD_PLATFORM_DEVTOOLS_H

// PokemonNative3G : ce que la plateforme fournit aux outils de debug (builds KANTO_DEBUG=1, src/platform/devtools.c).

// Le nom d'une adresse écrite « @N » par les outils (distance à AgbMain), lu dans le fichier .syms posé à côté du jeu
// par docker/build.sh ; NULL sans ce fichier ou sans symbole avant l'adresse. Le décalage dans le symbole va dans
// *delta.
const char *DevTools_SymbolName(long long offset, long long *delta);
// Le texte des outils avec chaque « @N » remplacé par son nom (« NULL » pour 0)
void DevTools_NameAddresses(char *dest, const char *src, unsigned destSize);

// Console en direct (--devtools PORT) : test/headless/dev.py envoie une ligne, la console répond {"reply": "…"}.
// Entre deux images du jeu : DevTools_PollConsole lit et répond aux commandes en attente.
void DevTools_StartConsole(int port);
void DevTools_PollConsole(void);
// La dernière image affichée (240x160, ABGR1555), pour la commande « capture » de la console
void DevTools_SetFrame(const unsigned short *image);

#endif // GUARD_PLATFORM_DEVTOOLS_H
