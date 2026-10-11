#include "types.h"
#include "hw/mem.h"
#include "actor.h"
#include "vram.h"

// Releases an allocation from AllocObjectVramTiles at once, without waiting for
// the next ApplyDeferredObjTileFrees.
void FreeObjectVramTileAllocationNow(u16 allocId, u32 pixelCount, u8 is8bpp)
{
    ClearObjTileAllocBits(allocId, (is8bpp ? pixelCount << 11 : pixelCount << 10) >> 16);
}
