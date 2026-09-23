#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "hippogriff_glide.h"
#include "input.h"
#include "save.h"

void UpdateHippogriffGlideMinigame(void)
{
    HippogriffGlideState *pState;

    switch (g_GameModeStackContext.dwModeState)
    {
    case HippogriffGlideStateFlying:
        if (g_wKeysPressed & KeyStart)
        {
            PlaySoundById(1);
            InitializeHippogriffGlideResultsMenu();
        }
        else
            ProcessHippogriffGlideMinigameFrame();
        break;
    case HippogriffGlideStateResults:
        HandleHippogriffGlideResultsMenuSelect();
        break;
    case HippogriffGlideStateExitSelect:
        HandleHippogriffGlideExitSelect();
        break;
    case HippogriffGlideStateFinished:
        pState = g_pHippogriffGlide;
        if (pState->dwScore >
            g_saveManager.adwHippogriffGlideHighScores[g_GameModeStackContext.dwCurrentGameModeArg3])
            g_saveManager.adwHippogriffGlideHighScores[g_GameModeStackContext.dwCurrentGameModeArg3] =
                pState->dwScore;

        InitializeHippogriffGlideResultsMenu();
        break;
    }
}
