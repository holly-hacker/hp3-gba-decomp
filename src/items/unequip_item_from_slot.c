#include "types.h"
#include "game/rewards.h"
#include "items.h"

// Returns the slot's item to the inventory; 0 when the slot is empty.
u32 UnequipItemFromSlot(u8 character, u32 slot)
{
    if (g_ItemInventory.aabEquipped[character][slot] == 0xFF)
        return 0;

    GrantRewardInline(g_ItemInventory.aabEquipped[character][slot], 1);
    g_ItemInventory.aabEquipped[character][slot] = 0xFF;
    ApplyEquipmentStatModifiers();

    return 1;
}
