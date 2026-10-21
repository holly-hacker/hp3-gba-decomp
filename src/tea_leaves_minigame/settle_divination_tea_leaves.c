#include "types.h"
#include "tea_leaves_minigame.h"
#include "screen_transitions.h"

void SettleDivinationTeaLeaves(void)
{
    SlowDivinationTeaLeaves();

    if ((g_DivinationTea.dwFrame & 7) == 0)
    {
        if (--g_DivinationTea.nBlendEvb < 0)
        {
            g_DivinationTea.nBlendEvb = 0;
            g_DivinationTea.dwSettled = 1;
        }

        if (++g_DivinationTea.nBlendEva > 0x10)
        {
            g_DivinationTea.nBlendEva = 0x10;
            g_DivinationTea.dwSettled = 1;
        }

        SetAlphaBlendTargets(2, 4);
        SetAlphaBlendCoefficients(g_DivinationTea.nBlendEva, g_DivinationTea.nBlendEvb);
    }
}
