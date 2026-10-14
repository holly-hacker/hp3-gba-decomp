#include "types.h"
#include "cheat_portraits.h"
#include "game/game_modes.h"
#include "input.h"
#include "menu/minigame_menu.h"

void UpdateCheatPortraits(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorLeftRight(&g_CheatPortraitsState.dwSelection, 0, 0x86, 1, 0))
        ShowCheatPortrait();

    if (g_wKeysPressed & KeyA)
        PushGameMode_2(Cheat, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    else if (g_wKeysPressed & KeyB)
        PushGameMode_2(Cheat, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
}
