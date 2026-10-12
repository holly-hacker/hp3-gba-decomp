#include "types.h"
#include "input.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "buckbeak_minigame.h"

void HandleBuckbeakMinigameResultsMenuSelect(void)
{
    u32 minSelection = 0;

    // Without time left there is nothing to resume.
    if (g_pBuckbeakMinigame->dwTimeLeft <= 0)
        minSelection = 1;

    if (g_wKeysPressed & KeyA)
    {
        PlaySoundById(1);

        switch ((s32)g_pBuckbeakMinigame->dwMenuSelection)
        {
        case 0:
            CloseBuckbeakMinigameResultsMenu();
            return;
        case 1:
            ResetBuckbeakMinigame();
            CloseBuckbeakMinigameResultsMenu();
            DrawBuckbeakMinigameScore();
            break;
        case 2:
            CloseBuckbeakMinigameResultsMenu();
            HandleBuckbeakMinigameExitSelect();
            break;
        }
    }

    if (g_pBuckbeakMinigame->dwTimeLeft > 0 && (g_wKeysPressed & (KeyB | KeyStart)))
    {
        PlaySoundById(2);
        CloseBuckbeakMinigameResultsMenu();
        g_GameModeStackContext.dwModeState = BuckbeakMinigameStateFlying;
        return;
    }

    if (StepCursorUpDown(&g_pBuckbeakMinigame->dwMenuSelection, minSelection, 2, 1, 0))
        PlaySoundById(0);
}
