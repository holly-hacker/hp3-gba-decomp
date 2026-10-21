#include "types.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

void UpdateOwlStatMeterBars(void)
{
    u32 i;

    for (i = 0; i < 3; i++)
    {
        if (g_OwlCareKitScreen.abShownMeters[i] != g_saveStateBlock.owlCareKit.abStatMeters[i])
        {
            g_OwlCareKitScreen.abShownMeters[i] = g_saveStateBlock.owlCareKit.abStatMeters[i];
            DrawOwlStatMeterBar(i, g_OwlCareKitScreen.abShownMeters[i]);
            g_OwlCareKitScreen.bMetersRedrawn = 1;
        }
    }
}
