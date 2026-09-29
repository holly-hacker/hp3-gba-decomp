#include "types.h"
#include "hw/mem.h"

void ExitItemUseScreen(void)
{
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
