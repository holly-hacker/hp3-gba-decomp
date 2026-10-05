#include "types.h"
#include "graphics/graphics.h"

void ResetAffineSlots(void)
{
    u32 i;

    g_bAffineSlotHighWaterMark = 0;
    for (i = 0; i < ARRAY_COUNT(g_abAffineSlotUsed); i++)
        g_abAffineSlotUsed[i] = 0;
}
