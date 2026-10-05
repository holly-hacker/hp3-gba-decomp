#include "types.h"
#include "hw/mem.h"
#include "menu/dialog.h"

void InitDialogBox(void)
{
    if (g_DialogState_candidate.wRevealStep_candidate == 0)
        g_DialogState_candidate.wRevealStep_candidate = 1;
    g_DialogState_candidate.dwState = 0;
    g_pDialogMacroExpandBuffer = AllocBlock(DIALOG_MACRO_EXPAND_BUFFER_SIZE);
}
