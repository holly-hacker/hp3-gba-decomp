#include "types.h"
#include "hw/mem.h"

// Marks tileCount OBJ tiles from firstTile as in use. Whole aligned bytes
// are set at once.
void MarkObjTilesInUse(u16 firstTile, u16 tileCount)
{
    u32 end = firstTile + tileCount;
    u32 tile = firstTile;
    u32 byteIndex;
    u32 bit;
    u32 mask;

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
        (g_abObjTileAllocBitmap)[byteIndex] |= mask;
    }
}
