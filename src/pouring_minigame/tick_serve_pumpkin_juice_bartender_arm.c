#include "types.h"
#include "actor.h"
#include "pouring_minigame.h"

// Follows the bartender's action state with its own animation.
void TickServePumpkinJuiceBartenderArm(Actor *arm)
{
    switch (arm->pOwnerActor->bActionState)
    {
    case 4:
        arm->dwFlags = (arm->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    case 2:
        if (arm->bActionState != 2)
        {
            arm->bActionState = 2;
            SetActorAnimData(arm, &g_ServePumpkinJuiceBartenderArmSprite, g_aabServePumpkinJuiceBartenderArmAnims[1], 0);
        }
        break;
    case 1:
    case 17:
        arm->dwFlags |= ActorFlagVisible;
        if (arm->bActionState != 1)
        {
            arm->bActionState = 1;
            SetActorAnimData(arm, &g_ServePumpkinJuiceBartenderArmSprite, g_aabServePumpkinJuiceBartenderArmAnims[0], 0);
        }
        break;
    case 16:
        arm->dwFlags |= ActorFlagVisible;
        if (arm->bActionState != 16)
        {
            arm->bActionState = 16;
            SetActorAnimData(arm, &g_ServePumpkinJuiceBartenderArmSprite, g_aabServePumpkinJuiceBartenderArmAnims[2], 0);
        }

        if (arm->pOwnerActor->pLinkedActor_candidate != NULL)
            arm->dwFlags &= ~ActorFlagVisible;
        break;
    default:
        arm->bActionState = 0;
        arm->dwFlags &= ~ActorFlagVisible;
        break;
    }
}
