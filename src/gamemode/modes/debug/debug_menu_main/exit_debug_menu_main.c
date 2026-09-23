#include "types.h"
#include "display.h"
#include "mem.h"

void ExitDebugMenuMain(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_080015D4(&g_ActiveObjectListState.pHead);
}
