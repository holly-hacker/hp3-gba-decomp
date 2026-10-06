#include "types.h"
#include "game/save.h"

void PackNibblesToSaveStream(const u8 *src, u32 count)
{
    const u8 *p;

    if ((g_saveManager.dwStreamBitPos & 3) > 0)
    {
        *g_saveManager.pStreamCursor &= 0xFF >> (8 - g_saveManager.dwStreamBitPos);
        if (g_saveManager.dwStreamBitPos <= 3)
            g_saveManager.dwStreamBitPos = 4;
        else
        {
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
    }

    p = src;
    for (; count != 0; count--)
    {
        if (g_saveManager.dwStreamBitPos == 0)
        {
            *g_saveManager.pStreamCursor = *p & 0xF;
            g_saveManager.dwStreamBitPos = 4;
        }
        else
        {
            *g_saveManager.pStreamCursor = ((*p & 0xF) << 4) + (*g_saveManager.pStreamCursor & 0xF);
            g_saveManager.pStreamCursor++;
            g_saveManager.dwStreamBitPos = 0;
        }
        p++;
    }
}
