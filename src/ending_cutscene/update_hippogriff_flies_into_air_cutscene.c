#include "types.h"
#include "modes.h"
#include "ending_cutscene.h"

// dwStateTimer counts down from 0x12C; at 0xC8 the hippogriff starts shrinking, at 0 the
// HippogriffTookToAirCutscene follows.
void UpdateHippogriffFliesIntoAirCutscene(void)
{
    g_pHippogriffFliesIntoAirActor->dwStateTimer--;
    if (g_pHippogriffFliesIntoAirActor->dwStateTimer == 0xC8)
        StartActorAffineScaleTween(g_pHippogriffFliesIntoAirActor, 0x1999, 0x1999, 0xFA);

    if (g_pHippogriffFliesIntoAirActor->dwStateTimer == 0)
        PushGameMode(HippogriffTookToAirCutscene);
}
