#include "types.h"
#include "hw/io_regs.h"
#include "overworld/room.h"

// Replaces the 32x32-pixel block covering pixel (x, y) on BG `layer` with block `blockId`.
// Each of the block's 4x4 tiles inside the loaded tile window releases the old block's tile
// from the tile cache; each tile inside the loaded or the current window then loads the new
// block's tile and writes it, with the block's attribute byte in bits 10+, to the layer's
// tilemap. The block map entry is overwritten with `blockId`.
void WriteRoomBgTile_candidate(u16 x, u16 y, u16 blockId, u8 layer)
{
    u16 *pBlockEntry;
    u32 col;
    u32 loadedLeft;
    u32 loadedTop;
    u32 scrollLeft;
    u32 scrollTop;
    const u16 *pOldTile;
    u32 sizeClass;
    u16 oldBlockId;
    u32 oldOffset;
    const u16 *pNewTile;
    u32 row;

    pBlockEntry = GetRoomBgBlockMapEntryPtr(x, y, layer);
    oldBlockId = ((u32)*pBlockEntry << 21) >> 21;
    oldOffset = oldBlockId * 32;
    sizeClass = ((layer + 1) & 2) >> 1;
    pOldTile = (const u16 *)((u8 *)g_RoomBgBlockData.apBlockTiles[layer] + oldOffset);
    pNewTile = g_RoomBgBlockData.apBlockTiles[layer][blockId];

    // Pixel position to the block's first tile.
    x >>= 5;
    x <<= 2;
    y >>= 5;
    y <<= 2;
    loadedLeft = g_BgLoadedScroll[0] >> 3;
    loadedTop = g_BgLoadedScroll[1] >> 3;
    scrollLeft = g_BgScroll[0] >> 3;
    scrollTop = g_BgScroll[1] >> 3;

    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 4; col++)
        {
            if (x >= loadedLeft && x < loadedLeft + 0x1F && y >= loadedTop
                && y < loadedTop + 0x15)
            {
                u16 tileId;
                const u8 *pAttrs;
                u16 *pTilemap;
                u32 mapX;
                u32 tile;

                ReleaseBgTileCacheEntry(*pOldTile, sizeClass, layer);
                tileId = *pNewTile;
                pAttrs = (u8 *)g_RoomBgBlockData.apBlockTiles[layer]
                         + g_adwBgBlockAttrOffset[layer] + blockId * 16;
                pTilemap = (u16 *)((u8 *)VRAM_BASE + g_aBgControl[layer].bScreenBlock * 0x800);
                pTilemap += (y & 0x1F) * 32;
                mapX = x & 0x1F;
                tile = DecompressBgTileToVram_candidate(tileId, sizeClass, 0, layer);
                pTilemap[mapX] = tile;
                pAttrs += (y & 3) * 4 + (x & 3);
                pTilemap[mapX] |= *pAttrs << 10;
            }
            else if (x >= scrollLeft && x < scrollLeft + 0x1F && y >= scrollTop
                     && y < scrollTop + 0x15)
            {
                u16 tileId;
                const u8 *pAttrs;
                u16 *pTilemap;
                u32 mapX;
                u32 tile;

                tileId = *pNewTile;
                pAttrs = (u8 *)g_RoomBgBlockData.apBlockTiles[layer]
                         + g_adwBgBlockAttrOffset[layer] + blockId * 16;
                pTilemap = (u16 *)((u8 *)VRAM_BASE + g_aBgControl[layer].bScreenBlock * 0x800);
                pTilemap += (y & 0x1F) * 32;
                mapX = x & 0x1F;
                tile = DecompressBgTileToVram_candidate(tileId, sizeClass, 0, layer);
                pTilemap[mapX] = tile;
                pAttrs += (y & 3) * 4 + (x & 3);
                pTilemap[mapX] |= *pAttrs << 10;
            }
            x++;
            pOldTile++;
            pNewTile++;
        }
        x -= 4;
        y++;
    }

    *pBlockEntry = blockId;
}
