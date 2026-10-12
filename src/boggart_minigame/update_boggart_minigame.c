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
            sub_08008C4C();
            g_BoggartMinigame.dwCountdown = 3;
            g_GameModeStackContext.dwModeState = BoggartMinigameStateAwaitInput;
        }
        break;
    case BoggartMinigameStateAwaitInput:
        if (--g_BoggartMinigame.dwCountdown == 0)
        {
            g_GameModeStackContext.dwModeState = BoggartMinigameStateInput;
            sub_08008404();
        }
        // fall through
    case BoggartMinigameStateInput:
        if (sub_08008604())
            break;
        if (g_wKeysPressed & KeyLeft)
            sub_08008B2C(0);
        else if (g_wKeysPressed & KeyRight)
            sub_08008B2C(2);
        else if (g_wKeysPressed & KeyDown)
            sub_08008B2C(3);
        else if (g_wKeysPressed & KeyUp)
            sub_08008B2C(1);
        else if (g_wKeysPressed & KeyStart)
            sub_08008A18();
        break;
    case BoggartMinigameStateResolve:
        if (sub_08008604())
            break;

        if (--g_BoggartMinigame.dwCountdown == 0)
            sub_08008698();
        break;
    case BoggartMinigameStateRoundEnd:
        if (--g_BoggartMinigame.dwCountdown == 0)
        {
            sub_08008CA8();
            if (g_BoggartMinigame.bUnk34 == 0)
            {
                sub_08008968();
            }
            else
            {
                sub_08008D4C();
                g_BoggartMinigame.pActor->dwFlags |= 0x82;
                g_BoggartMinigame.dwCountdown = 3;
                g_GameModeStackContext.dwModeState = BoggartMinigameStateIntro;
            }
        }
        break;
    case BoggartMinigameStateNextRound:
        if (sub_08008D80())
        {
            sub_08008CA8();
            g_BoggartMinigame.bUnk35++;
            sub_08008D4C();
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
                sub_08008E48();
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
                sub_08008DFC();
                break;
            case 1:
                PushGameMode_3(BoggartMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
                               g_GameModeStackContext.dwCurrentGameModeArg3);
                break;
            case 2:
                sub_08008E48();
                break;
            }
        }
        else if (g_wKeysPressed & (KeyB | KeyStart))
        {
            PlaySoundById(2);
            sub_08008DFC();
        }
        else if (StepCursorUpDown(&g_dwListMenuSelection, 0, 2, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    }
}
