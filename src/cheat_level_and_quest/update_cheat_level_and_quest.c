#include "types.h"
#include "cheat_level_and_quest.h"
#include "modes.h"
#include "input.h"
#include "menu/minigame_menu.h"

void UpdateCheatLevelAndQuest(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorUpDown(&g_CheatLevelAndQuestState.dwRow, 0, 3, 1, 0))
    {
        SetActorMoveTargetWithDuration(g_CheatLevelAndQuestState.pCursorActor, 0x9C,
                                                  g_CheatLevelAndQuestState.dwRow * 18 + 0x3A, 5);
    }

    if (StepCursorLeftRight(
            &g_CheatLevelAndQuestState.adwValue[g_CheatLevelAndQuestState.dwRow], 0,
            g_abCheatLevelAndQuestMax[g_CheatLevelAndQuestState.dwRow], 1, 0))
    {
        DrawCheatLevelAndQuestValues();
    }

    if (g_wKeysPressed & KeyA)
    {
        PushGameMode_2(Cheat, 0,
                       (g_CheatLevelAndQuestState.adwValue[3] << 24) |
                           (g_CheatLevelAndQuestState.adwValue[0] << 16) |
                           (g_CheatLevelAndQuestState.adwValue[1] << 8) |
                           g_CheatLevelAndQuestState.adwValue[2]);
    }
    else if (g_wKeysPressed & KeyB)
    {
        PushGameMode_2(Cheat, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}
