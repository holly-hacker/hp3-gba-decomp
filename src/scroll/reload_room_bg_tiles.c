#include "types.h"
#include "mem.h"
#include "scroll.h"

// Empties the BG tile cache and loads every tile of the window at g_BgScroll.
void ReloadRoomBgTiles(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aBgStripReleases); i++)
        g_aBgStripReleases[i].x = BG_STRIP_NONE;
    g_awBgLayerTileCount[0] = 0;
    g_awBgLayerTileCount[1] = 0;
    g_awBgLayerTileCount[2] = 0;
    g_awBgLayerTileCount[3] = 0;

    memset(g_apBgTileCacheEntries[0], 0xFF, 0x400 * sizeof(BgTileCacheEntry));
    memset(g_apBgTileCacheEntries[1], 0xFF, 0x200 * sizeof(BgTileCacheEntry));
    memset(g_apBgTileCacheBuckets[0], 0xFF, 0x800 * sizeof(u16));
    memset(g_apBgTileCacheBuckets[1], 0xFF, 0x400 * sizeof(u16));
    g_awBgTileCacheFreeCount[0] = 0x400;
    g_awBgTileCacheFreeCount[1] = 0x200;
    for (i = 0; i < 0x400; i++)
        g_apBgTileCacheFreeSlots[0][i] = 0x3FF - i;
    for (i = 0; i < 0x200; i++)
        g_apBgTileCacheFreeSlots[1][i] = 0x1FF - i;

    for (i = 0; i < 21; i++)
        LoadBgTileRow(g_BgScroll.x, g_BgScroll.y + i * 8);
    g_BgLoadedScroll = g_BgScroll;
}
