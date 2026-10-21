#include "types.h"
#include "actor.h"
#include "math.h"
#include "particles.h"
#include "spongify_pad_actor.h"

// The caller sets pTarget.
void InitSpongifyPadParticleEmitter0(ParticleEmitter *pEmitter, Actor *pEffect)
{
    pEmitter->wSpawnPeriod = 0;
    pEmitter->wDuration = 1;
    pEmitter->wLifetimeBase = 20;
    pEmitter->wLifetimeRange = 10;
    pEmitter->wFlags = ParticleEmitterFlagRelease | 0x10;
    pEmitter->wSpread = 5;
    pEmitter->wSpawnTimer = 1;
    pEmitter->bMode = ParticleModeRandomSpeed;
    pEmitter->bSpawnsPerPeriod = 2;
    pEmitter->bParam43 = 0;
    pEmitter->bAnimTicks = 1;
    pEmitter->bDirection = DirectionDown;
    pEmitter->dwSpeed = 0x200;
}
