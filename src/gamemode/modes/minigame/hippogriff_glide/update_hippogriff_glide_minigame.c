#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "minigame/hippogriff_glide.h"
#include "hw/input.h"
#include "game/save.h"

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
            g_saveManager.options.adwHippogriffGlideHighScores[g_GameModeStackContext.dwCurrentGameModeArg3])
            g_saveManager.options.adwHippogriffGlideHighScores[g_GameModeStackContext.dwCurrentGameModeArg3] =
                pState->dwScore;

        InitializeHippogriffGlideResultsMenu();
        break;
    }
}
