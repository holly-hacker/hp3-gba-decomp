#include "modes.h"
#include "pscreen_item_count.h"

void InitializeQuantitySelectScreen(void)
{
    g_GameModeStackContext.dwModeScratchB = 1;
    BeginQuantitySelectScreen();
    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeSubState = 0x10;
}
