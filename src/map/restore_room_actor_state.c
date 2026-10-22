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
    RoomActorTriggerZoneRecord *pTriggerZone;
    RoomActorDefaultRecord *pDefault;
    RoomActorWorldActorRecord *pWorldActor;
    RoomActorTileAnimationRecord *pTileAnimation;
    RoomActorSwitchRecord *pSwitch;
    RoomActorFlamePillarRecord *pFlamePillar;
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

    if (g_pRoomActorStateBuffer->bTriggerZoneCount != 0)
    {
        pTriggerZone = g_pRoomActorStateBuffer->aTriggerZone;
        for (count = g_pRoomActorStateBuffer->bTriggerZoneCount; count != 0; pTriggerZone++, count--)
        {
            pActor = SpawnRoomGroupMember(pTriggerZone->bTileCol, pTriggerZone->bTileRow);
            pActor->dwFlags = pTriggerZone->dwFlags;
            SetActorActionState(pActor, pTriggerZone->bActionState);
            pActor->dwStateTimer = pTriggerZone->dwStateTimer;
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

    if (g_pRoomActorStateBuffer->bWorldActorCount != 0)
    {
        pWorldActor = g_pRoomActorStateBuffer->aWorldActor;
        for (count = g_pRoomActorStateBuffer->bWorldActorCount; count != 0; pWorldActor++, count--)
        {
            pActor = SpawnRoomGroupMember(pWorldActor->bTileCol, pWorldActor->bTileRow);
            SetActorActionSubState(pActor, pWorldActor->bActionSubState);
            pActor->bDepthSortBias = pWorldActor->bDepthSortBias;
            pActor->dwFlags = pWorldActor->dwFlags;
            pActor->wTimedMoveTicks = pWorldActor->wTimedMoveTicks;
            pActor->anim = pWorldActor->anim;
            SnapActorPosition(pActor, pWorldActor->wPosX << 16, pWorldActor->wPosY << 16);
            pActor->vel = pWorldActor->vel;
            pActor->accel = pWorldActor->accel;
            pActor->modeState.actor.bRoomActorArg67_candidate = pWorldActor->bRoomActorArg67;
            pActor->scriptState.bytes.bAttackOutcomeState = pWorldActor->bScriptStateLow;
        }
    }

    pTileAnimation = g_pRoomActorStateBuffer->aTileAnimation;
    for (count = 0; count < g_pRoomActorStateBuffer->bTileAnimationCount; pTileAnimation++, count++)
    {
        pActor = SpawnRoomGroupMember(pTileAnimation->bTileCol, pTileAnimation->bTileRow);
        pTileAnim = FindRoomTileAnimation((s16)(pActor->pos.x >> 16), (s16)(pActor->pos.y >> 16));
        *pTileAnim = pTileAnimation->tileAnim;
        RewindRoomTileAnimationStep(pTileAnim);
    }

    pSwitch = g_pRoomActorStateBuffer->aWorldActorSwitch;
    for (count = 0; count < g_pRoomActorStateBuffer->bWorldActorSwitchCount; pSwitch++, count++)
    {
        pActor = SpawnRoomGroupMember(pSwitch->bTileCol, pSwitch->bTileRow);
        if (pSwitch->bConsumed)
            MarkRoomActorConsumed(pActor);
    }

    pFlamePillar = g_pRoomActorStateBuffer->aFlamePillar;
    for (count = 0; count < g_pRoomActorStateBuffer->bFlamePillarCount; pFlamePillar++, count++)
    {
        pActor = SpawnRoomGroupMember(pFlamePillar->bTileCol, pFlamePillar->bTileRow);
        if (pFlamePillar->bActionSubState == 8)
            IgniteFlamePillar(pActor);
        pActor->dwStateTimer = pFlamePillar->bStateTimer + 1;
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
