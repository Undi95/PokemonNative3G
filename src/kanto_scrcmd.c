// Commandes de script de Rouge Feu absentes d'Émeraude (src/scrcmd.c de RF), utilisées par
// les scripts de Kanto. Leurs opcodes (0xc7-0xcc, 0xd0) sont libres (nop1) dans Émeraude ;
// getbraillestringwidth reçoit un nouvel opcode à la fin de la table.
#include "global.h"
#include "kanto_map_preview_screen.h"
#include "event_data.h"
#include "overworld.h"
#include "script.h"
#include "string_util.h"
#include "text.h"

bool8 ScrCmd_textcolor(struct ScriptContext *ctx)
{
    gSpecialVar_PrevTextColor = gSpecialVar_TextColor;
    gSpecialVar_TextColor = ScriptReadByte(ctx);
    return FALSE;
}

// TODO Kanto : système d'aide de RF (bouton L/R) pas encore porté ; l'argument est lu.
bool8 ScrCmd_loadhelp(struct ScriptContext *ctx)
{
    ScriptReadPointer(ctx);
    return FALSE;
}

bool8 ScrCmd_unloadhelp(struct ScriptContext *ctx)
{
    return FALSE;
}

// TODO Kanto : style « panneau » de la boîte de message de RF (MsgSetSignpost) pas encore porté.
bool8 ScrCmd_signmsg(struct ScriptContext *ctx)
{
    return FALSE;
}

bool8 ScrCmd_normalmsg(struct ScriptContext *ctx)
{
    return FALSE;
}

bool8 ScrCmd_comparestat(struct ScriptContext *ctx)
{
    u8 statIdx = ScriptReadByte(ctx);
    u32 value = ScriptReadWord(ctx);
    u32 statValue = GetGameStat(statIdx);

    if (statValue < value)
        ctx->comparisonResult = 0;
    else if (statValue == value)
        ctx->comparisonResult = 1;
    else
        ctx->comparisonResult = 2;
    return FALSE;
}

// RF : QuestLog_RecordEnteredMap (journal, non porté) + MapPreview_SetFlag (pose le flag de carte).
bool8 ScrCmd_setworldmapflag(struct ScriptContext *ctx)
{
    u16 value = ScriptReadHalfword(ctx);
    MapPreview_SetFlag(value); // pose le drapeau ; l'aperçu dure plus longtemps à la première visite
    return FALSE;
}

bool8 ScrCmd_getbraillestringwidth(struct ScriptContext *ctx)
{
    u8 *msg = (u8 *)ScriptReadPointer(ctx);
    if (msg == NULL)
        msg = (u8 *)ctx->data[0];

    gSpecialVar_0x8004 = GetStringWidth(FONT_BRAILLE, msg, -1);
    return FALSE;
}
