#include "types.h"
#include "background.h"
#include "pscreen_items.h"
#include "mem.h"
#include "actor.h"
#include "pscreen_status_equip.h"
#include "items.h"

void ExitItemsItemSelect(void)
{
    if (g_ItemsItemSelect.dwHasItems != 0)
        CloseItemList();

    FreeAllActors(&g_ActiveActorListState.pHead);
    ClearBgTilemap(2);
}
