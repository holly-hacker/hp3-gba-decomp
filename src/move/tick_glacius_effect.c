#include "types.h"
#include "actor.h"
#include "move.h"
#include "particles.h"
#include "gen/graphics/overworld.h"

// pfnTick of a Glacius effect: flies like TickDiffindoEffect, trailing ice particles every
// third tick.
void TickGlaciusEffect(Actor *effect)
{
    ParticleEmitter *emitter;

    if (effect->bActionSubState == 3 && (u16)--effect->timer84.nFlightTicks == 0xFFFF)
    {
        effect->dwFlags &= ~ActorFlagWantsCollisionCheck;
        SetActorActionSubState(effect, 5);
    }

    switch (effect->bActionSubState)
    {
    case 0:
        effect->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate;
        effect->bTerrainBlockResponse = TerrainBlockEndFlight;
        effect->dwStateTimer = 45;
        SetActorActionSubState(effect, 3);
        emitter = AllocParticleEmitter((const ObjPalette *)gGlaciusEffectPalette, 2, 4);
        emitter->pTarget = effect;
        InitGlaciusParticleEmitter(emitter, effect);
        SetActorVelocityFromFacing(effect);
        break;
    case 3:
        if (effect->dwStateTimer != 0)
            effect->dwStateTimer--;
        if (effect->dwStateTimer % 3 == 0)
        {
            emitter = AllocParticleEmitter((const ObjPalette *)gGlaciusEffectPalette, 2, 4);
            emitter->pTarget = effect;
            InitGlaciusParticleEmitter(emitter, effect);
        }
        break;
    case 0x10:
        CancelActorMove_candidate(effect);
        SetActorActionSubState(effect, 0x12);
        break;
    case 5:
    case 0x11:
        CancelActorMove_candidate(effect);
        SetActorActionSubState(effect, 0x12);
        if (effect->timer84.nFlightTicks > 0)
            PlayFieldSpellHitSound(effect);
        break;
    case 0x12:
        EndFieldSpellEffect(effect);
        break;
    }
}
