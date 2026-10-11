#include "types.h"
#include "math.h"
#include "actor.h"
#include "actor_inline.h"

// An unused simpler form of TickActorFollow: walks toward pShadowActor while farther
// than bFollowResumeDistance and stops once closer.
void TickActorFollowSimple(Actor *actor)
{
    u8 facing;
    u8 subState;
    FixedPoint pos;
    FixedPoint target;
    s32 distance;
    u8 direction;
    Actor *leader;
    u8 resumeDistance;

    facing = actor->bFacing;
    subState = actor->bActionSubState;
    leader = actor->pShadowActor;
    pos = actor->pos;
    target = leader->pos;
    distance = ApproximateDistance(pos, target);
    distance >>= 16;
    resumeDistance = actor->modeState.actor.bFollowResumeDistance;

    if (resumeDistance > distance && subState != 3)
        SetActorActionSubState(actor, 3);
    else if (resumeDistance < distance && subState != 6)
        SetActorActionSubState(actor, 6);

    switch (subState) {
    case 3:
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
        break;
    default:
        TickActorIdle(actor);
        break;
    }
}
