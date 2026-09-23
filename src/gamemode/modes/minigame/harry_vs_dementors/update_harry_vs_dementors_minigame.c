#include "types.h"
#include "audio.h"
#include "debug_menu.h"
#include "game_modes.h"
#include "harry_vs_dementors.h"
#include "input.h"

void UpdateHarryVsDementorsMinigame(void)
{
    if (g_HarryVsDementors.dwEventTimer60 != 0 && --g_HarryVsDementors.dwEventTimer60 == 0)
        sub_0801ED48(g_HarryVsDementors.dwEventArg64);

    if (g_HarryVsDementors.dwHideTimer5C != 0 && --g_HarryVsDementors.dwHideTimer5C == 0)
        g_HarryVsDementors.pObject18->dwFlags &= ~ObjectFlagVisible;

    if (g_HarryVsDementors.dwHideTimer68 != 0 && --g_HarryVsDementors.dwHideTimer68 == 0)
        g_HarryVsDementors.pObject1C->dwFlags &= ~ObjectFlagVisible;

    switch (g_GameModeStackContext.dwModeState)
    {
    case HarryVsDementorsStatePlaying:
        if (g_wKeysPressed & KeyStart)
        {
            sub_0801E5F4();
            break;
        }

        sub_0801E8CC();
        if (g_wKeysPressed & KeyRight)
            sub_0801EAF8(0);
        else if (g_wKeysPressed & KeyLeft)
            sub_0801EAF8(2);
        else if (g_wKeysPressed & KeyUp)
            sub_0801EAF8(3);
        else if (g_wKeysPressed & KeyDown)
            sub_0801EAF8(1);

        if (g_HarryVsDementors.bUnk4C == 0)
            sub_0801E564();
        else
            sub_0801E6A0();
        break;
    case HarryVsDementorsStateResultsMenu:
        if (g_wKeysPressed & (KeyA | KeyStart))
        {
            PlaySoundById(1);
            switch (g_GameModeStackContext.dwModeScratchB)
            {
            case 0:
                PushGameMode_3(HarryVsDementorsMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
                               g_GameModeStackContext.dwCurrentGameModeArg3);
                break;
            case 1:
                sub_0801EE64();
                break;
            }
        }
        else if (StepWrappedSelectionVertical_candidate(&g_GameModeStackContext.dwModeScratchB, 0, 1, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    case HarryVsDementorsStatePauseMenu:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            switch (g_GameModeStackContext.dwModeScratchB)
            {
            case 0:
                sub_0801EFF4();
                break;
            case 1:
                PushGameMode_3(HarryVsDementorsMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
                               g_GameModeStackContext.dwCurrentGameModeArg3);
                break;
            case 2:
                sub_0801EE64();
                break;
            }
        }
        else if (g_wKeysPressed & (KeyB | KeyStart))
        {
            PlaySoundById(2);
            sub_0801EFF4();
        }
        else if (StepWrappedSelectionVertical_candidate(&g_GameModeStackContext.dwModeScratchB, 0, 2, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    }
}
