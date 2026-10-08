#include "types.h"
#include "graphics/graphics.h"

// Returns the shared, unreserved slot already holding pPalette, or 0xFF.
u32 FindResourceCacheSlot(const ObjPalette *pPalette)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aResourceCache); i++)
    {
        if (g_aResourceCache[i].pData == pPalette
            && !(g_aResourceCache[i].wFlags & (ResourceCacheFlagUnshared | ResourceCacheFlagReserved)))
            return i;
    }

    return 0xFF;
}
