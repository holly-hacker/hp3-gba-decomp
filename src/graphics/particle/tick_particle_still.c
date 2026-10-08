#include "types.h"
#include "graphics/graphics.h"

// Tick for ParticleModeStill: animation only.
void TickParticleStill(Particle *particle)
{
    if (++particle->wFrameCounter >= particle->bAnimTicks) {
        if (particle->bFrame < particle->pSprite->pHeader->wFrameCount - 1)
            particle->bFrame++;
        else if (particle->wFlags & ParticleEmitterFlagAnimTicksFixed)
            particle->bFrame = 0;
        particle->wFrameCounter = 0;
    }
}
