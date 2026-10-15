#include "types.h"
#include "game/items.h"
#include "inventory.h"

u32 GetEquippedItem(u8 character, u32 slot)
{
    return g_ItemInventory.aabEquipped[character][slot];
}
