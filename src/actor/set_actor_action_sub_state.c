#include "actor.h"

void SetActorActionSubState(Actor *actor, u8 state)
{
    if (actor->bActionSubState != state) {
        actor->bActionSubState = state;
        actor->bActionFlags |= 0x2;
    }
}
