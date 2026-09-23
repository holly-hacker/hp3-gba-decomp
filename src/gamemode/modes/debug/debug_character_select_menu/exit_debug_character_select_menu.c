#include "types.h"
#include "debug_menu.h"
#include "display.h"
#include "mem.h"

void ExitDebugCharacterSelectMenu(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0800B40C();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
