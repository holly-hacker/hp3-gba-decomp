#include "types.h"
#include "actor.h"
#include "hedwig_minigame.h"

// Follows 30 pixels above the owl until its animation ends.
void TickOwlThoughtBubble(Actor *pBubble)
{
    pBubble->pos.x = g_OwlCareKitScreen.pOwl->pos.x;
    pBubble->pos.y = g_OwlCareKitScreen.pOwl->pos.y - (30 << 16);
    if (pBubble->dwFlags & ActorFlagActionAnimDone)
        pBubble->dwFlags |= ActorFlagPendingDestroy;
}
