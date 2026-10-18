#pragma once

#include "modes.h"
#include "screen_transitions.h"

// Starts blending the menu over the screen below at the blend level in dwModeSubState (0 shows
// the menu, 0x10 the screen below); the in-game menu blends with a different layer set than
// the screens it opens.
static inline void StartMenuFade(void)
{
    if (g_GameModeStackContext.dwCurrentGameMode == InGameMenu
        || g_GameModeStackContext.dwCurrentGameMode == InGameMenuFadeIn)
        SetAlphaBlendTargets(0x16, 1);
    else
        SetAlphaBlendTargets(0x14, 3);

    SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                              g_GameModeStackContext.dwModeSubState);
}
