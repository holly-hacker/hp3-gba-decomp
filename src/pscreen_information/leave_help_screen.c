#include "screen_transitions.h"
#include "pscreen_information.h"

void LeaveHelpScreen(void)
{
    if (g_HelpState.bStandalone && g_HelpState.bPageDepth == 0)
    {
        PushGameMode_3(g_HelpState.dwExitMode, g_HelpState.dwExitArg1, g_HelpState.dwExitArg2,
                       g_HelpState.dwExitArg3);
        PlayScreenTransitionOutByIndex(0x3F, 2);
    }
    else
    {
        g_GameModeStackContext.dwModeSubState = 0;
        if (g_HelpState.bPageDepth == 0)
            SetAlphaBlendTargets(0x14, 1);
        g_GameModeStackContext.dwModeState = HelpScreenStateFadeOut;
        g_HelpState.pPendingPage = NULL;
    }
}
