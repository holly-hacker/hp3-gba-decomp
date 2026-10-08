#include "types.h"
#include "hw/mem.h"

// Returns the tiles freed since the last OAM buffer swap to the allocator
// and resets the pending-free mask.
void ApplyDeferredObjTileFrees(void)
{
    u32 i;
    u32 *pBitmap = (u32 *)g_abObjTileAllocBitmap;
    u32 *pMask = (u32 *)g_abObjTileFreeMask;

    for (i = 0; i < 32; i++) {
        pBitmap[i] &= pMask[i];
        pMask[i] = 0xFFFFFFFF;
    }
}
