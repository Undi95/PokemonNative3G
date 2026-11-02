#ifndef GUARD_DEBUG_TOOLS_H
#define GUARD_DEBUG_TOOLS_H

// PokemonNative3G : outils de debug (builds KANTO_DEBUG=1). Un seul registre de commandes, appelées depuis le menu
// DEBUG en jeu, le banc headless (« !dev ID ARGS », src/platform/test_state.c) et la console en direct du PC
// (--devtools, src/platform/devtools_console.c). Voir docs/DEVTOOLS.md.

enum DebugToolCategory
{
    DEBUG_TOOLS_GAME,     // état du moteur : callbacks, tâches, options
    DEBUG_TOOLS_MAP,      // carte, objets, connexions
    DEBUG_TOOLS_SCRIPT,   // scripts en cours, flags, variables
    DEBUG_TOOLS_PLAYER,   // équipe, sac, argent
    DEBUG_TOOLS_BATTLE,   // combat
    DEBUG_TOOLS_GFX,      // sprites, palettes, BG, fenêtres
    DEBUG_TOOLS_TEXT,     // imprimantes de texte
    DEBUG_TOOLS_SOUND,    // musique et effets
    DEBUG_TOOLS_SYSTEM,   // RNG, horloge, mémoire
    DEBUG_TOOLS_CATEGORY_COUNT,
};

#define DEBUG_TOOLS_MAX_ARGS 4

// Résultat d'une commande : texte UTF-8, une ligne par information
struct DebugToolsOutput
{
    char *text;
    u32 size;
    u32 length;
};

struct DebugTool
{
    const char *id;          // « gfx.sprites » : le nom des commandes du banc et de la console
    u8 category;             // DEBUG_TOOLS_*
    const u8 *name;          // nom dans le menu DEBUG (texte du jeu)
    const char *help;        // ce que fait la commande et ses arguments
    u8 argCount;             // arguments obligatoires (nombres)
    void (*run)(const s32 *args, u32 argCount, struct DebugToolsOutput *out);
};

extern const struct DebugTool gDebugTools[];
extern const u32 gDebugToolsCount;
extern const u8 *const gDebugToolsCategoryNames[DEBUG_TOOLS_CATEGORY_COUNT];

void DebugTools_Print(struct DebugToolsOutput *out, const char *format, ...) __attribute__((format(printf, 2, 3)));
const struct DebugTool *DebugTools_Find(const char *id);
// Lance « ID ARG… » ; FALSE si la commande n'existe pas ou manque d'arguments (le texte dit pourquoi)
bool8 DebugTools_RunLine(const char *line, struct DebugToolsOutput *out);
// Texte UTF-8 -> texte du jeu (lettres, chiffres, ponctuation, accents français ; le reste devient « ? »)
void DebugTools_ToGameText(u8 *dest, const char *src, u32 destSize);
// Texte du jeu -> UTF-8 (fin de ligne -> espace, autres codes et caractères sans équivalent -> « ? »)
void DebugTools_GameTextToUtf8(char *dest, const u8 *src, u32 destSize);
// Écran des outils dans le menu DEBUG (src/debug_tools_menu.c) ; B le ferme et rouvre le menu DEBUG
void DebugToolsMenu_Open(void);
// Le résultat d'une commande (sans nombres), ouvert depuis le menu DEBUG ; B y revient
void DebugToolsMenu_OpenResult(const char *id);
// Une adresse de fonction ou de donnée en distance à AgbMain (écrite « @N » ; les symboles de la build donnent son nom)
long long DebugTools_Offset(const void *address);

#endif // GUARD_DEBUG_TOOLS_H
