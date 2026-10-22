#include "sound.h"
#include "pscreen_information.h"

void TurnToPrevHelpPage(void)
{
    if (g_HelpState.pPrevPage != NULL)
    {
        PlaySoundById(0);
        g_GameModeStackContext.dwModeSubState = 0;
        g_HelpState.pPendingPage = g_HelpState.pPrevPage;
        g_GameModeStackContext.dwModeState = HelpScreenStateFadeOut;
    }
}
