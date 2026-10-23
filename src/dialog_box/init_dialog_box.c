#include "mem.h"
#include "dialog.h"
#include "dialog_box.h"

void InitDialogBox(void)
{
    if (g_DialogState.wRevealStep == 0)
        g_DialogState.wRevealStep = 1;
    g_DialogState.dwState = 0;
    g_pDialogMacroExpandBuffer = AllocBlock(DIALOG_MACRO_EXPAND_BUFFER_SIZE);
}
