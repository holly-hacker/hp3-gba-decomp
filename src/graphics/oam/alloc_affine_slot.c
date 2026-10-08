#include "types.h"
#include "graphics/graphics.h"

// Returns ARRAY_COUNT(g_abAffineSlotUsed) when every slot is in use.
u32 AllocAffineSlot(void)
{
    u16 slot;
    u16 remaining;

    for (slot = 0, remaining = ARRAY_COUNT(g_abAffineSlotUsed); remaining != 0;
         slot++, remaining--)
    {
        if (g_abAffineSlotUsed[slot] != 1)
        {
            g_abAffineSlotUsed[slot] = 1;
            if (slot >= g_bAffineSlotHighWaterMark)
                g_bAffineSlotHighWaterMark++;
            break;
        }
    }

    return slot;
}
