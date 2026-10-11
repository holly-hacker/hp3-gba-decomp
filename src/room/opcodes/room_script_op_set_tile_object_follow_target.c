#include "types.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectFollowTargetRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bTargetTileX;
    u8 bTargetTileY;
    u8 bUseTargetTile;  // 0 follows the controlled player object
    u8 bResumeDistance;
    u8 bStopDistance;
} SetTileObjectFollowTargetRecord;

// Action state 0x12 (tick at 0x08005094) follows pShadowActor: while walking it stops within
// the stop distance, and walks again once farther than both distances.
void RoomScriptOpSetTileObjectFollowTarget(SetTileObjectFollowTargetRecord *pRecord)
{
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);
    Actor *pTarget;

    if (pRecord->bUseTargetTile != 0)
        pTarget = GetRoomObjectField_candidate(pRecord->bTargetTileX, pRecord->bTargetTileY);
    else
        pTarget = g_OverworldControlState.aSlots[0].pObject;
    pObject->pShadowActor = pTarget;
    // Codegen construct: the ROM re-reads bUseTargetTile here and discards it, the trace of a
    // second test whose identical arms were merged. The original arms are unknown.
    if (pRecord->bUseTargetTile != 0)
        pObject->modeState.actor.bFollowResumeDistance = pRecord->bResumeDistance;
    else
        pObject->modeState.actor.bFollowResumeDistance = pRecord->bResumeDistance;
    pObject->modeState.actor.bFollowStopDistance = pRecord->bStopDistance;
    SetActorActionSubState(pObject, 6);
    SetActorActionState(pObject, 0x12);
}
