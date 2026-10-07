#include "types.h"
#include "game/game_modes.h"
#include "menu/quantity_select.h"

void InitializeQuantitySelectScreen(void)
{
    g_GameModeStackContext.dwModeScratchB = 1;
    sub_08039428();
    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeSubState = 0x10;
}
