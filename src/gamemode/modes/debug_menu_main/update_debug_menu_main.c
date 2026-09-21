#include "types.h"
#include "debug_menu.h"
#include "game_modes.h"
#include "input.h"
#include "main_menu.h"
#include "minigame_menu.h"

void UpdateDebugMenuMain(void)
{
    if (g_GameModeStackContext.dwModeState_candidate != 0)
        return;

    if (StepWrappedSelectionVertical_candidate(&g_DebugMenuMainState.dwSelection, 0, 5, 1, 0))
    {
        SetObjectMoveTargetWithDuration_candidate(g_DebugMenuMainState.pCursorObject, 0x78,
                                                  g_DebugMenuMainState.dwSelection * 0x10 + 0x2D, 5);
    }

    if (g_wKeysPressed & KeyA)
    {
        switch (g_DebugMenuMainState.dwSelection)
        {
        case 0:
            PushGameMode_2(DebugMenuMapSelect, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 1:
            PushGameMode_2(DebugMenuLevelAndQuestSelect, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 2:
            PushGameMode_2(DebugMenuCharacterSelect, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 3:
            PushGameMode_2(DebugMenuSoundTest, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 4:
            PushGameMode_2(DebugMenuCollectorCards, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        case 5:
            PushGameMode_2(DebugMenuPortraits, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
            break;
        }
    }
    else if (g_wKeysPressed & KeyB)
    {
        PushGameMode(MainMenu);
    }
}
