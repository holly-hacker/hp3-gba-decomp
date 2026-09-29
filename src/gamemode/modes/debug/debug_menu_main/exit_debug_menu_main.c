#include "types.h"
#include "graphics/display.h"
#include "hw/mem.h"

void ExitDebugMenuMain(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
