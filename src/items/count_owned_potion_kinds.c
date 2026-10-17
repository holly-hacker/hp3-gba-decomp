#include "types.h"
#include "constants/items.h"
#include "game/items.h"
#include "items.h"

u32 CountOwnedPotionKinds(void)
{
    u32 count;
    u32 item;

    count = 0;
    for (item = ITEM_WIGGENWELD_POTION; item <= ITEM_ANTI_PARALYSIS_POTION; item++)
    {
        if (g_ItemInventory.abQuantities[item] != 0)
            count++;
    }

    return count;
}
