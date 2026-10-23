#include "lupin_potion_cutscene.h"

// Follows the owner's walk cycle, whose frames start at 9.
void TickLupinPotionShadowActor(Actor *pActor)
{
    u8 *pOwnerFrame = &pActor->pOwnerActor->anim.bLoadedAnimFrame;

    if (*pOwnerFrame <= 8)
        SetActorAnimFrame(pActor, 0);
    else
        SetActorAnimFrame(pActor, (*pOwnerFrame - 8) % 8);
}
