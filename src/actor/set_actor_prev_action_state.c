#include "actor.h"

void SetActorPrevActionState(Actor *actor, u8 state)
{
    actor->bPrevActionState_candidate = state;
}
