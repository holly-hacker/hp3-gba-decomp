#include "types.h"
#include "constants/items.h"
#include "game/items.h"
#include "inventory.h"

// Battle item slots are the six potions, from ITEM_WIGGENWELD_POTION.
u32 IsBattleItemSlotUsable(u32 slot)
{
    return g_ItemInventory.abQuantities[slot + ITEM_WIGGENWELD_POTION] != 0;
}
