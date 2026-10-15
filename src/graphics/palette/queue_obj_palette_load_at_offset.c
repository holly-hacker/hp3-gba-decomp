#include "types.h"
#include "graphics/palette.h"

// QueueObjPaletteLoad with the source given as a byte offset into pPalettes.
s32 QueueObjPaletteLoadAtOffset(const u8 *pPalettes, u32 byteOffset, u32 firstColor, u32 colorCount)
{
    u32 count;

    count = g_dwObjPaletteQueueCount;
    if (count > 0x18)
        return 1;

    g_aObjPaletteQueue[count].pPalette = (const u16 *)(pPalettes + byteOffset);
    g_aObjPaletteQueue[count].wFirstColor = firstColor;
    g_aObjPaletteQueue[count].wColorCount = colorCount;
    g_dwObjPaletteQueueCount = count + 1;
    return 0;
}
