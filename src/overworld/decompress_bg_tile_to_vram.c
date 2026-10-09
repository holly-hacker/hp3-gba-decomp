#include "types.h"
#include "hw/io_regs.h"
#include "graphics/graphics.h"
#include "overworld/room.h"

typedef void (*BgTileDecoder)(u32 bitOffset, void *dest, u32 size, const void *codeTable);

// Takes a reference on `tileId` in the room BG tile cache of the given size class, decompressing
// the tile into its BG character VRAM slot on a miss. Returns the slot index.
u32 DecompressBgTileToVram_candidate(u32 tileId, u32 sizeClass, u32 arg2, u32 layer)
{
    u16 index;
    BgTileCacheEntry *pEntries;
    u16 prev;
    u32 key;
    BgTileDecoder pDecode;

    pDecode = (BgTileDecoder)g_aDecompressBgTileIwram;
    prev = 0xFFFF;
    if (sizeClass == 0)
        key = tileId & 0x7FF;
    else
        key = tileId & 0x3FF;

    index = g_apBgTileCacheBuckets[sizeClass][key];
    pEntries = g_apBgTileCacheEntries[sizeClass];
    for (; index != 0xFFFF; index = pEntries[index].wNext)
    {
        if (pEntries[index].wTileId == tileId)
        {
            pEntries[index].wRefcount++;
            return index;
        }
        prev = index;
    }

    g_awBgLayerTileCount[layer]++;
    g_awBgTileCacheFreeCount[sizeClass]--;
    index = g_apBgTileCacheFreeSlots[sizeClass][g_awBgTileCacheFreeCount[sizeClass]];
    if (prev != 0xFFFF)
        pEntries[prev].wNext = index;
    else
        g_apBgTileCacheBuckets[sizeClass][key] = index;
    pEntries[index].wTileId = tileId;
    pEntries[index].wRefcount = 1;
    pDecode(g_aBgTilesets[sizeClass].pTileBitOffsets[tileId],
                                (u8 *)VRAM_BASE + (index + sizeClass * 0x400) * 0x20, 0x20,
                                g_aBgTilesets[sizeClass].pCodeTable);
    return index;
}
