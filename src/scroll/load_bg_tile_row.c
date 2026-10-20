#include "types.h"
#include "hw/io_regs.h"
#include "scroll.h"

// Loads the 31-tile row starting at pixel (x, y) on every BG layer into the BG tile cache and
// writes it to the layer's tilemap.
void LoadBgTileRow(u32 x, u32 y)
{
    u32 row;
    s32 i;
    s32 layer;
    u32 sizeClass;
    u16 (*pBlocks)[16];
    u32 col;
    u16 *pMap;
    u16 *pTilemap;
    u32 mapX;
    const u16 *pBlock;
    const u8 *pAttrs;
    u32 tile;

    for (layer = 0; layer < 4; layer++)
    {
        sizeClass = ((layer + 1) & 2) >> 1;
        pBlocks = g_RoomBgBlockData.apBlockTiles[layer];
        col = (x & 0x18) >> 3;
        row = (y & 0x18) >> 1;
        pMap = g_RoomBgBlockData.apBlockMaps[layer] + (y >> 5) * g_wRoomBgLayer0BlocksWide + (x >> 5);
        pTilemap = (u16 *)((u8 *)VRAM_BASE + g_aBgControl[layer].bScreenBlock * 0x800);
        pTilemap += ((y & 0xFF) >> 3) * 32;
        mapX = (x & 0xFF) >> 3;
        pBlock = pBlocks[*pMap];
        pAttrs = (u8 *)pBlocks + g_adwBgBlockAttrOffset[layer] + *pMap * 16;
        for (i = 0; i < 31; i++)
        {
            tile = AcquireBgTileCacheEntry(pBlock[row + col], sizeClass, 0, layer);
            pTilemap[mapX] = tile | pAttrs[row + col] << 10;
            mapX = (mapX + 1) & 0x1F;
            col++;
            if (col > 3)
            {
                col -= 4;
                pMap++;
                pBlock = pBlocks[*pMap];
                pAttrs = (u8 *)pBlocks + g_adwBgBlockAttrOffset[layer] + *pMap * 16;
            }
        }
    }
}
