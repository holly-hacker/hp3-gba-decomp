#include "types.h"
#include "game/items.h"
#include "items.h"

u32 GetEquippedItem(u8 character, u32 slot)
{
    return g_ItemInventory.aabEquipped[character][slot];
}
