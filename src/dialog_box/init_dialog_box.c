#include "mem.h"
#include "dialog.h"
#include "dialog_box.h"

void InitDialogBox(void)
{
    if (g_DialogState_candidate.wRevealStep == 0)
        g_DialogState_candidate.wRevealStep = 1;
    g_DialogState_candidate.dwState = 0;
    g_pDialogMacroExpandBuffer = AllocBlock(DIALOG_MACRO_EXPAND_BUFFER_SIZE);
}
