#include "types.h"
#include "modes.h"
#include "screen_transitions.h"
#include "minigame_menu.h"

// Returns whether the fade out has finished.
u32 TickMinigameSwitchFadeOut(void)
{
    g_GameModeStackContext.dwModeTimer--;
    SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeTimer * 4, 16 - g_GameModeStackContext.dwModeTimer * 4);
    return g_GameModeStackContext.dwModeTimer == 0;
}
