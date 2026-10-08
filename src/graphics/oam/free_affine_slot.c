#include "types.h"
#include "graphics/graphics.h"

void FreeAffineSlot(u16 slot)
{
    g_abAffineSlotUsed[slot] = 0;

    // Freeing the top slot lowers the high-water mark past any free slots below it.
    if (slot == g_bAffineSlotHighWaterMark - 1 && g_bAffineSlotHighWaterMark != 0)
    {
        do
        {
            g_bAffineSlotHighWaterMark--;
            slot--;
        } while (g_bAffineSlotHighWaterMark != 0 && g_abAffineSlotUsed[slot] == 0);
    }
}
