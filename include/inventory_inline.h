#pragma once

#include "types.h"
#include "game/items.h"
#include "inventory.h"

// Inventory logic that the ROM compiles inline into other inventory routines.

// GetItemCharacterMask as CanFighterEquipItem inlines it; the standalone copy
// is written with its branches the other way round.
static inline u32 GetItemCharacterMaskInline(u32 item)
{
    if (g_pItemTable[item].dwCategory < ItemCategoryPotion)
        return g_pItemTable[item].nCharacterMask;

    return ItemCharacterMaskHarry | ItemCharacterMaskRon | ItemCharacterMaskHermione;
}

// The body of RemoveItems.
static inline u32 RemoveItemsInline(u32 item, u32 count)
{
    u8 *pQuantity = &g_ItemInventory.abQuantities[item];

    if (count > *pQuantity)
        count = *pQuantity;
    *pQuantity -= count;

    return *pQuantity;
}

// GetItemQuantity with the byte-sized result the ROM's callers test.
static inline u8 GetItemQuantityInline(u32 item)
{
    return g_ItemInventory.abQuantities[item];
}
