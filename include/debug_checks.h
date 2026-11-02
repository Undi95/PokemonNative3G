#ifndef GUARD_DEBUG_CHECKS_H
#define GUARD_DEBUG_CHECKS_H

// PokemonNative3G : détecteurs d'anomalies (builds KANTO_DEBUG=1, src/debug_checks.c, docs/DEVTOOLS.md). Un
// comportement anormal (texte coupé, flèche hors de sa fenêtre, cadre dessiné avec les tiles d'une autre boîte,
// sprite de Pokémon figé, teinte jour/nuit coupée sur une image visible, special pas porté…) est signalé une fois par
// cause : liste « Anomalies » des outils de debug, événement du banc headless (journal : ANOMALIE), qui fait échouer
// le scénario s'il n'est pas dans test/headless/anomalies_known.txt. Sans KANTO_DEBUG, tout disparaît.

#ifdef KANTO_DEBUG_START
struct DebugToolsOutput;

// kind : le détecteur (« texte coupé »…) ; windowId : la fenêtre concernée, ou -1
void DebugChecks_Report(const char *kind, s32 windowId, const char *format, ...) __attribute__((format(printf, 3, 4)));
// Les détecteurs qui regardent l'état du jeu à chaque image (sprites…)
void DebugChecks_OnFrame(void);
// Tiles de la boîte de dialogue chargées (text_window.c) : style Kanto (RF) ou Émeraude, pour vérifier les cadres
void DebugChecks_OnMessageBoxGfx(u8 bg, u16 base, bool8 kanto);
// Les anomalies vues depuis le lancement (les plus récentes en dernier), pour la commande sys.anomalies
void DebugChecks_Print(struct DebugToolsOutput *out);
#else
#define DebugChecks_Report(...) ((void)0)
#define DebugChecks_OnFrame() ((void)0)
#define DebugChecks_OnMessageBoxGfx(...) ((void)0)
#endif

#endif // GUARD_DEBUG_CHECKS_H
