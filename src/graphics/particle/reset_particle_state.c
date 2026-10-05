#include "types.h"
#include "graphics/graphics.h"

// Marks every graphics pool entry as having no OBJ tile allocation and frees
// every live emitter and particle.
void ResetParticleState(void)
{
    u32 pool;
    u32 entry;

    for (pool = 0; pool < PARTICLE_GFX_POOL_COUNT; pool++)
    {
        for (entry = 0; entry < PARTICLE_GFX_POOL_SIZE; entry++)
            g_apParticleGfxPools[pool][entry].wTileAllocId |= 0xFFFF;
    }

    FreeAllParticleEmitters();
    FreeAllParticles();
}
