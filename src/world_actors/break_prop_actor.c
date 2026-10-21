#include "types.h"
#include "actor.h"
#include "area.h"
#include "particles.h"
#include "sound.h"
#include "world_actors.h"
#include "gen/graphics/overworld.h"

// Plays a breakable prop's break animation and saves the frame Reparo restores. Kind 56
// only animates; the others also burst debris (action state 2 waits dwStateTimer ticks).
// The chain runs on the first break only.
void BreakPropActor(Actor *pActor)
{
    u8 kind = ROOM_ACTOR_TRIGGER_STATE(pActor)->bKind;

    PlaySoundById(0x20);

    if (kind == 56)
    {
        ROOM_ACTOR_TRIGGER_STATE(pActor)->bBrokenFrame = pActor->anim.bLastAnimFrameValue;
        SetActorAnimData(pActor, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 2);
    }
    else if (kind == 0)
    {
        ROOM_ACTOR_TRIGGER_STATE(pActor)->bBrokenFrame = pActor->anim.bLastAnimFrameValue;
        SetActorAnimData(pActor, g_apRoomActorTriggerAnimFrames[0], g_abRoomActorTriggerAnimData[0],
                         g_abRoomActorTriggerFacingAnimStart[pActor->bFacing]);
        LoadParticleGfx(1, 0, (const ActorAssetRecord *)&g_RoomPropParticleGfx0);
        LoadParticleGfx(1, 1, (const ActorAssetRecord *)&g_RoomPropParticleGfx1);
        LoadParticleGfx(1, 2, (const ActorAssetRecord *)&g_RoomPropParticleGfx2);
        InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 0), pActor);
        InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 1), pActor);
        InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 2), pActor);
        SetActorActionState(pActor, 2);
    }
    else
    {
        ROOM_ACTOR_TRIGGER_STATE(pActor)->bBrokenFrame = pActor->anim.bLastAnimFrameValue;
        SetActorAnimData(pActor, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 2);
        LoadParticleGfx(1, 0, (const ActorAssetRecord *)&g_RoomPropParticleGfx3);
        LoadParticleGfx(1, 1, (const ActorAssetRecord *)&g_RoomPropParticleGfx4);
        LoadParticleGfx(1, 2, (const ActorAssetRecord *)&g_RoomPropParticleGfx5);
        InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect028Palette, 1, 0), pActor);
        InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect028Palette, 1, 1), pActor);
        InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect028Palette, 1, 2), pActor);
        SetActorActionState(pActor, 2);
    }

    if (!(ROOM_ACTOR_TRIGGER_STATE(pActor)->b60 & 2))
    {
        if (ROOM_ACTOR_TRIGGER_STATE(pActor)->bChainRow != 0)
            RespawnGroupAndRunChain(0, ROOM_ACTOR_TRIGGER_STATE(pActor)->bChainRow);
        ROOM_ACTOR_TRIGGER_STATE(pActor)->b60 |= 2;
    }

    pActor->dwStateTimer = 35;
}
