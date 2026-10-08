#include "types.h"
#include "hw/mem.h"

// Clears tileCount OBJ tiles from firstTile in the pending-free mask; the tiles
// return to the allocator at the next ApplyDeferredObjTileFrees. firstTile 0xFFFF
// means no allocation.
void ClearObjTileFreeMaskBits(u16 firstTile, u16 tileCount)
{
    u32 end;
    u32 tile;
    u32 byteIndex;
    u32 bit;
    u32 mask;

    if (firstTile == 0xFFFF)
        return;

    end = firstTile + tileCount;
    tile = firstTile;
    while (tile < end) {
        byteIndex = tile >> 3;
        bit = tile & 7;
        if (bit == 0 && end - tile > 7) {
            mask = 0xFF;
            tile += 8;
        }
        else {
            mask = 1 << bit;
            tile++;
        }
        (g_abObjTileFreeMask)[byteIndex] &= ~mask;
    }
}
