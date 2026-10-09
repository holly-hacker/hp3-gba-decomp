#include "types.h"
#include "graphics/palette.h"

// Queues a load of `colorCount` colors from `pPalette` into OBJ palette RAM at color `firstColor`.
// Returns 1 if the queue (25 entries) is full, otherwise 0.
s32 QueueObjPaletteLoad(const u16 *pPalette, u32 firstColor, u32 colorCount)
{
    u32 count;

    count = g_dwObjPaletteQueueCount;
    if (count > 0x18)
        return 1;

    g_aObjPaletteQueue[count].pPalette = pPalette;
    g_aObjPaletteQueue[count].wFirstColor = firstColor;
    g_aObjPaletteQueue[count].wColorCount = colorCount;
    g_dwObjPaletteQueueCount = count + 1;
    return 0;
}
