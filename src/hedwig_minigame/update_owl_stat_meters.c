#include "types.h"
#include "hw/bios.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

const u8 g_aabOwlStatMeterWeights[3][6] = {
    { 2, 0, 4, 3, 0, 5 },
    { 5, 2, 3, 0, 6, 0 },
    { 0, 5, 0, 4, 1, 2 },
};

// Each meter targets 250 minus the weighted mean of the care counters; it
// moves one step toward it per call, or jumps to it when snap is set.
void UpdateOwlStatMeters(s32 snap)
{
    s32 meter;
    s32 i;
    s32 weighted;
    s32 totalWeight;
    s32 aTargets[3];

    for (meter = 0; meter < 3; meter++)
    {
        weighted = 0;
        totalWeight = 0;
        for (i = 0; i < 6; i++)
        {
            weighted += g_aabOwlStatMeterWeights[meter][i] * g_saveStateBlock.owlCareKit.abCareCounters[i];
            totalWeight += g_aabOwlStatMeterWeights[meter][i];
        }
        aTargets[meter] = 250 - bios_Div(weighted, totalWeight);

        if (snap)
            g_saveStateBlock.owlCareKit.abStatMeters[meter] = aTargets[meter];
        else if (aTargets[meter] > g_saveStateBlock.owlCareKit.abStatMeters[meter])
            g_saveStateBlock.owlCareKit.abStatMeters[meter]++;
        else if (aTargets[meter] < g_saveStateBlock.owlCareKit.abStatMeters[meter])
            g_saveStateBlock.owlCareKit.abStatMeters[meter]--;
    }
}
