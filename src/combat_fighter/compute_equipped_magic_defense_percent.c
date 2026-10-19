#include "types.h"
#include "combat_fighter.h"
#include "items.h"
#include "game/items.h"

// 100 less every equipped item's magic defense. No callers.
s32 ComputeEquippedMagicDefensePercent(u32 character)
{
    s32 percent;
    s32 slot;

    percent = 100;
    for (slot = 0; slot < EQUIP_SLOT_COUNT; slot++)
    {
        if (g_ItemInventory.aabEquipped[character][slot] != 0xFF)
            percent -= GetItemMagicDefense(g_ItemInventory.aabEquipped[character][slot]);
    }

    return percent;
}
