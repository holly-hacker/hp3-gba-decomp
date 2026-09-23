#include "types.h"
#include "debug_menu.h"
#include "game_modes.h"
#include "input.h"
#include "minigame_menu.h"

void UpdateDebugCollectorCardsMenu(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepWrappedSelectionHorizontal_candidate(&g_DebugCollectorCardsState.dwSelection, 0, 0x32, 1, 0))
        sub_0800BAF8();

    if (g_wKeysPressed & KeyA)
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    else if (g_wKeysPressed & KeyB)
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
}
