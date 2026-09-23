#include "types.h"
#include "audio.h"
#include "debug_menu.h"
#include "game_modes.h"
#include "input.h"
#include "minigame_menu.h"
#include "riddikulus.h"
#include "save.h"

void UpdateRiddikulusMinigame(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case RiddikulusStateIntro:
        if (--g_Riddikulus.dwCountdown == 0)
        {
            sub_08008C4C();
            g_Riddikulus.dwCountdown = 3;
            g_GameModeStackContext.dwModeState = RiddikulusStateAwaitInput;
        }
        break;
    case RiddikulusStateAwaitInput:
        if (--g_Riddikulus.dwCountdown == 0)
        {
            g_GameModeStackContext.dwModeState = RiddikulusStateInput;
            sub_08008404();
        }
        // fall through
    case RiddikulusStateInput:
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
    case RiddikulusStateResolve:
        if (sub_08008604())
            break;

        if (--g_Riddikulus.dwCountdown == 0)
            sub_08008698();
        break;
    case RiddikulusStateRoundEnd:
        if (--g_Riddikulus.dwCountdown == 0)
        {
            sub_08008CA8();
            if (g_Riddikulus.bUnk34 == 0)
            {
                sub_08008968();
            }
            else
            {
                sub_08008D4C();
                g_Riddikulus.pObject->dwFlags |= 0x82;
                g_Riddikulus.dwCountdown = 3;
                g_GameModeStackContext.dwModeState = RiddikulusStateIntro;
            }
        }
        break;
    case RiddikulusStateNextRound:
        if (sub_08008D80())
        {
            sub_08008CA8();
            g_Riddikulus.bUnk35++;
            sub_08008D4C();
            g_Riddikulus.pObject->dwFlags |= 0x82;
            g_Riddikulus.dwCountdown = 3;
            g_GameModeStackContext.dwModeState = RiddikulusStateIntro;
        }
        break;
    case RiddikulusStateResultsMenu:
        if (g_wKeysPressed & (KeyA | KeyStart))
        {
            if (g_Riddikulus.dwScore >
                g_saveManager.adwRiddikulusHighScores[g_GameModeStackContext.dwCurrentGameModeArg3])
                g_saveManager.adwRiddikulusHighScores[g_GameModeStackContext.dwCurrentGameModeArg3] =
                    g_Riddikulus.dwScore;

            PlaySoundById(1);
            switch (g_GameModeStackContext.dwModeScratchB)
            {
            case 0:
                PushGameMode_3(RiddikulusMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
                               g_GameModeStackContext.dwCurrentGameModeArg3);
                break;
            case 1:
                sub_08008E48();
                break;
            }
        }
        else if (StepWrappedSelectionVertical_candidate(&g_dwListMenuSelection, 0, 1, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    case RiddikulusStatePauseMenu:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            switch (g_GameModeStackContext.dwModeScratchB)
            {
            case 0:
                sub_08008DFC();
                break;
            case 1:
                PushGameMode_3(RiddikulusMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
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
        else if (StepWrappedSelectionVertical_candidate(&g_dwListMenuSelection, 0, 2, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    }
}
