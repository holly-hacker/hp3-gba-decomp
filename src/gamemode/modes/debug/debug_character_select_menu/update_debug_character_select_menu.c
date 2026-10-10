#include "types.h"
#include "menu/debug_menu.h"
#include "game/game_modes.h"
#include "input.h"
#include "menu/minigame_menu.h"

void UpdateDebugCharacterSelectMenu(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorUpDown(&g_DebugCharacterSelectState.dwRow, 0, 2, 1, 0))
    {
        SetObjectMoveTargetWithDuration_candidate(g_DebugCharacterSelectState.pCursorObject, 0x9C,
                                                  g_DebugCharacterSelectState.dwRow * 18 + 0x3A, 5);
    }

    if (StepCursorLeftRight(
            &g_DebugCharacterSelectState.adwCharacter[g_DebugCharacterSelectState.dwRow], 0, 9, 1, 0))
    {
        sub_0800B4B0();
    }

    if (g_wKeysPressed & (KeyA | KeyB))
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
}
