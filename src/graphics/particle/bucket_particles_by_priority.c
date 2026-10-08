#include "types.h"
#include "graphics/graphics.h"

// ParticleEmitterFlagSkipTick marks a particle as bucketed, so a
// ParticleEmitterFlagPriorityAbove particle lands only in its target's bucket.
void BucketParticlesByPriority(void)
{
    s32 priority;
    s32 count;
    Particle *particle;
    Particle *next;
    Particle **entry;

    for (priority = 0; priority <= 3; priority++) {
        count = 0;
        for (particle = (Particle *)g_pParticleActiveListHead; particle != NULL; particle = next) {
            next = (Particle *)particle->node.pNext;
            if (!(particle->wFlags & ParticleEmitterFlagSkipTick)
                && (particle->oam.priority == priority
                    || ((particle->wFlags & ParticleEmitterFlagPriorityAbove)
                        && particle->oam.priority - 1 == priority))) {
                entry = g_apParticlesByPriority[priority];
                entry += count;
                *entry = particle;
                count++;
                particle->wFlags |= ParticleEmitterFlagSkipTick;
            }
        }
        g_abParticlesByPriorityCount[priority] = count;
    }
}
