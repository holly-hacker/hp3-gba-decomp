#include "types.h"
#include "actor.h"
#include "hedwig_minigame.h"

void SpawnOwlThoughtBubble(u32 state)
{
    Actor *pBubble;

    pBubble = SpawnActor(15, 250, 30, g_aOwlThoughtBubbleSprites[state - OwlStateNeedFeed].pPalette);
    if (pBubble != NULL)
    {
        pBubble->pfnTick = TickOwlThoughtBubble;
        SetActorAnimData(pBubble, &g_aOwlThoughtBubbleSprites[state - OwlStateNeedFeed], g_abOwlThoughtBubbleAnim, 0);
        pBubble->dwFlags |= ActorFlagVisible;
    }
}
