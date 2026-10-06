#include "types.h"
#include "game/save.h"

// Reads count 2-bit values into dst's bytes, first moving to the next 2-bit
// boundary if the cursor is partway through one. Nothing calls it.
void UnpackBitPairsFromSaveStream(u8 *dst, u32 count)
{
    u8 *p;

    if ((g_saveManager.dwStreamBitPos & 1) > 0)
    {
        if (g_saveManager.dwStreamBitPos <= 6)
        {
            g_saveManager.dwStreamBitPos++;
        }
        else
        {
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
    }

    p = dst;
    for (; count != 0; count--)
    {
        *p = (*g_saveManager.pStreamCursor >> g_saveManager.dwStreamBitPos) & 3;
        g_saveManager.dwStreamBitPos += 2;
        if (g_saveManager.dwStreamBitPos > 7)
        {
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
        p++;
    }
}
