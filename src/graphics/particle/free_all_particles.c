#include "types.h"
#include "graphics/graphics.h"

void FreeAllParticles(void)
{
    Particle *particle;
    Particle *next;

    if (g_wActiveParticleCount == 0)
        return;

    for (particle = (Particle *)g_pParticleActiveListHead; particle != NULL; particle = next)
    {
        next = (Particle *)particle->node.pNext;
        ReleaseParticle(particle);
    }
}
