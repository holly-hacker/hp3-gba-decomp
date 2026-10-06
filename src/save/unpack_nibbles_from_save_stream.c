#include "types.h"
#include "game/save.h"

// Reads count nibbles into the low nibbles of dst's bytes, first moving to
// the next nibble boundary if the cursor is partway through one.
void UnpackNibblesFromSaveStream(u8 *dst, u32 count)
{
    u8 *p;

    if ((g_saveManager.dwStreamBitPos & 3) > 0)
    {
        if (g_saveManager.dwStreamBitPos <= 3)
        {
            g_saveManager.dwStreamBitPos = 4;
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
        if (g_saveManager.dwStreamBitPos == 0)
        {
            *p = *g_saveManager.pStreamCursor & 0xF;
            g_saveManager.dwStreamBitPos = 4;
        }
        else
        {
            *p = (*g_saveManager.pStreamCursor & 0xF0) >> 4;
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
        p++;
    }
}
