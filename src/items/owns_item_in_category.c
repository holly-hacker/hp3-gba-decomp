#include "types.h"
#include "constants/items.h"
#include "game/items.h"
#include "items.h"

u32 OwnsItemInCategory(u32 category)
{
    s32 item;

    for (item = 0; item < SIMPLE_ITEMS_END; item++)
    {
        if (g_pItemTable[item].dwCategory == category && g_ItemInventory.abQuantities[item] != 0)
            return 1;
    }

    return 0;
}
