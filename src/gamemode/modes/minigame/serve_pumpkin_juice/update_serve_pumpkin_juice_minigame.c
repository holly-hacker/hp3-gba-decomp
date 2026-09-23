#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "input.h"
#include "minigame_menu.h"
#include "mt19937.h"
#include "serve_pumpkin_juice.h"
#include "text.h"

void UpdateUnusedServePumpkinJuiceMinigame(void)
{
    s32 found = 0;
    s32 chosen = -1;
    u32 i;

    switch (g_GameModeStackContext.dwModeState)
    {
    case ServePumpkinJuiceStatePlaying:
        if (g_wKeysPressed & KeyStart)
        {
            g_ServePumpkinJuice.dwMenuSelection = 0;
            sub_08035330();
            g_GameModeStackContext.dwModeState = ServePumpkinJuiceStatePauseMenu;
        }

        for (i = 0; i < 3; i++)
        {
            if (g_ServePumpkinJuice.adwUnk20[i] > 0)
                found = 1;
            else if (chosen == -1 || Mt19937RandRange(0, 1) == 0)
                chosen = i;
        }

        if (found == 0 || (g_wKeysPressed & KeyL))
        {
            g_ServePumpkinJuice.dwMenuSelection = 0;
            g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateRoundOver;
            g_ServePumpkinJuice.dwScore +=
                ((2 << g_GameModeStackContext.dwCurrentGameModeArg3) + g_ServePumpkinJuice.dwRound + 1) * 100;
            sub_08035418();
        }
        else if (chosen != -1)
        {
            if (Mt19937RandRange(0, 1000) <= 4)
            {
                i = 0;
                while (i < Mt19937RandRange(0, g_ServePumpkinJuice.dwRound) + g_GameModeStackContext.dwCurrentGameModeArg3)
                {
                    u32 value = sub_08035474();

                    i++;
                    sub_08034F20(chosen, value, i);
                }
            }
        }

        if (g_ServePumpkinJuice.dwUnk0 != 0)
            sub_08035418();

        sub_0803518C();
        break;
    case ServePumpkinJuiceStateNextRound:
        g_ServePumpkinJuice.dwRound++;
        sub_0803526C();
        g_ServePumpkinJuice.dwMenuSelection = 0;
        sub_08035330();
        DrawStringAligned(g_ServePumpkinJuice.dwTileCursor, 0x78, 0x2D, g_ServePumpkinJuicePauseText, 1);
        g_GameModeStackContext.dwModeState = ServePumpkinJuiceStatePauseMenu;
        break;
    case ServePumpkinJuiceStatePauseMenu:
        if (g_wKeysPressed & KeyA)
        {
            switch ((s32)g_ServePumpkinJuice.dwMenuSelection)
            {
            case 0:
                sub_080075C0(3, 0, 5, 0x1E, 9, 0);
                g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateWaitInput;
                break;
            case 1:
                sub_080075C0(3, 0, 5, 0x1E, 9, 0);
                sub_0803539C();
                break;
            case 2:
                PushGameMode_2(MinigameDifficultySelect, 6, g_GameModeStackContext.dwCurrentGameModeArg2);
                break;
            }
        }

        if (g_wKeysPressed & KeyB)
        {
            sub_080075C0(3, 0, 5, 0x1E, 9, 0);
            g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateWaitInput;
        }

        if (StepWrappedSelectionVertical_candidate(&g_ServePumpkinJuice.dwMenuSelection, 0, 2, 1, 0))
            sub_08035330();
        break;
    case ServePumpkinJuiceStateWaitInput:
        if (g_wKeysPressed != 0 || g_wKeysHeld == 0)
            g_GameModeStackContext.dwModeState = ServePumpkinJuiceStatePlaying;
        break;
    case ServePumpkinJuiceStateResults:
        DrawStringAligned(g_ServePumpkinJuice.dwTileCursor, 0x78, 0x2D, g_ServePumpkinJuiceResultsText, 1);
        if (g_wKeysPressed & (KeyA | KeyB))
            PushGameMode_2(MinigameDifficultySelect, 6, g_GameModeStackContext.dwCurrentGameModeArg2);
        break;
    case ServePumpkinJuiceStateRoundOver:
        sub_0803518C();
        break;
    }
}
