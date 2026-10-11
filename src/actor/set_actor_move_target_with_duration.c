#include "actor.h"

// Sets the move target in whole pixels and the move duration in ticks.
void SetActorMoveTargetWithDuration(Actor *actor, s32 x, s32 y, u16 duration)
{
    x <<= 16;
    y <<= 16;
    actor->moveTarget.x = x;
    actor->moveTarget.y = y;
    actor->wMoveDuration = duration + 1;
}
