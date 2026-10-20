#include "types.h"
#include "actor.h"
#include "hero.h"
#include "map.h"

// Restores only the player and the wandering monsters, for a return to the
// room after its story variant changed.
void RestoreRoomActorStateMinimal(void)
{
    RoomActorWanderingMonsterRecord *pMonster;
    u16 count;
    Actor *pActor;

    SnapActorPosition(g_pPlayerActor, g_pRoomActorStateBuffer->playerPos.x, g_pRoomActorStateBuffer->playerPos.y);
    g_pPlayerActor->bFacing = g_pRoomActorStateBuffer->bPlayerFacing;
    SetActorActionState(g_pPlayerActor, 0x21);
    SetActorPrevActionState(g_pPlayerActor, 0x21);
    SetActorActionSubState(g_pPlayerActor, 0);

    if (g_pRoomActorStateBuffer->bWanderingMonsterCount != 0)
    {
        pMonster = g_pRoomActorStateBuffer->aWanderingMonster;
        for (count = g_pRoomActorStateBuffer->bWanderingMonsterCount; count != 0; pMonster++, count--)
        {
            pActor = SpawnWanderingMonsterActor(pMonster->wMonsterId, pMonster->pos.x >> 16, pMonster->pos.y >> 16,
                pMonster->bEncounterId, pMonster->bEncounterVariant, pMonster->bKind);
            pActor->moveTarget = pMonster->moveTarget;
            pActor->vel = pMonster->vel;
            pActor->bFacing = pMonster->bFacing;
        }
    }

    ClearRoomActorStateBuffer();
}
