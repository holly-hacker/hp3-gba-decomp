#include "types.h"
#include "modes.h"
#include "screen_transitions.h"
#include "minigame_menu.h"

void TickMinigameSwitchFadeIn(void)
{
    g_GameModeStackContext.dwModeTimer--;
    SetAlphaBlendCoefficients(16 - g_GameModeStackContext.dwModeTimer * 4, g_GameModeStackContext.dwModeTimer * 4);
    if (g_GameModeStackContext.dwModeTimer == 0)
    {
        SetAlphaBlendTargets(0, 0);
        g_GameModeStackContext.dwModeState = 0;
    }
}
