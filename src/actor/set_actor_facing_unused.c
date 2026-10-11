#include "types.h"
#include "actor.h"

// Byte-identical to SetActorFacing; no callers found anywhere in the ROM.
void SetActorFacing_unused(Actor *actor, u8 facing)
{
    if (actor->bFacing != facing)
    {
        actor->bFacing = facing;
        actor->bActionFlags |= 0x10;
    }
}
