#include "actor.h"

void ExitItemUseScreen(void)
{
    FreeAllActors(&g_ActiveActorListState.pHead);
}
