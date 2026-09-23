#include "types.h"
#include "display.h"
#include "items_menu.h"
#include "mem.h"
#include "status_equip.h"

void ExitItemsItemSelect(void)
{
    if (g_ItemsItemSelect.dwHasItems != 0)
        sub_08027BA4();

    FreeAllObjects(&g_ActiveObjectListState.pHead);
    ClearBgTilemap(2);
}
