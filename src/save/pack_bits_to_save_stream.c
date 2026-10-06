#include "types.h"
#include "game/save.h"

// Appends the low bit of each of count source bytes to the slot stream.
void PackBitsToSaveStream(const u8 *src, u32 count)
{
    const u8 *p = src;

    for (; count != 0; count--)
    {
        *g_saveManager.pStreamCursor &= 0xFF >> (8 - g_saveManager.dwStreamBitPos);
        *g_saveManager.pStreamCursor |= (*p & 1) << g_saveManager.dwStreamBitPos;
        g_saveManager.dwStreamBitPos++;
        if (g_saveManager.dwStreamBitPos > 7)
        {
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
        p++;
    }
}
