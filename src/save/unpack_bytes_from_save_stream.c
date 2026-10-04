#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

// Copies len bytes out of the slot stream, first skipping to the next byte
// boundary if the cursor is partway through a byte.
void UnpackBytesFromSaveStream(void *dst, u32 len)
{
    if (g_saveManager.dwStreamBitPos > 0)
    {
        g_saveManager.pStreamCursor++;
        g_saveManager.dwStreamBitPos = 0;
    }

    CopyMemory(dst, g_saveManager.pStreamCursor, len);
    g_saveManager.pStreamCursor += len;
}
