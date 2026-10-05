#include "types.h"
#include "hw/mem.h"
#include "graphics/graphics.h"

void InitResourceCachePools(void)
{
    s32 i;

    g_aParticles = AllocZeroed(MAX_PARTICLES * sizeof(Particle));
    g_aParticleEmitters = AllocZeroed(MAX_PARTICLE_EMITTERS * sizeof(ParticleEmitter));
    g_pParticleFreeListHead = BuildFreeList(g_aParticles, MAX_PARTICLES, sizeof(Particle));
    g_pParticleEmitterFreeListHead =
        BuildFreeList(g_aParticleEmitters, MAX_PARTICLE_EMITTERS, sizeof(ParticleEmitter));

    for (i = 0; i < ARRAY_COUNT(g_apParticlesByPriority); i++)
        g_apParticlesByPriority[i] = AllocZeroed(MAX_PARTICLES * sizeof(Particle *));

    for (i = 0; i < PARTICLE_GFX_POOL_COUNT; i++)
        g_apParticleGfxPools[i] = AllocZeroed(PARTICLE_GFX_POOL_SIZE * sizeof(ParticleGfxEntry));

    ResetParticleState();
}
