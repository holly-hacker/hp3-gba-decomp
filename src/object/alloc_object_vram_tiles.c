#include "types.h"
#include "hw/mem.h"
#include "graphics/object.h"

// Allocates a run of OBJ VRAM tiles large enough for pixelCount pixels and, when
// record is given, loads its tile sheet there. Returns the first tile, or 0xFFFF
// when no run is free.
u32 AllocObjectVramTiles(ObjectAssetRecord *record, u32 pixelCount, u32 is8bpp)
{
    u32 (*pfnFindFreeObjTileRun)(const u8 *, u32, u32) = FindFreeObjTileRunIwram;
    u32 tileCount;
    u32 firstTile;

    if (!is8bpp)
        tileCount = pixelCount / 64;
    else
        tileCount = pixelCount / 32;

    firstTile = pfnFindFreeObjTileRun(g_abObjTileAllocBitmap, tileCount, 0);
    if (firstTile != 0xFFFF) {
        MarkObjTilesInUse(firstTile, tileCount);
        if (record != NULL) {
            // Both pixel formats load through the 4bpp tile sheet loader.
            if (!is8bpp)
                LoadObjTileSheet(record, firstTile);
            else
                LoadObjTileSheet(record, firstTile);
        }
    }

    return firstTile;
}
