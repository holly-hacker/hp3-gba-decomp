#include "types.h"
#include "actor.h"
#include "move.h"
#include "particles.h"
#include "gen/graphics/overworld.h"

// pfnTick of a Spongify effect: flies like TickDiffindoEffect, trailing particles every eighth
// tick.
void TickSpongifyEffect(Actor *effect)
{
    u32 spell = effect->wCharacterId_candidate;

    if (effect->bActionSubState == 3 && (u16)--effect->timer84.nFlightTicks == 0xFFFF)
    {
        effect->dwFlags &= ~ActorFlagWantsCollisionCheck;
        SetActorActionSubState(effect, 5);
    }

    switch (effect->bActionSubState)
    {
    case 0:
        effect->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate;
        effect->bUnk_0x7C = 4;
        effect->dwStateTimer = 45;
        SetActorActionSubState(effect, 3);
        InitSpongifyParticleEmitter0(AllocParticleEmitter((const ObjPalette *)gSpongifyEffectPalette, 2, 0), effect);
        InitSpongifyParticleEmitter1(AllocParticleEmitter((const ObjPalette *)gSpongifyEffectPalette, 2, 1), effect);
        SetActorVelocityFromFacing(effect);
        break;
    case 3:
        if (effect->dwStateTimer != 0)
            effect->dwStateTimer--;
        if ((effect->dwStateTimer & 7) == 0)
        {
            InitSpongifyParticleEmitter0(AllocParticleEmitter((const ObjPalette *)gSpongifyEffectPalette, 2, 0), effect);
            InitSpongifyParticleEmitter1(AllocParticleEmitter((const ObjPalette *)gSpongifyEffectPalette, 2, 1), effect);
        }
        break;
    case 0x10:
        CancelActorMove_candidate(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_abSpongifyHitAnim, 0);
        SetActorActionSubState(effect, 0x12);
        break;
    case 5:
    case 0x11:
        CancelActorMove_candidate(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_abSpongifyEndAnim, 0);
        SetActorActionSubState(effect, 0x12);
        FreeAllParticleEmitters();
        if (effect->timer84.nFlightTicks > 0)
            PlayFieldSpellHitSound(effect);
        break;
    case 0x12:
        if (effect->dwFlags & ActorFlagActionAnimDone)
            EndFieldSpellEffect(effect);
        break;
    case 2:
        if (g_dwFieldSpellActive == 0)
            EndFieldSpellEffect(effect);
        break;
    }
}
