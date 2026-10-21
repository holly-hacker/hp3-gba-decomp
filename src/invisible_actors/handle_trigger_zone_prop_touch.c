#include "types.h"
#include "world_actors.h"
#include "invisible_actors.h"

// Collision callback of a kind 2 trigger zone's second box: a prop (room actor
// type 5) whose record byte 0x0F is nonzero fires the zone when it touches it
// and is snapped to the zone's 8-pixel cell and stopped there.
void HandleTriggerZonePropTouch(Actor *pSelf, Actor *pOther)
{
    s32 x;
    s32 y;

    if (pOther->wActorType == RoomActorType_ScriptedTrigger && ROOM_ACTOR_TRIGGER_STATE(pOther)->bPushable != 0)
    {
        SetActorActionState(pSelf, 5);
        pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        x = (s16)(pSelf->pos.x >> 16);
        y = (s16)(pSelf->pos.y >> 16);
        x &= ~7;
        y &= ~7;
        x -= pOther->aCollisionBoxes[1].offsets.edges.bLeft;
        y -= pOther->aCollisionBoxes[1].offsets.edges.bTop;
        SetActorPosition(pOther, x - 2, y - 2);
        SetActorVelocity(pOther, 0, 0);
        pOther->dwFlags |= ActorFlagNoPushTrigger_candidate;
        pOther->bDepthSortBias = 0xFF;
    }
}
