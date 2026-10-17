#include "types.h"
#include "sound.h"
#include "modes.h"
#include "buckbeak_minigame.h"
#include "input.h"
#include "save.h"

void UpdateBuckbeakMinigame(void)
{
    BuckbeakMinigameState *pState;

    switch (g_GameModeStackContext.dwModeState)
    {
    case BuckbeakMinigameStateFlying:
        if (g_wKeysPressed & KeyStart)
        {
            PlaySoundById(1);
            InitializeBuckbeakMinigameResultsMenu();
        }
        else
            ProcessBuckbeakMinigameFrame();
        break;
    case BuckbeakMinigameStateResults:
        HandleBuckbeakMinigameResultsMenuSelect();
        break;
    case BuckbeakMinigameStateExitSelect:
        HandleBuckbeakMinigameExitSelect();
        break;
    case BuckbeakMinigameStateFinished:
        pState = g_pBuckbeakMinigame;
        if (pState->dwScore >
            g_saveManager.options.aadwHighScores[HighScoreBuckbeak][g_GameModeStackContext.dwCurrentGameModeArg3])
            g_saveManager.options.aadwHighScores[HighScoreBuckbeak][g_GameModeStackContext.dwCurrentGameModeArg3] =
                pState->dwScore;

        InitializeBuckbeakMinigameResultsMenu();
        break;
    }
}
