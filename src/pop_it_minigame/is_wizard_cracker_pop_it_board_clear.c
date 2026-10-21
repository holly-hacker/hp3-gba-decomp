#include "types.h"
#include "pop_it_minigame.h"

u32 IsWizardCrackerPopItBoardClear(void)
{
    s32 i;

    for (i = 0; i < g_pWizardCrackerPopIt->nColumnCount; i++)
        if (g_pWizardCrackerPopIt->abColumnHeights[i] > 0)
            return 0;

    return 1;
}
