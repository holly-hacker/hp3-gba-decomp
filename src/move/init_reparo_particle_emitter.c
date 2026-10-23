#include "types.h"
#include "actor.h"
#include "hero.h"
#include "move.h"
#include "particles.h"

void InitReparoParticleEmitter(ParticleEmitter *emitter)
{
    emitter->wSpawnPeriod = 0;
    emitter->wDuration = 1;
    emitter->wLifetimeBase = 20;
    emitter->wLifetimeRange = 5;
    emitter->wFlags = ParticleEmitterFlagRelease | ParticleEmitterFlagPriorityBelow;
    emitter->wSpread = 2;
    emitter->wSpawnTimer = 1;
    emitter->bMode = ParticleModeRandomSpeed;
    emitter->bSpawnsPerPeriod = 5;
    emitter->bParam43 = 0;
    emitter->bAnimTicks = 2;
    emitter->bDirection = g_pPlayerActor->bFacing;
    emitter->dwSpeed = 0x300;
}
