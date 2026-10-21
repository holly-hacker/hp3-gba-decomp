#include "types.h"
#include "modes.h"
#include "pop_it_minigame.h"

// Awards 125 << difficulty for three crackers left, doubled for each fewer.
void AddWizardCrackerPopItClearBonus(void)
{
    s32 remaining;
    s32 i;
    u32 bonus;
    u32 score;

    remaining = 0;
    for (i = 0; i < g_pWizardCrackerPopIt->nColumnCount; i++)
        remaining += g_pWizardCrackerPopIt->abColumnHeights[i];

    if (remaining <= 3)
    {
        bonus = 125 << g_GameModeStackContext.dwCurrentGameModeArg3;
        for (i = 0; i < 3 - remaining; i++)
            bonus <<= 1;

        score = g_pWizardCrackerPopIt->dwScore + bonus;
        if (score > g_pWizardCrackerPopIt->dwScore)
            g_pWizardCrackerPopIt->dwScore = score;
    }
}
