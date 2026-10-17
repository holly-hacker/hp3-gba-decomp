#include "types.h"
#include "background.h"
#include "font.h"
#include "conversation.h"
#include "dialog.h"
#include "dialog_box.h"
#include "dialog_inline.h"

// Shows line wLineIndex of block wBlockId with its speaker's portrait.
void ShowDialogLine(void)
{
    g_dwDialogTextId = g_aDialogBlocks[g_DialogState_candidate.wBlockId].pTextIds[g_DialogState_candidate.wLineIndex];
    g_dwDialogPortrait = g_aDialogTextInfo[g_dwDialogTextId].dwPortrait;
    SetDialogPortrait(g_pDialogPortraitActor);
    g_DialogState_candidate.pText = GetDialogLineText(g_dwDialogTextId);
    g_DialogState_candidate.pText = ExpandTextMacros(g_pDialogMacroExpandBuffer, g_DialogState_candidate.pText,
                                                     DIALOG_MACRO_EXPAND_BUFFER_SIZE);
    g_DialogState_candidate.pLineStart = g_DialogState_candidate.pText;
    StartDialogPage();
}
