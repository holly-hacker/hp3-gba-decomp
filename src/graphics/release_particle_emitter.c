#include "types.h"
#include "graphics.h"

// Drops the emitter's resource-cache reference, unlinks it from the
// active-particle-emitter list, and decrements the active count.
void ReleaseParticleEmitter_candidate(ParticleEmitter *emitter)
{
    DecrementResourceCacheRefcount(emitter->bResourceCacheSlot);
    List_MoveToHead(&g_pParticleEmitterFreeListHead, &g_pParticleEmitterActiveListHead, &emitter->node);
    g_wActiveParticleEmitterCount--;
}
