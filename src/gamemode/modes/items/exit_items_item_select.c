#include "types.h"
#include "graphics/display.h"
#include "menu/items_menu.h"
#include "hw/mem.h"
#include "menu/status_equip.h"

void ExitItemsItemSelect(void)
{
    if (g_ItemsItemSelect.dwHasItems != 0)
        CloseItemList();

    FreeAllObjects(&g_ActiveObjectListState.pHead);
    ClearBgTilemap(2);
}
