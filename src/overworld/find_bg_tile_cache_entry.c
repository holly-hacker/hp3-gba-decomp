#include "types.h"
#include "overworld/room.h"

// Looks `tileId` up in the room BG tile cache of the given size class (0: 0x7FF hash buckets,
// 1: 0x3FF) and returns its entry index, which is also its VRAM slot, or 0xFFFF if not cached.
u16 FindBgTileCacheEntry(u16 tileId, u32 sizeClass)
{
    BgTileCacheEntry *pEntries;
    u16 index;
    u32 key;

    if (sizeClass == 0)
        key = tileId & 0x7FF;
    else
        key = tileId & 0x3FF;

    index = g_apBgTileCacheBuckets[sizeClass][key];
    pEntries = g_apBgTileCacheEntries[sizeClass];
    for (; index != 0xFFFF; index = pEntries[index].wNext)
    {
        if (pEntries[index].wTileId == tileId)
            break;
    }

    return index;
}
