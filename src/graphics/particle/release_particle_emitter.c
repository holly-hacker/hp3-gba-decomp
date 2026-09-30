#include "types.h"
#include "graphics/graphics.h"

// Drops the emitter's resource-cache reference, unlinks it from the
// active-particle-emitter list, and decrements the active count.
void ReleaseParticleEmitter_candidate(ParticleEmitter *emitter)
{
    FreeParticleEmitter(emitter);
}
