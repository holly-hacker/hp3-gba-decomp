#include "particles.h"

// Ticks the emitters that follow actor now and sets ParticleEmitterFlagSkipTick on them, so
// TickParticleEmitters skips them this frame.
void TickActorParticleEmitters(struct Actor *actor)
{
    ParticleEmitter *emitter;
    ParticleEmitter *next;

    if (g_wActiveParticleEmitterCount != 0)
    {
        emitter = (ParticleEmitter *)g_pParticleEmitterActiveListHead;
        while (emitter != NULL)
        {
            next = (ParticleEmitter *)emitter->node.pNext;
            if (emitter->pTarget == actor)
            {
                TickParticleEmitter(emitter);
                emitter->wFlags |= ParticleEmitterFlagSkipTick;
            }
            emitter = next;
        }
        g_bParticleSpawnBlocked = 0;
    }
}
