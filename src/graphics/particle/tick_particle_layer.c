#include "types.h"
#include "graphics/graphics.h"

// Called per OAM priority so particles interleave with objects of that priority.
s8 TickParticleLayer(u8 priority)
{
    s32 result;
    s32 i;
    Particle *particle;
    Particle **entry;

    result = 0;
    if (g_abParticlesByPriorityCount[priority] == 0)
        return 0;
    for (i = g_abParticlesByPriorityCount[priority] - 1; i >= 0; i--) {
        entry = g_apParticlesByPriority[priority];
        entry += i;
        particle = *entry;
        result = TickParticle(particle);
        particle->wFlags &= ~ParticleEmitterFlagSkipTick;
    }
    return result;
}
