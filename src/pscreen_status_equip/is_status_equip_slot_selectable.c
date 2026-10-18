#include "types.h"
#include "items.h"
#include "pscreen_character.h"
#include "pscreen_status_equip.h"

// Nonzero when the selected slot has an item equipped or the player owns an item for it.
u32 IsStatusEquipSlotSelectable(void)
{
    u32 result = 0;

    if (OwnsItemInCategory(g_aStatusEquipSlots[g_bStatusEquipSlot].dwType)
        || g_ItemInventory.aabEquipped[g_dwStatusEquipCharacter][g_aStatusEquipSlots[g_bStatusEquipSlot].dwType] != 0xFF)
        result = 1;

    return result;
}
