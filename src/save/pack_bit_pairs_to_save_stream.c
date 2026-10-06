#include "types.h"
#include "game/save.h"

void PackBitPairsToSaveStream(const u8 *src, u32 count)
{
    const u8 *p;

    if ((g_saveManager.dwStreamBitPos & 1) > 0)
    {
        *g_saveManager.pStreamCursor &= 0xFF >> (8 - g_saveManager.dwStreamBitPos);
        if (g_saveManager.dwStreamBitPos <= 6)
            g_saveManager.dwStreamBitPos++;
        else
        {
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
    }

    p = src;
    for (; count != 0; count--)
    {
        *g_saveManager.pStreamCursor &= 0xFF >> (8 - g_saveManager.dwStreamBitPos);
        *g_saveManager.pStreamCursor |= (*p & 3) << g_saveManager.dwStreamBitPos;
        g_saveManager.dwStreamBitPos += 2;
        if (g_saveManager.dwStreamBitPos > 7)
        {
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
        p++;
    }
}
