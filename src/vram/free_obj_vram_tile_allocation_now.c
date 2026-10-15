#include "types.h"
#include "mem.h"
#include "actor.h"
#include "vram.h"

// Releases an allocation from AllocObjVramTiles at once, without waiting for
// the next ApplyDeferredObjTileFrees.
void FreeObjVramTileAllocationNow(u16 allocId, u32 pixelCount, u8 is8bpp)
{
    ClearObjTileAllocBits(allocId, (is8bpp ? pixelCount << 11 : pixelCount << 10) >> 16);
}
