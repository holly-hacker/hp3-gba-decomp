#include "types.h"
#include "vram.h"

// Releases an allocation from AllocObjVramTiles. The tiles go back to the
// allocator at the next ApplyDeferredObjTileFrees.
void FreeObjVramTileAllocation(u16 allocId, u32 pixelCount, u8 is8bpp)
{
    u32 tileCount = pixelCount / 64;

    if (is8bpp)
        tileCount = pixelCount / 32;

    ClearObjTileFreeMaskBits(allocId, tileCount);
}
