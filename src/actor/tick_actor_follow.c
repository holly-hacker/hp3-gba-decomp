#include "types.h"
#include "math.h"
#include "actor.h"
#include "actor_inline.h"

// Action state 0x12: follows pShadowActor (see RoomScriptOpSetTileActorFollowTarget),
// stopping within bFollowStopDistance and walking again once farther than both distances.
void TickActorFollow(Actor *actor)
{
    u8 facing;
    u8 subState;
    FixedPoint pos;
    FixedPoint target;
    s32 distance;
    u8 resumeDistance;
    u8 stopDistance;
    Actor *leader;
    u8 direction;

    facing = actor->bFacing;
    subState = actor->bActionSubState;
    leader = actor->pShadowActor;
    pos = actor->pos;
    target = leader->pos;
    distance = ApproximateDistance(pos, target);
    distance >>= 16;
    resumeDistance = actor->modeState.actor.bFollowResumeDistance;
    stopDistance = actor->modeState.actor.bFollowStopDistance;

    switch (subState) {
    case 3:
        if (distance < stopDistance)
            SetActorActionSubState(actor, 6);
        direction = GetDirectionToTarget(actor->dwFlags, pos, target, actor->nMoveSpeed);
        if (((actor->dwFlags & ActorFlagFourWayDirections_candidate) && direction == Direction4None)
            || direction == DirectionNone) {
            SetActorActionSubState(actor, 6);
        }
        else if (direction != facing) {
            actor->bFacing = direction;
            actor->bActionFlags |= 0x10;
        }
        break;
    case 6:
        if (resumeDistance > distance && distance > stopDistance)
            SetActorActionSubState(actor, 3);
        break;
    default:
        TickActorIdle(actor);
        break;
    }
}
