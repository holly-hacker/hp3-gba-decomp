#include "types.h"
#include "cheat.h"
#include "modes.h"
#include "input.h"
#include "menu/main_menu.h"
#include "menu/minigame_menu.h"

void UpdateCheat(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorUpDown(&g_CheatState.dwSelection, 0, 5, 1, 0))
    {
        SetActorMoveTargetWithDuration(g_CheatState.pCursorActor, 0x78,
                                                  g_CheatState.dwSelection * 0x10 + 0x2D, 5);
    }

    if (g_wKeysPressed & KeyA)
    {
        switch (g_CheatState.dwSelection)
        {
        case 0:
            PushGameMode_2(CheatMap, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 1:
            PushGameMode_2(CheatLevelAndQuest, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 2:
            PushGameMode_2(CheatParty, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 3:
            PushGameMode_2(CheatSoundTest, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 4:
            PushGameMode_2(CheatWizardCards, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 5:
            PushGameMode_2(CheatPortraits, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        }
    }
    else if (g_wKeysPressed & KeyB)
    {
        PushGameMode(MainMenu);
    }
}
