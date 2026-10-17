#include "types.h"
#include "modes.h"
#include "pscreen_item_count.h"

void InitializeQuantitySelectScreen(void)
{
    g_GameModeStackContext.dwModeScratchB = 1;
    sub_08039428();
    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeSubState = 0x10;
}
