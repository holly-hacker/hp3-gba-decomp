#include "actor.h"

void CancelActorMove_candidate(Actor *actor)
{
    actor->accel.x = 0;
    actor->accel.y = 0;
    actor->vel.x = 0;
    actor->vel.y = 0;
}
