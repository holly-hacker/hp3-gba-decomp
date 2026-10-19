#include "types.h"
#include "particles.h"

// Runs every active particle not yet ticked this frame through TickParticle, and clears
// ParticleEmitterFlagSkipTick on all of them. Stops early, returning -1, when TickParticle
// does; otherwise returns the last result.
s8 TickAllParticles(void)
{
    Particle *particle;
    Particle *next;
    s32 result;

    result = 0;
    particle = (Particle *)g_pParticleActiveListHead;
    while (particle != NULL)
    {
        next = (Particle *)particle->node.pNext;
        if (!(particle->wFlags & ParticleEmitterFlagSkipTick))
        {
            result = TickParticle(particle);
            if (result == -1)
                return result;
        }
        particle->wFlags &= ~ParticleEmitterFlagSkipTick;
        particle = next;
    }
    return result;
}
