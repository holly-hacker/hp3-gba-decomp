#include "types.h"
#include "graphics/graphics.h"

void FreeAllParticleEmitters(void)
{
    ParticleEmitter *emitter;
    ParticleEmitter *next;

    if (g_wActiveParticleEmitterCount == 0)
        return;

    for (emitter = (ParticleEmitter *)g_pParticleEmitterActiveListHead; emitter != NULL; emitter = next)
    {
        next = (ParticleEmitter *)emitter->node.pNext;
        FreeParticleEmitter(emitter);
    }
}
