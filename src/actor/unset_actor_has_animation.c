#include "actor.h"

void UnsetActorHasAnimation(Actor *actor)
{
    actor->dwFlags &= ~ActorFlagHasAnimation;
}
