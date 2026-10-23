#include "conversation.h"
#include "dialog.h"
#include "dialog_inline.h"

// Continues with the next page of the line, the block's next line, or closes the box.
void AdvanceDialog(void)
{
    if (*g_DialogState.pText != 0)
        StartDialogPage();
    else if (++g_DialogState.wLineIndex < g_aDialogBlocks[g_DialogState.wBlockId].bLineCount)
        ShowDialogLine();
    else
        g_DialogState.bPhase = DialogPhaseSlideDown;
}
