#include "types.h"
#include "graphics/graphics.h"

static inline u32 FindEmptyResourceCacheSlot(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aResourceCache); i++)
    {
        if (g_aResourceCache[i].pData == NULL
            && !(g_aResourceCache[i].wFlags & ResourceCacheFlagReserved))
            return i;
    }

    return 0xFF;
}

static inline u32 FindUnreferencedResourceCacheSlot(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aResourceCache); i++)
    {
        if (g_aResourceCache[i].wRefcount == 0
            && !(g_aResourceCache[i].wFlags & ResourceCacheFlagReserved))
            return i;
    }

    return 0xFF;
}

static inline u32 FindSharedResourceCacheSlot(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aResourceCache); i++)
    {
        if (!(g_aResourceCache[i].wFlags & (ResourceCacheFlagUnshared | ResourceCacheFlagReserved)))
            return i;
    }

    return 0xFF;
}

// Prefers an empty slot, then one no object references, then any shared slot;
// reserved slots are skipped. Falls back to the last slot.
u32 AllocResourceCacheSlot(void)
{
    u32 slot;

    slot = FindEmptyResourceCacheSlot();
    if (slot == 0xFF)
    {
        slot = FindUnreferencedResourceCacheSlot();
        if (slot == 0xFF)
        {
            slot = FindSharedResourceCacheSlot();
            if (slot == 0xFF)
                slot = ARRAY_COUNT(g_aResourceCache) - 1;
        }
    }

    return slot;
}
