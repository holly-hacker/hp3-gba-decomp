#include "color.h"

// Slots are handed out in order and only reclaimed by ResetColorCycles.
u32 AllocColorCycleSlot(void)
{
    // NOTE: no bounds check; a 13th cycle before a reset would index past g_aColorCycles.
    return g_dwColorCycleCount++;
}
