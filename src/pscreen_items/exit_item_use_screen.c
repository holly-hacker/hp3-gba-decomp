#include "types.h"
#include "mem.h"
#include "actor.h"

void ExitItemUseScreen(void)
{
    FreeAllActors(&g_ActiveActorListState.pHead);
}
