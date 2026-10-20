#include "types.h"
#include "hw/io_regs.h"
#include "scroll.h"

// Loads `tileId` into the BG tile cache and writes it to tile (x, y) of BG `layer`'s tilemap, with
// the attribute byte of that tile within block `blockId` in bits 10+. No caller found.
void WriteBgTilemapEntry(u16 tileId, u32 sizeClass, u32 layer, u32 x, u32 y, u16 blockId)
{
    const u8 *pAttrs;
    u16 *pTilemap;
    u32 mapX;
    u32 tile;

    pAttrs = (u8 *)g_RoomBgBlockData.apBlockTiles[layer] + g_adwBgBlockAttrOffset[layer] + blockId * 16;
    pTilemap = (u16 *)((u8 *)VRAM_BASE + g_aBgControl[layer].bScreenBlock * 0x800);
    pTilemap += (y & 0x1F) * 32;
    mapX = x & 0x1F;
    tile = AcquireBgTileCacheEntry(tileId, sizeClass, 0, layer);
    pTilemap[mapX] = tile;
    pAttrs += (y & 3) * 4 + (x & 3);
    pTilemap[mapX] |= *pAttrs << 10;
}
