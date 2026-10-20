#include "actor.h"
#include "hero.h"

// dwStateTimer counts shown ticks; the popup slides down after 40 and hides after 54.
void TickMapNameActor(Actor *actor)
{
    if (actor->dwStateTimer != 0xFFFFFFFF)
    {
        if (++actor->dwStateTimer > 54)
        {
            actor->dwStateTimer = 0xFFFFFFFF;
            actor->dwFlags &= ~ActorFlagVisible;
            SetActorVelocity(actor, 0, 0);
        }
        else if (actor->dwStateTimer > 40)
            SetActorVelocity(actor, 0, 0x8000);
        else
            SetActorVelocity(actor, 0, 0);
    }
}
