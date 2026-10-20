#include "types.h"
#include "main.h"
#include "modes.h"
#include "screen_transitions.h"

void PlayScreenTransitionOutByIndex(u16 blendArg, u32 transitionIndex)
{
    g_dwGameModeFlags |= GameModeFlagScreenTransition | GameModeFlagScreenTransitionOut;
    g_apfnScreenTransitionsOut[transitionIndex](blendArg);
    g_dwGameModeFlags &= ~(GameModeFlagScreenTransition | GameModeFlagScreenTransitionOut);
}
