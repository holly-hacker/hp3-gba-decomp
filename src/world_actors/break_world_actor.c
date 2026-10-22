#include "types.h"
#include "actor.h"
#include "area.h"
#include "particles.h"
#include "sound.h"
#include "world_actors.h"
#include "gen/graphics/overworld.h"

// Plays a breakable world actor's break animation and saves the frame Reparo restores. Kind 56
// only animates; the others also burst debris (action state 2 waits dwStateTimer ticks).
// The chain runs on the first break only.
void BreakWorldActor(Actor *pActor)
{
    u8 kind = WORLD_ACTOR_STATE(pActor)->bKind;

    PlaySoundById(0x20);

    if (kind == 56)
    {
        WORLD_ACTOR_STATE(pActor)->bBrokenFrame = pActor->anim.bLastAnimFrameValue;
        SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 2);
    }
    else if (kind == 0)
    {
        WORLD_ACTOR_STATE(pActor)->bBrokenFrame = pActor->anim.bLastAnimFrameValue;
        SetActorAnimData(pActor, g_apWorldActorAnimFrames[0], g_abWorldActorAnimData[0],
                         g_abWorldActorFacingAnimStart[pActor->bFacing]);
        LoadParticleGfx(1, 0, (const ActorAssetRecord *)&g_WorldActorParticleGfx0);
        LoadParticleGfx(1, 1, (const ActorAssetRecord *)&g_WorldActorParticleGfx1);
        LoadParticleGfx(1, 2, (const ActorAssetRecord *)&g_WorldActorParticleGfx2);
        InitWorldActorBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 0), pActor);
        InitWorldActorBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 1), pActor);
        InitWorldActorBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 2), pActor);
        SetActorActionState(pActor, 2);
    }
    else
    {
        WORLD_ACTOR_STATE(pActor)->bBrokenFrame = pActor->anim.bLastAnimFrameValue;
        SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 2);
        LoadParticleGfx(1, 0, (const ActorAssetRecord *)&g_WorldActorParticleGfx3);
        LoadParticleGfx(1, 1, (const ActorAssetRecord *)&g_WorldActorParticleGfx4);
        LoadParticleGfx(1, 2, (const ActorAssetRecord *)&g_WorldActorParticleGfx5);
        InitWorldActorBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect028Palette, 1, 0), pActor);
        InitWorldActorBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect028Palette, 1, 1), pActor);
        InitWorldActorBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect028Palette, 1, 2), pActor);
        SetActorActionState(pActor, 2);
    }

    if (!(WORLD_ACTOR_STATE(pActor)->b60 & 2))
    {
        if (WORLD_ACTOR_STATE(pActor)->bChainRow != 0)
            RespawnGroupAndRunChain(0, WORLD_ACTOR_STATE(pActor)->bChainRow);
        WORLD_ACTOR_STATE(pActor)->b60 |= 2;
    }

    pActor->dwStateTimer = 35;
}
