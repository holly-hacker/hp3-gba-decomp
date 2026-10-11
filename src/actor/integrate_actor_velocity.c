#include "actor.h"

// Applies this tick's acceleration, then sets the pending position that
// TickActorList commits once collisions are resolved.
void IntegrateActorVelocity(Actor *actor)
{
    actor->vel.x += actor->accel.x;
    actor->vel.y += actor->accel.y;
    actor->posPrev.x = actor->pos.x + actor->vel.x;
    actor->posPrev.y = actor->pos.y + actor->vel.y;
}
