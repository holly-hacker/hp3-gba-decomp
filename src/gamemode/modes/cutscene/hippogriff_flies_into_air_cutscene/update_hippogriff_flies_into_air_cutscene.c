#include "types.h"
#include "game_modes.h"
#include "hippogriff_flies_into_air_cutscene.h"

// dwStateTimer counts down from 0x12C; at 0xC8 the hippogriff starts shrinking, at 0 the
// HippogriffTookToAirCutscene follows.
void UpdateHippogriffFliesIntoAirCutscene(void)
{
    g_pHippogriffFliesIntoAirObject->dwStateTimer--;
    if (g_pHippogriffFliesIntoAirObject->dwStateTimer == 0xC8)
        StartObjectAffineScaleTween(g_pHippogriffFliesIntoAirObject, 0x1999, 0x1999, 0xFA);

    if (g_pHippogriffFliesIntoAirObject->dwStateTimer == 0)
        PushGameMode(HippogriffTookToAirCutscene);
}
