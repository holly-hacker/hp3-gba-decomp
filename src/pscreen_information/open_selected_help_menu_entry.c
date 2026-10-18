#include "sound.h"
#include "pscreen_information.h"

void OpenSelectedHelpMenuEntry(void)
{
    if (g_HelpState.bPageKind == HelpPageMenu)
    {
        if (g_HelpState.aEntries[g_HelpState.bSelectedEntry].bAvailable)
        {
            g_HelpState.aPageStack[g_HelpState.bPageDepth].dwSelectedEntry = g_HelpState.bSelectedEntry;
            g_HelpState.bPageDepth++;
            PlaySoundById(1);
            g_GameModeStackContext.dwModeSubState = 0;
            g_HelpState.pPendingPage = g_HelpState.aEntries[g_HelpState.bSelectedEntry].pPage;
            g_GameModeStackContext.dwModeState = 3;
        }
        else
        {
            PlaySoundById(3);
        }
    }
}
