#include "actor.h"

void FollowOwnerActor(Actor *actor)
{
    u32 x;
    u32 y;

    y = actor->pOwnerActor->posPrev.y;
    x = actor->pOwnerActor->posPrev.x;
    actor->posPrev.x = x;
    actor->posPrev.y = y;
    actor->oam.priority = actor->pOwnerActor->oam.priority;

    if (actor->bDrawFlags & ActorDrawFlagFollowBelow)
        actor->posPrev.y += 0x10000;
    else if (actor->bDrawFlags & ActorDrawFlagFollowAbove)
        actor->posPrev.y -= 0x10000;
}
