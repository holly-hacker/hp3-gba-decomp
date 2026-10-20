#include "types.h"
#include "background.h"
#include "modes.h"
#include "input.h"
#include "random.h"
#include "pouring_minigame.h"
#include "font.h"

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
            DrawServePumpkinJuicePauseMenu();
            g_GameModeStackContext.dwModeState = ServePumpkinJuiceStatePauseMenu;
        }

        for (i = 0; i < ARRAY_COUNT(g_ServePumpkinJuice.adwCustomerCount); i++)
        {
            if (g_ServePumpkinJuice.adwCustomerCount[i] > 0)
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
            DrawServePumpkinJuiceScore();
        }
        else if (chosen != -1)
        {
            if (Mt19937RandRange(0, 1000) <= 4)
            {
                i = 0;
                while (i < Mt19937RandRange(0, g_ServePumpkinJuice.dwRound) + g_GameModeStackContext.dwCurrentGameModeArg3)
                {
                    u32 type = PickServePumpkinJuiceCustomerType();

                    i++;
                    SpawnServePumpkinJuiceCustomer(chosen, type, i);
                }
            }
        }

        if (g_ServePumpkinJuice.dwScoreChanged != 0)
            DrawServePumpkinJuiceScore();

        DrawServePumpkinJuiceTaps();
        break;
    case ServePumpkinJuiceStateNextRound:
        g_ServePumpkinJuice.dwRound++;
        SpawnServePumpkinJuiceCustomers();
        g_ServePumpkinJuice.dwMenuSelection = 0;
        DrawServePumpkinJuicePauseMenu();
        DrawStringAligned(g_ServePumpkinJuice.dwTileCursor, 0x78, 0x2D, g_ServePumpkinJuicePauseText, 1);
        g_GameModeStackContext.dwModeState = ServePumpkinJuiceStatePauseMenu;
        break;
    case ServePumpkinJuiceStatePauseMenu:
        if (g_wKeysPressed & KeyA)
        {
            switch ((s32)g_ServePumpkinJuice.dwMenuSelection)
            {
            case 0:
                FillBgTilemapRect(3, 0, 5, 0x1E, 9, 0);
                g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateWaitInput;
                break;
            case 1:
                FillBgTilemapRect(3, 0, 5, 0x1E, 9, 0);
                StartServePumpkinJuiceGame();
                break;
            case 2:
                PushGameMode_2(MinigameDifficultySelect, 6, g_GameModeStackContext.dwCurrentGameModeArg2);
                break;
            }
        }

        if (g_wKeysPressed & KeyB)
        {
            FillBgTilemapRect(3, 0, 5, 0x1E, 9, 0);
            g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateWaitInput;
        }

        if (StepCursorUpDown(&g_ServePumpkinJuice.dwMenuSelection, 0, 2, 1, 0))
            DrawServePumpkinJuicePauseMenu();
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
        DrawServePumpkinJuiceTaps();
        break;
    }
}
