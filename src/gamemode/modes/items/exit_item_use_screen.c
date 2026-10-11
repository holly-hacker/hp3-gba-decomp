#include "types.h"
#include "hw/mem.h"

void ExitItemUseScreen(void)
{
    FreeAllActors(&g_ActiveActorListState.pHead);
}
