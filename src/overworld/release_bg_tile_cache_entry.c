#include "types.h"
#include "overworld/room.h"

// Drops one reference to `tileId` in the room BG tile cache of the given size class. When the last
// reference goes, the entry is unlinked from its hash chain and returned to the free slot stack.
// Returns 1 if the tile is not cached, otherwise 0.
u32 ReleaseBgTileCacheEntry(u16 tileId, u32 sizeClass, u32 layer)
{
    BgTileCacheEntry *pEntries;
    u32 index;
    u16 prev;
    u32 key;

    prev = 0xFFFF;
    if (sizeClass == 0)
        key = tileId & 0x7FF;
    else
        key = tileId & 0x3FF;

    index = g_apBgTileCacheBuckets[sizeClass][key];
    pEntries = g_apBgTileCacheEntries[sizeClass];
    while (index != 0xFFFF && pEntries[index].wTileId != tileId)
    {
        prev = index;
        index = pEntries[index].wNext;
    }
    if (index == 0xFFFF)
        return 1;

    pEntries[index].wRefcount--;
    if (pEntries[index].wRefcount != 0)
        return 0;

    g_awBgLayerTileCount[layer]--;
    g_apBgTileCacheFreeSlots[sizeClass][g_awBgTileCacheFreeCount[sizeClass]++] = index;
    if (prev == 0xFFFF)
        g_apBgTileCacheBuckets[sizeClass][key] = g_apBgTileCacheEntries[sizeClass][index].wNext;
    else
        pEntries[prev].wNext = g_apBgTileCacheEntries[sizeClass][index].wNext;
    pEntries[index].wTileId = 0xFFFF;
    pEntries[index].wNext = 0xFFFF;
    return 0;
}
