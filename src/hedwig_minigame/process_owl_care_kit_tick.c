#include "types.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

void ProcessOwlCareKitTick(s32 nGrowCounters)
{
    u32 i;

    if (!(g_saveStateBlock.owlCareKit.bFlags & OwlCareKitFlagVisited))
        return;

    if (g_saveStateBlock.owlCareKit.wMailTimer != 0)
        g_saveStateBlock.owlCareKit.wMailTimer--;
    else if (++g_saveStateBlock.owlCareKit.wElapsedTicks > 149)
    {
        g_saveStateBlock.owlCareKit.wElapsedTicks = 0;
        if (nGrowCounters)
        {
            for (i = 0; i < 6; i++)
            {
                g_saveStateBlock.owlCareKit.abCareCounters[i]++;
                if (g_saveStateBlock.owlCareKit.abCareCounters[i] > 250)
                    g_saveStateBlock.owlCareKit.abCareCounters[i] = 250;
            }
        }
        UpdateOwlStatMeters(0);
    }

    if (g_saveStateBlock.dwOwlCareKitTicks < 0xFFFFFFFF)
        g_saveStateBlock.dwOwlCareKitTicks++;
}
