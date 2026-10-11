#include "types.h"
#include "actor.h"

void SetActorFacing(Actor *actor, u8 facing)
{
    if (actor->bFacing != facing)
    {
        actor->bFacing = facing;
        actor->bActionFlags |= 0x10;
    }
}
