#include "types.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

void ResetOwlCareKit(void)
{
    u32 i;

    for (i = 0; i < 6; i++)
        g_saveStateBlock.owlCareKit.abCareCounters[i] = 125;
    UpdateOwlStatMeters(1);
    g_saveStateBlock.owlCareKit.bFlags |= OwlCareKitFlagVisited;
}
