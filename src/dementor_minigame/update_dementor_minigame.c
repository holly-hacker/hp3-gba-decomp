#include "types.h"
#include "sound.h"
#include "minigame_menu.h"
#include "modes.h"
#include "dementor_minigame.h"
#include "input.h"

void UpdateDementorMinigame(void)
{
    if (g_DementorMinigame.dwSpellTimer != 0 && --g_DementorMinigame.dwSpellTimer == 0)
        ShowDementorMinigameSpell(g_DementorMinigame.dwSpellDirection);

    if (g_DementorMinigame.dwSpellHideTimer != 0 && --g_DementorMinigame.dwSpellHideTimer == 0)
        g_DementorMinigame.pSpellActor->dwFlags &= ~ActorFlagVisible;

    if (g_DementorMinigame.dwDamageHideTimer != 0 && --g_DementorMinigame.dwDamageHideTimer == 0)
        g_DementorMinigame.pDamageActor->dwFlags &= ~ActorFlagVisible;

    switch (g_GameModeStackContext.dwModeState)
    {
    case DementorMinigameStatePlaying:
        if (g_wKeysPressed & KeyStart)
        {
            ShowDementorMinigamePauseMenu();
            break;
        }

        UpdateDementorMinigameDementors();
        if (g_wKeysPressed & KeyRight)
            CastDementorMinigameSpell(0);
        else if (g_wKeysPressed & KeyLeft)
            CastDementorMinigameSpell(2);
        else if (g_wKeysPressed & KeyUp)
            CastDementorMinigameSpell(3);
        else if (g_wKeysPressed & KeyDown)
            CastDementorMinigameSpell(1);

        if (g_DementorMinigame.bLives == 0)
            ShowDementorMinigameResultsMenu();
        else
            UpdateDementorMinigameLaunches();
        break;
    case DementorMinigameStateResultsMenu:
        if (g_wKeysPressed & (KeyA | KeyStart))
        {
            PlaySoundById(1);
            switch (g_GameModeStackContext.dwModeScratchB)
            {
            case 0:
                PushGameMode_3(DementorMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
                               g_GameModeStackContext.dwCurrentGameModeArg3);
                break;
            case 1:
                LeaveDementorMinigame();
                break;
            }
        }
        else if (StepCursorUpDown(&g_GameModeStackContext.dwModeScratchB, 0, 1, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    case DementorMinigameStatePauseMenu:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            switch (g_GameModeStackContext.dwModeScratchB)
            {
            case 0:
                ResumeDementorMinigame();
                break;
            case 1:
                PushGameMode_3(DementorMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
                               g_GameModeStackContext.dwCurrentGameModeArg3);
                break;
            case 2:
                LeaveDementorMinigame();
                break;
            }
        }
        else if (g_wKeysPressed & (KeyB | KeyStart))
        {
            PlaySoundById(2);
            ResumeDementorMinigame();
        }
        else if (StepCursorUpDown(&g_GameModeStackContext.dwModeScratchB, 0, 2, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    }
}
