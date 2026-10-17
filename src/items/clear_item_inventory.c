#include "types.h"
#include "items.h"

void ClearItemInventory(void)
{
    s32 i;
    s32 slot;

    for (i = 0; i < ITEM_COUNT; i++)
        g_ItemInventory.abQuantities[i] = 0;

    for (i = 0; i < 3; i++)
    {
        for (slot = 0; slot < EQUIP_SLOT_COUNT; slot++)
            g_ItemInventory.aabEquipped[i][slot] |= 0xFF;
    }
}
