#include "types.h"
#include "items.h"

// Items outside the equipment categories can be used by anyone.
u32 GetItemCharacterMask(u32 item)
{
    u32 mask;

    if (g_pItemTable[item].dwCategory >= ItemCategoryPotion)
        mask = ItemCharacterMaskHarry | ItemCharacterMaskRon | ItemCharacterMaskHermione;
    else
        mask = g_pItemTable[item].nCharacterMask;

    return mask;
}
