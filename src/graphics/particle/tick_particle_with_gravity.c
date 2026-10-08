#include "types.h"
#include "graphics/graphics.h"

// Tick for ParticleModeRandomVelocity. Frames last one tick longer than in
// TickParticleMoving.
void TickParticleWithGravity(Particle *particle)
{
    if (particle->wFrameCounter++ >= particle->bAnimTicks) {
        if (particle->bFrame < particle->pSprite->pHeader->wFrameCount - 1)
            particle->bFrame++;
        else if (particle->wFlags & ParticleEmitterFlagAnimTicksFixed)
            particle->bFrame = 0;
        particle->wFrameCounter = 0;
    }
    particle->nX += particle->nVelX;
    particle->nY += particle->nVelY;
    particle->nVelY += particle->wParam46 << 4;
}
