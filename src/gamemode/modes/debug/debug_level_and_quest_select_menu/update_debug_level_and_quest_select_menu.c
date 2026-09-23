#include "types.h"
#include "debug_menu.h"
#include "game_modes.h"
#include "input.h"
#include "minigame_menu.h"

void UpdateDebugLevelAndQuestSelectMenu(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepWrappedSelectionVertical_candidate(&g_DebugLevelAndQuestSelectState.dwRow, 0, 3, 1, 0))
    {
        SetObjectMoveTargetWithDuration_candidate(g_DebugLevelAndQuestSelectState.pCursorObject, 0x9C,
                                                  g_DebugLevelAndQuestSelectState.dwRow * 18 + 0x3A, 5);
    }

    if (StepWrappedSelectionHorizontal_candidate(
            &g_DebugLevelAndQuestSelectState.adwValue[g_DebugLevelAndQuestSelectState.dwRow], 0,
            g_abDebugLevelAndQuestMax[g_DebugLevelAndQuestSelectState.dwRow], 1, 0))
    {
        sub_0800AE68();
    }

    if (g_wKeysPressed & KeyA)
    {
        PushGameMode_2(DebugMenuMain, 0,
                       (g_DebugLevelAndQuestSelectState.adwValue[3] << 24) |
                           (g_DebugLevelAndQuestSelectState.adwValue[0] << 16) |
                           (g_DebugLevelAndQuestSelectState.adwValue[1] << 8) |
                           g_DebugLevelAndQuestSelectState.adwValue[2]);
    }
    else if (g_wKeysPressed & KeyB)
    {
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}
