#include "types.h"
#include "menu/debug_menu.h"
#include "game/game_modes.h"
#include "input.h"
#include "menu/minigame_menu.h"

void UpdateDebugCollectorCardsMenu(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorLeftRight(&g_DebugCollectorCardsState.dwSelection, 0, 0x32, 1, 0))
        sub_0800BAF8();

    if (g_wKeysPressed & KeyA)
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    else if (g_wKeysPressed & KeyB)
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
}
