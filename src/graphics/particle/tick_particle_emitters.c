#include "types.h"
#include "graphics/graphics.h"

// Ticks every active emitter once per frame and clears the per-frame flags. An emitter
// with ParticleEmitterFlagSkipTick set is not ticked this frame.
void TickParticleEmitters(void)
{
    ParticleEmitter *emitter;
    ParticleEmitter *next;

    if (g_wActiveParticleEmitterCount != 0)
    {
        emitter = (ParticleEmitter *)g_pParticleEmitterActiveListHead;
        while (emitter != NULL)
        {
            next = (ParticleEmitter *)emitter->node.pNext;
            if (!(emitter->wFlags & ParticleEmitterFlagSkipTick))
                TickParticleEmitter(emitter);
            emitter->wFlags &= ~ParticleEmitterFlagSkipTick;
            emitter = next;
        }
        g_bParticleSpawnBlocked = 0;
    }
}
