#include "types.h"
#include "mem.h"

// Returns the tiles freed since the last OAM buffer swap to the allocator
// and resets the pending-free mask.
void ApplyDeferredObjTileFrees(void)
{
    u32 i;
    u32 *pBitmap = g_adwObjTileAllocBitmap;
    u32 *pMask = g_adwObjTileFreeMask;

    for (i = 0; i < 32; i++) {
        pBitmap[i] &= pMask[i];
        pMask[i] = 0xFFFFFFFF;
    }
}
