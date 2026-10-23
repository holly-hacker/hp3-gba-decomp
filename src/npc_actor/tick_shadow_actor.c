#include "types.h"
#include "npc_actor.h"

// While its owner moves, cycles the shadow through its 8 frames every 3 ticks.
void TickShadowActor(Actor *pShadow)
{
    Actor *pOwner = pShadow->pOwnerActor;

    if (pOwner->vel.x != 0 || pOwner->vel.y != 0)
    {
        if (pShadow->dwStateTimer != 0)
        {
            pShadow->dwStateTimer--;
        }
        else
        {
            u32 frame = (pShadow->anim.bLoadedAnimFrame + 1) & 7;

            pShadow->dwStateTimer = 2;
            SetActorAnimFrame(pShadow, frame);
        }

        pShadow->oam.priority = pOwner->oam.priority;
    }
}
