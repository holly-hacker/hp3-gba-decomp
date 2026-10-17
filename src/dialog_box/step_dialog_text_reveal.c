#include "dialog.h"
#include "dialog_box.h"

void StepDialogTextReveal(void)
{
    if (g_dwDialogPageFull == 0)
    {
        g_DialogState_candidate.wRevealCount += g_DialogState_candidate.wRevealStep;
        g_dwDialogPageFull = DrawDialogTextLine(g_DialogState_candidate.wRevealCount);
    }
}
