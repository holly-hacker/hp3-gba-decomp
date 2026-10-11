#include "actor.h"

// Writes the screen position UpdateActorOamCells last placed the actor at.
void GetActorOamPosition(Actor *actor, IntPoint *out)
{
    out->x = actor->oam.x;
    out->y = actor->oam.y;
}
