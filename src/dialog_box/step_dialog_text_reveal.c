#include "dialog.h"
#include "dialog_box.h"

void StepDialogTextReveal(void)
{
    if (g_dwDialogPageFull == 0)
    {
        g_DialogState.wRevealCount += g_DialogState.wRevealStep;
        g_dwDialogPageFull = DrawDialogTextLine(g_DialogState.wRevealCount);
    }
}
