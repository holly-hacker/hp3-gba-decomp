#include "types.h"
#include "display.h"
#include "mem.h"

void ExitDebugMapSelectMenu(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
