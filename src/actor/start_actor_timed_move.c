#include "actor.h"

// Starts a move to the 16.16 position x/y over `ticks` calls of
// TickActorTimedMove.
void StartActorTimedMove(Actor *actor, s32 x, s32 y, u16 ticks)
{
    actor->moveTarget.x = x;
    actor->moveTarget.y = y;
    actor->wTimedMoveTicks = ticks;
}
