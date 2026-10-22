#include "types.h"
#include "actor.h"
#include "move.h"
#include "particles.h"

void InitSpongifyParticleEmitter0(ParticleEmitter *emitter, Actor *effect)
{
    emitter->pTarget = effect;
    emitter->wSpawnPeriod = 0;
    emitter->wDuration = 1;
    emitter->wLifetimeBase = 20;
    emitter->wLifetimeRange = 10;
    emitter->wFlags = ParticleEmitterFlagRelease | ParticleEmitterFlagUnused10;
    emitter->wSpread = 5;
    emitter->wSpawnTimer = 1;
    emitter->bMode = ParticleModeRandomSpeed;
    emitter->bSpawnsPerPeriod = 2;
    emitter->bParam43 = 0;
    emitter->bAnimTicks = 1;
    emitter->bDirection = effect->bFacing;
    emitter->dwSpeed = 0x200;
}
