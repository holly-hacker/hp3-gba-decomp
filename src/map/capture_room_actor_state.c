#include "types.h"
#include "actor.h"
#include "area.h"
#include "flipbook.h"
#include "hero.h"
#include "mem.h"
#include "world_actors.h"
#include "map.h"

// Records the player and every room actor that differs from its default
// state into g_pRoomActorStateBuffer.
void CaptureRoomActorState(void)
{
    Actor *pActor;
    RoomActorRecordWorldActor *pStatic;
    RoomActorFlamePillarRecord *pFlamePillar;
    RoomActorTileAnimationRecord *pTileAnimation;
    RoomActorTriggerZoneRecord *pTriggerZone;
    RoomActorSwitchRecord *pSwitch;
    RoomActorWorldActorRecord *pWorldActor;
    RoomActorTileRecord *pPresence;
    RoomActorDefaultRecord *pDefault;
    RoomActorWanderingMonsterRecord *pMonster;

    memset(g_pRoomActorStateBuffer, 0, ROOM_ACTOR_STATE_BUFFER_SIZE);
    g_pRoomActorStateBuffer->playerPos = g_pPlayerActor->pos;
    g_pRoomActorStateBuffer->bPlayerFacing = g_pPlayerActor->bFacing;
    g_pRoomActorStateBuffer->bSwitchState = g_bRoomSwitchState;

    for (pActor = (Actor *)g_ActiveActorListState.pHead; pActor != NULL; pActor = (Actor *)pActor->node.pNext)
    {
        if (pActor->bRoomRecordCol != 0xFF)
        {
            pStatic = GetRoomActorStaticRecord(pActor->bRoomRecordCol, pActor->bRoomRecordRow);
            switch (pActor->wActorType)
            {
            case RoomActorType_FlamePillar:
                pFlamePillar = &g_pRoomActorStateBuffer->aFlamePillar[g_pRoomActorStateBuffer->bFlamePillarCount++];
                pFlamePillar->bTileCol = pActor->bRoomRecordCol;
                pFlamePillar->bTileRow = pActor->bRoomRecordRow;
                pFlamePillar->bStateTimer = pActor->dwStateTimer;
                pFlamePillar->bActionSubState = pActor->bActionSubState;
                break;
            case RoomActorType_TileAnimation:
                pTileAnimation = &g_pRoomActorStateBuffer->aTileAnimation[g_pRoomActorStateBuffer->bTileAnimationCount++];
                pTileAnimation->bTileCol = pActor->bRoomRecordCol;
                pTileAnimation->bTileRow = pActor->bRoomRecordRow;
                pTileAnimation->tileAnim = *FindRoomTileAnimation((s16)(pActor->pos.x >> 16), (s16)(pActor->pos.y >> 16));
                break;
            case RoomActorType_TriggerZone:
            case RoomActorType_TriggerRect:
                pTriggerZone = &g_pRoomActorStateBuffer->aTriggerZone[g_pRoomActorStateBuffer->bTriggerZoneCount++];
                pTriggerZone->bTileCol = pActor->bRoomRecordCol;
                pTriggerZone->bTileRow = pActor->bRoomRecordRow;
                pTriggerZone->dwFlags = pActor->dwFlags;
                pTriggerZone->bActionState = pActor->bActionState;
                pTriggerZone->dwStateTimer = pActor->dwStateTimer;
                break;
            case RoomActorType_WorldActor:
                if (((*(u32 *)&pStatic->bBreakable & 0xFF0000FF) == 0 && pStatic->bPushable == 0)
                    || pStatic->bKind == 9 || pStatic->bKind == 4)
                {
                    pPresence = &g_pRoomActorStateBuffer->aPresenceMarker[g_pRoomActorStateBuffer->bPresenceMarkerCount++];
                    pPresence->bTileCol = pActor->bRoomRecordCol;
                    pPresence->bTileRow = pActor->bRoomRecordRow;
                }
                else if (WORLD_ACTOR_STATE(pActor)->bKind == 0x33)
                {
                    pSwitch = &g_pRoomActorStateBuffer->aWorldActorSwitch[g_pRoomActorStateBuffer->bWorldActorSwitchCount++];
                    pSwitch->bTileCol = pActor->bRoomRecordCol;
                    pSwitch->bTileRow = pActor->bRoomRecordRow;
                    pSwitch->bConsumed = ((pActor->dwFlags >> 2) ^ 1) & 1;
                }
                else
                {
                    pWorldActor = &g_pRoomActorStateBuffer->aWorldActor[g_pRoomActorStateBuffer->bWorldActorCount++];
                    pWorldActor->bTileCol = pActor->bRoomRecordCol;
                    pWorldActor->bTileRow = pActor->bRoomRecordRow;
                    pWorldActor->bActionSubState = pActor->bActionSubState;
                    pWorldActor->bDepthSortBias = pActor->bDepthSortBias;
                    pWorldActor->dwFlags = pActor->dwFlags & ~ActorFlagHasPaletteSlot;
                    pWorldActor->wTimedMoveTicks = pActor->wTimedMoveTicks;
                    pWorldActor->anim = pActor->anim;
                    pWorldActor->wPosX = (s16)(pActor->pos.x >> 16);
                    pWorldActor->wPosY = (s16)(pActor->pos.y >> 16);
                    pWorldActor->vel = pActor->vel;
                    pWorldActor->accel = pActor->accel;
                    pWorldActor->bBrokenFrame = WORLD_ACTOR_STATE(pActor)->bBrokenFrame;
                    pWorldActor->bScriptStateLow = pActor->scriptState.bytes.bAttackOutcomeState;
                }
                break;
            case RoomActorType_Door:
            case RoomActorType_PushResetButton:
            case RoomActorType_SpongifyPad:
                pPresence = &g_pRoomActorStateBuffer->aPresenceMarker[g_pRoomActorStateBuffer->bPresenceMarkerCount++];
                pPresence->bTileCol = pActor->bRoomRecordCol;
                pPresence->bTileRow = pActor->bRoomRecordRow;
                break;
            default:
                if (pActor->wActorType == RoomActorType_Npc && pStatic->bPushable == 0)
                {
                    pPresence = &g_pRoomActorStateBuffer->aPresenceMarker[g_pRoomActorStateBuffer->bPresenceMarkerCount++];
                    pPresence->bTileCol = pActor->bRoomRecordCol;
                    pPresence->bTileRow = pActor->bRoomRecordRow;
                    break;
                }
                pDefault = &g_pRoomActorStateBuffer->aDefault[g_pRoomActorStateBuffer->bDefaultCount++];
                pDefault->bTileCol = pActor->bRoomRecordCol;
                pDefault->bTileRow = pActor->bRoomRecordRow;
                pDefault->dwFlags = pActor->dwFlags & ~ActorFlagHasPaletteSlot;
                pDefault->nMoveSpeed = pActor->nMoveSpeed;
                pDefault->wTimedMoveTicks = pActor->wTimedMoveTicks;
                pDefault->wActionVariant = pActor->wActionVariant;
                if (pActor->pShadowActor != NULL)
                {
                    pDefault->abShadowTile[0] = pActor->pShadowActor->bRoomRecordCol;
                    pDefault->abShadowTile[1] = pActor->pShadowActor->bRoomRecordRow;
                }
                if (pActor->pLinkedActor != NULL)
                {
                    pDefault->abLinkedTile[0] = pActor->pLinkedActor->bRoomRecordCol;
                    pDefault->abLinkedTile[1] = pActor->pLinkedActor->bRoomRecordRow;
                }
                if (pActor->pOwnerActor != NULL)
                {
                    pDefault->abOwnerTile[0] = pActor->pOwnerActor->bRoomRecordCol;
                    pDefault->abOwnerTile[1] = pActor->pOwnerActor->bRoomRecordRow;
                }
                pDefault->bFacing = pActor->bFacing;
                pDefault->anim = pActor->anim;
                pDefault->script = *(RoomActorScriptBlock *)&pActor->scriptState;
                pDefault->wMoveTargetX = pActor->moveTarget.x >> 16;
                pDefault->wMoveTargetY = pActor->moveTarget.y >> 16;
                pDefault->wPosX = (s16)(pActor->pos.x >> 16);
                pDefault->wPosY = (s16)(pActor->pos.y >> 16);
                pDefault->vel = pActor->vel;
                pDefault->bActionState = pActor->bActionState;
                pDefault->bActionSubState = pActor->bActionSubState;
                pDefault->bRoomActorKind = pActor->bKind;
                pDefault->bFighterIndex = pActor->bFighterIndex;
                pDefault->dwStateTimer = pActor->dwStateTimer;
                break;
            }
        }
        else if (pActor->wActorType == RoomActorType_WanderingMonster)
        {
            pMonster = &g_pRoomActorStateBuffer->aWanderingMonster[g_pRoomActorStateBuffer->bWanderingMonsterCount++];
            pMonster->wActorType = pActor->wActorType;
            pMonster->pos = pActor->pos;
            pMonster->moveTarget = pActor->moveTarget;
            pMonster->vel = pActor->vel;
            pMonster->bFacing = pActor->bFacing;
            pMonster->wMonsterId = pActor->bKind;
            pMonster->bEncounterId = pActor->bFighterIndex;
            pMonster->bEncounterVariant = pActor->bEncounterVariant;
            pMonster->bKind = pActor->bReceivedRewardId;
        }
    }
}
