#include "types.h"
#include "debug_menu.h"
#include "game_modes.h"
#include "input.h"
#include "minigame_menu.h"

void UpdateDebugPortraitsMenu(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepWrappedSelectionHorizontal_candidate(&g_DebugPortraitsState.dwSelection, 0, 0x86, 1, 0))
        sub_0800B52C();

    if (g_wKeysPressed & KeyA)
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    else if (g_wKeysPressed & KeyB)
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
}
