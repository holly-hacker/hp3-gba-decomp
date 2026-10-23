#include "font.h"
#include "conversation.h"
#include "dialog.h"
#include "dialog_box.h"
#include "dialog_inline.h"

// Shows line wLineIndex of block wBlockId with its speaker's portrait.
void ShowDialogLine(void)
{
    g_dwDialogTextId = g_aDialogBlocks[g_DialogState.wBlockId].pTextIds[g_DialogState.wLineIndex];
    g_dwDialogPortrait = g_aDialogTextInfo[g_dwDialogTextId].dwPortrait;
    SetDialogPortrait(g_pDialogPortraitActor);
    g_DialogState.pText = GetDialogLineText(g_dwDialogTextId);
    g_DialogState.pText = ExpandTextMacros(g_pDialogMacroExpandBuffer, g_DialogState.pText,
                                                     DIALOG_MACRO_EXPAND_BUFFER_SIZE);
    g_DialogState.pLineStart = g_DialogState.pText;
    StartDialogPage();
}
