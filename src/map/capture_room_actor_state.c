#include "types.h"
#include "actor.h"
#include "area.h"
#include "flipbook.h"
#include "hero.h"
#include "mem.h"
#include "world_actors.h"
#include "map.h"

// Records the player and every room actor that differs from its default
// state into g_pRoomActorStateBuffer; see docs/formats/save.md.
void CaptureRoomActorState(void)
{
    Actor *pActor;
    RoomActorRecordProp *pStatic;
    RoomActorPickupRecord *pPickup;
    RoomActorFloorItemRecord *pFloorItem;
    RoomActorKind4Or7Record *pKind4Or7;
    RoomActorSwitchRecord *pSwitch;
    RoomActorKind5Record *pKind5;
    RoomActorTileRecord *pPresence;
    RoomActorDefaultRecord *pDefault;
    RoomActorWanderingMonsterRecord *pMonster;

    memset(g_pRoomActorStateBuffer, 0, ROOM_ACTOR_STATE_BUFFER_SIZE);
    g_pRoomActorStateBuffer->playerPos = g_pPlayerActor->pos;
    g_pRoomActorStateBuffer->bPlayerFacing = g_pPlayerActor->bFacing;
    g_pRoomActorStateBuffer->bSwitchState = g_bRoomSwitchState;

    for (pActor = (Actor *)g_ActiveActorListState.pHead; pActor != NULL; pActor = (Actor *)pActor->node.pNext)
    {
        if (pActor->bRoomTileCol_candidate != 0xFF)
        {
            pStatic = GetRoomActorStaticRecord(pActor->bRoomTileCol_candidate, pActor->bRoomTileRow_candidate);
            switch (pActor->wActorType)
            {
            case 11:
                pPickup = &g_pRoomActorStateBuffer->aPickupMarker[g_pRoomActorStateBuffer->bPickupMarkerCount++];
                pPickup->bTileCol = pActor->bRoomTileCol_candidate;
                pPickup->bTileRow = pActor->bRoomTileRow_candidate;
                pPickup->bStateTimer = pActor->dwStateTimer;
                pPickup->bActionSubState = pActor->bActionSubState;
                break;
            case 1:
                pFloorItem = &g_pRoomActorStateBuffer->aFloorItem[g_pRoomActorStateBuffer->bFloorItemCount++];
                pFloorItem->bTileCol = pActor->bRoomTileCol_candidate;
                pFloorItem->bTileRow = pActor->bRoomTileRow_candidate;
                pFloorItem->tileAnim = *FindRoomTileAnimation((s16)(pActor->pos.x >> 16), (s16)(pActor->pos.y >> 16));
                break;
            case 4:
            case 7:
                pKind4Or7 = &g_pRoomActorStateBuffer->aKind4Or7[g_pRoomActorStateBuffer->bKind4Or7Count++];
                pKind4Or7->bTileCol = pActor->bRoomTileCol_candidate;
                pKind4Or7->bTileRow = pActor->bRoomTileRow_candidate;
                pKind4Or7->dwFlags = pActor->dwFlags;
                pKind4Or7->bActionState = pActor->bActionState;
                pKind4Or7->dwStateTimer = pActor->dwStateTimer;
                break;
            case 5:
                if (((*(u32 *)&pStatic->b64 & 0xFF0000FF) == 0 && pStatic->b63 == 0)
                    || pStatic->bKind == 9 || pStatic->bKind == 4)
                {
                    pPresence = &g_pRoomActorStateBuffer->aPresenceMarker[g_pRoomActorStateBuffer->bPresenceMarkerCount++];
                    pPresence->bTileCol = pActor->bRoomTileCol_candidate;
                    pPresence->bTileRow = pActor->bRoomTileRow_candidate;
                }
                else if (ROOM_ACTOR_TRIGGER_STATE(pActor)->bKind == 0x33)
                {
                    pSwitch = &g_pRoomActorStateBuffer->aKind5Switch[g_pRoomActorStateBuffer->bKind5SwitchCount++];
                    pSwitch->bTileCol = pActor->bRoomTileCol_candidate;
                    pSwitch->bTileRow = pActor->bRoomTileRow_candidate;
                    pSwitch->bConsumed = ((pActor->dwFlags >> 2) ^ 1) & 1;
                }
                else
                {
                    pKind5 = &g_pRoomActorStateBuffer->aKind5[g_pRoomActorStateBuffer->bKind5Count++];
                    pKind5->bTileCol = pActor->bRoomTileCol_candidate;
                    pKind5->bTileRow = pActor->bRoomTileRow_candidate;
                    pKind5->bActionSubState = pActor->bActionSubState;
                    pKind5->bDepthSortBias = pActor->bDepthSortBias;
                    pKind5->dwFlags = pActor->dwFlags & ~ActorFlagHasPaletteSlot;
                    pKind5->wTimedMoveTicks = pActor->wTimedMoveTicks;
                    pKind5->anim = pActor->anim;
                    pKind5->wPosX = (s16)(pActor->pos.x >> 16);
                    pKind5->wPosY = (s16)(pActor->pos.y >> 16);
                    pKind5->vel = pActor->vel;
                    pKind5->accel = pActor->accel;
                    pKind5->bRoomActorArg67 = pActor->modeState.actor.bRoomActorArg67_candidate;
                    pKind5->bScriptStateLow = pActor->scriptState.bytes.bAttackOutcomeState;
                }
                break;
            case 2:
            case 8:
            case 10:
                pPresence = &g_pRoomActorStateBuffer->aPresenceMarker[g_pRoomActorStateBuffer->bPresenceMarkerCount++];
                pPresence->bTileCol = pActor->bRoomTileCol_candidate;
                pPresence->bTileRow = pActor->bRoomTileRow_candidate;
                break;
            default:
                if (pActor->wActorType == 6 && pStatic->b63 == 0)
                {
                    pPresence = &g_pRoomActorStateBuffer->aPresenceMarker[g_pRoomActorStateBuffer->bPresenceMarkerCount++];
                    pPresence->bTileCol = pActor->bRoomTileCol_candidate;
                    pPresence->bTileRow = pActor->bRoomTileRow_candidate;
                    break;
                }
                pDefault = &g_pRoomActorStateBuffer->aDefault[g_pRoomActorStateBuffer->bDefaultCount++];
                pDefault->bTileCol = pActor->bRoomTileCol_candidate;
                pDefault->bTileRow = pActor->bRoomTileRow_candidate;
                pDefault->dwFlags = pActor->dwFlags & ~ActorFlagHasPaletteSlot;
                pDefault->nMoveSpeed = pActor->nMoveSpeed;
                pDefault->wTimedMoveTicks = pActor->wTimedMoveTicks;
                pDefault->wActionVariant = pActor->wActionVariant;
                if (pActor->pShadowActor != NULL)
                {
                    pDefault->abShadowTile[0] = pActor->pShadowActor->bRoomTileCol_candidate;
                    pDefault->abShadowTile[1] = pActor->pShadowActor->bRoomTileRow_candidate;
                }
                if (pActor->pLinkedActor_candidate != NULL)
                {
                    pDefault->abLinkedTile[0] = pActor->pLinkedActor_candidate->bRoomTileCol_candidate;
                    pDefault->abLinkedTile[1] = pActor->pLinkedActor_candidate->bRoomTileRow_candidate;
                }
                if (pActor->pOwnerActor != NULL)
                {
                    pDefault->abOwnerTile[0] = pActor->pOwnerActor->bRoomTileCol_candidate;
                    pDefault->abOwnerTile[1] = pActor->pOwnerActor->bRoomTileRow_candidate;
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
                pDefault->bRoomActorKind = pActor->bRoomActorKind_candidate;
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
            pMonster->wMonsterId = pActor->bRoomActorKind_candidate;
            pMonster->bEncounterId = pActor->bFighterIndex;
            pMonster->bEncounterVariant = pActor->bEncounterVariant;
            pMonster->bKind = pActor->bReceivedRewardId;
        }
    }
}
