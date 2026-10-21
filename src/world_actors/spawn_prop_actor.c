#include "types.h"
#include "area.h"
#include "npc_actor.h"
#include "world_actors.h"

// Room actor constructor for tile actorType 5, a scripted prop whose kind selects
// its sprite and behavior. See docs/formats/rooms.md.
Actor *SpawnPropActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordProp *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_ScriptedTrigger);
    u32 kind;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = 0x04002215;
    SetActorActionState(pActor, 0);
    pActor->bUnk_0x7C = 5;
    pActor->anim.bAnimFrameDelay = 1;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->bKind = pRecord->bKind;
    kind = pRecord->bKind;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->b62 = pRecord->b62;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->bPushable = pRecord->bPushable;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->bBreakable = pRecord->bBreakable;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->b65 = pRecord->b65;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->b66 = pRecord->b66;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->bChainRow = pRecord->bChainRow;
    pActor->bFacing = pRecord->bFacing;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->bActivated = 0;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->b6A = 0;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->b60 &= 0xFD;
    pActor->pfnTick = TickPropActor;
    pActor->apfnCollisionCallback[0] = HandlePropActorTouch;
    pActor->apfnCollisionCallback[1] = HandlePropActorSecondaryTouch;
    SetActorPendingPalette(pActor, g_apRoomActorTriggerEffectData[ROOM_ACTOR_TRIGGER_STATE(pActor)->bKind]);
    SetActorAnimData(pActor, g_apRoomActorTriggerAnimFrames[ROOM_ACTOR_TRIGGER_STATE(pActor)->bKind],
                      (void *)g_abRoomActorTriggerAnimData[ROOM_ACTOR_TRIGGER_STATE(pActor)->bKind], 0);

    if (kind == 26 || kind == 27 || kind == 28 || kind == 29 || kind == 30
        || kind == 31 || kind == 32 || kind == 33 || kind == 34 || kind == 35
        || kind == 36 || kind == 37 || kind == 38)
    {
        if (kind == 26 || kind == 29)
            pActor->oam.priority = 1;
        else
            pActor->oam.priority = 3;

        pActor->dwFlags &= ~0x04000204;
    }
    else
    {
        pActor->oam.priority = 1;
    }

    pActor->bDepthSortBias = 0x80;
    ROOM_ACTOR_TRIGGER_STATE(pActor)->bBrokenFrame = 0xFF;

    switch (kind)
    {
    case 66:
        pActor->oam.priority = 0;
        pActor->dwFlags &= ~0x04000200;
        break;
    case 12:
        pActor->oam.priority = 3;
        pActor->oam.hFlip = pActor->bFacing > 4;
        pActor->dwFlags &= ~0x200;
        break;
    case 40:
        pActor->dwFlags &= ~4;
        // fall through
    case 39:
        pActor->oam.priority = 1;
        pActor->dwFlags &= ~0x200;
        break;
    case 0:
        SetActorAnimFrame(pActor, g_abRoomActorTriggerFacingFrames[pActor->bFacing]);
        pActor->oam.hFlip = pActor->bFacing > 4;
        pActor->pShadowActor = SpawnShadowActor(pActor);
        break;
    case 18:
    case 20:
        pActor->oam.objMode = 1;
        break;
    case 21:
        pActor->bDrawFlags |= ActorDrawFlagBlink;
        break;
    case 1:
        pActor->dwFlags |= 8;
        pActor->dwFlags &= ~0x04000000;
        break;
    case 81:
        pActor->dwFlags |= 8;
        pActor->dwFlags &= ~0x04000000;

        if (ROOM_ACTOR_TRIGGER_STATE(pActor)->bPushable == 0)
            SetActorAnimFrame(pActor, 1);

        break;
    case 82:
        pActor->dwFlags &= ~0x04000204;
        SetActorDrawLayer(pActor, 1);
        break;
    case 14:
    case 15:
    case 51:
    case 76:
        pActor->oam.priority = 3;
        pActor->bDepthSortBias = 0xFF;
        break;
    case 55:
        pActor->bDepthSortBias = 0xA0;
        break;
    }

    return pActor;
}
