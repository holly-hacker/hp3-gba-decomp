#include "types.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

typedef struct SetTileActorFollowTargetRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bTargetTileX;
    u8 bTargetTileY;
    u8 bUseTargetTile;  // 0 follows the controlled player actor
    u8 bResumeDistance;
    u8 bStopDistance;
} SetTileActorFollowTargetRecord;

// Action state 0x12 (tick at 0x08005094) follows pShadowActor: while walking it stops within
// the stop distance, and walks again once farther than both distances.
void RoomScriptOpSetTileActorFollowTarget(SetTileActorFollowTargetRecord *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);
    Actor *pTarget;

    if (pRecord->bUseTargetTile != 0)
        pTarget = GetRoomActorField_candidate(pRecord->bTargetTileX, pRecord->bTargetTileY);
    else
        pTarget = g_OverworldControlState.aSlots[0].pActor;
    pActor->pShadowActor = pTarget;
    // Codegen construct: the ROM re-reads bUseTargetTile here and discards it, the trace of a
    // second test whose identical arms were merged. The original arms are unknown.
    if (pRecord->bUseTargetTile != 0)
        pActor->modeState.actor.bFollowResumeDistance = pRecord->bResumeDistance;
    else
        pActor->modeState.actor.bFollowResumeDistance = pRecord->bResumeDistance;
    pActor->modeState.actor.bFollowStopDistance = pRecord->bStopDistance;
    SetActorActionSubState(pActor, 6);
    SetActorActionState(pActor, 0x12);
}
