#include "types.h"
#include "scroll.h"

// Releases the cached tiles of the 31-tile row starting at pixel (x, y) on every BG layer.
void ReleaseBgTileRow(u32 x, u32 y)
{
    s32 layer;
    u32 row;
    u32 sizeClass;
    u16 (*pBlocks)[16];
    u32 col;
    u16 *pMap;
    const u16 *pBlock;
    s32 i;

    for (layer = 0; layer < 4; layer++)
    {
        sizeClass = ((layer + 1) & 2) >> 1;
        pBlocks = g_RoomBgBlockData.apBlockTiles[layer];
        col = (x & 0x18) >> 3;
        row = (y & 0x18) >> 1;
        pMap = g_RoomBgBlockData.apBlockMaps[layer] + (y >> 5) * g_wRoomBgLayer0BlocksWide + (x >> 5);
        pBlock = pBlocks[*pMap];
        for (i = 0; i < 31; i++)
        {
            ReleaseBgTileCacheEntry(pBlock[row + col], sizeClass, layer);
            col++;
            if (col > 3)
            {
                col -= 4;
                pMap++;
                pBlock = pBlocks[*pMap];
            }
        }
    }
}
