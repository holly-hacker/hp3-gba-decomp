#include "types.h"
#include "game/save.h"

// Reads count single bits into dst's bytes (0 or 1 each).
void UnpackBitsFromSaveStream(u8 *dst, u32 count)
{
    u8 *p = dst;

    for (; count != 0; count--)
    {
        *p = (*g_saveManager.pStreamCursor >> g_saveManager.dwStreamBitPos) & 1;
        g_saveManager.dwStreamBitPos++;
        if (g_saveManager.dwStreamBitPos > 7)
        {
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
        p++;
    }
}
