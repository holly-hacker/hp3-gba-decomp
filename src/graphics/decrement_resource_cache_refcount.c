#include "types.h"
#include "graphics.h"

void DecrementResourceCacheRefcount(s32 slotIndex)
{
    if (--g_aResourceCache[slotIndex].wRefcount == 0)
        g_aResourceCache[slotIndex].wFlags &= ~1;
}
