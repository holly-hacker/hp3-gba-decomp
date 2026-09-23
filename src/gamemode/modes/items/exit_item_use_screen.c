#include "types.h"
#include "mem.h"

void ExitItemUseScreen(void)
{
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
