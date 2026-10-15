#include "types.h"
#include "graphics/audio.h"
#include "menu/minigame_menu.h"
#include "game/game_modes.h"
#include "dementor_minigame.h"
#include "input.h"

void UpdateDementorMinigame(void)
{
    if (g_DementorMinigame.dwEventTimer60 != 0 && --g_DementorMinigame.dwEventTimer60 == 0)
        sub_0801ED48(g_DementorMinigame.dwEventArg64);

    if (g_DementorMinigame.dwHideTimer5C != 0 && --g_DementorMinigame.dwHideTimer5C == 0)
        g_DementorMinigame.pActor18->dwFlags &= ~ActorFlagVisible;

    if (g_DementorMinigame.dwHideTimer68 != 0 && --g_DementorMinigame.dwHideTimer68 == 0)
        g_DementorMinigame.pActor1C->dwFlags &= ~ActorFlagVisible;

    switch (g_GameModeStackContext.dwModeState)
    {
    case DementorMinigameStatePlaying:
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

        if (g_DementorMinigame.bUnk4C == 0)
            sub_0801E564();
        else
            sub_0801E6A0();
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
                sub_0801EE64();
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
                sub_0801EFF4();
                break;
            case 1:
                PushGameMode_3(DementorMinigame, 6, g_GameModeStackContext.dwCurrentGameModeArg2,
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
        else if (StepCursorUpDown(&g_GameModeStackContext.dwModeScratchB, 0, 2, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    }
}
