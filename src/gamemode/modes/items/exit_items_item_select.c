#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "menu/items_menu.h"
#include "hw/mem.h"
#include "menu/status_equip.h"

void ExitItemsItemSelect(void)
{
    if (g_ItemsItemSelect.dwHasItems != 0)
        CloseItemList();

    FreeAllActors(&g_ActiveActorListState.pHead);
    ClearBgTilemap(2);
}
