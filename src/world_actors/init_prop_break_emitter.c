#include "types.h"
#include "actor.h"
#include "particles.h"
#include "world_actors.h"

// Debris burst that follows a breaking prop.
void InitPropBreakEmitter(ParticleEmitter *pEmitter, Actor *pProp)
{
    pEmitter->pTarget = pProp;
    pEmitter->wSpawnPeriod = 1;
    pEmitter->wLifetimeBase = 10;
    pEmitter->wFlags = ParticleEmitterFlagRelease | ParticleEmitterFlagAnimTicksFixed
                     | ParticleEmitterFlagNoCollision | ParticleEmitterFlagPriorityBelow_candidate;
    pEmitter->wSpread = 8;
    pEmitter->wSpawnTimer = 0;
    pEmitter->bMode = ParticleModeRandomVelocity;
    pEmitter->bSpawnsPerPeriod = 2;
    pEmitter->wDuration = 1;
    pEmitter->bOamSize = 0;
    pEmitter->bParam43 = 0;
    pEmitter->bAnimTicks = 1;
    pEmitter->abVelRange[0] = -48;
    pEmitter->abVelRange[1] = 48;
    pEmitter->abVelRange[2] = 64;
    pEmitter->abVelRange[3] = 53;
    pEmitter->wParam38 = 0x1000;
}
