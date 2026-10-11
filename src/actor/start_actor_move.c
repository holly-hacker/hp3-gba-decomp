#include "actor.h"

void StartActorMove(Actor *actor, u32 x, u32 y, u16 mode)
{
    actor->moveTarget.x = x;
    actor->moveTarget.y = y;
    actor->wMoveDuration = mode + 1;
}
