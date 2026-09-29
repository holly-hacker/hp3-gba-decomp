#include "types.h"
#include "menu/debug_menu.h"
#include "graphics/display.h"
#include "hw/mem.h"

void ExitDebugCharacterSelectMenu(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0800B40C();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
