#include "types.h"
#include "actor.h"
#include "combat_fighter.h"
#include "combat.h"

// Mirrors the battle screen shake on a monster and, for monsters 45-47, its
// shadow: flipped for the first half of the shake, unflipped for the second,
// and restored on its last frame.
void FlipMonsterForIntroSweep(Actor *actor)
{
    if (g_pFightState->bIntroSweepTimer == 0)
        return;

    if (g_pFightState->bIntroSweepTimer == 1)
    {
        actor->oam.objMode = 0;
        ClearActorOrbit(actor);
        if (IS_SALAMANDER(actor->wActorType - 4))
            ClearActorOrbit(actor->pShadowActor);
    }
    else if (g_pFightState->bIntroSweepTimer > 0xF)
    {
        SetActorFlippedX(actor, 1);
        if (IS_SALAMANDER(actor->wActorType - 4))
            SetActorFlippedX(actor->pShadowActor, 1);
    }
    else
    {
        SetActorFlippedX(actor, 0);
        if (IS_SALAMANDER(actor->wActorType - 4))
            SetActorFlippedX(actor->pShadowActor, 0);
    }
}
