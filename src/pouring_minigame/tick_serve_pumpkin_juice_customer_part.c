#include "types.h"
#include "actor.h"
#include "pouring_minigame.h"

// Mirrors the customer's action state: hidden while waiting or walking (shown again once a
// type 6 customer switches to its variant walk), shown while drinking.
void TickServePumpkinJuiceCustomerPart(Actor *part)
{
    switch (part->pOwnerActor->bActionState)
    {
    case 0:
        if (part->bActionState != 0)
        {
            part->dwFlags &= ~ActorFlagVisible;
            SetActorAnimData(part, g_aapServePumpkinJuiceCustomerSpriteRows[part->wSubtype][1],
                             g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimWalk], 0);
            part->wActionVariant = 0;
            part->bActionState = 0;
        }

        if (part->pOwnerActor->wActionVariant == 1 && part->wActionVariant == 0)
        {
            part->dwFlags |= ActorFlagVisible;
            SetActorAnimData(part, g_aapServePumpkinJuiceCustomerSpriteRows[part->wSubtype][1],
                             g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimWalkVariant + 1], 0);
            part->wActionVariant = 1;
        }
        break;
    case 1:
        if (part->bActionState != 1)
        {
            part->dwFlags &= ~ActorFlagVisible;
            SetActorAnimData(part, g_aapServePumpkinJuiceCustomerSpriteRows[part->wSubtype][1],
                             g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimWalk], 0);
            part->bActionState = 1;
            part->wActionVariant = 0;
        }

        if (part->pOwnerActor->wActionVariant == 1 && part->wActionVariant == 0)
        {
            part->dwFlags |= ActorFlagVisible;
            SetActorAnimData(part, g_aapServePumpkinJuiceCustomerSpriteRows[part->wSubtype][1],
                             g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimWalkVariant + 1], 0);
            part->wActionVariant = 1;
        }
        break;
    case 2:
        if (part->bActionState != 2)
        {
            part->dwFlags |= ActorFlagVisible;
            if (part->wSubtype == 6)
                SetActorAnimData(part, g_aapServePumpkinJuiceCustomerSpriteRows[part->wSubtype][1],
                                 g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimDrinkVariant], 0);
            else
                SetActorAnimData(part, g_aapServePumpkinJuiceCustomerSpriteRows[part->wSubtype][1],
                                 g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimDrink], 0);

            part->bActionState = 2;
            part->wActionVariant = 0;
        }
        break;
    case 4:
        part->dwFlags = (part->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    }
}
