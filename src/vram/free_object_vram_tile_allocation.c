#include "types.h"
#include "hw/mem.h"
#include "actor.h"
#include "vram.h"

// Releases an allocation from AllocObjectVramTiles. The tiles go back to the
// allocator at the next ApplyDeferredObjTileFrees.
void FreeObjectVramTileAllocation(u16 allocId, u32 pixelCount, u8 is8bpp)
{
    u32 tileCount = pixelCount / 64;

    if (is8bpp)
        tileCount = pixelCount / 32;

    ClearObjTileFreeMaskBits(allocId, tileCount);
}
