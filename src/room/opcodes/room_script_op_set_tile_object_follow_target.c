#include "types.h"
#include "graphics/object.h"
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

void RoomScriptOpSetTileObjectFollowTarget(SetTileObjectFollowTargetRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);
    Object *pTarget;

    if (pRecord->bUseTargetTile != 0)
        pTarget = GetRoomObjectField_candidate(pRecord->bTargetTileX, pRecord->bTargetTileY);
    else
        pTarget = g_OverworldControlState.aSlots[0].pObject;
    pObject->pShadowObject = pTarget;
    // Codegen construct: the ROM re-reads bUseTargetTile here and discards it, the trace of a
    // second test whose identical arms were merged. The original arms are unknown.
    if (pRecord->bUseTargetTile != 0)
        pObject->bFollowResumeDistance = pRecord->bResumeDistance;
    else
        pObject->bFollowResumeDistance = pRecord->bResumeDistance;
    pObject->bFollowStopDistance = pRecord->bStopDistance;
    SetObjectActionSubState(pObject, 6);
    SetObjectActionState(pObject, 0x12);
}
