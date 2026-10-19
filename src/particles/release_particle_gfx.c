#include "types.h"
#include "particles.h"
#include "vram.h"

// Frees the OBJ tiles of entry `entry` of graphics pool `pool`, if it has any.
void ReleaseParticleGfx(u32 pool, u32 entry)
{
    if (g_apParticleGfxPools[pool][entry].wTileAllocId != 0xFFFF)
    {
        FreeObjVramTileAllocation(g_apParticleGfxPools[pool][entry].wTileAllocId,
                                  g_apParticleGfxPools[pool][entry].wPixelCount, 0);
        g_apParticleGfxPools[pool][entry].wTileAllocId |= 0xFFFF;
    }
}
