#include "types.h"
#include "math.h"
#include "actor.h"

// Returns the direction from source to actor (away from source); see
// GetDirectionToActor.
u8 GetDirectionFromActor(Actor *actor, Actor *source)
{
    IntPoint from;
    IntPoint to;
    FixedPoint delta;

    FixedToIntPoint(actor->pos, &to);
    FixedToIntPoint(source->pos, &from);
    delta.x = to.x - from.x;
    delta.y = to.y - from.y;
    return GetDirectionFromVector(delta, actor->dwFlags & ActorFlagFourWayDirections_candidate);
}
