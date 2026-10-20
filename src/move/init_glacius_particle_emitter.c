#include "types.h"
#include "actor.h"
#include "move.h"
#include "particles.h"

void InitGlaciusParticleEmitter(ParticleEmitter *emitter, Actor *effect)
{
    emitter->wSpawnPeriod = 0;
    emitter->wDuration = 1;
    emitter->wLifetimeBase = 17;
    emitter->wLifetimeRange = 10;
    emitter->wFlags = ParticleEmitterFlagRelease | ParticleEmitterFlagAnimTicksFixed;
    emitter->wSpread = 1;
    emitter->wSpawnTimer = 1;
    emitter->bMode = ParticleModeRandomSpeed;
    emitter->bSpawnsPerPeriod = 2;
    emitter->bParam43 = 0;
    emitter->bAnimTicks = 3;
    emitter->bDirection = 4;
    emitter->dwSpeed = 0x100;
}
