#ifndef GUARD_PLATFORM_DEVTOOLS_H
#define GUARD_PLATFORM_DEVTOOLS_H

// PokemonNative3G : ce que la plateforme fournit aux outils de debug (builds KANTO_DEBUG=1, src/platform/devtools.c).

// Le nom d'une adresse écrite « @N » par les outils (distance à AgbMain), lu dans le fichier .syms posé à côté du jeu
// par docker/build.sh ; NULL sans ce fichier ou sans symbole avant l'adresse. Le décalage dans le symbole va dans
// *delta.
const char *DevTools_SymbolName(long long offset, long long *delta);
// Le texte des outils avec chaque « @N » remplacé par son nom (« NULL » pour 0)
void DevTools_NameAddresses(char *dest, const char *src, unsigned destSize);

// Rapport de bug rejouable : la session commence au lancement (sauvegarde, heure locale), puis les touches de chaque
// image du jeu ; DevTools_WriteReport écrit rapport_DATE.tar dans le dossier des rapports (name = son nom ; sur
// Android, le partage est proposé). test/headless/replay.py rejoue un rapport.
void DevTools_StartSession(const char *savePath, const char *reportDir);
void DevTools_RecordFrameKeys(unsigned short keys);
// Les touches de l'image : celles du joueur, plus celles appuyées par la console (« touche »), enregistrées
unsigned short DevTools_FrameKeys(unsigned short physical);
bool8 DevTools_WriteReport(char *name, unsigned nameSize);
const char *DevTools_GetReportDir(void);

// Console en direct (--devtools PORT) : test/headless/dev.py envoie une ligne, la console répond {"reply": "…"}.
// Entre deux images du jeu : DevTools_PollConsole lit et répond aux commandes en attente.
void DevTools_StartConsole(int port);
void DevTools_PollConsole(void);
// La dernière image affichée (240x160, ABGR1555), pour la commande « capture » de la console
void DevTools_SetFrame(const unsigned short *image);

#endif // GUARD_PLATFORM_DEVTOOLS_H
