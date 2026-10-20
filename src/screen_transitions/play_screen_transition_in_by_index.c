#include "types.h"
#include "main.h"
#include "modes.h"
#include "screen_transitions.h"

void PlayScreenTransitionInByIndex(u16 blendArg, u32 transitionIndex)
{
    g_dwGameModeFlags |= GameModeFlagScreenTransition;
    g_apfnScreenTransitionsIn[transitionIndex](blendArg);
    g_dwGameModeFlags &= ~GameModeFlagScreenTransition;
}
