#include "types.h"
#include "game/items.h"
#include "inventory.h"

u32 GetItemQuantity(u32 item)
{
    return g_ItemInventory.abQuantities[item];
}
