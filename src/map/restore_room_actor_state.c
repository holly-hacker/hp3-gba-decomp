#include "types.h"
#include "actor.h"
#include "area.h"
#include "flipbook.h"
#include "hero.h"
#include "torch_actor.h"
#include "trigger_actor.h"
#include "world_actors.h"
#include "map.h"

// Respawns the room's saved actors from g_pRoomActorStateBuffer and writes
// their saved state back, then clears the buffer.
void RestoreRoomActorState(void)
{
    RoomActorKind4Or7Record *pKind4Or7;
    RoomActorDefaultRecord *pDefault;
    RoomActorKind5Record *pKind5;
    RoomActorFloorItemRecord *pFloorItem;
    RoomActorSwitchRecord *pSwitch;
    RoomActorPickupRecord *pPickup;
    RoomActorTileRecord *pPresence;
    RoomActorWanderingMonsterRecord *pMonster;
    u16 count;
    Actor *pActor;
    RoomTileAnimation *pTileAnim;

    SnapActorPosition(g_pPlayerActor, g_pRoomActorStateBuffer->playerPos.x, g_pRoomActorStateBuffer->playerPos.y);
    g_pPlayerActor->bFacing = g_pRoomActorStateBuffer->bPlayerFacing;
    g_bRoomSwitchState = g_pRoomActorStateBuffer->bSwitchState;
    SetActorActionState(g_pPlayerActor, 0x21);
    SetActorPrevActionState(g_pPlayerActor, 0x21);
    SetActorActionSubState(g_pPlayerActor, 0);
    g_bRestoringRoomActors_candidate = 1;

    if (g_pRoomActorStateBuffer->bKind4Or7Count != 0)
    {
        pKind4Or7 = g_pRoomActorStateBuffer->aKind4Or7;
        for (count = g_pRoomActorStateBuffer->bKind4Or7Count; count != 0; pKind4Or7++, count--)
        {
            pActor = SpawnRoomGroupMember(pKind4Or7->bTileCol, pKind4Or7->bTileRow);
            pActor->dwFlags = pKind4Or7->dwFlags;
            SetActorActionState(pActor, pKind4Or7->bActionState);
            pActor->dwStateTimer = pKind4Or7->dwStateTimer;
        }
    }

    if (g_pRoomActorStateBuffer->bDefaultCount != 0)
    {
        pDefault = g_pRoomActorStateBuffer->aDefault;
        for (count = g_pRoomActorStateBuffer->bDefaultCount; count != 0; pDefault++, count--)
        {
            pActor = SpawnRoomGroupMember(pDefault->bTileCol, pDefault->bTileRow);
            pActor->dwFlags |= pDefault->dwFlags;
            pActor->nMoveSpeed = pDefault->nMoveSpeed;
            pActor->wTimedMoveTicks = pDefault->wTimedMoveTicks;
            pActor->wActionVariant = pDefault->wActionVariant;
            pActor->bFacing = pDefault->bFacing;
            pActor->anim = pDefault->anim;
            *(RoomActorScriptBlock *)&pActor->scriptState = pDefault->script;
            pActor->moveTarget.x = pDefault->wMoveTargetX << 16;
            pActor->moveTarget.y = pDefault->wMoveTargetY << 16;
            SnapActorPosition(pActor, pDefault->wPosX << 16, pDefault->wPosY << 16);
            pActor->vel = pDefault->vel;
            SetActorActionState(pActor, pDefault->bActionState);
            SetActorActionSubState(pActor, pDefault->bActionSubState);
            pActor->bRoomActorKind_candidate = pDefault->bRoomActorKind;
            pActor->bFighterIndex = pDefault->bFighterIndex;
            pActor->dwStateTimer = pDefault->dwStateTimer;
        }
    }

    if (g_pRoomActorStateBuffer->bKind5Count != 0)
    {
        pKind5 = g_pRoomActorStateBuffer->aKind5;
        for (count = g_pRoomActorStateBuffer->bKind5Count; count != 0; pKind5++, count--)
        {
            pActor = SpawnRoomGroupMember(pKind5->bTileCol, pKind5->bTileRow);
            SetActorActionSubState(pActor, pKind5->bActionSubState);
            pActor->bDepthSortBias = pKind5->bDepthSortBias;
            pActor->dwFlags = pKind5->dwFlags;
            pActor->wTimedMoveTicks = pKind5->wTimedMoveTicks;
            pActor->anim = pKind5->anim;
            SnapActorPosition(pActor, pKind5->wPosX << 16, pKind5->wPosY << 16);
            pActor->vel = pKind5->vel;
            pActor->accel = pKind5->accel;
            pActor->modeState.actor.bRoomActorArg67_candidate = pKind5->bRoomActorArg67;
            pActor->scriptState.bytes.bAttackOutcomeState = pKind5->bScriptStateLow;
        }
    }

    pFloorItem = g_pRoomActorStateBuffer->aFloorItem;
    for (count = 0; count < g_pRoomActorStateBuffer->bFloorItemCount; pFloorItem++, count++)
    {
        pActor = SpawnRoomGroupMember(pFloorItem->bTileCol, pFloorItem->bTileRow);
        pTileAnim = FindRoomTileAnimation((s16)(pActor->pos.x >> 16), (s16)(pActor->pos.y >> 16));
        *pTileAnim = pFloorItem->tileAnim;
        RewindRoomTileAnimationStep(pTileAnim);
    }

    pSwitch = g_pRoomActorStateBuffer->aKind5Switch;
    for (count = 0; count < g_pRoomActorStateBuffer->bKind5SwitchCount; pSwitch++, count++)
    {
        pActor = SpawnRoomGroupMember(pSwitch->bTileCol, pSwitch->bTileRow);
        if (pSwitch->bConsumed)
            MarkRoomActorConsumed(pActor);
    }

    pPickup = g_pRoomActorStateBuffer->aPickupMarker;
    for (count = 0; count < g_pRoomActorStateBuffer->bPickupMarkerCount; pPickup++, count++)
    {
        pActor = SpawnRoomGroupMember(pPickup->bTileCol, pPickup->bTileRow);
        if (pPickup->bActionSubState == 8)
            GrantPickupMarkerItem(pActor);
        pActor->dwStateTimer = pPickup->bStateTimer + 1;
    }

    if (g_pRoomActorStateBuffer->bPresenceMarkerCount != 0)
    {
        pPresence = g_pRoomActorStateBuffer->aPresenceMarker;
        for (count = g_pRoomActorStateBuffer->bPresenceMarkerCount; count != 0; pPresence++, count--)
            SpawnRoomGroupMember(pPresence->bTileCol, pPresence->bTileRow);
    }

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
    g_bRestoringRoomActors_candidate = 0;
}
