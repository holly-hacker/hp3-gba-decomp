#include "types.h"
#include "items_list.h"

void FreeItemListIconGfx(u32 slot)
{
    g_ItemList.abIconGfxUsed[slot] = 0;
}
