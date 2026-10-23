#include "types.h"
#include "actor.h"
#include "random.h"
#include "map.h"

void PickWanderingMonsterRoamTarget(Actor *pActor)
{
    u32 blocked = 1;
    u32 direction;

    do
    {
        pActor->bTypeFlags = 0;
        direction = Mt19937RandMax(3);
        switch (direction)
        {
        case 0:
            blocked = TrySetWanderingMonsterMoveTarget(pActor, pActor->pos.x, pActor->pos.y - (Mt19937RandMax(16) << 16) - 0x40000);
            pActor->bFacing = direction;
            SetActorFlippedX(pActor, 0);
            break;
        case 2:
            blocked = TrySetWanderingMonsterMoveTarget(pActor, pActor->pos.x, pActor->pos.y + (Mt19937RandMax(16) << 16) + 0x40000);
            pActor->bFacing = direction;
            SetActorFlippedX(pActor, 0);
            break;
        case 1:
            blocked = TrySetWanderingMonsterMoveTarget(pActor, pActor->pos.x + (Mt19937RandMax(16) << 16) + 0x40000, pActor->pos.y);
            pActor->bFacing = direction;
            SetActorFlippedX(pActor, 0);
            break;
        case 3:
            blocked = TrySetWanderingMonsterMoveTarget(pActor, pActor->pos.x - (Mt19937RandMax(16) << 16) - 0x40000, pActor->pos.y);
            pActor->bFacing = direction;
            SetActorFlippedX(pActor, 1);
            break;
        }
    } while (blocked);
}
