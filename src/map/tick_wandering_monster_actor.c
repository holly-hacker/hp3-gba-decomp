#include "types.h"
#include "actor.h"
#include "hero.h"
#include "math.h"
#include "move.h"
#include "random.h"
#include "map.h"

// pfnTick of a wandering monster: keeps it on its terrain, then in action
// state 15 roams to random targets or chases a walking player within 58 pixels.
void TickWanderingMonsterActor(Actor *pActor)
{
    u8 terrain;
    u8 direction;

    if (pActor->dwStateTimer != 0 && --pActor->dwStateTimer == 0)
        pActor->dwFlags |= ActorFlagWantsCollisionCheck;

    terrain = GetCollisionTypeAtPixel_candidate((PixelPoint){ (s16)(pActor->pos.x >> 16), (s16)(pActor->pos.y >> 16) });
    if (terrain != 0x1A && terrain != 0x20 && terrain != 0x21)
    {
        // Off its terrain: step back and turn around.
        pActor->posPrev = pActor->pos;
        SetActorActionSubState(pActor, 1);
        switch (pActor->bFacing)
        {
        case 0:
            SetActorMoveTarget(pActor, pActor->pos.x, pActor->pos.y + (Mt19937RandMax(16) << 16) + 0xC0000);
            pActor->bFacing = 2;
            SetActorFlippedX(pActor, 0);
            break;
        case 2:
            SetActorMoveTarget(pActor, pActor->pos.x, pActor->pos.y - (Mt19937RandMax(16) << 16) - 0xC0000);
            pActor->bFacing = 0;
            SetActorFlippedX(pActor, 0);
            break;
        case 1:
            // Unlike the other turns, leaves bFacing as it was. In action state 15 the
            // facing is recomputed from the new move target later in this tick.
            SetActorMoveTarget(pActor, pActor->pos.x - (Mt19937RandMax(16) << 16) - 0xC0000, pActor->pos.y);
            SetActorFlippedX(pActor, 1);
            break;
        case 3:
            SetActorMoveTarget(pActor, pActor->pos.x + (Mt19937RandMax(16) << 16) + 0xC0000, pActor->pos.y);
            pActor->bFacing = 1;
            SetActorFlippedX(pActor, 0);
            break;
        }
    }

    switch (pActor->bActionState)
    {
    case 0:
        break;
    case 15:
        if (pActor->bActionSubState == 0)
        {
            SetActorActionSubState(pActor, 1);
            ApproximateDistance(pActor->pos, g_pPlayerActor->pos);
            if (g_pPlayerActor->bActionState == 0x21 && (u32)ApproximateDistance(pActor->pos, g_pPlayerActor->pos) < 0x3A0000)
            {
                SetActorMoveTarget(pActor, g_pPlayerActor->pos.x, g_pPlayerActor->pos.y);
                pActor->bFlags_0x94_candidate |= 1;
            }
            else
                PickWanderingMonsterRoamTarget(pActor);
        }

        if ((s16)(pActor->pos.x >> 16) > (pActor->moveTarget.x >> 16) - 2
            && (s16)(pActor->pos.x >> 16) < (pActor->moveTarget.x >> 16) + 2
            && (s16)(pActor->pos.y >> 16) > (pActor->moveTarget.y >> 16) - 2
            && (s16)(pActor->pos.y >> 16) < (pActor->moveTarget.y >> 16) + 2)
        {
            PickWanderingMonsterRoamTarget(pActor);
            break;
        }

        direction = GetDirectionToTarget(pActor->dwFlags, pActor->pos, pActor->moveTarget, 0x10000);
        if (pActor->bFlags_0x94_candidate & 1)
        {
            pActor->vel.x = g_aDirection4Vectors[(s8)direction][0];
            pActor->vel.y = g_aDirection4Vectors[(s8)direction][1];
        }
        else
        {
            pActor->vel.x = g_aDirection4Vectors[(s8)direction][0] / 2;
            pActor->vel.y = g_aDirection4Vectors[(s8)direction][1] / 2;
        }
        if (pActor->bActionSubState == 0 || pActor->bFacing != (s8)direction)
            pActor->bFacing = direction;
        break;
    }
}
