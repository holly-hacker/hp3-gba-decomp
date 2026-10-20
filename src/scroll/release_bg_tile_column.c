#include "types.h"
#include "scroll.h"

// Releases the cached tiles of the 21-tile column starting at pixel (x, y) on every BG layer.
void ReleaseBgTileColumn(u32 x, u32 y)
{
    s32 layer;
    u32 sizeClass;
    u16 *pMap;
    const u16 *pBlock;
    u32 col;
    u32 row;
    s32 i;

    for (layer = 0; layer < 4; layer++)
    {
        sizeClass = ((layer + 1) & 2) >> 1;
        col = (x & 0x18) >> 3;
        pMap = g_RoomBgBlockData.apBlockMaps[layer] + (y >> 5) * g_wRoomBgLayer0BlocksWide + (x >> 5);
        pBlock = g_RoomBgBlockData.apBlockTiles[layer][*pMap];
        row = (y & 0x18) >> 1;
        for (i = 0; i < 21; i++)
        {
            ReleaseBgTileCacheEntry(pBlock[row + col], sizeClass, layer);
            row += 4;
            if (row > 15)
            {
                row -= 16;
                pMap += g_wRoomBgLayer0BlocksWide;
                pBlock = g_RoomBgBlockData.apBlockTiles[layer][*pMap];
            }
        }
    }
}
