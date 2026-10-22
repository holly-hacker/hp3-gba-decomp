#include "sound.h"
#include "pscreen_information.h"

void TurnToNextHelpPage(void)
{
    if (g_HelpState.pNextPage != NULL)
    {
        PlaySoundById(0);
        g_GameModeStackContext.dwModeSubState = 0;
        g_HelpState.pPendingPage = g_HelpState.pNextPage;
        g_GameModeStackContext.dwModeState = HelpScreenStateFadeOut;
    }
}
