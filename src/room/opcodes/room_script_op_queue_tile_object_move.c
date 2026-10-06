#include "types.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

typedef struct QueueTileObjectMoveRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bRespawnRow;
    u8 bChainRow;
    s16 nSpeed;
    u16 wDelayFrames;
} QueueTileObjectMoveRecord;

void RoomScriptOpQueueTileObjectMove(QueueTileObjectMoveRecord *pRecord)
{
    Object *pControlled = g_OverworldControlState.aSlots[g_OverworldControlState.bSlotIndex].pObject;
    Object *pTarget;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    pTarget = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);
    if (g_dwRoomScriptRunState == 2)
        g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].dwResumeScript = 1;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].nStep = sub_0802C148(pRecord->nSpeed);
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].wCounter = pRecord->wDelayFrames;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].pTarget = pTarget;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bRespawnRow = pRecord->bRespawnRow;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bChainRow = pRecord->bChainRow;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bState = 1;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bSavedActionSubState = pControlled->bActionSubState;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].savedVel = *(ObjectVelocity *)&pControlled->nVelX;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bChainRan = 0;
    pControlled->nVelX = 0;
    pControlled->nVelY = 0;
}
