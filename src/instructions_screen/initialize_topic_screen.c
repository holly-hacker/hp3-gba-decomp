#include "types.h"
#include "instructions_screen.h"
#include "battle/battle.h"
#include "modes.h"
#include "pscreen_information.h"
#include "combat.h"

// Argument 2 of the pushed mode selects the topic: the minigame whose instructions to show,
// and the mode to return to.
void InitializeTopicScreen(void)
{
    switch (g_GameModeStackContext.dwCurrentGameModeArg2)
    {
    case 0:
        StartHelpScreen(g_aHelpWizardCrackerPopIt, 1);
        SetHelpExitMode(WizardCrackerPopItMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 1:
        StartHelpScreen(g_aHelpBuckbeakMinigame, 1);
        SetHelpExitMode(BuckbeakMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 2:
        StartHelpScreen(g_aHelpBoggart, 1);
        SetHelpExitMode(BoggartMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 3:
        StartHelpScreen(g_aHelpTeaLeafDivination, 1);
        SetHelpExitMode(DivinationTeaMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 4:
        StartHelpScreen(g_aHelpDementors, 1);
        SetHelpExitMode(DementorMinigame, 6, 0, g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    case 6:
        StartHelpScreen(g_aHelpMenuMain, 1);
        SetHelpExitMode(Battle, g_pFightState->abBattleResumeArgs_candidate[0],
                     g_pFightState->abBattleResumeArgs_candidate[1],
                     g_pFightState->abBattleResumeArgs_candidate[2]);
        break;
    }
}
