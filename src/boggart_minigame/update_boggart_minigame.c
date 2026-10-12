#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "input.h"
#include "menu/minigame_menu.h"
#include "boggart_minigame.h"
#include "game/save.h"

void UpdateBoggartMinigame(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case BoggartMinigameStateIntro:
        if (--g_BoggartMinigame.dwCountdown == 0)
        {
            SpawnBoggartMinigameBoggart();
            g_BoggartMinigame.dwCountdown = 3;
            g_GameModeStackContext.dwModeState = BoggartMinigameStateAwaitInput;
        }
        break;
    case BoggartMinigameStateAwaitInput:
        if (--g_BoggartMinigame.dwCountdown == 0)
        {
            g_GameModeStackContext.dwModeState = BoggartMinigameStateInput;
            StartBoggartMinigameBoggartMotion();
        }
        // fall through
    case BoggartMinigameStateInput:
        if (CheckBoggartMinigameBoggartReachedStudent())
            break;
        if (g_wKeysPressed & KeyLeft)
            StartBoggartMinigameCast(0);
        else if (g_wKeysPressed & KeyRight)
            StartBoggartMinigameCast(2);
        else if (g_wKeysPressed & KeyDown)
            StartBoggartMinigameCast(3);
        else if (g_wKeysPressed & KeyUp)
            StartBoggartMinigameCast(1);
        else if (g_wKeysPressed & KeyStart)
            ShowBoggartMinigamePauseMenu();
        break;
    case BoggartMinigameStateResolve:
        if (CheckBoggartMinigameBoggartReachedStudent())
            break;

        if (--g_BoggartMinigame.dwCountdown == 0)
            ResolveBoggartMinigameCast();
        break;
    case BoggartMinigameStateRoundEnd:
        if (--g_BoggartMinigame.dwCountdown == 0)
        {
            ClearBoggartMinigameMessage();
            if (g_BoggartMinigame.bLives == 0)
            {
                ShowBoggartMinigameResultsMenu();
            }
            else
            {
                ResetBoggartMinigameActors();
                g_BoggartMinigame.pActor->dwFlags |= 0x82;
                g_BoggartMinigame.dwCountdown = 3;
                g_GameModeStackContext.dwModeState = BoggartMinigameStateIntro;
            }
        }
        break;
    case BoggartMinigameStateNextRound:
        if (HasBoggartMinigameBoggartReturnedToCenter())
        {
            ClearBoggartMinigameMessage();
            g_BoggartMinigame.bRound++;
            ResetBoggartMinigameActors();
            g_BoggartMinigame.pActor->dwFlags |= 0x82;
            g_BoggartMinigame.dwCountdown = 3;
            g_GameModeStackContext.dwModeState = BoggartMinigameStateIntro;
        }
        break;
    case BoggartMinigameStateResultsMenu:
        if (g_wKeysPressed & (KeyA | KeyStart))
        {
            if (g_BoggartMinigame.dwScore >
                g_saveManager.options.aadwHighScores[HighScoreBoggart][g_GameModeStackContext.dwCurrentGameModeArg3])
                g_saveManager.options.aadwHighScores[HighScoreBoggart][g_GameModeStackContext.dwCurrentGameModeArg3] =
                    g_BoggartMinigame.dwScore;

            PlaySoundById(1);
            switch (g_GameModeStackContext.dwModeScratchB)
            {
            case 0:
                PushGameMode_3(BoggartMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
                               g_GameModeStackContext.dwCurrentGameModeArg3);
                break;
            case 1:
                LeaveBoggartMinigame();
                break;
            }
        }
        else if (StepCursorUpDown(&g_dwListMenuSelection, 0, 1, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    case BoggartMinigameStatePauseMenu:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            switch (g_GameModeStackContext.dwModeScratchB)
            {
            case 0:
                ResumeBoggartMinigame();
                break;
            case 1:
                PushGameMode_3(BoggartMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
                               g_GameModeStackContext.dwCurrentGameModeArg3);
                break;
            case 2:
                LeaveBoggartMinigame();
                break;
            }
        }
        else if (g_wKeysPressed & (KeyB | KeyStart))
        {
            PlaySoundById(2);
            ResumeBoggartMinigame();
        }
        else if (StepCursorUpDown(&g_dwListMenuSelection, 0, 2, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    }
}
