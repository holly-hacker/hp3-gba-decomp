#include "types.h"
#include "pop_it_minigame.h"

void ResetWizardCrackerPopItSettle(void)
{
    s32 i;

    for (i = 0; i < WIZARD_CRACKER_POP_IT_COLUMNS; i++)
        g_pWizardCrackerPopIt->abColumnGaps[i] = 0;
    g_pWizardCrackerPopIt->bSettleTimer = 0;
    g_pWizardCrackerPopIt->bSettleRow = 0;
}
