#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

// Appends len bytes to the slot stream, first closing a partly used byte
// (its unused high bits are cleared).
void PackBytesToSaveStream(const void *src, u32 len)
{
    if (g_saveManager.dwStreamBitPos > 0)
    {
        *g_saveManager.pStreamCursor &= 0xFF >> (8 - g_saveManager.dwStreamBitPos);
        g_saveManager.pStreamCursor++;
        g_saveManager.dwStreamBitPos = 0;
    }

    CopyMemory(g_saveManager.pStreamCursor, src, len);
    g_saveManager.pStreamCursor += len;
}
