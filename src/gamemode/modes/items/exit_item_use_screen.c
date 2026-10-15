#include "types.h"
#include "hw/mem.h"
#include "actor.h"

void ExitItemUseScreen(void)
{
    FreeAllActors(&g_ActiveActorListState.pHead);
}
