#include "graphics/graphics.h"

void ClearResourceCacheSlots(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aResourceCache); i++)
    {
        g_aResourceCache[i].pData = NULL;
        g_aResourceCache[i].wRefcount = 0;
        g_aResourceCache[i].wFlags = 0;
    }
}
