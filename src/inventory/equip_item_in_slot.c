#include "types.h"
#include "inventory.h"
#include "inventory_inline.h"

// Moves one owned copy of the item into the character's slot for its
// category, returning the previous item to the inventory. Returns 0 when the
// item is not owned or the character can't wear it.
u32 EquipItemInSlot(u8 character, u32 item)
{
    u32 slot;

    if (g_ItemInventory.abQuantities[item] == 0)
        return 0;
    if (!CanFighterEquipItem(character, item))
        return 0;

    slot = g_pItemTable[item].dwCategory;
    UnequipItemFromSlot(character, slot);
    RemoveItemsInline(item, 1);
    g_ItemInventory.aabEquipped[character][slot] = item;
    ApplyEquipmentStatModifiers();

    return 1;
}
