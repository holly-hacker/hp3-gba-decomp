#include "background.h"
#include "pscreen_items.h"
#include "actor.h"
#include "items_list.h"

void ExitItemsItemSelect(void)
{
    if (g_ItemsItemSelect.dwHasItems != 0)
        CloseItemList();

    FreeAllActors(&g_ActiveActorListState.pHead);
    ClearBgTilemap(2);
}
