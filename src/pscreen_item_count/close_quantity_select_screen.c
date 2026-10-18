#include "actor.h"
#include "background.h"
#include "pscreen_item_count.h"

void CloseQuantitySelectScreen(void)
{
    ClearBgTilemap(2);
    FreeAllActors(&g_ActiveActorListState.pHead);
}
