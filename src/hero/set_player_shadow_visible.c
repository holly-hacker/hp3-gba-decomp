#include "actor.h"
#include "hero.h"
#include "overworld/overworld.h"

void SetPlayerShadowVisible(u32 visible)
{
    if (visible == 1)
        g_pPlayerShadowActor->dwFlags |= ActorFlagVisible;
    else
        g_pPlayerShadowActor->dwFlags &= ~ActorFlagVisible;
}
