#include "types.h"
#include "math.h"
#include "actor.h"

// Returns the direction from actor to target, a Direction4 for an actor
// with ActorFlagFourWayDirections_candidate.
u8 GetDirectionToActor(Actor *actor, Actor *target)
{
    IntPoint from;
    IntPoint to;
    FixedPoint delta;

    FixedToIntPoint(actor->pos, &from);
    FixedToIntPoint(target->pos, &to);
    delta.x = to.x - from.x;
    delta.y = to.y - from.y;
    return GetDirectionFromVector(delta, actor->dwFlags & ActorFlagFourWayDirections_candidate);
}
